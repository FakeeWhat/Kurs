#include "Savin.h"

enum code {
	change = 1,
	viewing,
	report,
};


void Menu() {

	int l, i;
	string k;
	cout << endl << BROWN_TEXT << "Выберите, что хотите сделать: " << RESET_COLOR << endl;
	cout << YELLOW_TEXT << "1 - добавить/удалить/изменить запись\n";
	cout << "2 - просмотр записей\n";
	cout << "3 - отчёт по владельцам\n";
	cout << "0 - выход из программы\n" << RESET_COLOR;
	while (1) {
		try {
			cout << BROWN_TEXT << "Выбор... " << RESET_COLOR << "\n» ";
			cin >> k;
			if (k[0] >= '0' && k[0] <= '3' && k[1] == '\0')
				i = k[0] - '0';

			else
				throw runtime_error(RED_TEXT "Такой команды не существует! Попробуйте еще раз..." RESET_COLOR);
		}
		catch (const exception& error) {
			cerr << error.what() << endl;
			continue;
		}

		switch (i) {
		case change:
			cout << BROWN_TEXT << "Выберите, что хотите сделать: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - Добавить запись\n"
				<< "2 - Удалить запись по номеру авто\n"
				<< "3 - Изменить запись по ФИО владельца\n"
				<< "0 - Выйти в меню\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "Выбор... " << RESET_COLOR << "\n» ";
				cin >> l;
				if (l == 1) {
					addInfo();
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 2) {
					cin.ignore();
					delInfo();
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 3) {
					cin.ignore();
					changeInfo();
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 0) {
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
				}
				else {
					cout << RED_TEXT << "Такой команды не существует! Попробуйте еще раз... " << RESET_COLOR << endl;
					continue;
				}
			}
		case viewing:
			cout << BROWN_TEXT << "Выберите, что хотите сделать: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - Выдать на экран список всех записей\n"
				<< "2 - Выдать на экран список всех марок автомобилей и их количество\n"
				<< "0 - Выйти в меню\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "Выбор... " << RESET_COLOR << "\n» ";
				cin >> l;
				if (l == 1) {
					displayFileContent("car_records.txt");
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 2) {
					displayBrandList("car_records.txt");
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 0) {
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
				}
				else {
					cout << RED_TEXT << "Такой команды не существует! Попробуйте еще раз..." << RESET_COLOR << endl;
					continue;
				}
			}
		case report:
			cout << BROWN_TEXT << "Выберите, что хотите сделать: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - Сформировать файл-отчёт с автомобилями определённого владельца\n"
				<< "2 - Выдать на экран содержимое файла-отчёта\n"
				<< "0 - Выйти в меню\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "Выбор..." << RESET_COLOR << "\n» ";
				cin >> l;
				if (l == 1) {
					cin.ignore();
					createFileForOwner("car_records.txt", "owner_file.txt");
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 2) {
					displayFileContent("owner_file.txt");
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
					break;
				}
				if (l == 0) {
					cout << endl << BROWN_TEXT << "===============================================" << endl;
					Menu();
				}
				else {
					cout << RED_TEXT << "Такой команды не существует! Попробуйте еще раз..." << RESET_COLOR << endl;
					continue;
				}
			}
		case 0:
			exit(1);

		default:
			cout << RED_TEXT << "Такой команды не существует! Попробуйте еще раз... \n" << RESET_COLOR << endl;
			Menu();
		}

	}
}


void password() {
	int popitki = 4;
	ifstream file("password.txt");
	if (!file.is_open()) {
		cerr << RED_TEXT << "Ошибка открытия файла с хэшем пароля." << RESET_COLOR << endl;
		exit(1);
	}
	string hash;
	file >> hash;
	file.close();
	string password;
	while (1) {
		try {
			if (hash == hashPassword(password)) {
				cout << BROWN_TEXT << endl << "*********************************************" << RESET_COLOR << endl;
				cout << YELLOW_TEXT << "Добро пожаловать в программу по обработке данных по автомобилям!" << RESET_COLOR << endl;
				cout << "Версия: " << BLUE_TEXT << "1.0" << RESET_COLOR << endl;
				cout << "Автор: " << YELLOW_TEXT << "Савин Дмитрий" << RESET_COLOR << endl;
				cout << BROWN_TEXT << "*********************************************" << RESET_COLOR << endl;
				break;
			}
			else if (popitki == 3) {
				throw runtime_error(RED_TEXT "Вы ввели неверный пароль! У вас осталось 3 попытки!");
			}
			else if (popitki == 2)
				throw runtime_error(RED_TEXT "Вы ввели неверный пароль! У вас осталось 2 попытки!");
			else if (popitki == 1)
				throw runtime_error(RED_TEXT "Вы ввели неверный пароль! У вас осталось 1 попытка!");
		}
		catch (const exception& error) {
			cout << error.what() << endl;
		}
		try {
			if (popitki == 0)
				throw runtime_error(RED_TEXT "Исчерпан максимальный лимит попыток ввода пароля." RESET_COLOR);
		}
		catch (const exception& error) {
			cout << error.what() << endl;
			exit(1);
		}
		cout << YELLOW_TEXT << "Введите пароль: " << RESET_COLOR << "\n» ";
		cin >> password;
		popitki--;
	}

}