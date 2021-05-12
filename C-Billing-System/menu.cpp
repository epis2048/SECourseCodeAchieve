#include <iostream>
#include "data.h"
#include "auth.h"
using namespace std;

int showMenu(adminList* head_adminList, int nowAdminID) {
	cout << "欢迎使用计费系统！" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 1)) cout << "1.上机" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 1)) cout << "2.下机" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 2)) cout << "3.充值" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 2)) cout << "4.退费" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 3)) cout << "5.卡管理" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 4)) cout << "6.计费标准管理" << endl;
	if (auth_checkHasAuth(head_adminList, nowAdminID, 5)) cout << "7.日志查询" << endl;
	if(auth_checkHasAuth(head_adminList, nowAdminID, 0)) cout << "8.权限管理" << endl;
	cout << "9.数据保存" << endl;
	cout << "0.退出登录" << endl;
	int userChoose = -1;
	cout << "请选择：";
	cin >> userChoose;
	return userChoose;
}