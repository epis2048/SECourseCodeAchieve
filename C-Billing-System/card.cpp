#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include "billstd.h"
#include "auth.h"
#include "card.h"
#include "bill.h"

cardList* card_do_addCard(cardList* end_cardList, char password[50], int balance, int billStd, int* cardMaxID, int nowAdminID)
{
	cardList* p;
	p = (cardList*)malloc(sizeof(cardList));//�����ڴ�
	if (p == NULL) {
		cout << "����ʧ�ܣ�" << endl;
		system("pause");
		return end_cardList;
	}
	(*cardMaxID)++;
	p->id = *cardMaxID;
	int c = p->id;
	int i;
	//ѭ�����showID
	for (i = 5; i >= 0; i--) {
		if (c > 0) {
			p->showID[i] = c % 10 + '0';
			c /= 10;
		}
		else {
			p->showID[i] = '0';
		}
	}
	p->showID[6] = '\0';
	strcpy(p->password, password);
	p->balance = balance;
	p->billStd = billStd;
	std::time_t t = std::time(0);
	p->creatTime = t;
	p->adduid = nowAdminID;
	//����һЩû�õĳ�ʼ������֪��Ϊʲô������д�˲�����
	p->totalCharge = 0;
	p->isDel = false;
	p->recentBillTime = -1;
	p->recentChargeTime = -1;
	p->totalChargeTime = 0;
	//���ﵹ�Ҳ�����, Ϊʲô�����ż���ô��...
	p->prev = end_cardList;
	end_cardList = p;
	return end_cardList;
}

cardList* card_do_delCard(cardList* end_cardList, billUnfinishedList* head_billUnfinishedList, int cid, int nowAdminID) {
	bool hasFound = false;
	cardList* p = end_cardList;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			if (bill_query_isUp(head_billUnfinishedList, cid)) {
				cout << "�ÿ������ϻ��������»�����ע����" << endl;
				return end_cardList;
			}
			else if (p->balance != 0) {
				cout << "�ÿ���������Ƿ�ѣ�������ʺ�ע����" << endl;
				return end_cardList;
			}
			else{
				hasFound = true;
				p->isDel = true;
				break;
			}
		}
		p = p->prev;
	}
	if (hasFound) cout << "ע���ɹ���" << endl;
	else cout << "δ�ҵ��ÿ���" << endl;
	return end_cardList;
}

