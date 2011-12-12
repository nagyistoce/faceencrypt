/***************************************************
        ##time##:  20101008
		function:  对检测到的人脸图形做简单的处理
		           1)进行尺寸缩放
				   2)将图像进行灰度化
****************************************************/
#ifndef FACESIMPLIFY_CLASS
#define FACESIMPLIFY_CLASS
//the defination of faceSimplify
class faceSimplify{
public :
         faceSimplify();
		 ~faceSimplify();
		 IplImage * getFaceImage();
		 bool Simplify(const char * p);
		 bool Simplify(IplImage *src);
		 bool saveFaceImage(const char * name);
		 //bool Simplify(const char * p);
private:
	//double     scale 		    ;   //缩放倍数
	CvSize     dst_cvsize 		;	//目标图像尺寸
	IplImage   * faceGrayImg    ;   //化简后的目标图像
};
#endif;
