#pragma once
#include <ctime>
#include "data.h"

//�ϻ�
billUnfinishedList* bill_up(billUnfinishedList* head_billUnfinishedList, cardList* end_cardList, int nowAdminID);
//�»�
billList* bill_down(billList* end_billList, billUnfinishedList** head_billUnfinishedList, cardList* end_cardList, billStdList* head_billStdList, int nowAdminID, int* billMaxID);

//API
bool bill_query_isUp(billUnfinishedList* head_billUnfinishedList, int cardID);