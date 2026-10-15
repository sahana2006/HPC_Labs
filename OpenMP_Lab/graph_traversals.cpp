#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

const int V = 6;

// Static undirected graph
int graph[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0}
};

// BFS using queue and OpenMP
void BFS(int start) {
    vector<int> visited(V, 0);
    queue<int> q;

    visited[start] = 1;
    q.push(start);

    cout << "BFS Traversal: ";

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> nextVertices;

        // Process vertices of the current BFS level in parallel
        vector<int> currentLevel;
        while (!q.empty()) {
            currentLevel.push_back(q.front());
            q.pop();
        }

        #pragma omp parallel
        {
            vector<int> localNext;

            #pragma omp for schedule(static)
            for (int i = 0; i < levelSize; i++) {
                int u = currentLevel[i];

                for (int v = 0; v < V; v++) {
                    if (graph[u][v]) {
                        bool newlyVisited = false;

                        #pragma omp critical
                        {
                            if (!visited[v]) {
                                visited[v] = 1;
                                newlyVisited = true;
                            }
                        }

                        if (newlyVisited)
                            localNext.push_back(v);
                    }
                }
            }

            #pragma omp critical
            {
                nextVertices.insert(
                    nextVertices.end(),
                    localNext.begin(),
                    localNext.end()
                );
            }
        }

        for (int u : currentLevel)
            cout << u << " ";

        for (int v : nextVertices)
            q.push(v);
    }

    cout << '\n';
}

// Standard recursive DFS with OpenMP tasks
void DFSUtil(int u, vector<int>& visited) {
    bool process = false;

    #pragma omp critical
    {
        if (!visited[u]) {
            visited[u] = 1;
            process = true;
        }
    }

    if (!process)
        return;

    #pragma omp critical
    cout << u << " ";

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            #pragma omp task firstprivate(v) shared(visited)
            DFSUtil(v, visited);
        }
    }

    #pragma omp taskwait
}

void DFS(int start) {
    vector<int> visited(V, 0);

    cout << "DFS Traversal: ";

    #pragma omp parallel
    {
        #pragma omp single
        DFSUtil(start, visited);
    }

    cout << '\n';
}

int main() {
    omp_set_dynamic(0);
    omp_set_num_threads(4);

    BFS(0);
    DFS(0);

    return 0;
}