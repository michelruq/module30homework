#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <future>

using namespace std;

bool make_thread = true;

void quicksort(int *array, long left, long right) {
   if(left >= right) return;
   long left_bound = left;
   long right_bound = right;

   long middle = array[(left_bound + right_bound) / 2];

   do {
       while(array[left_bound] < middle) {
           left_bound++;
       }
       while(array[right_bound] > middle) {
           right_bound--;
       }

       //Меняем элементы местами
       if (left_bound <= right_bound) {
           std::swap(array[left_bound], array[right_bound]);
           left_bound++;
           right_bound--;
       }
   } while (left_bound <= right_bound);

   if(make_thread && (right_bound - left > 10000))
   {
       // если элементов в левой части больше чем 10000
       // вызываем асинхронно рекурсию для правой части
       auto f = async(launch::async, [&]() {
           quicksort(array,left,right_bound);
       });
       quicksort(array, left_bound, right);
   } else {
       // запускаем обе части синхронно
       quicksort(array, left, right_bound);
       quicksort(array, left_bound, right);
   }
}

void write_arr(const string& filename, const int*  arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if(fs.is_open()) // проверяем, что файл успешно открыт
    {
       fs << n << '\n';  // записываем размер массива
       for (int i = 0; i < n; i++)
           fs << arr[i] << ' '; // записываем значения через пробел
       fs << '\n';

       fs.close(); // закрываем файл
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;
 
    fs.open(filename, fstream::in);
    if(fs.is_open()) // проверяем, что файл успешно открыт
    {
       fs >> n;  // читаем размер массива
       arr = new int[n];
       for (int i = 0; i < n; i++)
           fs >> arr[i]; // читаем из файла разделительные символы - пробел и перенос строки
       
       fs.close(); // закрываем файл
    }
}

int main(int argc, char* argv[])
{
   std::string filenameInput = "C://skillfactoryeducation/module30/module30homework/test/unsorteddata.txt";
   std::string filenameOutput = "C://skillfactoryeducation/module30/module30homework/test/sorteddata.txt";
   std::string filenameInput1 = "C://skillfactoryeducation/module30/module30homework/test/unsorteddata1.txt";
   std::string filenameOutput1 = "C://skillfactoryeducation/module30/module30homework/test/sorteddata1.txt";
   
   long arr_size = 10000000;
   int* array = new int[arr_size];
   int* array1 = new int[arr_size];

   srand(time(nullptr)); 
   int left_border = 5;
   int range_len = 10;
   for (long i = 0; i < arr_size; i++)
      array[i] = left_border + rand() % range_len; 

   write_arr(filenameInput, array, arr_size); // записываем массив в файл   

   auto start = std::chrono::high_resolution_clock::now();

   quicksort(array, 0, arr_size-1);

   auto finish = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed = finish - start;
   std::cout << "Elapsed time of " << " : " << elapsed.count() << " sec" << std::endl;

   write_arr(filenameOutput, array, arr_size); // записываем массив в файл  

   for (long i = 0; i < arr_size; i++)
      array1[i] = left_border + rand() % range_len;

   write_arr(filenameInput1, array1, arr_size); // записываем массив в файл   

   start = std::chrono::high_resolution_clock::now();
   make_thread = false;

   quicksort(array1, 0, arr_size-1);
   finish = std::chrono::high_resolution_clock::now();
   elapsed = finish - start;
   std::cout << "Elapsed time of " << " : " << elapsed.count() << " sec" << std::endl;

   write_arr(filenameOutput1, array1, arr_size); // записываем массив в файл  

   delete [] array;
   delete [] array1;
   return 0;
}