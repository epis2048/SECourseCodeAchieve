#include <iostream>
#include "data.h"
#include "auth.h"
using namespace std;

int showMenu(adminList* head_adminList, int nowAdminID) {
	cout << "��ӭʹ�üƷ�ϵͳ��" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 1)) cout << "1.�ϻ�" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 1)) cout << "2.�»�" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 2)) cout << "3.��ֵ" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 2)) cout << "4.�˷�" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 3)) cout << "5.������" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 4)) cout << "6.�Ʒѱ�׼����" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 5)) cout << "7.��־��ѯ" << endl;
	if(auth_checkHasAuth(head_adminList, nowAdminID, 0)) cout << "8.Ȩ�޹���" << endl;
	cout << "9.���ݱ���" << endl;
	cout << "0.�˳���¼" << endl;
	int userChoose = -1;
	cout << "��ѡ��";
	cin >> userChoose;
	return userChoose;
}