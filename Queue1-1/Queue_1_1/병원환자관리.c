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
	printf("입력대기\n1. 병원 도착\n2. 병원 퇴장\n3. 서비스 종료\n");
}
void sub_menu() {
	printf("1. 대기자 등록\n2. 취소\n");
	int n;
	scanf("%d", &n);

	if (n == 1) {
		printf("이름 입력 :  ");
		person temp;
		temp.name = malloc(sizeof(char) * 20);	//입력받은 이름을 저장하기 위한 temp 구조체
		scanf("%s", temp.name);
		addq(temp);
	}
	else
		printf("입력대기 화면으로 나갑니다.\n");
}
void select_menu(int n) {
	switch (n) {
	case 1:	// 병원 도착
		if (queueFull()) {	//큐가 꽉 차면 에러 메시지 출력
			printf("Service is not available\n");
			break;
		}
		sub_menu();	//Full이 아니면 sub_menu로 
		break;
	case 2:	// 병원 퇴장
		if (queueEmpty())	// 큐가 비어있으면 메시지 출력
			printf("There is no patient wating.\n");
		else {	
			person temp = deleteq();	//퇴장하는 사람을 담을 temp
			printf("환자 : %s\n", temp.name);
		}
		break;
	case 3:	//서비스 종료
		printf("종료");
		exit(0);
		break;
	default :
		printf("올바른 숫자를 입력하시오.\n");
	}
}
