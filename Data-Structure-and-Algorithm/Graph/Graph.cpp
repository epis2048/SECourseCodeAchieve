#pragma once
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include <string>

constexpr auto MAX = 100000;
using namespace std;

// �궨��
#define DEFAULT_SIZE 0			// ȱʡԪ�ظ���
#define DEFAULT_INFINITY 1000000	// ȱʡ�����

typedef struct Path
{
	int* vexs;  //����һ��·��
	Path* next;  //��һ��·��
}PathList;

template <class ElemType>
struct Node
{
	// ���ݳ�Ա:
	ElemType data;				// ������
	Node<ElemType>* next;		// ָ����
// ���캯��:
	Node() {						// �޲����Ĺ��캯��

	}
	Node(ElemType e, Node<ElemType>* link = NULL) {	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
		data = e;
		next = link;
	}
};

// ˳���ģ��������� 
template <class ElemType>
class SqList
{
protected:
	// ˳�������ݳ�Ա
	int length;					// ˳���ĵ�ǰ���� 
	int maxLength;				// ˳�����������
	ElemType* data;			// Ԫ�ش洢�ռ���׵�ַ 
public:
	// ˳���ĺ�����Ա
	SqList(int size = DEFAULT_SIZE) {// ����һ���ձ�
		maxLength = DEFAULT_INFINITY;
		length = size;
		data = new ElemType[length];
	}
	SqList(ElemType v[], int n, int size = DEFAULT_SIZE) {	// ��������v�����ݹ���˳���
		maxLength = DEFAULT_INFINITY;
		length = size;
		data = v;
	}
	virtual ~SqList() {			// ��������
		delete(data);
	}
	int GetLength() const {		// ȡ˳�����	
		return length;
	}
	bool IsEmpty() const {		// �ж�˳����Ƿ�Ϊ��
		if (length == 0 || data == NULL) return true;
		else return false;
	}
	void Clear() {				// ��˳������
		length = 0;
		delete(data);
		data = NULL;
	}
	void Traverse(void (*Visit)(const ElemType&)) const {	// ����˳���
		if (length > 0) {
			//cout << length;
			for (int i = 0; i < length; i++) {
				(*Visit)(data[i]);
			}
		}
	}
	int LocateElem(const ElemType& e) const {	// Ԫ�ض�λ����ָ��Ԫ����˳����е�λ��
		if (data == NULL) return -1;
		bool hasFound = false;
		int i = 0;
		for (i = 0; i < length; i++) {
			if (data[i]->equal(e)) {
				hasFound = true;
				break;
			}
		}
		if (hasFound) return i;
		else return -1;
	}
	int LocateElemByName(const ElemType& e) const {	// Ԫ�ض�λ����ָ��Ԫ����˳����е�λ��
		if (data == NULL) return -1;
		bool hasFound = false;
		int i = 0;
		
		for (i = 0; i < length; i++) {
			if (data[i]->equalByName(e)) {
				hasFound = true;
				break;
			}
		}
		if (hasFound) return i;
		else return -1;
	}
	ElemType GetElem(int i) const {	// ȡ˳����е�i��Ԫ�ص�ֵ
		return data[i];
	}
	ElemType* GetElemLoc(int i) {
		return data + i;
	}
	int SetElem(int i, const ElemType& e) {	// �޸�˳����е�i��Ԫ�ص�ֵ
		data[i] = e;
		return 0;
	}
	int DeleteElem(int x) {      // ɾ��˳����е�x��Ԫ��
		if (x < length) {
			ElemType* newData = new ElemType[length - 1];
			int j = 0;
			for (int i = 0; i < length; i++) {
				if (x != i) {
					newData[j] = data[i];
					j++;
				}
			}
			delete(data);
			data = newData;
			length--;
			return 0;
		}
		else return -1;
	}
	int InsertElem(int i, const ElemType& e) { // ��˳����i��λ�ò���Ԫ��
		if (LocateElem(e) == -1) {
			ElemType* newData = new ElemType[length + 1];
			length++;
			for (int j = 0; j < i; j++) {
				newData[j] = data[j];
			}
			newData[i] = e;
			for (int j = i + 1; j < length; j++) {
				newData[j] = data[j - 1];
			}
			delete(data);
			data = newData;
			return 0;
		}
		else return -1;
	}
	int InsertElem(const ElemType& e) {        // ��˳����β����Ԫ��
		if (LocateElem(e) == -1) {
			ElemType* newData = new ElemType[length + 1];
			int j = 0;
			for (j = 0; j < length; j++) {
				newData[j] = data[j];
			}
			newData[j] = e;
			length++;
			delete(data);
			data = newData;
			return 0;
		}
		else return -1;
	}
	SqList(const SqList<ElemType>& sa) {        // ���ƹ��캯��
		maxLength = sa.maxLength;
		length = sa.length;
		data = new ElemType[length];
		for (int i = 0; i < length; i++) {
			data[i] = sa.data[i];
		}
	}
	SqList<ElemType>& operator =(const SqList<ElemType>& sa) { // ��ֵ�������
		maxLength = sa.maxLength;
		length = sa.length;
		data = new ElemType[length];
		for (int i = 0; i < length; i++) {
			data[i] = sa.data[i];
		}
		return this;
	}
	void TraverseEdge() {
		int allDis = 0;
		if (length > 0) {
			//cout << length;
			for (int i = 0; i < length; i++) {
				cout << data[i]->vex1->Name << " <== " << data[i]->weight << " ==> " << data[i]->vex2->Name << endl;
				allDis += data[i]->weight;
			}
			cout << "�ܾ���Ϊ��" << allDis << endl;
		}
	}
};

