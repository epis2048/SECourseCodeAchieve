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
	int hasAuth = 0;//初始化一个保存权限信息的临时变量，默认为无权限
	adminList* p = head_adminList;//声明一个循环用的内存
	while (1) {
		if (p == NULL) break;//循环到链表终止后结束循环
		if (p->id == nowAdminID) {//如果管理员ID相符
			hasAuth = p->authList[authID];//将该管理员的对应权限项的权限赋值到临时变量
			if (p->authList[0] == 1) hasAuth = 1;//authList数组第一项对应超级管理员，若该管理员是超级管理员，则一律返回有权限
		}
		p = p->next;//将指针挪到下一个节点
	}
	return hasAuth;//返回保存了权限信息的临时变量
}

int auth_login(adminList* head_adminList)
{
	cout << "欢迎使用计费系统！" << "请登录！" << endl;
	char username[20];
	cout << "用户名(输入exit退出程序)：";
	cin >> username;
	if (strcmp(username, "exit") == 0) return -1;
	char password[50];
	cout << "密码：";
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
			cout << "欢迎登录，" << p->realname << endl;
			//存LOG
			string s;
			s = p->username;
			s = "管理员登录：" + s;
			log_save(s);
			if (p->recentLoginTime < 0) {
				strcpy(al_s_t, "暂无");
			}
			else {
				ttime = localtime(&p->recentLoginTime);
				strftime(al_s_t, sizeof(al_s_t), "%Y年%m月%d日 %H:%M:%S", ttime);
			}
			cout << "最近登陆时间：" << al_s_t << endl;
			p->recentLoginTime = t;
		}
		p = p->next;
	}
	if (nowAdminID == 0) cout << "用户名或密码错误！" << endl;
	return nowAdminID;
}

adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID)
{
	adminList* p;
	adminList* q;
	p = (adminList*)malloc(sizeof(adminList));//申请内存
	if (p == NULL) {
		cout << "添加失败！" << endl;
		system("pause");
		return head_adminList;
	}
	//初始化数据
	(*adminMaxID)++;
	std::time_t t = std::time(0);
	strcpy(p->username, username);
	strcpy(p->realname, realname);
	strcpy(p->password, password);
	p->id = *adminMaxID;
	p->createTime = t;
	//我也不知道为什么定义里面的初值没管用。。
	p->authList[0] = 0;
	p->authList[1] = 0;
	p->authList[2] = 0;
	p->authList[3] = 0;
	p->authList[4] = 0;
	p->authList[5] = 0;
	if (isSuperAdmin == 1) p->authList[0] = 1;
	p->next = NULL;
	//链表里插数据
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
	//存LOG
	string s;
	s = p->username;
	s = "添加管理员：" + s + " / " + to_string(nowAdminID);
	log_save(s);
	return head_adminList;
}

adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID)
{
	if (head_adminList == NULL)//如果为空直接返回
	{
		return head_adminList;
	}
	adminList* p = head_adminList;
	adminList* q = NULL;
	if (head_adminList->id == delID) {//如果第一项就是那删除第一项
		string s = head_adminList->username;
		s = "删除管理员：" + s + " / " + to_string(nowAdminID);
		log_save(s);
		q = head_adminList;
		head_adminList = head_adminList->next;
		free(q);
	}
	else {
		while (1) {//如果不是，从第二项开始循环判断,初始指针为第一项
			if (p->next == NULL) break;
			if (p->next->id == delID) {//如果他的下一项要被删除，就直接删除它
				string s = p->next->username;
				s = "删除管理员：" + s + " / " + to_string(nowAdminID);
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
	addAdminBegin:p = head_adminList;//这里有一个goto的标签
	cout << "添加管理员" << endl;
	cout << "用户名：";
	cin >> username;
	//判断该用户名是否存在
	while (1) {
		if (p == NULL) break;
		if (strcmp(username, "exit") == 0) { //exit关键字不能用
			system("cls");
			cout << "非法用户名！请换一个" << endl;
			goto addAdminBegin;
		}
		if (strcmp(p->username, username) == 0) { //不能有重复的用户名
			system("cls");
			cout << "该用户名已存在！请换一个" << endl;
			goto addAdminBegin;
		}
		p = p->next;
	}
	cout << "真实姓名：";
	cin >> realname;
	aa_in_pw:cout << "密码：";
	inputPassword(password, 50);
	cout << "请输入重复密码：";
	inputPassword(password2, 50);
	if (strcmp(password, password2) != 0) {
		cout << "两次密码不一致" << endl;
		goto aa_in_pw;
	}
	//cin >> password;
	cout << "是否超级管理员（是为1，否为0）：";
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
	int sb; //没用，去掉VS烦人的警告
	adminList* p = head_adminList;
	cout << "请输入要编辑的管理员ID：";
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
			cout << "编辑管理员" << endl;
			cout << "管理员ID：" << p->id << " / 管理员真实姓名：" << p->realname << endl;
			cout << "编辑选项：" << endl;
			cout << "1. 用户名" << endl;
			cout << "2. 真实姓名" << endl;
			cout << "3. 密码" << endl;
			cout << "4. 权限" << endl;
			cout << "0. 退出编辑" << endl;
			cout << "请选择：";
			cin >> d;
			switch(d) {
			case 1:
				cout << "请输入新用户名：";
				cin >> e_un;
				strcpy(p->username, e_un);
				cout << "编辑成功！" << endl;
				system("pause");
				system("cls");
				break;
			case 2:
				cout << "请输入新真实姓名：";
				cin >> e_rn;
				strcpy(p->realname, e_rn);
				cout << "编辑成功！" << endl;
				system("pause");
				system("cls");
				break;
			case 3:
				cout << "请输入新密码：";
				inputPassword(e_pw, 50);
				cout << "请输入重复密码：";
				inputPassword(e_pw2, 50);
				if (strcmp(e_pw, e_pw2) == 0) {
					strcpy(p->password, e_pw);
					cout << "编辑成功！" << endl;

				}
				else cout << "修改失败！两次密码不一致" << endl;
				system("pause");
				system("cls");
				break;
			case 4:
				cout << "修改权限（0为否，1为真）" << endl;
				cout << setw(10) << " " << setw(10) << "超管" << setw(10) << "上下机" << setw(10) << "充值退费" << setw(10) << "卡管理" << setw(10) << "计费标准" << setw(10) << "查日志" << endl;
				cout << setw(10) << "现有：" << setw(10) << p->authList[0] << setw(10) << p->authList[1] << setw(10) << p->authList[2] << setw(10) << p->authList[3] << setw(10) << p->authList[4] << setw(10) << p->authList[5] << endl;
				cout << setw(10) << "新：";
				sb = scanf("%d %d %d %d %d %d", &p->authList[0], &p->authList[1], &p->authList[2], &p->authList[3], &p->authList[4], &p->authList[5]);
				system("cls");
				break;
			case 0:
				system("cls");
				break;
			default:
				cout << "错误的选项！" << endl;
				system("pause");
				system("cls");
				break;
			}
			if (d == 0) break;
		}
		system("cls");
	}
	else {
		cout << "未找到该用户！" << endl;
		system("pause");
		system("cls");
	}
	return head_adminList;
}

adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID)
{
	int delID = 0;
	cout << "请输入要删除的ID：" << endl;
	cin >> delID;
	system("cls");
	if (delID == nowAdminID) {
		cout << "不能删除自己！" << endl;
	}
	else { 
		head_adminList = auth_do_delAdmin(head_adminList, delID, nowAdminID);
	}
	return head_adminList;
}

