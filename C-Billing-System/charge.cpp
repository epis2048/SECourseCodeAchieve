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
	cout << "��ֵ" << endl;
	cout << "������Ҫ��ֵ�Ŀ��ţ�";
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
		cout << "δ�ҵ��ÿ���" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	int c;
	float cc;
	cout << "���ţ�" << p->showID << endl;
	cout << "��ǰ��" << p->balance * 1.0 / 100 << endl;
	cout << "������Ҫ��ֵ�Ľ�";
	cin >> cc;
	c = (int)(cc * 100);
	(p->balance) += c;
	std::time_t t = std::time(0);
	p->recentChargeTime = t;
	chargeList* q;
	q = (chargeList*)malloc(sizeof(chargeList));//�����ڴ�
	if (q == NULL) {
		cout << "��ֵʧ�ܣ�" << endl;
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
	cout << "��ֵ�ɹ���" << endl;
	cout << "���������Ϊ��" << p->balance * 1.0 / 100 << endl;
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
	cout << "�˷�" << endl;
	cout << "������Ҫ�˷ѵĿ��ţ�";
	cin >> ccid;
	while (1) {
		if (p == NULL) break;
		if (p->id == ccid) {
			cout << "�����뿨���룺";
			cin >> inpw;
			if (strcmp(inpw, p->password) == 0) {
				hasFoundCard = true;
			}
			else {
				cout << "�������";
				system("pause");
				system("cls");
				return end_chargeList;
			}
			break;
		}
		p = p->prev;
	}
	if (!hasFoundCard) {
		cout << "δ�ҵ��ÿ���" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	system("cls");
	int c;
	float cc;
	cout << "���ţ�" << p->showID << endl;
	cout << "��ǰ��" << p->balance * 1.0 / 100 << endl;
	cout << "������Ҫ�˷ѵĽ�";
	cin >> cc;
	c = (int)(cc * 100);
	if ((p->balance - c) < 0) {
		cout << "����Ǯ������" << endl;
		system("pause");
		system("cls");
		return end_chargeList;
	}
	(p->balance) -= c;
	std::time_t t = std::time(0);
	//p->recentChargeTime = t;//�˷Ѻ󲻸ı������ֵʱ��
	chargeList* q;
	q = (chargeList*)malloc(sizeof(chargeList));//�����ڴ�
	if (q == NULL) {
		cout << "�˷�ʧ�ܣ�" << endl;
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
	cout << "�˷ѳɹ���" << endl;
	cout << "���������Ϊ��" << p->balance * 1.0 / 100 << endl;
	system("pause");
	system("cls");
	return end_chargeList;
}
