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
#include <set>
#include <map>


using namespace std;


template <class T>
class My_Iterator {    // собственный класс итератора
private:
    T* m_ptr;            // 
    size_t m_cur_ptr;      //
    size_t m_capacity;     //
    size_t m_iter;         //
public:
    My_Iterator(size_t capacity) {
        m_cur_ptr = 0;
        m_capacity = capacity;
        m_ptr = new T[m_capacity];
    }
    void Add(T i) {
        m_ptr[m_cur_ptr] = i;   //
        ++m_cur_ptr;            //
    }
    T* begin() {
        m_iter = 0;       // когда вызывается begin - m_iter устанавливаем в 0 , чтобы потом можно было проходить контейнер перегруженным инкрементом ++
        return &m_ptr[0];
    }
    T* end() {
        return &m_ptr[m_cur_ptr];
    }
    void operator++() {                    // перегружаем префиксный инкримент
        ++m_iter;
    }
    T* operator* (My_Iterator& i) {        // перегружаем разыменование указателя
        return &m_ptr[m_iter];
    }

    ~My_Iterator() {
        delete[] m_ptr;
    }
};

template <class T>
void print_unique(T* it, T* end) {  // получаем начало и конец контейнера, сортируем слова по повторяемости
    map<T, int> freqs;

    for (; it != end; it++) {
        ++freqs[*it];
    }

    for (auto& x : freqs) {
        if(x.second == 1)  // если слово в контейнере не повторяется - выводим это слово
            cout << x.first << '\n';
    }

}


int main()
{
                   // задание 1 //////////////////////////////////////////////////////////////////////////
    cout << "\n\n";

    vector<string> st;
    st.push_back("pen");
    st.push_back("pencil");
    st.push_back("book");
    st.push_back("copybook");
    st.push_back("backpack");
    st.push_back("mirror");
    st.push_back("backpack");
    st.push_back("pencil");
    st.push_back("book");
    st.push_back("copybook");
    st.push_back("pen");

    My_Iterator<string> mi(11);  // создаём экземпляр собственного итератора

    for (auto s : st)  // добавляем в итератор все строки
        mi.Add(s);

    print_unique(mi.begin(), mi.end());    // вызываем функцию с итератором начала и конца контейнера

    ////////////////  повторяем всё, но только для типа integer   //////////////////////////////////////////
  
    cout << "\n\n";

    vector<int> sti;
    sti.push_back(1);
    sti.push_back(2);
    sti.push_back(3);
    sti.push_back(4);
    sti.push_back(5);
    sti.push_back(6);
    sti.push_back(1);
    sti.push_back(2);
    sti.push_back(3);
    sti.push_back(4);
    sti.push_back(5);

    My_Iterator<int> mii(11);

    for (auto si : sti)
        mii.Add(si);

    print_unique(mii.begin(), mii.end());


                   // задание 2 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string str;
    map<int, string> sents;

    cout << "\n\nEnter sentence, please:\n";
    getline(cin, str);
    cout << str << "\n";

    cout << "\n\n";

    int start = 0;  // начало предложения в подстроке
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.' && (str[i + 1] == ' ' || i == str.length() - 1)) {    // проверяем на конец предложения или на конец введённой строки
            string tmp = str.substr(start, i - start);
            sents.insert({tmp.length(), tmp});          // помещаем длину строки и собственно строку в контейнер
            start = i + 2;   // смещаем начало предложения на новую позицию
        }
    }

    for (auto& x : sents) {       // выводим отсортированные по длине предложения
        cout << x.second << '\n';
    }


    return 0;
}

















