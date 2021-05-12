#pragma once
#include <ctime>
#include "data.h"
using namespace std;

//����ʱ��������
void inputPassword(char password[50], int size);
//��ȡ��½״̬
int auth_checkStatus(adminList* head_adminList, int nowAdminID);
//��¼
int auth_login(adminList* head_adminList);
//����Ƿ���ĳ���Ȩ��
int auth_checkHasAuth(adminList* head_adminList, int nowAdminID, int authID);

//��ʾȨ�޹������˵�
adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//��ѯ����Ա
int auth_queryAdminDetail(adminList* head_adminList);
//��ӹ���Ա
adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID);
adminList* auth_addAdmin(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//�༭����Ա
adminList* auth_editAdmin(adminList* head_adminList, int nowAdminID);
//ɾ������Ա
adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID);
adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID);
//API���
string auth_query_getRealnameByID(adminList* head_adminList, int adminID);