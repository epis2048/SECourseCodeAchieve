#pragma once
#include <ctime>
#include "data.h"
using namespace std;

//输入时隐藏密码
void inputPassword(char password[50], int size);
//获取登陆状态
int auth_checkStatus(adminList* head_adminList, int nowAdminID);
//登录
int auth_login(adminList* head_adminList);
//检查是否有某项的权限
int auth_checkHasAuth(adminList* head_adminList, int nowAdminID, int authID);

//显示权限管理主菜单
adminList* auth_showMainMenu(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//查询管理员
int auth_queryAdminDetail(adminList* head_adminList);
//添加管理员
adminList* auth_do_addAdmin(adminList* head_adminList, char username[20], char realname[100], char password[50], int isSuperAdmin, int* adminMaxID, int nowAdminID);
adminList* auth_addAdmin(adminList* head_adminList, int* adminMaxID, int nowAdminID);
//编辑管理员
adminList* auth_editAdmin(adminList* head_adminList, int nowAdminID);
//删除管理员
adminList* auth_do_delAdmin(adminList* head_adminList, int delID, int nowAdminID);
adminList* auth_delAdmin(adminList* head_adminList, int nowAdminID);
//API相关
string auth_query_getRealnameByID(adminList* head_adminList, int adminID);