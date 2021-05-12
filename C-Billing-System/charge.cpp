#include <iostream>
#include "charge.h"
#include "card.h"

using namespace std;

chargeList* charge_reCharge(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID)
{
	int ccid;
	cardList* p = end_cardList;
	bool hasFoundCard = false;
	system("cls");
	cout << "充值" << endl;
	cout << "请输入要充值的卡号：";
	cin >> ccid;
	while (1) {
		if (p == NULL) break;
		if (p->id == ccid) {
			hasFoundCard = true;
			break;
		}
		p = p->prev;
	}
	if (!hasFoundCard) {
		cout << "未找到该卡！" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	int c;
	float cc;
	cout << "卡号：" << p->showID << endl;
	cout << "当前余额：" << p->balance * 1.0 / 100 << endl;
	cout << "请输入要充值的金额：";
	cin >> cc;
	c = (int)(cc * 100);
	(p->balance) += c;
	std::time_t t = std::time(0);
	p->recentChargeTime = t;
	chargeList* q;
	q = (chargeList*)malloc(sizeof(chargeList));//申请内存
	if (q == NULL) {
		cout << "充值失败！" << endl;
		system("pause");
		return end_chargeList;
	}
	(*chargeMaxID)++;
	q->id = *chargeMaxID;
	q->cardID = p->id;
	strcpy(q->cardShowID, p->showID);
	q->chargeType = 1;
	q->charge = c;
	q->adminID = nowAdminID;
	q->time = t;
	q->prev = end_chargeList;
	end_chargeList = q;
	cout << "充值成功！" << endl;
	cout << "操作后余额为：" << p->balance * 1.0 / 100 << endl;
	system("pause");
	system("cls");
	return end_chargeList;
}

chargeList* charge_reFund(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID)
{
	int ccid;
	cardList* p = end_cardList;
	bool hasFoundCard = false;
	char inpw[50];
	system("cls");
	cout << "退费" << endl;
	cout << "请输入要退费的卡号：";
	cin >> ccid;
	while (1) {
		if (p == NULL) break;
		if (p->id == ccid) {
			cout << "请输入卡密码：";
			cin >> inpw;
			if (strcmp(inpw, p->password) == 0) {
				hasFoundCard = true;
			}
			else {
				cout << "密码错误！";
				system("pause");
				system("cls");
				return end_chargeList;
			}
			break;
		}
		p = p->prev;
	}
	if (!hasFoundCard) {
		cout << "未找到该卡！" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	system("cls");
	int c;
	float cc;
	cout << "卡号：" << p->showID << endl;
	cout << "当前余额：" << p->balance * 1.0 / 100 << endl;
	cout << "请输入要退费的金额：";
	cin >> cc;
	c = (int)(cc * 100);
	if ((p->balance - c) < 0) {
		cout << "卡里钱不够！" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	(p->balance) -= c;
	std::time_t t = std::time(0);
	//p->recentChargeTime = t;//退费后不改变最近充值时间
	chargeList* q;
	q = (chargeList*)malloc(sizeof(chargeList));//申请内存
	if (q == NULL) {
		cout << "退费失败！" << endl;
		system("pause");
		return end_chargeList;
	}
	(*chargeMaxID)++;
	q->id = *chargeMaxID;
	q->cardID = p->id;
	strcpy(q->cardShowID, p->showID);
	q->chargeType = 2;
	q->charge = -c;
	q->adminID = nowAdminID;
	q->time = t;
	q->prev = end_chargeList;
	end_chargeList = q;
	cout << "退费成功！" << endl;
	cout << "操作后余额为：" << p->balance * 1.0 / 100 << endl;
	system("pause");
	system("cls");
	return end_chargeList;
}
