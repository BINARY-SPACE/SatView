// SATELLITETRACKING.CPP : Satellite Tracking Tool Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the satellite tracking
// tool related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/08/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef SATELLITETRACKING



/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneViewMessageBar

IMPLEMENT_DYNCREATE(CSpaceSceneViewMessageBar, CMFCCaptionBar)

CSpaceSceneViewMessageBar::CSpaceSceneViewMessageBar() : CMFCCaptionBar()
{
	m_sizeSymbol.cx = m_sizeSymbol.cy = 0;
	m_clrBarBorder = SPACESCENEVIEWMESSAGEBAR_COLOR_BORDER;
	m_clrBarBackground = SPACESCENEVIEWMESSAGEBAR_COLOR_BACKGROUND;
	m_bContent = FALSE;
}

BOOL CSpaceSceneViewMessageBar::Create(CFrameWnd *pParentWnd)
{
	if (CMFCCaptionBar::Create(WS_CHILD | WS_CLIPSIBLINGS, pParentWnd, AFX_IDW_DOCKBAR_TOP, -1, TRUE))
	{
		SetFlatBorder(FALSE);
		SetBorderSize(0);
		return TRUE;
	}
	return FALSE;
}

VOID CSpaceSceneViewMessageBar::SetBorderColor(COLORREF nColor)
{
	m_clrBarBorder = nColor;
}

COLORREF CSpaceSceneViewMessageBar::GetBorderColor() CONST
{
	return m_clrBarBorder;
}

VOID CSpaceSceneViewMessageBar::SetBackgroundColor(COLORREF nColor)
{
	m_clrBarBackground = nColor;
}

COLORREF CSpaceSceneViewMessageBar::GetBackgroundColor() CONST
{
	return m_clrBarBackground;
}

VOID CSpaceSceneViewMessageBar::SetIconSize()
{
	SetIconSize(CSize(0, 0));
}
VOID CSpaceSceneViewMessageBar::SetIconSize(CONST SIZE &size)
{
	m_sizeSymbol = size;
}

CSize CSpaceSceneViewMessageBar::GetIconSize() CONST
{
	return m_sizeSymbol;
}

