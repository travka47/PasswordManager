#include "parsing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;

string GetConfig() {
	ifstream fin("config.txt");
	char ch; string conf1;
	while (fin.get(ch))
		conf1 = conf1 + ch;
	fin.close();
	return conf1;
}

void NewConfig() { //C:\MyProjects\les\Debug"base.txt"
	ofstream fout("config.txt");
	string new_conf1;
	cout << "������� ������ ���� � �����" << endl;
	cin >> new_conf1;
	if (fout.is_open()) {
		fout << new_conf1;
		cout << "���� ��� ������" << endl;
		fout.close();
	}
	else cout << "������ �������� �����" << endl;
}

void ReadingData(Data* (&d), int& n) {
	ifstream reading(GetConfig());
	if (reading) {
		reading >> n;
		d = new Data[n];

		for (int i = 0; i < n; i++) {
			reading >> d[i].site;
			reading >> d[i].login;
			reading >> d[i].password;
		}
		reading.close();
	}
	else cout << "������ �������� �����" << endl;
}

void SavingData(Data* (&d), int& n) {
	ofstream record(GetConfig());
	if (record) {
		record << n << endl;

		for (int i = 0; i < n; i++) {
			record << d[i].site << endl;
			record << d[i].login << endl;
			if (i < n - 1)
				record << d[i].password << endl;
			else record << d[i].password;
		}
		record.close();
	}
	else cout << "������ �������� �����" << endl;
}

void MasterChange(Data* (&d), int& n) {
	string new_master, old_master, old_password, new_password;

	cout << "������� ������������ ������-������" << endl;
	vector<char> old_master_console;
	char c;
	while ((c = _getch()) != '\r') {
		old_master.push_back(c);
		_putch('*');
	}

	if (myhash(d, old_master, 1) != d[0].password) {
		cout << endl << "������� ����� ������-������";
		exit(0);
	}
	else {
		cout << endl << "������� ����� ������-������" << endl;
		vector<char> new_master_console;
		char c;
		while ((c = _getch()) != '\r') {
			new_master.push_back(c);
			_putch('*');
		}

		for (int i = 1; i < n; i++)
			d[i].password = mydehash(d, d[i].password, 0);

		d[0].password = myhash(d, new_master, 1);

		for (int i = 1; i < n; i++)
			d[i].password = myhash(d, d[i].password, 0);

		cout << endl << "������-������ ��� ������" << endl;
	}
}

void Start(Data* (&d), int& n) {
	string console_master;
	cout << "������� ������-������" << endl;
	vector<char> console;
	char c;
	while ((c = _getch()) != '\r') {
		console_master.push_back(c);
		_putch('*');
	}
	console_master = myhash(d, console_master, 1);

	if (console_master == d[0].password) cout << endl << "����� ����������!" << endl;
	else {
		cout << endl << "������� ����� ������-������";
		exit(0);
	}
}

void Buffer(Data* (&d), int& n) {
	string site, login, copy;
	bool flag_site = false, flag_login = false;
	cout << "������� ����" << endl;
	cin >> site;
	cout << "������� �����, ��� �������� ������ ����������� ������" << endl;
	cin >> login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
	}

	if (!flag_site) cout << "� ���� ��� ������ ��� ���������� �����, ��������� ������������ �������� ������" << endl;
	else if (flag_site && !flag_login) cout << "�� ����� �� ��������������� ������������ � ��������� �������" << endl;
	else {
		for (int i = 1; i < n; i++)
			if (d[i].site == site && d[i].login == login)
				copy = mydehash(d, d[i].password, 0);

		const char* output = copy.c_str();
		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
		cout << "������ ���������� � ����� ������" << endl;
	}
}

void AddData(Data* (&d), int& n) {
	string new_site, new_login, new_password;
	bool flag_login = false;
	cout << "������� ����" << endl;
	cin >> new_site;
	cout << "������� �����" << endl;
	cin >> new_login;

	for (int i = 1; i < n; i++) 
		if (d[i].login == new_login) flag_login = true;

	if (flag_login) cout << "�� ����� ��� ��������������� ������������ � ������ �������" << endl;
	else {
		cout << "������� ������" << endl;
		vector<char> password;
		char c;
		while ((c = _getch()) != '\r') {
			new_password.push_back(c);
			_putch('*');
		}

		Data* temp = new Data[n];
		Copy(temp, d, n);
		n++;
		d = new Data[n];
		Copy(d, temp, --n);

		d[n].site = new_site;
		d[n].login = new_login;
		d[n].password = myhash(d, new_password, 0);

		n++;
		delete[] temp;
		cout << endl << "������ ���������" << endl;
	}
}

void ChangeLogin(Data* (&d), int& n) {
	string site, old_login, new_login, password;
	bool flag_site = false, flag_login = false;
	int number;
	cout << "������� ����" << endl;
	cin >> site;
	cout << "������� �����, ������� ������ ��������" << endl;
	cin >> old_login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == old_login) flag_login = true;
		if (d[i].site == site && d[i].login == old_login) number = i;
	}

	if (!flag_site) cout << "� ���� ��� ������ ��� ���������� �����, ��������� ������������ �������� ������" << endl;
	else if (flag_site && !flag_login) cout << "�� ����� �� ��������������� ������������ � ��������� �������" << endl;
	else {
		cout << "������� ������ ��� ���������� ������" << endl;
		vector<char> password_console;
		char c;
		while ((c = _getch()) != '\r') {
			password.push_back(c);
			_putch('*');
		}

		if (myhash(d, password, 0) == d[number].password) {
			cout << endl << "������� ����� �����" << endl;
			cin >> new_login;
			d[number].login = new_login;
			cout << "����� ��� ������" << endl;
		}
		else cout << endl << "������ ����� �������, ����� �� ��� ������" << endl;
	}
}

