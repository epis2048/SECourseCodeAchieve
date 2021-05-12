// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "global.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(int runType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GAME, pParent)
{
	//初始化起始点坐标
	m_ptGameTop.x = 20;
	m_ptGameTop.y = 20;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	//初始化图标选中状态
	isFirstPoint = true;
	isPlaying = false;
	this->pParent = pParent;
	this->runType = runType;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CGameDlg::OnBnClickedButtonRestart)
	ON_BN_CLICKED(IDC_BUTTON_ENDGAME, &CGameDlg::OnBnClickedButtonEndgame)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

void CGameDlg::initBackground() {
	//加载BMP图片资源
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//获得当前对话框的视频内容
	CClientDC dc(this);
	//创建与视频内容兼容的内存DC
	dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	dcBG.SelectObject(Backbmp);
	//初始化内存DC
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	dcMem.SelectObject(&bmpMem);
	//hu绘制背景到内存DC中
	dcMem.BitBlt(0, 0, 800, 600, &dcBG, 0, 0, SRCCOPY);
	//设置窗口大小
	UpdateWindow();
}

void CGameDlg::initElement() {
	CClientDC dc(this);
	HANDLE Elmbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	dcElm.CreateCompatibleDC(&dc);
	dcElm.SelectObject(Elmbmp);
	//掩码图加载
	HANDLE Maskbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	dcMask.CreateCompatibleDC(&dc);
	dcMask.SelectObject(Maskbmp);
	//加载掩盖图片
	//加载BMP图片资源
	HANDLE hCache = ::LoadImage(NULL, _T("theme\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	dcCache.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	dcCache.SelectObject(hCache);
}

void CGameDlg::UpdateWindow() {
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);		//获得窗口大小
	this->GetWindowRect(rtClient);	//获得客户区大小
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Width() - rtClient.Width();
	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	//窗口居中
	CenterWindow();
}
void CGameDlg::OnPaint()
{
	CPaintDC dc(this);
	dc.BitBlt(0, 0, 800, 600, &dcMem, 0, 0, SRCCOPY);
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//窗口标题
	if (this->runType == 1)
		this->SetWindowTextW(_T("基本模式 - 欢乐连连看"));
	else if (this->runType == 2)
		this->SetWindowTextW(_T("休闲模式 - 欢乐连连看"));
	else if (this->runType == 3)
		this->SetWindowTextW(_T("闯关模式 - 欢乐连连看"));
	//初始化背景
	initBackground();
	//初始化元素
	initElement();
	//初始化按钮
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(false);
	//CProgressCtrl* m_prg = (CProgressCtrl*)this->GetDlgItem(IDC_TIME_PROGRESS);
	if (this->runType == 3) {
		this->score = 0;
		this->GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOW);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::OnBnClickedButtonEndgame() {
	EndDialog(0);
	pParent->ShowWindow(SW_SHOW);
}


void CGameDlg::OnBnClickedButtonStart() {
	game.startGame();
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(true);
	isPlaying = true;
	isFirstPoint = true;
	//更新地图
	updateMap(game.getMap());
	//更新窗口
	Invalidate(FALSE);
	//基本模式和关卡模式有进度条
	if (this->runType == 1) {
		CProgressCtrl* m_prg = (CProgressCtrl*)this->GetDlgItem(IDC_TIME_PROGRESS);
		m_prg->ShowWindow(SW_SHOW);
		m_prg->SetRange(0, MAX_PLAY_TIME);
		m_prg->SetStep(1);
		m_prg->SetPos(MAX_PLAY_TIME);
	}
	if (this->runType == 3) {
		CProgressCtrl* m_prg = (CProgressCtrl*)this->GetDlgItem(IDC_TIME_PROGRESS);
		m_prg->ShowWindow(SW_SHOW);
		m_prg->SetRange(0, MAX_PLAY_TIME);
		m_prg->SetStep(1);
		m_prg->SetPos(MAX_PLAY_TIME);
	}
	if (this->runType == 1) {
		SetTimer(1, 1000, NULL);  //设置1000毫秒一次.ID为1
	}
	if (this->runType == 3) {
		SetTimer(1, 1000, NULL);  //设置1000毫秒一次.ID为1
	}
}

//更新地图
void CGameDlg::updateMap(int** p)
{
	// TODO: 在此处添加实现代码.

	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			int nInfo = p[i][j];       //当前元素图片的数值
			if (nInfo == 0)  continue;
			//将背景与掩码相或，边保留，图像区域为1
			dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &dcMask, 0, nInfo * nElemH, SRCPAINT);
			//将元素图片相与，边保留，图像区域为元素图片
			dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &dcElm, 0, nInfo * nElemH, SRCAND);

		}
	}

}