VOID CSpaceSceneViewMessageBar::ShowMessage(LPCTSTR pszMessage, UINT nType, BarElementAlignment nAlignment, BOOL bSound)
{
	CDC  *pDC;
	INT  nLine;
	INT  nLines;
	INT  nPos[3];
	BOOL  bIsFirst;
	BOOL  bIsBold;
	HICON  hSymbol;
	CSize  sizeSymbol;
	CString  szMessage;
	CStringArray  szLines;

	if (!pszMessage)
	{
		RemoveText();
		RemoveIcon();
		UpdateBar(FALSE);
		return;
	}
	for (m_strText = szMessage = pszMessage, m_arTextParts.RemoveAll(), m_bTextParts[0].RemoveAll(), m_bTextParts[1].RemoveAll(), m_textAlignment = nAlignment, nPos[0] = nPos[1] = -1; (nPos[0] = szMessage.Find(CR)) >= 0 || (nPos[1] = szMessage.Find(EOL)) >= 0; nPos[0] = nPos[1] = -1)
	{
		for (szLines.Add(((nPos[0] < nPos[1] || nPos[1] < 0) && nPos[0] >= 0) ? szMessage.Left((nPos[2] = nPos[0])) : szMessage.Left((nPos[2] = nPos[1]))); nPos[0] >= 0 && nPos[0] < szMessage.GetLength() - 1 && szMessage.GetAt(nPos[0] + 1) == EOL;)
		{
			nPos[2]++;
			break;
		}
		szMessage = szMessage.Mid(nPos[2] + 1);
	}
	if (!szMessage.IsEmpty())
	{
		szLines.Add(szMessage);
	}
	for (nLine = 0, nLines = (INT)szLines.GetSize(); nLine < nLines; nLine++)
	{
		for (nPos[0] = 0, bIsFirst = TRUE, bIsBold = FALSE; (nPos[1] = szLines.GetAt(nLine).Mid(nPos[0]).Find(BOLD)) >= 0; nPos[0] += nPos[1] + 1)
		{
			if (nPos[1] > 0)
			{
				m_arTextParts.Add(szLines.GetAt(nLine).Mid(nPos[0], nPos[1]));
				m_bTextParts[0].Add(bIsFirst);
				m_bTextParts[1].Add(bIsBold);
				bIsFirst = FALSE;
			}
			bIsBold = !bIsBold;
		}
		m_arTextParts.Add(szLines.GetAt(nLine).Mid(nPos[0]));
		m_bTextParts[0].Add(bIsFirst);
		m_bTextParts[1].Add(bIsBold);
		bIsFirst = FALSE;
	}
	for (sizeSymbol = m_sizeSymbol; !sizeSymbol.cx && !sizeSymbol.cy;)
	{
		if ((pDC = GetDC()))
		{
			sizeSymbol = GetTextSize(pDC, m_strText);
			sizeSymbol.cx = max(min(sizeSymbol.cy, GetSystemMetrics(SM_CXICON)), GetSystemMetrics(SM_CXSMICON));
			sizeSymbol.cy = max(min(sizeSymbol.cy, GetSystemMetrics(SM_CYICON)), GetSystemMetrics(SM_CYSMICON));
			ReleaseDC(pDC);
			break;
		}
		sizeSymbol.cx = GetSystemMetrics(SM_CXSMICON);
		sizeSymbol.cy = GetSystemMetrics(SM_CYSMICON);
		break;
	}
	switch (nType)
	{
	case MB_ICONINFORMATION:
	{ hSymbol = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_INFORMATIONSYMBOL), IMAGE_ICON, sizeSymbol.cx, sizeSymbol.cy, LR_DEFAULTCOLOR);
	break;
	}
	case MB_ICONWARNING:
	{ hSymbol = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_WARNINGSYMBOL), IMAGE_ICON, sizeSymbol.cx, sizeSymbol.cy, LR_DEFAULTCOLOR);
	break;
	}
	case MB_ICONERROR:
	{ hSymbol = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_ERRORSYMBOL), IMAGE_ICON, sizeSymbol.cx, sizeSymbol.cy, LR_DEFAULTCOLOR);
	break;
	}
	case MB_ICONQUESTION:
	{ hSymbol = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_QUESTIONSYMBOL), IMAGE_ICON, sizeSymbol.cx, sizeSymbol.cy, LR_DEFAULTCOLOR);
	break;
	}
	case MB_NEWS:
	{ hSymbol = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_NEWSSYMBOL), IMAGE_ICON, sizeSymbol.cx, sizeSymbol.cy, LR_DEFAULTCOLOR);
	break;
	}
	default:
	{ hSymbol = (HICON)NULL;
	break;
	}
	}
	for (SetIcon(hSymbol, nAlignment); bSound;)
	{
		AlertBySound((nType == MB_ICONINFORMATION) ? SND_ALIAS_SYSTEMDEFAULT : ((nType == MB_ICONWARNING) ? SND_ALIAS_SYSTEMEXCLAMATION : ((nType == MB_ICONERROR) ? SND_ALIAS_SYSTEMHAND : ((nType == MB_ICONQUESTION) ? SND_ALIAS_SYSTEMQUESTION : SND_ALIAS_SYSTEMDEFAULT))));
		break;
	}
	UpdateBar(TRUE);
}

BOOL CSpaceSceneViewMessageBar::HasContent() CONST
{
	return m_bContent;
}

VOID CSpaceSceneViewMessageBar::UpdateBar()
{
	UpdateBar(m_bContent);
}
VOID CSpaceSceneViewMessageBar::UpdateBar(BOOL bShow)
{
	ShowWindow(((m_bContent = bShow)) ? SW_SHOW : SW_HIDE);
}

CSatelliteTrackingToolWnd *CSpaceSceneViewMessageBar::GetParent() CONST
{
	return((CSatelliteTrackingToolWnd *)CMFCCaptionBar::GetParent());
}

