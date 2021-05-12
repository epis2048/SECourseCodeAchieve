#pragma once
#include <ctime>
//把所有结构都定义在这里
//管理员列表
typedef struct admin {
	int id;
	char username[20];//用户名，登陆用
	char realname[100];//真实姓名，显示用
	char password[50];//密码，后期以md5存储
	time_t recentLoginTime;//最近登陆时间，存储为时间戳
	time_t createTime;//账户创建时间，存储为时间戳
	int authList[6] = { 0, 0, 0, 0, 0, 0 };//权限列表
	struct admin* next = NULL;
} adminList;
/*
AuthList说明
0 超级管理员
1 上下机
2 充值退费
3 卡管理
4 计费标准管理
5 日志查询
*/

//充值记录
typedef struct charge {
	int id;//ID，实现自增
	int cardID;//卡号
	char cardShowID[7];//卡号，显示用，六位，不足6位前面补0
	int chargeType;//变化形式 1是充值，2是退费
	int charge;//变化了了多少钱，单位是分，一元100
	int adminID;//管理员ID
	time_t time;//操作时间
	struct charge* prev;
} chargeList;

//卡列表
typedef struct card {
	int id;//程序用卡号，实现自增
	char showID[7];//显示和输入卡号，六位，不足6位前面补0
	char password[50];//卡密码
	int balance;//余额，单位是分，一块钱100
	int billStd;//此卡的计费标准
	int totalCharge = 0;//累计消费钱数，单位是分，一块钱100
	int totalChargeTime = 0;//累计消费次数
	time_t creatTime;//开卡时间
	int adduid;//开卡管理员ID
	time_t recentBillTime;//上次消费时间，以结束时间计算
	time_t recentChargeTime;//上次充值时间
	bool isDel = false;
	struct card* prev;//倒挂
} cardList;

//账单记录
typedef struct bill {
	int id;//ID，实现自增
	int stdID;//计费标准ID
	char stdUnit;//计费单位(秒：s、分：m、时：h)
	int stdUnitCost;//每单位多少钱, 单位是分，1元是100
	int cardID;//卡号
	int cost;//花费了多少钱，单位是分，一元100
	int upAdminID;//上机管理员ID
	time_t upTime;//上机时间
	int downAdminID;//下机管理员ID
	time_t downTime;//下机时间
	struct bill* prev;
} billList;

//在上机的卡
typedef struct billunfinish {
	int stdID;//计费标准ID
	int cardID;//卡号
	int upAdminID;//上机管理员ID
	time_t upTime;//上机时间
	struct billunfinish* next;
} billUnfinishedList;

//计费标准
typedef struct billstd {
	int id;//ID，实现自增
	char stdName[50];//计费标准名称
	time_t stdCreateTime;//创建时间
	char stdUnit;//计费单位(秒：s、分：m、时：h)
	int stdUnitCost;//每单位多少钱, 单位是分，1元是100
	bool isDel = false;
	struct billstd* next = NULL;
}billStdList;
