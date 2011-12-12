// SplitterNoMoveWnd.cpp: implementation of the CSplitterNoMoveWnd class.
//实现一个不可拖动分隔条的分割视图20110408WWW
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../FaceEncrypt.h"
#include "SplitterNoMoveWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/**//////////////////////////////////////////////////////////////////////////////
// CSplitterNoMoveWnd:

IMPLEMENT_DYNCREATE(CSplitterNoMoveWnd, CSplitterWnd)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitterNoMoveWnd, CSplitterWnd)
      ON_WM_NCHITTEST()
END_MESSAGE_MAP()

CSplitterNoMoveWnd::CSplitterNoMoveWnd()
{

}

CSplitterNoMoveWnd::~CSplitterNoMoveWnd()
{

}
//************************************20110408******************//
UINT  CSplitterNoMoveWnd::OnNcHitTest(CPoint point){
	return HTNOWHERE;
}
