#include <iostream>
#include <fstream>

struct data
{
    int val;
    int currMin;
    int currMax;
};

class Stack
{
private: 
    struct data* arr;
    int size_;
    int top_;
public:
    
    Stack();
    ~Stack();
    void resize(int new_size);
    bool isEmpty() const;
    bool isFull() const;
    void push(int n);
    int pop();
    int getMin() const;
    int getMax() const;
};

Stack::Stack()
{
    size_ = 100;
    arr = new data[size_];
    top_ = -1;
}

Stack::~Stack()
{
    delete[] arr;
}

void Stack::resize(int new_size)
{
    delete[] arr;
    arr = new data[new_size];
    size_ = new_size;
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
    if (top_ == 0)
    {
        arr[top_].currMin = n;
        arr[top_].currMax = n;
    }
    if (top_ > 0)
    {
        arr[top_].currMin = std::min(arr[top_ - 1].currMin, n);
        arr[top_].currMax = std::max(arr[top_ - 1].currMax, n);
    }
    arr[top_].val = n;
}

int Stack::pop()
{
    if (isEmpty())
    {
        //std::cout << "pop empty error;" << std::endl;
        return 0;
    }
    int item = arr[top_].val;
    --top_;
    return item;
}

int Stack::getMin() const
{
    if (isEmpty())
    {
        std::cout << "getMax empty error;" << std::endl;
        return 0;
    }
    return arr[top_].currMin;
}

int Stack::getMax() const
{
    if (isEmpty())
    {
        std::cout << "getMax empty error;" << std::endl;
        return 0;

    }
    return arr[top_].currMax;
}

class Queue
{
private:
    Stack inside;
    Stack out;
    int currMin;
    int currMax;
    
public:
    Queue(int size);
    int qMin();
    int qMax();
    void enqueue(int n);
    void dequeue();
    int diffMinMax();
};

Queue::Queue(int size)
{
    inside.resize(size);
    out.resize(size);
    currMin = 0;
    currMax = 0;
}

int Queue::qMin()
{
    if (inside.isEmpty() && out.isEmpty())
    {
        return 0;
    }

    if (inside.isEmpty() || out.isEmpty())
    {
        currMin = inside.isEmpty() ? out.getMin() : inside.getMin();
    }
    else
    {
        currMin = std::min(inside.getMin(), out.getMin());
    }

    return currMin;
}

int Queue::qMax()
{
    if (inside.isEmpty() && out.isEmpty())
    {
        return 0;
    }
    if (inside.isEmpty() || out.isEmpty())
    {
        currMax = inside.isEmpty() ? out.getMax() : inside.getMax();
    }
    else
    {
        currMax = std::max(inside.getMax(), out.getMax());
    }
    return currMax;
}

void Queue::enqueue(int n)
{
    if (inside.isFull())
    {
        std::cout << "overflow!" << std::endl;
        return;
    }

    inside.push(n);
}

void Queue::dequeue()
{
    if (out.isEmpty())
    {
        while (!inside.isEmpty())
        {
            out.push(inside.pop());
        }
        out.pop();
    }
    else
    {
        out.pop();
    }
}

int Queue::diffMinMax()
{
    if (inside.isEmpty() && out.isEmpty())
    {
        return 0;
    }
    return qMax() - qMin();
}


int main(int argc, char* argv[])
{
    int qSize;
    char cmd;
    int arg;

    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);

    if (!inFile.is_open() || !outFile.is_open())
    {
        std::cerr << "error op file..." << std::endl;
        return 1;
    }

    inFile >> qSize;

    if (qSize > 1e9)
    {
        return 1;
    }

    Queue queue(qSize);

    for (int i = 0; i < qSize; ++i)
    {
        inFile >> cmd;

        if (cmd == '+')
        {
            inFile >> arg;
            queue.enqueue(arg);
        }

        if (cmd == '-')
        {
            queue.dequeue();
        }

        if (cmd == '?')
        {
            outFile << queue.diffMinMax() << std::endl;
        }
    }

    outFile.close();
    inFile.close();

    return 0;
}