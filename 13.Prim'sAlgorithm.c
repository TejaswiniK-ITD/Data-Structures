#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Structure to represent a node in the graph
struct Node {
    int dest;
    int weight;
    struct Node* next;
};

// Structure to represent the adjacency list of a node
struct AdjList {
    struct Node* head;
};

// Structure to represent the graph
struct Graph {
    int numNodes;
    struct AdjList* array;
};

// Function to create a new node
struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'n' nodes
struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = n;
    graph->array = (struct AdjList*)malloc(n * sizeof(struct AdjList));
    for (int i = 0; i < n; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}
// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST stored in parent[]
void printMST(int parent[], int** graph, int n) {
    printf("Edge   Weight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Function to construct and print MST for a graph represented using adjacency matrix
void primMST(struct Graph* graph) {
    int n = graph->numNodes;
    int* parent = (int*)malloc(n * sizeof(int)); // Array to store constructed MST
    int* key = (int*)malloc(n * sizeof(int));    // Key values used to pick minimum weight edge in cut
    int* mstSet = (int*)malloc(n * sizeof(int)); // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
 // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have n vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, n);
        // Add the picked vertex to the MST set
        mstSet[u] = 1;
        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        struct Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;
            if (mstSet[v] == 0 && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }

    // Print the constructed MST
    printMST(parent, graph, n);
}

int main() {
    int n, e; // n is number of nodes, e is number of edges
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &e);

    struct Graph* graph = createGraph(n);

    printf("Enter the edges and weights (src dest weight):\n");
    for (int i = 0; i < e; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    // Print the Minimum Spanning Tree using Prim's Algorithm
    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    primMST(graph);

    return 0;
}
