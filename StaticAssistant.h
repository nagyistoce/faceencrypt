// StaticAssistant.h: interface for the CStaticAssistant class.
//����ͷ�ļ�
#include "StdAfx.h"
//////////////////////////////////////////////////////////////////////
#include <afx.h>  ///ʹ��CStringʱҪ�õ�
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
	  ////��ָ���ļ���ȡ������Ϣ��CArray����CString��
	  static BOOL LoadEncryptInfo(CString FileName,CStringArray * path);
	  //��CMap����CString�еļ�����Ϣ���浽ָ���ļ���
	  static BOOL    StoreEncryptInfo(CMapStringToString *m,CString fileName);
	  static BOOL    StoreEncryptInfo(CString path,CString fileName);
      //���ܺ�Ӽ���·���ļ�fileName��ɾ����ǰ·��path
	  static BOOL    DeleteUncryptInfo(CString path,CString fileName);
private:
	  static  BOOL        EncryptFlag;          //��ǰ�����Ǽ��ܻ��ǽ��ܣ�1--���ܡ�2--���ܣ�
	  static  CString     CurrentPath;        //��ǰ�������ļ�·��
};
#endif // !defined(AFX_STATICASSISTANT_H__D8309722_FCC0_4ECA_8313_5C963CDD894E__INCLUDED_)
