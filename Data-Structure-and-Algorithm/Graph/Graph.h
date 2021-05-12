#pragma once
#include <iostream>
using namespace std;

template <class ElemType>
class SqList {
protected: // 顺序表的数据成员
	int length;	// 顺序表的当前长度 
	ElemType* data; // 元素存储空间的首地址 
public: // 顺序表的函数成员
	SqList(int size = DEFAULT_SIZE); // 构造一个空表
	int GetLength() const; // 取顺序表长度
	void Traverse(void (*Visit)(const ElemType&)) const;  // 遍历顺序表
	int LocateElem(const ElemType& e) const; // 元素定位(根据节点的ID)
	int LocateElemByName(const ElemType& e) const; // 元素定位(根据节点的名称)
	ElemType GetElem(int i) const; // 取顺序表中第i个元素的值
	int InsertElem(int i, const ElemType& e); // 在顺序表第i个位置插入元素
	int InsertElem(const ElemType& e); // 在顺序表表尾插入元素
};