template <class ElemType>
void showVex(const ElemType& e) {
	cout << e->Name << "\t" << endl;
}

template <class ElemType>
void showEdge(const ElemType& e) {
	cout << e->vex1->Name << " <== " << e->weight << " ==> " << e->vex2->Name << endl;
}


struct Vex {
	char Name[100];
	int flag;
	char Des[1024];
	int ID;

	bool operator==(const struct Vex& svex) const {
		if (strcmp(Name, svex.Name) == 0) return true;
		else return false;
	}
	bool equalByName(const struct Vex* svex) const {
		return (strcmp(Name, svex->Name) == 0);
	}
	bool equal(const struct Vex* svex) const {
		return ID == svex->ID;
	}
};

struct Edge {
	Vex* vex1;
	Vex* vex2;
	int weight;
	bool operator==(const struct Edge& sedge) const {
		if ((vex1 == sedge.vex1 && vex2 == sedge.vex2) || (vex1 == sedge.vex2 && vex2 == sedge.vex1)) return true;
		else return false;
	}
	bool equalByName(const struct Edge* sedge) const {
		return ((vex1 == sedge->vex1 && vex2 == sedge->vex2) || (vex1 == sedge->vex2 && vex2 == sedge->vex1));
	}
	bool equal(const struct Edge* sedge) const {
		return ((vex1->equal(sedge->vex1) && vex2->equal(sedge->vex2)) || (vex1->equal(sedge->vex2) && vex2->equal(sedge->vex1)));
	}
};

