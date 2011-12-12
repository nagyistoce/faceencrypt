// StaticAssistant.cpp: implementation of the CStaticAssistant class.
////20110409：www
//FUC：一个提供辅助功能（用静态函数实现）的类，在各类中传递一些参数，（视图-->对话框）
//////////////////////////////////////////////////////////////////////
/*************头文件**********/
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
//初始化静态数据成员
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
//根据文件名删除文件
BOOL   CStaticAssistant::deleteFile(CString fileName,HWND h)
{
	//把所有的临时文件删除到回收站
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
		AfxMessageBox("删除文件出错,请检查");
		return false ;
	}
      return true;
}
/*****从指定文件加载加密路径信息到数组中fileName20110422www*****/
/******************************************************************
 * File:文件名                                                    *
 * path：数组                                                     *
 * 自动消除空格           *
 ******************************************************************/
BOOL  CStaticAssistant::LoadEncryptInfo(CString FileName,CStringArray *path){
	CStdioFile File;
	CString temppath=_T("");
	try {
		File.Open(FileName,CFile::modeRead);
		int rowLength=0;
		while(File.ReadString(temppath)==true)
		{
			temppath.TrimRight(); temppath.TrimLeft();  //消除空格
			//AfxMessageBox("key=:: "+key+"::");
			if(temppath=="")            continue;
		    else                    rowLength++;
		}
		File.SeekToBegin();
		for(int i=0;i<rowLength;i++)
		{
			File.ReadString(temppath);
			temppath.TrimRight(); temppath.TrimLeft();  //消除空格
			//AfxMessageBox("key=:: "+key+"::");
			if(temppath=="")
			{  i--;	continue;}   //读到空格会回退计数器
			path->SetAtGrow(i,temppath);//加到CArray中
		}
	}catch(...)
	{
		File.Close();
		return false;
		AfxMessageBox("加载重要文件错误，请重试");
	}
	return TRUE;
}
//保存信息到指定文件夹
BOOL CStaticAssistant::StoreEncryptInfo(CMapStringToString *m,CString fileName){
	CStdioFile File;
	try{
		CString key=_T(""), value=_T("");
		File.Open("res/temp.znl",CFile::modeWrite| CFile::modeCreate);
		File.SeekToBegin();
		//遍历Cmap获取数据并写入指定的那个文件
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
		AfxMessageBox("保存重要文件失败，请重试！");
	}
	return true;
}
/*****保存当前加密路径path到指定文件夹fileName20110422www*****/
/******************************************************************
 *   如过文件中有空格行，则加到第一个空格行处，否则               *
 * 加到文件的末尾，为了方面后面的删除行操作，应该再添加路径末尾   *
 * 自动添加足够（超过需要加密的最长路径的长度）多的空格           *
 ******************************************************************/
BOOL CStaticAssistant::StoreEncryptInfo(CString path,CString fileName){
		CStdioFile File;
		CString spacei="                                                                                                                      ";
		CString temp=_T("");
		int     tempLen=0;
	try{
		File.Open(fileName,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate);
		File.SeekToBegin();
		//遍历文件数据获取插入位置
		while(File.ReadString(temp)==true){
			tempLen=temp.GetLength()+2;         //重要，考虑换行符占2字节
			temp.TrimLeft(); temp.TrimRight(); //消除左右空格
			if(temp==""){
				File.Seek(-tempLen,CFile::current);
			    File.WriteString(path);  //写入要加入的路径名
			    return TRUE;
			}
		}
		File.WriteString(path+spacei+"\n");  ///写入末尾
		return TRUE;
	}catch(...){
		File.Close();
		return FALSE;
		AfxMessageBox("保存重要文件失败，请重试！");
	}
	return true;
}
/*****删除当前加密路径path从指定文件夹fileName20110423www*****/
/******************************************************************
 *  此删除主要使用与此路径名相同长度的空格串来覆盖                *
 ******************************************************************/
BOOL CStaticAssistant::DeleteUncryptInfo(CString path,CString fileName){
		CStdioFile File;
		CString spacei="                                                                                                                               ";
		CString temp=_T("");
		int     tempLen=0;
	try{
		File.Open(fileName,CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate);
		File.SeekToBegin();
		//遍历文件数据获取插入位置
		while(File.ReadString(temp)==true){
			tempLen=temp.GetLength()+2;         //重要，考虑换行符占2字节
			temp.TrimLeft(); temp.TrimRight(); //消除左右空格
			if(temp==path){
				int len=temp.GetLength();
				spacei=spacei.Left(len);
				File.Seek(-tempLen,CFile::current); //回退文件内部指针
			    File.WriteString(spacei);           //写入要加入的路径名
			    return TRUE;
			}
		}
		File.Close();   
		return FALSE;//关闭文件并返回
	}catch(...){
		File.Close();
		return FALSE;
	}
}