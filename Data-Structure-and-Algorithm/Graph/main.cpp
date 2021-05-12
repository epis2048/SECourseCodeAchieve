#pragma once
#include <iostream>
#include "Tourism.h"


using namespace std;

int main() {
	Tourism T;
	T.createGraph();
	int usrCho;
	string vexName;
	string vexName2;
	while (1) {
		system("cls");
		cout << "------------ 景区管理系统 ------------" << endl;
		cout << "1. 查询所有景区" << endl;
		cout << "2. 查询所有路径" << endl;
		cout << "3. 查询景区详细信息" << endl;
		cout << "4. 旅游景点导航" << endl;
		cout << "5. 搜索最短路径" << endl;
		cout << "6. Prim方法铺设电缆" << endl;
		cout << "0. 退出系统" << endl;
		cout << "请选择：";
		cin >> usrCho;
		if (!usrCho) break;
		switch (usrCho) {
		case 1:
			T.G.printVexs();
			break;
		case 2:
			T.G.printEdges();
			break;
		case 3:
			cout << "请输入景区名称：";
			cin >> vexName;
			T.searchVex(vexName);
			break;
		case 4:
			T.G.printVexs();
			cout << "请输入开始的景点名称：";
			cin >> vexName;
			T.doDFS(vexName);
			break;
		case 5:
			T.G.printVexs();
			cout << "请输入开始的景点名称：";
			cin >> vexName;
			cout << "请输入结束的景点名称：";
			cin >> vexName2;
			T.findShortPath(vexName, vexName2);
			break;
		case 6:
			T.G.PrimMinTree().printEdgesWithDis();
			break;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}