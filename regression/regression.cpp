///////////////////////////
// Шрейбер М. БСБО-13-18 //
///////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

float A = 0.0f;
float B = 0.0f;
int n = 0;

// Рассчет значений A и B
void regression(float x[], float y[]) {
	float sum_x = 0.0f, sum_y = 0.0f, sum_x2 = 0.0f, sum_xy = 0.0f;
	for (int i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_x2 += x[i]*x[i];
		sum_xy += x[i]*y[i];
	}
	A = (sum_x*sum_y - n * sum_xy) / (sum_x*sum_x - n * sum_x2);
	B = (sum_x*sum_xy - sum_x2 * sum_y) / (sum_x*sum_x - n * sum_x2);
}

// Генерация x, y на основе A и B
void generate_xy(float x[], float y[]) {
	float k = 0.5f;
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		x[i] = k + pow(-1, rand() % 10 + 1)*0.04*(rand() % 7 + 1);
		y[i] = x[i]*A + B + pow(-1, rand() % 10 + 1)*0.04*(rand() % 7 + 1);
		k += 0.5;
	}
}

// Функция возвращает первое найденное вещественное число
// и удаляет все символы от начала строки до этого числа включительно
float get_float(string& str) {
	bool digit = false;        
	int k = 0;
	string temp;
	for (int j = 0; j < str.size(); j++) {
		k = j + 1;
		if (isspace(str[j]) && digit) {
			digit = false;
			break;
		}
		if (digit) temp += str[j];
		if (isdigit(str[j]) && !digit) {
			digit = true;
			temp = str[j];
		}
	}
	str.erase(0, k);
	return stof(temp);
}

// Запись данных в файл
void save_xy(float x[], float y[]) {
	ofstream fout("data.txt", ios::trunc);
	fout << "n";
	for (int i = 1; i <= n; i++) fout << " " << i;
	fout << "\nxi";
	for (int i = 0; i < n; i++) fout << " " << x[i];
	fout << "\nyi";
	for (int i = 0; i < n; i++) fout << " " << y[i];
	fout.close();
}

int main() {
	SetConsoleOutputCP(1251);
	string str, temp;
	char s;
	bool end = false;

	ifstream fin("data.txt");

	getline(fin, str);
	for (int i = str.size() - 1; i > 0; i--) {
		if (!isdigit(str[i])) break;
		temp = str[i] + temp;
	}
	n = stoi(temp);

	float *x = new float[n];
	float *y = new float[n];

	getline(fin, str);
	int i = 0;
	while (str.size() != 0) {
		x[i] = get_float(str);
		i++;
	}

	getline(fin, str);
	i = 0;
	while (str.size() != 0) {
		y[i] = get_float(str);
		i++;
	}
	fin.close();

	regression(x,y);

	while (end != true) {
		cout << "A = " << A << "; B = " << B << endl;
		cout << "\n-----------------------------------" << endl;
		cout << "| 1 - сгенерировать значения x, y |" << endl;
		cout << "| 2 - изменить коэффиценты A, B   |" << endl;
		cout << "| 0 - выход                       |" << endl;
		cout << "-----------------------------------" << endl;

		s = _getch();

		switch (s) {
			case '1':
				generate_xy(x,y);
				regression(x,y);
				cout << "Записать значения в файл? (y/n): ";
				cin >> temp;
				if (temp == "y") save_xy(x,y);
				system("cls");
				break;
			case '2':
				cout << "Введите значение А: ";
				cin >> A;
				cout << "Введите значение B: ";
				cin >> B;
				system("cls");
				break;
			case '0':
				end = true;
				break;
			default:
				system("cls");
				break;
		}
		_getch();
	}	
	return 0;
}