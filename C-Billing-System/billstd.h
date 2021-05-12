#pragma once
#include <ctime>
#include "data.h"
using namespace std;


//显示计费标准菜单
billStdList* billstd_showMainMenu(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//添加计费标准
billStdList* billstd_do_addBillStd(billStdList* head_billStdList, char stdName[50], char stdUnit, int stdUnitCost, int* billStdMaxID, int nowAdminID);
billStdList* billstd_addBillStd(billStdList* head_billStdList, int* billStdMaxID, int nowAdminID);
//编辑计费标准
billStdList* billstd_editBillStd(billStdList* head_billStdList, int nowAdminID);
//删除计费标准
billStdList* billstd_do_delBillStd(billStdList* head_billStdList, int delID, int nowAdminID);
billStdList* billstd_delBillStd(billStdList* head_billStdList, int nowAdminID);
//API相关
bool billstd_query_isValid(billStdList* head_billStdList, int stdID);//查询计费标准是否有效
string billstd_query_nameAndStd(billStdList* head_billStdList, int stdID);//查询计费标准名称及内容
//零散功能
string intTranStr(double integer);