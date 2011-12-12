// SplitterNoMoveWnd.h: interface for the CSplitterNoMoveWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERNOMOVEWND_H__2A22B6AA_92EF_46BC_B9FB_8123E47B2628__INCLUDED_)
#define AFX_SPLITTERNOMOVEWND_H__2A22B6AA_92EF_46BC_B9FB_8123E47B2628__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSplitterNoMoveWnd : public CSplitterWnd  
{
	DECLARE_DYNCREATE(CSplitterNoMoveWnd)
public:
	CSplitterNoMoveWnd();
	virtual ~CSplitterNoMoveWnd();
    //virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
        // Generated message map functions
    //{{AFX_MSG(CSplitterNoMoveWnd)
        // NOTE - the ClassWizard will add and remove member functions here.
	afx_msg UINT    OnNcHitTest(CPoint point);     //∆¡±Œ Û±Í“∆∂Ø∑÷∏Ù
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SPLITTERNOMOVEWND_H__2A22B6AA_92EF_46BC_B9FB_8123E47B2628__INCLUDED_)
