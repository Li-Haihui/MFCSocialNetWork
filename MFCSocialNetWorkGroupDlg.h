#pragma once


// CMFCSocialNetWorkGroupDlg 对话框

class CMFCSocialNetWorkGroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCSocialNetWorkGroupDlg)

public:
	CMFCSocialNetWorkGroupDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMFCSocialNetWorkGroupDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GROUP_DIALOG };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_JoinUserComboBox;
	CComboBox m_JoinContactComboBox;
	CComboBox m_LeaveUserComboBox;
	CComboBox m_LeaveGroupComboBox;
	CComboBox m_SendUserComboBox;
	CComboBox m_SendGroupComboBox;
	CEdit m_SendMessageEdit;
	CComboBox m_ViewUserComboBox;
	CListCtrl m_ViewGroupList;
	CComboBox m_MessageUserComboBox;
	CComboBox m_MessageGroupComboBox;
	CListCtrl m_ViewMessageList;
	afx_msg void OnBnClickedJoinButton();
	afx_msg void OnCbnSelchangeJoinUserCombo();
	afx_msg void OnCbnSelchangeJionContactCombo();
	afx_msg void OnCbnSelchangeLeaveUserCombo();
};
