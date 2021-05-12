#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <conio.h>
#include "auth.h"
#include "log.h"
using namespace std;

int auth_checkStatus(adminList* head_adminList, int nowAdminID) {
	if (nowAdminID > 0) return 1;
	else return 0;
}

int auth_checkHasAuth(adminList* head_adminList, int nowAdminID, int authID){
	int hasAuth = 0;//��ʼ��һ������Ȩ����Ϣ����ʱ������Ĭ��Ϊ��Ȩ��
	adminList* p = head_adminList;//����һ��ѭ���õ��ڴ�
	while (1) {
		if (p == NULL) break;//ѭ����������ֹ�����ѭ��
		if (p->id == nowAdminID) {//�������ԱID���
			hasAuth = p->authList[authID];//���ù���Ա�Ķ�ӦȨ�����Ȩ�޸�ֵ����ʱ����
			if (p->authList[0] == 1) hasAuth = 1;//authList�����һ���Ӧ��������Ա�����ù���Ա�ǳ�������Ա����һ�ɷ�����Ȩ��
		}
		p = p->next;//��ָ��Ų����һ���ڵ�
	}
	return hasAuth;//���ر�����Ȩ����Ϣ����ʱ����
}

int auth_login(adminList* head_adminList)
{
	cout << "��ӭʹ�üƷ�ϵͳ��" << "���¼��" << endl;
	char username[20];
	cout << "�û���(����exit�˳�����)��";
	cin >> username;
	if (strcmp(username, "exit") == 0) return -1;
	char password[50];
	cout << "���룺";
	//cin >> password;
	inputPassword(password, 50);
	system("cls");
	adminList* p = head_adminList;
	int nowAdminID = 0;
	char al_s_t[25];
	struct tm* ttime;
	time_t t = std::time(0);
	while (1) {
		if (p == NULL) break;
		if ((strcmp(p->username, username) == 0) && (strcmp(p->password, password) == 0)) {
			nowAdminID = p->id;
			cout << "��ӭ��¼��" << p->realname << endl;
			//��LOG
			string s;
			s = p->username;
			s = "����Ա��¼��" + s;
			log_save(s);
			if (p->recentLoginTime < 0) {
				strcpy(al_s_t, "����");
			}
			else {
				ttime = localtime(&p->recentLoginTime);
				strftime(al_s_t, sizeof(al_s_t), "%Y��%m��%d�� %H:%M:%S", ttime);
			}
			cout << "�����½ʱ�䣺" << al_s_t << endl;
			p->recentLoginTime = t;
		}
		p = p->next;
	}
	if (nowAdminID == 0) cout << "�û������������" << endl;
	return nowAdminID;
}

adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID)
{
	adminList* p;
	adminList* q;
	p = (adminList*)malloc(sizeof(adminList));//�����ڴ�
	if (p == NULL) {
		cout << "���ʧ�ܣ�" << endl;
		system("pause");
		return head_adminList;
	}
	//��ʼ������
	(*adminMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->username, username);
	strcpy(p->realname, realname);
	strcpy(p->password, password);
	p->id = *adminMaxID;
	p->createTime = t;
	//��Ҳ��֪��Ϊʲô��������ĳ�ֵû���á���
	p->authList[0] = 0;
	p->authList[1] = 0;
	p->authList[2] = 0;
	p->authList[3] = 0;
	p->authList[4] = 0;
	p->authList[5] = 0;
	if (isSuperAdmin == 1) p->authList[0] = 1;
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
	//��LOG
	string s;
	s = p->username;
	s = "��ӹ���Ա��" + s + " / " + to_string(nowAdminID);
	log_save(s);
	return head_adminList;
}

adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID)
{
	if (head_adminList == NULL)//���Ϊ��ֱ�ӷ���
	{
		return head_adminList;
	}
	adminList* p = head_adminList;
	adminList* q = NULL;
	if (head_adminList->id == delID) {//�����һ�������ɾ����һ��
		string s = head_adminList->username;
		s = "ɾ������Ա��" + s + " / " + to_string(nowAdminID);
		log_save(s);
		q = head_adminList;
		head_adminList = head_adminList->next;
		free(q);
	}
	else {
		while (1) {//������ǣ��ӵڶ��ʼѭ���ж�,��ʼָ��Ϊ��һ��
			if (p->next == NULL) break;
			if (p->next->id == delID) {//���������һ��Ҫ��ɾ������ֱ��ɾ����
				string s = p->next->username;
				s = "ɾ������Ա��" + s + " / " + to_string(nowAdminID);
				log_save(s);
				q = p->next;
				p->next = p->next->next;
				free(q);
				break;
			}
			p = p->next;
		}
	}
	
	return head_adminList;
}

