#include <iostream>
#include <string>
#include<iomanip>
#include<Windows.h>

using namespace std;

int countLab=0;

struct student {
    string name;
    int* marks = new int[countLab];
    float points=0;
    int percent = 0;
    bool autoMark=false;
    bool admission=true;
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int maxPoints = 0;    
    cout << "Введите количество лабораторных работ: "; cin >> countLab;
    int* weightLab = new int[countLab];
    for (int i = 0; i < countLab; i++) {
        cout << "Введите вес " << i + 1 << " лабораторной работы: "; cin >> weightLab[i];
        maxPoints += 5 * weightLab[i];
    }
    float maxStudPoints;

    maxStudPoints = 0;
    int countStudents;
    cout << "Введите количество студентов: "; cin >> countStudents;
    student* students = new student[countStudents];
    
    for (int i = 0; i < countStudents; i++) {        
        cout << "Введите фамилию и имя " << i + 1 << " студента: "; cin.ignore(); getline(cin, students[i].name);
        for (int j = 0; j < countLab; j++) {
            cout << "Введите оценку за " << j + 1 << " лабораторную работу: "; cin >> students[i].marks[j];
            students[i].points += students[i].marks[j] * weightLab[j];
            if (students[i].admission == true && students[i].marks[j] <= 2)
                students[i].admission = false;
        }
        if (students[i].admission == true && students[i].points > 0.8 * maxPoints && students[i].points > maxStudPoints) 
                   maxStudPoints = students[i].points;
         
        
    }
    int procentForAutoMark=100;
    for (int i = 0; i < countStudents; i++) {
            students[i].percent = (students[i].points / maxPoints) * 100;

            if (maxStudPoints > 0) {
                procentForAutoMark = 0.8 * (maxStudPoints / maxPoints * 100);
                if (students[i].percent > procentForAutoMark && students[i].admission == true)
                    students[i].autoMark = true;
            }
            
    } 
    
    cout << setw(20) << " ";
    for (int i = 0; i < countLab; i++) {
        cout <<setw(7) << "Лаба " << i + 1;
    }
   
    cout <<setw(6) << "Итог" <<setw(9)<< "Процент" << setw(9)<< "Автомат" <<setw(8)<< "Допуск" << endl;
   
    for (int i = 0; i < countStudents; i++) {
 

        cout <<setw(20) << students[i].name;
   
        for (int j = 0; j < countLab; j++) {;

            cout << setw(7)<< students[i].marks[j];
        }
        cout <<setw(8)<< students[i].points << setw(7) << students[i].percent << "%";

        if (students[i].autoMark)
            cout <<setw(8) << "+";
        else
            cout << setw(8) << "-";

        if (students[i].admission)
            cout << setw(8) << "+";
        else
            cout << setw(8) << "-";

        cout << endl;
    }
   
    cout << setw(20) << "Вес лабы";
    for (int i = 0; i < countLab; i++) {
        cout << setw(7) << weightLab[i];
    }
    cout << endl;
    cout <<setw(20)<<"Максимальный балл" << setw(countLab * 9+2) << maxPoints<<endl;
    cout << setw(20) << "Минимальный процент" << setw(countLab * 9 + 9) << procentForAutoMark<<"%";

}

