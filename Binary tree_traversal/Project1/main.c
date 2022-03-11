
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {	// 노드 구조체
	int data;
	treePointer leftChild, rightChild;
};

void inorder(treePointer);	//중위 순회 출력
void preorder(treePointer);	// 전위 순회 출력
void postorder(treePointer); // 후위 순회 출력
struct node* makeNode(int); //노드 생성 함수
void left_insert(treePointer, treePointer);	//parent의 left에 노드를 삽입
void right_insert(treePointer, treePointer);	// prarent의 right에 노드를 삽입

int main() {
	// node를 만들어준다.
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
	//주어진 binary tree에 맞게 노드 연결
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
	
	//예상 결과 1 2 3 4 6 5 7 8 11 10 12 9 13
	printf("Inorder traversal의 결과: ");
	inorder(root);
	printf("\n");

	//예상 결과 8 4 2 1 3 5 6 7 9 10 11 12 13
	printf("Preorder traversal의 결과: ");
	preorder(root);
	printf("\n");

	//예상 결과 1 3 2 6 7 5 4 11 12 10 13 9 8
	printf("Postorder traversal의 결과: ");
	postorder(root);
	printf("\n");

	return 0;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
	}
	return;
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
	return;
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%d ", ptr->data);
	}
	return;
}
struct node* makeNode(int n) {
	treePointer newNode = (treePointer)malloc(sizeof(struct node));
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