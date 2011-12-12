// FaceEncryptView.h : interface of the CFaceEncryptView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEENCRYPTVIEW_H__94AD65A0_FC37_4C6E_B844_34D4E948070B__INCLUDED_)
#define AFX_FACEENCRYPTVIEW_H__94AD65A0_FC37_4C6E_B844_34D4E948070B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/********************包含头文件***************/
#include  "../FaceEncryptDoc.h"

class CFaceEncryptView : public CFormView
{
protected: // create from serialization only
	CFaceEncryptView();
	DECLARE_DYNCREATE(CFaceEncryptView)

public:
	//{{AFX_DATA(CFaceEncryptView)
	IplImage *welcomeImage;
	enum{ IDD = IDD_FACEENCRYPT_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CFaceEncryptDoc* GetDocument();
    
// Operations
public:
    void ShowImage( IplImage* img, UINT ID );    // ID 是Picture Control控件的ID号
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceEncryptView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
// 	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
// 	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
// 	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
// 	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceEncryptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceEncryptView)
	afx_msg   void   OnPaint();
    afx_msg   void   OnDraw(CDC *pDc);
	afx_msg   void   OnEnter();
	afx_msg   void   OnTuichu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FaceEncryptView.cpp
inline CFaceEncryptDoc* CFaceEncryptView::GetDocument()
   { return (CFaceEncryptDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEENCRYPTVIEW_H__94AD65A0_FC37_4C6E_B844_34D4E948070B__INCLUDED_)
