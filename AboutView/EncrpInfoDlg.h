#if !defined(AFX_ENCRPINFODLG_H__3C00B040_89D0_4129_A272_40E6D6FFEE94__INCLUDED_)
#define AFX_ENCRPINFODLG_H__3C00B040_89D0_4129_A272_40E6D6FFEE94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EncrpInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEncrpInfoDlg dialog

class CEncrpInfoDlg : public CDialog
{
// Construction
public:
	CEncrpInfoDlg(CWnd* pParent = NULL);   // standard constructor
	void SetInfo(CString info);
// Dialog Data
	//{{AFX_DATA(CEncrpInfoDlg)
	enum { IDD = IDD_INFO_DLG };
	CString	m_info;
	UINT	m_flag;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncrpInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEncrpInfoDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRPINFODLG_H__3C00B040_89D0_4129_A272_40E6D6FFEE94__INCLUDED_)
