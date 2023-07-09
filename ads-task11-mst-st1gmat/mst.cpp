#include <iostream>
#include<fstream>

struct Edge 
{
    int u, v, weight;
};

class make_set 
{
public:
    int* parent;
    int* rank;

    make_set(int n) 
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) 
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~make_set() 
    {
        delete[] parent;
        delete[] rank;
    }

    int find_set(int v) 
    {
        if (v == parent[v])
        {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) 
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
            {
                std::swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b])
            {
                rank[a]++;
            }
        }
    }
};

void merge(Edge* edges, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Edge* leftArray = new Edge[n1];
    Edge* rightArray = new Edge[n2];

    for (int i = 0; i < n1; i++)
    {
        leftArray[i] = edges[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        rightArray[j] = edges[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i].weight <= rightArray[j].weight) 
        {
            edges[k] = leftArray[i];
            i++;
        }
        else 
        {
            edges[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        edges[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        edges[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(Edge* edges, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(edges, left, mid);
        mergeSort(edges, mid + 1, right);
        merge(edges, left, mid, right);
    }
}


int kruskal(Edge* edges, int n, int m)
{
    make_set s(n);
    mergeSort(edges, 0, m - 1);

    int minWeight = 0;
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (s.find_set(u) != s.find_set(v))
        {
            minWeight += weight;
            s.union_sets(u, v);
        }
    }
    return minWeight;
}

int main(int argc, char* argv[]) 
{
    int n, m;
    std::ifstream inFile(argv[1]);
    //std::ifstream inFile("graph10.txt");

    inFile >> n >> m;

    Edge* edges = new Edge[m];

    for (int i = 0; i < m; i++) 
    {
        inFile >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    std::cout << kruskal(edges, n, m);

    delete[] edges;

    return 0;
}