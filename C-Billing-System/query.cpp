#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include "query.h"
#include "billstd.h"
#include "auth.h"

using namespace std;


void query_billUnfinishedList(billUnfinishedList* head_billUnfinishedList, billStdList* head_billStdList, adminList* head_adminList)
{
	system("cls");
	cout << "�����ϻ��Ŀ���" << endl;
	billUnfinishedList* p = head_billUnfinishedList;
	char showID[7];
	int i;
	int c;
	char q_bul_sut[25];
	struct tm* ttime;
	cout << setw(6) << "����" << setw(26) << "�Ʒѱ�׼" << setw(26) << "�ϻ�ʱ��" << setw(26) << "�ϻ�����Ա" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//ѭ�����showID
		for (i = 5; i >= 0; i--) {
			if (c > 0) {
				showID[i] = c % 10 + '0';
				c /= 10;
			}
			else {
				showID[i] = '0';
			}
		}
		showID[6] = '\0';
		ttime = localtime(&p->upTime);
		strftime(q_bul_sut, sizeof(q_bul_sut), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(6) << showID << setw(26) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(26) << q_bul_sut << setw(26) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << endl;
		p = p->next;
	}
	system("pause");
}

void query_billList(billList* end_billList, billStdList* head_billStdList, adminList* head_adminList)
{
	system("cls");
	cout << "�ϻ���¼��" << endl;
	billList* p = end_billList;
	char showID[7];
	int i;
	int c;
	char c_qbl_ut[25];
	char c_qbl_dt[25];
	struct tm* ttime;
	cout << setw(8) << "����" << setw(20) << "�Ʒѱ�׼" << setw(6) << "����" << setw(26) << "�ϻ�ʱ��" << setw(12) << "�ϻ�������" << setw(26) << "�»�ʱ��" << setw(12) << "�»�������" << endl;
	while (1) {
		if (p == NULL) break;
		c = p->cardID;
		//ѭ�����showID
		for (i = 5; i >= 0; i--) {
			if (c > 0) {
				showID[i] = c % 10 + '0';
				c /= 10;
			}
			else {
				showID[i] = '0';
			}
		}
		showID[6] = '\0';
		ttime = localtime(&p->upTime);
		ttime = localtime(&p->upTime);
		strftime(c_qbl_ut, sizeof(c_qbl_ut), "%Y��%m��%d�� %H:%M:%S", ttime);
		ttime = localtime(&p->downTime);
		strftime(c_qbl_dt, sizeof(c_qbl_dt), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(8) << showID << setw(20) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(6) << p->cost * 1.0 / 100 << setw(26) << c_qbl_ut << setw(12) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << setw(26) << c_qbl_dt << setw(12) << auth_query_getRealnameByID(head_adminList, p->downAdminID) << endl;
		p = p->prev;
	}
	system("pause");
}

void query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList)
{
	system("cls");
	cout << "�ϻ���¼��" << endl;
	char showID[7];
	int i;
	int c;
	char cl_s_rct[25];
	struct tm* ttime;
	chargeList* q = end_chargeList;
	char ot[10];
	cout << setw(4) << "ID" << setw(8) << "����" << setw(6) << "����" << setw(10) << "�仯��" << setw(12) << "������" << setw(26) << "����ʱ��" << endl;
	while (1) {
		if (q == NULL) break;
		if (q->chargeType == 1) strcpy(ot, "��ֵ");
		else strcpy(ot, "�˷�");
		ttime = localtime(&q->time);
		strftime(cl_s_rct, sizeof(cl_s_rct), "%Y��%m��%d�� %H:%M:%S", ttime);
		cout << setw(4) << q->id << setw(6) << ot << setw(8) << q->cardShowID << setw(10) << q->charge * 1.0 / 100 << setw(12) << auth_query_getRealnameByID(head_adminList, q->adminID) << setw(26) << cl_s_rct << endl;
		q = q->prev;
	}
	system("pause");
}

