// FaceProcess.cpp : implementation file
//����ͷ�ļ�
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
//�����ʱ��
#define timer  1
#define faceTimer  2
//����ʶ��ʱ��Ӵ�е���һЩ����
static  int totalTest=1;    //�Ѿ�����ͼƬ����
static  int correct=0;      //һ������ʶ��ƥ��ͼƬ��
//��OntimerҪ����ѵ����ͼƬ�õ���һЩ����
static  int count=1;         //����ͼƬ�±��
CString testFileName[5]={"temp/1.pgm","temp/2.pgm","temp/3.pgm","temp/4.pgm","temp/5.pgm"};
/////////////////////////////////////////////////////////////////////////////
// CFaceProcess dialog
CFaceProcess::CFaceProcess(CWnd* pParent /*=NULL*/)
:CDialog(CFaceProcess::IDD, pParent),needTrainNumber(3)//��ʼ������
{
	//{{AFX_DATA_INIT(CFaceProcess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��ʼ��  ///ֻ��Ҫ����ѵ��ͼƬ
	m_snap=0;
	faceImage=0;
    faceGray=0;
// 	hDC=0;
// 	pDC=0;
// 	pwnd=0;
// 	m_GrabFrame=0;
// 	m_Video=0;
}
//��������
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
	//���û��ຯ��
	CDialog::OnInitDialog();
	//��ȡ��ǰҪ������·���Ͳ�������
      b_flagProcess= CStaticAssistant::GetEncryptFlag();
      path=CStaticAssistant::GetCurrentPath();
	/************************************************************************/
		 /* ���ݹ��ܱ�־b_flagProgress�����Ƿ���ѵ������ʶ��ģ��
		    ����ǽ��ܣ���ѵ��*/
	/************************************************************************/
	int i=1;
	CString   picName="";
	/*********���ϴ�����·��*********************/
    CString   headPath="ImageLab/";
    char* pszStr=0;
	/*********����ǽ���*********************/
    if(b_flagProcess==FALSE){             
	  while(i<needTrainNumber+1){
		 picName=GetImageName(path,i);
    /*********���Ϻ�׺����*********************/
		 picName=headPath+picName+".pgm";
		 picName="11 "+picName;      //��ѵ��Ĭ��Ϊ11������
	     pszStr= picName.GetBuffer(picName.GetLength());
		 if(faceRecognitor.addFaceImgArray(pszStr,true,i)==true)
 			 i++;
	  }//while
   }//if
   /*********����ǽ���,ѵ��ģ��*********************/
   if(b_flagProcess==FALSE){  
	    GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(TRUE);//ʹ�ؼ���Ч
		faceRecognitor.learn();
   }
   GetDlgItem(IDC_OK)->EnableWindow(FALSE);//ʹ�ؼ���Ч
   /*********set icon*********************/
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
   /*********��ʾ������ԴͼƬ*********************/
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
		AfxMessageBox("���ر���ͼƬʧ��");
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(&m_Bitmap1);
	
	//CClientDC dc(this); 
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY);
	m_Bitmap1.DeleteObject();
	MemDC.DeleteDC();
	Invalidate();
	/************************************************************************/
	/* ���ݹ������ÿؼ�״̬                                                          */
	/************************************************************************/
	GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	GetDlgItem(IDC_RECOGNISE)->EnableWindow(FALSE);//ʹ�ؼ���Ч 
	GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	GetDlgItem(IDC_STATIC_OTHER)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	//GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	GetDlgItem(IDC_SAVE_PIC)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	/***********************������ʾ��ʼֵ*********************/
	SetDlgItemText(IDC_STATIC_FRAME_COUNT,"��");
	SetDlgItemText(IDC_STATIC_Width,"��");
	SetDlgItemText(IDC_STATIC_HEIGHT,"��");
	SetDlgItemText(IDC_STATIC_FPS,"��");
	SetDlgItemText(IDC_STATIC_CORRECT,"��");
	SetDlgItemText(IDC_STATIC_OTHER,"��");
	/***********************��ʼ����ر���**********************/
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
	    AfxMessageBox("������ͷʧ�ܣ���������豸!ԭ�����£�\n1������ͷ�Ѿ��򿪣�\n2���豸δ���ӣ�\n3������ԭ��"); 
	else
		SetTimer(timer,1,NULL) ;  //��Сֵֻ��Ϊ1
	return ;
}

