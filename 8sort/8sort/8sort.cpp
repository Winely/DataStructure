#include "Data.h"

int main()
{
	cout << "============================================" << endl;
	cout << "       1  -  Generate Datalist              " << endl;
	cout << "       2  -  Bubble Sort                    " << endl;
	cout << "       3  -  Insert Sort                    " << endl;
	cout << "       4  -  Select Sort                    " << endl;
	cout << "       5  -  Shell Sort                     " << endl;
	cout << "       6  -  Quick Sort                     " << endl;
	cout << "       7  -  Heap Sort                      " << endl;
	cout << "       8  -  Merge Sort                     " << endl;
	cout << "       9  -  Radix Sort                     " << endl;
	cout << "       10 -  Reset Datalist                 " << endl;
	cout << "       11 -  Show Origin Datalist           " << endl;
	cout << "       12 -  Quit                           " << endl;
	cout << "============================================" << endl << endl;
	
	DataList *datalist = nullptr;
	int op;
	while (true)
	{
		cout << "please input your operation: ";
		cin >> op;
		if (op == 12) return 0;
		if (!datalist) op = 1;
		switch (op)
		{
		case 10:	//Reset Datalist
			delete datalist;
		case 1:		//Generate Datalist
			cout << "Please input the size of the datalist:";
			int size;
			cin >> size;
			datalist = new DataList(size);
			break;
		case 2:		//Bubble Sort
			datalist->print(datalist->bubbleSort()); break;
		case 3:		//Insert Sort
			datalist->print(datalist->insertSort()); break;
		case 4:		//Select Sort
			datalist->print(datalist->selectSort()); break;
		case 5:		//Shell Sort
			datalist->print(datalist->shellSort()); break;
		case 6:		//Quick Sort
			datalist->print(datalist->quickSort()); break;
		case 7:		//Heap Sort
			datalist->print(datalist->heapSort()); break;
		case 8:		//Merge Sort
			datalist->print(datalist->mergeSort());  break;
		case 9:		//Radix Sort
			datalist->print(datalist->radixSort()); break;
		case 11:	//Show Origin Datalist
			datalist->printOrigin(); break;
		default:
			break;
		}
		datalist->clear();
		cout << "------------------------------------------" << endl;
	}
}