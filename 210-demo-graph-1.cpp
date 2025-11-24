#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 9;

struct Edge 
{
    int src, dest, weight; // weight = travel time in minutes
};

typedef pair<int,int> Pair; // Creates alias 'Pair' for the pair<int,int> data

class Graph 
{
public:
    vector<vector<Pair>> adjList;      // a vector of vectors of Pairs to represent an adjacency list
    vector<string> stationNames;        // names of stations

    // Graph Constructor
    Graph(vector<Edge> const &edges, vector<string> const &names) 
    {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        stationNames = names;

        // add edges to the undirected graph
        for (auto &edge : edges) 
        {
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
    void printNetwork()
    {
        cout << "City Transportation Network Topology:\n";
        cout << "================================\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << stationNames[i] << " connects to:\n";
            for (auto &p : adjList[i])
            {
                cout << "  → " << stationNames[p.first] << " (Travel time: " << p.second << " min)\n";
            }
        }
        cout << endl;
    }

    // -------- DFS ----------
    void DFS(int start)
    {
        vector<bool> visited(SIZE, false); // tracks which nodes have been visited
        cout << "Network Trace (DFS) from " << stationNames[start] << ":\n";
        cout << "Purpose: Tracing possible travel paths through the network        \n";
        cout << "=======================================\n";
        DFSUtil(start, visited);
        cout << endl;
    }

    void DFSUtil(int v, vector<bool>& visited)
    {
        visited[v] = true; // mark current node as visited
        cout << "Inspecting " << stationNames[v] << "\n";

        // reverse iterate through adjacency list so smaller-index neighbors print first
        for (int i = adjList[v].size() - 1; i >= 0; i--)
        {
            int next = adjList[v][i].first; // get neighboring node
            if (!visited[next]) // visit only unvisited neighbors
                cout << "  → Potential travel to " << stationNames[next] << " - Time: " << adjList[v][i].second << " min\n";
        }

        // recursive DFS call
        for (int i = adjList[v].size() - 1; i >= 0; i--)
        {
            int next = adjList[v][i].first;
            if (!visited[next])
                DFSUtil(next, visited); // recursive DFS call
        }
    }

    // -------- BFS ----------
    void BFS(int start)
    {
        vector<bool> visited(SIZE, false);   // tracks visited nodes
        vector<int> q;                       // queue for BFS
        visited[start] = true;               // mark start as visited
        q.push_back(start);                  // enqueue start node

        cout << "\nLayer-by-Layer Network Inspection (BFS) from " << stationNames[start] << ":  \n";
        cout << "Purpose: Analyzing service areas by distance from source\n";
        cout << "=================================================\n";

        int index = 0;                       // index simulates queue front pointer
        while (index < q.size()) {           // loop until queue is empty
            int v = q[index++];              // dequeue
            cout << "Checking " << stationNames[v] << "\n";

            for (auto &p : adjList[v]) {     // explore neighbors
                int next = p.first;
                if (!visited[next]) {        // only enqueue unvisited nodes
                    visited[next] = true;
                    q.push_back(next);       // enqueue neighbor
                    cout << "  → Next reachable station: " << stationNames[next] << " - Time: " << p.second << " min\n";
                }
            }
        }
    }

    // -------- Shortest Path (Dijkstra) ----------
    void shortestPath(int start)
    {
        cout << "Shortest path from " << stationNames[start] << ":\n";

        vector<int> dist(SIZE, numeric_limits<int>::max()); // stores shortest distances
        dist[start] = 0;

        // min-heap priority queue: pair(distance, vertex)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &p : adjList[u])
            {
                int v = p.first;
                int w = p.second;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // print shortest distances
        for (int i = 0; i < SIZE; i++)
        {
            cout << start << " -> " << i << " : " << dist[i] << "\n";
        }
    }

    // -------- Minimum Spanning Tree (Prim's algorithm) ----------
    void minimumSpanningTree()
    {
        vector<int> key(SIZE, numeric_limits<int>::max());   // min weight to connect node
        vector<int> parent(SIZE, -1);                        // stores MST edges
        vector<bool> inMST(SIZE, false);                     // whether node is in MST

        key[0] = 0; // start from node 0

        for (int count = 0; count < SIZE - 1; count++)
        {
            // pick the minimum key node not in MST
            int u = -1;
            int minKey = numeric_limits<int>::max();
            for (int v = 0; v < SIZE; v++)
            {
                if (!inMST[v] && key[v] < minKey)
                {
                    minKey = key[v];
                    u = v;
                }
            }

            inMST[u] = true;

            // update key and parent for neighbors
            for (auto &p : adjList[u])
            {
                int v = p.first;
                int w = p.second;
                if (!inMST[v] && w < key[v])
                {
                    key[v] = w;
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree edges:\n";
        for (int i = 1; i < SIZE; i++)
        {
            cout << "Edge from " << stationNames[parent[i]] << " to " << stationNames[i] 
                 << " with capacity: " << key[i] << " units\n";
        }
    }
};

int main()
{
    // Step 5 complete
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        {0,1,8},{0,2,21},
        {1,2,6},{1,3,5},{1,4,4},
        {2,7,11},{2,8,8},
        {3,4,9},
        {5,6,10},{5,7,15},{5,8,5},
        {6,7,3},{6,8,7}
    };

    // Names of stations for output
    vector<string> stations = {
        "Central Station",
        "North Hub",
        "East Terminal",
        "South Station",
        "West Terminal",
        "Uptown Hub",
        "Downtown Hub",
        "Airport Station",
        "Harbor Station"
    };

    // Creates graph
    Graph graph(edges, stations);

    graph.minimumSpanningTree();

    return 0;
}