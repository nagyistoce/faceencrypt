// FaceEncrypt.h : main header file for the FACEENCRYPT application
//

#if !defined(AFX_FACEENCRYPT_H__1885DAD5_5A4A_457B_9576_A609FA593577__INCLUDED_)
#define AFX_FACEENCRYPT_H__1885DAD5_5A4A_457B_9576_A609FA593577__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptApp:
// See FaceEncrypt.cpp for the implementation of this class
//

class CFaceEncryptApp : public CWinApp
{
public:
	CFaceEncryptApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceEncryptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFaceEncryptApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEENCRYPT_H__1885DAD5_5A4A_457B_9576_A609FA593577__INCLUDED_)