class graph {
private:
	int AdjMatrix[20][20]; //�ڽӾ���
	SqList<Vex*> Vexs; //��ļ���
	SqList<Edge*> Edges; //�ߵļ���
	int VexNum; //�������
	PathList* path;

public:
	graph() {
		VexNum = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				AdjMatrix[i][j] = MAX;
			}
		}
	}

	~graph() {

	}

	bool InsertVex(Vex* svex) {
		int i = Vexs.InsertElem(svex);
		if (i != -1) {
			AdjMatrix[i][i] = 0;//�Լ��ľ�����0
			VexNum += 1;//����+1
			return true;
		}
		else return false;
	}

	bool DeleteVex(Vex* svex) {
		int i = Vexs.LocateElem(svex);
		if (i != -1) {
			for (int j = 0; j < 20; j++) {//���ڽӾ�����ɾ��Ԫ��
				AdjMatrix[i][j] = MAX;
				AdjMatrix[j][i] = MAX;
			}
			//�������б�ɾ�������Ԫ�صı�
			int l = Edges.GetLength();
			for (int j = 0; j < l;) {
				if (Edges.GetElem(j)->vex1->equal(svex) || Edges.GetElem(j)->vex2->equal(svex)) {
					Edges.DeleteElem(j);
					showEdge(Edges.GetElem(j));
					l--;
				}
				else j++;
			}
			Vexs.DeleteElem(i);//ɾ��Ԫ��
			VexNum -= 1;//����-1
		}
		else return false;
	}

	bool UpdateVex(Vex* svex, const char* newName) {
		int i = Vexs.LocateElem(svex);
		if (i != -1) {
			strcpy(svex->Name, newName);
			Vexs.SetElem(i, svex);
			return true;
		}
		else return false;
	}

	Vex* getVex(Vex* svex) {
		int i = Vexs.LocateElem(svex);
		return Vexs.GetElem(i);
	}

	Vex* getVexByName(Vex* svex) {
		int i = Vexs.LocateElemByName(svex);
		if (i == -1) return NULL;
		return Vexs.GetElem(i);
	}

	bool InsertEdge(Edge* sedge) {
		if (Edges.InsertElem(sedge) != -1) {
			//�ھ�����д�������
			int i = Vexs.LocateElem(sedge->vex1);
			int j = Vexs.LocateElem(sedge->vex2);
			AdjMatrix[i][j] = sedge->weight;
			AdjMatrix[j][i] = sedge->weight;
			return true;
		}
		else {
			//cout << 0;
			return false;

		}
	}

	bool DeleteEdge(Edge* sedge) {
		int i = Edges.LocateElem(sedge);
		if (i != -1) {
			//�ھ�����ɾ�������
			int k = Vexs.LocateElem(sedge->vex1);
			int j = Vexs.LocateElem(sedge->vex2);
			AdjMatrix[k][j] = MAX;
			AdjMatrix[j][k] = MAX;
			Edges.DeleteElem(i);
			return true;
		}
		else return false;
	}

	bool UpdateEdge(Edge* sedge, int newWeight) {
		int i = Edges.LocateElem(sedge);
		if (i != -1) {
			sedge->weight = newWeight;
			Edges.SetElem(i, sedge);
			return true;
		}
		else return false;
	}

	void printEdgeByOneVexName(Vex* svex) {
		for (int i = 0; i < Edges.GetLength(); i++) {
			Edge* edge = Edges.GetElem(i);
			if (edge->vex1->equalByName(svex) || edge->vex2->equalByName(svex)) {
				cout << edge->vex1->Name << " <== " << edge->weight << " ==> " << edge->vex2->Name << endl;
			}
		}
	}

	bool hasVex(char* vexName) {
		bool has = false;
		for (int i = 0; i < Vexs.GetLength(); i++) {
			if (strcmp(Vexs.GetElem(i)->Name, vexName) == 0) {
				has = true;
				break;
			}
		}
		return has;
	}

	void DFSTraverse(Vex* vex) {
		int n = Vexs.GetLength();
		//��ʼ��һЩ�ݹ����
		bool* mark = new bool[n+1]; //��¼�����Ƿ񱻱���
		for (int v = 0; v < n; v++)
			mark[v] = false;
		int* vexPath = new int[n + 1]; //��¼����·��
		int visitDepth = 0; //��¼�������
		PathList* pathList = NULL; //����·��������
		//��v����������ȱ���ͼg
		int v = Vexs.LocateElem(vex);
		pathList = DFS(v, mark, pathList, &visitDepth, vexPath);
		int j = 0;
		while (1) {
			if (pathList == NULL) break;
			for (int i = 0; i < n; i++) {
				Vex* v = Vexs.GetElem(pathList->vexs[i]);
				cout << v->Name << " -> ";
			}
			cout << "���" << endl;
			pathList = pathList->next;
			j++;
		}
		cout << "һ����" << j << "��·��" << endl;
	}// dfstraverse


	PathList* DFS(int v, bool* mark, PathList* pathList, int* visitDepth, int* vexPath) {
		//��·��������vexPath��
		vexPath[(*visitDepth)++] = v;
		//��¼�ѷ���
		mark[v] = true;
		int n = Vexs.GetLength();
		if ((*visitDepth) >= n) { //������һ��������·��
			//��vexPath���浽p��
			PathList* p = new PathList;
			p->vexs = new int[n];
			for (int h = 0; h < n; h++) {
				p->vexs[h] = vexPath[h];
			}
			p->next = NULL;
			//��p��������
			PathList* q = pathList;
			if (q == NULL) { //��ͷ�ڵ�Ϊ��Ҫ��������һ��
				pathList = p;
			}
			else {
				while (q->next != NULL) q = q->next;
				q->next = p;
			}
		}
		else { //��������
			//��ȡ��һ���ڽӵ�
			int i = 0;
			for (i = 0; i < Vexs.GetLength(); i++) {
				//�ҵ�δ�����ʵĽڵ�
				if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
					pathList = DFS(i, mark, pathList, visitDepth, vexPath); //�����ݹ�
					(*visitDepth)--; //����
					mark[i] = false; //����Ϊδ������
				}
			}
		}
		return pathList; //������ʼ��
	}

	void DFS_old(int v, bool* mark) {
		//��ȡv0
		Vex* v0 = Vexs.GetElem(v);
		cout << v0->Name << " -> ";
		mark[v] = true;
		//��ȡ��һ���ڽӵ�
		int w = 0;
		int i = 0;
		for (i = 0; i < Vexs.GetLength(); i++) {
			//�ҵ���һ��δ�����ʵĽڵ�
			if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
				w = i;
				break;
			}
		}
		while (w){ //w����
			if (!mark[w]) DFS_old(w, mark); //��wδ�ã������w
			else break;
			//��ȡ��һ���ڽӵ�
			for (; i < Vexs.GetLength(); i++) {
				if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
					w = i;
					break;
				}
			}
		}
	}

	string dijkstraShortPath(Vex* startVex, Vex* endVex) {
		//��ʼ������
		int n = Vexs.GetLength();
		int startVexNum = Vexs.LocateElem(startVex);
		int endVexNum = Vexs.LocateElem(endVex);
		int* mark = new int[n];
		int* dist = new int[n];
		int* path = new int[n];
		for (int i = 0; i < n; i++) {
			mark[i] = 0;
			dist[i] = AdjMatrix[startVexNum][i];
			path[i] = startVexNum;
		}
		int j;
		//dijkstra�㷨
		while (!mark[endVexNum]) {
			int min = MAX;
			//�Ҳ���mark�о�����С�Ľڵ�
			for (int i = 0; i < n; i++) {
				if (mark[i] == 0 && dist[i] != 0) {
					if (dist[i] < min) {
						j = i;
						min = dist[i];
					}
				}
			}
			mark[j] = 1; //���������mark
			for (int i = 0; i < n; i++) { 
				if (mark[i] == 0 && AdjMatrix[j][i] > 0 && AdjMatrix[j][i] < MAX) {
					if ((dist[i] > dist[j] + AdjMatrix[j][i]) || (dist[i] == 0 && dist[j] != 0)) { //�޸�dist[i]
						path[i] = j;
						dist[i] = dist[j] + AdjMatrix[j][i];
					}
				}
			}
		}
		//������
		j = endVexNum;
		string s = "";
		int allWeight = 0;
		while (j != startVexNum) {
			s = Vexs.GetElem(j)->Name + s;
			s = " -> " + s;
			allWeight += AdjMatrix[j][path[j]];
			j = path[j];
		}
		s = Vexs.GetElem(startVexNum)->Name + s;
		s = "·�ߣ�" + s + "\n���룺" + to_string(allWeight);
		return s;
	}

	graph PrimMinTree() {
		graph G;
		G.InsertVex(this->Vexs.GetElem(0));
		SqList<Edge*> e = this->Edges; //e������G��û�еı�
		for (int j = 0; j < this->Vexs.GetLength() - 1; j++) { //ѭ��n-1��
			int minEdgeNum = MAX;
			int minEdgeWeight = MAX;
			for (int i = 0; i < e.GetLength(); i++) {
				if (G.Vexs.LocateElem(e.GetElem(i)->vex1) != -1 || G.Vexs.LocateElem(e.GetElem(i)->vex2) != -1) {//����e�����бߣ��������˵���G��Ϊ����
					//���ܳɻ�(�������˵㲻��ͬʱ��G�г���)
					if ((G.Vexs.LocateElem(e.GetElem(i)->vex1) != -1 && G.Vexs.LocateElem(e.GetElem(i)->vex2) == -1) || (G.Vexs.LocateElem(e.GetElem(i)->vex2) != -1 && G.Vexs.LocateElem(e.GetElem(i)->vex1) == -1)) {
						if (e.GetElem(i)->weight < minEdgeWeight) {//ȨֵС
							minEdgeNum = i;
							minEdgeWeight = e.GetElem(i)->weight;
						}
					}
				}
			}
			//��G����ӽڵ�ͱߣ���e��ɾ����
			Edge* etemp = e.GetElem(minEdgeNum);
			G.InsertVex(etemp->vex1);
			G.InsertVex(etemp->vex2);
			G.InsertEdge(etemp);
			e.DeleteElem(e.LocateElem(etemp));
		}
		return G;
	}

	graph KruskalMinTree() {
		graph G;
		//�������ڵ�����ǣ���ǲ�ͬ����ͨ����
		for (int i = 0; i < this->Vexs.GetLength(); i++) {
			this->Vexs.GetElem(i)->flag = i;
		}
		//�ѱ�Ǵ浽�ߵĽڵ���
		for (int i = 0; i < this->Edges.GetLength(); i++) {
			this->Edges.GetElem(i)->vex1->flag = this->Vexs.GetElem(this->Vexs.LocateElem(this->Edges.GetElem(i)->vex1))->flag;
			this->Edges.GetElem(i)->vex2->flag = this->Vexs.GetElem(this->Vexs.LocateElem(this->Edges.GetElem(i)->vex2))->flag;
		}
		SqList<Edge*> e = this->Edges; //e������G��û�еı�
		while (G.Edges.GetLength() < this->Vexs.GetLength() - 1) { //ѭ��n-1��
			Edge* etemp = e.GetElem(0);
			for (int i = 0; i < e.GetLength(); i++) {//ѡ��e����С�ı�
				if (e.GetElem(i)->weight < etemp->weight) {
					etemp = e.GetElem(i);
				}
			}
			//��������ͬʱ��ͬʱ��G�г��ֲ��ұ����ͬ��ͬһ����ͨ�����������ǻ�·
			if (!(G.Vexs.LocateElem(etemp->vex1) != -1 && G.Vexs.LocateElem(etemp->vex2) != -1 && etemp->vex1->flag == etemp->vex2->flag)) {
				G.InsertVex(etemp->vex1);
				G.InsertVex(etemp->vex2);
				G.InsertEdge(etemp);
				//�������ж��㣬���±��
				for (int i = 0; i < this->Vexs.GetLength(); i++) {
					if (this->Vexs.GetElem(i)->flag == etemp->vex2->flag) {//������2��flag���ĳ�1
						this->Vexs.GetElem(i)->flag = etemp->vex1->flag;
					}
				}
				//���±�Ǵ������бߵĽڵ���
				for (int i = 0; i < e.GetLength(); i++) {//���¶�Ӧe�еĽڵ��flag
					e.GetElem(i)->vex1->flag = this->Vexs.GetElem(this->Vexs.LocateElem(e.GetElem(i)->vex1))->flag;
					e.GetElem(i)->vex2->flag = this->Vexs.GetElem(this->Vexs.LocateElem(e.GetElem(i)->vex2))->flag;
				}
			}
			else {
			}
			e.DeleteElem(e.LocateElem(etemp));//ɾ���ҵ��������С�ı�
		}
		return G;
	}

	void print() {
		cout << "�ڵ��У�" << endl;
		Vexs.Traverse(showVex);
		cout << "���У�" << endl;
		Edges.Traverse(showEdge);
	}

	void printVexs() {
		cout << "�ڵ��У�" << endl;
		Vexs.Traverse(showVex);
	}

	void printEdges() {
		cout << "���У�" << endl;
		Edges.Traverse(showEdge);
	}

	void printEdgesWithDis() {
		cout << "���У�" << endl;
		Edges.TraverseEdge();
		//cout << "�ܾ��룺" << allDis << endl;
	}

	void test() {
		cout << "����ԣ�" << endl;
		Vex vex1, vex2, vex3, vex4;
		strcpy(vex1.Name, "����");
		strcpy(vex2.Name, "�Ϻ�");
		strcpy(vex3.Name, "����");
		strcpy(vex4.Name, "����");
		InsertVex(&vex1);
		InsertVex(&vex2);
		InsertVex(&vex3);
		InsertVex(&vex4);
		Vexs.Traverse(showVex);
		//DeleteVex(vex3);
		//UpdateVex(vex1, "���");
		//Vexs.Traverse(showVex);
		//UpdateVex(vex1, "����");
		cout << "�߲��ԣ�" << endl;
		Edge edge1, edge2, edge3;
		//�������Ϻ�1000
		edge1.vex1 = &vex1;
		edge1.vex2 = &vex2;
		edge1.weight = 1000;
		//����������2000
		edge2.vex1 = &vex1;
		edge2.vex2 = &vex3;
		edge2.weight = 2000;
		//���ݵ�����100
		edge3.vex1 = &vex3;
		edge3.vex2 = &vex4;
		edge3.weight = 100;
		Edges.InsertElem(&edge1);
		Edges.InsertElem(&edge2);
		Edges.InsertElem(&edge3);
		Edges.Traverse(showEdge);
		DeleteEdge(&edge2);
		UpdateEdge(&edge3, 150);
		Edges.Traverse(showEdge);
	}
};