void CSpaceSceneViewMessageBar::RecalcLayout()
{
	CRect  rBar[2];

	for (GetWindowRect(rBar[0]), rBar[1].SetRect(rBar[0].left, rBar[0].top, rBar[0].right, rBar[0].top + CalcFixedLayout(0, TRUE).cy), GetParent()->ScreenToClient(rBar[1]); rBar[0].Height() != rBar[1].Height();)
	{
		MoveWindow(rBar[1]);
		break;
	}
	CMFCCaptionBar::RecalcLayout();
	if (!m_rectImage.IsRectEmpty())
	{
		GetClientRect(rBar[0]);
		m_rectImage.SetRect(m_rectImage.left, (!m_rectDrawText.IsRectEmpty()) ? (m_rectDrawText.CenterPoint().y - m_rectImage.Height() / 2) : (rBar[0].CenterPoint().y - m_rectImage.Height() / 2), m_rectImage.right, (!m_rectDrawText.IsRectEmpty()) ? (m_rectDrawText.CenterPoint().y - m_rectImage.Height() / 2 + m_rectImage.Height()) : (rBar[0].CenterPoint().y - m_rectImage.Height() / 2 + m_rectImage.Height()));
	}
	if (!m_rectClose.IsRectEmpty())
	{
		GetClientRect(rBar[0]);
		m_rectClose = CRect(rBar[0].right - m_rectClose.Width() - GetMargin(), m_rectClose.top, rBar[0].right - GetMargin(), m_rectClose.top + m_rectClose.Height());
	}
}

CSize CSpaceSceneViewMessageBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CDC  *pDC;
	INT  nHeight[3];
	CRect  rBar;
	CSize  size;

	if ((pDC = GetDC()))
	{
		GetWindowRect(rBar);
		nHeight[0] = GetImageSize().cy;
		nHeight[1] = GetButtonRect().Height();
		nHeight[2] = GetTextSize(pDC, m_strText).cy;
		size = (nHeight[0] > 0 || nHeight[1] > 0 || nHeight[2] > 0) ? CSize(rBar.Width(), 2 * (GetMargin() + GetBorderSize()) + max(nHeight[0], max(nHeight[1], nHeight[2]))) : CSize(rBar.Width(), 0);
		ReleaseDC(pDC);
		return size;
	}
	return CSize(0, 0);
}

CSize CSpaceSceneViewMessageBar::GetTextSize(CDC *pDC, const CString &strText)
{
	INT  nPart;
	INT  nParts;
	CSize  sizePart;
	CSize  sizeLine;
	CSize  sizeText;
	CFont  *pOldFont;

	for (nPart = 0, nParts = (INT)m_arTextParts.GetSize(), sizeText.cx = sizeText.cy = sizeLine.cx = sizeLine.cy = 0; nPart < m_arTextParts.GetSize(); nPart++)
	{
		if (m_bTextParts[0][nPart])
		{
			sizeText.cx = max(sizeText.cx, sizeLine.cx);
			sizeText.cy += sizeLine.cy;
			sizeLine.cx = 0;
			sizeLine.cy = 0;
		}
		if (m_bTextParts[1][nPart])
		{
			if ((pOldFont = pDC->SelectObject(&afxGlobalData.fontBold)))
			{
				sizePart = pDC->GetTextExtent(m_arTextParts[nPart]);
				sizeLine.cx = (!m_bTextParts[0][nPart]) ? (sizeLine.cx + sizePart.cx) : sizePart.cx;
				sizeLine.cy = (!m_bTextParts[0][nPart]) ? max(sizeLine.cy, sizePart.cy) : sizePart.cy;
				pDC->SelectObject(pOldFont);
				continue;
			}
		}
		sizePart = pDC->GetTextExtent((!m_bTextParts[0][nPart] || !m_arTextParts[nPart].IsEmpty()) ? m_arTextParts[nPart] : SPACE);
		sizeLine.cx = (!m_bTextParts[0][nPart]) ? (sizeLine.cx + sizePart.cx) : ((!m_arTextParts[nPart].IsEmpty()) ? sizePart.cx : 0);
		sizeLine.cy = (!m_bTextParts[0][nPart]) ? max(sizeLine.cy, sizePart.cy) : sizePart.cy;
	}
	sizeText.cx = max(sizeText.cx, sizeLine.cx);
	sizeText.cy += sizeLine.cy;
	return sizeText;
}

BEGIN_MESSAGE_MAP(CSpaceSceneViewMessageBar, CMFCCaptionBar)
	//{{AFX_MSG_MAP(CSpaceSceneViewMessageBar)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneViewMessageBar message handlers

void CSpaceSceneViewMessageBar::OnDrawBorder(CDC *pDC, CRect rect)
{
	pDC->FillSolidRect(rect, m_clrBarBorder);
}

void CSpaceSceneViewMessageBar::OnDrawBackground(CDC *pDC, CRect rect)
{
	pDC->FillSolidRect(rect, m_clrBarBackground);
}

