#pragma once


// CMFCSocialNetWorkMessageDlg 对话框

class CMFCSocialNetWorkMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCSocialNetWorkMessageDlg)

public:
	CMFCSocialNetWorkMessageDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMFCSocialNetWorkMessageDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAGE_DIALOG };
#endif

protected:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ContactList;
	CEdit m_UserEdit;
	CEdit m_ContactEdit;
	CEdit m_MessageEdit;
	CEdit m_MessageUserEdit;
	CEdit m_MessageContactEdit;
	CListCtrl m_MessageList;
	CEdit m_MessageIDEdit;
	afx_msg void OnBnClickedSendmessageButton();
	afx_msg void OnBnClickedFlushButton();
	afx_msg void OnBnClickedDelemessageButton();
};
