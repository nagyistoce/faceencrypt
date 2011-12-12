// DriveTreeView.cpp : implementation of the CDriveView class
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/****************包含头文件*****************/
#include "DriveView.h"
#include "../Resource.h"
// Image indexes
#define ILI_HARD_DISK       0
#define ILI_FLOPPY          1
#define ILI_CD_ROM          2
#define ILI_NET_DRIVE       3
#define ILI_CLOSED_FOLDER   4
#define ILI_OPEN_FOLDER     5

/////////////////////////////////////////////////////////////////////////////
// CDriveView

IMPLEMENT_DYNCREATE(CDriveView, CTreeView)

BEGIN_MESSAGE_MAP(CDriveView, CTreeView)
	//{{AFX_MSG_MAP(CDriveView)
	ON_NOTIFY_REFLECT(NM_RCLICK,OnNMClick)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelectionChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriveView construction/destruction

CDriveView::CDriveView()
{
}

CDriveView::~CDriveView()
{
}

/********************************************************************************************
*函数: OnNMClick

*作用: 通过类向导添加的 NM_RCLICK 消息的响应函数,响应鼠标右键单击消息

*参数: pNMHDR                                       -- VS2010 添加，发送此通告的 Tree 控件的父句柄
       pResult                                      -- VS2010 添加，标记消息的已处理状态，不用修改

*返回值: 无
********************************************************************************************/

void CDriveView::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
 // TODO: Add your control notification handler code here
 /************************** 通过识别控件中鼠标位置获取当前选择项 
 /CTreeCtrl *pTreeCtrl = GetTreeCtrl();
 CPoint ptCurSel(0,0);
 TVHITTESTINFO HitTestInfo;
 // 通过鼠标在客户区中的位置
 GetCursorPos(&ptCurSel);
 pTreeCtrl->ScreenToClient(&ptCurSel);  
 // 获取当前选择的是哪一项
 HitTestInfo.pt = ptCurSel;  
 HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);
 
 if(hSelect != NULL)
 {
  CString strItem = pTreeCtrl->GetItemText(hSelect);
  ::AfxMessageBox( strItem); 
 }
 // 设置该项为选中状态
 pTreeCtrl->SelectItem(hSelect);
//以下方法获取的是上一次处于选中状态的项 ******
 //首先将点击的对象选中 
 /*
 CTreeCtrl* pTreeCtrl = this;
 HTREEITEM hSelect = pTreeCtrl->GetSelectedItem();
 HTREEITEM hLight = pTreeCtrl->GetDropHilightItem();
 if((hLight != NULL) && (hSelect != hLight)) ;
  //hSelect = hLight;
 if(hSelect   ==   NULL)
  return;
 pTreeCtrl->SelectItem(hSelect);

 //编辑当前选中对象名称
 pTreeCtrl->EditLabel(hSelect);
 if( NULL != hSelect )
 {
  CString strItem = pTreeCtrl->GetItemText(hSelect);
  
  if(strItem == _T("控制器"))
  {
   pTreeCtrl->SetItemText(hSelect, _T("改变了控制器名称"));
  }
  
  pTreeCtrl->SetItemText(hSelect, strItem);
  ::AfxMessageBox( strItem);  
 }
END ********************************/
	AfxMessageBox("On right button clicked!!");
}
/************************
return the m_selectPath
*************************/
CString CDriveView::GetSelectPath()
{
	return m_selectPath;
     
}
BOOL CDriveView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CTreeView::PreCreateWindow (cs))
		return FALSE;

    cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |
        TVS_SHOWSELALWAYS;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDriveView drawing