int auth_queryAdminDetail(adminList* head_adminList)
{
	int cid = 0;
	cout << "请输入要查询详细信息的ID：";
	cin >> cid;
	int hasFound = false;
	adminList* p = head_adminList;
	char aqad_c_t[25]; //临时存储格式化时间的变量
	struct tm* ttime;
	while (1) {
		if (p == NULL) break;
		if (p->id == cid) {
			hasFound = true;
			cout << "ID：" << p->id << endl;
			cout << "用户名：" << p->username << endl;
			cout << "真实姓名：" << p->realname << endl;
			//格式化时间
			if (p->createTime > 0) {
				ttime = localtime(&p->createTime);
				strftime(aqad_c_t, sizeof(aqad_c_t), "%Y年%m月%d日 %H:%M:%S", ttime);
			}
			else { strcpy(aqad_c_t, "暂无"); }
			cout << "账户创建时间：" << aqad_c_t << endl;
			//格式化时间
			if (p->recentLoginTime > 0) {
				ttime = localtime(&p->recentLoginTime);
				strftime(aqad_c_t, sizeof(aqad_c_t), "%Y年%m月%d日 %H:%M:%S", ttime);
			}
			else { strcpy(aqad_c_t, "暂无"); }
			cout << "最近登陆时间：" << aqad_c_t << endl;
			//输出权限
			if (p->authList[0] == 1) strcpy(aqad_c_t, "是");
			else strcpy(aqad_c_t, "否");
			cout << "是否超管：" << aqad_c_t << endl;
			if (p->authList[0] != 1) {
				cout << "权限列表：" << endl;
				if (p->authList[1] == 1) strcpy(aqad_c_t, "是");
				else strcpy(aqad_c_t, "否");
				cout << setw(16) << "上下机：" << setw(4) << aqad_c_t << endl;
				if (p->authList[2] == 1) strcpy(aqad_c_t, "是");
				else strcpy(aqad_c_t, "否");
				cout << setw(16) << "充值退费：" << setw(4) << aqad_c_t << endl;
				if (p->authList[3] == 1) strcpy(aqad_c_t, "是");
				else strcpy(aqad_c_t, "否");
				cout << setw(16) << "卡管理：" << setw(4) << aqad_c_t << endl;
				if (p->authList[4] == 1) strcpy(aqad_c_t, "是");
				else strcpy(aqad_c_t, "否");
				cout << setw(16) << "计费标准管理：" << setw(4) << aqad_c_t << endl;
				if (p->authList[5] == 1) strcpy(aqad_c_t, "是");
				else strcpy(aqad_c_t, "否");
				cout << setw(16) << "日志查询：" << setw(4) << aqad_c_t << endl;
			}
		}
		p = p->next;
	}
	if (!hasFound) cout << "没有查询要相关信息！" << endl;
	system("pause");
	system("cls");
	return 0;
}

adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID){
	int c = 0;
	system("cls");
	while (1) {
		cout << "管理员信息：" << endl; 
		cout << setw(12) << "ID" << setw(12) << "用户名" << setw(12) << "真实姓名" << setw(6) << "超管" << endl;
		adminList* p = head_adminList;
		char showIsSA[4];
		while (1) {
			if (p == NULL) break;
			if (p->authList[0] == 1) strcpy(showIsSA, "是");
			else strcpy(showIsSA, "");
			cout << setw(12) << p->id << setw(12) << p->username << setw(12) << p->realname << setw(6) << showIsSA << endl;
			p = p->next;
		}
		cout << "操作：" << endl;
		cout << "1.查询详细信息" << endl;
		cout << "2.添加管理员" << endl;
		cout << "3.编辑管理员" << endl;
		cout << "4.删除管理员" << endl;
		cout << "0.返回主菜单" << endl;
		cout << "请选择：";
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
			cout << "请选择正确的选项！" << endl;
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

//输入密码不可见
void inputPassword(char password[50], int size) {
	char c;
	int count = 0;
	while ((c = _getch()) != '\r') {

		if (c == 8) { // 退格
			if (count == 0) {
				continue;
			}
			putchar('\b'); // 回退一格
			putchar(' '); // 输出一个空格将原来的*隐藏
			putchar('\b'); // 再回退一格等待输入
			count--;
		}
		if (count == size - 1) { // 最大长度为size-1
			continue;
		}
		if ((c >= 33 && c <= 126)) {  // 密码只可包含ascii中33-126的字符
			putchar('*');  // 接收到一个字符后, 打印一个*
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
	string realname = "未找到";
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