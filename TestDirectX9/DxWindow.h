#pragma once

#include "Resource.h"
#include <d3d9.h>

class CDxWindow : public CFrameWindowImpl<CDxWindow>
{
private:
	IDirect3D9       *m_pDirect3D;
	IDirect3DDevice9 *m_pDevice;

public:
	CDxWindow();
	~CDxWindow();

	void Render();

	LRESULT OnCreate(CREATESTRUCT *lpcs);
	LRESULT OnClose();
	LRESULT OnDestroy();
	LRESULT OnSize(UINT uParam, const CSize& size);

	DECLARE_FRAME_WND_CLASS(_T("CS_DX_WINDOW32-DxTest"), IDR_MAINFRAME);

	BEGIN_MSG_MAP(CDxWindow)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(CFrameWindowImpl<CDxWindow>)
	END_MSG_MAP()

};

