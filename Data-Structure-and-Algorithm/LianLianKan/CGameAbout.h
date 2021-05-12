#pragma once
#include <fstream>
#include <string>

// CGameAbout 对话框

class CGameAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CGameAbout)

public:
	CGameAbout(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameAbout();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
