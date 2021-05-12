#include "pch.h"
#include "CGameLogic.h"
#include <time.h>

CGameLogic::CGameLogic() {
}

CGameLogic::~CGameLogic() {
}

bool CGameLogic::checkVexIsInRow(int** pGameMap, Vertex v1, Vertex v2) {
	if (v1.row == v2.row) { //����ͬ
		if (v1.col > v2.col) { //����v1��v2��ʹv1.colС��v2.col
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
	else if (v1.col == v2.col) { //����ͬ
		if (v1.row > v2.row) { //����v1��v2��ʹv1.rowС��v2.row
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
	else return false; //������ͬ
	return true; //�����;û�б���ϣ�������Ϊ����ͨ��
}

int* CGameLogic::checkVexOneCorner(int** pGameMap, Vertex v1, Vertex v2) {
	Vertex v3, v4; //ȡv1��v2���ڵ�Ĺյ�
	v3.row = v1.row; v3.col = v2.col;
	v4.row = v2.row; v4.col = v1.col;
	bool canGo = false;
	int* ret = new int[2];
	if (pGameMap[v3.row][v3.col] == 0) { //���v3��������
		if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v2, v3)) { //�жϾ���v3�Ƿ����
			canGo = true;
			ret[0] = v3.row; ret[1] = v3.col;
		}
	}
	else if (pGameMap[v4.row][v4.col] == 0) { //���v4��������
		if (checkVexIsInRow(pGameMap, v1, v4) && checkVexIsInRow(pGameMap, v2, v4)) { //�жϾ���v4�Ƿ����
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
	//���ж�����
	if (v1.col != v2.col) { //ǰ�������㲻����һ��
		for (int i = 0; i < MAX_ROW; i++) { //���ϵ���
			if (i == v1.row || i == v2.row) continue; //���ܺ�ԭ���ĵ��غ�
			v3.row = i; v4.row = i; v3.col = v1.col; v4.col = v2.col;
			if (pGameMap[v3.row][v3.col] == 0 && pGameMap[v4.row][v4.col] == 0) {
				if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v3, v4) && checkVexIsInRow(pGameMap, v4, v2)) { //�жϾ���v1,v3,v4,v2�Ƿ����
					canGo = true;
					ret[0] = v3.row; ret[1] = v3.col; ret[2] = v4.row; ret[3] = v4.col;
					break;
				}
			}
		}
	}
	//���жϺ���
	if (v1.row != v2.row) { //ǰ�������㲻����һ��
		for (int i = 0; i < MAX_COL; i++) { //������
			if (i == v1.col || i == v2.col) continue; //���ܺ�ԭ���ĵ��غ�
			v3.col = i; v4.col = i; v3.row = v1.row; v4.row = v2.row;
			if (pGameMap[v3.row][v3.col] == 0 && pGameMap[v4.row][v4.col] == 0) {
				if (checkVexIsInRow(pGameMap, v1, v3) && checkVexIsInRow(pGameMap, v3, v4) && checkVexIsInRow(pGameMap, v4, v2)) { //�жϾ���v1,v3,v4,v2�Ƿ����
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
	int x = 1; //x�ǵڼ���ͼƬ
	int count = 0;
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			pGameMap[i][j] = x;
			count++;
			if (count >= (MAX_ROW * MAX_COL / MAX_KIND_ICO)) {
				x++; //���ͼƬ��������
				count = 0;
			}
		}
	}
}

void CGameLogic::resetMap(int** pGameMap) {
	srand((int)time(NULL)); //��������
	for (int i = 0; i < MAX_ROW * MAX_COL * 10; i++) {
		//����õ���������
		int v1_row = rand() % MAX_ROW;
		int v2_row = rand() % MAX_ROW;
		int v1_col = rand() % MAX_COL;
		int v2_col = rand() % MAX_COL;
		//Ϊ���򲻱�
		if (pGameMap[v1_row][v1_col] == 0 || pGameMap[v2_row][v2_col] == 0) continue;
		//����������ֵ
		int temp = pGameMap[v1_row][v1_col];
		pGameMap[v1_row][v1_col] = pGameMap[v2_row][v2_col];
		pGameMap[v2_row][v2_col] = temp;
	}
}

int* CGameLogic::findPath(int** pGameMap) {
	int* path = NULL;
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			if (pGameMap[i][j] == 0) continue; //�����һ���ǿսڵ��Ǿ�����
			else {
				for (int i2 = 0; i2 < MAX_ROW; i2++) {
					for (int j2 = 0; j2 < MAX_COL; j2++) {
						if (pGameMap[i2][j2] == 0) continue; //����ڶ����ǿսڵ������
						else if (i == i2 && j == j2) continue; //һ����������ͬһ���ڵ�
						else if (pGameMap[i][j] != pGameMap[i2][j2]) continue; //���ڵ������ͬһ����ɫ
						else if (i2 <= i && j2 <= j) continue; //û��Ҫ���Ե�һ���ڵ��ԭ�����ɵľ��η�Χ�������ظ�������
						else {
							Vertex v1, v2;
							v1.row = i; v1.col = j; v1.info = pGameMap[i][j];
							v2.row = i2; v2.col = j2; v2.info = pGameMap[i2][j2];
							if (v1.info != v2.info) return false;
							if (v1.row == v2.row || v1.col == v2.col) { //��������㲻��ͬһ��/�У��Ͳ����ж���
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
