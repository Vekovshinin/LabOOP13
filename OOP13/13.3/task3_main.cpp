#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include "Pair.h"
using namespace std;

ostream& operator<<(ostream& out, map<double, Pair>& m) {
	for (map <double, Pair>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "���� " << it->first << ", value " << it->second;
	}
	return out;
}

void print_vect(Pair elem) {
	cout << "���� " << elem.sum() << ", value " << elem << endl;
}

void menu(const int c, map<double, Pair>& m) {
	switch (c) {
		//sort
	case 1: {
		cout << m << endl;
		cout << "������� < ��� ���������� �� �����������\n������� > ��� ���������� �� ��������\n";
		char op;
		cin >> op;
		if (op == '<') cout << m << endl;
		else if (op == '>') {
			vector<Pair> COPY;
			Pair elem;
			for (map <double, Pair>::iterator it = m.begin(); it != m.end(); ++it) {
				elem = it->second;
				COPY.push_back(elem);
			}
			sort(COPY.begin(), COPY.end(), mem_fun_ref(&Pair::operator>));
			for_each(COPY.begin(), COPY.end(), ptr_fun(print_vect));
			COPY.~vector();
		}
		else cout << "������������ ��������\n";

		break;
	}
		  //find element 
	case 2: {
		cout << m << "\n\n";
		cout << "������� ��������:\n";
		Pair value;
		cin >> value;
		const auto it = find_if(m.begin(), m.end(), [&value](decltype(*m.begin())& it)->bool {
			return it.second == value; 
			});

		if (it == m.end()) {
			cout << "������ �������� ���!" << endl;
			break;
		}
		for (map<double, Pair>::iterator i = m.begin(); i != m.end(); ++i) {
			if (i == it) {
				cout << "�������:  " << i->second << endl;
			}
		}
		break;
	}
		  //arithmetical mean
	case 3: {
		cout << m << endl << endl;
		Pair sum;
		for (auto it = m.begin(); it != m.end(); it++) sum += it->second;
		sum.set_first(sum.get_first() / m.size());
		sum.set_second(round((double)(sum.get_second() / m.size()) * 100) / 100);
		cout << "������� �������������� ����� " << sum.sum() << " in pair " << sum << "\n\n";
		m.insert(make_pair(sum.sum(), sum));
		cout << m << endl;
		break;
	}
		  //delete from range
	case 4: {
		cout << m << endl << endl;
		int one, two;
		cout << "\n������� ������ �������:\n"; cin >> one;
		cout << "\n������� ������ �������:\n"; cin >> two;
		if (one > two) swap(one, two);
		while (find_if(m.begin(), m.end(), [&one, &two](decltype(*m.begin())& it) -> bool {
			return it.second.sum() > one && it.second.sum() < two; // comparing with the object
			}) != m.end()) {
			const auto it = find_if(m.begin(), m.end(), [&one, &two](decltype(*m.begin())& it) -> bool {
				return it.second.sum() > one && it.second.sum() < two; // comparing with the object
				});
			m.erase(it->first);
		}

		cout << endl << m << endl;
		break;
	}
		  //minmax
	case 5: {
		cout << m << endl << endl;
		const auto mini = m.begin();
		const auto maxi = --m.end();
		cout << "min: " << mini->second << endl;
		cout << "max: " << maxi->second << endl;

		Pair sum;
		sum = mini->second + maxi->second;
		cout << "����� = " << sum << endl;
		for (auto it = m.begin(); it != m.end(); it++) {
			it->second.set_second(it->second.get_second() + sum.get_second());
			it->second.set_first(it->second.get_first() + sum.get_first());
		}
		cout << endl << m << endl;
		break;
	}
		  //print
	case 6: {
		cout << m << endl;
		break;
	}
		  //exit
	default: {
		cout << "\n����� �� ����" << endl;
		exit(777);
	}
	}
}


int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Ru");
	int n;
	cout << "������� ���������� ��������� ����������: ";
	cin >> n;
	map<double, Pair> m;
	for (int i = 0; i < n; ++i) {
		Pair p;
		p.set_random();
		m.insert(make_pair(p.sum(), p));
	}
	cout << m << endl;

	while (true) {
		system("pause");
		system("cls");
		cout << "1. ���������� ����������" << endl;
		cout << "2. ����� ���� ����" << endl;
		cout << "3. ��������� � ����� ������� ��������������" << endl;
		cout << "4. �������� ��������� �� ���������" << endl;
		cout << "5. �������� ������ ����������� � ������������ �������� ��� ������ ����" << endl;
		cout << "6. ��������� ��� ������" << endl;
		cout << "�������� ���� �������: ";
		int c;
		cin >> c;
		system("cls");
		menu(c, m);
	}
	return 0;
}