void CSpaceSceneViewMessageBar::OnDrawText(CDC *pDC, CRect rect, const CString &strText)
{
	INT  nPart;
	INT  nParts;
	CSize  sizePart;
	CSize  sizeLine;
	CFont  *pOldFont;
	CPoint  ptText;

	for (nPart = 0, nParts = (INT)m_arTextParts.GetSize(), ptText.x = rect.left, ptText.y = rect.top, sizeLine.cx = sizeLine.cy = 0; nPart < m_arTextParts.GetSize(); nPart++)
	{
		if (m_bTextParts[0][nPart])
		{
			ptText.x = rect.left;
			ptText.y += sizeLine.cy;
			sizeLine.cx = 0;
			sizeLine.cy = 0;
		}
		if (m_bTextParts[1][nPart])
		{
			if ((pOldFont = pDC->SelectObject(&afxGlobalData.fontBold)))
			{
				pDC->DrawText(m_arTextParts[nPart], CRect(min(ptText.x, rect.right), min(ptText.y, rect.bottom), rect.right, min(ptText.y + pDC->GetTextExtent(SPACE).cy, rect.bottom)), DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
				ptText.x += (sizePart = pDC->GetTextExtent(m_arTextParts[nPart])).cx;
				sizeLine.cx = (!m_bTextParts[0][nPart]) ? (sizeLine.cx + sizePart.cx) : sizePart.cx;
				sizeLine.cy = (!m_bTextParts[0][nPart]) ? max(sizeLine.cy, sizePart.cy) : sizePart.cy;
				pDC->SelectObject(pOldFont);
				continue;
			}
		}
		pDC->DrawText(m_arTextParts[nPart], CRect(min(ptText.x, rect.right), min(ptText.y, rect.bottom), rect.right, min(ptText.y + pDC->GetTextExtent(SPACE).cy, rect.bottom)), DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
		sizePart = pDC->GetTextExtent((!m_bTextParts[0][nPart] || !m_arTextParts[nPart].IsEmpty()) ? m_arTextParts[nPart] : SPACE);
		sizeLine.cx = (!m_bTextParts[0][nPart]) ? (sizeLine.cx + sizePart.cx) : ((!m_arTextParts[nPart].IsEmpty()) ? sizePart.cx : 0);
		sizeLine.cy = (!m_bTextParts[0][nPart]) ? max(sizeLine.cy, sizePart.cy) : sizePart.cy;
		ptText.x += (!m_arTextParts[nPart].IsEmpty()) ? sizePart.cx : 0;
	}
}

void CSpaceSceneViewMessageBar::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (!bShow)
	{
		RemoveText();
		RemoveIcon();
		m_bContent = FALSE;
	}
	GetParent()->RecalcLayout();
	CMFCCaptionBar::OnShowWindow(bShow, nStatus);
}


/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneView

IMPLEMENT_DYNCREATE(CSpaceSceneView, CSpaceView)

CSpaceSceneView::CSpaceSceneView() : CSpaceView()
{
	return;
}

CSatelliteTrackingToolWnd *CSpaceSceneView::GetParent() CONST
{
	return((CSatelliteTrackingToolWnd *)CView::GetParent());
}

BEGIN_MESSAGE_MAP(CSpaceSceneView, CSpaceView)
	//{{AFX_MSG_MAP(CSpaceSceneView)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneView message handlers

void CSpaceSceneView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	ShowFloatingMenu(pt);
	CSpaceView::OnRButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd

IMPLEMENT_DYNAMIC(CSatelliteTrackingToolWnd, CDisplayWnd)

CSatelliteTrackingToolWnd::CSatelliteTrackingToolWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_SATELLITETRACKINGTOOL);
	m_pwndSceneView = (CSpaceSceneView *)NULL;
	m_bInitialized = FALSE;
	m_bRunning = FALSE;
	m_bEnabled = TRUE;
}

CSatelliteTrackingToolWnd::~CSatelliteTrackingToolWnd()
{
	return;
}

BOOL CSatelliteTrackingToolWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle) ? STRING(IDS_DISPLAY_TITLE_SATELLITETRACKINGTOOL) : pszTitle, pDefaultInfo->rWnd, IDR_SATELLITETRACKINGTOOLFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode))
		{
			m_wndMessageBar.UpdateBar();
			RecalcLayout();
			return TRUE;
		}
		DestroyWindow();
	}
	return FALSE;
}

BOOL CSatelliteTrackingToolWnd::Start()
{
	for (Initialize(TRUE); m_bInitialized && !m_bRunning && m_bEnabled; )
	{
		if (m_pwndSceneView->Start())
		{
			m_bRunning = TRUE;
			return TRUE;
		}
		return FALSE;
	}
	return m_bInitialized;
}

