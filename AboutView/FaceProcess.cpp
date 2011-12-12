// FaceProcess.cpp : implementation file
//包含头文件
#include "stdafx.h"
#include "../FaceEncrypt.h"
#include "FaceProcess.h"
#include "../AboutFaceProcess/faceSimplify.h"
#include "EncryptFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//定义计时器
#define timer  1
#define faceTimer  2
//人脸识别时候哟感到的一些变量
static  int totalTest=1;    //已经测试图片数量
static  int correct=0;      //一次人脸识别匹配图片数
//在Ontimer要保存训练用图片用到的一些变量
static  int count=1;         //保存图片下标号
CString testFileName[5]={"temp/1.pgm","temp/2.pgm","temp/3.pgm","temp/4.pgm","temp/5.pgm"};
/////////////////////////////////////////////////////////////////////////////
// CFaceProcess dialog
CFaceProcess::CFaceProcess(CWnd* pParent /*=NULL*/)
:CDialog(CFaceProcess::IDD, pParent),needTrainNumber(3)//初始化常量
{
	//{{AFX_DATA_INIT(CFaceProcess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化  ///只需要三张训练图片
	m_snap=0;
	faceImage=0;
    faceGray=0;
// 	hDC=0;
// 	pDC=0;
// 	pwnd=0;
// 	m_GrabFrame=0;
// 	m_Video=0;
}
//析构函数
CFaceProcess::~CFaceProcess(){
     faceDetector.~faceDetect();
	 faceSimplifier.~faceSimplify();
	 faceRecognitor.~faceRecognition();
	 if(!m_Video)
		 cvReleaseCapture(&m_Video);
	 if(!m_snap)
		 cvReleaseImage(&m_snap);
	 if(!faceImage)
		 cvReleaseImage(&faceImage);
	 if(!faceGray)
		 cvReleaseImage(&faceGray);
}
void CFaceProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaceProcess)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFaceProcess, CDialog)
	//{{AFX_MSG_MAP(CFaceProcess)
 	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_OPEN_CAPTURE, OnOpenCapture)
	ON_BN_CLICKED(IDC_RECOGNISE, OnRecognise)
	ON_BN_CLICKED(IDC_SAVE_PIC, OnSavePic)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(ID_CLOSE_CAPTURE, OnCloseCapture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceProcess message handlers
BOOL CFaceProcess::OnInitDialog(){
	// TODO: Add extra initialization here
	//调用基类函数
	CDialog::OnInitDialog();
	//获取当前要操作的路径和操作类型
      b_flagProcess= CStaticAssistant::GetEncryptFlag();
      path=CStaticAssistant::GetCurrentPath();
	/************************************************************************/
		 /* 根据功能标志b_flagProgress决定是否先训练人脸识别模型
		    如果是解密，就训练*/
	/************************************************************************/
	int i=1;
	CString   picName="";
	/*********加上存放相对路径*********************/
    CString   headPath="ImageLab/";
    char* pszStr=0;
	/*********如果是解密*********************/
    if(b_flagProcess==FALSE){             
	  while(i<needTrainNumber+1){
		 picName=GetImageName(path,i);
    /*********加上后缀名称*********************/
		 picName=headPath+picName+".pgm";
		 picName="11 "+picName;      //新训练默认为11号人脸
	     pszStr= picName.GetBuffer(picName.GetLength());
		 if(faceRecognitor.addFaceImgArray(pszStr,true,i)==true)
 			 i++;
	  }//while
   }//if
   /*********如果是解密,训练模型*********************/
   if(b_flagProcess==FALSE){  
	    GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(TRUE);//使控件有效
		faceRecognitor.learn();
   }
   GetDlgItem(IDC_OK)->EnableWindow(FALSE);//使控件无效
   /*********set icon*********************/
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
   /*********显示背景资源图片*********************/
	pwnd = GetDlgItem(IDC_SHOW_PIC);
	pwnd->MoveWindow(20,25,385,300);
    pDC =pwnd->GetDC();
	//pDC =GetDC();
    hDC= pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);
	CDC MemDC; 
	CBitmap m_Bitmap1;
	BOOL b=m_Bitmap1.LoadBitmap(IDB_BKGROUND);
	if(b==false)
		AfxMessageBox("加载背景图片失败");
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(&m_Bitmap1);
	
	//CClientDC dc(this); 
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY);
	m_Bitmap1.DeleteObject();
	MemDC.DeleteDC();
	Invalidate();
	/************************************************************************/
	/* 根据功能设置控件状态                                                          */
	/************************************************************************/
	GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(FALSE);//使控件无效
	GetDlgItem(IDC_RECOGNISE)->EnableWindow(FALSE);//使控件无效 
	GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(FALSE);//使控件无效
	GetDlgItem(IDC_STATIC_OTHER)->EnableWindow(FALSE);//使控件无效
	//GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(FALSE);//使控件无效
	GetDlgItem(IDC_SAVE_PIC)->EnableWindow(FALSE);//使控件无效
	/***********************设置显示初始值*********************/
	SetDlgItemText(IDC_STATIC_FRAME_COUNT,"无");
	SetDlgItemText(IDC_STATIC_Width,"无");
	SetDlgItemText(IDC_STATIC_HEIGHT,"无");
	SetDlgItemText(IDC_STATIC_FPS,"无");
	SetDlgItemText(IDC_STATIC_CORRECT,"无");
	SetDlgItemText(IDC_STATIC_OTHER,"无");
	/***********************初始化相关变量**********************/
	m_Video=0;
	b_Process=0;
	m_fameCount=0;
    m_vieoProtery=0;
	m_GrabFrame=0;
	m_SaveFrame=0;
	return  TRUE;
}

