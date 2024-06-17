#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int numNodes;
    struct Node* adjList[MAX_NODES];
    int visited[MAX_NODES];
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'n' nodes
struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = n;
    for (int i = 0; i < n; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Adding edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Adding edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}
// Breadth First Search traversal of the graph
void BFS(struct Graph* graph, int start) {
    // Create a queue for BFS
    int queue[MAX_NODES], front = -1, rear = -1;
    // Mark the current node as visited and enqueue it
    graph->visited[start] = 1;
    queue[++rear] = start;
    while (front != rear) {
        // Dequeue a vertex from queue
        int current = queue[++front];
        printf("%d ", current);
        // Get all adjacent vertices of the dequeued vertex current
        // If an adjacent has not been visited, then mark it visited
        // and enqueue it
        struct Node* temp = graph->adjList[current];
        while (temp != NULL) {
            int adjNode = temp->data;
            if (graph->visited[adjNode] == 0) {
                graph->visited[adjNode] = 1;
                queue[++rear] = adjNode;
            }
            temp = temp->next;
        }
    }
}

// Depth First Search traversal of the graph (recursive)
void DFS(struct Graph* graph, int current) {
    graph->visited[current] = 1;
    printf("%d ", current);
    struct Node* temp = graph->adjList[current];
    while (temp != NULL) {
        int adjNode = temp->data;
        if (graph->visited[adjNode] == 0) {
            DFS(graph, adjNode);
        }
        temp = temp->next;
    }
}

int main() {
    int n, e; // n is number of nodes, e is number of edges
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &e);

    struct Graph* graph = createGraph(n);

    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < e; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Breadth First Search traversal: ");
    BFS(graph, 0); // Starting BFS from node 0
    printf("\n");

    // Resetting visited array for DFS
    for (int i = 0; i < n; i++) {
        graph->visited[i] = 0;
    }
    printf("Depth First Search traversal: ");
    DFS(graph, 0); // Starting DFS from node 0
    printf("\n");

    return 0;
}
