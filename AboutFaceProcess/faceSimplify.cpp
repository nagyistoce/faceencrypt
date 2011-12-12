/***************************************************
        ##time##:  20101008
		function:  �Լ�⵽������ͼ�����򵥵Ĵ���
		           1)���гߴ�����
				   2)��ͼ����лҶȻ�
****************************************************/
//the realize of class faceSimplify
#include "StdAfx.h"              //imprtant::������ʾ�ļ�û�н���
#include "faceSimplify.h"
//#include <math.h>
#define  WIDTH  92
#define  HEIGHT 112
//default constructor
//
faceSimplify::faceSimplify(){
	  // scale=0.618;
	   faceGrayImg=0;
	   dst_cvsize.width  = WIDTH;		    //Ŀ��ͼ��Ŀ�ΪԴͼ���
       dst_cvsize.height = HEIGHT;	        //Ŀ��ͼ��ĸ�ΪԴͼ���
}
//
faceSimplify::~faceSimplify(){
	// Free image memory
	if(faceGrayImg)
	   cvReleaseImage(&faceGrayImg);
    //void cvDestroyAllWindows(void);
}
IplImage * faceSimplify::getFaceImage(){
	return faceGrayImg;
}
/****************************************************
       20110310wwwFUCTION:�Լ�����������ͼƬ���л���
*****************************************************/
bool faceSimplify::Simplify(const char * p){
		//load the image for simplify
	   IplImage * src=cvLoadImage(p,CV_LOAD_IMAGE_COLOR);
	   if(src==NULL){
			AfxMessageBox("����ͼƬʧ��");
			return false;
		}
	  IplImage * dst = cvCreateImage( dst_cvsize, src->depth, src->nChannels);	//����Ŀ��ͼ��
		   cvResize(src, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��
		  // Allocate the grayscale image
		   faceGrayImg = cvCreateImage( cvSize(dst->width, dst->height), dst->depth, 1 );
		  // Convert it to grayscale
		   cvCvtColor(dst, faceGrayImg, CV_RGB2GRAY);
		///////////////////show the image/////////////////////
	   if(src)
		   cvReleaseImage(&src);
	   if(dst)
		   cvReleaseImage(&dst);
	   return true;
}
/****************************************************
       20110410wwwFUCTION:�Լ�����������ͼƬ���л���
	                       ���溯��������
*****************************************************/
bool faceSimplify::Simplify(IplImage * p){
		//load the image for simplify
	   //IplImage * src=cvLoadImage(p,CV_LOAD_IMAGE_COLOR);
       IplImage * src=cvCreateImage(cvGetSize(p),p->depth,p->nChannels);
             cvCopyImage(p,src);
	   if(src==NULL){
			AfxMessageBox("����ͼƬʧ��");
			return false;
		}
	  IplImage * dst = cvCreateImage( dst_cvsize, src->depth, src->nChannels);	//����Ŀ��ͼ��
		   cvResize(src, dst, CV_INTER_LINEAR);	//����Դͼ��Ŀ��ͼ��
		  // Allocate the grayscale image
		   faceGrayImg = cvCreateImage( cvSize(dst->width, dst->height), dst->depth, 1 );
		  // Convert it to grayscale
		   cvCvtColor(dst, faceGrayImg, CV_RGB2GRAY);
		///////////////////show the image/////////////////////
	   if(src)   
		   cvReleaseImage(&src);
	   if(dst)
		   cvReleaseImage(&dst);
	   return true;
}
/***********************************************************
       20110310WWWFUNCTION:�������������������ͼ��
	   ����Ϊ�ļ���
*************************************************************/
bool faceSimplify::saveFaceImage(const char * name)
{	 
	if(faceGrayImg!=NULL && !cvSaveImage(name, faceGrayImg) ){
		AfxMessageBox("����ͼƬʧ������");
		return false;
	 }
	/*������ͷ�faceImage���ᵼ��û�ҵ�����ͼ��ʱ����faceImageΪ��
	  ʱ���������һͼ��ļ����*/
	if(faceGrayImg!=NULL)
         cvReleaseImage(&faceGrayImg);
	return true;
}