#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUCKET 13
typedef struct {
	char name[30];
}hashTable;

unsigned int stringToInt(char* key);
int hashFunction(int x);
void searchHashTable(hashTable* HT, char* item);
void addHashTable(hashTable* HT, char* newItem);
void printHashTable(hashTable* HT);

int main()
{
	hashTable HT[BUCKET] = { "" };	//slot�� 1�̹Ƿ� �ٷ� �ʱ�ȭ
	addHashTable(HT, "do");
	addHashTable(HT, "for");
	addHashTable(HT, "if");
	addHashTable(HT, "case");
	addHashTable(HT, "else");
	addHashTable(HT, "return");
	addHashTable(HT, "function");

	printHashTable(HT);

	searchHashTable(HT, "do");
	searchHashTable(HT, "for");
	searchHashTable(HT, "if");
	searchHashTable(HT, "case");
	searchHashTable(HT, "else");
	searchHashTable(HT, "return");
	searchHashTable(HT, "function");

	return 0;
}

unsigned int stringToInt(char* key) {
	int number = 0;
	while (*key)
		number += (int)*key++;
	return number;
}

int hashFunction(int x) {
	int modulo = BUCKET;
	return x % modulo; // x mod M
}

void addHashTable(hashTable* HT, char* newItem) {
	int hIndex = hashFunction(stringToInt(newItem));
	bool found = false;

	if (strcmp(HT[hIndex].name, "") == 0)
		strcpy(HT[hIndex].name,newItem);
	else	// overflow �߻� ��
	{		//linear probing ���
		while ( strcmp(HT[hIndex].name,"") != 0 && !found) {
			if (strcmp(HT[hIndex].name ,newItem) == 0)//�ߺ��Ǵ� ���� �ִ���
				found = true;
			else
				hIndex = (hIndex + 1) % BUCKET;	// 1�� ����
		}//end of while
		if (found){	// �ߺ��Ǵ� name�� ���� ���
			printf("Duplicate items are not allowed.");
			exit(0);
		}
		else
			strcpy(HT[hIndex].name, newItem);
	}//end of else

}
void printHashTable(hashTable* HT) {
	printf("==================================\n");
	for (int i = 0; i < BUCKET ; i++)
		printf("%d			%s\n", i, HT[i].name);
	printf("==================================\n");
}
void searchHashTable(hashTable* HT, char* newItem) {

	int hIndex = hashFunction(newItem), location = -1, cnt = 0;
	bool found = false;

	while (!found && cnt != BUCKET) {	//cnt�� ���� bucket�� ������ �ݺ�

		if (strcmp(HT[hIndex].name, newItem) == 0) {
			location = hIndex;
			found = true;
		}

		hIndex = (hIndex + 1) % BUCKET;
		cnt++;
	}

	if (location == -1) {
		printf("\"%s\" is not founded.\n", newItem);
	}
	else {
		printf("Ž�� %s: ��ġ = %d\n", newItem, location);
	}

}