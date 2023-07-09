#include <iostream>
#include <fstream>

int quickSelect(int* arr, int left, int right, int k)
{
	while (left != right) 
	{
		int pivotVal = arr[(left + right) / 2];
		int i = left;
		int j = right;

		while (i <= j) 
		{
			while (arr[i] < pivotVal)
			{
				++i;
			}
			while (arr[j] > pivotVal)
			{
				--j;
			}
			if (i <= j)
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				++i;
				--j;
			}
		}

		if (k <= j) 
		{
			right = j;
		}
		else if (k >= i) 
		{
			left = i;
		}
		else
		{
			return arr[k];
		}
	}

	return arr[left];
}

void quickSort(int* arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;
	if (arr[mid] < arr[left])
	{
		int temp = arr[left];
		arr[left] = arr[mid];
		arr[mid] = temp;
	}
	if (arr[right] < arr[left])
	{
		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
	}
	if (arr[right] < arr[mid])
	{
		int temp = arr[mid];
		arr[mid] = arr[right];
		arr[right] = temp;
	}

	int pivotVal = arr[mid];

	int i = left;
	int j = right;
	while (i <= j)
	{
		while (arr[i] < pivotVal)
		{
			++i;
		}
		while (arr[j] > pivotVal)
		{
			--j;
		}
		if (i <= j)
		{
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			++i;
			--j;
		}
	}
	quickSort(arr, left, j);
	quickSort(arr, i, right);
}

int main(int argc, char* argv[])
{
	int k1;
	int k2;
	int n;
	int A;
	int B;
	int C;
	int x1;
	int x2;
	int* arr;
	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);

	/*std::ifstream inFile("input9.txt");
	std::ofstream outFile("output.txt");*/

	if (!inFile.is_open())
	{
		return -1;
	}
	inFile >> n >> k1 >> k2 >> A >> B >> C >> x1 >> x2;
	//n = 15;
	arr = new int[n];
	arr[0] = x1;
	arr[1] = x2;

	for (size_t i = 2; i < n; ++i)
	{
		arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
	}
	/*for (size_t i = 99999; i < 100011; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << std::endl;*/
	/*for (size_t i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << std::endl;*/
	/*Timer timer;
	timer.start();*/
	quickSelect(arr, 0, n - 1, k1 - 1);

	quickSelect(arr, k1 - 1, n - 1, k2 - 1);

	quickSort(arr, k1 - 1, k2 - 1);
	//std::cout << counter << std::endl;
	
	/*for (size_t i = 99999; i < 100011; i++)
	{
		std::cout << arr[i] << " ";
	}std::cout << std::endl;*/
	//for (size_t i = 0; i < n; i++)
	//{
	//	std::cout << arr[i] << " ";
	//}std::cout << std::endl;

	for (size_t k = k1 - 1; k < k2; ++k) 
	{
		if (k == k2 - 1)
		{
			outFile << arr[k];
			break;
		}
		outFile << arr[k] << " ";
	}
	//timer.stop();
	//std::cout << "Seconds: " << timer.elapsedSeconds() << std::endl;
	//std::cout << "Milliseconds: " << timer.elapsedMilliseconds() << std::endl;
	inFile.close();
	outFile.close();
	delete[] arr;

	return 0;
}