// C++ program to print DFS traversal from
// a given vertex in a given graph
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

#define NOT_SET 1000000

using namespace std;



bool sortBySecond(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

class Graph {
public:
	map<int, bool> visited;
	map<int, list<int> > adj;
    map<int, list<pair<int, int>>> adj_;
    map<int, int> distanceToVert;
    list<int> sorted;
    list<pair<int, int>> edges;


	// Function to add an edge to graph
	void addEdge(int v, int w);

    void addEdge(int v, int w, int weight);

    void print();

    void resetOutput();
    
    void resetDistance();
    
	void DFS(int v);

    void BFS(int v);

    void Prim(int v);

    void Dijkstra(int startingPoint);
};

void Graph::resetOutput() {
    visited.clear();
    sorted.clear();
}

void Graph::addEdge(int v, int w){
	// Add w to v’s list.
	adj[v].push_back(w);
}

void Graph::addEdge(int v, int w, int edgeWeight){
    adj_[v].emplace_back(int(w), int(edgeWeight));
}

void Graph::print(){
    for (auto i : sorted){
        cout << i << " ";
    }
    cout << endl;
}

void Graph::resetDistance(){
    for (int i = 0; i < adj_.size(); ++i) {
        distanceToVert[i] = NOT_SET;
    }
}

void Graph::DFS(int v){
	visited[v] = true;
    sorted.push_back(v);
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFS(*i);
}

void Graph::BFS(int v){
    resetOutput();
    list<int> queue;
    visited[v] = true;
    queue.push_front(v);

    while (!queue.empty()){
        list<int>::iterator i;
        for (i = adj[queue.front()].begin(); i != adj[queue.front()].end(); ++i)
            if (!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        sorted.push_back(queue.front());
        queue.pop_front();
    }
}

void Graph::Dijkstra(int startingPoint) {
    resetOutput();
    resetDistance();
    distanceToVert[startingPoint] = 0;
    vector<int> queue;
    queue.push_back(startingPoint);

    int prev_parent = startingPoint;
    for (int i = 0; i < queue.size(); ++i){
        int parent = queue[i];
        edges.push_back((prev_parent, parent));
        if (visited[parent]) continue;
        visited[parent] = true;
        vector<pair<int, int>> temp_queue;
        for (auto child:adj_[parent]) {
            if (distanceToVert[child.first] < distanceToVert[parent] + child.second) continue;
            distanceToVert[child.first] = distanceToVert[parent] + child.second;
            if (visited[child.first]) continue;
            temp_queue.push_back(child);
        }
        sort(temp_queue.begin(), temp_queue.end(), sortBySecond);
        for (auto element : temp_queue){
            queue.insert(queue.begin() + i, element.first);
        }
    }
}

// Driver code
int main()
{
	// Create a graph given in the above diagram
	Graph g;
	g.addEdge(0, 1, 4);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 2, 3);
	g.addEdge(2, 1, 1);
	g.addEdge(2, 3, 5);
	g.addEdge(1, 3, 2);
    g.addEdge(3, 3, 2);
    g.addEdge(1, 0, 10);

	cout << "Following is Depth First Traversal"
			" (starting from vertex 2) \n";

	// Function call
	g.DFS(2);
    g.print();
    g.resetOutput();


    g.BFS(2);
    g.print();

    g.Dijkstra(0);
    for (int i = 0; i < g.distanceToVert.size(); ++i) {
        cout << i << " " << g.distanceToVert[i] << endl;
    }

//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Points Array Example");
//    window.setFramerateLimit(30);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//
//
//        window.clear();
//
//
//        window.display();
//    }

	return 0;
}
