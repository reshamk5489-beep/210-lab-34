#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data

class Graph 
{
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) 
    {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:\n";
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // -------- DFS ----------
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        DFSUtil(start, visited);
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
    
        // reverse iterate
        for (int i = adjList[v].size() - 1; i >= 0; i--) {
            int next = adjList[v][i].first;
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    // -------- BFS ----------
    void BFS(int start) {
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
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{0,3,21},
        {2,3,6},{2,6,2},{5,6,6},
        {4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:\n";
    graph.DFS(0);

    cout << "\nBFS starting from vertex 0:\n";
    graph.BFS(0);

    return 0;
}
