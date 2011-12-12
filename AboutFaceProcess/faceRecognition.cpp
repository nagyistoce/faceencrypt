/***************************************************
        ##time##:  20101008
		function:  对faceSimplify处理过后的人脸进行识别
****************************************************/
//the realize of class faceSimplify
//包含头文件
#include "StdAfx.h"              //imprtant::否则提示文件没有结束
#include "faceRecognition.h"
//constructor
faceRecognition::faceRecognition(){
	faceImgArr        =0          ; // array of face images
	personNumTruthMat =0          ; // array of person numbers
    nTrainFaces       =0          ; // the number of training images
	nEigens           =0          ; // the number of eigenvalues
	pAvgTrainImg      =0          ; // the average image
	eigenVectArr      =0          ; // eigenvectors
	eigenValMat       =0          ; // eigenvalues
    projectedTrainFaceMat=0       ; // projected training faces
	learnFileListPath= "./res/train.txt";
	testFileListPath = "./res/test.txt" ;
}
//
faceRecognition::~faceRecognition(){
	//释放资源,不能用delete
// 	for(int i=0;i<nTrainFaces;i++)
// 		 if(faceImgArr[i]) cvReleaseImage(&faceImgArr[i]);
//     for(int j=0;j<nEigens;j++)
// 		 if(eigenVectArr[j]) cvReleaseImage(&eigenVectArr[j]);
	if(personNumTruthMat)
		 cvReleaseMat(&personNumTruthMat);
	if(projectedTrainFaceMat)
         cvReleaseMat(&projectedTrainFaceMat);
}
//////////////////////////////////
// learn()
//
void  faceRecognition::learn()
{   
	AfxMessageBox("训练人脸识别模型");
	int i, offset;
	// load training data
	nTrainFaces = loadFaceImgArray(learnFileListPath);
	if( nTrainFaces < 2){
		CString S;
		S.Format("Need 2 or more training faces\nInput file contains only %d\n", nTrainFaces);AfxMessageBox(S);    return;
	    return ;
	}
	// do PCA on the training faces
	doPCA();
	// project the training images onto the PCA subspace
	projectedTrainFaceMat = cvCreateMat( nTrainFaces, nEigens, CV_32FC1 );
	offset = projectedTrainFaceMat->step / sizeof(float);
	for(i=0; i<nTrainFaces; i++){
		//int offset = i * nEigens;
		cvEigenDecomposite(
			faceImgArr[i],
			nEigens,
			eigenVectArr,
			0, 0,
			pAvgTrainImg,
			//projectedTrainFaceMat->data.fl + i*nEigens);
			projectedTrainFaceMat->data.fl + i*offset);
	}
	// store the recognition data as an xml file
	storeTrainingData();
}
//////////////////////////////////
// recognize()
//返回本次训练通过的图片数
int faceRecognition::recognize()
{   
	int i, nTestFaces  = 0;         // the number of test images
	CvMat * trainPersonNumMat = 0;  // the person numbers during training
	float * projectedTestFace = 0;
	// load test images and ground truth for person number
	nTestFaces = loadFaceImgArray(testFileListPath);
	// load the saved training data
	if( !loadTrainingData( &trainPersonNumMat ) ) return 0;
	// project the test images onto the PCA subspace
	projectedTestFace = (float *)cvAlloc( nEigens*sizeof(float) );
	//处理输出结果,记录一次训练中正确匹配的图片数
	int count=0;
	for(i=0; i<nTestFaces; i++)
	{  int iNearest, nearest, truth;
		// project the test image onto the PCA subspace
		cvEigenDecomposite(
			faceImgArr[i],
			nEigens,
			eigenVectArr,
			0, 0,
			pAvgTrainImg,
			projectedTestFace);
		iNearest = findNearestNeighbor(projectedTestFace);
		truth    = personNumTruthMat->data.i[i];
		nearest  = trainPersonNumMat->data.i[iNearest];
	//	AfxMessageBox("nearest = %d, Truth = %d", nearest, truth);
		if(nearest==truth)
			  count++;
	}//for
	return count;
}


//////////////////////////////////
// loadTrainingData()
int faceRecognition::loadTrainingData(CvMat ** pTrainPersonNumMat)
{
	CvFileStorage * fileStorage;
	int i;
	// create a file-storage interface
	fileStorage = cvOpenFileStorage( "res/facedata.xml", 0, CV_STORAGE_READ );
	if( !fileStorage ){
		AfxMessageBox("Can't open facedata.xml\n");
		return 0;
	}
	nEigens = cvReadIntByName(fileStorage, 0, "nEigens", 0);
	nTrainFaces = cvReadIntByName(fileStorage, 0, "nTrainFaces", 0);
	*pTrainPersonNumMat = (CvMat *)cvReadByName(fileStorage, 0, "trainPersonNumMat", 0);
	eigenValMat  = (CvMat *)cvReadByName(fileStorage, 0, "eigenValMat", 0);
	projectedTrainFaceMat = (CvMat *)cvReadByName(fileStorage, 0, "projectedTrainFaceMat", 0);
	pAvgTrainImg = (IplImage *)cvReadByName(fileStorage, 0, "avgTrainImg", 0);
	eigenVectArr = (IplImage **)cvAlloc(nTrainFaces*sizeof(IplImage *));
	for(i=0; i<nEigens; i++){
		char varname[200];
		sprintf( varname, "eigenVect_%d", i );
		eigenVectArr[i] = (IplImage *)cvReadByName(fileStorage, 0, varname, 0);
	}
	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );
	return 1;
}


