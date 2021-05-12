
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "CGameMain.h"
#include "afxdialogex.h"
#include "CGameLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGameAbout.h"

// CGameMain 对话框

CGameMain::CGameMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameMain, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CGameMain::OnBnClickedButtonBase)
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &CGameMain::OnBnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_CG, &CGameMain::OnBnClickedButtonCg)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CGameMain::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT2, &CGameMain::OnBnClickedButtonExit2)
END_MESSAGE_MAP()


// CGameMain 消息处理程序

BOOL CGameMain::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	//initBackground();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameMain::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameMain::OnPaint()
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
		//创建CPaintDC对象
		//CPaintDC dc(this);

		//dc.BitBlt(0, 0, 800, 600, &dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
		m_font.CreatePointFont(500, _T("黑体"), NULL);
		GetDlgItem(IDC_STATIC)->SetFont(&m_font);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameMain::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CGameMain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CGameMain::OnBnClickedButtonBase() {
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(1, this);
	dlg.DoModal();
}

void CGameMain::OnBnClickedButtonRelax() {
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(2, this);
	dlg.DoModal();
}


void CGameMain::OnBnClickedButtonCg() {
	this->ShowWindow(SW_HIDE);
	CGameDlg dlg(3, this);
	dlg.DoModal();
}

void CGameMain::OnBnClickedButtonExit() {
	exit(0);
}


void CGameMain::OnBnClickedButtonExit2()
{
	CGameAbout about(this);
	about.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
