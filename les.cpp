#include "parsing.h"
#include <iostream>
#include <fstream>
using namespace std;

int stateMenu;
void Menu() {
	cout << endl << "  МЕНЮ\n"
		<< "(0) Выход из программы\n"
		<< "(1) Изменить путь\n"
		<< "(2) Установить новый мастер-пароль\n"
		<< "(3) Скопировать пароль в буфер обмена\n"
		<< "(4) Добавить данные\n"
		<< "(5) Изменить логин\n"
		<< "(6) Изменить пароль\n"
		<< "(7) Проверить наличие пароля\n"
		<< "(8) Вывести все сайты, на которых зарегистрирован пользователь\n"
		<< "(9) Вывести все существующие логины для сайта\n"
		<< "(10) Удалить пароль\n"
		<< "(11) Удалить все пароли для сайта\n"
		<< "Ваш выбор: ";
	cin >> stateMenu;
};

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int amountOfData = 0;
	Data* d = new Data[amountOfData];
	ReadingData(d, amountOfData);
	Start(d, amountOfData);
	Menu();
	while (stateMenu != 0)
	{
		switch (stateMenu)
		{
			////////////////////////////////////////////////////////////////////////
		case 1:
			NewConfig();
			ReadingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 2:
			MasterChange(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 3:
			Buffer(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 4:
			AddData(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 5:
			ChangeLogin(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 6:
			ChangePassword(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 7:
			CheckPassword(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 8:
			CheckSites(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 9:
			CheckLogins(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 10:
			DeletePassword(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		case 11:
			DeleteAll(d, amountOfData);
			SavingData(d, amountOfData);

			system("pause");
			Menu();
			break;
			////////////////////////////////////////////////////////////////////////
		default:
			cout << "Неверно введён номер функции" << endl;
			system("pause");
			Menu();
			break;
		}
	}
}