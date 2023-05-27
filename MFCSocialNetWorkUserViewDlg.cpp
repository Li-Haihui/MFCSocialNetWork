// MFCSocialNetWorkUserViewDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkUserViewDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"


// CMFCSocialNetWorkUserViewDlg 对话框

IMPLEMENT_DYNAMIC(CMFCSocialNetWorkUserViewDlg, CDialogEx)

CMFCSocialNetWorkUserViewDlg::CMFCSocialNetWorkUserViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_DIALOG2, pParent)
{

}

CMFCSocialNetWorkUserViewDlg::~CMFCSocialNetWorkUserViewDlg()
{
}

BOOL CMFCSocialNetWorkUserViewDlg::OnInitDialog()
{
	// 调用父类的 OnInitDialog() 函数
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小
	m_UserListControl.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格
	m_UserListControl.SetExtendedStyle(m_UserListControl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_UserListControl.InsertColumn(0, _T("用户名"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_UserListControl.InsertColumn(1, _T("地址"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_UserListControl.InsertColumn(2, _T("电话"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_UserListControl.InsertColumn(3, _T("生日"), LVCFMT_CENTER, rect.Width() / 4, 3);

	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	for (int i = 0; i < userNum; i++) {
		m_UserListControl.InsertItem(i, LPCTSTR(CString(users[i]->getName().c_str())));
		m_UserListControl.SetItemText(i, 1, LPCTSTR(CString(users[i]->getAddress().c_str())));
		m_UserListControl.SetItemText(i, 2, LPCTSTR(CString(users[i]->getPhone().c_str())));
		m_UserListControl.SetItemText(i, 3, LPCTSTR(CString(users[i]->getBirthdate().c_str())));
	}

	m_UserBirthEdit.SetWindowTextW(_T("mm/dd:7/1"));
	return TRUE;
}

void CMFCSocialNetWorkUserViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_USER_LIST, m_UserListControl);
	DDX_Control(pDX, IDC_USER_NAME_EDIT, m_UserNameEdit);
	DDX_Control(pDX, IDC_USER_ADDR_EDIT, m_UserAddrEdit);
	DDX_Control(pDX, IDC_USER_PHONE_EDIT, m_UserPhoneEdit);
	DDX_Control(pDX, IDC_USER_BIRTH_EDIT, m_UserBirthEdit);
}


BEGIN_MESSAGE_MAP(CMFCSocialNetWorkUserViewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FLUSH_BUTTON, &CMFCSocialNetWorkUserViewDlg::OnBnClickedFlushButton)
	ON_BN_CLICKED(IDC_USER_REGIST_BUTTON, &CMFCSocialNetWorkUserViewDlg::OnBnClickedUserRegistButton)
	ON_BN_CLICKED(IDC_USER_DELE_BUTTON, &CMFCSocialNetWorkUserViewDlg::OnBnClickedUserDeleButton)
	ON_BN_CLICKED(IDC_USER_FIX_BUTTON, &CMFCSocialNetWorkUserViewDlg::OnBnClickedUserFixButton)
	ON_EN_SETFOCUS(IDC_USER_BIRTH_EDIT, &CMFCSocialNetWorkUserViewDlg::OnEnSetfocusUserBirthEdit)
END_MESSAGE_MAP()


// CMFCSocialNetWorkUserViewDlg 消息处理程序

void CMFCSocialNetWorkUserViewDlg::OnBnClickedFlushButton()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	int pListCount = m_UserListControl.GetItemCount();
	for (int i = 0; i < userNum; i++) {
		if (pListCount <= i) {
			m_UserListControl.InsertItem(i, LPCTSTR(CString(users[i]->getName().c_str())));
		}
		else {
			m_UserListControl.SetItemText(i, 0, LPCTSTR(CString(users[i]->getName().c_str())));
		}
		
		m_UserListControl.SetItemText(i, 1, LPCTSTR(CString(users[i]->getAddress().c_str())));
		m_UserListControl.SetItemText(i, 2, LPCTSTR(CString(users[i]->getPhone().c_str())));
		m_UserListControl.SetItemText(i, 3, LPCTSTR(CString(users[i]->getBirthdate().c_str())));
	}
	
	for (int i = userNum; i < pListCount; i++) {
		m_UserListControl.DeleteItem(i);
	}
}


void CMFCSocialNetWorkUserViewDlg::OnBnClickedUserRegistButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pNameString, pPhoneString, pAddrString, pBirthString;
	m_UserNameEdit.GetWindowText(pNameString);
	m_UserAddrEdit.GetWindowText(pAddrString);
	m_UserPhoneEdit.GetWindowText(pPhoneString);
	m_UserBirthEdit.GetWindowText(pBirthString);

	bool ret = SocialNetwork::getInstance().registerUser(W2A(pNameString), W2A(pAddrString),
		W2A(pPhoneString), W2A(pBirthString));
	if (ret) {
		MessageBox(TEXT("注册用户成功"));
	}
	else {
		MessageBox(TEXT("注册用户失败"));
	}
}


void CMFCSocialNetWorkUserViewDlg::OnBnClickedUserDeleButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pNameString, pPhoneString, pAddrString, pBirthString;
	m_UserNameEdit.GetWindowText(pNameString);
	m_UserAddrEdit.GetWindowText(pAddrString);
	m_UserPhoneEdit.GetWindowText(pPhoneString);
	m_UserBirthEdit.GetWindowText(pBirthString);

	User* pUser = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == string(W2A(pNameString))) {
			pUser = users[i];
		}
	}

	if (pUser) {
		SocialNetwork::getInstance().removeUser(pUser);
		MessageBox(TEXT("注销用户成功"));
	}
	else {
		MessageBox(TEXT("注销用户失败"));
	}
}


void CMFCSocialNetWorkUserViewDlg::OnBnClickedUserFixButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pNameString, pPhoneString, pAddrString, pBirthString;
	m_UserNameEdit.GetWindowText(pNameString);
	m_UserAddrEdit.GetWindowText(pAddrString);
	m_UserPhoneEdit.GetWindowText(pPhoneString);
	m_UserBirthEdit.GetWindowText(pBirthString);

	User* pUser = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == string(W2A(pNameString))) {
			pUser = users[i];
		}
	}

	if (pUser) {
		pUser->setName(W2A(pNameString));
		pUser->setAddress(W2A(pAddrString));
		pUser->setPhone(W2A(pPhoneString));
		pUser->setBirthdate(W2A(pBirthString));
		MessageBox(TEXT("修改用户成功"));
	}
	else {
		MessageBox(TEXT("修改用户失败"));
	}
}


void CMFCSocialNetWorkUserViewDlg::OnEnSetfocusUserBirthEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_UserBirthEdit.SetWindowText(_T(""));
}
