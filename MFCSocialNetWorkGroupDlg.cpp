// MFCSocialNetWorkGroupDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkGroupDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"


// CMFCSocialNetWorkGroupDlg 对话框

IMPLEMENT_DYNAMIC(CMFCSocialNetWorkGroupDlg, CDialogEx)

CMFCSocialNetWorkGroupDlg::CMFCSocialNetWorkGroupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GROUP_DIALOG, pParent)
{

}

CMFCSocialNetWorkGroupDlg::~CMFCSocialNetWorkGroupDlg()
{
}

BOOL CMFCSocialNetWorkGroupDlg::OnInitDialog()
{
	// 调用父类的 OnInitDialog() 函数
	CDialogEx::OnInitDialog();

	vector<User*> users = SocialNetwork::getInstance().getUsers();
	for (int i = 0; i < users.size(); i++) {
		m_JoinUserComboBox.AddString(LPCTSTR(CString(users[i]->getName().c_str())));
		m_LeaveUserComboBox.AddString(LPCTSTR(CString(users[i]->getName().c_str())));
		m_SendUserComboBox.AddString(LPCTSTR(CString(users[i]->getName().c_str())));
		m_ViewUserComboBox.AddString(LPCTSTR(CString(users[i]->getName().c_str())));
		m_MessageUserComboBox.AddString(LPCTSTR(CString(users[i]->getName().c_str())));
		vector<User*> contacts = users[i]->getContacts();
		for (int j = 0; j < contacts.size(); j++) {
			m_JoinContactComboBox.AddString(LPCTSTR(CString(contacts[j]->getName().c_str())));
		}
		vector<User*> groups = users[i]->getGroups();
		for (int j = 0; j < groups.size(); j++) {
			m_LeaveGroupComboBox.AddString(LPCTSTR(CString(groups[j]->getName().c_str())));
			m_SendGroupComboBox.AddString(LPCTSTR(CString(groups[j]->getName().c_str())));
			m_MessageGroupComboBox.AddString(LPCTSTR(CString(groups[j]->getName().c_str())));
		}

	}
	m_JoinUserComboBox.SetCurSel(0);
	m_LeaveUserComboBox.SetCurSel(0);
	m_SendUserComboBox.SetCurSel(0);
	m_ViewUserComboBox.SetCurSel(0);
	m_MessageUserComboBox.SetCurSel(0);
	m_JoinContactComboBox.SetCurSel(0);
	m_LeaveGroupComboBox.SetCurSel(0);
	m_SendGroupComboBox.SetCurSel(0);
	m_MessageGroupComboBox.SetCurSel(0);

	CRect rect;
	// 获取编程语言列表视图控件的位置和大小
	m_ViewGroupList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格
	m_ViewGroupList.SetExtendedStyle(m_ViewGroupList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ViewGroupList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_ViewGroupList.InsertColumn(1, _T("群组"), LVCFMT_CENTER, rect.Width() / 4 * 3, 0);

	CRect rect2;
	// 获取编程语言列表视图控件的位置和大小
	m_ViewMessageList.GetClientRect(&rect2);
	// 为列表视图控件添加全行选中和栅格风格
	m_ViewMessageList.SetExtendedStyle(m_ViewGroupList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ViewMessageList.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_ViewMessageList.InsertColumn(1, _T("群组消息"), LVCFMT_CENTER, rect.Width() / 5 * 4, 0);


	return TRUE;
}

void CMFCSocialNetWorkGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JOIN_USER_COMBO, m_JoinUserComboBox);
	DDX_Control(pDX, IDC_JION_CONTACT_COMBO, m_JoinContactComboBox);
	DDX_Control(pDX, IDC_LEAVE_USER_COMBO, m_LeaveUserComboBox);
	DDX_Control(pDX, IDC_LEAVE_GROUP_COMBO, m_LeaveGroupComboBox);
	DDX_Control(pDX, IDC_SEND_USER_COMBO, m_SendUserComboBox);
	DDX_Control(pDX, IDC_SEND_GROUP_COMBO, m_SendGroupComboBox);
	DDX_Control(pDX, IDC_SEND_MESSAGE_EDIT, m_SendMessageEdit);
	DDX_Control(pDX, IDC_VIEW_USER_COMBO, m_ViewUserComboBox);
	DDX_Control(pDX, IDC_VIEW_GROUP_LIST, m_ViewGroupList);
	DDX_Control(pDX, IDC_MESSAGE_USER_COMBO, m_MessageUserComboBox);
	DDX_Control(pDX, IDC_MESSAGE_GROUP_COMBO, m_MessageGroupComboBox);
	DDX_Control(pDX, IDC_VIEW_MESSAGE_LIST, m_ViewMessageList);
}


BEGIN_MESSAGE_MAP(CMFCSocialNetWorkGroupDlg, CDialogEx)
	ON_BN_CLICKED(IDC_JOIN_BUTTON, &CMFCSocialNetWorkGroupDlg::OnBnClickedJoinButton)
	ON_CBN_SELCHANGE(IDC_JOIN_USER_COMBO, &CMFCSocialNetWorkGroupDlg::OnCbnSelchangeJoinUserCombo)
	ON_CBN_SELCHANGE(IDC_JION_CONTACT_COMBO, &CMFCSocialNetWorkGroupDlg::OnCbnSelchangeJionContactCombo)
	ON_CBN_SELCHANGE(IDC_LEAVE_USER_COMBO, &CMFCSocialNetWorkGroupDlg::OnCbnSelchangeLeaveUserCombo)
END_MESSAGE_MAP()


// CMFCSocialNetWorkGroupDlg 消息处理程序


void CMFCSocialNetWorkGroupDlg::OnBnClickedJoinButton()
{
	// TODO: 在此添加控件通知处理程序代码
	int userIndex = m_JoinUserComboBox.GetCurSel();
	int contactIndex = m_JoinContactComboBox.GetCurSel();
	User* pUser = nullptr, * pContact = nullptr;
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	pUser = users[userIndex];
	vector<User*> contacts = pUser->getContacts();
	pContact = contacts[contactIndex];
	pUser->joinGroup(pContact);
	MessageBox(TEXT("加入群组成功"));
}


void CMFCSocialNetWorkGroupDlg::OnCbnSelchangeJoinUserCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_JoinContactComboBox.ResetContent();
	// 获取当前选中的列表项的索引
	int index = m_JoinUserComboBox.GetCurSel();
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	User* pUser = users[index];
	vector<User*> contacts = pUser->getContacts();
	for (int j = 0; j < contacts.size(); j++) {
		m_JoinContactComboBox.AddString(LPCTSTR(CString(contacts[j]->getName().c_str())));
	}
	m_JoinContactComboBox.SetCurSel(0);
}


void CMFCSocialNetWorkGroupDlg::OnCbnSelchangeJionContactCombo()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCSocialNetWorkGroupDlg::OnCbnSelchangeLeaveUserCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LeaveGroupComboBox.ResetContent();
	int index = m_LeaveUserComboBox.GetCurSel();
	vector<User*> users = SocialNetwork::getInstance().getUsers();
	User* pUser = users[index];

}
