#include <stdio.h>
#include <iostream>
#include <thread>
using namespace std;
int* A; // исходная последовательность
int n; // количество чисел
int nThread; //количество потоков
int* distribution; //распределение последовательности
void thread_body(int index)
{
int* B = new int[distribution[(int)index]];
int start = 0;
for (int i = 0; i < (int)index; i++)
start += distribution[i];
int end = start + distribution[(int)index];
int j = 0;
for (int i = start; i < end; i++) {
for (int k = 1; k <= A[i]; k++)
if (k * k == A[i]) {
B[j++] = A[i];
printf("\n %d", A[i]);
break;
}
}
}
int main()
{
//Задаем количество элементов
cout << "Введите кол-во элементов" << endl;
cin >> n;
srand(time(0));
A = new int[n];
for (int i = 0; i < n; i++)
A[i] = rand() % 100 + 1;
//Вводим количество потоков
cout << endl << "Введите кол-во потоков (2.." << n / 2 << ")" << endl;
cin >> nThread;
distribution = new int[nThread];
//Распределяем части последовательностей по потокам
for (int i = 0; i < nThread; i++)
distribution[i] = n / nThread;
for (int i = 0; i < n % nThread; i++)
distribution[i]++;
//Выводим рандомно заполненный массив
int z = 0;
for (int i = 0; i < nThread; i++) {
cout << i + 1 << " Поток: ";
for (int j = z; j < z + distribution[i]; j++)
cout << A[j] << " ";
cout << endl;
z += distribution[i];
}
cout << endl << endl;
thread* arr = new thread[nThread];
for (int i = 0; i < nThread; i++)
arr[i] = thread(thread_body, i);
for (int i = 0; i < nThread; i++)
arr[i].join();
printf("\n\nPress any key...");
return 0;
}