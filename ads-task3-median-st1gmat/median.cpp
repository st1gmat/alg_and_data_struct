#include <iostream>
#include <fstream>

class Stack
{
private:
    int* arr;
    int size_;
    int top_;
public:

    Stack();
    Stack(int size);

    ~Stack();
    bool isEmpty() const;
    bool isFull() const;
    void push(int n);
    int pop();
};

Stack::Stack()
{
    size_ = 100;
    arr = new int[size_];
    top_ = -1;
}

Stack::Stack(int size) :size_(size)
{
    arr = new int[size_];
    top_ = -1;
}
Stack::~Stack()
{
    delete[] arr;
}

bool Stack::isEmpty() const {
    return (top_ == -1);
}

bool Stack::isFull() const
{
    return (top_ == size_ - 1);
}

void Stack::push(int n)
{
    if (isFull())
    {
        return;
    }
    top_++;
    arr[top_] = n;
}

int Stack::pop()
{
    if (isEmpty())
    {
        return 0;
    }
    int item = arr[top_];
    --top_;
    return item;
}

struct student
{
    double value;
    int id;
};

void quickSort(student* data, int size)
{
    int left = 0;
    int right = size - 1;
    Stack lr(right - left + 1);

    lr.push(left);
    lr.push(right);

    while (!lr.isEmpty())
    {
        right = lr.pop();
        left = lr.pop();

        int i = left - 1;

        for (int j = left; j <= right - 1; ++j)
        {
            if (data[j].value <= data[right].value)
            {
                i++;
                std::swap(data[i].value, data[j].value);
                std::swap(data[i].id, data[j].id);
            }
        }
        std::swap(data[i + 1].value, data[right].value);
        std::swap(data[i + 1].id, data[right].id);

        int pivot = i + 1;

        if (pivot - 1 > left)
        {
            lr.push(left);
            lr.push(pivot - 1);
        }

        if (pivot + 1 < right)
        {
            lr.push(pivot + 1);
            lr.push(right);
        }
    }
}

void weakAverageBest(student* arr, int size, int& weak, int& mid, int& best)
{
    weak = (arr[0].value < arr[1].value) ? arr[0].id : arr[1].id;
    best = (arr[size - 1].value > arr[size - 2].value) ? arr[size - 1].id : arr[size - 2].id;
    int middle = size / 2;
    mid = (arr[middle - 1].value > arr[middle].value) ? arr[middle - 1].id : arr[middle].id;
}

int main(int argc, char* argv[])
{
    int size;
    int weak;
    int average;
    int best;
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open())
    {
        return -1;
    }

    inFile >> size;

    student* M = new student[size];

    for (int j = 0; j < size; j++)
    {
        inFile >> M[j].value;
        M[j].id = j + 1;
    }

    quickSort(M, size);
    weakAverageBest(M, size, weak, average, best);

    std::cout << weak << " " << average << " " << best << " " << std::endl;

    delete[] M;
    return 0;
}