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
	  AfxMessageBox("���ĵ����캯��������ؼ�����Ϣ");
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
	//��ָ���ļ���ʼ������
	//ֱ��ɾ�����ã��ɿ����ÿո񸲸�ԭ�ļ�
	//CStaticAssistant::deleteFile("res/temp.znl",NULL);
	//this->Serialize()
// 	BOOL b=CStaticAssistant::LoadEncryptInfo("res/temp.znl",&EncryptedPath);
// 	if(!b)
// 	{   AfxMessageBox("������Ҫ�ļ�ʧ��,�����ԣ�");  return FALSE;}
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
		//AfxMessageBox("���л�");
	}
	else
	{
		// TODO: add loading code here
		//ar>>SelectedPath;
// 		BOOL b=CStaticAssistant::LoadEncryptInfo("res/��temp.znl",&EncryptMap);
//          ASSERT(b==true);
		//AfxMessageBox("���л�");
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
//���õ�ǰѡ���ļ�·��
void  CFaceEncryptDoc::setSelectedPath(CString path1){
	SelectedPath=path1;
}
//��ȡ��ǰѡ���ļ�·��
CString CFaceEncryptDoc::getSelectedPath(){
	return SelectedPath;
}
//���õ�ǰѡ���ļ�������Ϣ
void  CFaceEncryptDoc::setCurEncryInfo(CString info){
	CurrentEnCryInfo=info;
}
//��ȡ��ǰѡ���ļ�������Ϣ
CString CFaceEncryptDoc::getCurEncryInfo(){
	return CurrentEnCryInfo;
}
//�жϸ���·���Ƿ��Ѿ�����
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
//��ȡ���ܼ�ֵ����Ϣ
CStringArray *CFaceEncryptDoc::GetEncryptInfo(){
	return &EncryptedPath;
}
