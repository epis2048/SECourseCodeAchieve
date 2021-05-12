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
	p = (billStdList*)malloc(sizeof(billStdList));//�����ڴ�
	if (p == NULL) {
		cout << "���ʧ�ܣ�" << endl;
		system("pause");
		return head_billStdList;
	}
	//��ʼ������
	(*billStdMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->stdName, stdName);
	p->id = *billStdMaxID;
	p->stdCreateTime = t;
	p->stdUnit = stdUnit;
	p->stdUnitCost = stdUnitCost;
	p->isDel = false;
	p->next = NULL;
	//�����������
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
	int sb;//scanf��Ҫ����ֵ����
	cout << "��ӼƷѱ�׼" << endl;
	cout << "�Ʒѱ�׼���ƣ�";
	cin >> billStdName;
	inbstd2:cout << "�Ʒѱ�׼(����/��λ���Ʒѵ�λs,m,h����"; //����һ����ǩ
	sb = scanf("%f/%c", &stdUnitCostInput, &stdUnit);
	if (!(stdUnit == 'h' || stdUnit == 'm' || stdUnit == 's')) {
		cout << "��λ��Ч��" << endl;
		goto inbstd2;
	}

	stdUnitCostInput *= 100;
	stdUnitCost = (int)stdUnitCostInput;
	head_billStdList = billstd_do_addBillStd(head_billStdList, billStdName, stdUnit, stdUnitCost, billStdMaxID, nowAdminID);
	system("cls");
	cout << "��ӳɹ���" << endl;
	return head_billStdList;
}

billStdList* billstd_delBillStd(billStdList* head_billStdList, int nowAdminID)
{
	int c;
	cout << "������Ҫɾ����ID��";
	cin >> c;
	head_billStdList = billstd_do_delBillStd(head_billStdList, c, nowAdminID);
	system("cls");
	return head_billStdList;
}

billStdList* billstd_editBillStd(billStdList* head_billStdList, int nowAdminID)
{
	int c;
	int d;
	cout << "������Ҫ�༭��ID��";
	cin >> c;
	bool hasFound = false;
	char newName[50];
	char newUnit;
	int newUnitCost;
	float newUnitCostInput;
	int sb;//VS��Ҫ����ֵ
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
			cout << "��׼ID��" << p->id << endl;
			cout << "1. ��׼���ƣ�" << p->stdName << endl;
			cout << "2. ��׼��" << (p->stdUnitCost)*1.0/100 << "/" << p->stdUnit << endl;
			cout << "0. �˳�" << endl;
			cout << "�������ţ�";
			cin >> d;
			switch (d)
			{
			case 1:
				cout << "�����������ƣ�";
				cin >> newName;
				strcpy(p->stdName, newName);
				break;
			case 2:
				inbstd:cout << "�������µļƷѱ�׼(����/��λ���Ʒѵ�λs,m,h����"; //����һ����ǩ
				sb = scanf("%f/%c", &newUnitCostInput, &newUnit);
				if (!(newUnit == 'h' || newUnit == 'm' || newUnit == 's')) {
					cout << "��λ��Ч��" << endl;
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
				cout << "ѡ�����" << endl;
				system("pause");
				break;
			}
			if (d == 0) {
				break;
			}
		}
	}
	else {
		cout << "û���ҵ�Ҫ�༭�ı�׼��";
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
		cout << "�Ʒѱ�׼�б�" << endl;
		cout << setw(6) << "ID" << setw(12) << "����" << setw(26) << "����ʱ��" << setw(6) << "    ��׼" << endl;
		billStdList* p = head_billStdList;
		while (1) {
			if (p == NULL) break;
			if (p->isDel == true) {
				p = p->next;
				continue;
			}
			ttime = localtime(&p->stdCreateTime);
			strftime(bl_s_ct, sizeof(bl_s_ct), "%Y��%m��%d�� %H:%M:%S", ttime);
			cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost*1.0/100 << "/" << p->stdUnit << endl;
			p = p->next;
		}
		cout << "������" << endl;
		cout << "1.��ӼƷѱ�׼" << endl;
		cout << "2.�༭�Ʒѱ�׼" << endl;
		cout << "3.ɾ���Ʒѱ�׼" << endl;
		cout << "0.�������˵�" << endl;
		cout << "��ѡ��";
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
			cout << "��ѡ����ȷ��ѡ�" << endl;
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
	string ret = "δ�ҵ��ñ�׼��";
	billStdList* p = head_billStdList;
	while (1) {
		if (p == NULL) break;
		if (p->id == stdID) {
			ret = p->stdName;
			ret = ret + ": ";
			ret = ret + intTranStr(p->stdUnitCost*1.0/100) + '/' + p->stdUnit;
			if (p->isDel) ret = ret + " (��ʧЧ)";
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