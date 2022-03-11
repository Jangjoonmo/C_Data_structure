#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// 다항식 구조체
typedef struct {
	int coef;
	int expon;
	struct polyNode* link;
} polyNode;

// 다항식 헤더의 타입
typedef struct {
	int size;
	polyNode* head;
	polyNode* tail;
} ListType;

//  헤더 생성 함수
ListType* make_head()
{
	ListType* listPointer = (ListType*)malloc(sizeof(ListType));
	listPointer->size = 0;
	listPointer->head = listPointer->tail = NULL;
	return  listPointer;
}
// listPointer는 연결 리스트의 헤더를 가리키는 포인터, 

void insert_last(ListType* plist, int coef, int expon)
{
	polyNode* temp = (polyNode*)malloc(sizeof(polyNode));

	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void polysub(ListType* plist1, ListType* plist2, ListType* plist3)
{
	polyNode* a = plist1->head;
	polyNode* b = plist2->head;
	int sum;

	while (a && b) {
		if (a->expon == b->expon) {   		// a의 차수 == b의 차수
			sum = a->coef - b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {  	// a의 차수 > b의 차수 
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {				// a의 차수 < b의 차수
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)  // a중 남아있는 항들을 모두 결과 다항식으로 복사
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)  // b중 남아있는 항들을 모두 결과 다항식으로 복사
		insert_last(plist3, b->coef, b->expon);
}


// 리스트 출력
void poly_print(ListType* plist)
{
	polyNode* p;

	printf("두 다항식의 차 = ");
	for (p = plist->head; p != NULL; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}
//입력 받은 문자를 int배열에 복사한 후 insert_last함수로 넘겨주는 함수
void scanlist(ListType* list, int n) {
	printf("다항식%d 입력: ", n);
	char str[100] = { 0 };
	int num[100], i, cnt = 0;

	scanf("%[^\n]", str);  // gets_s(str) 와 동일

	for (i = 2; i > 1; cnt += i > 0)
		i = sscanf(str, "%d%*[\\^+-]%[^\n]", &num[cnt], str);
	// 다항식을 한꺼번에 입력받아 저장하기 위해 %*[\\^+-] 사용
	for (i = 0; i < cnt; i += 2) {
		insert_last(list, num[i], num[i + 1]);	//계수, 지수 순서대로 넘겨준다.
	}
	while (getchar() != '\n');
}
int main() {
	ListType* list1, * list2, * list3;

	// 연결 리스트 헤더 생성
	list1 = make_head();
	list2 = make_head();
	list3 = make_head();

	//list에 추가할 다항식 입력받기
	scanlist(list1, 1);	
	scanlist(list2, 2);

	polysub(list1, list2, list3);
	poly_print(list3);

	free(list1); free(list2); free(list3);

	return 0;
}