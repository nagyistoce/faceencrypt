/***************************************************
        ##time##:  20101008
		function:  �Լ�⵽������ͼ�����򵥵Ĵ���
		           1)���гߴ�����
				   2)��ͼ����лҶȻ�
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
	//double     scale 		    ;   //���ű���
	CvSize     dst_cvsize 		;	//Ŀ��ͼ��ߴ�
	IplImage   * faceGrayImg    ;   //������Ŀ��ͼ��
};
#endif;
