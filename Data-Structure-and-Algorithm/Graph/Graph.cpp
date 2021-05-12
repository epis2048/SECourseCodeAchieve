#pragma once
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include <string>

constexpr auto MAX = 100000;
using namespace std;

// 宏定义
#define DEFAULT_SIZE 0			// 缺省元素个数
#define DEFAULT_INFINITY 1000000	// 缺省无穷大

typedef struct Path
{
	int* vexs;  //保存一条路径
	Path* next;  //下一条路径
}PathList;

template <class ElemType>
struct Node
{
	// 数据成员:
	ElemType data;				// 数据域
	Node<ElemType>* next;		// 指针域
// 构造函数:
	Node() {						// 无参数的构造函数

	}
	Node(ElemType e, Node<ElemType>* link = NULL) {	// 已知数数据元素值和指针建立结构
		data = e;
		next = link;
	}
};

// 顺序表模板类的申明 
template <class ElemType>
class SqList
{
protected:
	// 顺序表的数据成员
	int length;					// 顺序表的当前长度 
	int maxLength;				// 顺序表的最大容量
	ElemType* data;			// 元素存储空间的首地址 
public:
	// 顺序表的函数成员
	SqList(int size = DEFAULT_SIZE) {// 构造一个空表
		maxLength = DEFAULT_INFINITY;
		length = size;
		data = new ElemType[length];
	}
	SqList(ElemType v[], int n, int size = DEFAULT_SIZE) {	// 根据数组v的内容构造顺序表
		maxLength = DEFAULT_INFINITY;
		length = size;
		data = v;
	}
	virtual ~SqList() {			// 析构函数
		delete(data);
	}
	int GetLength() const {		// 取顺序表长度	
		return length;
	}
	bool IsEmpty() const {		// 判断顺序表是否为空
		if (length == 0 || data == NULL) return true;
		else return false;
	}
	void Clear() {				// 将顺序表清空
		length = 0;
		delete(data);
		data = NULL;
	}
	void Traverse(void (*Visit)(const ElemType&)) const {	// 遍历顺序表
		if (length > 0) {
			//cout << length;
			for (int i = 0; i < length; i++) {
				(*Visit)(data[i]);
			}
		}
	}
	int LocateElem(const ElemType& e) const {	// 元素定位，求指定元素在顺序表中的位置
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
	int LocateElemByName(const ElemType& e) const {	// 元素定位，求指定元素在顺序表中的位置
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
	ElemType GetElem(int i) const {	// 取顺序表中第i个元素的值
		return data[i];
	}
	ElemType* GetElemLoc(int i) {
		return data + i;
	}
	int SetElem(int i, const ElemType& e) {	// 修改顺序表中第i个元素的值
		data[i] = e;
		return 0;
	}
	int DeleteElem(int x) {      // 删除顺序表中第x个元素
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
	int InsertElem(int i, const ElemType& e) { // 在顺序表第i个位置插入元素
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
	int InsertElem(const ElemType& e) {        // 在顺序表表尾插入元素
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
	SqList(const SqList<ElemType>& sa) {        // 复制构造函数
		maxLength = sa.maxLength;
		length = sa.length;
		data = new ElemType[length];
		for (int i = 0; i < length; i++) {
			data[i] = sa.data[i];
		}
	}
	SqList<ElemType>& operator =(const SqList<ElemType>& sa) { // 赋值语句重载
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
			cout << "总距离为：" << allDis << endl;
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
	int AdjMatrix[20][20]; //邻接矩阵
	SqList<Vex*> Vexs; //点的集合
	SqList<Edge*> Edges; //边的集合
	int VexNum; //点的数量
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
			AdjMatrix[i][i] = 0;//自己的距离是0
			VexNum += 1;//数量+1
			return true;
		}
		else return false;
	}

	bool DeleteVex(Vex* svex) {
		int i = Vexs.LocateElem(svex);
		if (i != -1) {
			for (int j = 0; j < 20; j++) {//从邻接矩阵中删除元素
				AdjMatrix[i][j] = MAX;
				AdjMatrix[j][i] = MAX;
			}
			//遍历边列表，删除带这个元素的边
			int l = Edges.GetLength();
			for (int j = 0; j < l;) {
				if (Edges.GetElem(j)->vex1->equal(svex) || Edges.GetElem(j)->vex2->equal(svex)) {
					Edges.DeleteElem(j);
					showEdge(Edges.GetElem(j));
					l--;
				}
				else j++;
			}
			Vexs.DeleteElem(i);//删除元素
			VexNum -= 1;//数量-1
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
			//在矩阵中写入这个边
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
			//在矩阵中删除这个边
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
		//初始化一些递归变量
		bool* mark = new bool[n+1]; //记录顶点是否被遍历
		for (int v = 0; v < n; v++)
			mark[v] = false;
		int* vexPath = new int[n + 1]; //记录访问路径
		int visitDepth = 0; //记录遍历深度
		PathList* pathList = NULL; //访问路径的链表
		//从v出发深度优先遍历图g
		int v = Vexs.LocateElem(vex);
		pathList = DFS(v, mark, pathList, &visitDepth, vexPath);
		int j = 0;
		while (1) {
			if (pathList == NULL) break;
			for (int i = 0; i < n; i++) {
				Vex* v = Vexs.GetElem(pathList->vexs[i]);
				cout << v->Name << " -> ";
			}
			cout << "完毕" << endl;
			pathList = pathList->next;
			j++;
		}
		cout << "一共有" << j << "条路径" << endl;
	}// dfstraverse


	PathList* DFS(int v, bool* mark, PathList* pathList, int* visitDepth, int* vexPath) {
		//将路径保存在vexPath中
		vexPath[(*visitDepth)++] = v;
		//记录已访问
		mark[v] = true;
		int n = Vexs.GetLength();
		if ((*visitDepth) >= n) { //访问了一条完整的路径
			//将vexPath保存到p中
			PathList* p = new PathList;
			p->vexs = new int[n];
			for (int h = 0; h < n; h++) {
				p->vexs[h] = vexPath[h];
			}
			p->next = NULL;
			//将p插入链表
			PathList* q = pathList;
			if (q == NULL) { //对头节点为空要单独处理一下
				pathList = p;
			}
			else {
				while (q->next != NULL) q = q->next;
				q->next = p;
			}
		}
		else { //继续访问
			//获取第一个邻接点
			int i = 0;
			for (i = 0; i < Vexs.GetLength(); i++) {
				//找到未被访问的节点
				if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
					pathList = DFS(i, mark, pathList, visitDepth, vexPath); //继续递归
					(*visitDepth)--; //回溯
					mark[i] = false; //设置为未被访问
				}
			}
		}
		return pathList; //返回起始点
	}

	void DFS_old(int v, bool* mark) {
		//获取v0
		Vex* v0 = Vexs.GetElem(v);
		cout << v0->Name << " -> ";
		mark[v] = true;
		//获取第一个邻接点
		int w = 0;
		int i = 0;
		for (i = 0; i < Vexs.GetLength(); i++) {
			//找到第一个未被访问的节点
			if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
				w = i;
				break;
			}
		}
		while (w){ //w存在
			if (!mark[w]) DFS_old(w, mark); //若w未访，则访问w
			else break;
			//获取下一个邻接点
			for (; i < Vexs.GetLength(); i++) {
				if (AdjMatrix[v][i] < MAX && AdjMatrix[v][i] > 0 && !mark[i]) {
					w = i;
					break;
				}
			}
		}
	}

	string dijkstraShortPath(Vex* startVex, Vex* endVex) {
		//初始化部分
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
		//dijkstra算法
		while (!mark[endVexNum]) {
			int min = MAX;
			//找不在mark中距离最小的节点
			for (int i = 0; i < n; i++) {
				if (mark[i] == 0 && dist[i] != 0) {
					if (dist[i] < min) {
						j = i;
						min = dist[i];
					}
				}
			}
			mark[j] = 1; //将顶点加入mark
			for (int i = 0; i < n; i++) { 
				if (mark[i] == 0 && AdjMatrix[j][i] > 0 && AdjMatrix[j][i] < MAX) {
					if ((dist[i] > dist[j] + AdjMatrix[j][i]) || (dist[i] == 0 && dist[j] != 0)) { //修改dist[i]
						path[i] = j;
						dist[i] = dist[j] + AdjMatrix[j][i];
					}
				}
			}
		}
		//输出结果
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
		s = "路线：" + s + "\n距离：" + to_string(allWeight);
		return s;
	}

	graph PrimMinTree() {
		graph G;
		G.InsertVex(this->Vexs.GetElem(0));
		SqList<Edge*> e = this->Edges; //e保存了G中没有的边
		for (int j = 0; j < this->Vexs.GetLength() - 1; j++) { //循环n-1次
			int minEdgeNum = MAX;
			int minEdgeWeight = MAX;
			for (int i = 0; i < e.GetLength(); i++) {
				if (G.Vexs.LocateElem(e.GetElem(i)->vex1) != -1 || G.Vexs.LocateElem(e.GetElem(i)->vex2) != -1) {//遍历e中所有边，以他俩端点在G中为条件
					//不能成环(即两个端点不能同时在G中出现)
					if ((G.Vexs.LocateElem(e.GetElem(i)->vex1) != -1 && G.Vexs.LocateElem(e.GetElem(i)->vex2) == -1) || (G.Vexs.LocateElem(e.GetElem(i)->vex2) != -1 && G.Vexs.LocateElem(e.GetElem(i)->vex1) == -1)) {
						if (e.GetElem(i)->weight < minEdgeWeight) {//权值小
							minEdgeNum = i;
							minEdgeWeight = e.GetElem(i)->weight;
						}
					}
				}
			}
			//在G中添加节点和边，在e中删除边
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
		//给各个节点做标记，标记不同的连通分量
		for (int i = 0; i < this->Vexs.GetLength(); i++) {
			this->Vexs.GetElem(i)->flag = i;
		}
		//把标记存到边的节点里
		for (int i = 0; i < this->Edges.GetLength(); i++) {
			this->Edges.GetElem(i)->vex1->flag = this->Vexs.GetElem(this->Vexs.LocateElem(this->Edges.GetElem(i)->vex1))->flag;
			this->Edges.GetElem(i)->vex2->flag = this->Vexs.GetElem(this->Vexs.LocateElem(this->Edges.GetElem(i)->vex2))->flag;
		}
		SqList<Edge*> e = this->Edges; //e保存了G中没有的边
		while (G.Edges.GetLength() < this->Vexs.GetLength() - 1) { //循环n-1次
			Edge* etemp = e.GetElem(0);
			for (int i = 0; i < e.GetLength(); i++) {//选择e中最小的边
				if (e.GetElem(i)->weight < etemp->weight) {
					etemp = e.GetElem(i);
				}
			}
			//两个顶点同时在同时在G中出现并且标记相同（同一个连通分量），就是回路
			if (!(G.Vexs.LocateElem(etemp->vex1) != -1 && G.Vexs.LocateElem(etemp->vex2) != -1 && etemp->vex1->flag == etemp->vex2->flag)) {
				G.InsertVex(etemp->vex1);
				G.InsertVex(etemp->vex2);
				G.InsertEdge(etemp);
				//遍历所有顶点，更新标记
				for (int i = 0; i < this->Vexs.GetLength(); i++) {
					if (this->Vexs.GetElem(i)->flag == etemp->vex2->flag) {//把所有2的flag都改成1
						this->Vexs.GetElem(i)->flag = etemp->vex1->flag;
					}
				}
				//把新标记存在所有边的节点里
				for (int i = 0; i < e.GetLength(); i++) {//更新对应e中的节点的flag
					e.GetElem(i)->vex1->flag = this->Vexs.GetElem(this->Vexs.LocateElem(e.GetElem(i)->vex1))->flag;
					e.GetElem(i)->vex2->flag = this->Vexs.GetElem(this->Vexs.LocateElem(e.GetElem(i)->vex2))->flag;
				}
			}
			else {
			}
			e.DeleteElem(e.LocateElem(etemp));//删掉找到的这个最小的边
		}
		return G;
	}

	void print() {
		cout << "节点有：" << endl;
		Vexs.Traverse(showVex);
		cout << "边有：" << endl;
		Edges.Traverse(showEdge);
	}

	void printVexs() {
		cout << "节点有：" << endl;
		Vexs.Traverse(showVex);
	}

	void printEdges() {
		cout << "边有：" << endl;
		Edges.Traverse(showEdge);
	}

	void printEdgesWithDis() {
		cout << "边有：" << endl;
		Edges.TraverseEdge();
		//cout << "总距离：" << allDis << endl;
	}

	void test() {
		cout << "点测试：" << endl;
		Vex vex1, vex2, vex3, vex4;
		strcpy(vex1.Name, "北京");
		strcpy(vex2.Name, "上海");
		strcpy(vex3.Name, "广州");
		strcpy(vex4.Name, "深圳");
		InsertVex(&vex1);
		InsertVex(&vex2);
		InsertVex(&vex3);
		InsertVex(&vex4);
		Vexs.Traverse(showVex);
		//DeleteVex(vex3);
		//UpdateVex(vex1, "天津");
		//Vexs.Traverse(showVex);
		//UpdateVex(vex1, "北京");
		cout << "边测试：" << endl;
		Edge edge1, edge2, edge3;
		//北京到上海1000
		edge1.vex1 = &vex1;
		edge1.vex2 = &vex2;
		edge1.weight = 1000;
		//北京到广州2000
		edge2.vex1 = &vex1;
		edge2.vex2 = &vex3;
		edge2.weight = 2000;
		//广州到深圳100
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