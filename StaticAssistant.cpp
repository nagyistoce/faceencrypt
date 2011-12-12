// StaticAssistant.cpp: implementation of the CStaticAssistant class.
////20110409��www
//FUC��һ���ṩ�������ܣ��þ�̬����ʵ�֣����࣬�ڸ����д���һЩ����������ͼ-->�Ի���
//////////////////////////////////////////////////////////////////////
/*************ͷ�ļ�**********/
#include "StdAfx.h" 
#include "FaceEncrypt.h"
#include "StaticAssistant.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//��ʼ����̬���ݳ�Ա
BOOL    CStaticAssistant::EncryptFlag=true;
CString   CStaticAssistant::CurrentPath="";
//BOOL CStaticAssistant::EncryptFlag=true;
CStaticAssistant::CStaticAssistant()
{

}

CStaticAssistant::~CStaticAssistant()
{

}
//setors

void CStaticAssistant::SetEncryptFlag(BOOL flag){
           EncryptFlag=flag ;
}
void CStaticAssistant::SetCurrentPath(CString path){
           CurrentPath=path;
}
//getors
BOOL CStaticAssistant::GetEncryptFlag(){
           return EncryptFlag;
}
CString  CStaticAssistant::GetCurrentPath(){
           return  CurrentPath;
}
//�����ļ���ɾ���ļ�
BOOL   CStaticAssistant::deleteFile(CString fileName,HWND h)
{
	//�����е���ʱ�ļ�ɾ��������վ
	//AfxMessageBox(fileName);
        //fileName="E:\\Test\\3.txt\0";
	char *File =fileName.GetBuffer(fileName.GetLength());
	//AfxMessageBox(CString(File));
	SHFILEOPSTRUCT op;
	ZeroMemory(&op, sizeof(op));
	    op.hwnd =h;//(HWND)AfxGetMainWnd();
    	op.wFunc = FO_DELETE;
	    op.pFrom = File;
	    op.fFlags=FOF_NOCONFIRMATION | FOF_NOERRORUI;//FOF_ALLOWUNDO;
    //SHFileOperation( &op);
	if( 0 != SHFileOperation(&op))
	{
		AfxMessageBox("ɾ���ļ�����,����");
		return false ;
	}
      return true;
}
/*****��ָ���ļ����ؼ���·����Ϣ��������fileName20110422www*****/
/******************************************************************
 * File:�ļ���                                                    *
 * path������                                                     *
 * �Զ������ո�           *
 ******************************************************************/
BOOL  CStaticAssistant::LoadEncryptInfo(CString FileName,CStringArray *path){
	CStdioFile File;
	CString temppath=_T("");
	try {
		File.Open(FileName,CFile::modeRead);
		int rowLength=0;
		while(File.ReadString(temppath)==true)
		{
			temppath.TrimRight(); temppath.TrimLeft();  //�����ո�
			//AfxMessageBox("key=:: "+key+"::");
			if(temppath=="")            continue;
		    else                    rowLength++;
		}
		File.SeekToBegin();
		for(int i=0;i<rowLength;i++)
		{
			File.ReadString(temppath);
			temppath.TrimRight(); temppath.TrimLeft();  //�����ո�
			//AfxMessageBox("key=:: "+key+"::");
			if(temppath=="")
			{  i--;	continue;}   //�����ո����˼�����
			path->SetAtGrow(i,temppath);//�ӵ�CArray��
		}
	}catch(...)
	{
		File.Close();
		return false;
		AfxMessageBox("������Ҫ�ļ�����������");
	}
	return TRUE;
}
//������Ϣ��ָ���ļ���
BOOL CStaticAssistant::StoreEncryptInfo(CMapStringToString *m,CString fileName){
	CStdioFile File;
	try{
		CString key=_T(""), value=_T("");
		File.Open("res/temp.znl",CFile::modeWrite| CFile::modeCreate);
		File.SeekToBegin();
		//����Cmap��ȡ���ݲ�д��ָ�����Ǹ��ļ�
		POSITION pos = m->GetStartPosition();
		while(pos)	{ 
			m->GetNextAssoc(pos,key,value);
			File.WriteString(key+"\n");
			File.WriteString(value+"\n");
			//AfxMessageBox(key+"::"+value);			 
		}
	}catch(...){
		File.Close();
		return false;
		AfxMessageBox("������Ҫ�ļ�ʧ�ܣ������ԣ�");
	}
	return true;
}
/*****���浱ǰ����·��path��ָ���ļ���fileName20110422www*****/
/******************************************************************
 *   ����ļ����пո��У���ӵ���һ���ո��д�������               *
 * �ӵ��ļ���ĩβ��Ϊ�˷�������ɾ���в�����Ӧ�������·��ĩβ   *
 * �Զ�����㹻��������Ҫ���ܵ��·���ĳ��ȣ���Ŀո�           *
 ******************************************************************/
BOOL CStaticAssistant::StoreEncryptInfo(CString path,CString fileName){
		CStdioFile File;
		CString spacei="                                                                                                                      ";
		CString temp=_T("");
		int     tempLen=0;
	try{
		File.Open(fileName,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate);
		File.SeekToBegin();
		//�����ļ����ݻ�ȡ����λ��
		while(File.ReadString(temp)==true){
			tempLen=temp.GetLength()+2;         //��Ҫ�����ǻ��з�ռ2�ֽ�
			temp.TrimLeft(); temp.TrimRight(); //�������ҿո�
			if(temp==""){
				File.Seek(-tempLen,CFile::current);
			    File.WriteString(path);  //д��Ҫ�����·����
			    return TRUE;
			}
		}
		File.WriteString(path+spacei+"\n");  ///д��ĩβ
		return TRUE;
	}catch(...){
		File.Close();
		return FALSE;
		AfxMessageBox("������Ҫ�ļ�ʧ�ܣ������ԣ�");
	}
	return true;
}
/*****ɾ����ǰ����·��path��ָ���ļ���fileName20110423www*****/
/******************************************************************
 *  ��ɾ����Ҫʹ�����·������ͬ���ȵĿո�������                *
 ******************************************************************/
BOOL CStaticAssistant::DeleteUncryptInfo(CString path,CString fileName){
		CStdioFile File;
		CString spacei="                                                                                                                               ";
		CString temp=_T("");
		int     tempLen=0;
	try{
		File.Open(fileName,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate);
		File.SeekToBegin();
		//�����ļ����ݻ�ȡ����λ��
		while(File.ReadString(temp)==true){
			tempLen=temp.GetLength()+2;         //��Ҫ�����ǻ��з�ռ2�ֽ�
			temp.TrimLeft(); temp.TrimRight(); //�������ҿո�
			if(temp==path){
				int len=temp.GetLength();
				spacei=spacei.Left(len);
				File.Seek(-tempLen,CFile::current); //�����ļ��ڲ�ָ��
			    File.WriteString(spacei);           //д��Ҫ�����·����
			    return TRUE;
			}
		}
		File.Close();   
		return FALSE;//�ر��ļ�������
	}catch(...){
		File.Close();
		return FALSE;
	}
}