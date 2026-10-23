//------------------------------------------------------------------
// Purpose:     This program demonstrates seven sorting algorithms.
// Author:      John Gauch
//------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
using namespace std;

//------------------------------------------------------------------
// Simple CPU timer for timing sort operations
//------------------------------------------------------------------
class Timer
{
public:
   void start_timer()
   {
      start = clock();
   }

   void end_timer()
   {
      end = clock();
   }

   double elapsed_cpu() const
   {
      return static_cast<double>(end - start) / CLOCKS_PER_SEC;
   }

private:
   clock_t start;
   clock_t end;
};

//------------------------------------------------------------------
// Check to see if data is sorted correctly
//------------------------------------------------------------------
bool data_sorted(int data[], int count)
{
   // Put specified count of random numbers into data array
   for (int index = 1; index < count; index++)
      if (data[index-1] > data[index])
         return false;
   return true;
}

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range)
{
   // Put random data values into array
   for (int index = 0; index < count; index++)
      data[index] = rand() % range;
}

//------------------------------------------------------------------
// Initialize data array with mostly sorted values
//------------------------------------------------------------------
void create_mostly_sorted_data(int data[], int count, int swaps)
{
   // Put sorted data values into array
   for (int index = 0; index < count; index++)
      data[index] = index;

   // Shuffle data by swapping random pairs of values
   for (int index = 0; index < swaps; index++)
   {
      int pos1 = rand() % count;
      int pos2 = rand() % count;
      int temp = data[pos1];
      data[pos1] = data[pos2];
      data[pos2] = temp;
   }
}

//------------------------------------------------------------------
// Read input file to initialize data array
//------------------------------------------------------------------
void read_data(string name, int data[], int &count, int &range)
{
   // Open input file
   ifstream din;
   din.open(name.c_str());
   if (din.fail())
      cout << "Error: could not open input file\n";

   // Read the data
   range = 0;
   din >> count;
   for (int i = 0; i < count; i++)
   {
      din >> data[i];
      if (data[i] > range)
	 range = data[i];
   }

   // Close the file
   din.close();
   range++;
}

//------------------------------------------------------------------
// Write data array to output file
//------------------------------------------------------------------
void write_data(string name, int data[], int count)
{
   // Open output file
   ofstream dout;
   dout.open(name.c_str());
   if (dout.fail())
      cout << "Error: could not open output file\n";

   // Write the data
   dout << count;
   for (int i = 0; i < count; i++)
   {
      if (i % 20 == 0)
	 dout << endl;
      dout << data[i] << " ";
   }

   // Close the file 
   dout.close();
}

//------------------------------------------------------------------
// Gnome sort algorithm
// Best case O(N) - sorted data
// Worst case O(N^2) - random data
// Average case O(N^2) - random data
//------------------------------------------------------------------
void gnome_sort(int data[], int low, int high)
{
   // Loop over array until sorted
   int index = low;
   while (index <= high)
   {
      // Move forward
      if (index == low || data[index-1] <= data[index])
         index++;

      // Swap and move backward
      else
      {
         int temp = data[index];
         data[index] = data[index-1];
         data[--index] = temp;
      }
   }
}

//------------------------------------------------------------------
// Basic bubble sort algorithm
// Best case O(N^2) - random data
// Worst case O(N^2) - random data
// Average case O(N^2) - random data
//------------------------------------------------------------------
void basic_bubble_sort(int data[], int low, int high)
{
   // Loop over array N times
   for (int count = low; count < high; count++)
   {
      // Loop over N elements in array 
      for (int index = low; index < high; index++)
      {
	 // Swap two data values if out of order
	 if (data[index] > data[index + 1])
	 {
	    int temp = data[index];
	    data[index] = data[index + 1];
	    data[index + 1] = temp;
	 }
      }
   }
}

//------------------------------------------------------------------
// Faster bubble sort algorithm
// Best case O(N) - sorted data
// Worst case O(N^2) - reverse sorted data
// Average case O(N^2) - random data
//------------------------------------------------------------------
void faster_bubble_sort(int data[], int low, int high)
{
   // Bubble largest value to the right N times
   int pass = 1;
   int exchange = 1;
   int count = high - low + 1;
   while ((pass < count) && (exchange > 0))
   {
      // Scan unsorted part of data array
      exchange = 0;
      for (int index = low; index <= high - pass; index++)
      {
	 // Swap two data values if out of order
	 if (data[index] > data[index + 1])
	 {
	    int temp = data[index];
	    data[index] = data[index + 1];
	    data[index + 1] = temp;
	    exchange++;
	 }
      }
      pass++;
   }
}