adminList* auth_addAdmin(adminList* head_adminList, int* adminMaxID, int nowAdminID)
{
	char username[20];
	char realname[100];
	char password[50];
	char password2[50];
	int isSuperAdmin = 0;
	adminList* p;
	system("cls");
	addAdminBegin:p = head_adminList;//������һ��goto�ı�ǩ
	cout << "��ӹ���Ա" << endl;
	cout << "�û�����";
	cin >> username;
	//�жϸ��û����Ƿ����
	while (1) {
		if (p == NULL) break;
		if (strcmp(username, "exit") == 0) { //exit�ؼ��ֲ�����
			system("cls");
			cout << "�Ƿ��û������뻻һ��" << endl;
			goto addAdminBegin;
		}
		if (strcmp(p->username, username) == 0) { //�������ظ����û���
			system("cls");
			cout << "���û����Ѵ��ڣ��뻻һ��" << endl;
			goto addAdminBegin;
		}
		p = p->next;
	}
	cout << "��ʵ������";
	cin >> realname;
	aa_in_pw:cout << "���룺";
	inputPassword(password, 50);
	cout << "�������ظ����룺";
	inputPassword(password2, 50);
	if (strcmp(password, password2) != 0) {
		cout << "�������벻һ��" << endl;
		goto aa_in_pw;
	}
	//cin >> password;
	cout << "�Ƿ񳬼�����Ա����Ϊ1����Ϊ0����";
	cin >> isSuperAdmin;
	head_adminList = auth_do_addAdmin(head_adminList, username, realname, password, isSuperAdmin, adminMaxID, nowAdminID);
	system("cls");
	return head_adminList;
}

adminList* auth_editAdmin(adminList* head_adminList, int nowAdminID)
{
	int c,d;
	int hasFound = false;
	char e_un[20];
	char e_rn[100];
	char e_pw[50];
	char e_pw2[50];
	int sb; //û�ã�ȥ��VS���˵ľ���
	adminList* p = head_adminList;
	cout << "������Ҫ�༭�Ĺ���ԱID��";
	cin >> c;
	while (1) {
		if (p == NULL) break;
		if (p->id == c) {
			hasFound = true;
			break;
		}
		p = p->next;
	}
	if (hasFound) {
		system("cls");
		while (1) {
			cout << "�༭����Ա" << endl;
			cout << "����ԱID��" << p->id << " / ����Ա��ʵ������" << p->realname << endl;
			cout << "�༭ѡ�" << endl;
			cout << "1. �û���" << endl;
			cout << "2. ��ʵ����" << endl;
			cout << "3. ����" << endl;
			cout << "4. Ȩ��" << endl;
			cout << "0. �˳��༭" << endl;
			cout << "��ѡ��";
			cin >> d;
			switch(d) {
			case 1:
				cout << "���������û�����";
				cin >> e_un;
				strcpy(p->username, e_un);
				cout << "�༭�ɹ���" << endl;
				system("pause");
				system("cls");
				break;
			case 2:
				cout << "����������ʵ������";
				cin >> e_rn;
				strcpy(p->realname, e_rn);
				cout << "�༭�ɹ���" << endl;
				system("pause");
				system("cls");
				break;
			case 3:
				cout << "�����������룺";
				inputPassword(e_pw, 50);
				cout << "�������ظ����룺";
				inputPassword(e_pw2, 50);
				if (strcmp(e_pw, e_pw2) == 0) {
					strcpy(p->password, e_pw);
					cout << "�༭�ɹ���" << endl;

				}
				else cout << "�޸�ʧ�ܣ��������벻һ��" << endl;
				system("pause");
				system("cls");
				break;
			case 4:
				cout << "�޸�Ȩ�ޣ�0Ϊ��1Ϊ�棩" << endl;
				cout << setw(10) << " " << setw(10) << "����" << setw(10) << "���»�" << setw(10) << "��ֵ�˷�" << setw(10) << "������" << setw(10) << "�Ʒѱ�׼" << setw(10) << "����־" << endl;
				cout << setw(10) << "���У�" << setw(10) << p->authList[0] << setw(10) << p->authList[1] << setw(10) << p->authList[2] << setw(10) << p->authList[3] << setw(10) << p->authList[4] << setw(10) << p->authList[5] << endl;
				cout << setw(10) << "�£�";
				sb = scanf("%d %d %d %d %d %d", &p->authList[0], &p->authList[1], &p->authList[2], &p->authList[3], &p->authList[4], &p->authList[5]);
				system("cls");
				break;
			case 0:
				system("cls");
				break;
			default:
				cout << "�����ѡ�" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (d == 0) break;
		}
		system("cls");
	}
	else {
		cout << "δ�ҵ����û���" << endl;
		system("pause");
		system("cls");
	}
	return head_adminList;
}

adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID)
{
	int delID = 0;
	cout << "������Ҫɾ����ID��" << endl;
	cin >> delID;
	system("cls");
	if (delID == nowAdminID) {
		cout << "����ɾ���Լ���" << endl;
	}
	else { 
		head_adminList = auth_do_delAdmin(head_adminList, delID, nowAdminID);
	}
	return head_adminList;
}

