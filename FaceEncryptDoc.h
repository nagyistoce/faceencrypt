// FaceEncryptDoc.h : interface of the CFaceEncryptDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEENCRYPTDOC_H__84C18444_F9B7_437D_B7F0_3D5B3B14FD02__INCLUDED_)
#define AFX_FACEENCRYPTDOC_H__84C18444_F9B7_437D_B7F0_3D5B3B14FD02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include   <vector>
// using   namespace   std;

class CFaceEncryptDoc : public CDocument
{
protected: // create from serialization only
	CFaceEncryptDoc();
	DECLARE_DYNCREATE(CFaceEncryptDoc)

// Attributes
public:

// Operations
public:
     void      setSelectedPath(CString path1);
	 CString   getSelectedPath();
	 void      setCurEncryInfo(CString info);
	 CString   getCurEncryInfo();
	 BOOL      IsEncrypt(CString path);
	 CStringArray* GetEncryptInfo();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceEncryptDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument( );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceEncryptDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//CMapStringToString EncryptMap;     不用MAP，只保存路径名即可
	CStringArray                EncryptedPath;
	CString                     SelectedPath;
	CString                     CurrentEnCryInfo;
// Generated message map functions
protected:
	//{{AFX_MSG(CFaceEncryptDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
/*	afx_msg  void  OnCloseDocument();*/
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEENCRYPTDOC_H__84C18444_F9B7_437D_B7F0_3D5B3B14FD02__INCLUDED_)
