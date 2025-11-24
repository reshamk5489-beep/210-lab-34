#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE = 9;

struct Edge { int src, dest, weight; };
typedef pair<int,int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &e : edges) {
            adjList[e.src].push_back({e.dest, e.weight});
            adjList[e.dest].push_back({e.src, e.weight});
        }

        // Sort neighbors ascending by vertex index for BFS/printing
        for (int i = 0; i < SIZE; i++)
            sort(adjList[i].begin(), adjList[i].end(), [](Pair a, Pair b){ return a.first < b.first; });
    }

    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " --> ";
            for (auto &v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE,false);
        DFSUtil(start, visited);
    }

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        // Explore neighbors in reverse order to match expected DFS
        for (int i = adjList[v].size()-1; i >= 0; i--) {
            int next = adjList[v][i].first;
            if (!visited[next]) DFSUtil(next, visited);
        }
    }

    void BFS(int start) {
        vector<bool> visited(SIZE,false);
        vector<int> q;
        visited[start] = true;
        q.push_back(start);

        int index = 0;
        while(index < q.size()) {
            int v = q[index++];
            cout << v << " ";
            for(auto &p: adjList[v]) {
                int next = p.first;
                if(!visited[next]) {
                    visited[next] = true;
                    q.push_back(next);
                }
            }
        }
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,8},{0,2,21},
        {1,2,6},{1,3,5},{1,4,4},
        {2,7,11},{2,8,8},
        {3,4,9},
        {5,6,10},{5,7,15},{5,8,5},
        {6,7,3},{6,8,7}
    };

    Graph graph(edges);

    graph.printGraph();

    cout << "DFS starting from vertex 0:\n";
    graph.DFS(0);

    cout << "\nBFS starting from vertex 0:\n";
    graph.BFS(0);
    cout << endl;
    return 0;
}