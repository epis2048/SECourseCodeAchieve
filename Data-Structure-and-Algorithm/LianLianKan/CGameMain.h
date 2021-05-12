#pragma once
#include "CGameDlg.h"

class CGameMain : public CDialogEx {
public:
	CGameMain(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;
	CFont m_font;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonBase();
	afx_msg void OnBnClickedButtonRelax();
	afx_msg void OnBnClickedButtonCg();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonExit2();
};
