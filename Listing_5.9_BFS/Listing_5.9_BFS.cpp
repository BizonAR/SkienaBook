/*
***************** ����� � ������ *********************
*/
#define MAXV 100

struct edgenode { // ��������� ��� ���������� � �����
	int y; // ����� ������� �� ����� �����
	int weight; // ��� �����
	struct edgenode *next; // ��������� �� ��������� ����������� �����
};

struct graph { // ������ ������ �����
	edgenode *edges[MAXV + 1]; // ������ ������� ����� ����������� ��������
	int degree[MAXV + 1]; // ������ �������� ������
	int nvertices; // ���������� ������
	int nedges; // ���������� �����
	bool directed; // ������?
};

// ������� ��� ������� ������ ��� ������ ���. 187
bool processed[MAXV + 1]; /* ������������ �������*/
bool discovered[MAXV + 1]; /* �������� ������� */
int parent[MAXV + 1]; /* ��������� �������� */

// ������� 5.8 ������������� ������ ��� ������ � ������ ���. 187
void initialize_search(graph *g)
{
	int i; /* ������� */
	for (i = 1; i <= g->nvertices; i++) {
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}
// ������������� ������������ �����
#include<queue>
// ����������� �������� (����� ���������� �� ����� �)
#define TRUE true
#define FALSE false

// ��������������� ������� ��������� ����� � ������
typedef void(*process_vertex_late)(int v);
typedef void(*process_vertex_early)(int v);
typedef void(*process_edge)(int x, int y);
int nedges = 0; // ���������� ����� ����� (�������������� ��� ������ BFS)

// ������� 5.9 ����� ����� � ������ ���. 188
void bfs(graph *g, int start, process_vertex_early pve, process_edge pe, process_vertex_late pvl)
{
	std::queue<int> q; /* ������� ������ ��� ��������� */
	int v; /* ������� ������� */
	int y; /* ��������� ������� */
	edgenode *p; /* ��������� ��������� */
	while (!q.empty()) // ������� �������
		q.pop();
	nedges = 0; // �������� ��� �������� ��������� �����
	q.push(start);
	discovered[start] = TRUE;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		pve(v);
		processed[v] = TRUE;
		p = g->edges[v];
		while (p != NULL) {
			y = p->y;
			if ((processed[y] == FALSE) || g->directed)
				pe(v, y);
			if (discovered[y] == FALSE) {
				q.push(y);
				discovered[y] = TRUE;
				parent[y] = v;
			}
			p = p->next;
		}
		pvl(v);
	}
}
// ������� 5.10 ������� ������������� ������� ���. 187
void r_process_vertex_late(int v)
{
	printf("processed vertex late %d\n", v);
}

// ������� 5.11 ������� ������������� ������� � ��������� ����� ���. 188
void r_process_vertex_early(int v)
{
	printf("processed vertex early %d\n", v);
}

void r_process_edge(int x, int y)
{

	printf("processed edge (%d, %d) \n", x, y);
	nedges++; // ������� ���������� ����� - �� �������� 5.12 ���. 188
}
