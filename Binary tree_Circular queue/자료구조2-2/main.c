
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 8	
// Level-order traversal�� addq�� 2���� ���� �� deleteq�� ����ǹǷ�
// MAX_QEUEUE_SIZE�� �ּ� 8�̻� (deepth * 2)�̾�� �Ѵ�.
// ex) MAX_QUEUE_SIZE�� 7�� ��쿣 6��° node�� 10�� ���� �� 13�� ���� �� Queue full�� �߻��Ѵ�.

typedef struct node* treePointer;
typedef struct node {	// ��� ����ü
	int data;
	treePointer leftChild, rightChild;
};
int front = 0; int rear = 0; // �������� ����

treePointer makeNode(int); //��� ���� �Լ�
void left_insert(treePointer, treePointer);	//parent�� left�� ��带 ����
void right_insert(treePointer, treePointer);	// prarent�� right�� ��带 ����
void levelOrder(treePointer);
void addq(treePointer);
treePointer deleteq(void);

treePointer Queue[MAX_QUEUE_SIZE];

int main() {
	// node�� ������ش�.
	treePointer root = makeNode(8);
	treePointer n1 = makeNode(4);
	treePointer n2 = makeNode(9);
	treePointer n3 = makeNode(2);
	treePointer n4 = makeNode(5);
	treePointer n5 = makeNode(10);
	treePointer n6 = makeNode(13);
	treePointer n7 = makeNode(1);
	treePointer n8 = makeNode(3);
	treePointer n9 = makeNode(6);
	treePointer n10 = makeNode(7);
	treePointer n11 = makeNode(11);
	treePointer n12 = makeNode(12);
	//�־��� binary tree�� �°� ��� ����
	left_insert(root, n1);
	right_insert(root, n2);
	left_insert(n1, n3);
	right_insert(n1, n4);
	left_insert(n2, n5);
	right_insert(n2, n6);
	left_insert(n3, n7);
	right_insert(n3, n8);
	left_insert(n4, n9);
	right_insert(n4, n10);
	left_insert(n5, n11);
	right_insert(n5, n12);

	printf("Level order traversal�� ���: ");
	levelOrder(root);
	return 0;
}

treePointer makeNode(int n) {
	treePointer newNode;
	newNode = (treePointer)malloc(sizeof(struct node));
	newNode->data = n;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}
void left_insert(treePointer parent, treePointer left) {
	parent->leftChild = left;
}
void right_insert(treePointer parent, treePointer right) {
	parent->rightChild = right;
}
void levelOrder(treePointer ptr) {
	if (!ptr) return;	// empty tree
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%d ", ptr->data);
			if (ptr->leftChild)
				addq(ptr->leftChild);
			if (ptr->rightChild)
				addq(ptr->rightChild);
		}
		else
			break;
	}
}
void addq(treePointer node) { 
	
	if (front == ((rear + 1) % MAX_QUEUE_SIZE)) {	// queue full
		printf("Queue is full.\n");
		exit(1);
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	Queue[rear] = node;
}
treePointer deleteq() {
	if (rear == front)
	{
		printf("Queue is empty.\n");
		exit(1);
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return Queue[front];
}