BOOL CSatelliteTrackingToolWnd::Prepare(BOOL bDialog)
{
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_SATELLITETRACKINGTOOL_USE);
}

VOID CSatelliteTrackingToolWnd::Update()
{
	if (!Check())
	{
		ReportEvent((IsWindowVisible()) ? USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION : USER_NOERROR);
		ActivateFrame(SW_HIDE);
		return;
	}
	CDisplayWnd::Update();
}

BOOL CSatelliteTrackingToolWnd::Stop()
{
	if (m_bInitialized && m_bRunning && m_bEnabled)
	{
		if (m_pwndSceneView->Stop())
		{
			m_bRunning = FALSE;
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

VOID CSatelliteTrackingToolWnd::SetConfigurationFileName(LPCTSTR pszFileName)
{
	m_szConfigurationFileName = pszFileName;
}

CString CSatelliteTrackingToolWnd::GetConfigurationFileName() CONST
{
	return((m_szConfigurationFileName.IsEmpty()) ? ConstructConfiguratonFileName() : m_szConfigurationFileName);
}

VOID CSatelliteTrackingToolWnd::SetHelpFileName(LPCTSTR pszFileName)
{
	m_szHelpFileName = pszFileName;
}

CString CSatelliteTrackingToolWnd::GetHelpFileName() CONST
{
	return((m_szHelpFileName.IsEmpty()) ? ConstructHelpFileName() : m_szHelpFileName);
}

BOOL CSatelliteTrackingToolWnd::CalculateSpacecraftPasses(CSpacecraftPasses &pPasses) CONST
{
	return m_pwndSceneView->CalculateSpacecraftPasses(pPasses);
}

BOOL CSatelliteTrackingToolWnd::CalculateSpacecraftInterlinks(CSpacecraftInterlinks &pInterlinks) CONST
{
	return m_pwndSceneView->CalculateSpacecraftInterlinks(pInterlinks);
}

BOOL CSatelliteTrackingToolWnd::CalculateSpacecraftOrbit(CSpacecraft *pSpacecraft, CONST CTimeKey &tTime) CONST
{
	return m_pwndSceneView->CalculateSpacecraftOrbit(pSpacecraft, tTime);
}

BOOL CSatelliteTrackingToolWnd::CalculateSpacecraftState(CONST CSpacecraft *pSpacecraft, CONST CTimeKey &tTime, StateVector &sState) CONST
{
	return m_pwndSceneView->CalculateSpacecraftOrbit(pSpacecraft, tTime, sState);
}

BOOL CSatelliteTrackingToolWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	CProfile  cProfile;

	return(CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && cProfile.SetToolsSatelliteTrackingOptionsInfo(m_szConfigurationFileName, m_szHelpFileName, m_bEnabled));
}

BOOL CSatelliteTrackingToolWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	CProfile  cProfile;

	return(CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetToolsSatelliteTrackingOptionsInfo(m_szConfigurationFileName, m_szHelpFileName, m_bEnabled));
}

BOOL CSatelliteTrackingToolWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_GLOBAL;
	pDefaultInfo->nMode = DISPLAY_MODE_REALTIME;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = FALSE;
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	cImages.DeleteImageList();
	nImageIDs.RemoveAll();
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::ShowMessage(LPCTSTR pszMessage, UINT nType, CMFCCaptionBar::BarElementAlignment nAlignment, BOOL bSound)
{
	if (nType != (UINT)-1)
	{
		if (IsWindow(m_wndMessageBar.GetSafeHwnd()) && pszMessage != (LPCTSTR)NULL)
		{
			m_wndMessageBar.ShowMessage(pszMessage, nType, nAlignment, bSound);
			RecalcLayout();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSatelliteTrackingToolWnd::ShowProgress(LPCTSTR pszAction, INT nProgress)
{
	return TRUE;
}

BOOL CALLBACK CSatelliteTrackingToolWnd::ShowMessageProc(CONST CView* pView, Message::Type nType, LPCTSTR pszText, BOOL bSound)
{
	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	return(((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetMainWnd()->GetGlobalDisplay())) ? pSatelliteTrackingToolWnd->ShowMessage(pszText, nType, CMFCCaptionBar::ALIGN_CENTER, bSound) : FALSE);
}

BOOL CALLBACK CSatelliteTrackingToolWnd::ShowProgressProc(CONST CView*, LPCTSTR pszAction, INT nProgress)
{
	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	return(((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetMainWnd()->GetGlobalDisplay())) ? pSatelliteTrackingToolWnd->ShowProgress(pszAction, nProgress) : FALSE);
}

CString CSatelliteTrackingToolWnd::ConstructConfiguratonFileName() CONST
{
	CString  szDirectory;
	CModuleToken  cModuleToken;
	CLogicalDrives  cLogicalDrives;

	return((!(szDirectory = cModuleToken.GetModuleFileRoot()).IsEmpty() && szDirectory.Right(1) != cLogicalDrives.GetPathDelimiter()) ? (szDirectory + cLogicalDrives.GetPathDelimiter() + STRING(IDS_SATELLITETRACKING_DEFAULTCONFIGURATIONFILENAME)) : (szDirectory + STRING(IDS_SATELLITETRACKING_DEFAULTCONFIGURATIONFILENAME)));
}

CString CSatelliteTrackingToolWnd::ConstructHelpFileName() CONST
{
	CString  szDirectory;
	CModuleToken  cModuleToken;
	CLogicalDrives  cLogicalDrives;

	return((!(szDirectory = cModuleToken.GetModuleFileRoot()).IsEmpty() && szDirectory.Right(1) != cLogicalDrives.GetPathDelimiter()) ? (szDirectory + cLogicalDrives.GetPathDelimiter() + STRING(IDS_SATELLITETRACKING_DEFAULTHELPFILENAME)) : (szDirectory + STRING(IDS_SATELLITETRACKING_DEFAULTHELPFILENAME)));
}

VOID CSatelliteTrackingToolWnd::Enable(BOOL bEnable)
{
	if (m_bEnabled != bEnable)
	{
		if (bEnable)
		{
			if (m_pwndSceneView->Start())
			{
				m_bEnabled = TRUE;
				return;
			}
			ReportEvent(SYSTEM_WARNING_DISPLAY_START_FAILURE);
			return;
		}
		if (m_pwndSceneView->Stop())
		{
			ActivateFrame(SW_HIDE);
			m_bEnabled = FALSE;
			return;
		}
		ReportEvent(SYSTEM_WARNING_DISPLAY_STOP_FAILURE);
	}
}

BOOL CSatelliteTrackingToolWnd::IsEnabled() CONST
{
	return m_bEnabled;
}

void CSatelliteTrackingToolWnd::RecalcLayout(BOOL bNotify)
{
	CRect  rBar;
	CRect  rView;

	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		if (IsWindow(m_wndMessageBar.GetSafeHwnd()))
		{
			for (GetClientRect(rView), rBar.SetRectEmpty(); m_wndMessageBar.HasContent();)
			{
				m_wndMessageBar.GetWindowRect(rBar);
				break;
			}
			m_pwndSceneView->MoveWindow(0, rBar.Height(), rView.Width(), rView.Height() - rBar.Height());
		}
	}
	CDisplayWnd::RecalcLayout(bNotify);
}

BEGIN_MESSAGE_MAP(CSatelliteTrackingToolWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CSatelliteTrackingToolWnd)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_INITMENU()
	ON_WM_SYSCOMMAND()
	ON_WM_MDIACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd message handlers

int CSatelliteTrackingToolWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nIndex;
	INT  nCount;
	INT  nItem[2];
	INT  nItems[2];
	UINT  nType;
	CMenu  *pMenu;
	CString  szMessages;
	CString  szMenuItem;
	Messages  cMessages;
	CLocaleMenu  cMenu;

	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		if ((pMenu = GetSystemMenu(FALSE)))
		{
			for (nItem[0] = 0, nItems[0] = (cMenu.LoadMenu(IDR_SATELLITETRACKINGTOOLFRAME)) ? pMenu->GetMenuItemCount() : -1; nItem[0] < nItems[0]; nItem[0]++)
			{
				if (pMenu->GetMenuItemID(nItem[0]) == SC_MAXIMIZE)
				{
					for (nItem[1] = 0, nItems[1] = cMenu.GetMenuItemCount(); nItem[1] < nItems[1]; nItem[1]++)
					{
						for (cMenu.GetMenuString(nItem[1], szMenuItem, MF_BYPOSITION); !nItem[1]; )
						{
							pMenu->InsertMenu(nItem[0] + 1, MF_BYPOSITION | MF_SEPARATOR);
							break;
						}
						pMenu->InsertMenu(nItem[0] + nItem[1] + 1 + 1, (!szMenuItem.IsEmpty()) ? (MF_BYPOSITION | MF_STRING) : (MF_BYPOSITION | MF_SEPARATOR), cMenu.GetMenuItemID(nItem[1]), szMenuItem);
					}
					break;
				}
			}
		}
		if (m_wndMessageBar.Create(this))
		{
			if ((m_pwndSceneView = new CSpaceSceneView))
			{
				if (m_pwndSceneView->Create(AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), (HBRUSH)NULL), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy), this, 0))
				{
					for (nIndex = 0, m_bInitialized = m_pwndSceneView->Initialize(GetConfigurationFileName(), EMPTYSTRING, GetHelpFileName(), FALSE, cMessages, ShowMessageProc, ShowProgressProc), nCount = (INT)cMessages.GetSize(), nType = Message::Type::None; nIndex < nCount; nIndex++)
					{
						nType = max((UINT)cMessages.GetAt(nIndex).GetType(), nType);
						szMessages += (!szMessages.IsEmpty()) ? (CString(CR) + EOL + CString(cMessages.GetAt(nIndex).GetText())) : CString(cMessages.GetAt(nIndex).GetText());
					}
					switch (nType)
					{
					case Message::Type::News:
					{
						ShowMessage(szMessages, MB_NEWS, CMFCCaptionBar::ALIGN_CENTER, FALSE);
						break;
					}
					case Message::Type::Informational:
					{
						ShowMessage(szMessages, MB_ICONINFORMATION, CMFCCaptionBar::ALIGN_CENTER, FALSE);
						break;
					}
					case Message::Type::Warning:
					{
						ShowMessage(szMessages, MB_ICONWARNING, CMFCCaptionBar::ALIGN_CENTER, FALSE);
						break;
					}
					case Message::Type::Error:
					{
						ShowMessage(szMessages, MB_ICONERROR, CMFCCaptionBar::ALIGN_CENTER, FALSE);
						break;
					}
					default:
					{
						ShowMessage(szMessages, -1, CMFCCaptionBar::ALIGN_CENTER, FALSE);
						break;
					}
					}
					LoadAccelTable(IDR_SATELLITETRACKINGTOOLFRAME);
					return 0;
				}
				m_pwndSceneView = (CSpaceSceneView *)NULL;
			}
		}
	}
	return -1;
}

