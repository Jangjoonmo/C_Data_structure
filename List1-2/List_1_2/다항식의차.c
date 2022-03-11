#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

// ���׽� ����ü
typedef struct {
	int coef;
	int expon;
	struct polyNode* link;
} polyNode;

// ���׽� ����� Ÿ��
typedef struct {
	int size;
	polyNode* head;
	polyNode* tail;
} ListType;

//  ��� ���� �Լ�
ListType* make_head()
{
	ListType* listPointer = (ListType*)malloc(sizeof(ListType));
	listPointer->size = 0;
	listPointer->head = listPointer->tail = NULL;
	return  listPointer;
}
// listPointer�� ���� ����Ʈ�� ����� ����Ű�� ������, 

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
		if (a->expon == b->expon) {   		// a�� ���� == b�� ����
			sum = a->coef - b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {  	// a�� ���� > b�� ���� 
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {				// a�� ���� < b�� ����
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	for (; a != NULL; a = a->link)  // a�� �����ִ� �׵��� ��� ��� ���׽����� ����
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)  // b�� �����ִ� �׵��� ��� ��� ���׽����� ����
		insert_last(plist3, b->coef, b->expon);
}


// ����Ʈ ���
void poly_print(ListType* plist)
{
	polyNode* p;

	printf("�� ���׽��� �� = ");
	for (p = plist->head; p != NULL; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}
//�Է� ���� ���ڸ� int�迭�� ������ �� insert_last�Լ��� �Ѱ��ִ� �Լ�
void scanlist(ListType* list, int n) {
	printf("���׽�%d �Է�: ", n);
	char str[100] = { 0 };
	int num[100], i, cnt = 0;

	scanf("%[^\n]", str);  // gets_s(str) �� ����

	for (i = 2; i > 1; cnt += i > 0)
		i = sscanf(str, "%d%*[\\^+-]%[^\n]", &num[cnt], str);
	// ���׽��� �Ѳ����� �Է¹޾� �����ϱ� ���� %*[\\^+-] ���
	for (i = 0; i < cnt; i += 2) {
		insert_last(list, num[i], num[i + 1]);	//���, ���� ������� �Ѱ��ش�.
	}
	while (getchar() != '\n');
}
int main() {
	ListType* list1, * list2, * list3;

	// ���� ����Ʈ ��� ����
	list1 = make_head();
	list2 = make_head();
	list3 = make_head();

	//list�� �߰��� ���׽� �Է¹ޱ�
	scanlist(list1, 1);	
	scanlist(list2, 2);

	polysub(list1, list2, list3);
	poly_print(list3);

	free(list1); free(list2); free(list3);

	return 0;
}