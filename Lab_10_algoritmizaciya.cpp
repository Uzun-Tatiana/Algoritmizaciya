#include <iostream>

using namespace std;

int** create_arr(const int STOLBEC, const int ROW) {
    int** arr = new int* [STOLBEC];
    for (int i = 0; i < STOLBEC; i++) arr[i] = new int[ROW];

    return arr;
}

void del_arr(int** arr, const int STOLBEC, const int ROW) {
    for (int i = 0; i < STOLBEC; i++) delete[]arr[i];
    delete[]arr;
}

void fill_arr(int** arr, const int STOLBEC, const int ROW) {
    int count = 0;
    for (int i = 0; i < STOLBEC; i++) {
        for (int j = 0; j < ROW; j++) {
            arr[i][j] = ++count;
        }
    }
}

void print(int** arr, int STOLBEC, int ROW) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < STOLBEC; j++) {
            cout << arr[j][i] << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

/*ФУНКЦИЯ УДАЛЕНИЯ СТОЛБЦА ДВУМЕРНОГО МАССИВА*/
void del_row(int** arr, int& STOLBEC, const int ROW, const int number) {

    if (number < 1 || number > STOLBEC) {
        cout << "Столбец " << number << ": стерт\n\n";
        return;
    }

    delete[]arr[number - 1];
    STOLBEC--;
    for (int i = number - 1; i < STOLBEC; i++) arr[i] = arr[i + 1];

    cout << "Столбец " << number << " удалён" << endl;
}


int main() {
    setlocale(0, ""); // Включаем кириллицу
    int ROW;
    int STOLBEC;

    cout << "Введите число строк" << endl;
    cin >> ROW;
    cout << "Введите число столбцов" << endl;
    cin >> STOLBEC;


    int** arr = create_arr(STOLBEC, ROW);
    fill_arr(arr, STOLBEC, ROW);
    print(arr, STOLBEC, ROW);

    int number; //удаляемая строка
    cout << "Введите номер столбца который удаляем" << endl;
    cin >> number;

    del_row(arr, STOLBEC, ROW, number);
    print(arr, STOLBEC, ROW);

    del_arr(arr, STOLBEC, ROW);

}