void CFaceProcess::OnOpenCapture() 
{
	// TODO: Add your control notification handler code here
	if(!m_Video)
	{
	   m_Video=cvCreateCameraCapture(-1);
	}
	if(!m_Video)
	    AfxMessageBox("打开摄像头失败，请检查相关设备!原因如下：\n1、摄像头已经打开；\n2、设备未连接；\n3、其他原因"); 
	else
		SetTimer(timer,1,NULL) ;  //最小值只能为1
	return ;
}

void CFaceProcess::OnCloseCapture() 
{
	// TODO: Add your control notification handler code here
	if(m_Video)
	         cvReleaseCapture(&m_Video);
	else
		     AfxMessageBox("摄像头已关闭！");
	//释放资源
	if(m_snap)
		cvReleaseImage(&m_snap);
	if(faceImage)
		cvReleaseImage(&faceImage);
	if(faceGray)
		cvReleaseImage(&faceGray);
	//还原变量
	correct=0;  totalTest=1;   count=1;   b_Process=0;  	m_fameCount=0;
	//kill timer//关闭时钟
	  KillTimer(timer);
	  KillTimer(faceTimer);
	//重置背景图片
	CDC MemDC; 
	CBitmap m_Bitmap1;
	m_Bitmap1.LoadBitmap(IDB_BKGROUND); 
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(&m_Bitmap1);
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY); 
	m_Bitmap1.DeleteObject();
	MemDC.DeleteDC();	
	//设置显示初始值
	SetDlgItemText(IDC_STATIC_FRAME_COUNT,"无");
	SetDlgItemText(IDC_STATIC_Width,"无");
	SetDlgItemText(IDC_STATIC_HEIGHT,"无");
	SetDlgItemText(IDC_STATIC_FPS,"无");
	SetDlgItemText(IDC_STATIC_CORRECT,"无");
	SetDlgItemText(IDC_STATIC_OTHER,"无");
}
void CFaceProcess::OnRecognise() 
{
	// TODO: Add your control notification handler code here
	//设置定时器
	if(!m_Video){
		AfxMessageBox("请先打开摄像头");  return ;
	} 
 	else
		SetTimer(faceTimer,3000,NULL);
}
BOOL  CFaceProcess::OnSavePic() 
{
	// TODO: Add your control notification handler code here
	KillTimer(timer);
	if (!m_Video){
// 	{AfxMessageBox("先打开摄像头"); return false; 	}
// 	m_GrabFrame=cvQueryFrame(m_Video);
// 	if (!m_GrabFrame)
// 	{AfxMessageBox("截取视屏帧失败，请重试！"); return false; 	}
	//static	char countsnap='1';
	if( !cvGrabFrame( m_Video))
		return FALSE;
	m_GrabFrame = cvRetrieveFrame(m_Video );
	if( !m_GrabFrame)
		return FALSE;
	if( !m_SaveFrame)
		m_SaveFrame = cvCreateImage( cvSize(m_GrabFrame->width,m_GrabFrame->height),
		IPL_DEPTH_8U, m_GrabFrame->nChannels );
	if( m_GrabFrame->origin == IPL_ORIGIN_TL )
		cvCopy( m_GrabFrame, m_SaveFrame, 0 );
	else
			cvFlip( m_GrabFrame, m_SaveFrame, 0 );
	}//if (!m_Video){
	static  int countsnap=1;
	CString   m_name1=GetImageName(path,countsnap);
	/*********加上后缀名称,加上存放相对路径*********************/
	CString   headPath="ImageLab/";
			  m_name1=headPath+m_name1+".pgm";
	const char* pszStr1 = m_name1.GetBuffer(m_name1.GetLength());
	//AfxMessageBox(m_name);
	IplImage * m_snap1=cvCreateImage(cvGetSize(m_SaveFrame),m_SaveFrame->depth,m_SaveFrame->nChannels);
	        cvCopy(m_SaveFrame,m_snap1,NULL);
	        //m_snap1->origin=1;//等于0保存倒立图向
	IplImage *faceImage1=0;
	IplImage *faceGray1=0;
	//检测人脸
	try{
    	if(faceDetector.detect_and_draw(m_snap1)){
	                  faceImage1=faceDetector.getFaceImage();
	                 // faceImage1->origin=1;
	                  //化简图片
	                  if(faceSimplifier.Simplify(faceImage1)){
	                           faceGray1=faceSimplifier.getFaceImage();
                               //faceGray1->origin=1;//等于0保存倒立图向
         	                   cvSaveImage(pszStr1,faceGray1);	//把图像写入文件
							   countsnap++;
					  }
		}
		SetTimer(timer,1,NULL) ;
	}catch(...)
	{
		SetTimer(timer,1,NULL) ;
        AfxMessageBox("保存图片失败--OnSavePic！！");
		return false;
	}
	if(countsnap>3)
			GetDlgItem(IDC_OK)->EnableWindow(TRUE);//使控件有效
	if(m_snap1)
		cvReleaseImage(&m_snap1);
    if(faceImage1)
		cvReleaseImage(&faceImage1);
	if(faceGray1)
		cvReleaseImage(&faceGray1);
	return true;
}
//响应时间事件
void CFaceProcess::OnTimer(UINT nIDEvent){
	//AfxMessageBox("In OnTimer()");
	 CString     temp="";
 	 const char  *pszStr="";
	 int         match=0;
switch(nIDEvent){
	//定时器1的相应处理部分
   case timer:
	if(m_Video){
		if( !cvGrabFrame( m_Video))
			return ;
		m_GrabFrame = cvRetrieveFrame(m_Video );
		if( !m_GrabFrame)
			return ;
		if( !m_SaveFrame)
			m_SaveFrame = cvCreateImage( cvSize(m_GrabFrame->width,m_GrabFrame->height),
			IPL_DEPTH_8U, m_GrabFrame->nChannels );
		if( m_GrabFrame->origin == IPL_ORIGIN_TL )
			cvCopy( m_GrabFrame, m_SaveFrame, 0 );
		else
			cvFlip( m_GrabFrame, m_SaveFrame, 0 );
//		m_GrabFrame=cvQueryFrame(m_Video);
// 		if(m_GrabFrame->origin==0)
//		m_GrabFrame->origin=1;
        /**************对获取的帧进行人脸检测处理并且显示*****************/
		faceDetector.detect_and_draw(m_SaveFrame);
        //m_GrabFrame=faceDetector.getSrcImage();
	    m_CvvImage.CopyOf(m_SaveFrame,1);
	    m_CvvImage.DrawToHDC(hDC,&rect);
		//cvReleaseImage(&m_SaveFrame);
	 }
//	return;
	/************************************************************************/
	/* 获得b_Process状态                                                             */
	/************************************************************************/
	if(m_Video && b_flagProcess==true)
		b_Process=1;
	else if(m_Video && b_flagProcess==false)
		b_Process=2;
	else
		b_Process=0;
	/************************************************************************/
	/* 根据b_Process状态动态设置控件有效性                                                            */
	/************************************************************************/
     if(b_Process==1)//此时可以关摄像头、保存图片
	 {
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true);//使控件有效
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(true);    //使控件有效
	 }
	 else if(b_Process==2)//此时可以人脸识别、匹配率显示，不能保存图片
	 {
		//更新状态
		GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true); //使控件有效
		GetDlgItem(IDC_RECOGNISE)->EnableWindow(true);    //使控件有效
        GetDlgItem(IDC_SAVE_PIC)->EnableWindow(false);    //使控件wu效   
	   /******此时可保存供人脸识别用的图片**************************
		//  每次保存五张
		//  定时器而负责定时训练图片，并更新匹配率
		//  保存图片不断覆盖以前的图片
	   ****************************/		
		if((count % 5)==0)
		           count=1;
		 pszStr = testFileName[count].GetBuffer(testFileName[count].GetLength());
		 m_snap=cvCreateImage(cvGetSize(m_SaveFrame),m_SaveFrame->depth,m_SaveFrame->nChannels);
		 cvCopy(m_SaveFrame,m_snap,NULL);
		 //m_snap->origin=1;//等于0保存倒立图向
		 //检测人脸并保存测试图片
		//AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10)));
	    try{
		  if(faceDetector.detect_and_draw(m_snap)){
		     faceImage=faceDetector.getFaceImage();
			 if(faceImage){
			    //faceImage->origin=1;
		     //化简图片
			    if(faceSimplifier.Simplify(faceImage)){
				   faceGray=faceSimplifier.getFaceImage();
				   //faceGray->origin=1;//等于0保存倒立图向
				   cvSaveImage(pszStr,faceGray);	//把图像写入文件
				 //AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10))+"t1");
				   count++;
				}
			}// if(faceImage)
		  }
		}catch(...)  //重要,避免检测不到人脸时的异常终止
		{ /* AfxMessageBox("保存图片失败！！");*/	return ; }
	 }else //b_Process==0)  //此时只可以进行打开摄像头操或者退出
	 {
		 GetDlgItem(IDC_STATIC_OTHER)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(IDC_RECOGNISE)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(FALSE);//使控件无效
	 }
	/************************************************************************/
	/* 显示属性   需要随时更新的在次显示，更新慢的在慢定时器facetimer中更新*/
	/************************************************************************/
	   m_fameCount++;
	//	m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_COUNT);
	  itoa(m_fameCount,chEdit,10);
	  SetDlgItemText(IDC_STATIC_FRAME_COUNT,chEdit);
	break;
		//定时器2的相应处理部分
    case faceTimer:
	   //****************//人脸识别
	 correct=correct+faceRecognitor.recognize();
	 totalTest+=5;
	 matchPercent=float(correct)/totalTest;
	 match=int(matchPercent*100);
	/************************************************************************/
	/* 显示属性   需要随时更新的在次显示，更新慢的在慢定时器facetimer中更新*/
	/************************************************************************/	
    //匹配率的更新
	 itoa(match,chEdit,10);
	 temp=" "+CString(chEdit)+" %";
	 SetDlgItemText(IDC_STATIC_CORRECT,temp);
	 GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(TRUE);//使控件有效
	//根据匹配判断是否可以进入下一步
	 if(matchPercent>0.75 && totalTest>20)
        GetDlgItem(IDC_OK)->EnableWindow(TRUE);//使控件有效
	//其他更新
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_POS_MSEC);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_OTHER,chEdit);
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_WIDTH);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_Width,chEdit);
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_HEIGHT);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_HEIGHT,chEdit);
     m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FPS);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_FPS,chEdit);
   break;
   default:
	       break;
	}
	//调用基类时间
	CDialog::OnTimer(nIDEvent);
}
void CFaceProcess::OnPaint(){
	if (IsIconic())
	{
        CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialog::OnPaint();
	}
	if (!b_Process){
		CDC MemDC; 
		CBitmap m_Bitmap1;
		m_Bitmap1.LoadBitmap(IDB_BKGROUND); 
		MemDC.CreateCompatibleDC(NULL);
		MemDC.SelectObject(&m_Bitmap1);
		//CClientDC dc(this); 
		pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY); 
		m_Bitmap1.DeleteObject();
		MemDC.DeleteDC();
	}
}

