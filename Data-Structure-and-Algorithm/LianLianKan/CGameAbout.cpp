// CGameAbout.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CGameAbout.h"
#include "afxdialogex.h"



// CGameAbout 对话框

IMPLEMENT_DYNAMIC(CGameAbout, CDialogEx)

CGameAbout::CGameAbout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

CGameAbout::~CGameAbout()
{
}

void CGameAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameAbout, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGameAbout::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CGameAbout::OnInitDialog() {
	CDialogEx::OnInitDialog();
	/*
	CStdioFile file;
	CString str;
	if (file.Open(_T("readme.txt"), CFile::modeRead))
	{
		// 读入一行数据到 变量 str里 , 当到达文件末尾的时候 次函数就返回false了
		while (file.ReadString(str))
		{
			this->GetDlgItem(IDC_RICHEDIT21)->SetWindowText(str);
		}
		file.Close();
	}*/
	return TRUE;
}
// CGameAbout 消息处理程序


void CGameAbout::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
