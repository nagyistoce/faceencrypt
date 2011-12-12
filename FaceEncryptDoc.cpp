// FaceEncryptDoc.cpp : implementation of the CFaceEncryptDoc class
//

#include "stdafx.h"
#include "FaceEncrypt.h"

#include "FaceEncryptDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptDoc

IMPLEMENT_DYNCREATE(CFaceEncryptDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceEncryptDoc, CDocument)
	//{{AFX_MSG_MAP(CFaceEncryptDoc)
/*	ON_COMMAND(WM_CLOSE,OnCloseDocument)*/
	// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptDoc construction/destruction

CFaceEncryptDoc::CFaceEncryptDoc()
{
	// TODO: add one-time construction code here
      SelectedPath=" ";
	  AfxMessageBox("在文档构造函数里面加载加密信息");
	  BOOL b=CStaticAssistant::LoadEncryptInfo("res/temp.znl",&EncryptedPath);
      ASSERT(b==true);
	  //EncryptMap.CMap();
}

CFaceEncryptDoc::~CFaceEncryptDoc()
{
}

BOOL CFaceEncryptDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//从指定文件初始化数据
	//直接删除不好，可考虑用空格覆盖原文件
	//CStaticAssistant::deleteFile("res/temp.znl",NULL);
	//this->Serialize()
// 	BOOL b=CStaticAssistant::LoadEncryptInfo("res/temp.znl",&EncryptedPath);
// 	if(!b)
// 	{   AfxMessageBox("加载重要文件失败,请重试！");  return FALSE;}
	  return  TRUE;
}
void CFaceEncryptDoc::OnCloseDocument(){
	//AfxMessageBox("close  File");
	CDocument::OnCloseDocument();
}
/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptDoc serialization

void CFaceEncryptDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar<<SelectedPath;
// 		BOOL b=CStaticAssistant::StoreEncryptInfo(&EncryptMap,"res/temp.znl");
//          ASSERT(b==true);
		//AfxMessageBox("串行化");
	}
	else
	{
		// TODO: add loading code here
		//ar>>SelectedPath;
// 		BOOL b=CStaticAssistant::LoadEncryptInfo("res/无temp.znl",&EncryptMap);
//          ASSERT(b==true);
		//AfxMessageBox("并行化");
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptDoc diagnostics

#ifdef _DEBUG
void CFaceEncryptDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceEncryptDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceEncryptDoc commands
//设置当前选中文件路径
void  CFaceEncryptDoc::setSelectedPath(CString path1){
	SelectedPath=path1;
}
//获取当前选中文件路径
CString CFaceEncryptDoc::getSelectedPath(){
	return SelectedPath;
}
//设置当前选中文件加密信息
void  CFaceEncryptDoc::setCurEncryInfo(CString info){
	CurrentEnCryInfo=info;
}
//获取当前选中文件加密信息
CString CFaceEncryptDoc::getCurEncryInfo(){
	return CurrentEnCryInfo;
}
//判断给定路经是否已经加密
BOOL CFaceEncryptDoc::IsEncrypt(CString path){
	 CString  CurPath;
	 int EncryptCount=EncryptedPath.GetSize();
	 for(int i=0;i<EncryptCount;i++){
		 if(EncryptedPath[i]==path)
			 return TRUE;
	 }
	 return FALSE;
	//return EncryptedPath.(path,(char *&)CurPath);
}
//获取加密键值对信息
CStringArray *CFaceEncryptDoc::GetEncryptInfo(){
	return &EncryptedPath;
}
