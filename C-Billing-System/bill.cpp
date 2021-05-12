#include <iostream>
#include <ctime>
#include "bill.h"
#include "billstd.h"

using namespace std;

billUnfinishedList* bill_up(billUnfinishedList* head_billUnfinishedList, cardList* end_cardList, int nowAdminID)
{
	int cid;
	bool hasFoundCard = false;
	cardList* pcl = end_cardList;
	billUnfinishedList* p;
	billUnfinishedList* q;
	system("cls");
	cout << "�ϻ�" << endl;
	cout << "�����뿨�ţ�";
	cin >> cid;
	while (1) {
		if (pcl == NULL) break;
		if (pcl->id == cid) {
			hasFoundCard = true;
			break;
		}
		pcl = pcl->prev;
	}
	if (hasFoundCard) {
		if (bill_query_isUp(head_billUnfinishedList, cid)) {
			cout << "�ÿ������ϻ���" << endl;
		}
		else {
			char cpw[50];
			cout << "�����뿨���룺";
			cin >> cpw;
			if (strcmp(cpw, pcl->password) == 0) {
				system("cls");
				if (pcl->balance < 0) {
					cout << "�ÿ����㣡" << endl;
				}
				else {
					p = (billUnfinishedList*)malloc(sizeof(billUnfinishedList));//�����ڴ�
					if (p == NULL) {
						cout << "�ϻ�ʧ�ܣ�" << endl;
					}
					else {
						std::time_t t = std::time(0);
						p->cardID = pcl->id;
						p->stdID = pcl->billStd;
						p->upAdminID = nowAdminID;
						p->upTime = t;
						p->next = NULL;
						//�����������
						if (head_billUnfinishedList == NULL) {
							head_billUnfinishedList = p;
						}
						else {
							q = head_billUnfinishedList;
							while (q->next != NULL) {
								q = q->next;
							}
							q->next = p;
						}
						cout << "�ϻ��ɹ���" << endl;
					}
				}
			}
			else {
				cout << "���������" << endl;
			}
		}
	}
	else {
		cout << "û���ҵ��ÿ���" << endl;
	}
	system("pause");
	system("cls");
	return head_billUnfinishedList;
}