void CDriveView::OnDraw(CDC* pDC)
{
	CFaceEncryptDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CDriveView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	//
	// Initialize the image list.
	//
    m_ilDrives.Create (IDB_DRIVES, 16, 1, RGB (255, 0, 255));
    GetTreeCtrl ().SetImageList (&m_ilDrives, TVSIL_NORMAL);

	//
	// Populate the tree view with drive items.
	//
    AddDrives ();

	//
	// Show the folders on the current drive.
	//
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory (sizeof (szPath) / sizeof (TCHAR), szPath);
	CString strPath = szPath;
	strPath = strPath.Left (3);
	HTREEITEM hItem = GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT);
	while (hItem != NULL) {
		if (GetTreeCtrl ().GetItemText (hItem) == strPath)
			break;
		hItem = GetTreeCtrl ().GetNextSiblingItem (hItem);
	}

	if (hItem != NULL) {
		GetTreeCtrl ().Expand (hItem, TVE_EXPAND);
		GetTreeCtrl ().Select (hItem, TVGN_CARET);
	}

	//
	// Initialize the list view.
	//
	strPath = GetPathFromItem (GetTreeCtrl ().GetSelectedItem ());
    GetDocument ()->UpdateAllViews (this, 0x5A, (CObject*) (LPCTSTR) strPath);
}

/////////////////////////////////////////////////////////////////////////////
// CDriveView diagnostics

#ifdef _DEBUG
void CDriveView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDriveView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFaceEncryptDoc* CDriveView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceEncryptDoc)));
	return (CFaceEncryptDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDriveView message handlers

int CDriveView::AddDrives()
{
    int nPos = 0;
    int nDrivesAdded = 0;
    CString string = _T ("?:\\");

    DWORD dwDriveList = ::GetLogicalDrives ();

    while (dwDriveList) {
        if (dwDriveList & 1) {
            string.SetAt (0, _T ('A') + nPos);
            if (AddDriveItem (string))
                nDrivesAdded++;
        }
        dwDriveList >>= 1;
        nPos++;
    }
    return nDrivesAdded;
}

BOOL CDriveView::AddDriveItem(LPCTSTR pszDrive)
{
    CString string;
    HTREEITEM hItem;

    UINT nType = ::GetDriveType (pszDrive);

    switch (nType) {

    case DRIVE_REMOVABLE:
        hItem = GetTreeCtrl ().InsertItem (pszDrive, ILI_FLOPPY,
            ILI_FLOPPY);
        GetTreeCtrl ().InsertItem (_T (""), ILI_CLOSED_FOLDER,
            ILI_CLOSED_FOLDER, hItem);
        break;

    case DRIVE_FIXED:
    case DRIVE_RAMDISK:
        hItem = GetTreeCtrl ().InsertItem (pszDrive, ILI_HARD_DISK,
            ILI_HARD_DISK);
        SetButtonState (hItem, pszDrive);
        break;

    case DRIVE_REMOTE:
        hItem = GetTreeCtrl ().InsertItem (pszDrive, ILI_NET_DRIVE,
            ILI_NET_DRIVE);
        SetButtonState (hItem, pszDrive);
        break;

    case DRIVE_CDROM:
        hItem = GetTreeCtrl ().InsertItem (pszDrive, ILI_CD_ROM,
            ILI_CD_ROM);
        GetTreeCtrl ().InsertItem (_T (""), ILI_CLOSED_FOLDER,
            ILI_CLOSED_FOLDER, hItem);
        break;

    default:
        return FALSE;
    }
    return TRUE;
}
/********************
         20110315WWW::在每个当前问路
		 径(非空）的子目录上添加一个空文件夹以便出现加号
********************/
BOOL CDriveView::SetButtonState(HTREEITEM hItem, LPCTSTR pszPath)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;
    BOOL bResult = FALSE;

    CString strPath = pszPath;
    if (strPath.Right (1) != _T ("\\"))
        strPath += _T ("\\");
    strPath += _T ("*.*");

    if ((hFind = ::FindFirstFile (strPath, &fd)) == INVALID_HANDLE_VALUE)
        return bResult;

    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            CString strComp = (LPCTSTR) &fd.cFileName;
            if ((strComp != _T (".")) && (strComp != _T (".."))) {
                GetTreeCtrl ().InsertItem (_T (""), ILI_CLOSED_FOLDER,
                    ILI_CLOSED_FOLDER, hItem);
                bResult = TRUE;
                break;
            }
        }
    } while (::FindNextFile (hFind, &fd));
    ::FindClose (hFind);
    return bResult;
}

