#pragma once
#include <iostream>
#include "Graph.cpp"

using namespace std;

class Tourism {
public:
	graph G;
	Tourism();
	void createGraph(); //创建图
	void searchVex(string vexName); //搜索节点
	void doDFS(string vexName);
	void findShortPath(string startVexName, string endVexName);
	~Tourism();
};
