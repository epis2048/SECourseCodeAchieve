#pragma once
#include <ctime>
#include "data.h"

//��ѯ�����ϻ��Ŀ�
void query_billUnfinishedList(billUnfinishedList* head_billUnfinishedList, billStdList* head_billStdList, adminList* head_adminList);
//��ѯ�������»���¼
void query_billList(billList* end_billList, billStdList* head_billStdList, adminList* head_adminList);
//��ѯ���г�ֵ�˷Ѽ�¼
void query_chargeList(cardList* end_cardList, chargeList* end_chargeList, adminList* head_adminList);
//ͳ��
void query_recentData(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);
//���˵�
void query_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);