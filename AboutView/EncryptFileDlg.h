#if !defined(AFX_ENCRYPTFILEDLG_H__83BD2A88_B0D3_445B_901C_07BB055F7082__INCLUDED_)
#define AFX_ENCRYPTFILEDLG_H__83BD2A88_B0D3_445B_901C_07BB055F7082__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncryptFileDlg.h : header file
//
//#include "StdAfx.h"
#include "../AboutEncrypt/encrypt.h"
#include "../AboutEncrypt/RWEncry.h"
#include "EncrpInfoDlg.h"
#define   WM_INFOMESSAGE   WM_USER+30  //自定义消息
/////////////////////////////////////////////////////////////////////////////
// CEncryptFileDlg dialog
class  CEncryptFileDlg;
typedef struct _CryParam
{
	CString strFileName;
	CString strInfo;
	CString strPwd;
	CListBox *listCtrl;
	EncryInfo pinfo;
	CEncrpInfoDlg *dlg;
	CEncryptFileDlg *dlgThis;
	//HWND	_hWnd;
	int fileOrDir;
	bool bEncry;
	void Copy(struct _CryParam *dest)
	{
		strFileName = dest->strFileName;
		strInfo = dest->strInfo;
		strPwd = dest->strPwd;
		listCtrl = dest->listCtrl;
		pinfo = dest->pinfo;
		dlg = dest->dlg;
		fileOrDir = dest->fileOrDir;
		bEncry = dest->bEncry;
		dlgThis = dest->dlgThis;
		//_hWnd = dest->_hWnd;
	}
}CryParam;
class CEncryptFileDlg : public CDialog
{
// Construction
public:
	CEncryptFileDlg(CWnd* pParent = NULL);   // standard constructor
	void Info(CString info);
	void Mess(CString info,CString title,DWORD flag);
// Dialog Data
	//{{AFX_DATA(CEncryptFileDlg)
	enum { IDD = IDD_ENCRYPT_DLG };
	CListBox	m_listCtrl;
	CString	    m_pwd;
	CString	    m_listInfo;
	CString	    m_repwd;
	UINT	    m_fileOrDir;
	CString	    m_encryFile;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncryptFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
	void Encrypt();
	void Uncrypt();
	// Generated message map functions
	//{{AFX_MSG(CEncryptFileDlg)
	afx_msg void OnIntroduce();
	afx_msg void OnClear();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg  LRESULT OnViewMess( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRYPTFILEDLG_H__83BD2A88_B0D3_445B_901C_07BB055F7082__INCLUDED_)
