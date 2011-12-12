// EncryptFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../FaceEncrypt.h"
#include "EncryptFileDlg.h"
#include "EncrpInfoDlg.h"
#include "../StaticAssistant.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CFaceEncryptApp theApp;  //定义全局变量
/////////////////////////////////////////////////////////////////////////////
// CEncryptFileDlg dialog


CEncryptFileDlg::CEncryptFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncryptFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncryptFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_pwd = _T("");
	m_listInfo = _T("");
	m_repwd = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CEncryptFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncryptFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_INFO_LIST, m_listCtrl);
	DDX_Text(pDX, IDC_PSW, m_pwd);
	DDX_LBString(pDX, IDC_INFO_LIST, m_listInfo);
	DDX_Text(pDX, IDC_REPSW, m_repwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEncryptFileDlg, CDialog)
	//{{AFX_MSG_MAP(CEncryptFileDlg)
	ON_BN_CLICKED(ID_INTRODUCE, OnIntroduce)
	ON_BN_CLICKED(ID_CLEAR, OnClear)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_INFOMESSAGE,OnViewMess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncryptFileDlg message handlers

void CEncryptFileDlg::OnIntroduce() 
{
	// TODO: Add your control notification handler code here
	
}

void CEncryptFileDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_pwd = "";
	m_repwd = "";
	UpdateData(FALSE);
}

void CEncryptFileDlg::OnOK() 
{
	// TODO: Add extra validation here
	AfxMessageBox("void CEncryptFileDlg::OnOK()");
	BOOL isEncypt=CStaticAssistant::GetEncryptFlag();
	if(isEncypt==TRUE)
		Encrypt();
	else
		Uncrypt();
	CDialog::OnOK();
}

void CEncryptFileDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
/***********************************************
/*  FUNC:初始化对话框
/*
/*
************************************************/
BOOL CEncryptFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// IDM_ABOUTBOX must be in the system command range.
// 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
// 	ASSERT(IDM_ABOUTBOX < 0xF000);
// 	
// 	CMenu* pSysMenu = GetSystemMenu(FALSE);
// 	if (pSysMenu != NULL)
// 	{
// 		CString strAboutMenu;
// 		strAboutMenu.LoadString(IDS_ABOUTBOX);
// 		if (!strAboutMenu.IsEmpty())
// 		{
// 			pSysMenu->AppendMenu(MF_SEPARATOR);
// 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
// 		}
// 	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	//RECT rc;
	//m_staCtrl.GetWindowRect(&rc);
	RECT rcList;
	m_listCtrl.GetWindowRect(&rcList);
	//m_listCtrl.Set	
	//SetDlgItemText(IDC_FILE_R,"1");
	//	GetDlgItem(IDC_ENCRYFILE_E)->EnableWindow(0);
	//获取操作类型和路径名
    m_fileOrDir=1;

    m_encryFile=CStaticAssistant::GetCurrentPath();
	AfxMessageBox(m_encryFile);

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
/********************************************************************
/* If you add a minimize button to your dialog, you will need the code below
/*  to draw the icon.  For MFC applications using the document/view model,
/*  this is automatically done for you by the framework.
***********************************************************************/
void CEncryptFileDlg::OnPaint() 
{
	if (IsIconic()){
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}else{
		CDialog::OnPaint();
	}
}
/********************************************************************
/* The system calls this to obtain the cursor to display while the user drags
/*  the minimized window.
********************************************************************/
  HCURSOR CEncryptFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/***********************************************
/*  FUNC:显示消息,接下来四个函数
/*
/*
************************************************/
LRESULT CEncryptFileDlg::OnViewMess(WPARAM wParam,LPARAM lParam)
 {
	  LPTSTR info = (LPTSTR)wParam;
	  int flag = (int)lParam;
	  if(flag == 1)
	  {
		  MessageBox(info,"提示",MB_OK|MB_ICONINFORMATION);
	  }
	  else if(flag == 2)
	  {
		  MessageBox(info,"错误",MB_OK|MB_ICONERROR);
	  }
	return 0L;
}
void CEncryptFileDlg::Mess(CString info,CString title,DWORD flag)
{
	MessageBox(info,title,flag);
}
void CEncryptFileDlg::Info(CString info)
{
	m_listCtrl.AddString(info + "\n");
}
void PrintInfo(CString info,int errMod,CListBox *listCtrl)
{
	if(listCtrl)
	{
		int nCount = listCtrl->GetCount();
		if(errMod == 1 || errMod == 2){
			listCtrl->InsertString(nCount,info+"\n");
		}else{
			listCtrl->InsertString(0,info+"\n");
		}
		listCtrl->SetCurSel(nCount);
		if(errMod == 3){
			::SendMessage(theApp.GetMainWnd()->GetSafeHwnd(),
				WM_INFOMESSAGE,(WPARAM)(LPCSTR)info,2);
		}
		//listCtrl->SetScrollPos(2,nCount);
	}
}
/***********************************************
/*  FUNC:加解密控制函数
/*
/*
************************************************/
UINT Encry(LPVOID lp)
{
	CryParam crlp;
	crlp.Copy((CryParam*)lp);
 	while(crlp.dlg->m_flag == 0)
 	{
 		Sleep(500);
 	}
	//CRWEncry cry;
	DesEncrypt cry;
	crlp.listCtrl->ResetContent();
	cry.SetPrintInfo(crlp.pinfo,crlp.listCtrl);
	DWORD dwRetval = 0;
	if(crlp.fileOrDir == 1)
	{
		if(!crlp.bEncry)
		{
			dwRetval = cry.UncryDir(crlp.strFileName,crlp.strPwd);			
		}
		else
		{
			dwRetval = cry.EncryDir(crlp.strFileName,crlp.strPwd);
		}
	}
	else
	{
		if(!crlp.bEncry)
		{
			dwRetval = cry.UncryFile(crlp.strFileName,crlp.strPwd);			
		}
		else
		{
			dwRetval = cry.EncryFile(crlp.strFileName,crlp.strPwd);
		}		
	}
 	crlp.dlg->m_flag = 3;
 	Sleep(300);
	TCHAR	tcInfo[512] = {0};
	if(dwRetval==FALSE)
	{
		if(!crlp.bEncry)
		{
			sprintf(tcInfo,"解密%s[%s]失败!",crlp.strInfo,crlp.strFileName);
		}
		else
		{
			sprintf(tcInfo,"加密%s[%s]失败!",crlp.strInfo,crlp.strFileName);
		}
		//::MessageBox(NULL,tcInfo,"错误",MB_OK|MB_ICONERROR);
		crlp.dlgThis->Mess(tcInfo,"错误",MB_OK|MB_ICONERROR);
		return 0L;
	}
	if(!crlp.bEncry)
	{
		sprintf(tcInfo,"%s[%s]解密成功!",crlp.strInfo,crlp.strFileName);
		//把解密成功的文件夹名称从保存加密路径的文件中删除
		CStaticAssistant::DeleteUncryptInfo(crlp.strFileName,"res/temp.znl");
	}
	else
	{
		sprintf(tcInfo,"%s[%s]加密成功!",crlp.strInfo,crlp.strFileName);
		//把加密成功的文件夹名称添加到保存加密路径的文件中
		CStaticAssistant::StoreEncryptInfo(crlp.strFileName,"res/temp.znl");
	}
	crlp.dlgThis->Mess(tcInfo,"提示",MB_OK|MB_ICONINFORMATION);
	return 0L;
}
void CEncryptFileDlg::Encrypt() 
{
	UpdateData(TRUE);
	m_encryFile.TrimLeft();
	m_encryFile.TrimRight();
	m_pwd.TrimLeft();
	m_pwd.TrimRight();
	m_repwd.TrimLeft();
	m_repwd.TrimRight();
	TCHAR	cmInfo[100] = {0};
	TCHAR	tcInfo[512] = {0};
	if(m_fileOrDir == 1)
	{
		sprintf(cmInfo,"文件夹");
	}
	else
	{
		sprintf(cmInfo,"文件");
	}
	if(m_encryFile == "")
	{
		sprintf(tcInfo,"加密%s路径不能为空!",cmInfo);
		MessageBox(tcInfo,"错误",MB_OK|MB_ICONERROR);
		return;
	}
	if(m_pwd != m_repwd)
	{
		MessageBox("两次输入密码不一样,请重新输入!","错误",MB_OK|MB_ICONERROR);
		return;
	}
	if(m_pwd == "")
	{
		UpdateData(FALSE);
		MessageBox("密码不能为空(空格),请重新输入!","错误",MB_OK|MB_ICONERROR);
		return;
	}
	sprintf(tcInfo,"确定对%s进行加密吗!",cmInfo);
	if(MessageBox(tcInfo,"系统提示",MB_YESNO|MB_ICONINFORMATION|MB_DEFBUTTON2) == IDNO)
	{
		return;
	}
	CEncrpInfoDlg dlg;
	dlg.m_flag = 0;
	sprintf(tcInfo,"正在加密%s，请稍等...",cmInfo);
	dlg.SetInfo(tcInfo);
	CryParam crLp;
	crLp.dlg = &dlg;
	crLp.listCtrl = &m_listCtrl;
	crLp.pinfo = &PrintInfo;
	crLp.strFileName = m_encryFile;
	crLp.strInfo = cmInfo;
	crLp.strPwd = m_pwd;
	crLp.fileOrDir = m_fileOrDir;
	crLp.bEncry = true;
	crLp.dlgThis = this;
	CWinThread* thr = AfxBeginThread(Encry,&crLp);
	dlg.DoModal();
}

