#pragma once
#include <ctime>
//�����нṹ������������
//����Ա�б�
typedef struct admin {
	int id;
	char username[20];//�û�������½��
	char realname[100];//��ʵ��������ʾ��
	char password[50];//���룬������md5�洢
	time_t recentLoginTime;//�����½ʱ�䣬�洢Ϊʱ���
	time_t createTime;//�˻�����ʱ�䣬�洢Ϊʱ���
	int authList[6] = { 0, 0, 0, 0, 0, 0 };//Ȩ���б�
	struct admin* next = NULL;
} adminList;
/*
AuthList˵��
0 ��������Ա
1 ���»�
2 ��ֵ�˷�
3 ������
4 �Ʒѱ�׼����
5 ��־��ѯ
*/

//��ֵ��¼
typedef struct charge {
	int id;//ID��ʵ������
	int cardID;//����
	char cardShowID[7];//���ţ���ʾ�ã���λ������6λǰ�油0
	int chargeType;//�仯��ʽ 1�ǳ�ֵ��2���˷�
	int charge;//�仯���˶���Ǯ����λ�Ƿ֣�һԪ100
	int adminID;//����ԱID
	time_t time;//����ʱ��
	struct charge* prev;
} chargeList;

//���б�
typedef struct card {
	int id;//�����ÿ��ţ�ʵ������
	char showID[7];//��ʾ�����뿨�ţ���λ������6λǰ�油0
	char password[50];//������
	int balance;//����λ�Ƿ֣�һ��Ǯ100
	int billStd;//�˿��ļƷѱ�׼
	int totalCharge = 0;//�ۼ�����Ǯ������λ�Ƿ֣�һ��Ǯ100
	int totalChargeTime = 0;//�ۼ����Ѵ���
	time_t creatTime;//����ʱ��
	int adduid;//��������ԱID
	time_t recentBillTime;//�ϴ�����ʱ�䣬�Խ���ʱ�����
	time_t recentChargeTime;//�ϴγ�ֵʱ��
	bool isDel = false;
	struct card* prev;//����
} cardList;

//�˵���¼
typedef struct bill {
	int id;//ID��ʵ������
	int stdID;//�Ʒѱ�׼ID
	char stdUnit;//�Ʒѵ�λ(�룺s���֣�m��ʱ��h)
	int stdUnitCost;//ÿ��λ����Ǯ, ��λ�Ƿ֣�1Ԫ��100
	int cardID;//����
	int cost;//�����˶���Ǯ����λ�Ƿ֣�һԪ100
	int upAdminID;//�ϻ�����ԱID
	time_t upTime;//�ϻ�ʱ��
	int downAdminID;//�»�����ԱID
	time_t downTime;//�»�ʱ��
	struct bill* prev;
} billList;

//���ϻ��Ŀ�
typedef struct billunfinish {
	int stdID;//�Ʒѱ�׼ID
	int cardID;//����
	int upAdminID;//�ϻ�����ԱID
	time_t upTime;//�ϻ�ʱ��
	struct billunfinish* next;
} billUnfinishedList;

//�Ʒѱ�׼
typedef struct billstd {
	int id;//ID��ʵ������
	char stdName[50];//�Ʒѱ�׼����
	time_t stdCreateTime;//����ʱ��
	char stdUnit;//�Ʒѵ�λ(�룺s���֣�m��ʱ��h)
	int stdUnitCost;//ÿ��λ����Ǯ, ��λ�Ƿ֣�1Ԫ��100
	bool isDel = false;
	struct billstd* next = NULL;
}billStdList;
