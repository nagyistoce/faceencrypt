// FaceEncryptView.cpp : implementation of the CFaceEncryptView class
//

#include "stdafx.h"
/***********************����ͷ�ļ�***************/
#include "../FaceEncrypt.h"
#include "MainFrm.h"
#include "../FaceEncryptDoc.h"
#include "FaceEncryptView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IMAGE_CHANNELS  3
/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptView
IMPLEMENT_DYNCREATE(CFaceEncryptView, CFormView)

BEGIN_MESSAGE_MAP(CFaceEncryptView, CFormView)
	//{{AFX_MSG_MAP(CFaceEncryptView)
    ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
    ON_BN_CLICKED(IDC_TUICHU, OnTuichu)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptView construction/destruction

CFaceEncryptView::CFaceEncryptView()
	: CFormView(CFaceEncryptView::IDD)
{
	//{{AFX_DATA_INIT(CFaceEncryptView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CFaceEncryptView::~CFaceEncryptView()
{
	cvReleaseImage(&welcomeImage);
}

void CFaceEncryptView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaceEncryptView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CFaceEncryptView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFaceEncryptView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
    /********************���ֳ�ʼ������***************/
	CWnd *p=GetDlgItem(IDC_WELCOME_PIC);
	if(p==NULL)
		AfxMessageBox("GetDlgItem(IDC_WELCOME_PIC)  failed!!!");
	CRect  rc;
	p->GetWindowRect(&rc);
	CvSize ImgSize;
	//��ȡ��ʾͼƬ�Ŀؼ���С
    ImgSize.height =rc.Height();
    ImgSize.width = rc.Width();
	//CString S1;
	//S1.Format("henght:%d::width:%d",ImgSize.height,ImgSize.width);
    welcomeImage= cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);
	//AfxMessageBox(S1);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptView diagnostics