void query_recentData(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int cd;
	cout << "��ѯͳ��" << endl;
	cout << "������Ҫ��ѯ��������";
	cin >> cd;
	time_t tnow = time(0);
	time_t tstart = tnow - (time_t)cd * 60 * 60 * 24;
	system("cls");
	cout << "��ѯ��� " << cd << " ��" << endl;
	char qcd_t_st[25];
	char qcd_t_et[25];
	struct tm* ttime;
	ttime = localtime(&tstart);
	strftime(qcd_t_st, sizeof(qcd_t_st), "%Y��%m��%d�� %H:%M:%S", ttime);
	ttime = localtime(&tnow);
	strftime(qcd_t_et, sizeof(qcd_t_et), "%Y��%m��%d�� %H:%M:%S", ttime);
	cout << "��ʼʱ�䣺" << qcd_t_st << endl << "����ʱ�䣺" << qcd_t_et << endl;
	int count_charge = 0;//��ֵ��Ǯ��
	int count_fund = 0;//�˿���Ǯ��
	int count_chargeTime = 0;//��ֵ����
	int count_billTime = 0;//���Ѵ���
	int count_bill = 0;//������Ǯ��
	int count_system_balanceNow = 0;//ϵͳ�����п������
	int count_system_admin = 0;//ϵͳ�ڹ���Ա����
	int count_system_cardValid = 0;//ϵͳ����Ч������
	int count_system_card = 0;//ϵͳ�����п�����
	int count_system_bill = 0;//ϵͳ�����Ѽ�¼������
	int count_system_billStdValid = 0;//ϵͳ����Ч�Ʒѱ�׼����
	int count_system_billStd = 0;//ϵͳ�����мƷѱ�׼����
	int count_system_charge = 0;//ϵͳ�ڳ�ֵ��¼������

	//ͳ��count_billTime, count_chargeTime, count_balanceNow, count_system_card, count_system_cardValid
	cardList* cl = end_cardList;
	while (1) {
		if (cl == NULL)break;
		if (cl->recentBillTime >= tstart) count_billTime++;
		if (cl->recentChargeTime >= tstart) count_chargeTime++;
		count_system_balanceNow += cl->balance;
		count_system_card++;
		if (cl->isDel == false) count_system_cardValid++;
		cl = cl->prev;
	}

	//ͳ��count_charge, count_system_charge
	chargeList* cll = end_chargeList;
	while (1) {
		if (cll == NULL)break;
		if (cll->time >= tstart && cll->chargeType == 1) count_charge += cll->charge;
		if (cll->time >= tstart && cll->chargeType == 2) count_fund += cll->charge;
		count_system_charge++;
		cll = cll->prev;
	}

	//ͳ��count_bill, count_system_bill
	billList* bl = end_billList;
	while (1) {
		if (bl == NULL)break;
		if (bl->downTime >= tstart) count_bill += bl->cost;
		count_system_bill++;
		bl = bl->prev;
	}

	//ͳ��count_system_admin
	adminList* al = head_adminList;
	while (1) {
		if (al == NULL) break;
		count_system_admin++;
		al = al->next;
	}

	//ͳ��count_system_billStdValid, count_system_billStd
	billStdList* bsl = head_billStdList;
	while (1) {
		if (bsl == NULL)break;
		count_system_billStd++;
		if (bsl->isDel == false) count_system_billStdValid++;
		bsl = bsl->next;
	}

	cout << endl;
	cout << setw(26) << "Name" << setw(8) << "Value" << endl;
	cout << setw(26) << "���" + to_string(cd) + "����������" << setw(8) << count_billTime << endl;
	cout << setw(26) << "���" + to_string(cd) + "��������Ǯ��" << setw(8) << count_bill * 1.0 / 100 << endl;
	cout << setw(26) << "���" + to_string(cd) + "���ֵ����" << setw(8) << count_chargeTime << endl;
	cout << setw(26) << "���" + to_string(cd) + "���ֵ��Ǯ��" << setw(8) << count_charge * 1.0 / 100 << endl;
	cout << setw(26) << "���" + to_string(cd) + "���˷���Ǯ��" << setw(8) << count_fund * 1.0 / 100 << endl;
	cout << "----------------------------------" << endl;
	cout << setw(26) << "ϵͳ�����п������" << setw(8) << count_system_balanceNow * 1.0 / 100 << endl;
	cout << setw(26) << "ϵͳ����Ч������" << setw(8) << count_system_cardValid << endl;
	cout << setw(26) << "ϵͳ�����п�����" << setw(8) << count_system_card << endl;
	cout << setw(26) << "ϵͳ�����Ѽ�¼������" << setw(8) << count_system_bill << endl;
	cout << setw(26) << "ϵͳ�ڳ�ֵ��¼������" << setw(8) << count_system_charge << endl;
	cout << setw(26) << "ϵͳ�ڹ���Ա����" << setw(8) << count_system_admin << endl;
	cout << setw(26) << "ϵͳ����Ч�Ʒѱ�׼����" << setw(8) << count_system_billStdValid << endl;
	cout << setw(26) << "ϵͳ�����мƷѱ�׼����" << setw(8) << count_system_billStd << endl;

	cout << endl;
	system("pause");
}

void query_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	int c;
	while (1) {
		cout << "��ѯ�˵���" << endl;
		cout << "1. ��ѯ�����ϻ��Ŀ�" << endl;
		cout << "2. ��ѯ�����ϻ���¼" << endl;
		cout << "3. ��ѯ���г�ֵ�˷Ѽ�¼" << endl;
		cout << "4. ��ѯ�����ͳ������" << endl;
		cout << "0. �����ϼ�" << endl;
		cout << "��ѡ��";
		cin >> c;
		switch (c) {
		case 1:
			query_billUnfinishedList(head_billUnfinishedList, head_billStdList, head_adminList);
			system("cls");
			break;
		case 2:
			query_billList(end_billList, head_billStdList, head_adminList);
			system("cls");
			break;
		case 3:
			query_chargeList(end_cardList, end_chargeList, head_adminList);
			system("cls");
			break;
		case 4:
			query_recentData(head_adminList, head_billStdList, end_cardList, end_billList, head_billUnfinishedList, end_chargeList);
			system("cls");
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
	return;
}