void CGameDlg::OnBnClickedButtonRestart() {
	if (this->runType == 3) {
		if (this->score >= COST_RESTART) {
			game.restartGame();
			updateMap(game.getMap());
			InvalidateRect(m_rtGameRect, FALSE);
			this->score -= COST_RESTART;
			updateScore();
		}
		else {
			this->GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("积分不足！"));
		}
	}
	else {
		game.restartGame();
		updateMap(game.getMap());
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	if (isPlaying) { //只有在游戏过程中才可以点
		//去掉小于0状态
		if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y) {
			return CDialogEx::OnLButtonUp(nFlags, point);
		}
		//换算点击的坐标
		int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;//行号
		int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
		//判断坐标的有效性
		if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1) {
			return CDialogEx::OnLButtonUp(nFlags, point);
		}
		//第一个点
		if (isFirstPoint) {
			//绘制提示框
			drawTipFrame(nRow, nCol);
			row1 = nRow;
			col1 = nCol;
		}
		//第二个点
		else {
			int** p = game.getMap();
			if (row1 == nRow && col1 == nCol) { //自己不能消自己
				isFirstPoint = !isFirstPoint; //赋反值
			}
			else if (p[row1][col1] != p[nRow][nCol]) { //如果两个点不是一种东西
				updateMap(p); //删除老的矩形框
				InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
				//将这个变成第一个点
				drawTipFrame(nRow, nCol); //绘制新的矩形框
				row1 = nRow;
				col1 = nCol;
				isFirstPoint = !isFirstPoint; //赋反值
			}
			else {
				drawTipFrame(nRow, nCol); //绘制矩形框
				//判断是否是相同图片
				int* x;
				x = game.killPoint(row1, col1, nRow, nCol);
				if (x != NULL) {
					if (x[0] == 0) { //一条线消子
						drawTipLine(row1, col1, nRow, nCol);
					}
					else if (x[0] == 1) { //两条线消子
						drawTipLine(row1, col1, x[1], x[2]);
						drawTipLine(x[1], x[2], nRow, nCol);
					}
					else if (x[0] == 2) { //三条线消子
						drawTipLine(row1, col1, x[1], x[2]);
						drawTipLine(x[1], x[2], x[3], x[4]);
						drawTipLine(x[3], x[4], nRow, nCol);
					}
					updateMap(p); //更新地图
					Sleep(200); //延迟
				}
				Sleep(200); //延迟
				InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
				if (this->runType == 3) {
					this->score += 1;
					updateScore();
				}
				//判断胜负
				if (game.isWin()) {
					isPlaying = false;
					//初始化按钮
					this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
					this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
					this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(false);
					this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(false);
					KillTimer(1);
					MessageBox(_T("成功！你好厉害"), _T("欢乐连连看"));
					return;
				}
			}
		}
		isFirstPoint = !isFirstPoint; //赋反值
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::drawTipLine(int startX, int startY, int endX, int endY) {
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	dc.MoveTo(m_ptGameTop.x + startY * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + startX * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	dc.LineTo(m_ptGameTop.x + endY * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + endX * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.SelectObject(pOldPen);
}

//绘制矩形提示框
void CGameDlg::drawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::updateScore() {
	CString str;
	str.Format(_T("积分：%d"), this->score * 10);
	this->GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(str);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent) {
	if (isPlaying) { //暂停时候不计时
		CProgressCtrl* m_prg = (CProgressCtrl*)this->GetDlgItem(IDC_TIME_PROGRESS);
		int n_pos = m_prg->GetPos();
		if (n_pos <= 0) { //时间已到
			KillTimer(1);
			isPlaying = false;
			//初始化按钮
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true);
			this->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
			this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(false);
			this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(false);
			MessageBox(_T("失败！时间已到"), _T("欢乐连连看"));
			this->score = 0; //积分置0
		}
		else {
			m_prg->SetPos(n_pos - 1);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnBnClickedButtonPause() {
	if (this->isPlaying) {
		this->isPlaying = false;
		this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(false);
		this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(false);
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("继续"));
		dcMem.BitBlt(m_ptGameTop.y, m_ptGameTop.x, m_rtGameRect.Width(), m_rtGameRect.Height(), &dcCache, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
	}
	else {
		this->isPlaying = true;
		this->GetDlgItem(IDC_BUTTON_HELP)->EnableWindow(true);
		this->GetDlgItem(IDC_BUTTON_RESTART)->EnableWindow(true);
		this->GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowText(_T("暂停"));
		updateMap(game.getMap());
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
	}
}


void CGameDlg::OnBnClickedButtonHelp() {
	int* path = game.findPath();
	if (path == NULL) { //没有路径则重置地图
		game.restartGame();
		updateMap(game.getMap());
		InvalidateRect(m_rtGameRect, FALSE);
	}
	else {
		if (this->runType == 3) {
			if (this->score >= COST_HELP) {
				this->score -= COST_HELP;
				updateScore();
			}
			else {
				this->GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("积分不足！"));
				return;
			}
		}
		if (path[0] == 0) { //找到了一条直线的方法
			//画点的提示框
			drawTipFrame(path[1], path[2]);
			drawTipFrame(path[3], path[4]);
			//画线的提示框
			drawTipLine(path[1], path[2], path[3], path[4]);
		}
		else if (path[0] == 1) { //找到了两条直线的方法
			//画点的提示框
			drawTipFrame(path[1], path[2]);
			drawTipFrame(path[5], path[6]);
			//画线的提示框
			drawTipLine(path[1], path[2], path[3], path[4]);
			drawTipLine(path[3], path[4], path[5], path[6]);
		}
		else if (path[0] == 2) { //找到了三条直线的方法
			//画点的提示框
			drawTipFrame(path[1], path[2]);
			drawTipFrame(path[7], path[8]);
			//画线的提示框
			drawTipLine(path[1], path[2], path[3], path[4]);
			drawTipLine(path[3], path[4], path[5], path[6]);
			drawTipLine(path[5], path[6], path[7], path[8]);
		}
		updateMap(game.getMap()); //更新地图
		Sleep(1000);    //延迟
		updateMap(game.getMap()); //更新地图
		InvalidateRect(m_rtGameRect, FALSE); //局部矩形更新
	}
}


void CGameDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	pParent->ShowWindow(SW_SHOW);
	CDialogEx::OnClose();
}
