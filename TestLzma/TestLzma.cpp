// TestLzma.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LzmaDec.h"

#define BUFFER_SIZE (64*1024)

static void *SzAlloc(void *p, size_t size) { p = p; return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE); }
static void SzFree(void *p, void *address) { p = p; VirtualFree(address, 0, MEM_RELEASE); }
static ISzAlloc g_Alloc = { SzAlloc, SzFree };

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFileIn  = ::CreateFile(_T("C:\\Users\\Christoph\\Desktop\\S.csv.lzma"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFileOut = ::CreateFile(_T("C:\\Users\\Christoph\\Desktop\\S.csv.decd"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BYTE header[LZMA_PROPS_SIZE + 8];
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;
	::ReadFile(hFileIn, header, sizeof(header), &dwBytesRead, NULL);

	ELzmaStatus status;
	CLzmaDec state;
	LzmaDec_Construct(&state);
	LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &g_Alloc);
	LzmaDec_Init(&state);

	__int64 nSize = *reinterpret_cast<__int64*>(header + LZMA_PROPS_SIZE);
	_tprintf(_T("Extracted size: %d\n"), nSize);

	BYTE *pDataIn  = new BYTE[BUFFER_SIZE];
	BYTE *pDataOut = new BYTE[BUFFER_SIZE];

	size_t nTotalSize = (size_t)nSize;
	size_t nInSize = BUFFER_SIZE, nInPos = 0;
	size_t nOutSize = BUFFER_SIZE;

	while (nTotalSize)
	{
		if (!::ReadFile(hFileIn, pDataIn, BUFFER_SIZE, &dwBytesRead, NULL)) break;
		if (dwBytesRead == 0) break;
		nInSize = dwBytesRead;
		nInPos = 0;
		_tprintf(_T("."));
		
		while (nInPos < nInSize)
		{
			size_t nInProcessed  = nInSize - nInPos;
			size_t nOutProcessed = BUFFER_SIZE;
			LzmaDec_DecodeToBuf(&state, pDataOut, &nOutProcessed,
				                        pDataIn + nInPos, &nInProcessed,
										(nOutProcessed > nTotalSize)? LZMA_FINISH_END : LZMA_FINISH_ANY,
										&status);
			::WriteFile(hFileOut, pDataOut, nOutProcessed, &dwBytesRead, NULL);
			nInPos += nInProcessed;
			nTotalSize -= nOutProcessed;

			if (nInProcessed == 0 && nOutProcessed == 0)
			{
				nInPos = nInSize = 0;
				nTotalSize = 0;
			}
		}
	}

	delete[] pDataOut;
	delete[] pDataIn;

	LzmaDec_Free(&state, &g_Alloc);

	::CloseHandle(hFileOut);
	::CloseHandle(hFileIn);

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif
	return 0;
}

