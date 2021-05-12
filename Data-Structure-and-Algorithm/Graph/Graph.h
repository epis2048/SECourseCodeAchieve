#pragma once
#include <iostream>
using namespace std;

template <class ElemType>
class SqList {
protected: // ˳�������ݳ�Ա
	int length;	// ˳���ĵ�ǰ���� 
	ElemType* data; // Ԫ�ش洢�ռ���׵�ַ 
public: // ˳���ĺ�����Ա
	SqList(int size = DEFAULT_SIZE); // ����һ���ձ�
	int GetLength() const; // ȡ˳�����
	void Traverse(void (*Visit)(const ElemType&)) const;  // ����˳���
	int LocateElem(const ElemType& e) const; // Ԫ�ض�λ(���ݽڵ��ID)
	int LocateElemByName(const ElemType& e) const; // Ԫ�ض�λ(���ݽڵ������)
	ElemType GetElem(int i) const; // ȡ˳����е�i��Ԫ�ص�ֵ
	int InsertElem(int i, const ElemType& e); // ��˳����i��λ�ò���Ԫ��
	int InsertElem(const ElemType& e); // ��˳����β����Ԫ��
};
