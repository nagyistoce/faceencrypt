// faceDetect.cpp
//
// Example code showing how to detect faces using
// OpenCV's CvHaarClassifierCascade
//
// See also, facedetect.c, in the samples directory.
//
// Usage: DetectFaces <imagefilename>
#include "StdAfx.h"              //imprtant::������ʾ�ļ�û�н���
#include "faceDetect.h"
#include "../MyException.h"
// *** Change this to your install location! ***
// *********************************************
#define OPENCV_ROOT  "E:/Program Files/OpenCV"   //�궨��
// *********************************************
faceDetect::~faceDetect(){
	// clean up and release resources
	if(!pCascade)
		cvReleaseHaarClassifierCascade(&pCascade);
	if(!pStorage)
		cvReleaseMemStorage(&pStorage);

}

faceDetect::faceDetect( ){
		faceImage = 0;
	    pFaceRectSeq = 0;
	try{
		pStorage = cvCreateMemStorage(0);                     // memory for detector to use
		pCascade = (CvHaarClassifierCascade *)cvLoad          // the face detector
			((OPENCV_ROOT"/data/haarcascades/haarcascade_frontalface_default.xml"),
	   0, 0, 0 );
// 		// validate that everything initialized properly
// 		if(!pStorage)
// 			AfxMessageBox("in faceDetect::faceDetect(const char *src): pStorege is empty\n");
// 		if(!pCascade)
// 			AfxMessageBox("in faceDetect::faceDetect(const char *src): PCascade is empty\n");
		if( !pStorage  || !pCascade)
		{
	 	char  *p=("Initialization failed:\n",
				(!faceImage)?  "can't load image file" :
			(!pCascade)? "can't load haar-cascade//  -- "
				"make sure path is correct" :
			"unable to allocate memory for data storage");
			AfxMessageBox(CString(p));
		}
	}catch(...)
	{
		AfxMessageBox("�����������з�������!!");
       // e.ReportError();
	}
}
//gettors

IplImage * faceDetect::getSrcImage(){
          return srcImage;
}

IplImage *faceDetect::getFaceImage(){
	CMyException e;
	if(faceImage)
	      return faceImage;
	else
		throw &e;
          
}

