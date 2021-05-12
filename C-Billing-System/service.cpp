#include <iostream>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include "service.h"
constexpr auto File_adminList = "data/adminList.dat";
constexpr auto File_billStdList = "data/billStdList.dat";
constexpr auto File_cardList = "data/cardList.dat";
constexpr auto File_chargeList = "data/chargeList.dat";
constexpr auto File_billUnfinishedList = "data/billUnfList.dat";
constexpr auto File_billList = "data/billList.dat";
using namespace std;

adminList* read_auth_adminList(int* adminMaxID)
{
	adminList* head_adminList = NULL;
	adminList* p;
	adminList* q;
	int id;
	char username[20];
	char realname[100];
	char password[50];
	time_t rlt;
	time_t ct;
	int authList[6] = { 0, 0, 0, 0, 0, 0 };
	//��ȡ����
	FILE* fp;
	int i;
	if ((fp = fopen(File_adminList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		*(adminMaxID) = id;
		fscanf(fp, "%s", username);
		fscanf(fp, "%s", realname);
		fscanf(fp, "%s", password);
		fscanf(fp, "%lld", &rlt);
		fscanf(fp, "%lld", &ct);
		for (i = 0; i <= 5; i++) fscanf(fp, "%d", &authList[i]);
		//������
		p = (adminList*)malloc(sizeof(adminList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->username, username);
		strcpy(p->realname, realname);
		strcpy(p->password, password);
		p->id = id;
		p->createTime = ct;
		p->recentLoginTime = rlt;
		for (i = 0; i <= 5; i++) p->authList[i] = authList[i];
		p->next = NULL;
		//�����������
		if (head_adminList == NULL) {
			head_adminList = p;
		}
		else {
			q = head_adminList;
			while (q->next != NULL) {
				q = q->next;
			}
			q->next = p;
		}
	}
	fclose(fp);
	return head_adminList;
}

billStdList* read_billStd_billStdList(int* billStdMaxID)
{
	billStdList* head_billStdList = NULL;
	billStdList* p;
	billStdList* q;
	int id;
	char stdName[50];
	time_t stdCreateTime;
	char stdUnit;
	int stdUnitCost;
	int delInt;
	bool isDel = false;
	//��ȡ����
	FILE* fp;
	if ((fp = fopen(File_billStdList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		*(billStdMaxID) = id;
		fscanf(fp, "%s", stdName);
		fscanf(fp, "%lld", &stdCreateTime);
		fscanf(fp, "%c", &stdUnit);//���Իس���ʲôë��
		fscanf(fp, "%c", &stdUnit);
		fscanf(fp, "%d", &stdUnitCost);
		fscanf(fp, "%d", &delInt);
		if (delInt == 1) isDel = true;
		else isDel = false;
		//������
		p = (billStdList*)malloc(sizeof(billStdList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->stdName, stdName);
		p->id = id;
		p->stdCreateTime = stdCreateTime;
		p->stdUnit = stdUnit;
		p->stdUnitCost = stdUnitCost;
		p->isDel = isDel;
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
	}
	fclose(fp);
	return head_billStdList;
}

cardList* read_card_cardList(int* cardMaxID)
{
	cardList* end_cardList = NULL;
	cardList* p;
	int id;//�����ÿ��ţ�ʵ������
	char showID[7];//��ʾ�����뿨�ţ���λ������6λǰ�油0
	char password[50];//������
	int balance;//����λ�Ƿ֣�һ��Ǯ100
	int billStd;//�˿��ļƷѱ�׼
	int totalCharge = 0;//�ۼ�����Ǯ������λ�Ƿ֣�һ��Ǯ100
	int totalChargeTime = 0;//�ۼ����Ѵ���
	time_t creatTime;//����ʱ��
	int adduid;//��������ԱID
	time_t recentBillTime;//�ϴ�����ʱ�䣬�Խ���ʱ�����
	time_t recentChargeTime;//�ϴγ�ֵʱ��
	int delInt;
	bool isDel = false;
	//��ȡ����
	FILE* fp;
	if ((fp = fopen(File_cardList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		if(id > * (cardMaxID)) *(cardMaxID) = id;
		fscanf(fp, "%s", showID);
		fscanf(fp, "%s", password);
		fscanf(fp, "%d", &balance);
		fscanf(fp, "%d", &billStd);
		fscanf(fp, "%d", &totalCharge);
		fscanf(fp, "%d", &totalChargeTime);
		fscanf(fp, "%lld", &creatTime);
		fscanf(fp, "%d", &adduid);
		fscanf(fp, "%lld", &recentBillTime);
		fscanf(fp, "%lld", &recentChargeTime);
		fscanf(fp, "%d", &delInt);
		if (delInt == 1) isDel = true;
		else isDel = false;
		//������
		p = (cardList*)malloc(sizeof(cardList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->showID, showID);
		strcpy(p->password, password);
		p->id = id;
		p->balance = balance;
		p->billStd = billStd;
		p->totalCharge = totalCharge;
		p->creatTime = creatTime;
		p->totalChargeTime = totalChargeTime;
		p->adduid = adduid;
		p->recentBillTime = recentBillTime;
		p->recentChargeTime = recentChargeTime;
		p->isDel = isDel;
		//�����������
		p->prev = end_cardList;
		end_cardList = p;
	}
	fclose(fp);
	return end_cardList;
}

chargeList* read_charge_chargeList(int* chargeMaxID)
{
	chargeList* end_chargeList = NULL;
	chargeList* p;
	int id;
	int cardID;
	char cardShowID[7];
	int chargeType;
	int charge;
	int adminID;
	time_t time;
	//��ȡ����
	FILE* fp;
	if ((fp = fopen(File_chargeList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		*(chargeMaxID) = id;
		fscanf(fp, "%d", &cardID);
		fscanf(fp, "%s", &cardShowID);
		fscanf(fp, "%d", &chargeType);
		fscanf(fp, "%d", &charge);
		fscanf(fp, "%d", &adminID);
		fscanf(fp, "%lld", &time);
		//������
		p = (chargeList*)malloc(sizeof(chargeList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		strcpy(p->cardShowID, cardShowID);
		p->id = id;
		p->cardID = cardID;
		p->chargeType = chargeType;
		p->charge = charge;
		p->adminID = adminID;
		p->time = time;
		//�����������
		p->prev = end_chargeList;
		end_chargeList = p;
	}
	fclose(fp);
	return end_chargeList;
}

billUnfinishedList* read_bill_billUnfinishedList()
{
	billUnfinishedList* head_billUnfinishedList = NULL;
	billUnfinishedList* p;
	billUnfinishedList* q;
	int stdID;
	int cardID;
	int upAdminID;
	time_t upTime;
	//��ȡ����
	FILE* fp;
	if ((fp = fopen(File_billUnfinishedList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &stdID);
		if (stdID < 0) break;
		fscanf(fp, "%d", &cardID);
		fscanf(fp, "%d", &upAdminID);
		fscanf(fp, "%lld", &upTime);
		//������
		p = (billUnfinishedList*)malloc(sizeof(billUnfinishedList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		p->cardID = cardID;
		p->stdID = stdID;
		p->upAdminID = upAdminID;
		p->upTime = upTime;
		p->next = NULL;
		//�����������
		if (head_billUnfinishedList == NULL) {
			head_billUnfinishedList = p;
		}
		else {
			q = head_billUnfinishedList;
			while (q->next != NULL) {
				q = q->next;
			}
			q->next = p;
		}
	}
	fclose(fp);
	return head_billUnfinishedList;
}

billList* read_bill_billList(int* billMaxID)
{
	billList* end_billList = NULL;
	billList* p;
	int id;//ID��ʵ������
	int stdID;//�Ʒѱ�׼ID
	char stdUnit;//�Ʒѵ�λ(�룺s���֣�m��ʱ��h)
	int stdUnitCost;//ÿ��λ����Ǯ, ��λ�Ƿ֣�1Ԫ��100
	int cardID;//����
	int cost;//�����˶���Ǯ����λ�Ƿ֣�һԪ100
	int upAdminID;//�ϻ�����ԱID
	time_t upTime;//�ϻ�ʱ��
	int downAdminID;//�»�����ԱID
	time_t downTime;//�»�ʱ��
	//��ȡ����
	FILE* fp;
	if ((fp = fopen(File_billList, "r")) == NULL) {
		cout << "��ʼ��ʧ�ܣ�" << endl;
		system("pause");
		return NULL;
	}
	while (1) {
		//��ȡ
		fscanf(fp, "%d", &id);
		if (id < 0) break;
		if (id > * (billMaxID))* (billMaxID) = id;
		fscanf(fp, "%d", &stdID);
		fscanf(fp, "%c", &stdUnit);//Ԥ�����Իس�
		fscanf(fp, "%c", &stdUnit);
		fscanf(fp, "%d", &stdUnitCost);
		fscanf(fp, "%d", &cardID);
		fscanf(fp, "%d", &cost);
		fscanf(fp, "%d", &upAdminID);
		fscanf(fp, "%lld", &upTime);
		fscanf(fp, "%d", &downAdminID);
		fscanf(fp, "%lld", &downTime);
		//������
		p = (billList*)malloc(sizeof(billList));//�����ڴ�
		if (p == NULL) {
			cout << "��ʼ��ʧ�ܣ�" << endl;
			system("pause");
			return NULL;
		}
		p->id = id;
		p->stdID = stdID;
		p->stdUnit = stdUnit;
		p->stdUnitCost = stdUnitCost;
		p->cardID = cardID;
		p->cost = cost;
		p->upAdminID = upAdminID;
		p->upTime = upTime;
		p->downAdminID = downAdminID;
		p->downTime = downTime;
		//�����������
		p->prev = end_billList;
		end_billList = p;
	}
	fclose(fp);
	return end_billList;
}

bool save_auth_adminList(adminList* head_adminList) {
	adminList* p = head_adminList;
	FILE* fp;
	int i;
	if ((fp = fopen(File_adminList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->username);
		fprintf(fp, "%s\n", p->realname);
		fprintf(fp, "%s\n", p->password);
		fprintf(fp, "%lld\n", p->recentLoginTime);
		fprintf(fp, "%lld\n", p->createTime);
		for(i=0;i<=5;i++) fprintf(fp, "%d\n", p->authList[i]);
		p = p->next;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_billStd_billStdList(billStdList* head_billStdList) {
	billStdList* p = head_billStdList;
	FILE* fp;
	if ((fp = fopen(File_billStdList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->stdName);
		fprintf(fp, "%lld\n", p->stdCreateTime);
		fprintf(fp, "%c\n", p->stdUnit);
		fprintf(fp, "%d\n", p->stdUnitCost);
		fprintf(fp, "%d\n", p->isDel);
		p = p->next;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_card_cardList(cardList* end_cardList) {
	cardList* p = end_cardList;
	FILE* fp;
	if ((fp = fopen(File_cardList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%s\n", p->showID);
		fprintf(fp, "%s\n", p->password);
		fprintf(fp, "%d\n", p->balance);
		fprintf(fp, "%d\n", p->billStd);
		fprintf(fp, "%d\n", p->totalCharge);
		fprintf(fp, "%d\n", p->totalChargeTime);
		fprintf(fp, "%lld\n", p->creatTime);
		fprintf(fp, "%d\n", p->adduid);
		fprintf(fp, "%lld\n", p->recentBillTime);
		fprintf(fp, "%lld\n", p->recentChargeTime);
		fprintf(fp, "%d\n", p->isDel);
		p = p->prev;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_charge_chargeList(chargeList* end_chargeList)
{
	chargeList* p = end_chargeList;
	FILE* fp;
	if ((fp = fopen(File_chargeList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%d\n", p->cardID);
		fprintf(fp, "%s\n", p->cardShowID);
		fprintf(fp, "%d\n", p->chargeType);
		fprintf(fp, "%d\n", p->charge);
		fprintf(fp, "%d\n", p->adminID);
		fprintf(fp, "%lld\n", p->time);
		p = p->prev;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_bill_billUnfinishedList(billUnfinishedList* head_billUnfinishedList)
{
	billUnfinishedList* p = head_billUnfinishedList;
	FILE* fp;
	if ((fp = fopen(File_billUnfinishedList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->stdID);
		fprintf(fp, "%d\n", p->cardID);
		fprintf(fp, "%d\n", p->upAdminID);
		fprintf(fp, "%lld\n", p->upTime);
		p = p->next;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

bool save_bill_billList(billList* end_billList)
{
	billList* p = end_billList;
	FILE* fp;
	if ((fp = fopen(File_billList, "w+")) == NULL) {
		return false;
	}
	while (1) {
		if (p == NULL) break;
		fprintf(fp, "%d\n", p->id);
		fprintf(fp, "%d\n", p->stdID);
		fprintf(fp, "%c\n", p->stdUnit);
		fprintf(fp, "%d\n", p->stdUnit);
		fprintf(fp, "%d\n", p->cardID);
		fprintf(fp, "%d\n", p->cost);
		fprintf(fp, "%d\n", p->upAdminID);
		fprintf(fp, "%lld\n", p->upTime);
		fprintf(fp, "%d\n", p->downAdminID);
		fprintf(fp, "%lld\n", p->downTime);
		p = p->prev;
	}
	fprintf(fp, "-1\n");
	fclose(fp);
	return true;
}

void save_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList)
{
	system("cls");
	cout << "���ݱ��棺" << endl;
	//adminList
	cout << "����adminList...";
	if (save_auth_adminList(head_adminList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//billStdList
	cout << "����billStdList...";
	if (save_billStd_billStdList(head_billStdList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//cardList
	cout << "����cardList...";
	if (save_card_cardList(end_cardList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//chargeList
	cout << "����chargeList...";
	if (save_charge_chargeList(end_chargeList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//billUnfinishedList
	cout << "����billUnfinishedList...";
	if (save_bill_billUnfinishedList(head_billUnfinishedList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//billList
	cout << "����billList...";
	if (save_bill_billList(end_billList)) cout << " �ɹ���" << endl;
	else cout << " ʧ�ܣ�" << endl;
	//Finish
	cout << "������ɣ�" << endl;
	system("pause");
}