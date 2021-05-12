#pragma once
#include <iostream>
#include "Graph.cpp"

using namespace std;

class Tourism {
public:
	graph G;
	Tourism();
	void createGraph(); //����ͼ
	void searchVex(string vexName); //�����ڵ�
	void doDFS(string vexName);
	void findShortPath(string startVexName, string endVexName);
	~Tourism();
};
