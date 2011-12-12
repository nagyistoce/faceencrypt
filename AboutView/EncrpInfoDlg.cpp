// EncrpInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../FaceEncrypt.h"
#include "EncrpInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEncrpInfoDlg dialog


CEncrpInfoDlg::CEncrpInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncrpInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncrpInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_info = _T("");
	//}}AFX_DATA_INIT
}


void CEncrpInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncrpInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEncrpInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CEncrpInfoDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncrpInfoDlg message handlers
void CEncrpInfoDlg::SetInfo(CString info)
{
	m_info = info;
}

BOOL CEncrpInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != NULL)
	{
		UINT ct = pSysMenu->GetMenuItemCount();
		for(int i=0;i<ct;++i)
		{
			CString txt(_T(""));
			pSysMenu->GetMenuString(i,txt,MF_BYPOSITION);
			if(txt.Find("¹Ø±Õ") != -1)
			{
				pSysMenu->EnableMenuItem(pSysMenu->GetMenuItemID(i),MF_DISABLED | MF_GRAYED);
			}
		}
	}
	
	m_flag = 0;
	SetTimer(1,200,NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEncrpInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	m_flag = 1;
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CEncrpInfoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_flag == 3)
	{
		CDialog::OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}

LRESULT CEncrpInfoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == WM_SHOWWINDOW)
	{
		m_flag = 1;
	}
	else if(message == WM_CLOSE)
	{
		m_flag = 0;
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}
