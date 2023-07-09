#include <iostream>
#include <fstream>

template<typename T>
class Vector 
{
private:
    T* data;
    int size;
    int capacity;

    void resize(int newCapacity) 
    {
        T* newData = new T[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    ~Vector() 
    {
        delete[] data;
    }

    void push_back(const T& value) 
    {
        if (size == capacity)
        {
            int newCapacity = (capacity == 0) ? 1 : 2 * capacity;
            resize(newCapacity);
        }

        data[size] = value;
        size++;
    }

    void pop_back() 
    {
        if (size > 0) 
        {
            size--;
        }
    }

    T& operator[](int index) 
    {
        return data[index];
    }
    T& back() {
        return data[size - 1];
    }
    const T& operator[](int index) const
    {
        return data[index];
    }

    int getSize() const 
    {
        return size;
    }

    bool empty() const 
    {
        return size == 0;
    }

    void clear() 
    {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
};


class PriorityQueue 
{
private:
    struct Values 
    {
        int value;
        int index;

        Values(int value, int index) : value(value), index(index) {}
        Values() : value(0), index(0) {}
    };

    Vector<Values> heap;
    int* check_ind;
    int map_size;

    void resizeMap(int newSize) 
    {
        int* newMap = new int[newSize];
        for (int i = 0; i < map_size; ++i) 
        {
            newMap[i] = check_ind[i];
        }
        delete[] check_ind;
        check_ind = newMap;
        map_size = newSize;
    }

    void siftUp(int index) 
    {
        while (index > 0) 
        {
            int parentIndex = (index - 1) / 2;
            if (heap[parentIndex].value > heap[index].value) 
            {
                //swapNodes(index, parentIndex);
                std::swap(heap[index], heap[parentIndex]);
                check_ind[heap[index].index] = index;
                check_ind[heap[parentIndex].index] = parentIndex;
                index = parentIndex;
            }
            else 
            {
                break;
            }
        }
    }

    void siftDown(int index) 
    {
        int heapSize = heap.getSize();
        while (true) 
        {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int minIndex = index;

            if (leftChild < heapSize && heap[leftChild].value < heap[minIndex].value)
            {
                minIndex = leftChild;
            }

            if (rightChild < heapSize && heap[rightChild].value < heap[minIndex].value)
            {
                minIndex = rightChild;
            }

            if (minIndex != index) 
            {
                std::swap(heap[index], heap[minIndex]);
                check_ind[heap[index].index] = index;
                check_ind[heap[minIndex].index] = minIndex;
                index = minIndex;
            }
            else
            {
                break;
            }
        }
    }

public:
    PriorityQueue() : check_ind(nullptr), map_size(0) {}

    ~PriorityQueue() 
    {
        delete[] check_ind;
    }

    void push(int value, int index) 
    {
        Values n(value, index);
        heap.push_back(n);

        if (index >= map_size) 
        {
            int newMapSize = index + 1;
            resizeMap(newMapSize); // меняем размер
        }
        check_ind[index] = heap.getSize() - 1;

        siftUp(heap.getSize() - 1); // up
    }

    int extractMin() {
        if (heap.empty()) 
        {
            return INT_MIN;
        }

        int minValue = heap[0].value;
        int minIndex = heap[0].index;
        check_ind[minIndex] = -1; // -1 ==> убрали элемент

        if (heap.getSize() > 1) 
        {
            heap[0] = heap.back();
            check_ind[heap[0].index] = 0;
            heap.pop_back();
            siftDown(0);
        }
        else 
        {
            heap.clear();
        }

        return minValue;
    }

    void decreaseKey(int index, int newValue) 
    {
        if (index >= map_size) 
        {
            int newMapSize = index + 1;
            resizeMap(newMapSize);
        }

        int heapIndex = check_ind[index];
        if (heapIndex == -1) 
        {
            return; // не найден
        }

        int oldValue = heap[heapIndex].value;
        if (newValue < oldValue) 
        {
            heap[heapIndex].value = newValue;
            siftUp(heapIndex);
        }
    }
};



int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    PriorityQueue priorityQueue;

    char command[15];
    int x, y;
    int counter = 0;
    //int counter_ext = 0;

    while (inputFile >> command)
    {
        if (strcmp(command, "push") == 0)
        {
            inputFile >> x;
            priorityQueue.push(x, counter);
        }
        else if (strcmp(command, "extract-min") == 0)
        {
            int minValue = priorityQueue.extractMin();
            //counter_ext++;
            if (minValue == INT_MIN)
            {
                outputFile << "*\n";
            }
            else
            {
                outputFile << minValue << "\n";
            }
        }
        else if (strcmp(command, "decrease-key") == 0)
        {
            inputFile >> x >> y;
            priorityQueue.decreaseKey(x - 1, y);
        }
        counter++;

    }

    inputFile.close();
    outputFile.close();

    return 0;
}