/***********************************************************
       20110310WWWFUNCTION:��ȡһ��ͼ�����ͼ��
	   �����ֱ����ԭͼ�����ͼ������ 
*************************************************************/
IplImage* faceDetect::cvGetSubImage(IplImage *image, CvRect roi)
{
	IplImage *result;
	// ���� ROI
	cvSetImageROI(image,roi);
	// ������ͼ��
	result = cvCreateImage( cvSize(roi.width, roi.height), image->depth, image->nChannels );
	cvCopy(image,result);
	cvResetImageROI(image);
	return result;
} 
/***********************************************************
       20110310WWWFUNCTION:����������������һ����ɫ����ο� 
*************************************************************/
void faceDetect::displayDetections(){
	     int     i=0;
        CvRect   *r=0;
	// draw a rectangular outline around each detection
try{
    	for(i=0;i<(pFaceRectSeq? pFaceRectSeq->total:0); i++ )
		{
		r = (CvRect*)cvGetSeqElem(pFaceRectSeq, i);
		CvPoint pt1 = { r->x, r->y };
		CvPoint pt2 = { r->x + r->width, r->y + r->height };
		cvRectangle(srcImage, pt1, pt2, CV_RGB(0,255,0), 3, 4, 0);
		//�õ�������������ͼ
		faceImage=cvGetSubImage(srcImage,CvRect(*r));
		if(!faceImage){
			AfxMessageBox("in void faceDetect::displayDetections(): faceImage is empty ,can't save it!!!\n");
		}
		}//for
	}catch(...)
	{
		AfxMessageBox("�����������з�������!!");
		//e.ReportError();
		return ;
	}
	    // create a window to display detected faces
}
/***********************************************************
       20110310WWWFUNCTION:��ͼƬ����������⣬����Ϊ��
	   ����ͼƬ�����ɹ�����true 
*************************************************************/
BOOL  faceDetect::faceDetector( const char *src ){   
	//load the image for dectect
try{
	srcImage  = cvLoadImage(src, CV_LOAD_IMAGE_COLOR) ;
// 	if(!srcImage)
// 	{		
// 		AfxMessageBox("in faceDetect::faceDetect(const char *src): srcImage is empty\n");
// 	    return false;
// 	}
	// detect faces in image
	pFaceRectSeq = cvHaarDetectObjects
		(srcImage, pCascade, pStorage,
		1.1,                       // increase search scale by 10% each pass
		3,                         // merge groups of three detections
		CV_HAAR_DO_CANNY_PRUNING,  // skip regions unlikely to contain a face
		cvSize(40,40));            // smallest size face to detect = 40x40
    // display face detections
// 	if(pFaceRectSeq==NULL)
// 	{
// 		AfxMessageBox("error in IplImage*  faceDetect::faceDetector() : pFaceRectSeq is empty!! ");
// 	    return false;
// 	}
    displayDetections();           //important: or else r is not well defined and get value!!!
}catch(CException e)
{
	AfxMessageBox("�����������з�������!!");
	 e.ReportError();
	 return false;
}
return true;
}
/***********************************************************
       20110310WWWFUNCTION:��ͼƬ����������⣬����Ϊ��
	   ����ͼƬ�����ɹ�����true----ɣ�溯������ 
*************************************************************/
BOOL  faceDetect::faceDetector(IplImage *p){   
	//create the image for dectect
  try{
	srcImage=cvCreateImage(cvGetSize(p),p->depth,p->nChannels);
	srcImage->origin=1;
	cvCopyImage(p,srcImage);
// 	if(!srcImage)
// 	{		
// 		//AfxMessageBox("in faceDetect::faceDetect(const char *src): srcImage is empty\n");
// 		//throw e;
// 		return false;
// 	}
	// detect faces in image
	pFaceRectSeq = cvHaarDetectObjects
		(srcImage, pCascade, pStorage,
		1.1,                       // increase search scale by 10% each pass
		3,                         // merge groups of three detections
		CV_HAAR_DO_CANNY_PRUNING,  // skip regions unlikely to contain a face
		cvSize(30,30));           // smallest size face to detect = 40x40
    // display face detections
// 	if(pFaceRectSeq==NULL)
// 	{
// 		AfxMessageBox("error in IplImage*  faceDetect::faceDetector() : pFaceRectSeq is empty!! ");
// 		return false;
// 	}
    displayDetections();           //important: or else r is not well defined and get value!!!
	}catch(CException e)
	{
		AfxMessageBox("�����������з�������!!");
		e.ReportError();
		return false;
	}
  return true;
}
/***********************************************************
       20110310WWWFUNCTION:�������������ֵ����һ����׼����
	   �ַ����ļ���������x.pgm������xΪ����ֵ��
*************************************************************/
const char * faceDetect::produceName(int index)
{
   char c1[2];
   char c2[]={".pgm"};
   itoa(index,c1,10);
   strcpy(c1+strlen(c1),c2);
   const char *p=c1;
   return p;
}
/***********************************************************
       20110310WWWFUNCTION:���������������ͼ��
	   ����Ϊ�ļ���
*************************************************************/
bool faceDetect::saveFaceImage(const char * name)
{	 
	if(faceImage!=NULL && !cvSaveImage(name, faceImage) )
	{
			AfxMessageBox("failed to write image file in bool faceDetect::saveFaceImage()\n");
	        return false;
	 }
	/*������ͷ�faceImage���ᵼ��û�ҵ�����ͼ��ʱ����faceImageΪ��
	  ʱ���������һͼ��ļ����*/
	if(faceImage!=NULL)
         	cvReleaseImage(&faceImage);
	 return true;
}
/***********************************************************
       20110424WWWFUNCTION:�����������
	   ���ұ�ǳ��������򣺣���Բ������
*************************************************************/
BOOL faceDetect::detect_and_draw( IplImage* img )
{
	//��ɫ����
    static CvScalar colors[] = 
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };
    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
		cvRound (img->height/scale)),
		8, 1 );
  try{
    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage(pStorage);
        //double t = (double)cvGetTickCount();
         pFaceRectSeq = cvHaarDetectObjects( small_img,pCascade,pStorage,
			1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
			cvSize(40, 40) );
        //t = (double)cvGetTickCount() - t;
        //printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for(int i = 0; i < (pFaceRectSeq ? pFaceRectSeq->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( pFaceRectSeq, i );
            //��Բ�α��
// 			CvPoint center;
//             int radius;
//             center.x = cvRound((r->x + r->width*0.5)*scale);
//             center.y = cvRound((r->y + r->height*0.5)*scale);
//             radius = cvRound((r->width + r->height)*0.25*scale);
//             cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
// 			//�þ��α��
// 	        CvPoint pt1 = { cvRound(r->x*scale),cvRound(r->y*scale)};
// 			CvPoint pt2 = {cvRound((r->x + r->width)*scale),cvRound((r->y + r->height)*scale)};
			CvPoint pt1 = { r->x*scale, r->y*scale};
			CvPoint pt2 = { (r->x + r->width)*scale, (r->y + r->height)*scale };
			if(r->height<80 || r->width<80)
				continue;
			cvRectangle(img, pt1, pt2,colors[i%8], 3, 4, 0);
			//��ͼ�񱣴浽faceImage��
			//CvRect temp=CvRect(pt1.x,pt1.y,pt2.x-pt1.x,pt2.y-pt1.y);
			r->x=pt1.x;  r->y=pt1.y; 
			r->width=pt2.x-pt1.x; r->width=pt2.y-pt1.y;
			faceImage=cvGetSubImage(img,*r);
        }
	}catch(...)
	{
          return  FALSE;
	}
	//�ͷ���Դ
	if(gray)
		cvReleaseImage(&gray);
	if(small_img)
		cvReleaseImage(&small_img);
	return TRUE;
}