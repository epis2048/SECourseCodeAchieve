#include "pch.h"
#include "CGameControl.h"

CGameControl::CGameControl() {
}

CGameControl::~CGameControl() {
}

void CGameControl::startGame() {
	int** p = new int* [MAX_ROW];
	for (int i = 0; i < MAX_ROW; i++)
		p[i] = new int[MAX_COL];
	gameLogic.initMap(p);
	gameLogic.resetMap(p);
	pGameMap = p;
}

void CGameControl::restartGame() {
	gameLogic.resetMap(pGameMap);
}

int* CGameControl::killPoint(int v1_row, int v1_col, int v2_row, int v2_col) {
	bool isSuccess = false;
	Vertex v1, v2; //初始化节点信息
	v1.row = v1_row; v1.col = v1_col; v1.info = pGameMap[v1_row][v1_col];
	v2.row = v2_row; v2.col = v2_col; v2.info = pGameMap[v2_row][v2_col];
	if (v1.info != v2.info) return false;
	int* x = NULL;
	if (v1.row == v2.row || v1.col == v2.col) { //如果两个点不在同一行/列，就不用判断了
		if (gameLogic.checkVexIsInRow(pGameMap, v1, v2)) {
			x = new int;
			x[0] = 0;
			isSuccess = true;
			goto ret;
		}
	}
	int* y = gameLogic.checkVexOneCorner(pGameMap, v1, v2);
	if (y != NULL) {
		x = new int[3];
		x[0] = 1; x[1] = y[0]; x[2] = y[1];
		isSuccess = true;
		goto ret;
	}
	y = gameLogic.checkVexTwoCorner(pGameMap, v1, v2);
	if (y != NULL) {
		x = new int[5];
		x[0] = 2; x[1] = y[0]; x[2] = y[1]; x[3] = y[2]; x[4] = y[3];
		isSuccess = true;
		goto ret;
	}
	ret:
	if (isSuccess) { //成功则消点
		pGameMap[v1_row][v1_col] = 0;
		pGameMap[v2_row][v2_col] = 0;
		return x;
	}
	else return NULL;
}

int** CGameControl::getMap() {
	return pGameMap;
}

bool CGameControl::isWin() {
	return gameLogic.isWin(pGameMap);
}

int* CGameControl::findPath() {
	return gameLogic.findPath(pGameMap);
}