//////////////////////////////////
// storeTrainingData()
//
void faceRecognition::storeTrainingData()
{
	CvFileStorage * fileStorage;
	int i;
	// create a file-storage interface
	fileStorage = cvOpenFileStorage( "./res/facedata.xml", 0, CV_STORAGE_WRITE );
	// store all the data
	cvWriteInt( fileStorage, "nEigens", nEigens );
	cvWriteInt( fileStorage, "nTrainFaces", nTrainFaces );
	cvWrite(fileStorage, "trainPersonNumMat", personNumTruthMat, cvAttrList(0,0));
	cvWrite(fileStorage, "eigenValMat", eigenValMat, cvAttrList(0,0));
	cvWrite(fileStorage, "projectedTrainFaceMat", projectedTrainFaceMat, cvAttrList(0,0));
	cvWrite(fileStorage, "avgTrainImg", pAvgTrainImg, cvAttrList(0,0));
	for(i=0; i<nEigens; i++){
		char varname[200];
		sprintf( varname, "eigenVect_%d", i );
		cvWrite(fileStorage, varname, eigenVectArr[i], cvAttrList(0,0));
	}
	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage);
}
//////////////////////////////////
// findNearestNeighbor()
//
int faceRecognition::findNearestNeighbor(float * projectedTestFace)
{
	//double leastDistSq = 1e12;
	double leastDistSq = DBL_MAX;
	int i, iTrain, iNearest = 0;
	for(iTrain=0; iTrain<nTrainFaces; iTrain++)	{
		double distSq=0;
		for(i=0; i<nEigens; i++){
			float d_i =projectedTestFace[i] -projectedTrainFaceMat->data.fl[iTrain*nEigens + i];
			//distSq += d_i*d_i / eigenValMat->data.fl[i];  // Mahalanobis
			distSq += d_i*d_i; // Euclidean
		}
		if(distSq < leastDistSq){
			leastDistSq = distSq;
			iNearest = iTrain;
		}
	}return iNearest;
}


//////////////////////////////////
// doPCA()
//
void faceRecognition::doPCA()
{   int i;
	CvTermCriteria calcLimit;
	CvSize faceImgSize;
	// set the number of eigenvalues to use
	nEigens = nTrainFaces-1;
	// allocate the eigenvector images
	faceImgSize.width  = faceImgArr[0]->width;
	faceImgSize.height = faceImgArr[0]->height;
	eigenVectArr = (IplImage**)cvAlloc(sizeof(IplImage*) * nEigens);
	for(i=0; i<nEigens; i++)
		eigenVectArr[i] = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);
	// allocate the eigenvalue array
	eigenValMat = cvCreateMat( 1, nEigens, CV_32FC1 );
	// allocate the averaged image
	pAvgTrainImg = cvCreateImage(faceImgSize, IPL_DEPTH_32F, 1);
	// set the PCA termination criterion
	calcLimit = cvTermCriteria( CV_TERMCRIT_ITER, nEigens, 1);
	// compute average image, eigenvalues, and eigenvectors
	cvCalcEigenObjects(
		nTrainFaces,                    // Number of source objects.
		(void*)faceImgArr,              // ...
		(void*)eigenVectArr,
		CV_EIGOBJ_NO_CALLBACK,          //Input/output flags.
		0,                              //Input/output buffer size in bytes. The size is zero, if unknown.
		0,          //Pointer to the structure that contains all necessary data for the callback functions.
		&calcLimit,                     //Determines conditions for the calculation to be finished.
		pAvgTrainImg,                   //Averaged object.
		eigenValMat->data.fl);          //Pointer to the eigenvalues array in the descending order;may be NULL.
    //根据norm_type的不同值，图像src将被规范化
	cvNormalize(eigenValMat, eigenValMat, 1, 0, CV_L1, 0);
}