LRESULT CSatelliteTrackingToolWnd::OnNcHitTest(CPoint point)
{
	LRESULT  lResult;

	for (lResult = CDisplayWnd::OnNcHitTest(point); IsWindow(m_pwndSceneView->GetSafeHwnd()); )
	{
		if (m_pwndSceneView->IsRecordingVideo())
		{
			switch (lResult)
			{
			case HTLEFT:
			case HTTOP:
			case HTTOPLEFT:
			case HTTOPRIGHT:
			case HTRIGHT:
			case HTBOTTOM:
			case HTBOTTOMLEFT:
			case HTBOTTOMRIGHT:
			case HTSIZE:
			case HTREDUCE:
			case HTZOOM:
			{
				return HTNOWHERE;
			}
			default: break;
			}
		}
		break;
	}
	return lResult;
}

void CSatelliteTrackingToolWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	lpMMI->ptMinTrackSize.x = 2 * GetSystemMetrics(SM_CXFRAME) + SATELLITETRACKINGTOOL_MIN_WIDTH;
	lpMMI->ptMinTrackSize.y = 2 * GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + SATELLITETRACKINGTOOL_MIN_HEIGHT;
	CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CSatelliteTrackingToolWnd::OnSize(UINT nType, int cx, int cy)
{
	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		RecalcLayout();
	}
	CDisplayWnd::OnSize(nType, cx, cy);
}

