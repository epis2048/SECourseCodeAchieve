#pragma once
#include "pch.h"
#include <iostream>
#include "global.h"
#include "CGameLogic.h"

class CGameControl {
protected:
	CGameLogic gameLogic;
	int** pGameMap;
public:
	CGameControl();
	~CGameControl();
	void startGame();
	void restartGame();
	int* killPoint(int v1_row, int v1_col, int v2_row, int v2_col);
	int** getMap();
	bool isWin();
	int* findPath();
};