billList* bill_down(billList* end_billList, billUnfinishedList** head_billUnfinishedList, cardList* end_cardList, billStdList* head_billStdList, int nowAdminID, int* billMaxID)
{
	int cid;
	system("cls");
	cout << "�»�" << endl << "�����뿨�ţ�";
	cin >> cid;
	//��ѯ�ÿ����ϻ���¼
	bool hasFoundBul = false;
	billUnfinishedList* bul = *head_billUnfinishedList;
	while (1) {
		if (bul == NULL) break;
		if (bul->cardID == cid) {
			hasFoundBul = true;
			break;
		}
		bul = bul->next;
	}
	//��ѯ��
	bool hasFoundCard = false;
	cardList* cl = end_cardList;
	while (1)
	{
		if (cl == NULL) break;
		if (cl->id == cid) {
			hasFoundCard = true;
			break;
		}
		cl = cl->prev;
	}
	if (hasFoundBul && hasFoundCard) {
		//��������
		char inpw[50];
		cout << "�����뿨���룺";
		cin >> inpw;
		if (strcmp(inpw, cl->password) == 0) {
			system("cls");
			char b_bd_st[25];
			struct tm* ttime;
			time_t tnow = time(0);
			//��ȡ��ǰʱ��
			ttime = localtime(&bul->upTime);
			strftime(b_bd_st, sizeof(b_bd_st), "%Y��%m��%d�� %H:%M:%S", ttime);
			cout << "�ϻ�ʱ�䣺" << b_bd_st << endl;
			ttime = localtime(&tnow);
			strftime(b_bd_st, sizeof(b_bd_st), "%Y��%m��%d�� %H:%M:%S", ttime);
			cout << "��ǰʱ�䣺" << b_bd_st << endl;
			//�����ϻ�ʱ��
			long sec;
			float min;
			float hour;
			sec = tnow - bul->upTime;
			min = sec * 1.0 / 60;
			hour = min / 60;
			cout << "��һ������ " << (int)hour << "Сʱ" << (int)(min - ((int)hour) * 60) << "��" << (int)(sec - ((int)min) * 60) << "��" << endl;
			//��ȡ�Ʒѱ�׼
			billStdList* bsl = head_billStdList;
			bool hasFoundBsl = false;
			while (1) {
				if (bsl == NULL) break;
				if (bsl->id == bul->stdID) {
					hasFoundBsl = true;
					break;
				}
				bsl = bsl->next;
			}
			if (hasFoundBsl) {
				billList* p;
				p = (billList*)malloc(sizeof(billList));//�����ڴ�
				if (p == NULL) {
					cout << "�»�ʧ�ܣ�" << endl;
				}
				else {
					string showBsl;
					showBsl = bsl->stdName;
					showBsl = showBsl + ": ";
					showBsl = showBsl + intTranStr(bsl->stdUnitCost * 1.0 / 100) + '/' + bsl->stdUnit;
					if (bsl->isDel) showBsl = showBsl + " (��ʧЧ)";
					cout << "���ļƷѱ�׼�ǣ�" << showBsl << endl;
					//�۷�
					int cost;
					if (bsl->stdUnit == 'm') {
						cost = min * bsl->stdUnitCost;
					}
					else if (bsl->stdUnit == 'h') {
						cost = hour * bsl->stdUnitCost;
					}
					else {
						cost = sec * bsl->stdUnitCost;
					}
					cout << "�۷�ǰ��" << cl->balance * 1.0 / 100 << endl;
					cout << "�������ļƷѱ�׼�������λ����ˣ�" << cost * 1.0 / 100 << endl;
					cl->balance -= cost;
					cout << "�۷Ѻ���" << cl->balance * 1.0 / 100 << endl;
					if (cl->balance < 0) {
						cout << "�ÿ���Ƿ�ѣ�" << endl;
					}
					//�����¼
					cl->recentBillTime = tnow;
					cl->totalCharge += cost;
					cl->totalChargeTime++;
					p->cardID = cid;
					p->cost = cost;
					p->downAdminID = nowAdminID;
					p->downTime = tnow;
					p->stdID = bsl->id;
					p->stdUnit = bsl->stdUnit;
					p->stdUnitCost = bsl->stdUnitCost;
					p->upAdminID = bul->upAdminID;
					p->upTime = bul->upTime;
					(*billMaxID)++;
					p->id = *billMaxID;
					p->prev = end_billList;
					end_billList = p;
					//ɾ�������ϻ��ļ�¼
					billUnfinishedList* q = *head_billUnfinishedList;//��ʼ��������ʱ������q����ѭ������
					billUnfinishedList* t = *head_billUnfinishedList;//t���ڱ�����һ���ڵ�
					if (q != NULL) { //����ͷ�ڵ㲻Ϊ�գ���ʵ��ҵ���߼��У����ж�û��Ҫ��
						if (q->cardID == cid) *head_billUnfinishedList = q->next;//�����һ���ڵ����Ҫɾ�������ݣ�ֱ�ӽ�ͷ�ڵ��Ϊ�ڶ���
						else {
							while (1) {//��������
								if (q->cardID == cid) {//�����ǰ�ڵ���Ҫ��ɾ���Ľڵ㣬���˳�ѭ��
									break;
								}
								else {
									t = q;//������ǣ��ͱ��浱ǰ�ڵ㵽t����һ��ѭ��ʱt������һ��ѭ������һ���ڵ�
								}
								q = q->next;//��ָ��ָ����һ���ڵ㣬׼����������
							}
							t->next = q->next;//����Ҫ��ɾ���Ľڵ����һ���ڵ��ָ����һ���ڵ㣩��ָ��ָ��Ҫ��ɾ���Ľڵ����һ���ڵ�
							free(q);
						}
					}
				}
			}
			else {
				cout << "�Ҳ����Ʒѱ�׼��" << endl;
			}
		}
		else {
			cout << "���������" << endl;
		}
	}
	else {
		cout << "���Ų����ڻ��߸ÿ������ϻ�" << endl;
	}
	system("pause");
	system("cls");
	return end_billList;
}

bool bill_query_isUp(billUnfinishedList* head_billUnfinishedList, int cardID)
{
	bool isUp = false;
	billUnfinishedList* p = head_billUnfinishedList;
	while (1) {
		if (p == NULL) break;
		if (p->cardID == cardID) {
			isUp = true;
			break;
		}
		p = p->next;
	}
	return isUp;
}