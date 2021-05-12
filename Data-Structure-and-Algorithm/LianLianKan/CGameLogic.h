#pragma once
#include "pch.h"
#include <iostream>
#include "global.h"

using namespace std;

class CGameLogic {
public:
	CGameLogic();
	~CGameLogic();
	bool checkVexIsInRow(int** pGameMap, Vertex v1, Vertex v2); //两个点是否在一个直线上
	int* checkVexOneCorner(int** pGameMap, Vertex v1, Vertex v2); //两个点连线是两个边，一个拐角
	int* checkVexTwoCorner(int** pGameMap, Vertex v1, Vertex v2); //两个点连线是三个边，两个个拐角
	bool isWin(int** pGameMap); //检测图中是否有剩余点
	void initMap(int** pGameMap);
	void resetMap(int** pGameMap);
	int* findPath(int** pGameMap);
};