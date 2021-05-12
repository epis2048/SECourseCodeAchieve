#pragma once
#include "pch.h"
#include <iostream>
#include "global.h"

using namespace std;

class CGameLogic {
public:
	CGameLogic();
	~CGameLogic();
	bool checkVexIsInRow(int** pGameMap, Vertex v1, Vertex v2); //�������Ƿ���һ��ֱ����
	int* checkVexOneCorner(int** pGameMap, Vertex v1, Vertex v2); //�����������������ߣ�һ���ս�
	int* checkVexTwoCorner(int** pGameMap, Vertex v1, Vertex v2); //�����������������ߣ��������ս�
	bool isWin(int** pGameMap); //���ͼ���Ƿ���ʣ���
	void initMap(int** pGameMap);
	void resetMap(int** pGameMap);
	int* findPath(int** pGameMap);
};