#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTEX 10


typedef struct graphNode {	//Vertex ������ ���� ����ü
	int vertex;
	int weight;
	struct graphNode* link;
} graphNode;

typedef struct graphType {	// graph ����ü
	int n;
	graphNode* adjList_H[MAX_VERTEX];
	int visited[MAX_VERTEX];	//�湮 ���θ� ���� �迭
} graphType;
 
typedef struct QNode {	//linked ť�� �̿�
	int data;
	struct QNode* link;
} QNode;

typedef struct {
	QNode* front, * rear;
} LQueueType;

LQueueType* createLinkedQueue()
{
	LQueueType* LQ;
	LQ = (LQueueType*)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

//�⺻���� ť ����
int isEmpty(LQueueType* LQ)
{
	if (LQ->front == NULL) {
		printf("\n ť�� ������ϴ�. \n");
		return 1;
	}
	else return 0;
}

void enQueue(LQueueType* LQ, int item)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

int deQueue(LQueueType* LQ)
{
	QNode* old = LQ->front;
	int item;
	if (isEmpty(LQ)) return 0;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}

void createGraph(graphType* g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTEX; v++) {
		g->visited[v] = false;
		g->adjList_H[v] = NULL;
	}
}

void insertVertex(graphType* g, int v)	//���� �׽�Ʈ
{
	if (((g->n) + 1) > MAX_VERTEX) {
		printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
		return;
	}
	g->n++;
}

void insertEdge(graphType* g, int u, int v, int weight)
{
	graphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("\n �׷����� ���� �����Դϴ�!");
		return;
	}
	node = (graphNode*)malloc(sizeof(graphNode));
	node->vertex = v;
	node->weight = weight;
	node->link = g->adjList_H[u];
	g->adjList_H[u] = node;
}

void print_grapgh(graphType* g)
{
	int i;
	graphNode* p;

	printf("Prim's algorithm�� �̿��� minimum cost spanning tree ����:\n");

	printf("  TV={");
	for (i = 0; i < 7; i++)
	{
		p = g->adjList_H[i];
		if (p == NULL)
			continue;
		else
		{
			while (p)
			{
				printf("( %d, %d ) ", i,  p->vertex);
				p = p->link;
			}
		}
	}
	printf("}\n");
	printf("  T={ 0 ");
	for (i = 0; i < 7; i++)
	{
		p = g->adjList_H[i];
		if (p == NULL)
			continue;
		else
		{
			while (p)
			{
				printf("%d ", p->vertex);
				p = p->link;
			}
		}
	}
	printf("}\n");

}



//����ġ�� �����۰� �湮���� �ʴ� ��带 �˻�
void Prime_adjList(graphType* g, int v)
{
	graphType* SpanTree;
	SpanTree = (graphType*)malloc(sizeof(graphType));


	graphNode* w;
	graphNode* s_edge = NULL;    //����ġ �ּҰ��� ã�� ���� ����

	int min_weight = 9999;

	int edge_cnt = 0;
	int i;
	int min_u;            //�ּҰ��� ã�������� ����

	createGraph(SpanTree);   //�׷��� �ʱ�ȭ
	for (i = 0; i < 7; i++)
		insertVertex(SpanTree, i);

	SpanTree->visited[v] = true;

	while (edge_cnt < 6) //n-1���� �ݺ�
	{

		for (i = 0; i < 7; i++)
		{
			//�湮�� ��� �߿� �ּ� ��� ã��

			if (SpanTree->visited[i] == false)      //�湮���� ���� ���� �ѱ�
				continue;

			for (w = g->adjList_H[i]; w; w = w->link)
			{
				if (SpanTree->visited[w->vertex] == true)   //�̹� �湮�� ��带 ����Ű�� ������� �ѱ��.
					continue;

				else if (w->weight < min_weight)   //��� ���Ͽ� ����ġ �ּҰ��� ã�´�
				{
					min_weight = w->weight;
					s_edge = w;
					min_u = i;
				}
			}
		}

		insertEdge(SpanTree, min_u, s_edge->vertex, s_edge->weight);  //�ּҰ� ����
		SpanTree->visited[s_edge->vertex] = true;    //���Ե� ���� �湮�Ѱ����� ������

		edge_cnt++;  min_weight = 30000;
	}

	print_grapgh(SpanTree);
}

void main()
{
	int i;
	graphType* Graph;
	Graph = (graphType*)malloc(sizeof(graphType));

	createGraph(Graph);
	for (i = 0; i < 7; i++)
		insertVertex(Graph, i);

	insertEdge(Graph, 0, 1, 3);
	insertEdge(Graph, 0, 2, 17);
	insertEdge(Graph, 0, 3, 6);

	insertEdge(Graph, 1, 0, 3);
	insertEdge(Graph, 1, 3, 5);
	insertEdge(Graph, 1, 6, 12);

	insertEdge(Graph, 2, 0, 17);
	insertEdge(Graph, 2, 4, 10);
	insertEdge(Graph, 2, 5, 8);

	insertEdge(Graph, 3, 0, 6);
	insertEdge(Graph, 3, 1, 5);
	insertEdge(Graph, 3, 4, 9);

	insertEdge(Graph, 4, 2, 10);
	insertEdge(Graph, 4, 6, 2);
	insertEdge(Graph, 4, 5, 4);

	insertEdge(Graph, 5, 2, 8);
	insertEdge(Graph, 5, 4, 4);
	insertEdge(Graph, 5, 6, 14);

	insertEdge(Graph, 6, 1, 12);
	insertEdge(Graph, 6, 4, 2);
	insertEdge(Graph, 6, 5, 14);

	printf("\n\n  Prime �˰��� ���� Ž�� >> ");
	Prime_adjList(Graph, 0);

	return 0;
}