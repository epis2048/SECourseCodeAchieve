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
		cout << "------------ ��������ϵͳ ------------" << endl;
		cout << "1. ��ѯ���о���" << endl;
		cout << "2. ��ѯ����·��" << endl;
		cout << "3. ��ѯ������ϸ��Ϣ" << endl;
		cout << "4. ���ξ��㵼��" << endl;
		cout << "5. �������·��" << endl;
		cout << "6. Prim�����������" << endl;
		cout << "0. �˳�ϵͳ" << endl;
		cout << "��ѡ��";
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
			cout << "�����뾰�����ƣ�";
			cin >> vexName;
			T.searchVex(vexName);
			break;
		case 4:
			T.G.printVexs();
			cout << "�����뿪ʼ�ľ������ƣ�";
			cin >> vexName;
			T.doDFS(vexName);
			break;
		case 5:
			T.G.printVexs();
			cout << "�����뿪ʼ�ľ������ƣ�";
			cin >> vexName;
			cout << "����������ľ������ƣ�";
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