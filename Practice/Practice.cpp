#include <iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<vector>
using namespace std;

struct student {
    string name;
    vector<int>marks; 
    int points=0;
    float percent = 0;
    bool autoMark=false;
    bool admission=true;
};

int maxPoints = 0; //максимально возможное кол-во баллов
int countLab = 1;
float minPercent = 80; //пороговый процент для автомата
int maxStudPoints = 0; //максимальное кол-во баллов среди студентов
vector <student> students; 
vector<int> weightLab; 

void inputFromFile();
void manualInput();
void outputToFile();
void outputToConsole();

int main()
{
    //для ввода и вывода русских букв
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);  

    bool isAutoMarks = false; //для определения есть ли среди студентов хотя бы один автомат
    unsigned char vvod;
    cout << (int)'a' << endl;
    do {
        // выбор способа ввода
        cout << "Выберите способ ввода:" << endl << "0 - ввод из файла" << endl << "1 - ручной ввод" << endl;
        cin >> vvod;
        system("cls");
        if (vvod == '0') {
            // ввод данных из файла
            inputFromFile();
        }
        else if (vvod=='1') {
            // ручной ввод
            manualInput();
        }
        else{
            //в случае ввода некорректоной команды
            cout << "Такой команды не существует" << endl;
            cout << endl;
        }

    } while (vvod != '0' && vvod != '1');  

    // формирование суммы баллов, процента успеваемости, наличия автомата и допуска для каждого студента
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
            minPercent =  students[i].percent/100*80;
        }

        if (isAutoMarks) {
            if (students[i].admission && students[i].percent > minPercent)
                students[i].autoMark = true;
        }
    }

    unsigned char outRes;
    do {
        // выбор способа вывода
        cout << "Выберите способ вывода:" << endl << "0 - вывод в файл" << endl << "1 - вывод в консоль" << endl;
        cin >> outRes;
        system("cls");
        if (outRes == '1') {
            // вывод в консоль
            outputToConsole();
        }
        else if (outRes == '0') {
            // вывод в файл
            outputToFile();
            cout << endl << "Результаты успешно записаны в файл studentsResults.txt" << endl;
        }
        else {
            //в случае ввода некорректной команды
            cout << "Такой команды не существует" << endl;
            cout << endl;
        }
    } while (outRes != '0' && outRes != '1');       
}

void inputFromFile() {
    ifstream fin;
    fin.open("students.txt");
    if (!fin.is_open()) {
        cout << "Файл не найден" << endl;;
        exit(1);
    }
    else {
        fin >> countLab;
        weightLab.resize(countLab); // расширене массива под заданное количество лаб
        for (int i = 0; i < countLab; i++) {
            fin >> weightLab[i];
            maxPoints += 5 * weightLab[i]; 
        }
        while (!fin.eof()) {
            student readStudent; // для считывания данных о студенте
            readStudent.marks.resize(countLab);// расширене массива под заданное количество лаб
            for (int i = 0; i < countLab; i++) {
                fin >> readStudent.marks[i];
            }
            fin.ignore();
            getline(fin, readStudent.name);
            students.push_back(readStudent); //добавление в конец массива считанных данных
        }
        fin.close();
    }
}