#ifdef _DEBUG
void CFaceEncryptView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFaceEncryptView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFaceEncryptDoc* CFaceEncryptView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceEncryptDoc)));
	return (CFaceEncryptDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptView message handlers
void CFaceEncryptView::ShowImage( IplImage* img, UINT ID )    // ID ��Picture Control�ؼ���ID��
{
	CWnd *p=GetDlgItem( ID );
	if(p==NULL)
		AfxMessageBox("GetDlgItem( ID )  failed!!!");
    CDC* pDC = GetDlgItem( ID ) ->GetDC();        // �����ʾ�ؼ��� DC
    HDC hDC = pDC ->GetSafeHdc();                // ��ȡ HDC(�豸���) �����л�ͼ����
    CRect rect;
    GetDlgItem(ID) ->GetClientRect( &rect );
    int rw = rect.right - rect.left;            // ���ͼƬ�ؼ��Ŀ�͸�
    int rh = rect.bottom - rect.top;
    int iw = img->width;                        // ��ȡͼƬ�Ŀ�͸�
    int ih = img->height;
    int tx = (int)(rw - iw)/2;                    // ʹͼƬ����ʾλ�������ڿؼ�������
    int ty = (int)(rh - ih)/2;
    SetRect( rect, tx, ty, tx+iw, ty+ih );

    CvvImage cimg;
    cimg.CopyOf( img );                            // ����ͼƬ
    cimg.DrawToHDC( hDC, &rect );                // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
    ReleaseDC( pDC );
}

void CFaceEncryptView::OnEnter() 
{
	   CFaceEncryptDoc *pDoc=GetDocument();
	    ASSERT(pDoc!=NULL);
		//AfxMessageBox(pDoc->getSelectedPath());
	// TODO: Add your control notification handler code here
	CMainFrame *pWnd=(CMainFrame *)AfxGetMainWnd();
	     pWnd->SwitchView(1);
}
void   CFaceEncryptView::OnDraw(CDC *pDc){
	/*��ȡҪ��ʵ�ĳ�ʼͼƬ*/
	IplImage *pic;
	pic=cvLoadImage("./res/WelcomeBkPic.jpg",CV_LOAD_IMAGE_COLOR);
    if(pic==NULL)
	{     AfxMessageBox("��ȡ��־ͼƬʧ��,лл!");  return ;}
	cvResize(pic,welcomeImage);
	//*****����һ********
	AfxMessageBox("��ӭʹ��");
    ShowImage(welcomeImage,IDC_WELCOME_PIC);  //����ͼƬ�ؼ�ID��ʾͼƬ
	if(pic)
		cvReleaseImage(&pic);
	//���û����Ա
	CFormView::OnDraw(pDc);
//     /******������*********/
//	CDC* pDC = GetDlgItem( IDC_WELCOME_PIC) ->GetDC();
//	HDC hDC = pDC ->GetSafeHdc(); 
 //   CvvImage  m_CvvImage;
  //  CRect rect;
  //  GetDlgItem(IDC_WELCOME_PIC)->GetClientRect( &rect );
	//	m_CvvImage.CopyOf(welcomeImage,1);	
//	AfxMessageBox("��ӭʹ��");
	//	m_CvvImage.DrawToHDC(hDC,&rect);   
     //ReleaseDC( pDC );
		//������
	//	CString path="./res/bitmap1.bmp";
		// HWND hwnd=GetDlgItem(IDC_WELCOME_PIC)->m_hWnd;
        //HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //path��bmp·��
        //::SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,&hBitmap);
      //  ::SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBitmap);
	//	CFormView::OnDraw(pDc);  //important��Ӧ����������
	//	HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetApp()->m_hInstance,path,IMAGE_BITMAP, 0, 0,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);      
	//	CStatic*pEdit=(CStatic*)GetDlgItem(IDC_STATIC);//IDC_PIC��picture control�ؼ���ID
      //  pEdit->SetBitmap(hBitmap);
}
void CFaceEncryptView::OnPaint(){
// 		CDC MemDC; 
// 		CBitmap m_Bitmap1;
// 		m_Bitmap1.LoadBitmap(IDB_WELCONE_BK); 
// 		MemDC.CreateCompatibleDC(NULL);
// 		MemDC.SelectObject(&m_Bitmap1);
//    
// 		//CClientDC dc(this); 
// 		pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY); 
// 		
// 		m_Bitmap1.DeleteObject();
// 		MemDC.DeleteDC();
	//���û����Ա
	CFormView::OnPaint();
}
void CFaceEncryptView::OnTuichu(){
 //	AfxMessageBox("�˳�");
	//���ԣ����ļ�����д���ļ���
// 	CStdioFile  f1;
// 	try{
// 		if(f1.Open("./res/train.txt",CFile::modeReadWrite)==FALSE)
// 		{  AfxMessageBox("open failed");  return ;}
// 	}catch(CFileException e)
// 	{
//        AfxMessageBox("open failed");
// 	   e.ReportError();
// 	}
// 	CString S;
// 	while(f1.ReadString(S))
// 		AfxMessageBox(S);
// 	CStdioFile  f2;
// 		if(f2.Open("./res/test.txt",CFile::modeReadWrite)==FALSE)
// 		{  AfxMessageBox("open failed");  return ;}
//     f2.SeekToEnd();
// 	int i=0;
// 	while(i<3)
// 	{
// 		f2.WriteString("1 ../Im/face_train/face_simple_image.pgm\n");
// 		i++;
// 	}
// 	char *File ="E:\\Test/4.mp3";//fileName.GetBuffer(fileName.GetLength());// "C:\\windows\\temp\\*.TMP\0";
// 	SHFILEOPSTRUCT op;
// 	ZeroMemory(&op, sizeof(op));
// 	op.hwnd =NULL;//(HWND)AfxGetMainWnd();
// 	op.wFunc = FO_DELETE;
// 	op.pFrom = File;
// 	op.pTo=NULL;
// 	op.fFlags=FOF_NOCONFIRMATION | FOF_NOERRORUI;//FOF_ALLOWUNDO--������վ;
//     //SHFileOperation( &op);
// 	if( 0 != SHFileOperation(&op))
// 	{
// 		AfxMessageBox("ɾ���ļ�����,����");
// 		//return false ;
// 	}
	/*************ɾ���ļ�*******/
// 	CString S="E:\\Test/���� (2) 1.txt";	
// //      CStaticAssistant::deleteFile(S,this->GetSafeHwnd());
// //          //return true;
// //           return;
// 	/*************���Դ��л�*******/
//  	CFaceEncryptDoc *pDoc=GetDocument();
//  	    ASSERT(pDoc!=NULL);
//  	pDoc->setSelectedPath("This a test __D@#_01.pgm%^&***(");
//////////////////////////////////////////////////////////////////////////
//  	if(TRUE==CStaticAssistant::StoreEncryptInfo("this is a test!","res/temp.znl"))
// 		AfxMessageBox("��ӳɹ�");
// 	else
// 		AfxMessageBox("ʧ��");E:\Test\�ĵ�
	if(TRUE==CStaticAssistant::DeleteUncryptInfo("E:\\Test\\�ĵ�","res/temp.znl"))
		AfxMessageBox("ɾ���ɹ�");
	else
		AfxMessageBox("ʧ��");
	CFormView::OnClose();
	SendMessage(WM_CLOSE,NULL,NULL);
}