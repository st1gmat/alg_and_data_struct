#include <iostream>
#include <fstream>

void lsd_sort(char** str, int n, int m, int k)
{
    char** sorted = new char* [n + 1];
    for (int i = m - 1; i >= m - k; --i)
    {
        int C[CHAR_MAX]{ 0 };
        for (size_t j = 0; j < n; ++j)
        {
            ++C[static_cast<int>(str[j][i])];
        }

        int count = 0;
        for (size_t j = 0; j < CHAR_MAX; ++j)
        {
            int tmp = C[j];
            C[j] = count;
            count += tmp;
        }

        for (size_t j = 0; j < n; ++j)
        {
            sorted[C[static_cast<int>(str[j][i])]] = str[j];
            C[static_cast<int>(str[j][i])]++;
        }

        for (size_t j = 0; j < n; ++j)
        {
            str[j] = sorted[j];
        }
    }
    delete[] sorted;
}

int main(int argc, char* argv[])
{
    std::ifstream inFile(argv[1]/*"input9.txt"*/);
    std::ofstream outFile(argv[2]/*"output2323232.txt"*/);
    int n, m, k;

    inFile >> n >> m >> k;
    char** str = new char* [n + 1];
    for (size_t i = 0; i < n; ++i)
    {
        str[i] = new char[m + 1];
    }
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            inFile >> str[j][i];
        }
    }

    lsd_sort(str, n, m, k);
    for (size_t i = 0; i < n; i++)
    {
        outFile << str[i][0];
    }

    for (int i = 0; i < n; ++i)
    {
        delete[] str[i];
    }
    delete[] str;

    return 0;
}