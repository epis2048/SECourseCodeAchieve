#pragma once
#include <ctime>
#include "data.h"

//��ֵ
chargeList* charge_reCharge(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID);
//�˷�
chargeList* charge_reFund(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID);