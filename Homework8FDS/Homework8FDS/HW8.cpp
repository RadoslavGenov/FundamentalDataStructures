#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

/*Merge Sort: */
void merge(std::vector<int> values, int leftFirst, int leftLast, int rightFirst, int rightLast, int& count);

void mergesort(std::vector<int> a, int start, int end, int& count) {  //no significant comparisons are done during splitting
	if (start < end) {
		int mid = (start + end) / 2;
		mergesort(a, start, mid, count);
		mergesort(a, mid + 1, end, count);
		merge(a, start, mid, mid + 1, end, count);
	}
}

void merge(std::vector<int> values, int leftFirst, int leftLast, int rightFirst, int rightLast, int& count) {
	std::vector<int> temparray(values.size());
	int index = leftFirst;
	int saveFirst = leftFirst;

	while ((leftFirst <= leftLast) && (rightFirst <= rightLast)) {//compare and select smallest from two subarrays

		if (values[leftFirst] < values[rightFirst]) {
			temparray[index] = values[leftFirst]; //smallest assigned to temp
			leftFirst++;
		}
		else
		{
			temparray[index] = values[rightFirst];
			rightFirst++;
		}
		index++;
		++count;  //count of comaparisons done during merge  
	}
	while (leftFirst <= leftLast) {
		temparray[index] = values[leftFirst];
		leftFirst++;
		index++;
	}
	while (rightFirst <= rightLast) {
		temparray[index] = values[rightFirst];
		rightFirst++;
		index++;
	}
	for (index = saveFirst; index <= rightLast; index++) {
		values[index] = temparray[index];
	}
}

/*Insertion Sort: */
void insertionSort(std::vector<int> A, int n, int& count)
{
	int i, j, index;
	for (i = 1; i < n; i++)
	{
		index = A[i];
		for (j = i - 1; j >= 0 && A[j] > index; j--)
		{
			A[j + 1] = A[j];
			++count;//comparison count++
		}
		A[j + 1] = index;
	}
}

/*Quick Sort: */
int partition(std::vector<int> arr, int l, int h, int& count)
{
	int x = arr[h];
	int i = (l - 1);
	for (int j = l; j <= h - 1; j++)
	{
		++count;//comparison count++
		if (arr[j] <= x)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[h]);
	return (i + 1);
}

void QSort(std::vector<int> A, int l, int h, int& count)
{
	if (l < h)
	{
		++count;
		int p = partition(A, l, h, count);
		QSort(A, l, p - 1, count);
		QSort(A, p + 1, h, count);
	}
}

/*Heap Sort: */
void maxHeapify(std::vector<int> a, int i, int n, int& count)
{
	int j, temp;
	temp = a[i];
	j = 2 * i;
	while (j <= n)
	{
		if (j < n && a[j + 1] > a[j]) {
			j = j + 1;
			++count;//comparison count++
		}
		if (temp > a[j]) {
			++count;//comparison count++
			break;
		}
		else if (temp <= a[j])
		{
			++count;//comparison count++
			a[j / 2] = a[j];
			j = 2 * j;
		}
	}
	a[j / 2] = temp;
	return;
}

void heapSort(std::vector<int> a, int n, int& count)
{
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		maxHeapify(a, 1, i - 1, count);
	}
}

void buildMaxHeap(std::vector<int> a, int n, int& count)
{
	int i;
	for (i = n / 2; i >= 1; i--)
	{
		maxHeapify(a, i, n, count);
	}
}

void vectors(int size) {
	// use time to generate the random sequence
	std::srand(unsigned(time(0)));
	int countQuickSort = 0, countMergeSort = 0, countHeapSort = 0, countInsertionSort = 0;
	int random;//random number
	for (int i = 0; i < 5; i++) {//create 5 vectors
		std::vector<int> v;
		for (int j = 0; j < size; j++) {
			random = rand();
			if (std::find(v.begin(), v.end(), random) != v.end())
			{// check if the number is not already contained in the vector
				j--;
			}
			else
			{
				v.push_back(random);
			}
		}
		buildMaxHeap(v, v.size() - 1, countHeapSort);
		heapSort(v, v.size() - 1, countHeapSort);
		mergesort(v, 0, v.size() - 1, countMergeSort);
		insertionSort(v, v.size(), countInsertionSort);
		QSort(v, 0, v.size() - 1, countQuickSort);
	}
	std::cout << "Size: " << size << "\t\tAverages:" << std::endl;
	std::cout << "QuickSort: " << (countQuickSort / 5) << " MergeSort: " << (countMergeSort / 5) << " HeapSort: " << (countHeapSort / 5) << " InsertionSort: " << (countInsertionSort / 5) << std::endl;
	std::cout << std::endl;
}

int main() {
	vectors(1000);
	vectors(10000);
	vectors(20000);
	return 0;
}