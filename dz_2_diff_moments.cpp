#include "pch.h"
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
#include <any>
//#define _USE_MATH_DEFINES
//#include <math.h>
#include "Timer.h"


                                                                          // successfully compiled with VS2019
using namespace std;

template <class T>
void SWAP(T** p1, T** p2) {   // меняет значения указателей на переменные

    T* tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


template <class T>
void SortPointers(vector<T*> &v) {

    vector<pair<T*, T>> PP;     // вектор пар: указатель и переменная, на которую он указывает

    for (int i = 0; i < v.size(); i++)
        PP.push_back(make_pair(v[i], *(v[i])));  // добавляем пару в вектор

    sort(PP.begin(), PP.end(),
        [](pair<T*, T> p1, pair<T*, T> p2) -> bool
        {
            return p1.second < p2.second;                // сортируем по значениям переменных, т.е.,  по вторым элементам в парах
        }
    );
}

bool is_Vowel(char cc) {    // унарный предикат, определяем гласную букву    Vowel  Consonant
    char c = tolower(cc);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool is_Vowel2(char cc) {
    char c = tolower(cc);
    string vowels = "aeiouy";
    size_t found = vowels.find(c);   // ищем, нет ли символа в строке всех гласных
    bool out;
    found == std::string::npos ? out = false : out = true;
    return out;
}

int main()
{
    int i = 56;
    int j = 37;

    int* pi = &i;
    int* pj = &j;

    cout << "------Before--------" << endl;
    cout << *pi << "\n";
    cout << *pj << "\n\n";

      // передаём адреса указателей, т.е., указатели на казатели
    SWAP(&pi, &pj);       // меняем адреса в указателях, сами переменные i, j не меняются

    cout << "------After--------" << endl;
    cout << *pi << "\n";
    cout << *pj << "\n\n";

    cout << "------Original--------" << endl;
    cout << i << "\n";
    cout << j << "\n\n\n";


    string str = "";   // в этой строке будет содержимое файла

    ifstream is("war_and_peace.txt");
    if (is.is_open()) {

        while (!is.eof()) {
            char c = is.get();            // в "c" получаем символ из файла
            str += c;               // добавляем полученный символ в строку
        }

        is.close();


        int num_vowel = 0;

        //--------------------------------------------------------------------
 
        Timer timer("count_if + simple");
        num_vowel = count_if(str.begin(), str.end(), is_Vowel);        // прогоняем всю строку , проверяя на гласные простым посимвольным сравнением
        timer.print();

        cout << "There are " << num_vowel << " vowels in text  \n\n";

        //--------------------------------------------------------------------

        Timer timer2("count_if + find");
        num_vowel = 0;
        num_vowel = count_if(str.begin(), str.end(), is_Vowel2);       // 
        timer2.print();

        cout << "There are " << num_vowel << " vowels in text  \n\n";

        //--------------------------------------------------------------------

        Timer timer3("for");
        num_vowel = 0;
        for (int i = 0; i < str.size(); i++) {         // перебор элементов строки циклом for
            if (is_Vowel(str.at(i)))
                ++num_vowel;
        }
        timer3.print();

        cout << "There are " << num_vowel << " vowels in text  \n\n";

        //--------------------------------------------------------------------

        Timer timer4("for + find");
        num_vowel = 0;
        for (int i = 0; i < str.size(); i++) {         // перебор элементов строки циклом for и find
            if (is_Vowel2(str.at(i)))
                ++num_vowel;
        }
        timer4.print();

        cout << "There are " << num_vowel << " vowels in text  \n\n";

        //--------------------------------------------------------------------

        num_vowel = 0;
        string vowels = "aeiouy";
        Timer timer5("for + for");
        for (int i = 0; i < str.size(); i++) {         // перебор элементов строки циклом for и for
            for (int j = 0; j < vowels.size(); j++) {
                if (str.at(i) == vowels.at(j)) {
                    ++num_vowel;
                    break;
                }
            }
        }
        timer5.print();

        cout << "There are " << num_vowel << " vowels in text  \n\n";
    }
    else
        cout << "Can't open file:  war_and_peace.txt  \n\n";



    return 0;
}

















