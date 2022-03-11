#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 7

typedef struct {
	char* name;
} person;
person queue[MAX_QUEUE_SIZE];

bool queueEmpty();
bool queueFull();
void show_menu();
void sub_menu();
void select_menu(int);

int rear = 0; int front = 0;

void addq(person item) {
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}

person deleteq() {
	free(queue[front].name);
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

int main() {
	int num = 0;
	while (num != 3) {
		show_menu();
		scanf("%d", &num);
		select_menu(num);
	}
	return 0;
}

bool queueEmpty() {
	return rear == front ? 1 : 0;
}
bool queueFull() {
	return (rear + 1) % MAX_QUEUE_SIZE == front;
}
void show_menu() {
	printf("�Է´��\n1. ���� ����\n2. ���� ����\n3. ���� ����\n");
}
void sub_menu() {
	printf("1. ����� ���\n2. ���\n");
	int n;
	scanf("%d", &n);

	if (n == 1) {
		printf("�̸� �Է� :  ");
		person temp;
		temp.name = malloc(sizeof(char) * 20);	//�Է¹��� �̸��� �����ϱ� ���� temp ����ü
		scanf("%s", temp.name);
		addq(temp);
	}
	else
		printf("�Է´�� ȭ������ �����ϴ�.\n");
}
void select_menu(int n) {
	switch (n) {
	case 1:	// ���� ����
		if (queueFull()) {	//ť�� �� ���� ���� �޽��� ���
			printf("Service is not available\n");
			break;
		}
		sub_menu();	//Full�� �ƴϸ� sub_menu�� 
		break;
	case 2:	// ���� ����
		if (queueEmpty())	// ť�� ��������� �޽��� ���
			printf("There is no patient wating.\n");
		else {	
			person temp = deleteq();	//�����ϴ� ����� ���� temp
			printf("ȯ�� : %s\n", temp.name);
		}
		break;
	case 3:	//���� ����
		printf("����");
		exit(0);
		break;
	default :
		printf("�ùٸ� ���ڸ� �Է��Ͻÿ�.\n");
	}
}
