#include <random>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
#define RADIX 10

class DataList{
public:
	DataList(){}
	DataList(int number);
	int* bubbleSort();
	int* selectSort();
	int* insertSort();
	int* shellSort();
	int* quickSort();
	int* heapSort();
	int* mergeSort();
	int* radixSort();
	int *copy();
	void print(int*);
	void printOrigin();
	//quickSort
	int partition(int *a, const int low, const int high);
	void quick(int *a, const int left, const int right);
	//heapSort
	void heapAdjust(int *heap, int current, int end);
	//margeSort
	void merge(int* merge, int begin, int end);
	//general
	void swap(int &a, int &b){ int temp(a); a = b; b = temp;  exchangeTimes++; }
	void clear(){ sortTime = 0; exchangeTimes = 0; compareTimes = 0; }
private:
	vector<int> datalist;
	int num;
	double sortTime;
	long exchangeTimes;
	int compareTimes;
};

DataList::DataList(int number) :num(number), exchangeTimes(0), compareTimes(0)
{
	for (int i = 0; i < number; i++)
	{
		datalist.push_back(rand() % (number*10));
	}
}

int *DataList::copy()
{
	auto list = new int[num];
	for (int i = 0; i < num; i++) list[i] = datalist[i];
	return list;
}

int* DataList::bubbleSort()
{
	auto bubble = copy();
	auto t = clock();//开始计时
	bool exchange(false);
	for (int i = 0; i < num - 1; i++)
	{
		exchange = false;
		for (int j = 1; j < num; j++)
		{
			if (compareTimes++, bubble[j]<bubble[j - 1])
			{
				swap(bubble[j], bubble[j - 1]);
				exchange = true;
			}
		}
		if (!exchange) break;
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return bubble;
}

int* DataList::selectSort()
{
	auto select = copy();
	auto t = clock();
	for (int i = 0; i < num-1; i++)
	{
		int k = i;
		for (int j = i + 1; j < num; j++) if (compareTimes++, select[j] < select[k]) k = j;
		if (k != i) swap(select[i], select[k]);
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return select;
}

int* DataList::insertSort()
{
	auto insert = copy();
	auto t = clock();
	for (int i = 1; i < num; i++)
	{
		if (compareTimes++, insert[i] < insert[i - 1])
		{
			int temp(insert[i]), j(i);
			for (j = i - 1; j >= 0 && (compareTimes++, insert[j] > temp); --j) 
			{
				exchangeTimes++;
				insert[j + 1] = insert[j];
			}
			exchangeTimes++;
			insert[j + 1] = temp;
		}
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return insert;
}

int* DataList::shellSort()
{
	auto shell = copy();
	auto t = clock();
	for (int gap = num / 3 + 1; gap >= 1; gap = gap / 3 + 1)
	{
		for (int i = gap; i < num; i++)
		{
			if (compareTimes++, shell[i] < shell[i - gap])
			{
				int temp = shell[i], j = i - gap;
				while (j>=0 && shell[j]>temp)
				{
					exchangeTimes++;
					shell[j + gap] = shell[j];
					j -= gap;
				}
				exchangeTimes++;
				shell[j + gap] = temp;
			}
		}
		if (gap == 1)break;
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return shell;
}

int* DataList::quickSort()
{
	auto qsort = copy();
	auto t = clock();
	quick(qsort, 0, num - 1);
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return qsort;
}

int DataList::partition(int *a, const int low, const int high)
{
	int pivotpos = low;
	int pivot = a[low];
	for (int i = low + 1; i <= high; i++){
		if (a[i]<pivot && ++pivotpos != i){
			swap(a[pivotpos], a[i]);
			exchangeTimes++;  //exchange time
		}
		swap(a[low], a[pivotpos]);
		exchangeTimes++;  //exchange time
	}
	return pivotpos;
}

void DataList::quick(int *a, const int left, const int right)
{
	if (left < right){
		int pivotpos = partition(a, left, right);
		quick(a, left, pivotpos - 1);
		quick(a, pivotpos + 1, right);
	}
}

void DataList::heapAdjust(int* heap, int current, int end)
{
	int leftChild = (current << 1) + 1,
		rightChild = leftChild + 1,
		max = current;
	if (leftChild < end && (compareTimes++, heap[leftChild] > heap[max])) max = leftChild;
	if (rightChild < end && (compareTimes++, heap[rightChild] > heap[max])) max = rightChild;
	if (max != current)
	{
		swap(heap[max], heap[current]);
		heapAdjust(heap, max, end);
	}
}

int* DataList::heapSort()
{
	auto heap = copy();
	auto t = clock();
	for (int i = (num >> 1) - 1; i >= 0; i--) heapAdjust(heap, i, num);//建造堆
	for (int i = num - 1; i>=0; i--)
	{
		swap(heap[0], heap[i]);
		heapAdjust(heap, 0, i);
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return heap;
}

int* DataList::mergeSort()
{
	auto data = copy();
	auto t = clock();
	merge(data, 0, num - 1);
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return data;
}

void DataList::merge(int* data, int begin, int end)
{
	if (begin == end) return;
	int mid = (begin + end) >> 1;
	merge(data, begin, mid);
	merge(data, mid + 1, end);

	vector<int> temp;
	mid++;
	int i = begin, j = mid;
	while (i < mid && j <= end)
	{
		if (compareTimes++, data[i] < data[j]) temp.push_back(data[i++]);
		else temp.push_back(data[j++]);
	}

	while (i < mid) temp.push_back(data[i++]);
	while (j <= end)temp.push_back(data[j++]);

	for (int k = 0; k != temp.size(); k++) data[begin+k] = temp[k];
}

int* DataList::radixSort()
{
	auto data = copy();
	double t = clock();
	int base = 1;
	while (1)
	{
		vector<int> index[RADIX];
		bool zero(true);
		for (int i = 0; i < num; i++)
		{
			int v = (data[i] / base) % RADIX;
			if (v) zero = false;
			index[v].push_back(data[i]);
		}

		int k = 0;
		for (int i = 0; i < RADIX;i++)
		for (int j = 0; j < index[i].size(); j++)
			data[k++] = index[i][j];

		if (zero) break;
		else base *= RADIX;
	}
	sortTime = (double)(clock() - t) / (double)CLOCKS_PER_SEC;
	return data;
}

void DataList::print(int* data)
{
	int count = 10;
	for (int i = 0; i < num; i++)
	{
		cout << data[i];
		if (count == 0){ cout << endl; count = 10; }
		else { cout << "\t"; count--; }
	}
	cout << endl << endl;
	cout << "Exchange Times:  " << exchangeTimes << endl;
	cout << "Sort Time:       " << sortTime << endl;
	cout << "Compare Times:   " << compareTimes << endl;
	cout << endl;
}

void DataList::printOrigin()
{
	int count = 9;
	for (int i = 0; i < num; i++)
	{
		cout << datalist[i];
		if (count == 0){ cout << endl; count = 9; }
		else { cout << "\t"; count--; }
	}
	cout << endl << endl;
}