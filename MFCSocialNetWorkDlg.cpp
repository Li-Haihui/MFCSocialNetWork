
// MFCSocialNetWorkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSocialNetWork.h"
#include "MFCSocialNetWorkDlg.h"
#include "MFCSocialNetWorkUserInfoDlg.h"
#include "MFCSocialNetWorkUserViewDlg.h"
#include "MFCSocialNetWorkContactViewDlg.h"
#include "MFCSocialNetWorkMessageDlg.h"
#include "MFCSocialNetWorkGroupDlg.h"
#include "SocialNetworkApp.h"
#include "SocialNetWorkUser.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
afx_msg void OnBnClickedButton2();
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnBnClickedButton2()
{

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCSocialNetWorkDlg 对话框



CMFCSocialNetWorkDlg::CMFCSocialNetWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSOCIALNETWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSocialNetWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BIRTH_STATIC, m_BirthStatic);
	DDX_Control(pDX, IDC_MONTH_EDIT, m_MonthEdit);
	DDX_Control(pDX, IDC_DAY_EDIT, m_DayEdit);
	DDX_Control(pDX, IDC_DATE_BUTTON, m_DateButton);
}

BEGIN_MESSAGE_MAP(CMFCSocialNetWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_DATE_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedDateButton)
	ON_BN_CLICKED(IDC_USER_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedUserButton)
	ON_BN_CLICKED(IDC_CONTACT_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedContactButton)
	ON_BN_CLICKED(IDC_MESSAGE_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedMessageButton)
	ON_BN_CLICKED(IDC_GROUP_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedGroupButton)
	ON_BN_CLICKED(IDC_IMPORT_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedImportButton)
	ON_BN_CLICKED(IDC_DATA_EXPORT_BUTTON, &CMFCSocialNetWorkDlg::OnBnClickedDataExportButton)
END_MESSAGE_MAP()


// CMFCSocialNetWorkDlg 消息处理程序

BOOL CMFCSocialNetWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	// 获取当前系统日期
	CTime time = CTime::GetCurrentTime();
	int month = time.GetMonth();

	// 将月份赋值给 MFC 的 Edit 控件
	CString strMonth;
	strMonth.Format(_T("%d"), month);
	m_MonthEdit.SetWindowText(strMonth);

	int day = time.GetDay();
	// 将月份赋值给 MFC 的 Edit 控件
	CString strDay;
	strDay.Format(_T("%d"), day);
	m_DayEdit.SetWindowText(strDay);

	USES_CONVERSION;
	CString pMonthStr, pDayStr, pDate;
	m_MonthEdit.GetWindowText(pMonthStr);
	m_DayEdit.GetWindowText(pDayStr);
	pDate = pMonthStr + "/" + pDayStr;
	SocialNetwork::getInstance().setAppDate(string(W2A(pDate)));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSocialNetWorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


void CMFCSocialNetWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSocialNetWorkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSocialNetWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSocialNetWorkDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	USES_CONVERSION;
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	if (WA_ACTIVE == nState) {
		CString pMonthStr, pDayStr, pDate;
		m_MonthEdit.GetWindowText(pMonthStr);
		m_DayEdit.GetWindowText(pDayStr);
		pDate = pMonthStr + "/" + pDayStr;
		SocialNetwork::getInstance().setAppDate(string(W2A(pDate)));
		vector<User*> users = SocialNetwork::getInstance().getUsers();
		bool birthFlag = false;
		for (int i = 0; i < users.size(); i++) {
			if (SocialNetwork::getInstance().isBirthday(users[i])) {
				birthFlag = true;
				break;
			}
		}

		if (birthFlag) {
			m_BirthStatic.SetWindowText(_T("Happy birthday!"));
		}
	}
	else {

	}
}


void CMFCSocialNetWorkDlg::OnBnClickedDateButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_MonthEdit.EnableWindow(FALSE);
	m_DayEdit.EnableWindow(FALSE);
	m_DateButton.EnableWindow(FALSE);
}


void CMFCSocialNetWorkDlg::OnBnClickedUserButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCSocialNetWorkUserViewDlg dlg;
	dlg.DoModal();
}


void CMFCSocialNetWorkDlg::OnBnClickedContactButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCSocialNetWorkContactViewDlg dlg;
	dlg.DoModal();
}


void CMFCSocialNetWorkDlg::OnBnClickedMessageButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCSocialNetWorkMessageDlg dlg;
	dlg.DoModal();
}


void CMFCSocialNetWorkDlg::OnBnClickedGroupButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCSocialNetWorkGroupDlg dlg;
	dlg.DoModal();
}


void CMFCSocialNetWorkDlg::OnBnClickedImportButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SocialNetwork::getInstance().importData("user.data");
}


void CMFCSocialNetWorkDlg::OnBnClickedDataExportButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SocialNetwork::getInstance().exportData("user.data");
}
