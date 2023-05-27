// MFCSocialNetWorkMessageDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkMessageDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"


// CMFCSocialNetWorkMessageDlg 对话框

IMPLEMENT_DYNAMIC(CMFCSocialNetWorkMessageDlg, CDialogEx)

CMFCSocialNetWorkMessageDlg::CMFCSocialNetWorkMessageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESSAGE_DIALOG, pParent)
{

}

CMFCSocialNetWorkMessageDlg::~CMFCSocialNetWorkMessageDlg()
{
}

BOOL CMFCSocialNetWorkMessageDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	CRect rect2;
	// 获取编程语言列表视图控件的位置和大小
	m_MessageList.GetClientRect(&rect2);
	// 为列表视图控件添加全行选中和栅格风格
	m_MessageList.SetExtendedStyle(m_MessageList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_MessageList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect2.Width() / 4, 0);
	m_MessageList.InsertColumn(1, _T("消息"), LVCFMT_CENTER, rect2.Width() / 4 * 3, 1);

	return TRUE;
}


void CMFCSocialNetWorkMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTACT_LIST, m_ContactList);
	DDX_Control(pDX, IDC_USER_EDIT, m_UserEdit);
	DDX_Control(pDX, IDC_CONTACT_EDIT, m_ContactEdit);
	DDX_Control(pDX, IDC_MESSAGE_EDIT, m_MessageEdit);
	DDX_Control(pDX, IDC_MESSAGE_USER_EDIT, m_MessageUserEdit);
	DDX_Control(pDX, IDC_MESSAGE_CONTACT_EDIT, m_MessageContactEdit);
	DDX_Control(pDX, IDC_MESSAGE_LIST, m_MessageList);
	DDX_Control(pDX, IDC_MESSAGEID_EDIT, m_MessageIDEdit);
}


BEGIN_MESSAGE_MAP(CMFCSocialNetWorkMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SENDMESSAGE_BUTTON, &CMFCSocialNetWorkMessageDlg::OnBnClickedSendmessageButton)
	ON_BN_CLICKED(IDC_FLUSH_BUTTON, &CMFCSocialNetWorkMessageDlg::OnBnClickedFlushButton)
	ON_BN_CLICKED(IDC_DELEMESSAGE_BUTTON, &CMFCSocialNetWorkMessageDlg::OnBnClickedDelemessageButton)
END_MESSAGE_MAP()


// CMFCSocialNetWorkMessageDlg 消息处理程序



void CMFCSocialNetWorkMessageDlg::OnBnClickedSendmessageButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pUserString, pContactString, pMessageString;
	m_UserEdit.GetWindowText(pUserString);
	m_ContactEdit.GetWindowText(pContactString);
	m_MessageEdit.GetWindowText(pMessageString);

	User* pUser = nullptr, *pContact = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == string(W2A(pUserString))) {
			pUser = users[i];
			break;
		}
	}

	int contactNum = pUser ? pUser->getContacts().size() : 0;
	for (int i = 0; pUser && (i < contactNum); i++) {
		if ((pUser->getContacts())[i]->getName() == string(W2A(pContactString))) {
			pContact = (pUser->getContacts())[i];
			break;
		}
	}

	if (pUser && pContact) {
		SocialNetwork::getInstance().sendMessage(pContact, W2A(pMessageString));
		MessageBox(TEXT("发送消息成功"));
	}
	else {
		MessageBox(TEXT("发送消息失败"));
	}
}


void CMFCSocialNetWorkMessageDlg::OnBnClickedFlushButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pUserString, pContactString;
	m_MessageUserEdit.GetWindowText(pUserString);
	m_MessageContactEdit.GetWindowText(pContactString);

	User* pUser = nullptr, * pContact = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == string(W2A(pUserString))) {
			pUser = users[i];
			break;
		}
	}

	int contactNum = pUser ? pUser->getContacts().size() : 0;
	for (int i = 0; pUser && (i < contactNum); i++) {
		if ((pUser->getContacts())[i]->getName() == string(W2A(pContactString))) {
			pContact = (pUser->getContacts())[i];
			break;
		}
	}

	if (pUser && pContact) {
		int messageNum = pContact->getMessages().size();
		int messageListNum = m_MessageList.GetItemCount();
		for (int i = 0; i < messageNum; i++) {
			CString indexString;
			indexString.Format(_T("%d"), i + 1);
			if (messageListNum <= i) {
				m_MessageList.InsertItem(i, LPCTSTR(indexString));
			}
			else {
				m_MessageList.SetItemText(i, 0, LPCTSTR(indexString));
			}
			m_MessageList.SetItemText(i, 1, LPCTSTR(CString((pContact->getMessages())[i].c_str())));
		}

		for (int i = messageNum; i < messageListNum; i++) {
			m_MessageList.DeleteItem(i);
		}
	}


}


void CMFCSocialNetWorkMessageDlg::OnBnClickedDelemessageButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString pUserString, pContactString;
	m_MessageUserEdit.GetWindowText(pUserString);
	m_MessageContactEdit.GetWindowText(pContactString);

	User* pUser = nullptr, * pContact = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		if (users[i]->getName() == string(W2A(pUserString))) {
			pUser = users[i];
			break;
		}
	}

	int contactNum = pUser ? pUser->getContacts().size() : 0;
	for (int i = 0; pUser && (i < contactNum); i++) {
		if ((pUser->getContacts())[i]->getName() == string(W2A(pContactString))) {
			pContact = (pUser->getContacts())[i];
			break;
		}
	}

	if (pUser && pContact) {
		CString messageIndex;
		m_MessageIDEdit.GetWindowText(messageIndex);
		int index = _ttoi(messageIndex);
		pContact->removeMessage(index);
		MessageBox(TEXT("删除消息成功"));
	}
	else {
		MessageBox(TEXT("删除消息失败"));
	}
}
