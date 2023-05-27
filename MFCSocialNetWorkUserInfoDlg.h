#pragma once


// CMFCSocialNetWorkUserInfoDlg 对话框

class CMFCSocialNetWorkUserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCSocialNetWorkUserInfoDlg)

public:
	CMFCSocialNetWorkUserInfoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMFCSocialNetWorkUserInfoDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUserRegistButton();
	afx_msg void OnBnClickedUserDeleButton();
	afx_msg void OnBnClickedUserFixButton();
};