void CEncryptFileDlg::Uncrypt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_encryFile.TrimLeft();
	m_encryFile.TrimRight();
	m_pwd.TrimLeft();
	m_pwd.TrimRight();
	m_repwd.TrimLeft();
	m_repwd.TrimRight();
	TCHAR	cmInfo[100] = {0};
	TCHAR	tcInfo[512] = {0};
	if(m_fileOrDir == 1)
	{
		sprintf(cmInfo,"文件夹");
	}
	else
	{
		sprintf(cmInfo,"文件");
	}
	if(m_encryFile == "")
	{
		sprintf(tcInfo,"解密%s路径不能为空!",cmInfo);
		MessageBox(tcInfo,"错误",MB_OK|MB_ICONERROR);
		return;
	}
	if(m_pwd == "")
	{
		UpdateData(FALSE);
		MessageBox("密码不能为空(空格),请重新输入!","错误",MB_OK|MB_ICONERROR);
		return;
	}
	sprintf(tcInfo,"确定对%s进行解密吗!",cmInfo);
	if(MessageBox(tcInfo,"系统提示",MB_YESNO|MB_ICONINFORMATION|MB_DEFBUTTON2) == IDNO)
	{
		return;
	}
	CEncrpInfoDlg dlg;
	dlg.m_flag = 0;
	sprintf(tcInfo,"正在解密%s，请稍等...",cmInfo);
	dlg.SetInfo(tcInfo);
	CryParam crLp;
	crLp.dlg = &dlg;
	crLp.listCtrl = &m_listCtrl;
	crLp.pinfo = &PrintInfo;
    crLp.strFileName = m_encryFile;
	/////////////crLp.strFileName = m_encryFile;
	crLp.strInfo = cmInfo;
	crLp.strPwd = m_pwd;
	crLp.fileOrDir = m_fileOrDir;
	crLp.bEncry = false;
	crLp.dlgThis = this;
	CWinThread* thr = AfxBeginThread(Encry,&crLp);
	dlg.DoModal();
}