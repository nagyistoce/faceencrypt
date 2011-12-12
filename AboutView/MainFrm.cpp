// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "../FaceEncrypt.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/********************����ͷ�ļ�************/
#include "../AboutView/DriveView.h"
#include "FaceEncryptView.h"
#include "CHooseOperation.h"
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    //cs.cx = 900;
    //cs.cy = 560;
    cs.style &= ~WS_MAXIMIZEBOX;//��ֹ���
    cs.style &= ~WS_THICKFRAME;//��ֹ������С
    //cs.style &= ~WS_MINIMIZEBOX;��ֹ��С��
    cs.lpszName = "˫����֤�ļ��м�/����";
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	//
	// Note: Create the CFileView first so the CDriveView's OnInitialUpdate
	// function can call OnUpdate on the CFileView.
	//
	//AfxMessageBox("In BOOL CMainFrame::OnCreateClient");
	CRect rect; 
    GetClientRect(&rect);
	//CString S1;
	//S1.Format("w=%d::h=%d",rect.Width(),rect.Height());
	//AfxMessageBox(S1);
    if (!m_splitter.CreateStatic(this, 1, 2) ||
        !m_splitter.CreateView (0, 0, RUNTIME_CLASS (CFaceEncryptView),
            CSize (rect.Width()-1,rect.Height()-1), pContext)	||
        !m_splitter.CreateView (0, 1, RUNTIME_CLASS (CChooseOperation),
            CSize (1,rect.Height()), pContext))
        return FALSE;
	SetFocus();
    return TRUE;
}
/*******************�л���ͼ************/
BOOL  CMainFrame::SwitchView(int falg){
	if(falg==1)
	{/**************��ÿͻ�����С***********/
	    CRect rc;
        GetClientRect(&rc);
		//CString S1;
		//S1.Format("w=%d::h=%d",rc.Width(),rc.Height());
	    //AfxMessageBox(S1);
        //ɾ��ԭ����ͼ
	    m_splitter.DeleteView(0,0);
        m_splitter.CreateView(0,0,RUNTIME_CLASS(CDriveView),CSize(rc.Width()*3/4,rc.Height()),NULL); 
        //m_splitter.SetColumnInfo( 0,rcRight.Width()*2/3,0);//���������ұߴ��ڴ�СΪ������ܴ��ڵ�2/3 
	    m_splitter.DeleteView(0,1);
		m_splitter.CreateView(0,1,RUNTIME_CLASS(CChooseOperation),CSize(rc.Width()*1/4,rc.Height()),NULL);
		m_splitter.RecalcLayout();//���²���
        //Invalidate();
	}
	 return true;
}
/*******************���ó�ʼ��С************/
void   CMainFrame::OnGetMinMaxInfo(MINMAXINFO   FAR*   lpMMI)  
{
//   TODO:   Add   your   message   handler   code   here   and/or   call   default

//lpMMI-> ptMinTrackSize.x=1024;
//lpMMI-> ptMinTrackSize.y=768;

CFrameWnd::OnGetMinMaxInfo(lpMMI);
} 