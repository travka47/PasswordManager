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
	cout << "Введите полный путь к файлу" << endl;
	cin >> new_conf1;
	if (fout.is_open()) {
		fout << new_conf1;
		cout << "Путь был изменён" << endl;
		fout.close();
	}
	else cout << "Ошибка открытия файла" << endl;
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
	else cout << "Ошибка открытия файла" << endl;
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
	else cout << "Ошибка открытия файла" << endl;
}

void MasterChange(Data* (&d), int& n) {
	string new_master, old_master, old_password, new_password;

	cout << "Введите существующий мастер-пароль" << endl;
	vector<char> old_master_console;
	char c;
	while ((c = _getch()) != '\r') {
		old_master.push_back(c);
		_putch('*');
	}

	if (myhash(d, old_master, 1) != d[0].password) {
		cout << endl << "Неверно введён мастер-пароль";
		exit(0);
	}
	else {
		cout << endl << "Введите новый мастер-пароль" << endl;
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

		cout << endl << "Мастер-пароль был изменён" << endl;
	}
}

void Start(Data* (&d), int& n) {
	string console_master;
	cout << "Введите мастер-пароль" << endl;
	vector<char> console;
	char c;
	while ((c = _getch()) != '\r') {
		console_master.push_back(c);
		_putch('*');
	}
	console_master = myhash(d, console_master, 1);

	if (console_master == d[0].password) cout << endl << "Добро пожаловать!" << endl;
	else {
		cout << endl << "Неверно введён мастер-пароль";
		exit(0);
	}
}

void Buffer(Data* (&d), int& n) {
	string site, login, copy;
	bool flag_site = false, flag_login = false;
	cout << "Введите сайт" << endl;
	cin >> site;
	cout << "Введите логин, для которого хотите скопировать пароль" << endl;
	cin >> login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
	}

	if (!flag_site) cout << "В базе нет данных для указанного сайта, проверьте корректность вводимых данных" << endl;
	else if (flag_site && !flag_login) cout << "На сайте не зарегистрирован пользователь с указанным логином" << endl;
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
		cout << "Пароль скопирован в буфер обмена" << endl;
	}
}

void AddData(Data* (&d), int& n) {
	string new_site, new_login, new_password;
	bool flag_login = false;
	cout << "Введите сайт" << endl;
	cin >> new_site;
	cout << "Введите логин" << endl;
	cin >> new_login;

	for (int i = 1; i < n; i++) 
		if (d[i].login == new_login) flag_login = true;

	if (flag_login) cout << "На сайте уже зарегистрирован пользователь с данным логином" << endl;
	else {
		cout << "Введите пароль" << endl;
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
		cout << endl << "Данные добавлены" << endl;
	}
}

void ChangeLogin(Data* (&d), int& n) {
	string site, old_login, new_login, password;
	bool flag_site = false, flag_login = false;
	int number;
	cout << "Введите сайт" << endl;
	cin >> site;
	cout << "Введите логин, который хотите изменить" << endl;
	cin >> old_login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == old_login) flag_login = true;
		if (d[i].site == site && d[i].login == old_login) number = i;
	}

	if (!flag_site) cout << "В базе нет данных для указанного сайта, проверьте корректность вводимых данных" << endl;
	else if (flag_site && !flag_login) cout << "На сайте не зарегистрирован пользователь с указанным логином" << endl;
	else {
		cout << "Введите пароль для указанного логина" << endl;
		vector<char> password_console;
		char c;
		while ((c = _getch()) != '\r') {
			password.push_back(c);
			_putch('*');
		}

		if (myhash(d, password, 0) == d[number].password) {
			cout << endl << "Введите новый логин" << endl;
			cin >> new_login;
			d[number].login = new_login;
			cout << "Логин был изменён" << endl;
		}
		else cout << endl << "Пароль введён неверно, логин не был изменён" << endl;
	}
}

void ChangePassword(Data* (&d), int& n) {
	string site, login, new_password, old_password;
	bool flag_site = false, flag_login = false;
	int number;
	cout << "Введите сайт" << endl;
	cin >> site;
	cout << "Введите логин, пароль для которого хотите изменить" << endl;
	cin >> login;

	
	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
		if (d[i].site == site && d[i].login == login) number = i;
	}

	if (!flag_site) cout << "В базе нет данных для указанного сайта, проверьте корректность вводимых данных" << endl;
	else if (flag_site && !flag_login) cout << "На сайте не зарегистрирован пользователь с указанным логином" << endl;
	else {
		cout << "Введите пароль, который хотите изменить" << endl;
		vector<char> old_password_console;
		char c;
		while ((c = _getch()) != '\r') {
			old_password.push_back(c);
			_putch('*');
		}

		if (myhash(d, old_password, 0) == d[number].password) {
			cout << endl << "Введите новый пароль" << endl;
			vector<char> new_password_console;
			char c;
			while ((c = _getch()) != '\r') {
				new_password.push_back(c);
				_putch('*');
			}
			d[number].password = myhash(d, new_password, 0);
			cout << endl << "Пароль был изменён" << endl;
		}
		else cout << endl << "Пароль введён неверно" << endl;
	}
}

void CheckPassword(Data* (&d), int& n) {
	string site, login;
	bool flag = false;
	cout << "Введите сайт" << endl;
	cin >> site;
	cout << "Введите логин, для которого хотите проверить наличие пароля" << endl;
	cin >> login;

	for (int i = 1; i < n; i++)
		if (d[i].site == site && d[i].login == login)
			flag = true;
	
	if (flag) cout << "Пароль существует" << endl;
	else cout << "Пароль для этих данных не существует" << endl;
}

void CheckSites(Data* (&d), int& n) {
	Sorting(d, n);
	cout << "Доступные сайты:\n";
	for (int i = 1; i < n; i++)
		if (d[i].site != d[i - 1].site)
			cout << d[i].site << endl;
}

void CheckLogins(Data* (&d), int& n) {
	string site;
	bool flag = false;
	cout << "Введите сайт, логины для которого хотите посмотреть" << endl;
	cin >> site;
	for (int i = 1; i < n; i++)
		if (d[i].site == site) {
			cout << d[i].login << endl;
			flag = true;
		}
	if (!flag) cout << "Для введённого сайта ещё не существует ни одного логина" << endl;
}

void DeletePassword(Data* (&d), int& n) { 
	string site, login;
	bool flag_site = false, flag_login = false;
	cout << "Введите сайт" << endl;
	cin >> site;
	cout << "Введите логин, для которого хотите удалить пароль" << endl;
	cin >> login;

	for (int i = 1; i < n; i++) {
		if (d[i].site == site) flag_site = true;
		if (d[i].login == login) flag_login = true;
	}

	if (!flag_site) cout << "В базе нет данных для указанного сайта, проверьте корректность вводимых данных" << endl;
	else if (flag_site && !flag_login) cout << "На сайте не зарегистрирован пользователь с указанным логином" << endl;
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
		cout << "Пароль удалён" << endl;
	}
}

void DeleteAll(Data* (&d), int& n) { 
	string site;
	bool flag = false;
	cout << "Введите сайт, для которого хотите удалить все пароли" << endl;
	cin >> site;

	for (int i = 1; i < n; i++)
		if (d[i].site == site)
			flag = true;

	if (!flag) cout << "В базе нет данных для указанного сайта, проверьте корректность вводимых данных" << endl;
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
		cout << "Пароли удалены" << endl;
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
