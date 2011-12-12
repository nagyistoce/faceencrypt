// eigenface.c, by Robin Hewitt, 2007
// Example program showing how to implement eigenface with OpenCV
// Usage:
// First, you need some face images. I used the ORL face database.
// You can download it for free at
//    www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
// List the training and test face images you want to use in the
// input files train.txt and test.txt. (Example input files are provided
// in the download.) To use these input files exactly as provided, unzip
// the ORL face database, and place train.txt, test.txt, and eigenface.exe
// at the root of the unzipped database.
//
// To run the learning phase of eigenface, enter
//    eigenface train
// at the command prompt. To run the recognition phase, enter
//    eigenface test
/***************************************************
        ##time##:  20101008
		function:  对faceSimplify处理过后的人脸进行识别
****************************************************/
#ifndef FACERECOGNITION_CLASS
#define FACERECOGNITION_CLASS

class faceRecognition{
public:
	//// Function prototypes
	faceRecognition();
	~faceRecognition();
	void learn();
	int recognize();
	void doPCA();
	void storeTrainingData();
	int  loadTrainingData(CvMat ** pTrainPersonNumMat);
	int  findNearestNeighbor(float * projectedTestFace);
	//BOOL addFaceImgArray(char * filename,char *ImageName);
	BOOL addFaceImgArray(char *ImageName,bool flag); ///重载：默认添加图片文件名到1--learnFileListPath,2--testFileListPat文件中
	BOOL addFaceImgArray(char *name,bool flag,int row);//添加到指定行
	int  loadFaceImgArray(char * filename);
private:
	//// Global variables
	IplImage ** faceImgArr        ; // array of face images
	CvMat    *  personNumTruthMat ; // array of person numbers
	int nTrainFaces               ; // the number of training images
	int nEigens                   ; // the number of eigenvalues
	IplImage * pAvgTrainImg       ; // the average image
	IplImage ** eigenVectArr      ; // eigenvectors
	CvMat    * eigenValMat           ; // eigenvalues
    CvMat    * projectedTrainFaceMat ; // projected training faces
	char     * learnFileListPath     ; // the image list for learn
    char     * testFileListPath      ; // the image list for test
};

#endif;