#include<iostream>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

typedef struct {
	char name[255];
	char adress[255];
	int group; // номер группы
	float rating; // рейтинг студента rating
}STUDENT; //student 

STUDENT createSTUDENT() {
	STUDENT newSTUDENT;

	cout << "Введите ФИО студента: ";
	cin.get();//Ожидает ввода символа
	cin.getline(newSTUDENT.name, 255);// ввод с пробелами

	cout << "Введите адрес студента: ";
	cin.getline(newSTUDENT.adress, 255);

	cout << "Введите номер группы: ";
	cin >> newSTUDENT.group;
	if (cin.fail()) {
		cerr << "\n\nОшибка: введен некорректный символ. Завершение программы...\n";
		exit(EXIT_FAILURE);
	}

	cout << "Введите рейтинг (float)";
	cin >> newSTUDENT.rating;
	if (cin.fail()) {
		cerr << "\n\nОшибка: введен некорректный символ. Заверешение программы...\n";
		exit(EXIT_FAILURE);
	}
	return newSTUDENT;
}

void StudentFileEnd(const char* filename, const STUDENT& studentToAdd) {//добавить страну в конец файла

	ofstream fout(filename, ios::binary | ios::out | ios::app);

	if (!fout.is_open())

	{

		cerr << "Не удалось открыть файл. Завершение программы...";

		exit(EXIT_FAILURE);

	}

	fout.write((char*)&studentToAdd, sizeof(studentToAdd));

	fout.close();

}

//добавить студента в файл после элемента

void AddSTUDENT(const char* filename, const int& num, const STUDENT& studentToAdd) {

	if (num < 1) return;

	ifstream f1(filename, ios::binary | ios::in);

	if (!f1.is_open()) {

		cerr << "Не удалось открыть файл. Завершение программы...";

		exit(EXIT_FAILURE);

	}

	int fileSize = 0;

	STUDENT tmp;

	while (f1.read((char*)&tmp, sizeof(tmp))) fileSize++;

	f1.clear();

	f1.seekg(0, ios::beg);

	if (fileSize == 0 || num >= fileSize) {

		f1.close();

		StudentFileEnd(filename, studentToAdd);

		cout << "Запись эелемента в файл прошла успешно.\n\n";

	}

	else {

		ofstream f2("tmp.bin", ios::binary | ios::out | ios::app);

		if (!f2.is_open()) {

			cerr << "Не удалось открыть файл. Завершение программы...";

			exit(EXIT_FAILURE);

		}

		int count = 0;

		STUDENT tmp;

		while (count != num) {

			f1.read((char*)&tmp, sizeof(tmp));

			f2.write((char*)&tmp, sizeof(tmp));

			count++;

		}

		f2.write((char*)&studentToAdd, sizeof(studentToAdd));

		while (f1.read((char*)&tmp, sizeof(tmp)))

			f2.write((char*)&tmp, sizeof(tmp));

		if (f1.eof()) cout << "Запись элелемента в файл прошла успешно.\n\n";

		else {

			cerr << "Произошел сбой при чтении файла. Завершение программы...";

			exit(EXIT_FAILURE);

		}

		f1.close();

		f2.close();

		if (rename(filename, "prev.bin")) {

			cerr << "Аварийное завершение программы...";

			exit(EXIT_FAILURE);

		}

		if (rename("tmp.bin", filename)) {

			cerr << "Аварийное завершение программы...";

			exit(EXIT_FAILURE);

		}

		remove("prev.bin");

	}

}
//удалить из файла студентов с низким рейтингом
void DelFileMinRating(const char* filename, const float& limit)
{
	ifstream f1(filename, ios::binary | ios::in);
	ofstream f2("tmp.bin", ios::binary | ios::out);
	// Закрытие программы если не удалось открыть файл
	if (!f1.is_open() || !f2.is_open())
	{
		cerr << "Не удалось открыть файл. Завершение программы...";
		exit(EXIT_FAILURE);
	}

	STUDENT tmp;
	while (f1.read((char*)&tmp, sizeof(tmp)))
	{
		if (tmp.rating > limit) f2.write((char*)&tmp, sizeof(tmp));
		else continue;
	}
	if (f1.eof()) cout << "Удаление элементов из файла прошло успешно.\n\n";
	else
	{
		cerr << "Произошел сбой при чтении файла. Завершение программы...";
		exit(EXIT_FAILURE);
	}

	f1.close();
	f2.close();

	if (rename(filename, "prev.bin"))
	{
		cerr << "Аварийное завершение программы...";
		exit(EXIT_FAILURE);
	}

	if (rename("tmp.bin", filename))
	{
		cerr << "Аварийное завершение программы...";
		exit(EXIT_FAILURE);
	}
	remove("prev.bin");
}

void PrintFile(const char* filename)
{
	ifstream fin(filename, ios::binary | ios::in);

	if (!fin.is_open()) {
		cerr << "Не удалось открыть файл. Завершение программы...";
		exit(EXIT_FAILURE);
	}

	cout << "Файл " << filename << " содержит:\n\n";
	bool isEmpty = true;
	STUDENT tmp;
	while (fin.read((char*)&tmp, sizeof(tmp)))
	{
		isEmpty = false;
		cout << tmp.name << '\n' << tmp.adress << '\n' << tmp.group << '\n' << tmp.rating << "\n\n";
	}

	if (isEmpty)
	{
		cout << "Файл пуст.\n\n";
		fin.close();
		return;
	}

	if (fin.eof()) cout << "Файл прочитан.\n\n";
	else
	{
		cerr << "Произошел сбой при чтении файла. Завершение программы...";
		fin.close();
		exit(EXIT_FAILURE);
	}
	fin.close();
}

int main()
{
	setlocale(0, ""); // Включаем кириллицу
	float r;
	int n;

	STUDENT newSTUDENT;
	cout << "Укажите количество студенов: ";
	cin >> n;// указали кол-во студентов
	cout << endl;

	const char* filename = "Students.bin";

	for (int i = 0; i < n; i++)
	{
		STUDENT tmp = createSTUDENT();
		cout << "Записываем студента " << tmp.name << " в файл " << filename << "...\n\n";
		StudentFileEnd(filename, tmp);
	}

	PrintFile(filename);
	const float limit = 4.3;// мин рейтинг
	cout << "Удаляем информацию о студентах из файла " << filename << "...\n\n";
	DelFileMinRating(filename, limit);
	PrintFile(filename);// вывод после удаления
	cout << "Укажите информацию о студенте, которого хотите добавить в файл.\n\n";
	newSTUDENT = createSTUDENT();
	cout << "\nУкажите позицию, которую студент должен занять(кроме 1) : ";
	int num;
	cin >> num;
	cout << endl;
	cout << "Добавляем студента " << newSTUDENT.name << " в файл " << filename << "...\n\n";
	AddSTUDENT(filename, num - 1, newSTUDENT);
	PrintFile(filename);

}