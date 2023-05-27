
// MFCSocialNetWorkDlg.h: 头文件
//

#pragma once


// CMFCSocialNetWorkDlg 对话框
class CMFCSocialNetWorkDlg : public CDialogEx
{
// 构造
public:
	CMFCSocialNetWorkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSOCIALNETWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	virtual void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedDateButton();
	afx_msg void OnBnClickedUserButton();
	afx_msg void OnBnClickedContactButton();
	afx_msg void OnBnClickedMessageButton();
	afx_msg void OnBnClickedGroupButton();
	afx_msg void OnBnClickedImportButton();
	afx_msg void OnBnClickedDataExportButton();

public:
	CStatic m_BirthStatic;
	CEdit m_MonthEdit;
	CEdit m_DayEdit;
	CButton m_DateButton;
};