BOOL CSatelliteTrackingToolWnd::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CSatelliteTrackingToolWnd::OnInitMenu(CMenu *pMenu)
{
	CMenu  *pSysMenu;

	if ((pSysMenu = GetSystemMenu(FALSE)))
	{
		if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
		{
			pSysMenu->EnableMenuItem(SC_MINIMIZE, (!m_pwndSceneView->IsRecordingVideo()) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_GRAYED));
			pSysMenu->EnableMenuItem(SC_MAXIMIZE, (!m_pwndSceneView->IsRecordingVideo()) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_GRAYED));
			pSysMenu->EnableMenuItem(IDM_HELP, (m_pwndSceneView->IsHelpAvailable()) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_GRAYED));
		}
		else
		{
			pSysMenu->EnableMenuItem(SC_MINIMIZE, MF_BYCOMMAND | MF_GRAYED);
			pSysMenu->EnableMenuItem(SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED);
			pSysMenu->EnableMenuItem(IDM_HELP, MF_BYCOMMAND | MF_GRAYED);
		}
	}
	CDisplayWnd::OnInitMenu(pMenu);
}

void CSatelliteTrackingToolWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	switch (nID)
	{
	case SC_MINIMIZE:
	case SC_MAXIMIZE:
	{
		if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
		{
			if (m_pwndSceneView->IsRecordingVideo()) return;
		}
		break;
	}
	case IDM_SATELLITETRACKINGTOOLHELP:
	{
		if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
		{
			m_pwndSceneView->ShowHelp();
		}
		break;
	}
	}
	CDisplayWnd::OnSysCommand(nID, lParam);
}

void CSatelliteTrackingToolWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		if (bActivate)
		{
			m_pwndSceneView->SetFocus();
		}
	}
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CSatelliteTrackingToolWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		m_pwndSceneView->SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

void CSatelliteTrackingToolWnd::OnMenuID(UINT nID)
{
	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		m_pwndSceneView->OnMenuID(nID);
	}
}

void CSatelliteTrackingToolWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CSatelliteTrackingToolWnd::OnUpdateMenuID(CCmdUI *pCmdUI)
{
	if (IsWindow(m_pwndSceneView->GetSafeHwnd()))
	{
		for (m_pwndSceneView->OnUpdateMenuID(pCmdUI); pCmdUI->m_nID == IDM_MULTIMEDIA_VIDEO_SAVETOFILE; )
		{
			if (m_wndMessageBar.IsVisible())
			{
				pCmdUI->Enable(FALSE);
			}
			break;
		}
	}
}

#else

/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd

IMPLEMENT_DYNAMIC(CSatelliteTrackingToolWnd, CDisplayWnd)

CSatelliteTrackingToolWnd::CSatelliteTrackingToolWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_SATELLITETRACKINGTOOL);
}

CSatelliteTrackingToolWnd::~CSatelliteTrackingToolWnd()
{
	return;
}

BOOL CSatelliteTrackingToolWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle) ? STRING(IDS_DISPLAY_TITLE_SATELLITETRACKINGTOOL) : pszTitle, pDefaultInfo->rWnd, IDR_SATELLITETRACKINGTOOLFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode))
		{
			return TRUE;
		}
		DestroyWindow();
	}
	return FALSE;
}

BOOL CSatelliteTrackingToolWnd::Start()
{
	Initialize(TRUE);
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::Prepare(BOOL bDialog)
{
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::Check() CONST
{
	return FALSE;
}

VOID CSatelliteTrackingToolWnd::Update()
{
	ActivateFrame(SW_HIDE);
	CDisplayWnd::Update();
}

BOOL CSatelliteTrackingToolWnd::Stop()
{
	return TRUE;
}

VOID CSatelliteTrackingToolWnd::SetConfigurationFileName(LPCTSTR pszFileName)
{
	return;
}

CString CSatelliteTrackingToolWnd::GetConfigurationFileName() CONST
{
	return EMPTYSTRING;
}

VOID CSatelliteTrackingToolWnd::SetHelpFileName(LPCTSTR pszFileName)
{
	return;
}

CString CSatelliteTrackingToolWnd::GetHelpFileName() CONST
{
	return EMPTYSTRING;
}

BOOL CSatelliteTrackingToolWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_GLOBAL;
	pDefaultInfo->nMode = DISPLAY_MODE_REALTIME;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = FALSE;
	return TRUE;
}

BOOL CSatelliteTrackingToolWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	cImages.DeleteImageList();
	nImageIDs.RemoveAll();
	return TRUE;
}

VOID CSatelliteTrackingToolWnd::ShowSideBars(BOOL bShow)
{
	return;
}

VOID CSatelliteTrackingToolWnd::Enable(BOOL bEnable)
{
	return;
}

BOOL CSatelliteTrackingToolWnd::IsEnabled() CONST
{
	return FALSE;
}

BEGIN_MESSAGE_MAP(CSatelliteTrackingToolWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CSatelliteTrackingToolWnd)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd message handlers


#endif