cardList* card_addCard(cardList* end_cardList, billStdList* head_billStdList, int* cardMaxID, int nowAdminID)
{
	system("cls");
	int i;
	int c = *cardMaxID;
	//����һ����һ�ſ��Ŀ���
	char showID[7];
	c++;
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
	char password[50];
	cout << "����" << endl;
	cout << "���ţ�" << showID << endl;
	cout << "���룺";
	cin >> password;
	//cout << password << endl;
	float inputBalance;
	int balance;
	cout << "��ʼ��";
	cin >> inputBalance;
	inputBalance *= 100;
	balance = (int)inputBalance;
	int billStd = 0;
	//��ʾ�Ʒѱ�׼
	char bl_s_ct[25];
	struct tm* ttime;
	adc_showbstd:system("cls");//����һ����ǩ
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
		cout << setw(6) << p->id << setw(12) << p->stdName << setw(26) << bl_s_ct << setw(6) << p->stdUnitCost * 1.0 / 100 << "/" << p->stdUnit << endl;
		p = p->next;
	}
	cout << "��ѡ��Ʒѱ�׼ID��";
	cin >> billStd;
	p = head_billStdList;
	if (!billstd_query_isValid(head_billStdList, billStd)) goto adc_showbstd;//���������ID�治����
	end_cardList = card_do_addCard(end_cardList, password, balance, billStd, cardMaxID, nowAdminID);
	cout << "�����ɹ���" << endl;
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_queryCardList(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, billUnfinishedList* head_billUnfinishedList, int nowAdminID)
{
	system("cls");
	cardList* p = end_cardList;
	string str_billStd;
	char c_s_t[25];
	struct tm* ttime;
	cout << "���б�" << endl;
	cout << setw(6) << "����" << setw(6) << "���" << setw(26) << "�Ʒѱ�׼" << setw(26) << "���ʹ��ʱ��" << setw(12) << "��ǰ�Ƿ��ϻ�" << endl;
	while (1) {
		if (p == NULL) break;
		if (p->isDel) { 
			p = p->prev;
			continue; 
		}
		if(p->recentBillTime < 0){
			strcpy(c_s_t, "���޼�¼");
		}
		else {
			ttime = localtime(&p->recentBillTime);
			strftime(c_s_t, sizeof(c_s_t), "%Y��%m��%d�� %H:%M:%S", ttime);
		}
		str_billStd = billstd_query_nameAndStd(head_billStdList, p->billStd);
		string s;
		if (bill_query_isUp(head_billUnfinishedList, p->id)) {
			s = "��";
		}
		else {
			s = "��";
		}
		cout << setw(6) << p->showID << setw(6) << p->balance * 1.0 / 100 << setw(26) << str_billStd << setw(26) << c_s_t << setw(12) << s << endl;
		p = p->prev;
	}
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_queryCardDetail(cardList* end_cardList, billStdList* head_billStdList, adminList* head_adminList, billUnfinishedList* head_billUnfinishedList, int nowAdminID)
{
	cardList* p = end_cardList;
	int cid;
	bool hasFound = false;
	char c_qcd_ta[25];
	struct tm* ttime;
	system("cls");
	cout << "��ѯ������" << endl;
	cout << "�����뿨�ţ�";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		system("cls");
		cout << "��ѯ�ɹ���" << endl;
		cout << setw(12) << "Name" << setw(26) << "Value" << endl;
		cout << setw(12) << "ID" << setw(26) << p->showID << endl;
		cout << setw(12) << "���" << setw(26) << p->balance*1.0/100 << endl;
		string s;
		if (bill_query_isUp(head_billUnfinishedList, p->id)) {
			s = "��";
		}
		else {
			s = "��";
		}
		cout << setw(12) << "��ǰ�Ƿ��ϻ�" << setw(26) << s << endl;
		cout << setw(12) << "�Ʒѱ�׼" << setw(26) << billstd_query_nameAndStd(head_billStdList, p->billStd )<< endl;
		cout << setw(12) << "�ۼ����Ѵ���" << setw(26) << p->totalChargeTime << endl;
		cout << setw(12) << "�ۼ����ѽ��" << setw(26) << p->totalCharge * 1.0 / 100 << endl;
		if (p->recentBillTime < 0) strcpy(c_qcd_ta, "����");
		else {
			ttime = localtime(&p->recentBillTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y��%m��%d�� %H:%M:%S", ttime);
		}
		cout << setw(12) << "�ϴ�����ʱ��" << setw(26) << c_qcd_ta << endl;
		if (p->recentChargeTime < 0) strcpy(c_qcd_ta, "����");
		else {
			ttime = localtime(&p->recentChargeTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y��%m��%d�� %H:%M:%S", ttime);
		}
		cout << setw(12) << "�ϴγ�ֵʱ��" << setw(26) << c_qcd_ta << endl;
		if (p->creatTime < 0) strcpy(c_qcd_ta, "����");
		else {
			ttime = localtime(&p->creatTime);
			strftime(c_qcd_ta, sizeof(c_qcd_ta), "%Y��%m��%d�� %H:%M:%S", ttime);
		}
		cout << setw(12) << "����ʱ��" << setw(26) << c_qcd_ta << endl;
		cout << setw(12) << "������" << setw(26) << auth_query_getRealnameByID(head_adminList, p->adduid) << endl;
		if (p->isDel) strcpy(c_qcd_ta, "��");
		else strcpy(c_qcd_ta, "��");
		cout << setw(12) << "�Ƿ���Ч" << setw(26) << c_qcd_ta << endl;
	}
	else {
		cout << "δ�ҵ��˿���" << endl;
	}
	system("pause");
	system("cls");
	return end_cardList;
}

cardList* card_editCard(cardList* end_cardList, billStdList* head_billStdList, int nowAdminID)
{
	int cid, c;
	cardList* p = end_cardList;
	billStdList* q = head_billStdList;
	bool hasFound = false;
	char newPw[50];
	char bl_s_ct[25];
	struct tm* ttime;
	int newBS;
	cout << "�����뿨ID��";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid && !p->isDel) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		while (1) {
			system("cls");
			cout << "���ţ�" << p->showID << endl;
			cout << "1. �޸Ŀ�����" << endl;
			cout << "2. �޸Ŀ��Ʒѱ�׼" << endl;
			cout << "0. �޸����" << endl;
			cout << "��ѡ��";
			cin >> c;
			switch (c)
			{
			case 1:
				cout << "�����������룺";
				cin >> newPw;
				strcpy(p->password, newPw);
				cout << "�޸ĳɹ���" << endl;
				break;
			case 2:
				adc_showbstd:system("cls");//����һ����ǩ
				cout << "�Ʒѱ�׼�б�" << endl;
				cout << setw(6) << "ID" << setw(12) << "����" << setw(26) << "����ʱ��" << setw(6) << "    ��׼" << endl;
				while (1) {
					if (q == NULL) break;
					if (q->isDel == true) {
						q = q->next;
						continue;
					}
					ttime = localtime(&q->stdCreateTime);
					strftime(bl_s_ct, sizeof(bl_s_ct), "%Y��%m��%d�� %H:%M:%S", ttime);
					cout << setw(6) << q->id << setw(12) << q->stdName << setw(26) << bl_s_ct << setw(6) << q->stdUnitCost * 1.0 / 100 << "/" << q->stdUnit << endl;
					q = q->next;
				}
				cout << "��ѡ��Ʒѱ�׼ID��";
				cin >> newBS;
				q = head_billStdList;
				if (!billstd_query_isValid(head_billStdList, newBS)) goto adc_showbstd;//���������ID�治����
				p->billStd = newBS;
				cout << "�޸ĳɹ���" << endl;
				break;
			case 0:
				break;
			default:
				cout << "��ѡ����ȷ��ѡ�" << endl;
				break;
			}
			if (c == 0) break;
			system("pause");
		}
	}
	else {
		cout << "δ�ҵ������ѱ�ע��!" << endl;
		system("pause");
	}
	system("cls");
	return end_cardList;
}

