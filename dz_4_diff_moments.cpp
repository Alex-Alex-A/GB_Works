#include "pch.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <deque>
#include <iterator>
#include <stdarg.h>
#include <cstddef>
#include <string_view>
#include <tuple>
#include <list>
#include <any>
#include <numeric>
//#define _USE_MATH_DEFINES
//#include <math.h>
#include "Timer.h"


using namespace std;

template <class T> void insert_sorted(vector<T>& v, T i) {
    vector<T> d;
    typename vector<T>::iterator it;

    for (it = v.begin(); it != v.end(); it++)     // находим позицию, после которой можно внедрить элемент
        if (*it < i && *(it + 1) >= i)
            break;

    copy(v.begin(), ++it, back_inserter(d));   // копируем фрагмент до позиции внедрения
    d.push_back(i);                            // внедряем объект
    copy(it, v.end(), back_inserter(d));       // копируем фрагмент после внедрения
    v.clear();
    copy(d.begin(), d.end(), back_inserter(v));  // копируем новый контейнер в старый
}



double rand_double() {                    /// функция, выдающая рандомный double
    int rnd = 0;
    for (int i = 0; i < 7; i++)
        rnd += rand() % 10;

    return (static_cast<double>(rnd) / 6.0);
}


double my_add(double x, double y) { return x + y; }                // сложение
double my_act(double x, double y) { return ((x - y)*(x - y)); }    // вычитание элементов контейнеров и возведение в квадрат 

int main()
{
               // задание 1
    vector<int> v = { 1, 3, 5, 7, 9 };

    cout << "Old container:\n";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    cout << "\n\n";

    insert_sorted(v, 4);    // внедряем 4

    cout << "New container:\n";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    cout << "\n\n\n\n";

               // задание 2
#define ARR_COUNT   100

    double vd[ARR_COUNT];
    int vi[ARR_COUNT];

    for (int i = 0; i < ARR_COUNT; i++) {     // заполняем массив случайными числами double
        vd[i] = rand_double();
    }

    cout << "================ vector double =================\n";
    for (int i = 0; i < ARR_COUNT; i++) {
        cout << vd[i] << " ";
    }

    cout << "\n\n";

    transform(begin(vd), end(vd), vi, [=](int i) { return static_cast<int>(vd[i]); });  // преобразуем double в int

    cout << "================ vector integer =================\n";
    for (int i = 0; i < ARR_COUNT; i++) {
        cout << vi[i] << "   ";
    }

    cout << "\n\n";


    cout << "================ digital bias =================\n";
    double vd2[ARR_COUNT];
    for (int i = 0; i < ARR_COUNT; i++) {
        vd2[i] = static_cast<double>(vi[i]);
    }

    cout << "\n";

    double init = 0.0;

    cout << inner_product(begin(vd), end(vd), vd2, init, my_add, my_act);    // вызываем функцию с указателями на функции для вычисления цифровой ошибки

    cout << "\n\n";

    return 0;
}

















