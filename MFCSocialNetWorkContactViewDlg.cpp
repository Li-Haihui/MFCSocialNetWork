// MFCSocialNetWorkContactViewDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkContactViewDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"


// CMFCSocialNetWorkContactViewDlg 对话框

IMPLEMENT_DYNAMIC(CMFCSocialNetWorkContactViewDlg, CDialogEx)

CMFCSocialNetWorkContactViewDlg::CMFCSocialNetWorkContactViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTACT_DIALOG, pParent)
{

}

CMFCSocialNetWorkContactViewDlg::~CMFCSocialNetWorkContactViewDlg()
{
}

BOOL CMFCSocialNetWorkContactViewDlg::OnInitDialog()
{
	// 调用父类的 OnInitDialog() 函数
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小
	m_ContactList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格
	m_ContactList.SetExtendedStyle(m_ContactList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ContactList.InsertColumn(0, _T("用户名"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_ContactList.InsertColumn(1, _T("联系人1"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_ContactList.InsertColumn(2, _T("联系人2"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_ContactList.InsertColumn(3, _T("联系人3"), LVCFMT_CENTER, rect.Width() / 4, 3);

	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	for (int i = 0; i < userNum; i++) {
		m_ContactList.InsertItem(i, LPCTSTR(CString(users[i]->getName().c_str())));
		vector<User*> contacts = users[i]->getContacts();
		for (int j = 0; j < contacts.size(); j++) {
			m_ContactList.SetItemText(i, j + 1, LPCTSTR(CString(contacts[j]->getName().c_str())));
		}
	}

	return TRUE;
}


void CMFCSocialNetWorkContactViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTACT_LIST, m_ContactList);
	DDX_Control(pDX, IDC_CONTACT_EDIT1, m_NameEdit);
	DDX_Control(pDX, IDC_CONTACT_EDIT2, m_ContactEdit);
}


BEGIN_MESSAGE_MAP(CMFCSocialNetWorkContactViewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_CONTACT_BUTTON, &CMFCSocialNetWorkContactViewDlg::OnBnClickedAddContactButton)
	ON_BN_CLICKED(IDC_FLUSH_BUTTON, &CMFCSocialNetWorkContactViewDlg::OnBnClickedFlushButton)
	ON_BN_CLICKED(IDC_DEL_CONTACT_BUTTON, &CMFCSocialNetWorkContactViewDlg::OnBnClickedDelContactButton)
END_MESSAGE_MAP()


// CMFCSocialNetWorkContactViewDlg 消息处理程序


void CMFCSocialNetWorkContactViewDlg::OnBnClickedAddContactButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	m_NameEdit.GetWindowText(m_NameString);
	m_ContactEdit.GetWindowText(m_ContactString);

	User* pUser = nullptr, *pContact = nullptr;
	bool ret = false;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	for (int i = 0; i < userNum; i++) {
		if (users[i]->getName() == string(W2A(m_NameString))) {
			pUser = users[i];
			continue;
		}

		if (users[i]->getName() == string(W2A(m_ContactString))) {
			pContact = users[i];
		}
	}


	if (pUser && pContact) {
		ret = pUser->addContact(pContact);
	}
	else {
		MessageBox(TEXT("添加联系人失败"));
	}

	if (ret) {
		MessageBox(TEXT("添加联系人成功"));
	}
}


void CMFCSocialNetWorkContactViewDlg::OnBnClickedFlushButton()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	for (int i = 0; i < userNum; i++) {
		m_ContactList.SetItemText(i, 0, LPCTSTR(CString(users[i]->getName().c_str())));
		//m_ContactList.InsertItem(i, LPCTSTR(CString(users[i]->getName().c_str())));
		vector<User*> contacts = users[i]->getContacts();
		for (int j = 0; j < contacts.size(); j++) {
			m_ContactList.SetItemText(i, j + 1, LPCTSTR(CString(contacts[j]->getName().c_str())));
		}
	}
}


void CMFCSocialNetWorkContactViewDlg::OnBnClickedDelContactButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	m_NameEdit.GetWindowText(m_NameString);
	m_ContactEdit.GetWindowText(m_ContactString);

	User* pUser = nullptr, * pContact = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	int userNum = users.size();
	for (int i = 0; i < userNum; i++) {
		if (users[i]->getName() == string(W2A(m_NameString))) {
			pUser = users[i];
			break;
		}
	}

	vector<User*> contacts = pUser->getContacts();
	for (int i = 0; i < contacts.size(); i++) {
		if (contacts[i]->getName() == string(W2A(m_ContactString))) {
			pContact = contacts[i];
		}
	}

	if (pUser && pContact) {
		pUser->removeContact(pContact);
	}
	else {
		MessageBox(TEXT("删除联系人失败"));
	}

	MessageBox(TEXT("删除联系人成功"));

}