//------------------------------------------------------------------
// Insertion sort algorithm
// Best case O(N) - sorted data
// Worst case O(N^2) - reverse sorted data
// Average case O(N^2) - random data
//------------------------------------------------------------------
void insertion_sort(int data[], int low, int high)
{
   // Insert each element of unsorted list into sorted list
   for (int unsorted = low + 1; unsorted <= high; unsorted++)
   {
      // Select unsorted value to be inserted
      int value = data[unsorted];
      int posn = unsorted;

      // Make room for new data value
      while ((posn > 0) && (data[posn - 1] > value))
      {
	 data[posn] = data[posn - 1];
	 posn--;
      }

      // Put new value into array
      data[posn] = value;
   }
}

//------------------------------------------------------------------
// Selection sort algorithm
// Best case O(N^2) - random data
// Worst case O(N^2)  - random data
// Average case O(N^2) - random data
//------------------------------------------------------------------
void selection_sort(int data[], int low, int high)
{
   // Put smallest unsorted value at front of sorted list
   for (int first = low; first < high; first++)
   {
      // Find index of smallest value in unsorted array
      int smallest = first;
      for (int index = first + 1; index <= high; index++)
         if (data[index] < data[smallest])
            smallest = index;

      // Swap with first element in unsorted array
      int temp = data[first];
      data[first] = data[smallest];
      data[smallest] = temp;
   }
}

void selection_sort2(int data[], int low, int high)
{
   // Put largest unsorted value at end of sorted list
   for (int last = high; last > low; last--)
   {
      // Find index of largest value in unsorted array
      int largest = low;
      for (int index = low + 1; index <= last; index++)
	 if (data[index] > data[largest])
	    largest = index;

      // Swap with last element in unsorted array
      int temp = data[last];
      data[last] = data[largest];
      data[largest] = temp;
   }
}

//------------------------------------------------------------------
// Find median of 3 values (2.66 compares on average)
//------------------------------------------------------------------
int median3(int a, int b, int c)
{
   if (a < b)
   {
      if (a < c)
      {
         if (b < c)
            return b;
         else
            return c;
      }
      else
         return a;
   }
   else
   {
      if (a < c)
         return a;
      else
      {
         if (b < c)
            return c;
         else
            return b;
      }
   }
}

//------------------------------------------------------------------
// Partition function for quicksort
//------------------------------------------------------------------
void partition(int data[], int low, int high, int &mid)
{
#define HIGH_PIVOT

#ifdef HIGH_PIVOT
   // Use data[high] for pivot value
   int pivot = data[high];
#endif

#ifdef LOW_PIVOT
   // Use data[low] for pivot value
   int pivot = data[low];
   data[low] = data[high];
   data[high] = pivot;
#endif

#ifdef MID_PIVOT
   // Use data[mid] for pivot value
   mid = (low + high) / 2;
   int pivot = data[mid];
   data[mid] = data[high];
   data[high] = pivot;
#endif

#ifdef MEDIAN_PIVOT
   // Use median for pivot value
   mid = (low + high) / 2;
   int pivot = median3(data[low], data[mid], data[high]);
   if (data[low] == pivot)
   {
      data[low] = data[high];
      data[high] = pivot;
   }
   else if (data[mid] == pivot)
   {
      data[mid] = data[high];
      data[high] = pivot;
   }
#endif

   // Partition array into two parts
   int left = low;
   int right = high;
   while (left < right)
   {
      // Scan left to right
      while ((left < right) && (data[left] < pivot)) 
         left++;

      // Scan right to left
      while ((left < right) && (data[right] >= pivot)) 
         right--;

      // Swap data values
      int temp = data[left];
      data[left] = data[right];
      data[right] = temp;
   }

   // Swap pivot to mid
   mid = left;
   data[high] = data[mid];
   data[mid] = pivot;
}

//------------------------------------------------------------------
// Quicksort sort algorithm
// Best case O(NlogN) - random data
// Worst case O(N^2) - sorted data 
// Average case O(NlogN) - random data
//------------------------------------------------------------------
void quick_sort(int data[], int low, int high)
{
   // Check terminating condition
   if (low < high)
   {
      // Partition data into two parts
      int mid = 0;
      partition(data, low, high, mid);

      // Recursive calls to sort array
      quick_sort(data, low, mid - 1);
      quick_sort(data, mid + 1, high);
   }
}

