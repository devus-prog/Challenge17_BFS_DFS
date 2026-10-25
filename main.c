
#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
char names[MAX][50];
int n;

// Breadth-First Search
void BFS(int start, int target) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int found = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS traversal: ");

    while (front < rear) {
        int current = queue[front++];

        printf("%s ", names[current]);

        if (current == target)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 &&
                !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\nBFS result: %s\n",
           found ? "File found" : "File not found");
}

// Depth-First Search
void DFSVisit(int current, int target,
              int visited[], int *found) {
    visited[current] = 1;

    printf("%s ", names[current]);

    if (current == target)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] == 1 &&
            !visited[i]) {
            DFSVisit(i, target, visited, found);
        }
    }
}

void DFS(int start, int target) {
    int visited[MAX] = {0};
    int found = 0;

    printf("\nDFS traversal: ");

    DFSVisit(start, target, visited, &found);

    printf("\nDFS result: %s\n",
           found ? "File found" : "File not found");
}

int main(void) {
    int start, target;

    printf("FILE SYSTEM SEARCH USING BFS AND DFS\n");

    printf("Enter number of nodes (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter name of node %d (no spaces): ", i);
        scanf("%49s", names[i]);
    }

    printf("\nEnter adjacency matrix (%d x %d):\n", n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                printf("Enter only 0 or 1.\n");
                return 1;
            }
        }
    }

    printf("\nNodes:\n");
    for (int i = 0; i < n; i++) {
        printf("%d = %s\n", i, names[i]);
    }

    printf("\nEnter starting node index: ");
    if (scanf("%d", &start) != 1 ||
        start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    char targetName[50];
    printf("Enter file/directory name to search: ");
    scanf("%49s", targetName);

    target = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(names[i], targetName) == 0) {
            target = i;
            break;
        }
    }

    if (target == -1) {
        printf("\nThe specified file is not in the graph.\n");
        return 0;
    }

    BFS(start, target);
    DFS(start, target);

    return 0;
}
