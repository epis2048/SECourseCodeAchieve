#pragma once
#include "CGameMain.h"
#include "CGameControl.h"

class CGameDlg : public CDialogEx {
	DECLARE_DYNAMIC(CGameDlg)
	DECLARE_MESSAGE_MAP()
public:
	CGameDlg(int runType, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GAME };
#endif

protected:
	//界面
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自定义
	CWnd* pParent; //父页面指针
	CDC dcMem; //内存DC：整体图
	CDC dcElm; //内存DC：元素
	CDC dcMask; //内存DC：掩码
	CDC dcBG; //内存DC：背景
	CDC dcCache; //内存DC：暂停图
	CPoint m_ptGameTop; //起始点坐标
	CSize m_sizeElem; //图片元素大小
	CRect m_rtGameRect; //游戏区域的大小
	CGameControl game; //游戏控制类
	int row1, col1; //第一个点的点的坐标
	bool isPlaying; //当前是否开始
	bool isFirstPoint;	//选中的图片是不是第一次选中的，TRUE是，FALSE否
	int runType; //运行模式 1. 基本模式（比2多时间进度条）/ 2. 休闲模式 / 3. 闯关模式（比1多积分）
	int score; //积分 闯关模式专用

public:
	//重写函数
	virtual BOOL OnInitDialog();
	void OnLButtonUp(UINT nFlags, CPoint point);
	void UpdateWindow();
	//事件函数
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnBnClickedButtonEndgame();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//自有函数
	void initBackground(); //初始化背景
	void initElement(); //初始化连连看元素
	void updateMap(int** p); //更新地图
	void updateScore(); //更新积分
	void drawTipFrame(int nRow, int nCol); //画矩形提示框
	void drawTipLine(int startX, int startY, int endX, int endY); //绘制提示线
};
