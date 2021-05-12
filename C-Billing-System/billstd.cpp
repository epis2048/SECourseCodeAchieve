#include <iostream>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include "billstd.h"
using namespace std;

billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID)
{
	billStdList* p;
	billStdList* q;
	p = (billStdList*)malloc(sizeof(billStdList));//申请内存
	if (p == NULL) {
		cout << "添加失败！" << endl;
		system("pause");
		return head_billStdList;
	}
	//初始化数据
	(*billStdMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->stdName, stdName);
	p->id = *billStdMaxID;
	p->stdCreateTime = t;
	p->stdUnit = stdUnit;
	p->stdUnitCost = stdUnitCost;
	p->isDel = false;
	p->next = NULL;
	//链表里插数据
	if (head_billStdList == NULL) {
		head_billStdList = p;
	}
	else {
		q = head_billStdList;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
	return head_billStdList;
}

billStdList* billstd_do_delBillStd(billStdList* head_billStdList, int delID, int nowAdminID)
{
	billStdList* p = head_billStdList;
	while (1) {
		if (p == NULL) break;
		if (p->id == delID) {
			p->isDel = true;
		}
		p = p->next;
	}
	return head_billStdList;
}

billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID)
{
	system("cls");
	char billStdName[50];
	char stdUnit;
	float stdUnitCostInput;
	int stdUnitCost;
	int sb;//scanf非要返回值。。
	cout << "添加计费标准" << endl;
	cout << "计费标准名称：";
	cin >> billStdName;
	inbstd2:cout << "计费标准(花费/单位、计费单位s,m,h）："; //这有一个标签
	sb = scanf("%f/%c", &stdUnitCostInput, &stdUnit);
	if (!(stdUnit == 'h' || stdUnit == 'm' || stdUnit == 's')) {
		cout << "单位无效！" << endl;
		goto inbstd2;
	}

	stdUnitCostInput *= 100;
	stdUnitCost = (int)stdUnitCostInput;
	head_billStdList = billstd_do_addBillStd(head_billStdList, billStdName, stdUnit, stdUnitCost, billStdMaxID, nowAdminID);
	system("cls");
	cout << "添加成功！" << endl;
	return head_billStdList;
}

billStdList* billstd_delBillStd(billStdList* head_billStdList, int nowAdminID)
{
	int c;
	cout << "请输入要删除的ID：";
	cin >> c;
	head_billStdList = billstd_do_delBillStd(head_billStdList, c, nowAdminID);
	system("cls");
	return head_billStdList;
}

billStdList* billstd_editBillStd(billStdList* head_billStdList, int nowAdminID)
{
	int c;
	int d;
	cout << "请输入要编辑的ID：";
	cin >> c;
	bool hasFound = false;
	char newName[50];
	char newUnit;
	int newUnitCost;
	float newUnitCostInput;
	int sb;//VS非要返回值
	billStdList* p = head_billStdList;
	while (1) {
		if (p == NULL) break;
		if (p->id == c) {
			hasFound = true;
			break;
		}
		p = p->next;
	}
	if (hasFound) {
		while (1) {
			system("cls");
			cout << "标准ID：" << p->id << endl;
			cout << "1. 标准名称：" << p->stdName << endl;
			cout << "2. 标准：" << (p->stdUnitCost)*1.0/100 << "/" << p->stdUnit << endl;
			cout << "0. 退出" << endl;
			cout << "请输入编号：";
			cin >> d;
			switch (d)
			{
			case 1:
				cout << "请输入新名称：";
				cin >> newName;
				strcpy(p->stdName, newName);
				break;
			case 2:
				inbstd:cout << "请输入新的计费标准(花费/单位、计费单位s,m,h）："; //这有一个标签
				sb = scanf("%f/%c", &newUnitCostInput, &newUnit);
				if (!(newUnit == 'h' || newUnit == 'm' || newUnit == 's')) {
					cout << "单位无效！" << endl;
					goto inbstd;
				}
				newUnitCostInput *= 100;
				newUnitCost = (int)newUnitCostInput;
				p->stdUnit = newUnit;
				p->stdUnitCost = newUnitCost;
				break;
			case 0:
				break;
			default:
				cout << "选择错误！" << endl;
				system("pause");
				break;
			}
			if (d == 0) {
				break;
			}
		}
	}
	else {
		cout << "没有找到要编辑的标准！";
		system("pause");
	}
	system("cls");
	return head_billStdList;
}

billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	char bl_s_ct[25];
	struct tm* ttime;
	while (1) {
		cout << "计费标准列表：" << endl;
		cout << setw(6) << "ID" << setw(12) << "名称" << setw(26) << "创建时间" << setw(6) << "    标准" << endl;
		billStdList* p = head_billStdList;
		while (1) {
			if (p == NULL) break;
			if (p->isDel == true) {
				p = p->next;
				continue;
			}
			ttime = localtime(&p->stdCreateTime);
			strftime(bl_s_ct, sizeof(bl_s_ct), "%Y年%m月%d日 %H:%M:%S", ttime);
			cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost*1.0/100 << "/" << p->stdUnit << endl;
			p = p->next;
		}
		cout << "操作：" << endl;
		cout << "1.添加计费标准" << endl;
		cout << "2.编辑计费标准" << endl;
		cout << "3.删除计费标准" << endl;
		cout << "0.返回主菜单" << endl;
		cout << "请选择：";
		cin >> c;
		switch (c) {
		case 1:
			head_billStdList = billstd_addBillStd(head_billStdList, billStdMaxID, nowAdminID);
			break;
		case 2:
			head_billStdList = billstd_editBillStd(head_billStdList, nowAdminID);
			break;
		case 3:
			head_billStdList = billstd_delBillStd(head_billStdList, nowAdminID);
			break;
		case 0:
			break;
		default:
			cout << "请选择正确的选项！" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (c == 0) {
			break;
		}
	}
	return head_billStdList;
}

string billstd_query_nameAndStd(billStdList* head_billStdList, int stdID)
{
	string ret = "未找到该标准！";
	billStdList* p = head_billStdList;
	while (1) {
		if (p == NULL) break;
		if (p->id == stdID) {
			ret = p->stdName;
			ret = ret + ": ";
			ret = ret + intTranStr(p->stdUnitCost*1.0/100) + '/' + p->stdUnit;
			if (p->isDel) ret = ret + " (已失效)";
			break;
		}
		p = p->next;
	}
	return ret;
}

bool billstd_query_isValid(billStdList* head_billStdList, int stdID)
{
	billStdList* p = head_billStdList;
	bool isV = false;
	while (1) {
		if (p == NULL) break;
		if (p->id == stdID && !p->isDel) {
			isV = true;
		}
		p = p->next;
	}
	return isV;
}

string intTranStr(double integer) {
	stringstream ss;
	ss << integer;
	return ss.str();
}