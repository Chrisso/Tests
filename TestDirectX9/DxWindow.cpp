#include "StdAfx.h"
#include "DxWindow.h"

///////////////////////////////////////////////////////////////////////////////
// Construction/ Destruction
///////////////////////////////////////////////////////////////////////////////

CDxWindow::CDxWindow() : m_pDirect3D(NULL), m_pDevice(NULL)
{
}

CDxWindow::~CDxWindow()
{
}

///////////////////////////////////////////////////////////////////////////////
// Windows Message Handling
///////////////////////////////////////////////////////////////////////////////

LRESULT CDxWindow::OnCreate(CREATESTRUCT *lpcs)
{
	LOGMSG_DEBUG(_T("Creating main window...\n"));

	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pDirect3D)
	{
		LOGMSG_ERROR(_T("Failed to create Direct3D9-Context!\n"));
		return 1;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect =  D3DSWAPEFFECT_DISCARD;;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	
	if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,  D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice)))
	{
		LOGMSG_INFO(_T("Fallback to software vertex processing.\n"));
		if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,  D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice)))
		{
			LOGMSG_ERROR(_T("Failed to create Direct3D9-Device!\n"));
			return 1;
		}
	}

	SetMsgHandled(FALSE);
	return 0;
}

LRESULT CDxWindow::OnClose()
{
	LOGMSG_DEBUG(_T("Closing main window...\n"));

	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if (m_pDirect3D)
	{
		m_pDirect3D->Release();
		m_pDirect3D = NULL;
	}

	DestroyWindow();
	return 0;
}

LRESULT CDxWindow::OnDestroy()
{
	LOGMSG_DEBUG(_T("Destroying main window...\n"));
	PostQuitMessage(0);
	return 0;
}

LRESULT CDxWindow::OnSize(UINT uParam, const CSize& size)
{
	SetMsgHandled(FALSE);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Method Implementation
///////////////////////////////////////////////////////////////////////////////

void CDxWindow::Render()
{
	ATLASSERT(m_pDevice != NULL);

	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(64, 64, 64), 1.0f, 0);
	m_pDevice->BeginScene();
		// TODO: Logic
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}
