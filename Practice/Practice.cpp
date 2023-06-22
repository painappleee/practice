#include <iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<vector>
using namespace std;

struct student {
    string name;
    vector<int>marks; // массив для хранения оценок студента
    int points=0;
    float percent = 0;
    bool autoMark=false;
    bool admission=true;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <student> students; //массив для данных о студентах
    int maxPoints = 0;
    int countLab = 0;
    int maxStudPoints = 0;
    float minPercent = 80;
    bool isAutoMarks = false;
    // выбор способа ввода
    bool vvod;
    cout << "Выберите способ ввода:" << endl << "0 - ввод из файла" << endl << "1 - ручной ввод" << endl;
    cin >> vvod;
    vector<int> weightLab; // массив для хранения веса лаб
    if (!vvod) {
        // ввод данных из файла
        ifstream fin("students.txt");
        fin >> countLab; // ввод количества лаб
        weightLab.resize(countLab); // расширене массива под заданное количество лаб
        for (int i = 0; i < countLab; i++) {
            fin >> weightLab[i];
            maxPoints += 5 * weightLab[i]; // нахождение максимально возможного количества баллов
        }
        while (!fin.eof()) {
            student readStudent; // переменная для считывания данных о студенте
            readStudent.marks.resize(countLab);// расширене массива под заданное количество лаб
            for (int i = 0; i < countLab; i++) {
                fin >> readStudent.marks[i];
            }
            

            getline(fin, readStudent.name);

            students.push_back(readStudent);

        }

        fin.close();
    }
    
    else {
        // ручной ввод
        cout << "Введите количество лабораторных работ: "; cin >> countLab;
        weightLab.resize(countLab);

        cout << "Введите веса лабораторных работ через пробел: ";
        for (int i = 0; i < countLab; i++) {
            cin >> weightLab[i];
            maxPoints += 5 * weightLab[i];
        }

        student readStudent;
        bool addStudent;

        do {
            cout << "Введите имя и фамилию студента: "; cin.ignore(); getline(cin, readStudent.name);
            cout << "Введите через пробел оценки студента за лабы: ";
            readStudent.marks.resize(countLab);// расширене массива под заданное количество лаб
            for (int i = 0; i < countLab; i++) {
                cin >> readStudent.marks[i];
            }
            students.push_back(readStudent);
            cout <<"Выберите дальнейшее действие:" << endl << "0 - добавить студента" << endl << "1 - вывести таблицу"<<endl;
            cin >> addStudent;
            
        } while (!addStudent);
    }

    for (int i = 0; i < students.size(); i++) {
        for (int j = 0; j < countLab; j++) {
            students[i].points += students[i].marks[j]*weightLab[j];
            if (students[i].admission && students[i].marks[j] <= 2)
                students[i].admission = false;
        }
        students[i].percent = float(students[i].points)/ maxPoints*100;
        if (students[i].admission && students[i].percent > 80 && students[i].points > maxStudPoints) {
            maxStudPoints = students[i].points;
            isAutoMarks = true;
            minPercent = 0.8 * students[i].percent;
        }

        if (isAutoMarks) {
            if (students[i].admission && students[i].percent > minPercent)
                students[i].autoMark = true;
        }
    }

    bool out;
    cout << "Выберите способ вывода:" << endl<< "0 - вывод в консоль" << endl << "1 - вывод в файл" << endl;
    cin >> out;
    if (!out) {
        cout << setw(20) << " ";
        for (int i = 0; i < countLab; i++)
            cout << setw(7) << "Лаба " << i + 1;

        cout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;

        for (int i = 0; i < students.size(); i++) {
            cout << setw(20) << students[i].name;
            for (int j = 0; j < countLab; j++)
                cout << setw(7) << students[i].marks[j];
            cout << setw(10) << fixed << setprecision(0) << students[i].points << setw(8) << fixed << setprecision(1) << students[i].percent << "%";

            if (students[i].autoMark)
                cout << setw(8) << "+";
            else
                cout << setw(8) << "-";

            if (students[i].admission)
                cout << setw(8) << "+";
            else
                cout << setw(8) << "-";

            cout << endl;
        }

        cout << endl;
        cout << "Вес лабы: ";
        for (int i = 0; i < countLab; i++)
            cout << weightLab[i] << " ";
        cout << endl;
        cout << "Максимальный балл: " << maxPoints << endl << "Наилучшая успеваемость: " << fixed << setprecision(0) << maxStudPoints << endl;
        cout << "Минимальный процент: " << fixed << setprecision(1) << minPercent << "%";
    }
    else {
        ofstream fout("studentsResults.txt");
        fout << setw(20) << " ";
        for (int i = 0; i < countLab; i++)
            fout << setw(7) << "Лаба " << i + 1;

        fout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;

        for (int i = 0; i < students.size(); i++) {
            fout << setw(20) << students[i].name;
            for (int j = 0; j < countLab; j++)
                fout << setw(7) << students[i].marks[j];
            fout << setw(10) << fixed << setprecision(0) << students[i].points << setw(8) << fixed << setprecision(1) << students[i].percent << "%";

            if (students[i].autoMark)
                fout << setw(8) << "+";
            else
                fout << setw(8) << "-";

            if (students[i].admission)
                fout << setw(8) << "+";
            else
                fout << setw(8) << "-";

            fout << endl;
        }

        fout << endl;
        fout << "Вес лабы: ";
        for (int i = 0; i < countLab; i++)
            fout << weightLab[i] << " ";
        fout << endl;
        fout << "Максимальный балл: " << maxPoints << endl << "Наилучшая успеваемость: " << fixed << setprecision(0) << maxStudPoints << endl;
        fout << "Минимальный процент: " << fixed << setprecision(1) << minPercent << "%";

        cout<<"Результаты успешно записаны в файл studentsResults.txt";
    }
       
}

