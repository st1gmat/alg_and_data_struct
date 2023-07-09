#include <iostream>

long long partition(int& n /* number */, int& k /* size */);

int main()
{
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    std::cout << partition(n, k);
    return 0;
}

long long partition(int& n /* number */, int& k /* size */)
{
		if(n < k)
		{
			std::swap(n, k);
		}
    long long* p = new long long[n + 1];
    long long* prev = new long long[n + 1];
    p[0] = 0;
    prev[0] = 0;
    std::fill(p + 1, p + n + 1, 0);
    std::fill(prev + 1, prev + n + 1, 0);
    for (int j = 1; j <= k; ++j)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i == j)
            {
                p[i] = 1;
            }
            else if (j > i)
            {
                p[i] = 0;
            }
            else
            {
                p[i] = prev[i - 1] + p[i - j];
            }

        }
        std::swap(p, prev);
        std::fill(p + 1, p + n + 1, 0);
    }
    long long res = prev[n];
    delete[] p;
    delete[] prev;
    return res;
}