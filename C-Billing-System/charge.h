#pragma once
#include <ctime>
#include "data.h"

//≥‰÷µ
chargeList* charge_reCharge(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID);
//ÕÀ∑—
chargeList* charge_reFund(chargeList* end_chargeList, cardList* end_cardList, int* chargeMaxID, int nowAdminID);