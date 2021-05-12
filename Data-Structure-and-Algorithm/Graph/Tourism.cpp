#pragma once
#include <iostream>
#include<fstream>
#include "Tourism.h"

using namespace std;

Tourism::Tourism() {

}

void Tourism::createGraph() {
	ifstream in;
	int num;
	in.open("Vex.txt");
	if (!in.is_open()) {
		cout << "����Ϣ�ļ��򿪳���" << endl;
		return;
	}
	//������
	in >> num;
	cout << "---- Vex ---- " << endl;
	cout << "������Ϊ��" << num << endl;
	for (int i = 0; i < num; i++) {
		Vex* vex = new Vex;
		in >> vex->ID;
		in >> vex->Name;
		in >> vex->Des;
		G.InsertVex(vex);
	}
	in.close();
	//������
	in.open("Edge.txt");
	if (!in.is_open()) {
		cout << "����Ϣ�ļ��򿪳���" << endl;
		return;
	}
	cout << "---- Edge ---- " << endl;
	num = 0;
	while (!in.eof()) {
		Edge* edge = new Edge;
		Vex* vex = new Vex;
		in >> vex->ID;
		edge->vex1 = G.getVex(vex);
		in >> vex->ID;
		edge->vex2 = G.getVex(vex);
		in >> edge->weight;
		G.InsertEdge(edge);
		num++;
	}
	cout << "·����Ϊ��" << num << endl;
	in.close();
}

void Tourism::searchVex(string vexName) {
	Vex* vex = new Vex;
	strcpy(vex->Name, vexName.c_str());
	vex = G.getVexByName(vex);
	if (vex) {
		cout << "�ҵ����㣺" << vex->Name << endl;
		cout << "����������" << vex->Des << endl;
		cout << "�ٽ����㣺" << endl;
		G.printEdgeByOneVexName(vex);
	}
	else {
		cout << "δ�ҵ���" << endl;
	}
}

void Tourism::doDFS(string vexName) {
	Vex* vex = new Vex;
	strcpy(vex->Name, vexName.c_str());
	vex = G.getVexByName(vex);
	if (vex) {
		G.DFSTraverse(vex);
	}
	else {
		cout << "δ�ҵ���" << endl;
	}
}

void Tourism::findShortPath(string startVexName, string endVexName) {
	Vex* vex1 = new Vex;
	Vex* vex2 = new Vex;
	strcpy(vex1->Name, startVexName.c_str());
	strcpy(vex2->Name, endVexName.c_str());
	vex1 = G.getVexByName(vex1);
	vex2 = G.getVexByName(vex2);
	if (vex1 && vex2) {
		cout << G.dijkstraShortPath(vex1, vex2) << endl;
	}
	else {
		cout << "δ�ҵ���" << endl;
	}
}

Tourism::~Tourism() {

}
