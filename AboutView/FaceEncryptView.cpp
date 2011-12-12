// FaceEncryptView.cpp : implementation of the CFaceEncryptView class
//

#include "stdafx.h"
/***********************包含头文件***************/
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
    /********************部分初始化工作***************/
	CWnd *p=GetDlgItem(IDC_WELCOME_PIC);
	if(p==NULL)
		AfxMessageBox("GetDlgItem(IDC_WELCOME_PIC)  failed!!!");
	CRect  rc;
	p->GetWindowRect(&rc);
	CvSize ImgSize;
	//获取显示图片的控件大小
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
void CFaceEncryptView::ShowImage( IplImage* img, UINT ID )    // ID 是Picture Control控件的ID号
{
	CWnd *p=GetDlgItem( ID );
	if(p==NULL)
		AfxMessageBox("GetDlgItem( ID )  failed!!!");
    CDC* pDC = GetDlgItem( ID ) ->GetDC();        // 获得显示控件的 DC
    HDC hDC = pDC ->GetSafeHdc();                // 获取 HDC(设备句柄) 来进行绘图操作
    CRect rect;
    GetDlgItem(ID) ->GetClientRect( &rect );
    int rw = rect.right - rect.left;            // 求出图片控件的宽和高
    int rh = rect.bottom - rect.top;
    int iw = img->width;                        // 读取图片的宽和高
    int ih = img->height;
    int tx = (int)(rw - iw)/2;                    // 使图片的显示位置正好在控件的正中
    int ty = (int)(rh - ih)/2;
    SetRect( rect, tx, ty, tx+iw, ty+ih );

    CvvImage cimg;
    cimg.CopyOf( img );                            // 复制图片
    cimg.DrawToHDC( hDC, &rect );                // 将图片绘制到显示控件的指定区域内
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
	/*获取要现实的初始图片*/
	IplImage *pic;
	pic=cvLoadImage("./res/WelcomeBkPic.jpg",CV_LOAD_IMAGE_COLOR);
    if(pic==NULL)
	{     AfxMessageBox("获取标志图片失败,谢谢!");  return ;}
	cvResize(pic,welcomeImage);
	//*****方法一********
	AfxMessageBox("欢迎使用");
    ShowImage(welcomeImage,IDC_WELCOME_PIC);  //根据图片控件ID显示图片
	if(pic)
		cvReleaseImage(&pic);
	//调用基类成员
	CFormView::OnDraw(pDc);
//     /******方法二*********/
//	CDC* pDC = GetDlgItem( IDC_WELCOME_PIC) ->GetDC();
//	HDC hDC = pDC ->GetSafeHdc(); 
 //   CvvImage  m_CvvImage;
  //  CRect rect;
  //  GetDlgItem(IDC_WELCOME_PIC)->GetClientRect( &rect );
	//	m_CvvImage.CopyOf(welcomeImage,1);	
//	AfxMessageBox("欢迎使用");
	//	m_CvvImage.DrawToHDC(hDC,&rect);   
     //ReleaseDC( pDC );
		//方法三
	//	CString path="./res/bitmap1.bmp";
		// HWND hwnd=GetDlgItem(IDC_WELCOME_PIC)->m_hWnd;
        //HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);  //path是bmp路径
        //::SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,&hBitmap);
      //  ::SendMessage(hwnd,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBitmap);
	//	CFormView::OnDraw(pDc);  //important且应放在最后调用
	//	HBITMAP hBitmap=(HBITMAP)LoadImage(AfxGetApp()->m_hInstance,path,IMAGE_BITMAP, 0, 0,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);      
	//	CStatic*pEdit=(CStatic*)GetDlgItem(IDC_STATIC);//IDC_PIC是picture control控件的ID
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
	//调用基类成员
	CFormView::OnPaint();
}
void CFaceEncryptView::OnTuichu(){
 //	AfxMessageBox("退出");
	//测试：想文件读、写入文件名
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
// 	op.fFlags=FOF_NOCONFIRMATION | FOF_NOERRORUI;//FOF_ALLOWUNDO--到回收站;
//     //SHFileOperation( &op);
// 	if( 0 != SHFileOperation(&op))
// 	{
// 		AfxMessageBox("删除文件出错,请检查");
// 		//return false ;
// 	}
	/*************删除文件*******/
// 	CString S="E:\\Test/复件 (2) 1.txt";	
// //      CStaticAssistant::deleteFile(S,this->GetSafeHwnd());
// //          //return true;
// //           return;
// 	/*************测试串行化*******/
//  	CFaceEncryptDoc *pDoc=GetDocument();
//  	    ASSERT(pDoc!=NULL);
//  	pDoc->setSelectedPath("This a test __D@#_01.pgm%^&***(");
//////////////////////////////////////////////////////////////////////////
//  	if(TRUE==CStaticAssistant::StoreEncryptInfo("this is a test!","res/temp.znl"))
// 		AfxMessageBox("添加成功");
// 	else
// 		AfxMessageBox("失败");E:\Test\文档
	if(TRUE==CStaticAssistant::DeleteUncryptInfo("E:\\Test\\文档","res/temp.znl"))
		AfxMessageBox("删除成功");
	else
		AfxMessageBox("失败");
	CFormView::OnClose();
	SendMessage(WM_CLOSE,NULL,NULL);
}