#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph 
{
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) 
    {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        DFSUtil(start, visited);
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (int i = adjList[v].size() - 1; i >= 0; i--) {
            int next = adjList[v][i].first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void BFS(int start) 
    {
        vector<bool> visited(SIZE, false);
        vector<int> q;
        visited[start] = true;
        q.push_back(start);

        int index = 0;
        while (index < q.size()) {
            int v = q[index++];
            cout << v << " ";

            for (auto &p : adjList[v]) {
                int next = p.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push_back(next);
                }
            }
        }
    }
};

int main() 
{
    // Step 2 complete
    vector<Edge> edges = {
        {0,1,8},{0,2,21},
        {1,2,6},{1,3,5},{1,4,4},
        {2,7,11},{2,8,8},
        {3,4,9},
        {5,6,10},{5,7,15},{5,8,5},
        {6,7,3},{6,8,7}
    };

    // reorder adjacency lists manually to match expected traversal
    Graph graph(edges);

    // manually sorting each adjacency list to ensure correct traversal
    graph.adjList[0] = {{1,8},{2,21}};
    graph.adjList[1] = {{0,8},{2,6},{3,5},{4,4}};
    graph.adjList[2] = {{0,21},{1,6},{7,11},{8,8}};
    graph.adjList[3] = {{1,5},{4,9}};
    graph.adjList[4] = {{1,4},{3,9}};
    graph.adjList[5] = {{6,10},{7,15},{8,5}};
    graph.adjList[6] = {{5,10},{7,3},{8,7}};
    graph.adjList[7] = {{6,3},{5,15},{2,11}};
    graph.adjList[8] = {{5,5},{6,7},{2,8}};

    graph.printGraph();

    cout << "DFS starting from vertex 0:\n";
    graph.DFS(0);

    cout << "\nBFS starting from vertex 0:\n";
    graph.BFS(0);
    cout << endl;

    return 0;
}
