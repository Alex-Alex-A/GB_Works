#include "pch.h"
#include <string>
//#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
//#include <memory>
#include <vector>
//#include <deque>
#include <iterator>
//#include <stdarg.h>
//#include <cstddef>
//#include <string_view>
//#include <tuple>
//#include <list>
//#include <any>
//#include <numeric>
//#include <set>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
//#define _USE_MATH_DEFINES
//#include <math.h>
//#include "Timer.h"


using namespace std;

mutex g_lock;

void pcout(int a)
{
    lock_guard lg(g_lock);     // блокируем процесс
    
    this_thread::sleep_for(chrono::seconds(rand() % 10));
    cout << a << "\n";
}


int counter = 0;     // глобальная переменная, счётчик числа найденных простых чисел
int cur_pos = 0, step = 1000;     // текущая позиция и шаг для вывода результатов в основном потоке

int is_prime(int x) {
    int num = 2;
    cout << "Calculating. Please, wait...\n";

    while (counter < x) {
        bool is_prime = true;
        for (int i = 2; i < num; ++i) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime)
            ++counter;

        num++;
    }
    return num - 1;
}

void async_out(int n) {
    while (counter < n - 1) {
        if (counter > cur_pos) {
            cur_pos += step;
            cout << "Calculated " << counter << " numbers (this message has shown at parallel thread)\n";
        }
    }
}

vector<int> things;         // вещи с ценностью от 1 до 10

void Master() {
    for (int i = 0; i < 10; i++) {
        int th = 1 + rand() % 10;  // добавляем вещь с ценностью от 1 до 10
        g_lock.lock();     // блокируем процесс
        things.push_back(th);
        g_lock.unlock();   // разблокируем процесс
        cout << "Brought: " << th << "\n";

        this_thread::sleep_for(chrono::seconds(1));  // делаем задержку
    }
}

void Thief() {
    for (int i = 0; i < 10; i++) {
        g_lock.lock();     // блокируем процесс
        vector<int>::iterator it = max_element(things.begin(), things.end());  // вор забирает самую ценную вещь
        cout << "Stolen: " << *it << "\n";
        things.erase(it);
        g_lock.unlock();   // разблокируем процесс

        this_thread::sleep_for(chrono::seconds(2));  // делаем задержку
    }
}

int main()
{
                   // задание 1
    thread thr1(pcout, 1);
    thread thr2(pcout, 2);
    thread thr3(pcout, 3);
    thread thr4(pcout, 4);
    thread thr5(pcout, 5);
    thread thr6(pcout, 6);
    thread thr7(pcout, 7);
    thread thr8(pcout, 8);
    thread thr9(pcout, 9);
    thread thr10(pcout, 10);

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();
    thr5.join();
    thr6.join();
    thr7.join();
    thr8.join();
    thr9.join();
    thr10.join(); //

                   // задание 2
    cout << "\n\n";

    int n_th_prime = 70000;           // какое по счёту простое число нужно найти. Поставил 70000, т.к. 1000000 считается очень долго, во всяком случае, на моём компьютере

    future<int> fut = async(launch::async, is_prime, n_th_prime);     // расчёт простого числа

    cout << "Checking " << n_th_prime << "'th prime number.\n";
// ...
    async(launch::async, async_out, n_th_prime);                      // вывод процесса расчёта

    int ret = fut.get();      // waits for is_prime to return

    cout << "\n" << n_th_prime << "'th prime number is: " << ret << "\n\n";

                   // задание 3
    things.push_back(7);  // сразу ложим несколько вещей
    things.push_back(8);
    things.push_back(9);

    cout << "There are initial things with values: 7, 8, 9\n";

    thread thr11(Master);
    thread thr22(Thief);
    thr11.join();
    thr22.join();  //


    return 0;
}

