cardList* card_delCard(cardList* end_cardList, billUnfinishedList* head_billUnfinishedList, int nowAdminID) 
{
	int cid;
	system("cls");
	cout << "������Ҫע���Ŀ��ţ�";
	cin >> cid;
	end_cardList = card_do_delCard(end_cardList, head_billUnfinishedList,  cid, nowAdminID);
	system("pause");
	system("cls");
	return end_cardList;
}

void card_queryChargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList)
{
	system("cls");
	int cid;
	bool hasFound = false;
	cardList* p = end_cardList;
	cout << "��ѯ����ֵ�˷Ѽ�¼" << endl;
	cout << "�����뿨�ţ�";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		char cl_s_rct[25];
		struct tm* ttime;
		chargeList* q = end_chargeList;
		char ot[10];
		system("cls");
		cout << "���ţ�" << p->showID << endl;
		cout << "��ǰ��" << p->balance * 1.0 / 100 << endl;
		if (p->recentChargeTime < 0) {
			strcpy(cl_s_rct, "���޼�¼");
		}
		else {
			ttime = localtime(&p->recentChargeTime);
			strftime(cl_s_rct, sizeof(cl_s_rct), "%Y��%m��%d�� %H:%M:%S", ttime);
		}
		cout << "�����ֵʱ�䣺" << cl_s_rct << endl;
		cout << setw(4) << "ID" << setw(6) << "����" << setw(10) << "�仯��" << setw(12) << "������" << setw(26) << "����ʱ��" << endl;
		while (1) {
			if (q == NULL) break;
			if (q->cardID == p->id) {
				if (q->chargeType == 1) strcpy(ot, "��ֵ");
				else strcpy(ot, "�˷�");
				ttime = localtime(&q->time);
				strftime(cl_s_rct, sizeof(cl_s_rct), "%Y��%m��%d�� %H:%M:%S", ttime);
				cout << setw(4) << q->id << setw(6) << ot << setw(10) << q->charge * 1.0 / 100 << setw(12) << auth_query_getRealnameByID(head_adminList, q->adminID) << setw(26) << cl_s_rct << endl;
			}
			q = q->prev;
		}
	}
	else {
		cout << "δ�ҵ��ÿ���" << endl;
	}
	system("pause");
	system("cls");
}

