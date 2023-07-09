#include <iostream>
#include <fstream>
class Node
{
public:
    int key;
    Node* next;

    Node(int key) : key(key), next(nullptr) {}
};

class hashTable
{
private:
    static const int tableSize = 1001;
    Node** table;

public:
    hashTable()
    {
        table = new Node * [tableSize]();
    }

    ~hashTable() {
        for (int i = 0; i < tableSize; ++i)
        {
            Node* node = table[i];
            while (node != nullptr)
            {
                Node* prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] table;
    }

    static int hashFunction(int key)
    {
        return std::abs(key) % tableSize;
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        Node* node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return;
            }
            node = node->next;
        }
        node = new Node(key);
        node->next = table[index];
        table[index] = node;
    }

    void erase(int key)
    {
        int index = hashFunction(key);
        Node* node = table[index];
        Node* prev = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                if (prev == nullptr)
                {
                    table[index] = node->next;
                }
                else
                {
                    prev->next = node->next;
                }
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
    }

    bool find(int key)
    {
        int index = hashFunction(key);
        Node* node = table[index];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return true;
            }
            node = node->next;
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    /*std::ifstream inFile("input7.txt");
    std::ofstream outFile("output.txt");*/
    int n;
    inFile >> n;
    hashTable tab;
    char command;
    for (int i = 0; i < n; i++)
    {
        int value;
        inFile >> command;
        if (command == '+')
        {
            inFile >> value;
            tab.insert(value);
        }
        else if (command == '-')
        {
            inFile >> value;
            tab.erase(value);
        }
        else if (command == '?')
        {
            inFile >> value;
            if (tab.find(value))
            {
                outFile << "true" << "\n";
            }
            else
            {
                outFile << "false" << "\n";
            }
        }
    }
    inFile.close();
    outFile.close();
    return 0;
}
