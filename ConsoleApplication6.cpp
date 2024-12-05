#include <iostream>
#include <cmath>
#include <iomanip>
#include <clocale>
#include <fstream>
#include <string>
#include <time.h> 
#include <vector>

using namespace std;

class CAR {
public:
	int year;
	int month;
	int day;
	string number;

public:

	CAR() {};

	CAR(string newyear, string newmonth, string newday, string newnumber) {
		year = stoi(newyear);
		month = stoi(newmonth);
		day = stoi(newday);
		number = newnumber;
	}

	int totalday() {
		return (day + month * 30 + year * 365);
	}

};

int k = 0;
std::vector <CAR> load_txt(ifstream &ist, std::vector <CAR> &data) {

	string year, month, day, number;


	string line;
	while (getline(ist, line)) {
		if (line[2] == '.' && line[5] == '.') {

			day = line.substr(0, 2);
			month = line.substr(3, 2);
			year = line.substr(6, 4);
			number = line.substr(11, 8);
		}
		else {
			day = line.substr(9, 2);
			month = line.substr(12, 2);
			year = line.substr(15, 4);
			number = line.substr(0, 8);
		}
		data.push_back({ year, month, day, number });
	}
	return data;
}

void print_all_cars(const std::vector <CAR> &data) {
	for (int i = 0; i < data.size(); i++) {
		cout << i + 1 << " машина проехала - " << data[i].day << "." << data[i].month << "." << data[i].year << " " << data[i].number << endl;
	}
}

void car_sort(std::vector <CAR> &data) {
	for (int i = 1; i < data.size(); i++) {
		if (data[i].totalday() > data[i - 1].totalday()) {
			swap(data[i], data[i - 1]);
			i = 0;
		}
	}
}

void find_car(const std::vector <CAR> &data, string num) {
	int f = 0;
	for (int i = 0; i < data.size(); i++) {
		if (num == data[i].number) {
			f++;
		}
	}
	if (f > 1)
		cout << "Даты проезда: " << endl;
	else if (f == 1)
		cout << "Дата проезда: " << endl;
	if (f > 0) {
		for (int i = 0, j = 1; i < data.size(); i++) {
			if (num == data[i].number) {
				if (f == 1)
					cout << data[i].day << "." << data[i].month << "." << data[i].year << endl;
				else if (f > 1)
					cout << j << ". " << data[i].day << "." << data[i].month << "." << data[i].year << endl;
				j++;
			}
		}
	}
	if (f == 0)
		cout << "Такая машина не проезжала";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int buf;
	string num;
	ifstream ist("ist.txt");
	if (!ist.is_open()) cout << "Не удалось открыть файл 'ist.txt' !";
	std::vector <CAR> data;
	load_txt(ist, data);
	ist.close();
	ifstream ist2("ist2.txt");
	if (!ist2.is_open()) cout << "Не удалось открыть файл 'ist2.txt' !";
	load_txt(ist2, data);
	ist2.close();
	cout << "Выберите режим работы: " << endl << "1 - Вывести все номера машин с датами их проезда + опциональная сортировка" << endl << "2 - Найти дату проезда машины по её номеру" << endl;
	cin >> buf;
	switch (buf) {
	case 1:
		cout << "Выполнить сортировку по датам?" << endl << "1 - Да, 2 - Нет" << endl;
		cin >> buf;
		switch (buf) {
		case 1:
			car_sort(data);
			print_all_cars(data);
			break;
		case 2:
			print_all_cars(data);
			break;
		}

		break;
	case 2:
		cout << "Введите номер машины" << endl;
		cin >> num;
		find_car(data, num);
		break;
	}

}
