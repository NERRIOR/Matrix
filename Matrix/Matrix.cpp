#include <time.h>
#include <cmath>
#include <string>
#include <format>
#include <iostream>
#include <fstream>
using namespace std;
template <typename T>
class Matrix
{
private:
	int lines = 0;
	int columns = 0;
	double det = 0;
public:
	T** arr;
	// конструктор
	Matrix(int n, int p) 
	{
		srand(time(0));
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
	Matrix<T> transposition()
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
		Matrix<T> array_trans = Matrix<T>(lines, columns);
		array_trans.arr = arr_t;
		return array_trans;
	}
	// функция освобождения памяти, выделенной под двумерный динамический массив
	void clearMemory(T** a, int n)
	{ 
		for (int i = 0; i < n; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
	// рекурсивная функция вычисления определителя матрицы, будем находить матрицу разложением по строке
	T findDet(T** a, int n) 
	{
		if (lines != columns)
		{
			// если матрица не квадратная -> определитель не найден
			return 404;
		}
		if (n == 1)
		{
			return a[0][0];
		}
		else if (n == 2)
		{
			return a[0][0] * a[1][1] - a[0][1] * a[1][0];
		}
		else 
		{
			T d = 0;
			for (int k = 0; k < n; k++) 
			{
				// выделяем память под минор матрицы
				T** m = new T* [n - 1];
				for (int i = 0; i < n - 1; i++) 
				{
					m[i] = new T[n - 1];
				}
				// заполняем минор значениями
				for (int i = 1; i < n; i++)
				{
					int t = 0;
					for (int j = 0; j < n; j++) 
					{
						if (j == k)
							continue;
						m[i - 1][t] = a[i][j];
						t++;
					}
				}
				d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
				// освобождаем память, выделенную под минор
				clearMemory(m, n - 1); 
			}
			det = d;
			// возвращаем определитель матрицы
			return d; 
		}
	}
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
	// перегрузка операторов для матрицы и числа
	void operator+(const double digit)
	{
		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				arr[i][j] += digit;
			}
		}
	}
	void operator-(const double digit)
	{
		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				arr[i][j] -= digit;
			}
		}
	}
	void operator*(const double digit)
	{
		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				arr[i][j] *= digit;
			}
		}
	}
	bool operator/(const double digit)
	{
		for (int i = 0; i < lines; i++)
		{
			if (digit == 0) 
			{
				cout << "Деление на ноль" << endl << endl;
				return 0;
			}
			for (int j = 0; j < columns; j++)
			{
				arr[i][j] /= digit;
			}
		}
		return 1;
	}
	// перегрузка операторов для матриц
	// оператор сложения
	Matrix<T> operator+(const Matrix<T> &other_matrix)
	{
		// создадим матрицу sum такой же размерности что и переданные матрицы
		Matrix<T> sum = Matrix<T>(lines, columns);
		for(int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				sum.arr[i][j] = this->arr[i][j] + other_matrix.arr[i][j];
			}
		}
		return sum;
	}
	// оператор вычитания
	Matrix<T> operator-(const Matrix<T> &other_matrix)
	{
		// создадим матрицу sum такой же размерности что и переданные матрицы
		Matrix<T> sum = Matrix<T>(lines, columns);
		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				sum.arr[i][j] = this->arr[i][j] - other_matrix.arr[i][j];
			}
		}
		return sum;
	}
	// оператор умножения
	Matrix<T> operator*(const Matrix<T> &other_matrix)
	{
		// содаем матрицу результата
		Matrix<T> prod_result = Matrix<T>(this->lines, other_matrix.columns);
		T** res;
		int i, j;
		res = new T* [lines];
		for (i = 0; i < other_matrix.columns;i++)
		{
			res[i] = new T[other_matrix.columns];
		}
		for (i = 0; i < this->lines;i++)
		{
			for (j = 0; j < other_matrix.columns;j++)
			{
				res[i][j] = 0;
				for (int k = 0; k < this->columns; k++)
				{
					res[i][j] += this->arr[i][k] * other_matrix.arr[k][j];
				}
			}
		}
		prod_result.arr = res;
		return prod_result;

	}
	// считывание из файла в матрицу
	Matrix<T> file_read(string f) 
	{
		//Создаем файловый поток и связываем его с файлом
		ifstream in(f);
		if (in.is_open())
		{
			//Вначале посчитаем сколько чисел в файле
			int count = 0;
			int temp;
			// пробегаем пока не встретим конец файла eof
			while (!in.eof())
			{
				//в пустоту считываем из файла числа
				in >> temp;
				// увеличиваем счетчик числа чисел
				count++;
			}
			//переведем каретку в потоке в начало файла
			in.seekg(0, ios::beg);
			in.clear();

			//Число пробелов в первой строчке вначале равно 0
			int count_space = 0;
			char symbol;
			while (!in.eof())
			{
				//теперь нам нужно считывать не числа, а посимвольно считывать данные
				in.get(symbol);
				//Если это пробел, то число пробелов увеличиваем
				if (symbol == ' ') count_space++;
				//Если дошли до конца строки, то выходим из цикла
				if (symbol == '\n') break;
			}

			//Опять переходим в потоке в начало файла
			in.seekg(0, ios::beg);
			in.clear();

			//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
			//Теперь можем считать матрицу.
			//число строк
			int n = count / (count_space + 1);
			//число столбцов на единицу больше числа пробелов
			int m = count_space + 1;
			double** x;
			x = new double* [n];
			for (int i = 0; i < n; i++) x[i] = new double[m];
			//Считаем матрицу из файла
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					in >> x[i][j];
			Matrix<T> array_read = Matrix<T>(n, m);
			array_read.arr = x;
			//под конец закроем файла
			in.close();
			return array_read;
		}
		else
		{
			//Если открытие файла прошло не успешно
			cout << "Файл не найден.";
			Matrix<T> zero = Matrix<T>(1, 1);
			zero.arr[0][0] = 0;
			return zero;
		}
	}
	void file_write()
	{
		// поток для записи
		ofstream out;
		out.open("D:/m_write.txt");
		if (out.is_open())
		{
			for (int i = 0; i < this->lines; i++)
			{
				for (int j = 0; j < this->columns; j++)
				{
					out << this->arr[i][j] << " ";
				}
				out << '\n';
			}
			out.close();
		}
		else
		{
			cout << "Не удалось открыть файл";
		}
	}
};
int main()
{
	setlocale(LC_ALL, "RUS");
	// создаем две матрицы
	Matrix<double> my_array_1 = Matrix<double>(3, 3);
	Matrix<double> my_array_2 = Matrix<double>(3, 3);
	// заполняем матрицу случайными числами
	my_array_1.full_random();
	my_array_2.full_random();
	// вывод матриц на экран
	cout << "my_array_1: " << endl;
	my_array_1.show_matrix();
	cout << endl;
	cout << "my_array_2: " << endl;
	my_array_2.show_matrix();
	cout << endl;
	// подсчет определителя
	cout << "det = " << my_array_1.findDet(my_array_1.arr, 3) << endl << endl;
	// прибавляем к каждому элементу матрицы число
	cout << "my_array_1 + 8: " << endl;
	my_array_1 + 8;
	my_array_1.show_matrix();
	cout << endl;
	// отнимаем от каждого элемента матрицы число
	cout << "my_array_1 - 3: " << endl;
	my_array_1 - 3;
	my_array_1.show_matrix();
	cout << endl;
	// умножаем каждый элемент матрицы число
	cout << "my_array_1 * 2: " << endl;
	my_array_1 * 2;
	my_array_1.show_matrix();
	cout << endl;
	// делим каждый элемент матрицы число
	cout << "my_array_1 / 2: " << endl;
	my_array_1 / 2;
	my_array_1.show_matrix();
	cout << endl;
	// сложение двух матриц
	cout << "my_array_1 + my_array_2: " << endl;
	Matrix<double> my_array_3 = my_array_1 + my_array_2;
	my_array_3.show_matrix();
	cout << endl;
	// найдем транспонированную матрицу
	cout << "my_array_trans: " << endl;
	Matrix<double> my_array_trans = my_array_1.transposition();
	my_array_trans.show_matrix();
	cout << endl;
	// произведение двух матриц
	Matrix<double> prod = my_array_1 * my_array_2;
	cout << "my_array_1 * my_array_2: " << endl;
	prod.show_matrix();
	cout << endl;
	// чтение матрицы из файла
	cout << "file_read: " << endl;
	Matrix<double> array_r = array_r.file_read("D:/m_read.txt");
	array_r.show_matrix();
	cout << endl;
	// запись матрицы в файл
	prod.file_write();
}
