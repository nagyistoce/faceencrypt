/***************************************************
        ##time##:  20101008
		function:  人脸检测
****************************************************/
//包含头文件
#ifndef FACEDETECT_CLASS
#define FACEDETECT_CLASS

class faceDetect{
public :
	faceDetect();
	~faceDetect();
	IplImage*   getSrcImage();
	IplImage*   getFaceImage();
	IplImage*   cvGetSubImage(IplImage *image, CvRect roi);  //get a sunImage
	void        displayDetections();             //画出检测出来的人脸区域轮廓
	BOOL        faceDetector(const char* src);   //设置人脸区域的一幅图指针
	BOOL        faceDetector(IplImage *p);       //设置人脸区域的一幅图指针
	BOOL        detect_and_draw( IplImage* img );//人脸检测
	const char* produceName(int index);          //产生标准化文件名
	bool        saveFaceImage(const char * name);//保存检测出来的人脸图像
private:
	IplImage                 * srcImage;        //载入的待处理的图像
	IplImage                 * faceImage; 
	//人脸检测出来的人脸图像--srcImage的字图
	CvHaarClassifierCascade  * pCascade;         // the face detector
	CvMemStorage             * pStorage;         // memory for detector to use
	CvSeq                    * pFaceRectSeq;     // memory-access interface
};
#endif;