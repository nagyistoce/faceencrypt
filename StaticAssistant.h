// StaticAssistant.h: interface for the CStaticAssistant class.
//包含头文件
#include "StdAfx.h"
//////////////////////////////////////////////////////////////////////
#include <afx.h>  ///使用CString时要用到
//#include "afxtempl.h"

#if !defined(AFX_STATICASSISTANT_H__D8309722_FCC0_4ECA_8313_5C963CDD894E__INCLUDED_)
#define AFX_STATICASSISTANT_H__D8309722_FCC0_4ECA_8313_5C963CDD894E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaticAssistant  
{
public:
	CStaticAssistant();
	virtual ~CStaticAssistant();
	  //set
	  static void SetEncryptFlag(BOOL  flag);
	  static void SetCurrentPath(CString path);
	 //get
	  static BOOL   GetEncryptFlag();
	  static CString GetCurrentPath();
	//Arttributes
	  static BOOL    deleteFile(CString fileName,HWND hwnd);
	  ////从指定文件读取加密信息到CArray或者CString中
	  static BOOL LoadEncryptInfo(CString FileName,CStringArray * path);
	  //将CMap或者CString中的加密信息保存到指定文件中
	  static BOOL    StoreEncryptInfo(CMapStringToString *m,CString fileName);
	  static BOOL    StoreEncryptInfo(CString path,CString fileName);
      //解密后从加密路径文件fileName中删除当前路径path
	  static BOOL    DeleteUncryptInfo(CString path,CString fileName);
private:
	  static  BOOL        EncryptFlag;          //当前操作是加密还是解密（1--加密、2--解密）
	  static  CString     CurrentPath;        //当前操作的文件路径
};
#endif // !defined(AFX_STATICASSISTANT_H__D8309722_FCC0_4ECA_8313_5C963CDD894E__INCLUDED_)
