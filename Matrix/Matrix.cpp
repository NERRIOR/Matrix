#include <time.h>
#include <format>
#include <iostream>
using namespace std;
template <typename T>
class Matrix
{
private:
	int lines = 0;
	int columns = 0;
	T det = 0;
public:
	T** arr;
	// конструктор
	Matrix(int n, int p) 
	{
		lines = n;
		columns = p;
		arr = new T* [lines];
		for (int line = 0; line < lines; line++)
		{
			arr[line] = new T[columns];
		}
	}
	// деструктор
	~Matrix() 
	{
	}
	// заполнение массива случайными числами
	void full_random()
	{
		// входной параметр для генерации случайных чисел, без него каждый раз будет генерироваться одна последовательность
		srand(time(0));
		for (int line = 0; line < lines; line++)
		{
			for (int column = 0; column < columns; column++)
			{
				// rand() % (end - start + 1) + start данная формула генерирует число в диапазоне от start до end
				arr[line][column] = rand() % (30 - 0 + 1) + 0;
			}
		}
	}
	// заполнение матрицы нулями
	void zero_matrix()
	{
		for (int line = 0; line < lines; line++)
		{
			for (int column = 0; column < columns; column++)
			{
				arr[line][column] = 0;
			}
		}
	}
	// заполнение матрицы единицами
	void one_matrix()
	{
		for (int line = 0; line < lines; line++)
		{
			for (int column = 0; column < columns; column++)
			{
				arr[line][column] = 1;
			}
		}
	}
	// единичная матрица(должна быть квадратной)
	bool one_diagonal_matrix()
	{
		if (lines != columns)
		{
			return 0;
		}
		else 
		{
			for (int line = 0; line < lines; line++)
			{
				for (int column = 0; column < columns; column++)
				{
					(line == column) ? arr[line][column] = 1 : arr[line][column] = 0;
				}
			}
			return 1;
		}
	}
	// транспонирование матрицы
	void transposition()
	{
		// выделение памяти под транспонированную матрицу
		T** arr_t = new T* [columns];
		for (int column = 0; column < columns; column++)
		{
			arr_t[column] = new T[lines];
		}
		// заполнение транспонированной матрицы
		for (int column = 0; column < columns; column++)
		{
			for (int line = 0; line < lines; line++)
			{
				arr_t[column][line] = arr[line][column];
			}
		}
		// присвоение транспонированной матрицы исходной матрице
		delete[] arr;
		arr = arr_t;
		// меняем ряды со столбцами (чтобы вывод на экран был корректный)
		int medium = lines;
		lines = columns;
		columns = medium;
	}
	// вычисление определителя матрицы (реализовать метод, возвращающий определитель) пишу в данный момент
	bool determinator()
	{
		if (lines == columns)
		{
			return 0;
		}
		else
		{

		}
	}
	// пишу в данных момент
	void show_matrix()
	{
		for (int line = 0; line < lines; line++)
		{
			for (int column = 0; column < columns; column++)
			{
				// для каждого числа минимальная длина вывода 2 символа
				cout << format("|{:2} ", arr[line][column]);
			}
			cout << endl;
		}
	}
};
int main() 
{
	Matrix<int> my_array = Matrix<int>(2, 3);
	my_array.full_random();
	my_array.show_matrix();
	cout << endl;
	my_array.transposition();
	my_array.show_matrix();
}