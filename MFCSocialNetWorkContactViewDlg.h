#pragma once


// CMFCSocialNetWorkContactViewDlg 对话框

class CMFCSocialNetWorkContactViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCSocialNetWorkContactViewDlg)

public:
	CMFCSocialNetWorkContactViewDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMFCSocialNetWorkContactViewDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTACT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ContactList;
	CEdit m_NameEdit;
	CString m_NameString;
	CEdit m_ContactEdit;
	CString m_ContactString;
	afx_msg void OnBnClickedAddContactButton();
	afx_msg void OnBnClickedFlushButton();
	afx_msg void OnBnClickedDelContactButton();
};
