#if !defined(AFX_FACEPROCESS_H__FF113614_22E9_4A55_9894_C4B306D3A657__INCLUDED_)
#define AFX_FACEPROCESS_H__FF113614_22E9_4A55_9894_C4B306D3A657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FaceProcess.h : header file
//����ͷ�ļ�
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
	IplImage  * m_SaveFrame;//���ڴ洢һ֡
	IplImage  * m_GrabFrame;//���ڴ洢һ֡
	int       m_vieoProtery;            //������Ƶ����
	char      chEdit[10];
	CRect     rect;
	CDC       *pDC;
	HDC       hDC;
	CWnd      *pwnd;
	CString   path;                  //��ǰ���ڲ�����·������
	BOOL      b_flagProcess;         //��־�Ǽ��ܻ��ǽ���1-���ܡ�2-����
	 //b_Process�����Ƿ����ڴ���ͼƬ����ϵ������ͼƬ��Paint�������Ƿ��ڽ���������֤
	 //����״̬��0---δ��ʾ����   1--����ʱ��������ʾ    2----����ʱ��������ʾ
	int      b_Process; 
    int      m_fameCount;            //�Ѿ������ͼƬ��
    float    matchPercent;           //����ʶ���Ƶ�ƥ����
	faceDetect       faceDetector;   //���������
	faceSimplify     faceSimplifier; //ͼƬ����
	faceRecognition  faceRecognitor; //����ѵ����ʶ����]
	const int        needTrainNumber;//����ѵ������ʶ��ģ�͵�������
	//��OntimerҪ����ѵ����ͼƬ�õ���һЩ����
	IplImage *m_snap;    
	IplImage *faceImage;             //��⵽������ͼƬ
    IplImage *faceGray;              //����������ͼƬ
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
