#include "pch.h"
#include "CGameLogic.h"
#include <time.h>

CGameLogic::CGameLogic() {
}

CGameLogic::~CGameLogic() {
}

bool CGameLogic::checkVexIsInRow(int** pGameMap, Vertex v1, Vertex v2) {
	if (v1.row == v2.row) { //行相同
		if (v1.col > v2.col) { //交换v1，v2，使v1.col小于v2.col
			Vertex temp = v1;
			v1 = v2;
			v2 = temp;
		}
		int i = v1.col + 1;
		while (i < v2.col) {
			if (pGameMap[v1.row][i] != 0) {
				return false;
			}
			i++;
		}
	}
	else if (v1.col == v2.col) { //列相同
		if (v1.row > v2.row) { //交换v1，v2，使v1.row小于v2.row
			Vertex temp = v1;
			v1 = v2;
			v2 = temp;
		}
		int i = v1.row + 1;
		while (i < v2.row) {
			if (pGameMap[i][v1.col] != 0) {
				return false;
			}
			i++;
		}
	}
	else return false; //都不相同
	return true; //如果中途没有被打断，即可认为是联通的
}

int* CGameLogic::checkVexOneCorner(int** pGameMap, Vertex v1, Vertex v2) {
	Vertex v3, v4; //取v1，v2两节点的拐点
	v3.row = v1.row; v3.col = v2.col;
	v4.row = v2.row; v4.col = v1.col;
	bool canGo = false;
	int* ret = new int[2];
	if (pGameMap[v3.row][v3.col] == 0) { //如果v3这个点可用
		if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v2, v3)) { //判断经由v3是否可行
			canGo = true;
			ret[0] = v3.row; ret[1] = v3.col;
		}
	}
	else if (pGameMap[v4.row][v4.col] == 0) { //如果v4这个点可用
		if (checkVexIsInRow(pGameMap, v1, v4) && checkVexIsInRow(pGameMap, v2, v4)) { //判断经由v4是否可行
			canGo = true;
			ret[0] = v4.row; ret[1] = v4.col;
		}
	}
	if (canGo) return ret;
	else return NULL;
}

int* CGameLogic::checkVexTwoCorner(int** pGameMap, Vertex v1, Vertex v2) {
	Vertex v3, v4;
	bool canGo = false;
	int* ret = new int[4];
	//先判断竖向
	if (v1.col != v2.col) { //前提是俩点不能在一列
		for (int i = 0; i < MAX_ROW; i++) { //从上到下
			if (i == v1.row || i == v2.row) continue; //不能和原来的点重合
			v3.row = i; v4.row = i; v3.col = v1.col; v4.col = v2.col;
			if (pGameMap[v3.row][v3.col] == 0 && pGameMap[v4.row][v4.col] == 0) {
				if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v3, v4) && checkVexIsInRow(pGameMap, v4, v2)) { //判断经由v1,v3,v4,v2是否可行
					canGo = true;
					ret[0] = v3.row; ret[1] = v3.col; ret[2] = v4.row; ret[3] = v4.col;
					break;
				}
			}
		}
	}
	//再判断横向
	if (v1.row != v2.row) { //前提是俩点不能在一行
		for (int i = 0; i < MAX_COL; i++) { //从左到右
			if (i == v1.col || i == v2.col) continue; //不能和原来的点重合
			v3.col = i; v4.col = i; v3.row = v1.row; v4.row = v2.row;
			if (pGameMap[v3.row][v3.col] == 0 && pGameMap[v4.row][v4.col] == 0) {
				if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v3, v4) && checkVexIsInRow(pGameMap, v4, v2)) { //判断经由v1,v3,v4,v2是否可行
					canGo = true;
					ret[0] = v3.row; ret[1] = v3.col; ret[2] = v4.row; ret[3] = v4.col;
					break;
				}
			}
		}
	}
	if (canGo) return ret;
	else return NULL;
}

bool CGameLogic::isWin(int** pGameMap) {
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (pGameMap[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

void CGameLogic::initMap(int** pGameMap) {
	int x = 1; //x是第几个图片
	int count = 0;
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			pGameMap[i][j] = x;
			count++;
			if (count >= (MAX_ROW * MAX_COL / MAX_KIND_ICO)) {
				x++; //这个图片数量够了
				count = 0;
			}
		}
	}
}

void CGameLogic::resetMap(int** pGameMap) {
	srand((int)time(NULL)); //设置种子
	for (int i = 0; i < MAX_ROW * MAX_COL * 10; i++) {
		//随机得到两个坐标
		int v1_row = rand() % MAX_ROW;
		int v2_row = rand() % MAX_ROW;
		int v1_col = rand() % MAX_COL;
		int v2_col = rand() % MAX_COL;
		//为空则不变
		if (pGameMap[v1_row][v1_col] == 0 || pGameMap[v2_row][v2_col] == 0) continue;
		//交换两个数值
		int temp = pGameMap[v1_row][v1_col];
		pGameMap[v1_row][v1_col] = pGameMap[v2_row][v2_col];
		pGameMap[v2_row][v2_col] = temp;
	}
}

int* CGameLogic::findPath(int** pGameMap) {
	int* path = NULL;
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (pGameMap[i][j] == 0) continue; //如果第一个是空节点那就跳过
			else {
				for (int i2 = 0; i2 < MAX_ROW; i2++) {
					for (int j2 = 0; j2 < MAX_COL; j2++) {
						if (pGameMap[i2][j2] == 0) continue; //如果第二个是空节点就跳过
						else if (i == i2 && j == j2) continue; //一、二不能是同一个节点
						else if (pGameMap[i][j] != pGameMap[i2][j2]) continue; //俩节点必须是同一个花色
						else if (i2 <= i && j2 <= j) continue; //没必要找以第一个节点和原点连成的矩形范围（存在重复遍历）
						else {
							Vertex v1, v2;
							v1.row = i; v1.col = j; v1.info = pGameMap[i][j];
							v2.row = i2; v2.col = j2; v2.info = pGameMap[i2][j2];
							if (v1.info != v2.info) return false;
							if (v1.row == v2.row || v1.col == v2.col) { //如果两个点不在同一行/列，就不用判断了
								if (checkVexIsInRow(pGameMap, v1, v2)) {
									path = new int[5];
									path[0] = 0; path[1] = i; path[2] = j; path[3] = i2; path[4] = j2;
									goto success;
								}
							}
							int* y = checkVexOneCorner(pGameMap, v1, v2);
							if (y != NULL) {
								path = new int[7];
								path[0] = 1; path[1] = i; path[2] = j; path[3] = y[0]; path[4] = y[1]; path[5] = i2; path[6] = j2;
								goto success;
							}
							y = checkVexTwoCorner(pGameMap, v1, v2);
							if (y != NULL) {
								path = new int[9];
								path[0] = 2; path[1] = i; path[2] = j; path[3] = y[0]; path[4] = y[1]; path[5] = y[2]; path[6] = y[3]; path[7] = i2; path[8] = j2;
								goto success;
							}
						}
					}
				}
			}
		}
	}
	return NULL;
success: return path;
}
