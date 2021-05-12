#pragma once
#include "data.h"
//Ö÷½çÃæ
void save_showMainMenu(adminList* head_adminList, billStdList* head_billStdList, cardList* end_cardList, billList* end_billList, billUnfinishedList* head_billUnfinishedList, chargeList* end_chargeList);
//adminList
bool save_auth_adminList(adminList* head_adminList);
adminList* read_auth_adminList(int* adminMaxID);
//billStdList
bool save_billStd_billStdList(billStdList* head_billStdList);
billStdList* read_billStd_billStdList(int* billStdMaxID);
//cardList
bool save_card_cardList(cardList* end_cardList);
cardList* read_card_cardList(int* cardMaxID);
//chargeList
bool save_charge_chargeList(chargeList* end_chargeList);
chargeList* read_charge_chargeList(int* chargeMaxID);
//billUnfinishedList
bool save_bill_billUnfinishedList(billUnfinishedList* head_billUnfinishedList);
billUnfinishedList* read_bill_billUnfinishedList();
//billList
bool save_bill_billList(billList* end_billList);
billList* read_bill_billList(int* billMaxID);