int auth_queryAdminDetail(adminList* head_adminList)
{
	int cid = 0;
	cout << "������Ҫ��ѯ��ϸ��Ϣ��ID��";
	cin >> cid;
	int hasFound = false;
	adminList* p = head_adminList;
	char aqad_c_t[25]; //��ʱ�洢��ʽ��ʱ��ı���
	struct tm* ttime;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			cout << "ID��" << p->id << endl;
			cout << "�û�����" << p->username << endl;
			cout << "��ʵ������" << p->realname << endl;
			//��ʽ��ʱ��
			if (p->createTime > 0) {
				ttime = localtime(&p->createTime);
				strftime(aqad_c_t, sizeof(aqad_c_t), "%Y��%m��%d�� %H:%M:%S", ttime);
			}
			else { strcpy(aqad_c_t, "����"); }
			cout << "�˻�����ʱ�䣺" << aqad_c_t << endl;
			//��ʽ��ʱ��
			if (p->recentLoginTime > 0) {
				ttime = localtime(&p->recentLoginTime);
				strftime(aqad_c_t, sizeof(aqad_c_t), "%Y��%m��%d�� %H:%M:%S", ttime);
			}
			else { strcpy(aqad_c_t, "����"); }
			cout << "�����½ʱ�䣺" << aqad_c_t << endl;
			//���Ȩ��
			if (p->authList[0] == 1) strcpy(aqad_c_t, "��");
			else strcpy(aqad_c_t, "��");
			cout << "�Ƿ񳬹ܣ�" << aqad_c_t << endl;
			if (p->authList[0] != 1) {
				cout << "Ȩ���б�" << endl;
				if (p->authList[1] == 1) strcpy(aqad_c_t, "��");
				else strcpy(aqad_c_t, "��");
				cout << setw(16) << "���»���" << setw(4) << aqad_c_t << endl;
				if (p->authList[2] == 1) strcpy(aqad_c_t, "��");
				else strcpy(aqad_c_t, "��");
				cout << setw(16) << "��ֵ�˷ѣ�" << setw(4) << aqad_c_t << endl;
				if (p->authList[3] == 1) strcpy(aqad_c_t, "��");
				else strcpy(aqad_c_t, "��");
				cout << setw(16) << "������" << setw(4) << aqad_c_t << endl;
				if (p->authList[4] == 1) strcpy(aqad_c_t, "��");
				else strcpy(aqad_c_t, "��");
				cout << setw(16) << "�Ʒѱ�׼����" << setw(4) << aqad_c_t << endl;
				if (p->authList[5] == 1) strcpy(aqad_c_t, "��");
				else strcpy(aqad_c_t, "��");
				cout << setw(16) << "��־��ѯ��" << setw(4) << aqad_c_t << endl;
			}
		}
		p = p->next;
	}
	if (!hasFound) cout << "û�в�ѯҪ�����Ϣ��" << endl;
	system("pause");
	system("cls");
	return 0;
}

adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID){
	int c = 0;
	system("cls");
	while (1) {
		cout << "����Ա��Ϣ��" << endl; 
		cout << setw(12) << "ID" << setw(12) << "�û���" << setw(12) << "��ʵ����" << setw(6) << "����" << endl;
		adminList* p = head_adminList;
		char showIsSA[4];
		while (1) {
			if (p == NULL) break;
			if (p->authList[0] == 1) strcpy(showIsSA, "��");
			else strcpy(showIsSA, "");
			cout << setw(12) << p->id << setw(12) << p->username << setw(12) << p->realname << setw(6) << showIsSA << endl;
			p = p->next;
		}
		cout << "������" << endl;
		cout << "1.��ѯ��ϸ��Ϣ" << endl;
		cout << "2.��ӹ���Ա" << endl;
		cout << "3.�༭����Ա" << endl;
		cout << "4.ɾ������Ա" << endl;
		cout << "0.�������˵�" << endl;
		cout << "��ѡ��";
		cin >> c;
		switch (c) {
		case 1:
			auth_queryAdminDetail(head_adminList);
			break;
		case 2:
			head_adminList = auth_addAdmin(head_adminList, adminMaxID, nowAdminID);
			break;
		case 3:
			head_adminList = auth_editAdmin(head_adminList, nowAdminID);
			break;
		case 4:
			head_adminList = auth_delAdmin(head_adminList, nowAdminID);
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
	return head_adminList;
}

//�������벻�ɼ�
void inputPassword(char password[50], int size) {
	char c;
	int count = 0;
	while ((c = _getch()) != '\r') {

		if (c == 8) { // �˸�
			if (count == 0) {
				continue;
			}
			putchar('\b'); // ����һ��
			putchar(' '); // ���һ���ո�ԭ����*����
			putchar('\b'); // �ٻ���һ��ȴ�����
			count--;
		}
		if (count == size - 1) { // ��󳤶�Ϊsize-1
			continue;
		}
		if ((c >= 33 && c <= 126)) {  // ����ֻ�ɰ���ascii��33-126���ַ�
			putchar('*');  // ���յ�һ���ַ���, ��ӡһ��*
			password[count] = c;
			count++;
		}
	}
	password[count] = '\0';
	cout << endl;
	return;
}

string auth_query_getRealnameByID(adminList* head_adminList, int adminID)
{
	string realname = "δ�ҵ�";
	adminList* p = head_adminList;
	while (1) {
		if (p == NULL) break;
		if (p->id == adminID) {
			realname = p->realname;
			break;
		}
		p = p->next;
	}
	return realname;
}