//------------------------------------------------------------------
// Mergesort implementation with copy array
//------------------------------------------------------------------
void merge_sort2(int data[], int copy[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Divide the array and sort both halves
      int mid = (low + high) / 2;
      merge_sort2(data, copy, low, mid);
      merge_sort2(data, copy, mid + 1, high);

      // Initialize array indices
      int index1 = low;
      int index2 = mid + 1;
      int index = 0;

      // Merge smallest data elements into copy array
      while (index1 <= mid && index2 <= high)
      {
	 if (data[index1] < data[index2])
	    copy[index++] = data[index1++];
	 else
	    copy[index++] = data[index2++];
      }

      // Copy any remaining entries from the first half
      while (index1 <= mid)
	 copy[index++] = data[index1++];

      // Copy any remaining entries from the second half
      while (index2 <= high)
	 copy[index++] = data[index2++];

      // Copy data back from the temporary array
      for (index = 0; index < range; index++)
	 data[low + index] = copy[index];
   }
}

//------------------------------------------------------------------
// Mergesort implementation without copy array
// Best case O(NlogN) - random data
// Worst case O(NlogN) - random data
// Average case O(NlogN) - random data
//------------------------------------------------------------------
void merge_sort(int data[], int low, int high)
{
   // Check terminating condition
   int range = high - low + 1;
   if (range > 1)
   {
      // Allocate memory and call merge_sort2
      int *copy = new int[range];
      merge_sort2(data, copy, low, high);
      delete[]copy;
   }
}

//------------------------------------------------------------------
// Counting sort assuming data values between 0 and range-1
// Best case O(M+N) - random data
// Worst case O(M+N) - random data
// Average case O(M+N) - random data
//------------------------------------------------------------------
void counting_sort(int data[], int low, int high, int range)
{
   // Initialize data count array
   int *datacount = new int[range];
   for (int cindex = 0; cindex < range; cindex++)
      datacount[cindex] = 0;

   // Count number of occurrences of each data value
   for (int dindex = low; dindex <= high; dindex++)
      datacount[data[dindex]]++;

   // Generate output array
   int dindex = low;
   for (int cindex = 0; cindex < range; cindex++)
   {
      for (int index = 0; index < datacount[cindex]; index++)
	 data[dindex + index] = cindex;
      dindex += datacount[cindex];
   }
   delete[]datacount;
}

//------------------------------------------------------------------
// main program to test sorting functions
//------------------------------------------------------------------
int main()
{
   const int MAX_COUNT = 1000000;
   const int MAX_RANGE = 1000000;
   int data[MAX_COUNT];

   // Prompt user for sort parameters
   cout << "Enter number of data values [1.." << MAX_COUNT << "]:";
   int count;
   cin >> count;
   if (count > MAX_COUNT)
      count = MAX_COUNT;

   cout << "Enter range of data values [1.." << MAX_RANGE << "]:";
   int range;
   cin >> range;
   if (range > MAX_RANGE)
      range = MAX_RANGE;

   // Print input data menu
   cout << "Select initial data:\n"
      << "  r - random data\n"
      << "  m - mostly sorted data\n"
      << "  s - sorted data\n";
   char choice;
   cin >> choice;
   
   // Create input data
   if (choice == 'r') 
      create_random_data(data, count, range);
   else if (choice == 'm')
      create_mostly_sorted_data(data, count, count/10);
   else if (choice == 's')
      create_mostly_sorted_data(data, count, 0);
   write_data("sort.in", data, count);

   // Print sorting method menu
   cout << "Select sorting method:\n"
      << "  g - use gnome sort\n"
      << "  b - use basic bubble sort\n"
      << "  f - use faster bubble sort\n"
      << "  i - use insertion sort\n"
      << "  s - use selection sort\n"
      << "  q - use quick sort\n"
      << "  m - use merge sort\n" 
      << "  c - use counting sort\n";

   // Perform requested sort
   cin >> choice;
   Timer t;
   t.start_timer();
   switch (choice)
   {
   case 'g':
      gnome_sort(data, 0, count - 1);
      break;
   case 'b':
      basic_bubble_sort(data, 0, count - 1);
      break;
   case 'f':
      faster_bubble_sort(data, 0, count - 1);
      break;
   case 'i':
      insertion_sort(data, 0, count - 1);
      break;
   case 's':
      selection_sort(data, 0, count - 1);
      break;
   case 'q':
      quick_sort(data, 0, count - 1);
      break;
   case 'm':
      merge_sort(data, 0, count - 1);
      break;
   case 'c':
      counting_sort(data, 0, count - 1, range);
      break;
   }
   t.end_timer();
   cout << "CPU time = " << t.elapsed_cpu() << " sec\n";
 
   // Write output file
   write_data("sort.out", data, count);

   // Check data is sorted
   if (!data_sorted(data, count))
      cerr << "ERROR: Data not sorted correctly!\n";
}