void manualInput() {
    do {
        if (countLab < 1)
            cout << "Количество лабораторных работ не может быть меньше 1" << endl;
        cout << "Введите количество лабораторных работ: "; cin >> countLab;
        system("cls");
    } while (countLab < 1);
    weightLab.resize(countLab);// расширене массива под заданное количество лаб
    bool isError = false; //для определения есть ли ошибка среди введённых данных
    do {
        if (isError)
            cout << "Веса лабораторных работ не могут быть меньше 0" << endl;
        cout << "Введите веса лабораторных работ через пробел: ";        
        isError = false;
        for (int i = 0; i < countLab; i++) {
            cin >> weightLab[i];
            if (weightLab[i] <= 0)
                isError = true;
            maxPoints += 5 * weightLab[i];
        }
        system("cls");
    } while (isError);

    student readStudent; //для ввода данных о студенте
    unsigned char addStudent='0';//для определения дальнейших действий после ввода данных о студенте

    do {
        cout << "Введите имя и фамилию студента: "; cin.ignore(); getline(cin, readStudent.name);
        readStudent.marks.resize(countLab);// расширене массива под заданное количество лаб
        bool isError = false;//для определения есть ли ошибка среди введённых данных
        do {
            if (isError)
                cout << "Оценки за лабы должны быть в диапазоне от 0 до 5" << endl;
            cout << "Введите через пробел оценки студента за лабы: ";
            isError = false;
            for (int i = 0; i < countLab; i++) {
                cin >> readStudent.marks[i];
                if (readStudent.marks[i] < 0 || readStudent.marks[i] > 5)
                    isError = true;
            }
            system("cls");
        } while (isError);

        students.push_back(readStudent);//добавление в конец массива введённх данных
        system("cls");        
        do {  
            if (addStudent != '1' && addStudent != '0')
                cout << "Такой команды не существует"<<endl<<endl;
            cout << "Выберите дальнейшее действие:" << endl << "0 - добавить студента" << endl << "1 - вывести таблицу" << endl;
            cin >> addStudent;
            system("cls");
        } while (addStudent != '1' && addStudent != '0');
        
        system("cls");
    } while (addStudent!='1');
}

void outputToFile() {
    ofstream fout("studentsResults.txt");
    fout << setw(20) << " ";
    for (int i = 0; i < countLab; i++)
        fout << setw(8) << "Лаба " << i + 1;
    fout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;
    for (int i = 0; i < students.size(); i++) {
        fout << setw(20) << left << students[i].name;
        for (int j = 0; j < countLab; j++)
            fout << setw(9) << right << students[i].marks[j];
        fout << setw(5) << fixed << setprecision(0) << students[i].points << setw(8) << fixed << setprecision(1) << students[i].percent << "%";
        if (students[i].autoMark)
            fout << setw(7) << "+";
        else
            fout << setw(7) << "-";

        if (students[i].admission)
            fout << setw(9) << "+";
        else
            fout << setw(9) << "-";

        fout << endl;
    }
    fout << endl;
    fout << "Вес лаб: ";
    for (int i = 0; i < countLab; i++)
        fout << weightLab[i] << " ";
    fout << endl;
    fout << "Максимально возможная сумма баллов: " << maxPoints << endl << "Наилучшая успеваемость: " << fixed << setprecision(0) << maxStudPoints << endl;
    fout << "Порог для автомата: " << fixed << setprecision(1) << minPercent << "%";
}

void outputToConsole() {
    cout << setw(20) << " ";
    for (int i = 0; i < countLab; i++)
        cout << setw(8) << "Лаба " << i + 1;
    cout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;
    for (int i = 0; i < students.size(); i++) {
        cout << setw(20) << left << students[i].name;
        for (int j = 0; j < countLab; j++)
            cout << setw(9) << right << students[i].marks[j];
        cout << setw(5) << fixed << setprecision(0) << students[i].points << setw(8) << fixed << setprecision(1) << students[i].percent << "%";

        if (students[i].autoMark)
            cout << setw(7) << "+";
        else
            cout << setw(7) << "-";

        if (students[i].admission)
            cout << setw(9) << "+";
        else
            cout << setw(9) << "-";

        cout << endl;
    }
    cout << endl;
    cout << "Вес лаб: ";
    for (int i = 0; i < countLab; i++)
        cout << weightLab[i] << " ";
    cout << endl;
    cout << "Максимально возможная сумма баллов: " << maxPoints << endl << "Наилучшая успеваемость: " << fixed << setprecision(0) << maxStudPoints << endl;
    cout << "Порог для автомата: " << fixed << setprecision(1) << minPercent << "%" << endl;
}