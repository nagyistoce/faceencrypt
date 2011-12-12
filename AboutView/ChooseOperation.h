#if !defined(AFX_CHOOSEOPERATION_H__8C237001_1E60_4842_A211_6DC9978DF269__INCLUDED_)
#define AFX_CHOOSEOPERATION_H__8C237001_1E60_4842_A211_6DC9978DF269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseOperation.h : header file
//包含头文件
#include "../FaceEncryptDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CChooseOperation form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CChooseOperation : public CFormView
{
protected:
	CChooseOperation();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChooseOperation)

// Form Data
public:
	CFaceEncryptDoc* GetDocument();
	//{{AFX_DATA(CChooseOperation)
	enum { IDD = IDD_CHOOSEOPERATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
    BOOL PreCreateWindow(CREATESTRUCT& cs);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseOperation)
	protected:
	virtual void OnInitialUpdate();
    virtual BOOL Create(LPCTSTR, LPCTSTR, DWORD,const RECT&, CWnd*, UINT, CCreateContext*);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChooseOperation();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChooseOperation)
   	afx_msg void  OnGetMinMaxInfo(MINMAXINFO   FAR*   lpMMI);
	afx_msg void OnEncrypt();
	afx_msg void OnUncrypt();
	afx_msg void OnEncryptInfo();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in FaceEncryptView.cpp
inline CFaceEncryptDoc* CChooseOperation::GetDocument()
   { return (CFaceEncryptDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEOPERATION_H__8C237001_1E60_4842_A211_6DC9978DF269__INCLUDED_)
