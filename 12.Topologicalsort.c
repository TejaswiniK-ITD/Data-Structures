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
// Function to display the ordering of vertices
void displayOrdering(struct Graph* graph) {
    printf("Ordering of vertices:\n");
    for (int i = 0; i < graph->numNodes; i++) {
        printf("%d: ", i);
        struct Node* temp = graph->adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
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

    displayOrdering(graph);

    return 0;
}