void CFaceProcess::OnCloseCapture() 
{
	// TODO: Add your control notification handler code here
	if(m_Video)
	         cvReleaseCapture(&m_Video);
	else
		     AfxMessageBox("����ͷ�ѹرգ�");
	//�ͷ���Դ
	if(m_snap)
		cvReleaseImage(&m_snap);
	if(faceImage)
		cvReleaseImage(&faceImage);
	if(faceGray)
		cvReleaseImage(&faceGray);
	//��ԭ����
	correct=0;  totalTest=1;   count=1;   b_Process=0;  	m_fameCount=0;
	//kill timer//�ر�ʱ��
	  KillTimer(timer);
	  KillTimer(faceTimer);
	//���ñ���ͼƬ
	CDC MemDC; 
	CBitmap m_Bitmap1;
	m_Bitmap1.LoadBitmap(IDB_BKGROUND); 
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(&m_Bitmap1);
	pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,48,48,SRCCOPY); 
	m_Bitmap1.DeleteObject();
	MemDC.DeleteDC();	
	//������ʾ��ʼֵ
	SetDlgItemText(IDC_STATIC_FRAME_COUNT,"��");
	SetDlgItemText(IDC_STATIC_Width,"��");
	SetDlgItemText(IDC_STATIC_HEIGHT,"��");
	SetDlgItemText(IDC_STATIC_FPS,"��");
	SetDlgItemText(IDC_STATIC_CORRECT,"��");
	SetDlgItemText(IDC_STATIC_OTHER,"��");
}
void CFaceProcess::OnRecognise() 
{
	// TODO: Add your control notification handler code here
	//���ö�ʱ��
	if(!m_Video){
		AfxMessageBox("���ȴ�����ͷ");  return ;
	} 
 	else
		SetTimer(faceTimer,3000,NULL);
}
BOOL  CFaceProcess::OnSavePic() 
{
	// TODO: Add your control notification handler code here
	KillTimer(timer);
	if (!m_Video){
// 	{AfxMessageBox("�ȴ�����ͷ"); return false; 	}
// 	m_GrabFrame=cvQueryFrame(m_Video);
// 	if (!m_GrabFrame)
// 	{AfxMessageBox("��ȡ����֡ʧ�ܣ������ԣ�"); return false; 	}
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
	/*********���Ϻ�׺����,���ϴ�����·��*********************/
	CString   headPath="ImageLab/";
			  m_name1=headPath+m_name1+".pgm";
	const char* pszStr1 = m_name1.GetBuffer(m_name1.GetLength());
	//AfxMessageBox(m_name);
	IplImage * m_snap1=cvCreateImage(cvGetSize(m_SaveFrame),m_SaveFrame->depth,m_SaveFrame->nChannels);
	        cvCopy(m_SaveFrame,m_snap1,NULL);
	        //m_snap1->origin=1;//����0���浹��ͼ��
	IplImage *faceImage1=0;
	IplImage *faceGray1=0;
	//�������
	try{
    	if(faceDetector.detect_and_draw(m_snap1)){
	                  faceImage1=faceDetector.getFaceImage();
	                 // faceImage1->origin=1;
	                  //����ͼƬ
	                  if(faceSimplifier.Simplify(faceImage1)){
	                           faceGray1=faceSimplifier.getFaceImage();
                               //faceGray1->origin=1;//����0���浹��ͼ��
         	                   cvSaveImage(pszStr1,faceGray1);	//��ͼ��д���ļ�
							   countsnap++;
					  }
		}
		SetTimer(timer,1,NULL) ;
	}catch(...)
	{
		SetTimer(timer,1,NULL) ;
        AfxMessageBox("����ͼƬʧ��--OnSavePic����");
		return false;
	}
	if(countsnap>3)
			GetDlgItem(IDC_OK)->EnableWindow(TRUE);//ʹ�ؼ���Ч
	if(m_snap1)
		cvReleaseImage(&m_snap1);
    if(faceImage1)
		cvReleaseImage(&faceImage1);
	if(faceGray1)
		cvReleaseImage(&faceGray1);
	return true;
}
//��Ӧʱ���¼�
void CFaceProcess::OnTimer(UINT nIDEvent){
	//AfxMessageBox("In OnTimer()");
	 CString     temp="";
 	 const char  *pszStr="";
	 int         match=0;
switch(nIDEvent){
	//��ʱ��1����Ӧ������
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
        /**************�Ի�ȡ��֡����������⴦������ʾ*****************/
		faceDetector.detect_and_draw(m_SaveFrame);
        //m_GrabFrame=faceDetector.getSrcImage();
	    m_CvvImage.CopyOf(m_SaveFrame,1);
	    m_CvvImage.DrawToHDC(hDC,&rect);
		//cvReleaseImage(&m_SaveFrame);
	 }
//	return;
	/************************************************************************/
	/* ���b_Process״̬                                                             */
	/************************************************************************/
	if(m_Video && b_flagProcess==true)
		b_Process=1;
	else if(m_Video && b_flagProcess==false)
		b_Process=2;
	else
		b_Process=0;
	/************************************************************************/
	/* ����b_Process״̬��̬���ÿؼ���Ч��                                                            */
	/************************************************************************/
     if(b_Process==1)//��ʱ���Թ�����ͷ������ͼƬ
	 {
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true);//ʹ�ؼ���Ч
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(true);    //ʹ�ؼ���Ч
	 }
	 else if(b_Process==2)//��ʱ��������ʶ��ƥ������ʾ�����ܱ���ͼƬ
	 {
		//����״̬
		GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true); //ʹ�ؼ���Ч
		GetDlgItem(IDC_RECOGNISE)->EnableWindow(true);    //ʹ�ؼ���Ч
        GetDlgItem(IDC_SAVE_PIC)->EnableWindow(false);    //ʹ�ؼ�wuЧ   
	   /******��ʱ�ɱ��湩����ʶ���õ�ͼƬ**************************
		//  ÿ�α�������
		//  ��ʱ��������ʱѵ��ͼƬ��������ƥ����
		//  ����ͼƬ���ϸ�����ǰ��ͼƬ
	   ****************************/		
		if((count % 5)==0)
		           count=1;
		 pszStr = testFileName[count].GetBuffer(testFileName[count].GetLength());
		 m_snap=cvCreateImage(cvGetSize(m_SaveFrame),m_SaveFrame->depth,m_SaveFrame->nChannels);
		 cvCopy(m_SaveFrame,m_snap,NULL);
		 //m_snap->origin=1;//����0���浹��ͼ��
		 //����������������ͼƬ
		//AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10)));
	    try{
		  if(faceDetector.detect_and_draw(m_snap)){
		     faceImage=faceDetector.getFaceImage();
			 if(faceImage){
			    //faceImage->origin=1;
		     //����ͼƬ
			    if(faceSimplifier.Simplify(faceImage)){
				   faceGray=faceSimplifier.getFaceImage();
				   //faceGray->origin=1;//����0���浹��ͼ��
				   cvSaveImage(pszStr,faceGray);	//��ͼ��д���ļ�
				 //AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10))+"t1");
				   count++;
				}
			}// if(faceImage)
		  }
		}catch(...)  //��Ҫ,�����ⲻ������ʱ���쳣��ֹ
		{ /* AfxMessageBox("����ͼƬʧ�ܣ���");*/	return ; }
	 }else //b_Process==0)  //��ʱֻ���Խ��д�����ͷ�ٻ����˳�
	 {
		 GetDlgItem(IDC_STATIC_OTHER)->EnableWindow(FALSE);//ʹ�ؼ���Ч
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(FALSE);//ʹ�ؼ���Ч
		 GetDlgItem(IDC_RECOGNISE)->EnableWindow(FALSE);//ʹ�ؼ���Ч
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(FALSE);//ʹ�ؼ���Ч
	 }
	/************************************************************************/
	/* ��ʾ����   ��Ҫ��ʱ���µ��ڴ���ʾ����������������ʱ��facetimer�и���*/
	/************************************************************************/
	   m_fameCount++;
	//	m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_COUNT);
	  itoa(m_fameCount,chEdit,10);
	  SetDlgItemText(IDC_STATIC_FRAME_COUNT,chEdit);
	break;
		//��ʱ��2����Ӧ������
    case faceTimer:
	   //****************//����ʶ��
	 correct=correct+faceRecognitor.recognize();
	 totalTest+=5;
	 matchPercent=float(correct)/totalTest;
	 match=int(matchPercent*100);
	/************************************************************************/
	/* ��ʾ����   ��Ҫ��ʱ���µ��ڴ���ʾ����������������ʱ��facetimer�и���*/
	/************************************************************************/	
    //ƥ���ʵĸ���
	 itoa(match,chEdit,10);
	 temp=" "+CString(chEdit)+" %";
	 SetDlgItemText(IDC_STATIC_CORRECT,temp);
	 GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(TRUE);//ʹ�ؼ���Ч
	//����ƥ���ж��Ƿ���Խ�����һ��
	 if(matchPercent>0.75 && totalTest>20)
        GetDlgItem(IDC_OK)->EnableWindow(TRUE);//ʹ�ؼ���Ч
	//��������
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
	//���û���ʱ��
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
	//�ر�����ͷ
	OnCloseCapture();

	CDialog::OnCancel();
}