void CFaceProcess::OnCancel() 
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox("void CFaceProcess::OnCancel");
	CString  defaultName="                                                                                                                                                                                                               ";
	for(int i=1;i<needTrainNumber+1;i++)
	      faceRecognitor.addFaceImgArray(defaultName.GetBuffer(defaultName.GetLength()),true,i);
	//关闭摄像头
	OnCloseCapture();

	CDialog::OnCancel();
}

void CFaceProcess::OnOk() 
{
	// TODO: Add your control notification handler code here
	//为train.txt前三行赋初值
 	CString  defaultName="                                                                                                                                                                                                               ";
 	for(int i=1;i<needTrainNumber+1;i++)
  	      faceRecognitor.addFaceImgArray(defaultName.GetBuffer(defaultName.GetLength()),true,i);
	//关闭摄像头
	OnCloseCapture();
	//OnCloseCapture();
	//CPassWord  pswDlg=0;
	//设置操作参数
 	if(b_flagProcess==true)
 		CStaticAssistant::SetEncryptFlag(TRUE);
	else
        CStaticAssistant::SetEncryptFlag(FALSE);
   	CStaticAssistant::SetCurrentPath(path);
//进行下一步加解密文件夹的操作
    CEncryptFileDlg encryptDlg;
	encryptDlg.DoModal();	
// 	if(pswDlg.DoModal()==IDOK)
// 	{ 
// 	//	::SendMessage((HWND)AfxGetMainWnd(),ID_FILE_CLOSE,0, 0);
// 		delete pswDlg;
// 	}
//	AfxMessageBox("OnOK()");
	CDialog::OnOK();
}
void CFaceProcess::OnClose(){
	//OnCloseCapture(); 不用，会调用OnCancel（）函数
	 CDialog::OnClose();
}
/****获得保存图片名称,不包含后缀名20110422www********/
//参数为：当前路径名 注意：最多允许保存99张图片
//将路径名中的“：”改为“@”，将“/”改为“#”，并在末尾加上
//形如格式“_XX”的下标，XX为两位十进制数
//如D:/Test ------->D@#Test_00
CString  CFaceProcess::GetImageName(CString filePath, int frameCount){
	 CString filePath1=filePath;
	 CString  picName="";
	 CString  middle1="";
	 CString  middle2="";
	 if(frameCount<0 || frameCount>99) {	 
		 AfxMessageBox("获取文件名时参数有误,帧数应在0-99之间");
	     return picName;
	 }
     middle1='_';
	 if(frameCount<10)
	     middle2="0";
	if(frameCount>=10)
         middle2="";
	      filePath1.Replace('\\','#');
	      filePath1.Replace(':','@');
	 char c[2]={'0'};
		  itoa(frameCount,c,10);
          picName=filePath1+middle1+middle2+CString(c);
   return  picName;
}
