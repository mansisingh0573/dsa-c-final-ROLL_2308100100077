#include <stdio.h>

#define MAX 100
#define INF 1000000

int cost[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];

void printPath(int node)
{
    if (parent[node] == -1)
    {
        printf("%d ", node);
        return;
    }

    printPath(parent[node]);
    printf("%d ", node);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize cost matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = INF;
        }
    }

    // Read graph
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        cost[u][v] = w;
    }

    int S, D;
    scanf("%d %d", &S, &D);

    // Initialization
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[S] = 0;

    // Dijkstra
    for (int count = 0; count < n; count++)
    {
        int u = -1;
        int minDist = INF;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                cost[u][v] != INF &&
                dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[D] == INF)
    {
        printf("UNREACHABLE\n");
    }
    else
    {
        printf("%d\n", dist[D]);
        printPath(D);
        printf("\n");
    }

    return 0;
}