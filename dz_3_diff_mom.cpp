
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <stdarg.h>
#include <cstddef>
#include <string_view>
#include <tuple>
#include <list>
#include <any>
//#define _USE_MATH_DEFINES
//#include <math.h>
#include "Timer.h"


                                                                          // successfully compiled with VS2019
using namespace std;

template <class T>
class Matrix {
private:
    size_t m_n;        // размерность матрицы
    T* m_pointer;      // указатель на элементы матрицы
public:
    Matrix(size_t n) {
        m_n = n;
        m_pointer = new T[m_n * 3];     // матрица у нас квадратная
    }
    void Set_Element(size_t x, size_t y, T el) {          // задаём значения элементов матрицы
        m_pointer[(y - 1) * m_n + (x - 1)] = el;
    }

    T Get_Element(size_t x, size_t y) {                   // получаем элемент матрицы, отсчёт с "1", а не с "0" 
        return m_pointer[(y - 1) * m_n + (x - 1)];
    }

    T Get_Det() {
        T res_common = 0;       // пояснения вычисления пределителя матрицы здесь: https://ru.wikipedia.org/wiki/%D0%9A%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%BD%D0%B0%D1%8F_%D0%BC%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0
                                // и здесь: https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%BE_%D0%A1%D0%B0%D1%80%D1%80%D1%8E%D1%81%D0%B0
        for (size_t x = 1; x <= m_n; x++) {            // вычисляем "плюсовую" часть определителя

            T res_mult = 1;
            for (size_t y = 1, add = 0; y <= m_n; y++, add++) {
                size_t x_mult = x + add;
                if (x_mult > m_n)
                    x_mult -= m_n;
                res_mult *= Get_Element(x_mult, y);
            }

            res_common += res_mult;
        }

        for (size_t x = m_n; x <= m_n * 2 - 1; x++) {  // вычисляем "минусовую" часть определителя

            T res_mult = 1;
            for (size_t y = 1, add = 0; y <= m_n; y++, add++) {
                size_t x_mult = x - add;
                if (x_mult > m_n)
                    x_mult -= m_n;
                res_mult *= Get_Element(x_mult, y);
            }

            res_common -= res_mult;
        }


        return res_common;
    }

    ~Matrix() {
        delete[] m_pointer;
    }
};


class My_Iterator {    // для упрощения кода пропустил проверки на переполнение, и пр.
private:
    int* m_ptr;            // указатель на целочисленные данные
    size_t m_cur_ptr;      // текущее положение в массиве
    size_t m_capacity;     // вместимость котейнера (задаётся при инциализации)
public:
    My_Iterator(size_t capacity) {
        m_cur_ptr = 0;
        m_capacity = capacity;
        m_ptr = new int[m_capacity];
    }
    void Add(int i) {
        m_ptr[m_cur_ptr] = i;   // добавляем число
        ++m_cur_ptr;            // увеличиваем текущее положение на 1
    }
    int* begin() {
        return &m_ptr[0];
    }
    int* end() {
        return &m_ptr[m_cur_ptr];
    }
    ~My_Iterator() {
        delete[] m_ptr;
    }
};


int main()
{
               // задание 1
    list<double> n { 1.34, 3.67, 4.52 };

    double sum = 0.0;   // сумма всех элементов

    for (list<double>::iterator it = n.begin(); it != n.end(); it++)
        sum += *it;

    n.push_back(sum / static_cast<double>(n.size()));   // помещаем среднее арифметическое в конец списка

    list<double>::iterator it = n.end();
    cout << "Last element: " << * (--it) << "\n\n";       // выводим последний элемент (т.е., среднее арифметическое)


               // задание 2
    Matrix<int> m(3);
    m.Set_Element(1, 1, 1);
    m.Set_Element(2, 1, 2);
    m.Set_Element(3, 1, 33);
    m.Set_Element(1, 2, 44);
    m.Set_Element(2, 2, 5);
    m.Set_Element(3, 2, 6);
    m.Set_Element(1, 3, 7);
    m.Set_Element(2, 3, 8);
    m.Set_Element(3, 3, 9);
    int det = m.Get_Det();

    cout << "Determinant is: " << det << "\n\n\n";


               // задание 3
    My_Iterator mi(5);
    mi.Add(1);
    mi.Add(2);
    mi.Add(3);

    for (auto i : mi)
        cout << i << "\n";

    return 0;
}

















