/***************************************************
        ##time##:  20101008
		function:  对检测到的人脸图形做简单的处理
		           1)进行尺寸缩放
				   2)将图像进行灰度化
****************************************************/
//the realize of class faceSimplify
#include "StdAfx.h"              //imprtant::否则提示文件没有结束
#include "faceSimplify.h"
//#include <math.h>
#define  WIDTH  92
#define  HEIGHT 112
//default constructor
//
faceSimplify::faceSimplify(){
	  // scale=0.618;
	   faceGrayImg=0;
	   dst_cvsize.width  = WIDTH;		    //目标图像的宽为源图象宽
       dst_cvsize.height = HEIGHT;	        //目标图像的高为源图象高
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
       20110310wwwFUCTION:对检测出来的人脸图片进行化简
*****************************************************/
bool faceSimplify::Simplify(const char * p){
		//load the image for simplify
	   IplImage * src=cvLoadImage(p,CV_LOAD_IMAGE_COLOR);
	   if(src==NULL){
			AfxMessageBox("加载图片失败");
			return false;
		}
	  IplImage * dst = cvCreateImage( dst_cvsize, src->depth, src->nChannels);	//构造目标图象
		   cvResize(src, dst, CV_INTER_LINEAR);	//缩放源图像到目标图像
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
       20110410wwwFUCTION:对检测出来的人脸图片进行化简
	                       上面函数的重载
*****************************************************/
bool faceSimplify::Simplify(IplImage * p){
		//load the image for simplify
	   //IplImage * src=cvLoadImage(p,CV_LOAD_IMAGE_COLOR);
       IplImage * src=cvCreateImage(cvGetSize(p),p->depth,p->nChannels);
             cvCopyImage(p,src);
	   if(src==NULL){
			AfxMessageBox("加载图片失败");
			return false;
		}
	  IplImage * dst = cvCreateImage( dst_cvsize, src->depth, src->nChannels);	//构造目标图象
		   cvResize(src, dst, CV_INTER_LINEAR);	//缩放源图像到目标图像
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
       20110310WWWFUNCTION:保存检测出来化简后的人脸图像
	   参数为文件名
*************************************************************/
bool faceSimplify::saveFaceImage(const char * name)
{	 
	if(faceGrayImg!=NULL && !cvSaveImage(name, faceGrayImg) ){
		AfxMessageBox("保存图片失败啦！");
		return false;
	 }
	/*如果不释放faceImage，会导致没找到人脸图像时，即faceImage为空
	  时，会输出上一图像的检测结果*/
	if(faceGrayImg!=NULL)
         cvReleaseImage(&faceGrayImg);
	return true;
}