void CFaceProcess::OnOk() 
{
	// TODO: Add your control notification handler code here
	//Ϊtrain.txtǰ���и���ֵ
 	CString  defaultName="                                                                                                                                                                                                               ";
 	for(int i=1;i<needTrainNumber+1;i++)
  	      faceRecognitor.addFaceImgArray(defaultName.GetBuffer(defaultName.GetLength()),true,i);
	//�ر�����ͷ
	OnCloseCapture();
	//OnCloseCapture();
	//CPassWord  pswDlg=0;
	//���ò�������
 	if(b_flagProcess==true)
 		CStaticAssistant::SetEncryptFlag(TRUE);
	else
        CStaticAssistant::SetEncryptFlag(FALSE);
   	CStaticAssistant::SetCurrentPath(path);
//������һ���ӽ����ļ��еĲ���
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
	//OnCloseCapture(); ���ã������OnCancel��������
	 CDialog::OnClose();
}
/****��ñ���ͼƬ����,��������׺��20110422www********/
//����Ϊ����ǰ·���� ע�⣺���������99��ͼƬ
//��·�����еġ�������Ϊ��@��������/����Ϊ��#��������ĩβ����
//�����ʽ��_XX�����±꣬XXΪ��λʮ������
//��D:/Test ------->D@#Test_00
CString  CFaceProcess::GetImageName(CString filePath, int frameCount){
	 CString filePath1=filePath;
	 CString  picName="";
	 CString  middle1="";
	 CString  middle2="";
	 if(frameCount<0 || frameCount>99) {	 
		 AfxMessageBox("��ȡ�ļ���ʱ��������,֡��Ӧ��0-99֮��");
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
