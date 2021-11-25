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

#include <gtest/gtest.h>

using namespace std;

class Person {
private:
    string m_last_name;        // surname
    string m_first_name;
    string m_patronymic;
public:
    Person(string lname, string fname, string pname) : m_last_name(lname), m_first_name(fname), m_patronymic(pname) {}
    Person(string lname, string fname) : m_first_name(lname), m_last_name(fname) { m_patronymic = ""; }                                    // перегружаем конструктор для людей без отчества

    friend std::ostream& operator<< (std::ostream& out, const Person& person) {                                        // перегружаем оператор вывода
        out << " " << person.m_last_name << "  " << person.m_first_name << "  " << person.m_patronymic << "  ";
        return out;
    }

    friend bool operator< (const Person& p1, const Person& p2) {                                                  // перегружаем оператор <
        if (p1.m_patronymic == "" || p2.m_patronymic == "")         // если нет отчества - сравниваем без него
            return tie(p1.m_first_name, p1.m_last_name) < tie(p2.m_first_name, p2.m_last_name);
        else
            return tie(p1.m_first_name, p1.m_patronymic, p1.m_last_name) < tie(p2.m_first_name, p2.m_patronymic, p2.m_last_name);
    }

    friend bool operator== (const Person& p1, const Person& p2) {                                                 // перегружаем оператор ==
        if (p1.m_patronymic == "" || p2.m_patronymic == "")         // если нет отчества - сравниваем без него
            return tie(p1.m_last_name, p1.m_first_name) == tie(p2.m_last_name, p2.m_first_name);
        else
            return tie(p1.m_last_name, p1.m_first_name, p1.m_patronymic) == tie(p2.m_last_name, p2.m_first_name, p2.m_patronymic);
    }

    string Get_SurName() {
        return m_last_name;
    }

    string Get_FirstName() {
        return m_first_name;
    }

    string Get_PatrName() {
        return m_patronymic;
    }
};


class PhoneNumber {
private:
    int m_country_code = 0;
    int m_city_code = 0;
    string m_number = "";
    int m_add = 0;
public:
    PhoneNumber() {}
    PhoneNumber(int country_c, int city_c, string number, int add = 0) : m_country_code(country_c), m_city_code(city_c), m_number(number), m_add(add) {}

    friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& pn) {                                        // перегружаем оператор вывода
        if (pn.m_add != 0)
            out << "+" << pn.m_country_code << "(" << pn.m_city_code << ")" << pn.m_number << " " << pn.m_add << "\n";  // если есть добавочный код
        else
            out << "+" << pn.m_country_code << "(" << pn.m_city_code << ")" << pn.m_number << "\n";
        return out;
    }

    int Get_Country_Code() {
        return m_country_code;
    }

    int Get_City_Code() {
        return m_city_code;
    }

    string Get_Number() {
        return m_number;
    }
};