void ChangePassword(Data* (&d), int& n) {
	string site, login, new_password, old_password;
	bool flag_site = false, flag_login = false;
	int number;
	cout << "������� ����" << endl;
	cin >> site;
	cout << "������� �����, ������ ��� �������� ������ ��������" << endl;
	cin >> login;

	
	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
		if (d[i].site == site && d[i].login == login) number = i;
	}

	if (!flag_site) cout << "� ���� ��� ������ ��� ���������� �����, ��������� ������������ �������� ������" << endl;
	else if (flag_site && !flag_login) cout << "�� ����� �� ��������������� ������������ � ��������� �������" << endl;
	else {
		cout << "������� ������, ������� ������ ��������" << endl;
		vector<char> old_password_console;
		char c;
		while ((c = _getch()) != '\r') {
			old_password.push_back(c);
			_putch('*');
		}

		if (myhash(d, old_password, 0) == d[number].password) {
			cout << endl << "������� ����� ������" << endl;
			vector<char> new_password_console;
			char c;
			while ((c = _getch()) != '\r') {
				new_password.push_back(c);
				_putch('*');
			}
			d[number].password = myhash(d, new_password, 0);
			cout << endl << "������ ��� ������" << endl;
		}
		else cout << endl << "������ ����� �������" << endl;
	}
}

void CheckPassword(Data* (&d), int& n) {
	string site, login;
	bool flag = false;
	cout << "������� ����" << endl;
	cin >> site;
	cout << "������� �����, ��� �������� ������ ��������� ������� ������" << endl;
	cin >> login;

	for (int i = 1; i < n; i++)
		if (d[i].site == site && d[i].login == login)
			flag = true;
	
	if (flag) cout << "������ ����������" << endl;
	else cout << "������ ��� ���� ������ �� ����������" << endl;
}

void CheckSites(Data* (&d), int& n) {
	Sorting(d, n);
	cout << "��������� �����:\n";
	for (int i = 1; i < n; i++)
		if (d[i].site != d[i - 1].site)
			cout << d[i].site << endl;
}

void CheckLogins(Data* (&d), int& n) {
	string site;
	bool flag = false;
	cout << "������� ����, ������ ��� �������� ������ ����������" << endl;
	cin >> site;
	for (int i = 1; i < n; i++)
		if (d[i].site == site) {
			cout << d[i].login << endl;
			flag = true;
		}
	if (!flag) cout << "��� ��������� ����� ��� �� ���������� �� ������ ������" << endl;
}

void DeletePassword(Data* (&d), int& n) { 
	string site, login;
	bool flag_site = false, flag_login = false;
	cout << "������� ����" << endl;
	cin >> site;
	cout << "������� �����, ��� �������� ������ ������� ������" << endl;
	cin >> login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
	}

	if (!flag_site) cout << "� ���� ��� ������ ��� ���������� �����, ��������� ������������ �������� ������" << endl;
	else if (flag_site && !flag_login) cout << "�� ����� �� ��������������� ������������ � ��������� �������" << endl;
	else {
		Data* temp = new Data[n];
		Copy(temp, d, n);
		--n;
		d = new Data[n];

		int j = 0;
		for (int i = 0; i <= n; i++)
			if (temp[i].site != site && temp[i].login != login) {
				d[j] = temp[i];
				++j;
			}

		delete[] temp;
		cout << "������ �����" << endl;
	}
}

void DeleteAll(Data* (&d), int& n) { 
	string site;
	bool flag = false;
	cout << "������� ����, ��� �������� ������ ������� ��� ������" << endl;
	cin >> site;

	for (int i = 1; i < n; i++)
		if (d[i].site == site)
			flag = true;

	if (!flag) cout << "� ���� ��� ������ ��� ���������� �����, ��������� ������������ �������� ������" << endl;
	else {
		Data* temp = new Data[n];
		Copy(temp, d, n);
		int n_const = n;

		for (int i = 0; i < n_const; i++)
			if (temp[i].site == site)
				--n;
		d = new Data[n];

		int j = 0;
		for (int i = 0; i < n_const; i++)
			if (temp[i].site != site) {
				d[j] = temp[i];
				++j;
			}
		cout << "������ �������" << endl;
	}
}

void Copy(Data* (&d_new), Data* (&d_old), int& n) {
	for (int i = 0; i < n; i++)
		d_new[i] = d_old[i];
}

void CopyEl(Data& d_new, Data& d_old) {
	d_new.site = d_old.site;
	d_new.login = d_old.login;
	d_new.password = d_old.password;
}

void Sorting(Data* (&d), int& n) {
	Data temp;
	for (int i = 1; i < n; i++) 
		for (int j = i + 1; j < n; j++)
			if (d[i].site > d[j].site) {
				CopyEl(temp, d[j]);
				CopyEl(d[j], d[i]);
				CopyEl(d[i], temp);
			}
	SavingData(d, n);
}
