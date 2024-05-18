#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
#include "Pair.h"
using namespace std;

ostream& operator<<(ostream& out, priority_queue<Pair>& q) {
	vector<Pair> COPY;
	Pair elem;
	int num = q.size();
	for (size_t i = 0; i < num; ++i) {
		elem = q.top();
		cout << elem;
		COPY.push_back(elem);
		q.pop();
	}
	int k = 0;
	for (int i = 0; i < COPY.size(); ++i) {
		q.push(COPY[k++]);
	}
	COPY.clear();
	return out;
}

bool EQUAL(Pair a, Pair t) {
	if (a == t) return true;
	return false;
}

void menu(const int c, priority_queue<Pair>& q) {
	switch (c) {
		//sort
	case 1: {
		char op;
		cout << "������� < ��� ���������� �� �����������\n������� > ��� ���������� �� ��������\n";
		cin >> op;
		if (op == '>') cout << q << endl;
		else if (op == '<') {
			vector<Pair> COPY;
			Pair elem;
			int num = q.size();
			for (int i = 0; i < num; ++i) {
				elem = q.top();
				COPY.push_back(elem);
				q.pop();
			}
			sort(COPY.begin(), COPY.end(), mem_fun_ref(&Pair::operator<));
			for_each(COPY.begin(), COPY.end(), [](Pair& p) {cout << p; });
			while (!COPY.empty()) {
				q.push(COPY[COPY.size() - 1]);
				COPY.pop_back();
			}
		}
		else cout << "������������ ��������!\n";
		break;
	}
		  //find element 
	case 2: {
		cout << q << "\n\n";
		cout << "������� ��������:\n";
		Pair value;
		cin >> value;
		auto f = [value](priority_queue<Pair>& q) {
			vector<Pair> COPY;
			Pair elem;
			bool flag = false;
			int num = q.size();
			for (int i = 0; i < num && !flag; ++i) {
				elem = q.top();
				if (EQUAL(elem, value)) {
					flag = true;
					cout << "�������: " << elem << endl;
				}
				COPY.emplace_back(elem);
				q.pop();
			}
			if (!flag) cout << "������ �������� ���!\n";
			while (!COPY.empty()) {
				q.push(COPY[COPY.size() - 1]);
				COPY.pop_back();
			}
		};
		f(q);
		break;
	}
		  //arithmetical mean
	case 3: {
		cout << q << endl;
		vector<Pair> COPY;
		Pair elem;
		while (!q.empty()) {
			elem = q.top();
			COPY.push_back(elem);
			q.pop();
		}
		Pair sum;
		for_each(COPY.begin(), COPY.end(), [&sum](Pair& p) {sum += p; });
		sum.set_first(round(sum.get_first() / COPY.size() * 100) / 100);
		sum.set_second(round(sum.get_second() / COPY.size() * 100) / 100);
		cout << "������� �������������� ����� " << sum << "\n\n";
		q.push(sum);
		while (!COPY.empty()) {
			q.push(COPY[COPY.size() - 1]);
			COPY.pop_back();
		}
		cout << q << endl;
		break;
	}
		  //delete from range
	case 4: {
		cout << q << endl;
		Pair elem;
		vector<Pair> COPY;
		while (!q.empty()) {
			elem = q.top();
			COPY.push_back(elem);
			q.pop();
		}
		Pair one, two;
		cout << "������� ��������� ������� ��������: " << endl;
		for_each(COPY.begin(), COPY.end(), [](Pair& p) {cout << p.sum() << " "; });

		cout << "\n������� ������ �������:\n"; cin >> one;
		cout << "\n������� ������ �������:\n"; cin >> two;
		if (one > two) swap(one, two);

		auto s = remove_if(COPY.begin(), COPY.end(), [one, two](Pair& p) {return p >= one && p <= two; });
		COPY.erase(s, COPY.end());

		while (!COPY.empty()) {
			q.push(COPY[COPY.size() - 1]);
			COPY.pop_back();
		}
		cout << endl << q << endl;
		break;
	}
		  //minmax
	case 5: {
		cout << q << endl << endl;
		Pair elem;
		vector<Pair> COPY;
		while (!q.empty()) {
			elem = q.top();
			COPY.push_back(elem);
			q.pop();
		}
		auto mini = COPY[COPY.size() - 1];
		auto maxi = COPY[0];
		cout << "min: " << mini;
		cout << "max: " << maxi;
		Pair sum;
		sum = mini + maxi;
		cout << "����� = " << sum << endl;
		for_each(COPY.begin(), COPY.end(), [&sum](Pair& p) {p += sum; });
		while (!COPY.empty()) {
			q.push(COPY[COPY.size() - 1]);
			COPY.pop_back();
		}
		cout << endl << q << endl;
		break;
	}
		  //print
	case 6: {
		cout << q << endl;
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
	system("color F0");
	setlocale(LC_ALL, "Ru");
	int n;
	cout << "������� ������ �������: ";
	cin >> n;
	priority_queue<Pair> q;
	Pair p;
	for (int i = 0; i < n; ++i) {
		p.set_random();
		q.push(p);
	}

	cout << q << endl;
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
		menu(c, q);
	}
	return 0;
}