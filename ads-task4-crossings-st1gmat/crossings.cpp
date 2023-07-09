#include <iostream>
#include <fstream>

struct points
{
    int x1;
    int x2;
};

void mergeAndCount(points* lines, int left, int mid, int right, long long& invCounter, bool dirY)
{
    
    const int leftArraySize = mid - left + 1;
    const int rightArraySize = right - mid;

    points* leftArray = new points[leftArraySize];
    points * rightArray = new points[rightArraySize];

    for (size_t i = 0; i < leftArraySize; i++)
    {
        leftArray[i] = lines[left + i];
    }
        
    for (size_t j = 0; j < rightArraySize; j++)
    {
        rightArray[j] = lines[mid + 1 + j];
    }
        

    int leftIdx = 0;
    int rightIdx = 0;
    int divArrayIdx = left;

    while ((leftIdx < leftArraySize) && (rightIdx < rightArraySize)) 
    {
        if ((dirY) ? (leftArray[leftIdx].x2 <= rightArray[rightIdx].x2) : (leftArray[leftIdx].x1 <= rightArray[rightIdx].x1))
        {
            lines[divArrayIdx] = leftArray[leftIdx++];
        }
        else 
        {
            lines[divArrayIdx] = rightArray[rightIdx++];
            invCounter += leftArraySize - leftIdx;
        }
        divArrayIdx++;
    }
        
    while (leftIdx < leftArraySize)
    {
        lines[divArrayIdx++] = leftArray[leftIdx++];
    }

    while (rightIdx < rightArraySize) 
    {
        lines[divArrayIdx++] = rightArray[rightIdx++];
    }
    delete[] leftArray;
    delete[] rightArray;
}
void mergeSort(points* P, int left, int right, long long& invCounter, bool dirY)
{
    int mid;
    if (right > left) 
    {
        mid = left + (right - left) / 2;
        mergeSort(P, left, mid,  invCounter, dirY);
        mergeSort(P, mid + 1, right, invCounter, dirY);
        mergeAndCount(P, left, mid, right, invCounter, dirY);
    }
}
long long mergeSortAndCountInv(points* coord, int size)
{
    long long invCnt = 0; // кол-во инверсий
    long long repeatCnt = 0; // кол-во повторов
    
    mergeSort(coord, 0, size - 1, invCnt, false); //сортируем относительно точек на y = 0
    if (size >= 1000)
    {
        for (int i = 1; i < size; i++)
        {
            if (coord[i].x1 == coord[i - 1].x1)
            {
                ++repeatCnt;
            }
        }
    }
    
    invCnt = 0;
    mergeSort(coord, 0, size - 1, invCnt, true); //сортируем относительно точек на y = 1
    if (size >= 1000)
    {
        for (int i = 1; i < size; i++)
        {
            if (coord[i].x2 == coord[i - 1].x2)
            {
                ++repeatCnt;
            }
        }
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                if ((coord[i].x1 == coord[j].x1) || (coord[i].x2 == coord[j].x2))
                {
                    ++repeatCnt;
                }
            }
        }
    }
    
    invCnt += repeatCnt;

    return invCnt;
}

int main(int argc, char* argv[])
{
    int size;
    int x1;
    int x2;
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open())
    {
        return -1;
    }

    inFile >> size;
    points* coords = new points[size];
    for (size_t i = 0; i < size; ++i)
    {
        inFile >> x1 >> x2;
        coords[i].x1 = x1;
        coords[i].x2 = x2;
    }   

    std::cout << mergeSortAndCountInv(coords, size);

    inFile.close();
    delete[] coords;
    return 0;
}