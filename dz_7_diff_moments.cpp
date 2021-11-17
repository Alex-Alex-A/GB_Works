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

class StudentsGroup {
private:
    string m_FirstName;
    string m_LastName;
    string m_Patronymic;
    vector<int> marks;
public:
    StudentsGroup(string fname, string lname, string pname) : m_FirstName(fname), m_LastName(lname), m_Patronymic(pname) {}
    void Open(string path, string& result) {
        ifstream in(path, ios::binary);
        result.resize(1024);
        in.read(result.data(), result.size());
        result.resize(in.gcount());
    }
    void Save(string path, string data) {
        ofstream out(path, ios::binary);
        out.write(data.c_str(), data.size());
    }

    double GetAverageScore() {
        double avg = 0.0;
        for (int i = 0; i < marks.size(); i++) {
            avg += static_cast<double>(marks.at(i));
        }
        return avg;
    }
    string GetAllInfo() {
        return m_FirstName + " " + m_LastName + " " + m_Patronymic + " " + to_string(GetAverageScore());      
    }
};


int main()
{
                   // задание 3




    return 0;
}

