//////////////////////////////////
// loadFaceImgArray()
//
int faceRecognition::loadFaceImgArray(char * filename)
{
	//////////////////////////////////////////////////////////////////////////
	//改用CStdioFile实现
	CStdioFile imgListFile;
	CString    imgFileName;
	CString     temp;
	CString     tempId1="";
	int iFace, nFaces=0;
	// open the input file
 try{
	imgListFile.Open(filename,CStdioFile::modeRead);
	// count the number of faces
	imgListFile.SeekToBegin();
	while(imgListFile.ReadString(imgFileName)) ++nFaces;
	//20101003_问题一:将文件内部的位置指针重新指向一个流（数据流/文件）的开头 
	imgListFile.SeekToBegin();                
	// allocate the face-image array and person number matrix
	faceImgArr        = (IplImage **)cvAlloc( nFaces*sizeof(IplImage *) );
	personNumTruthMat = cvCreateMat( 1, nFaces, CV_32SC1 );
	// store the face images in an array
	for(iFace=0; iFace<nFaces; iFace++){ 
		//temp.Format("%d %s",personNumTruthMat->data.i+iFace,imgFileName);
		imgListFile.ReadString(temp);
		imgFileName=temp.Right(temp.GetLength()-3);
		tempId1=temp.Left(3);   //读取人脸编号
		//去掉左、右边空格
		tempId1.TrimRight();imgFileName.TrimLeft();
        *(personNumTruthMat->data.i+iFace)=atoi(tempId1.GetBuffer(tempId1.GetLength()));
		//去掉左、右边空格
		imgFileName.TrimRight();imgFileName.TrimLeft();
		imgFileName=imgFileName.GetBuffer(imgFileName.GetLength());
		//AfxMessageBox("$"+imgFileName+"$");
		faceImgArr[iFace] = cvLoadImage(imgFileName, CV_LOAD_IMAGE_GRAYSCALE);
// 		if(!faceImgArr[iFace]){CString S;
// 			    S.Format("Can\'t load image from %s\n", imgFileName); AfxMessageBox(S);return 0;
// 		    AfxMessageBox(S);}
	}
	imgListFile.Close();
 }catch(...){
		imgListFile.Close();
		AfxMessageBox("加载训练图片失败");
		return 0;
	}
	return nFaces;
}
//////////////////////////////////
// addFaceImgArray()：添加固定格式训练、测试图片信息（编号、文件名）到txt文件
//
// BOOL faceRecognition::addFaceImgArray(char * fileName,char * imgName){
//    CStdioFile  fwrite;
//    CString  temp=CString(imgName);
// 	       temp=temp+"\n";
//   try{
//       if(fwrite.Open(fileName,CStdioFile::modeReadWrite)==FALSE)
// 		  AfxMessageBox("打开文件 "+CString(fileName)+" 失败！！");
// 	  fwrite.SeekToEnd();
// 	  fwrite.WriteString(temp);  //自动加上换行符号
// 	  //close()
// 	  fwrite.Close();
//   }catch(CFileException e)
//   {
//       AfxMessageBox("文件写入失败：："+CString(fileName));
//   }	 
// 	  return true;
// }
//////////////////////////////////
// addFaceImgArray()：添加固定格式训练、测试图片信息（编号、文件名）到txt文件
// 上面重载函数
BOOL faceRecognition::addFaceImgArray(char *name,bool flag){
	CStdioFile  fwrite;
	CString  temp=CString(name);
	temp=temp+"\n";//自动加上换行符号
	try{
		if(flag==true) {//for train
			if(fwrite.Open(learnFileListPath,CFile::modeNoTruncate|CStdioFile::modeReadWrite|CStdioFile::modeCreate)==FALSE)
			  AfxMessageBox("打开文件 "+CString(learnFileListPath)+" 失败！！");
		}else{
		   if(fwrite.Open(testFileListPath,CStdioFile::modeReadWrite)==FALSE)
			  AfxMessageBox("打开文件 "+CString(testFileListPath)+" 失败！！");
		}
		fwrite.SeekToEnd();
		fwrite.WriteString(temp);  
		//close()
		fwrite.Close();
	}catch(CFileException e)
	{
		AfxMessageBox("文件写入失败：："+CString(name));
	}	 
	  return true;
}
//写到指定的行，及替换原来的行
BOOL faceRecognition::addFaceImgArray(char *name,bool flag,int row){
	CStdioFile  fwrite;
    CString S1="";
	row=row-1;
	CString  temp=CString(name);
	//temp=temp+"\n";//自动加上换行符号
	try{
		if(flag==true) 
		{//for train
			if(fwrite.Open(learnFileListPath,CStdioFile::modeReadWrite|CStdioFile::modeCreate|CStdioFile::modeNoTruncate)==FALSE)
				AfxMessageBox("打开文件 "+CString(learnFileListPath)+" 失败！！");
		}else{
			if(fwrite.Open(testFileListPath,CStdioFile::modeReadWrite)==FALSE)
				AfxMessageBox("打开文件 "+CString(testFileListPath)+" 失败！！");
		}
		fwrite.SeekToBegin();
		for(int i=0; i<row; i++){
			fwrite.ReadString(S1);
		}
        fwrite.ReadString(S1); //指针指向第row+1行开头
		///fwrite.ReadString(S2);
        fwrite.Seek(-S1.GetLength()-2,CFile::current);  //考虑回车换行符//指针指向第row行开头
        fwrite.WriteString(temp);
		// AfxMessageBox(S2);
		//fwrite.WriteString(temp);
// 		int len=S1.GetLength()-2-temp.GetLength();
// 		if(len>0)       //用指定符号覆盖多余字符
		fwrite.SeekToBegin();
		fwrite.Close();
	}catch(CFileException e)
	{
        fwrite.Close();
		AfxMessageBox("文件写入失败：："+CString(name));
	}	 
	return true;
}