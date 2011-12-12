#if !defined(AFX_FACEPROCESS_H__FF113614_22E9_4A55_9894_C4B306D3A657__INCLUDED_)
#define AFX_FACEPROCESS_H__FF113614_22E9_4A55_9894_C4B306D3A657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FaceProcess.h : header file
//包含头文件
#include "../AboutFaceProcess/faceDetect.h"
#include "../AboutFaceProcess/faceRecognition.h"
#include "../AboutFaceProcess/faceSimplify.h"
/////////////////////////////////////////////////////////////////////////////
// CFaceProcess dialog

class CFaceProcess : public CDialog
{
// Construction
public:
	CFaceProcess(CWnd* pParent = NULL);   // standard constructor
    ~CFaceProcess();
protected:
// Dialog Data
	//{{AFX_DATA(CFaceProcess)
	enum { IDD = IDD_FACE_WND };
	HICON m_hIcon;
	CvvImage m_CvvImage;
	CvCapture * m_Video;
	IplImage  * m_SaveFrame;//用于存储一帧
	IplImage  * m_GrabFrame;//用于存储一帧
	int       m_vieoProtery;            //保存视频特性
	char      chEdit[10];
	CRect     rect;
	CDC       *pDC;
	HDC       hDC;
	CWnd      *pwnd;
	CString   path;                  //当前正在操作的路径名称
	BOOL      b_flagProcess;         //标志是加密还是解密1-加密、2-解密
	 //b_Process：：是否正在处理图片，关系到背景图片的Paint（）即是否在进行人脸认证
	 //三种状态：0---未显示视屏   1--加密时的视屏显示    2----解密时的视屏显示
	int      b_Process; 
    int      m_fameCount;            //已经保存的图片数
    float    matchPercent;           //人脸识别似的匹配率
	faceDetect       faceDetector;   //人脸检测类
	faceSimplify     faceSimplifier; //图片化简
	faceRecognition  faceRecognitor; //人脸训练和识别类]
	const int        needTrainNumber;//用来训练人脸识别模型的人脸数
	//在Ontimer要保存训练用图片用到的一些变量
	IplImage *m_snap;    
	IplImage *faceImage;             //检测到的人脸图片
    IplImage *faceGray;              //化简后的人脸图片
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceProcess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString GetImageName(CString filePath,int frameCount);
	// Generated message map functions
	//{{AFX_MSG(CFaceProcess)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	afx_msg void OnOk();
	afx_msg void OnClose();
	afx_msg void OnOpenCapture();
	afx_msg void OnRecognise();
	afx_msg BOOL OnSavePic();
	afx_msg void OnCloseCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEPROCESS_H__FF113614_22E9_4A55_9894_C4B306D3A657__INCLUDED_)
