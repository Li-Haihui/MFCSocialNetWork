#pragma once


// CMFCSocialNetWorkUserViewDlg 对话框

class CMFCSocialNetWorkUserViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCSocialNetWorkUserViewDlg)

public:
	CMFCSocialNetWorkUserViewDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMFCSocialNetWorkUserViewDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_UserListControl;
	CEdit m_UserNameEdit;
	CEdit m_UserAddrEdit;
	CEdit m_UserPhoneEdit;
	CEdit m_UserBirthEdit;
	afx_msg void OnBnClickedFlushButton();
	afx_msg void OnBnClickedUserRegistButton();
	afx_msg void OnBnClickedUserDeleButton();
	afx_msg void OnBnClickedUserFixButton();
	afx_msg void OnEnSetfocusUserBirthEdit();
};