void card_queryBillList(cardList* end_cardList, billList* end_billList, billStdList* head_billStdList, adminList* head_adminList, billUnfinishedList* head_billUnfinishedList)
{
	system("cls");
	int cid;
	bool hasFound = false;
	cardList* p = end_cardList;
	cout << "��ѯ�����»���¼" << endl;
	cout << "�����뿨�ţ�";
	cin >> cid;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			break;
		}
		p = p->prev;
	}
	if (hasFound) {
		billList* p = end_billList;
		char c_qbl_ut[25];
		char c_qbl_dt[25];
		struct tm* ttime;
		bool isUp = false;
		billUnfinishedList* q = head_billUnfinishedList;
		while (1) {
			if (q == NULL) break;
			if (q->cardID == cid) {
				isUp = true;
				break;
			}
			q = q->next;
		}
		if (isUp) {
			cout << "�ÿ������ϻ�" << endl;
			ttime = localtime(&q->upTime);
			strftime(c_qbl_ut, sizeof(c_qbl_ut), "%Y��%m��%d�� %H:%M:%S", ttime);
			cout << "�ϻ�ʱ�䣺" << c_qbl_ut << endl;
			cout << "�Ʒѱ�׼��" << billstd_query_nameAndStd(head_billStdList, q->stdID) << endl;
		}
		cout << "���Ѽ�¼��" << endl;
		cout << setw(20) << "�Ʒѱ�׼" << setw(6) << "����" << setw(26) << "�ϻ�ʱ��" << setw(12) << "�ϻ�������" << setw(26) << "�»�ʱ��" << setw(12) << "�»�������" << endl;
		while (1) {
			if (p == NULL) break;
			if (p->cardID == cid) {
				ttime = localtime(&p->upTime);
				strftime(c_qbl_ut, sizeof(c_qbl_ut), "%Y��%m��%d�� %H:%M:%S", ttime);
				ttime = localtime(&p->downTime);
				strftime(c_qbl_dt, sizeof(c_qbl_dt), "%Y��%m��%d�� %H:%M:%S", ttime);
				cout << setw(20) << billstd_query_nameAndStd(head_billStdList, p->stdID) << setw(6) << p->cost * 1.0 / 100 << setw(26) << c_qbl_ut << setw(12) << auth_query_getRealnameByID(head_adminList, p->upAdminID) << setw(26) << c_qbl_dt << setw(12) << auth_query_getRealnameByID(head_adminList, p->downAdminID) << endl;
			}
			p = p->prev;
		}
	}
	else {
		cout << "δ�ҵ��ÿ���" << endl;
	}
	system("pause");
	system("cls");
}

cardList* card_showMainMenu(cardList* end_cardList, billStdList* head_billStdList, billList* end_billList, chargeList* end_chargeList, billUnfinishedList* head_billUnfinishedList, adminList* head_adminList, int* cardMaxID, int nowAdminID)
{
	int c = 0;
	system("cls");
	while (1) {
		cout << "������" << endl;
		cout << "1. ����" << endl;
		cout << "2. ע����" << endl;
		cout << "3. ��ѯ���б�" << endl;
		cout << "4. ��ѯ�����Ѽ�¼" << endl;
		cout << "5. ��ѯ����ֵ�˷Ѽ�¼" << endl;
		cout << "6. ��ѯ������" << endl;
		cout << "7. �޸Ŀ�����/�Ʒѱ�׼" << endl;
		cout << "0. ����" << endl;
		cout << "��ѡ��" ;
		cin >> c;
		switch (c) {
		case 1:
			end_cardList = card_addCard(end_cardList, head_billStdList, cardMaxID, nowAdminID);
			break;
		case 2:
			end_cardList = card_delCard(end_cardList, head_billUnfinishedList, nowAdminID);
			break;
		case 3:
			end_cardList = card_queryCardList(end_cardList, head_billStdList, head_adminList, head_billUnfinishedList, nowAdminID);
			break;
		case 4:
			card_queryBillList(end_cardList, end_billList, head_billStdList, head_adminList, head_billUnfinishedList);
			break;
		case 5:
			card_queryChargeList(end_cardList, end_chargeList, head_adminList);
			break;
		case 6:
			end_cardList = card_queryCardDetail(end_cardList, head_billStdList, head_adminList, head_billUnfinishedList, nowAdminID);
			break;
		case 7:
			end_cardList = card_editCard(end_cardList, head_billStdList, nowAdminID);
			break;
		case 0:
			break;
		default:
			cout << "��������ȷ��ѡ�" << endl;
			system("pause");
			system("cls");
			break;
		}
		if (c == 0) {
			break;
		}
	}
	return end_cardList;
}