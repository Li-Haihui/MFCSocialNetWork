// MFCSocialNetWorkUserInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkUserInfoDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"


// CMFCSocialNetWorkUserInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMFCSocialNetWorkUserInfoDlg, CDialogEx)

CMFCSocialNetWorkUserInfoDlg::CMFCSocialNetWorkUserInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_DIALOG1, pParent)
{

}

CMFCSocialNetWorkUserInfoDlg::~CMFCSocialNetWorkUserInfoDlg()
{
}

BOOL CMFCSocialNetWorkUserInfoDlg::OnInitDialog()
{
	// 调用父类的 OnInitDialog() 函数
	CDialogEx::OnInitDialog();
	return TRUE;
}

void CMFCSocialNetWorkUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMFCSocialNetWorkUserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_USER_REGIST_BUTTON, &CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserRegistButton)
	ON_BN_CLICKED(IDC_USER_DELE_BUTTON, &CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserDeleButton)
	ON_BN_CLICKED(IDC_USER_FIX_BUTTON, &CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserFixButton)
END_MESSAGE_MAP()


// CMFCSocialNetWorkUserInfoDlg 消息处理程序


void CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserRegistButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CEdit* pUserNameEdit = (CEdit*)GetDlgItem(IDC_USER_NAME_EDIT);
	CString pUserName;
	pUserNameEdit->GetWindowText(pUserName);

	CEdit* pUserAddrEdit = (CEdit*)GetDlgItem(IDC_USER_ADDR_EDIT);
	CString pUserAddr;
	pUserAddrEdit->GetWindowText(pUserAddr);

	CEdit* pUserPhoneEdit = (CEdit*)GetDlgItem(IDC_USER_PHONE_EDIT);
	CString pUserPhone;
	pUserPhoneEdit->GetWindowText(pUserPhone);

	CEdit* pUserBirthdateEdit = (CEdit*)GetDlgItem(IDC_USER_BIRTH_EDIT);
	CString pUserBirthdate;
	pUserBirthdateEdit->GetWindowText(pUserBirthdate);

	SocialNetwork::getInstance().registerUser(W2A(pUserName), W2A(pUserAddr),
		W2A(pUserPhone), W2A(pUserBirthdate));
}


void CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserDeleButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CEdit* pUserNameEdit = (CEdit*)GetDlgItem(IDC_USER_NAME_EDIT);
	CString pUserName;
	pUserNameEdit->GetWindowText(pUserName);

	CEdit* pUserAddrEdit = (CEdit*)GetDlgItem(IDC_USER_ADDR_EDIT);
	CString pUserAddr;
	pUserAddrEdit->GetWindowText(pUserAddr);

	CEdit* pUserPhoneEdit = (CEdit*)GetDlgItem(IDC_USER_PHONE_EDIT);
	CString pUserPhone;
	pUserPhoneEdit->GetWindowText(pUserPhone);

	CEdit* pUserBirthdateEdit = (CEdit*)GetDlgItem(IDC_USER_BIRTH_EDIT);
	CString pUserBirthdate;
	pUserBirthdateEdit->GetWindowText(pUserBirthdate);

	User user(W2A(pUserName), W2A(pUserAddr), W2A(pUserAddr), W2A(pUserBirthdate));
	SocialNetwork::getInstance().removeUser(&user);
}


void CMFCSocialNetWorkUserInfoDlg::OnBnClickedUserFixButton()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CEdit* pUserNameEdit = (CEdit*)GetDlgItem(IDC_USER_NAME_EDIT);
	CString pUserName;
	pUserNameEdit->GetWindowText(pUserName);

	CEdit* pUserAddrEdit = (CEdit*)GetDlgItem(IDC_USER_ADDR_EDIT);
	CString pUserAddr;
	pUserAddrEdit->GetWindowText(pUserAddr);

	CEdit* pUserPhoneEdit = (CEdit*)GetDlgItem(IDC_USER_PHONE_EDIT);
	CString pUserPhone;
	pUserPhoneEdit->GetWindowText(pUserPhone);

	CEdit* pUserBirthdateEdit = (CEdit*)GetDlgItem(IDC_USER_BIRTH_EDIT);
	CString pUserBirthdate;
	pUserBirthdateEdit->GetWindowText(pUserBirthdate);

	User user(W2A(pUserName), W2A(pUserAddr), W2A(pUserAddr), W2A(pUserBirthdate));
	SocialNetwork::getInstance().fixUser(W2A(pUserName), &user);
}