class PhoneBook {
private:
    vector<pair<Person, PhoneNumber>> PP;
public:
    PhoneBook(string fname) {
        ifstream is(fname);
        if (is.is_open()) {     // проверяем, открыт ли файл
            char buf[256];

            while (!is.eof()) {
                is.getline(buf, 256, '\n');    // в buf получаем строку из файла
                //cout << buf << "\n\n";

                string s(buf);  // преобразуем c-style строку в std::string
                s = s + " ";    // добавляем в конец строки пробел для работы функции поиска
                size_t found;
                size_t start = 0;
                string lname, fname, pname, country_code, city_code, number, add;

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    lname = s.substr(start, found - start);      // парсим фамилию
                    //cout << lname << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    fname = s.substr(start, found - start);      // парсим имя
                    //cout << fname << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    pname = s.substr(start, found - start);      // парсим отчество
                    //cout << pname << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    country_code = s.substr(start, found - start);      // парсим код страны
                    //cout << country_code << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    city_code = s.substr(start, found - start);      // парсим код города
                    //cout << city_code << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    number = s.substr(start, found - start);      // парсим номер телефона
                    //cout << number << "\n";
                    start = found + 1;
                }

                found = s.find(" ", start);
                if (found != std::string::npos) {
                    add = s.substr(start, found - start);      // парсим добавочный код
                    //cout << add << "\n";
                    start = found + 1;
                }

                //cout << "\n";

                if (pname == "-")      // если нет отчества
                    pname = "";
                Person pr(lname, fname, pname);

                int icountry_c, icity_c, iadd;
                icountry_c = stoi(country_code);  // переводим string в integer
                icity_c = stoi(city_code);

                if (add == "-")     // если нет добавочного кода
                    iadd = 0;
                else
                    iadd = stoi(add);

                PhoneNumber pn(icountry_c, icity_c, number, iadd);

                PP.push_back(make_pair(pr, pn));  // добавляем пару в вектор
            }

            is.close();
        }
        else
            cout << "Can't open file:  " << fname << "\n\n";
    }

    friend std::ostream& operator<< (std::ostream& out, const PhoneBook& pb) {      // перегружаем оператор вывода

        for (int i = 0; i < pb.PP.size(); i++)
            out << pb.PP[i].first << pb.PP[i].second;

        return out;
    }

    void SortByName() {

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                string sname1 = p1.first.Get_SurName();
                string sname2 = p2.first.Get_SurName();
                return sname1[0] < sname2[0];                // сортируем по первой букве фамилии
            }
        );

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                string sname1 = p1.first.Get_SurName();
                string sname2 = p2.first.Get_SurName();
                return (sname1[1] < sname2[1] && sname1[0] == sname2[0]);                // сортируем по второй букве фамилии, при условии, что предыдущие буквы равны
            }
        );

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                string sname1 = p1.first.Get_SurName();
                string sname2 = p2.first.Get_SurName();
                return (sname1[2] < sname2[2] && sname1[1] == sname2[1]);                // сортируем по третьей букве фамилии, при условии, что предыдущие буквы равны
            }
        );

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                string sname1 = p1.first.Get_SurName();
                string sname2 = p2.first.Get_SurName();
                string fname1 = p1.first.Get_FirstName();
                string fname2 = p2.first.Get_FirstName();
                return (fname1[0] < fname2[0] && sname1 == sname2);                // сортируем по первой букве имени, при условии, что фамилии одинаковые
            }
        );

    }


    void SortByPhone() {

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                int concode1 = p1.second.Get_Country_Code();
                int concode2 = p2.second.Get_Country_Code();
                return concode1 < concode2;                     // сортируем по кантри коду
            }
        );

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                int concode1 = p1.second.Get_Country_Code();
                int concode2 = p2.second.Get_Country_Code();
                int citcode1 = p1.second.Get_City_Code();
                int citcode2 = p2.second.Get_City_Code();
                return (citcode1 < citcode2&& concode1 == concode2);                     // сортируем по city коду, при условии, что коды страны одинаковые
            }
        );

        sort(PP.begin(), PP.end(),
            [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2) -> bool
            {
                int concode1 = p1.second.Get_Country_Code();
                int concode2 = p2.second.Get_Country_Code();
                int citcode1 = p1.second.Get_City_Code();
                int citcode2 = p2.second.Get_City_Code();
                int num1 = stoi(p1.second.Get_Number());
                int num2 = stoi(p2.second.Get_Number());
                return (num1 < num2&& citcode1 == citcode2 && concode1 == concode2);     // сортируем по номеру, при условии, что коды страны одинаковые и city коды одинаковые
            }
        );

    }

    tuple<string, PhoneNumber> GetPhoneNumber(const string& sname) {
        int i = 0, count = 0, target = 0;
        string s;
        for_each(PP.begin(), PP.end(),
            [sname, &i, &count, &target](pair<Person, PhoneNumber> p) mutable
            {
                if (p.first.Get_SurName() == sname)
                {
                    target = count;         // помещаем в target индекс элемента в vector
                    ++i;    // если есть совпадения
                }
                ++count;    // общий счёт элементов
            }
        );
        if (i == 0) {
            s = "not found";
            PhoneNumber pn;
            return make_tuple(s, pn);
        }
        if (i == 1) {         // найдено единственное совпадение
            s = sname + " found at " + to_string(target) + " positon , ";
            return make_tuple(s, PP[target].second);
        }
        if (i > 1) {
            s = "found more than 1";
            PhoneNumber pn;
            return make_tuple(s, pn);
        }
    }

    string ChangePhoneNumber(string& sname, string& fname, string& pname, string& country_c, string& city_c, string& number, string add = "") {
        bool has_found = false;
        int count = 0, target = 0;

        vector<pair<Person, PhoneNumber>>::iterator it = find_if(PP.begin(), PP.end(),
            [sname, fname, pname, country_c, city_c, number, add, this, &has_found, &count, &target](pair<Person, PhoneNumber> p) mutable
            {
                if (p.first.Get_SurName() == sname && p.first.Get_FirstName() == fname && p.first.Get_PatrName() == pname)   // найдено совпадение по персоне
                {
                    target = count;

                    PP.erase(PP.begin() + target);   // удаляем старый элемент (c прежним номером телефона) вектора

                    Person pr(sname, fname, pname);
                    string s = add;
                    if (s == "")  s = "0";
                    PhoneNumber pn(stoi(country_c), stoi(city_c), number, stoi(s));
                    PP.push_back(make_pair(pr, pn));  // формируем и добавляем новую пару (с новым номером) в вектор

                    has_found = true;
                }
                ++count;
                return false;
            }
        );
        if (!has_found)
            return "No matches found!";
        else {
            return "Account has changed!";
        }
    }

};


class PhoneBookTests : public testing::Test
{
protected:
    PhoneBook *book;
    void SetUp() override
    {
        book = new PhoneBook("phb.txt");
    }
};

TEST_F(PhoneBookTests, Compare_ScoreIsTen)
{
    string sname = "Davydov";       // прежние ФИО (имеющиеся в базе)
    string fname = "Filipp";
    string pname = "Grigorevich";

    string country_code = "7";      // новый номер , будет вместо старого
    string city_code = "624";
    string number = "1234567";
                                // не могу сообразить, на что протестировать все эти классы
								// на ум пришло только наличие-отсутствие ФИО в базе данных
								// может, подкините идеи?
    ASSERT_STREQ(book->ChangePhoneNumber(sname, fname, pname, country_code, city_code, number).c_str(), "Account has changed!");
}

int main(int argc, char** argv) {

	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}