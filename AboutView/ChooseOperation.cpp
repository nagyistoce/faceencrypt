// ChooseOperation.cpp : implementation file
//����ͷ�ļ�
#include "stdafx.h"
#include "../FaceEncrypt.h"
#include "ChooseOperation.h"
#include "MainFrm.h"
#include "FaceProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseOperation

IMPLEMENT_DYNCREATE(CChooseOperation, CFormView)

CChooseOperation::CChooseOperation()
	: CFormView(CChooseOperation::IDD)
{
	//{{AFX_DATA_INIT(CChooseOperation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CChooseOperation::~CChooseOperation()
{
}

void CChooseOperation::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseOperation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseOperation, CFormView)
	//{{AFX_MSG_MAP(CChooseOperation)
	 ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(IDC_UNCRYPT, OnUncrypt)
	ON_BN_CLICKED(IDC_ENCRYPT_INFO, OnEncryptInfo)
	 ON_WM_SIZE()
	 ON_WM_CREATE()
	ON_BN_CLICKED(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseOperation diagnostics

#ifdef _DEBUG
void CChooseOperation::AssertValid() const
{
	CFormView::AssertValid();
}

void CChooseOperation::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
CFaceEncryptDoc* CChooseOperation::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceEncryptDoc)));
	return (CFaceEncryptDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChooseOperation message handlers
/*void CChooseOperation::OnSize(UINT nType, int cx, int cy){
	  AfxMessageBox("OnSize()");
	  CWnd   *pMain=AfxGetMainWnd();
	  CRect  rc; 
	       pMain->GetClientRect(&rc);
	 CString S1;
		   S1.Format("w=%d::h=%d",rc.Width(),rc.Height());
	       AfxMessageBox(S1);
}*/
BOOL CChooseOperation::PreCreateWindow(CREATESTRUCT& cs)
{
//	AfxMessageBox("CChooseOperation::PreCreateWindow");
	if( !CFormView::PreCreateWindow(cs) )
		return FALSE;
             cs.cx=600;
		     cs.cy=480;
		return true;
}
/*******************���ó�ʼ��С************/
//��ʱ�������ã�û�б�����
void   CChooseOperation::OnGetMinMaxInfo(MINMAXINFO   FAR*   lpMMI){
	AfxMessageBox("OnGetMinMaxInfo()");
	lpMMI-> ptMinTrackSize.x=1024;
	lpMMI-> ptMinTrackSize.y=768;	
    CFormView::OnGetMinMaxInfo(lpMMI);
}
/*************CSize()�еĲ�����������**************/
BOOL CChooseOperation::Create(LPCTSTR c1, LPCTSTR c2, DWORD c3,const RECT& r1, CWnd* c4, UINT c5, CCreateContext* c6){
    //AfxMessageBox("Create()");
	//CFormView::SetScrollSizes(MM_TEXT,CSize(2000,200),sizeDefault,sizeDefault);
	return  CFormView::Create(c1,c2,c3,r1,c4,c5,c6);
}
///////////////////////////////////////////
////��ʼ��
void CChooseOperation::OnInitialUpdate(){
    CScrollView::OnInitialUpdate();
	//����Ϊ��Ч
	//GetDlgItem(IDC_ENCRYPT_INFO)->EnableWindow(FALSE);
	CMainFrame   *pMain=(CMainFrame *)AfxGetMainWnd();
	//���ó�ʼ����С
	CRect  rc1; 
	       pMain->GetClientRect(&rc1);
	//CString S1;
		   //S1.Format("w=%d::h=%d",rc1.Width(),rc1.Height());
	       //AfxMessageBox(S1);
	//CView* pView=(CView*)pMain->m_splitter.GetPane(0,1);
	CSize sizeTotal(0,0); // 
	CSize sizePage(sizeTotal.cx , sizeTotal.cy); //�����Scrollbar�հ���ʱ�������ƶ��ô�С
	CSize sizeLine(sizeTotal.cx , sizeTotal.cy); //���SCrollbar���������Ұ�ť
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

void CChooseOperation::OnEncrypt() 
{
	// TODO: Add your control notification handler code here
	CStaticAssistant::SetEncryptFlag(true);    //���ü��ܱ�־
	//��õ�ǰ����·�����Ҵ��ݸ�FaceProcess��
	CFaceEncryptDoc* pDoc = GetDocument();     
	    ASSERT_VALID(pDoc);
	CString  currentpath=pDoc->getSelectedPath();
	CStaticAssistant::SetCurrentPath(currentpath);    //���ü���·��
	//�жϵ�ǰ·���Ƿ��Ѿ�����
	BOOL isEncrypt=pDoc->IsEncrypt(currentpath);
	if(isEncrypt==TRUE){
		AfxMessageBox("��ѡ����ļ����Ѿ����ܣ������ظ����ܣ�лл����");
	   //���ò鿴������Ϣ��ťΪ��Ч
		GetDlgItem(IDC_ENCRYPT_INFO)->EnableWindow(TRUE);
		return ;
	}
	//��������ʶ��Ի���
	CFaceProcess  faceDlg;
                  faceDlg.DoModal();
	delete faceDlg;
}

void CChooseOperation::OnUncrypt() 
{
	// TODO: Add your control notification handler code here
	CStaticAssistant::SetEncryptFlag(false);          //���ü��ܱ�־
	//��õ�ǰ����·�����Ҵ��ݸ�FaceProcess��
	CFaceEncryptDoc* pDoc = GetDocument();     
	     ASSERT_VALID(pDoc);
	CString  currentpath=pDoc->getSelectedPath();
	CStaticAssistant::SetCurrentPath(currentpath);    //���ü���·��
	//�жϵ�ǰ·���Ƿ��Ѿ�����
	BOOL isEncrypt=pDoc->IsEncrypt(currentpath);
	if(isEncrypt==FALSE){
		AfxMessageBox("��ѡ���·����û�м��ܣ����ý��ܣ�лл����");
		return ;
	}
	//���ܶԻ���
	CFaceProcess  faceDlg;
             faceDlg.DoModal();
	delete faceDlg;
}

void CChooseOperation::OnEncryptInfo() 
{
	// TODO: Add your control notification handler code here
	CFaceEncryptDoc* pDoc = GetDocument();     
	        ASSERT_VALID(pDoc);
    //�����չʾ�Ѿ����ܵ�·��
	CStringArray *EncryptPath=pDoc->GetEncryptInfo();
	int    encryCount=EncryptPath->GetSize();
	char   temp[10];
	CString temp1=CString(itoa(encryCount,temp,10));
	for(int i=0;i<encryCount;i++)
		AfxMessageBox("�Ѿ������ļ��� "+CString(itoa(i,temp,10))+" / "+temp1+"��\n"+EncryptPath->GetAt(i));
}

void CChooseOperation::OnAppExit() 
{
  // TODO: Add your control notification handler code here
		CFaceEncryptDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
  // 		CString  currentpath=pDoc->getSelectedPath();
  // 		AfxMessageBox(currentpath);
	   // SendMessage(WM_CLOSE,0,0);
		//�˳�����
	//	CFormView::OnClose();
}
