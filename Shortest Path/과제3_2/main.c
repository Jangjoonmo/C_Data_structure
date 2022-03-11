#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 7
#define INF 10000
#define FALSE 0
#define TRUE 1


int cost[][MAX_VERTICES] =
{//  A   B   C	 D   E	  F   G
	{0, 10, 7, INF, 15, INF, INF},
	{10, 0, INF, 5, 8, INF, INF},
	{7, INF, 0, INF, 6, INF, INF},
	{INF, 5, INF, 0, 12, 6, INF},
	{15, 8, 6, 12, 0, INF, 3},
	{INF, INF, INF, 6, INF, 0, 1},
	{INF, INF, INF, INF, 3, 1, 0}
};

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int n = MAX_VERTICES;
int pi[MAX_VERTICES];

 //다익스트라 알고리즘
int choose(void);
void shortestPath(int v);
void printPath(int src, int dest);

int main(void) {

	char src, dst;


	printf("출발 지역을 입력하세요: ");
	scanf(" %c", &src);
	printf("도착 지역을 입력하세요: ");
	scanf(" %c", &dst);

	shortestPath(src - 65);

	printf("Vertex %c에서 Vertex %c로 가는 최단 경로는 ", src, dst);

	printPath(src - 65, dst - 65);

	printf("%c이며, 이때 최단 거리는 %d입니다.",dst, distance[(dst - 65)]);

	return 0;
}

int choose(void) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}



void shortestPath(int v) {

	int i, u, w;

	for (i = 0; i < n; i++) {
		found[i] = FALSE;
		distance[i] = cost[v][i];
		if (distance[i] < INF) {
			pi[i] = v;
		}
	}

	found[v] = TRUE;
	distance[v] = 0;

	for (i = 0; i < n - 2; i++) {
		u = choose();

		found[u] = TRUE;

		for (w = 0; w < n; w++) {
			if (!found[w]) {
				if (distance[u] + cost[u][w] < distance[w]) {
					distance[w] = distance[u] + cost[u][w];
					pi[w] = u;
				}
			}
		}

	}

}


void printPath(int src, int dest) {

	if (src == dest) {
		return;
	}
	else {
		printPath(src, pi[dest]);
		printf("%c ", pi[dest] + 65);
	}

}