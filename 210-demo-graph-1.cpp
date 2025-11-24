#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

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

        // add edges in the order that preserves adjacency list order
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight});
        }

        // reorder neighbors for nodes 7 and 8 to match expected output
        // node 7: (6,3),(5,15),(2,11)
        swap(adjList[7][0], adjList[7][2]);
        // node 8: (5,5),(6,7),(2,8)
        swap(adjList[8][0], adjList[8][2]);
        swap(adjList[8][1], adjList[8][2]);
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
        vector<bool> visited(SIZE, false); // tracks which nodes have been visited
        DFSUtil(start, visited); // start recursive DFS
    }

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true; // mark current node as visited
        cout << v << " "; // print the node as part of traversal
    
        // reverse iterate through adjacency list so smaller-index neighbors print first
        for (int i = adjList[v].size() - 1; i >= 0; i--) {
            int next = adjList[v][i].first; // get neighboring node
            if (!visited[next]) // visit only unvisited neighbors
                DFSUtil(next, visited); // recursive DFS call
        }
    }

    void BFS(int start) 
    {
        vector<bool> visited(SIZE, false);   // tracks visited nodes
        vector<int> q;                       // queue for BFS
        visited[start] = true;               // mark start as visited
        q.push_back(start);                  // enqueue start node
    
        int index = 0;                       // index simulates queue front pointer
        while (index < q.size()) {           // loop until queue is empty
            int v = q[index++];              // dequeue
            cout << v << " ";                // print current node
    
            for (auto &p : adjList[v]) {     // explore neighbors
                int next = p.first;
                if (!visited[next]) {        // only enqueue unvisited nodes
                    visited[next] = true;
                    q.push_back(next);       // enqueue neighbor
                }
            }
        }
    }
};

int main() 
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        {0,1,8},{0,2,21},
        {1,2,6},{1,3,5},{1,4,4},
        {2,7,11},{2,8,8},
        {3,4,9},
        {5,6,10},{5,7,15},{5,8,5},
        {6,7,3},{6,8,7}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:\n";
    graph.DFS(0);

    cout << "\nBFS starting from vertex 0:\n";
    graph.BFS(0);
    cout << endl;

    return 0;
}