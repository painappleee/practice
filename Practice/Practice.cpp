#include <iostream>
#include <string>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<vector>

using namespace std;

int countLab=0;


struct student {
    string name;
    int* marks = new int[countLab];
    float points=0;
    float percent = 0;
    bool autoMark=false;
    bool admission=true;
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    
    vector <student> students(0);
    int maxPoints = 0;
    bool isAutoMarks = false;

    bool vvod;
    cout << "Выберите способ ввода:" << endl << "0 - ввод из файла" << endl << "1 - ручной ввод" << endl;
    cin >> vvod;

  
    float maxStudPoints = 0;
   
    int* weightLab = new int[countLab];
    if (!vvod) {
        ifstream fin("students.txt");
        fin >> countLab;
        
        for (int i = 0; i < countLab; i++) {
            fin >> weightLab[i];
            maxPoints += 5 * weightLab[i];


        }
        while (!fin.eof()) {

            student readStudent;
            readStudent.marks = new int[countLab];

            for (int i = 0; i < countLab; i++) {
                fin >> readStudent.marks[i]; ;
                readStudent.points += readStudent.marks[i] * weightLab[i];
                if (readStudent.marks[i] <= 2)
                    readStudent.admission = false;
            }
            readStudent.percent = (readStudent.points / maxPoints) * 100;

            if (readStudent.points > maxStudPoints) {
                maxStudPoints = readStudent.points;
                if (readStudent.admission == true && readStudent.points > 0.8 * maxPoints)
                    isAutoMarks = true;

            }
            getline(fin, readStudent.name);

            students.push_back(readStudent);

        }

        fin.close();

        float procentForAutoMark = 80.1;
        for (int i = 0; i < students.size(); i++) {

            if (isAutoMarks) {
                procentForAutoMark = 0.8 * (maxStudPoints / maxPoints * 100);
                if (students[i].percent > procentForAutoMark && students[i].admission == true)
                    students[i].autoMark = true;
            }

        }

        cout << setw(20) << " ";
        for (int i = 0; i < countLab; i++) {
            cout << setw(7) << "Лаба " << i + 1;
        }

        cout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;

        for (vector<student>::iterator it = students.begin(); it != students.end(); it++) {
            cout << setw(20) << (*it).name << " ";
            for (int i = 0; i < countLab; i++) {
                cout << setw(7) << (*it).marks[i] << " ";
            }

            cout << setw(4) << fixed << setprecision(0) << (*it).points << setw(8) << fixed << setprecision(1) << (*it).percent << "% ";

            if ((*it).autoMark)
                cout << setw(6) << "+";
            else
                cout << setw(6) << "-";

            if ((*it).admission)
                cout << setw(9) << "+";
            else
                cout << setw(9) << "-";

            cout << endl;
       

        }
    }
    else {            
            cout << "Введите количество лабораторных работ: "; cin >> countLab;
            int* weightLab = new int[countLab];

            for (int i = 0; i < countLab; i++) {
                cout << "Введите вес " << i + 1 << " лабораторной работы: "; cin >> weightLab[i];
                maxPoints += 5 * weightLab[i];
            }

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

                if (students[i].points > maxStudPoints) {
                    maxStudPoints = students[i].points;
                    if (students[i].admission == true && students[i].points > 0.8 * maxPoints)
                        isAutoMarks = true;

                }
                students[i].percent = (students[i].points / maxPoints) * 100;

                if (students[i].points > maxStudPoints) {
                    maxStudPoints = students[i].points;
                    if (students[i].admission == true && students[i].points > 0.8 * maxPoints)
                        isAutoMarks = true;

                }


            }
            float procentForAutoMark = 80.1;
            for (int i = 0; i < countStudents; i++) {

                if (isAutoMarks) {
                    procentForAutoMark = 0.8 * (maxStudPoints / maxPoints * 100);
                    if (students[i].percent > procentForAutoMark && students[i].admission == true)
                        students[i].autoMark = true;
                }

            } 
            cout << setw(20) << " ";
            for (int i = 0; i < countLab; i++) {
                cout << setw(7) << "Лаба " << i + 1;
            }

            cout << setw(6) << "Итог" << setw(9) << "Процент" << setw(9) << "Автомат" << setw(8) << "Допуск" << endl;

            for (int i = 0; i < countStudents; i++) {


                cout << setw(20) << students[i].name;

                for (int j = 0; j < countLab; j++) {
                    ;

                    cout << setw(7) << students[i].marks[j];
                }
                cout << setw(8) << fixed << setprecision(0) << students[i].points << setw(7) << fixed << setprecision(1) << students[i].percent << "%";

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

            cout<< "Вес лабы";
            for (int i = 0; i < countLab; i++) {
                cout<< weightLab[i]<<" ";
            }
            cout << endl;
            cout << "Максимальный балл: " << maxPoints << endl;
            cout << "Наилучшая успеваемость: " << fixed << setprecision(0) << maxStudPoints << endl;
            cout << "Минимальный процент: " << fixed << setprecision(1) << procentForAutoMark << "%";
    }  

    
    

}

