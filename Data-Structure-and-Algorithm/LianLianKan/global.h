#pragma once
typedef struct tagVertex {
	int row; //行
	int col; //列
	int info; //内容
}Vertex;

# define MAX_ROW 12 //行数
# define MAX_COL 15 //列数
# define MAX_KIND_ICO 15 //图标类别数
# define MAX_PLAY_TIME 180 //游戏时常
# define COST_HELP 3 //提示按钮所需积分
# define COST_RESTART 10 //重排按钮所需积分
/*
# define MAX_ROW 4
# define MAX_COL 4
# define MAX_KIND_ICO 8
# define MAX_PLAY_TIME 20
*/