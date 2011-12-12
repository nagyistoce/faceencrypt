/***************************************************
        ##time##:  20101008
		function:  �������
****************************************************/
//����ͷ�ļ�
#ifndef FACEDETECT_CLASS
#define FACEDETECT_CLASS

class faceDetect{
public :
	faceDetect();
	~faceDetect();
	IplImage*   getSrcImage();
	IplImage*   getFaceImage();
	IplImage*   cvGetSubImage(IplImage *image, CvRect roi);  //get a sunImage
	void        displayDetections();             //������������������������
	BOOL        faceDetector(const char* src);   //�������������һ��ͼָ��
	BOOL        faceDetector(IplImage *p);       //�������������һ��ͼָ��
	BOOL        detect_and_draw( IplImage* img );//�������
	const char* produceName(int index);          //������׼���ļ���
	bool        saveFaceImage(const char * name);//���������������ͼ��
private:
	IplImage                 * srcImage;        //����Ĵ������ͼ��
	IplImage                 * faceImage; 
	//����������������ͼ��--srcImage����ͼ
	CvHaarClassifierCascade  * pCascade;         // the face detector
	CvMemStorage             * pStorage;         // memory for detector to use
	CvSeq                    * pFaceRectSeq;     // memory-access interface
};
#endif;