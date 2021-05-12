#pragma once
#include <ctime>
#include "data.h"

//查询正在上机的卡
void query_billUnfinishedList(billUnfinishedList* head_billUnfinishedList, billStdList* head_billStdList, adminList* head_adminList);
//查询所有上下机记录
void query_billList(billList* end_billList, billStdList* head_billStdList, adminList* head_adminList);
//查询所有充值退费记录
void query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList);
//统计
void query_recentData(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);
//主菜单
void query_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);