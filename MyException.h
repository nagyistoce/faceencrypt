// MyException.h: interface for the CMyException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXCEPTION_H__C1335F3D_8636_4F24_8D58_BF11E5B5123C__INCLUDED_)
#define AFX_MYEXCEPTION_H__C1335F3D_8636_4F24_8D58_BF11E5B5123C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyException : public CException  
{
public:
	CMyException();
	virtual ~CMyException();

};

#endif // !defined(AFX_MYEXCEPTION_H__C1335F3D_8636_4F24_8D58_BF11E5B5123C__INCLUDED_)