void CDriveView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    HTREEITEM hItem = pNMTreeView->itemNew.hItem;
    CString string = GetPathFromItem (hItem);
    
    *pResult = FALSE;

    if (pNMTreeView->action == TVE_EXPAND) {
        DeleteFirstChild (hItem);
        if (AddDirectories (hItem, string) == 0)
            *pResult = TRUE;
    }
    else { // pNMTreeView->action == TVE_COLLAPSE
        DeleteAllChildren (hItem);
        if (GetTreeCtrl ().GetParentItem (hItem) == NULL)
            GetTreeCtrl ().InsertItem (_T (""),ILI_CLOSED_FOLDER,
                ILI_CLOSED_FOLDER, hItem);
        else
  	      SetButtonState (hItem, string);
		}
	//AfxMessageBox("CDriveView::OnItemExpanding");
}

CString CDriveView::GetPathFromItem(HTREEITEM hItem)
{
    CString strResult = GetTreeCtrl ().GetItemText (hItem);

    HTREEITEM hParent;
    while ((hParent = GetTreeCtrl ().GetParentItem (hItem)) != NULL) {
        CString string = GetTreeCtrl ().GetItemText (hParent);
        if (string.Right (1) != _T ("\\"))
            string += _T ("\\");
        strResult = string + strResult;
        hItem = hParent;
    }
    return strResult;
}

void CDriveView::DeleteFirstChild(HTREEITEM hItem)
{
    HTREEITEM hChildItem;
    if ((hChildItem = GetTreeCtrl ().GetChildItem (hItem)) != NULL)
        GetTreeCtrl ().DeleteItem (hChildItem);
}

void CDriveView::DeleteAllChildren(HTREEITEM hItem)
{
    HTREEITEM hChildItem;
    if ((hChildItem = GetTreeCtrl ().GetChildItem (hItem)) == NULL)
        return;

    do {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChildItem);
        GetTreeCtrl ().DeleteItem (hChildItem);
        hChildItem = hNextItem;
    } while (hChildItem != NULL);
}

int CDriveView::AddDirectories(HTREEITEM hItem, LPCTSTR pszPath)
{
   //AfxMessageBox("before1");
    HANDLE hFind;
    WIN32_FIND_DATA fd;
    HTREEITEM hNewItem;

    int nCount = 0;

    CString strPath = pszPath;
    if (strPath.Right (1) != _T ("\\"))
        strPath += _T ("\\");
    strPath += _T ("*.*");

    if ((hFind = ::FindFirstFile (strPath, &fd)) == INVALID_HANDLE_VALUE) {
        if (GetTreeCtrl ().GetParentItem (hItem) == NULL)
            GetTreeCtrl ().InsertItem (_T (""), ILI_CLOSED_FOLDER,
                ILI_CLOSED_FOLDER, hItem);
        return 0;
    }

    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            CString strComp = (LPCTSTR) &fd.cFileName;
		//	. 当前目录   ..上级目录
            if ((strComp != _T (".")) && (strComp != _T (".."))) {
                hNewItem =
                    GetTreeCtrl ().InsertItem ((LPCTSTR) &fd.cFileName,
                    ILI_CLOSED_FOLDER, ILI_OPEN_FOLDER, hItem);
                CString strNewPath = pszPath;
                if (strNewPath.Right (1) != _T ("\\"))
                    strNewPath += _T ("\\");

                strNewPath += (LPCTSTR) &fd.cFileName;
                SetButtonState (hNewItem, strNewPath);
                nCount++;
            }
        }
    } while (::FindNextFile (hFind, &fd));
     //   
    ::FindClose (hFind);
    return nCount;
}

void CDriveView::OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{   //获取文件句柄
	CFaceEncryptDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pNMHDR;
    CString strPath = GetPathFromItem (pNMTreeView->itemNew.hItem);
	//获取选择路径并且更新到文档中
	      m_selectPath=strPath;
	//AfxMessageBox(m_selectPath);
          pDoc->setSelectedPath(m_selectPath);
    GetDocument ()->UpdateAllViews (this, 0x5A, (CObject*) (LPCTSTR) strPath);
	*pResult = 0;
}
