#include "Savin.h"

enum code {
	change = 1,
	viewing,
	report,
};


void Menu() {

	int l, i;
	string k;
	cout << endl << BROWN_TEXT << "��������, ��� ������ �������: " << RESET_COLOR << endl;
	cout << YELLOW_TEXT << "1 - ��������/�������/�������� ������\n";
	cout << "2 - �������� �������\n";
	cout << "3 - ����� �� ����������\n";
	cout << "0 - ����� �� ���������\n" << RESET_COLOR;
	while (1) {
		try {
			cout << BROWN_TEXT << "�����... " << RESET_COLOR << "\n� ";
			cin >> k;
			if (k[0] >= '0' && k[0] <= '3' && k[1] == '\0')
				i = k[0] - '0';

			else
				throw runtime_error(RED_TEXT "����� ������� �� ����������! ���������� ��� ���..." RESET_COLOR);
		}
		catch (const exception& error) {
			cerr << error.what() << endl;
			continue;
		}

		switch (i) {
		case change:
			cout << BROWN_TEXT << "��������, ��� ������ �������: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - �������� ������\n"
				<< "2 - ������� ������ �� ������ ����\n"
				<< "3 - �������� ������ �� ��� ���������\n"
				<< "0 - ����� � ����\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "�����... " << RESET_COLOR << "\n� ";
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
					cout << RED_TEXT << "����� ������� �� ����������! ���������� ��� ���... " << RESET_COLOR << endl;
					continue;
				}
			}
		case viewing:
			cout << BROWN_TEXT << "��������, ��� ������ �������: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - ������ �� ����� ������ ���� �������\n"
				<< "2 - ������ �� ����� ������ ���� ����� ����������� � �� ����������\n"
				<< "0 - ����� � ����\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "�����... " << RESET_COLOR << "\n� ";
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
					cout << RED_TEXT << "����� ������� �� ����������! ���������� ��� ���..." << RESET_COLOR << endl;
					continue;
				}
			}
		case report:
			cout << BROWN_TEXT << "��������, ��� ������ �������: " << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "1 - ������������ ����-����� � ������������ ������������ ���������\n"
				<< "2 - ������ �� ����� ���������� �����-������\n"
				<< "0 - ����� � ����\n" << RESET_COLOR;
			while (1) {
				cout << BROWN_TEXT << "�����..." << RESET_COLOR << "\n� ";
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
					cout << RED_TEXT << "����� ������� �� ����������! ���������� ��� ���..." << RESET_COLOR << endl;
					continue;
				}
			}
		case 0:
			exit(1);

		default:
			cout << RED_TEXT << "����� ������� �� ����������! ���������� ��� ���... \n" << RESET_COLOR << endl;
			Menu();
		}

	}
}


void password() {
	int popitki = 4;
	ifstream file("password.txt");
	if (!file.is_open()) {
		cerr << RED_TEXT << "������ �������� ����� � ����� ������." << RESET_COLOR << endl;
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
				cout << YELLOW_TEXT << "����� ���������� � ��������� �� ��������� ������ �� �����������!" << RESET_COLOR << endl;
				cout << "������: " << BLUE_TEXT << "1.0" << RESET_COLOR << endl;
				cout << "�����: " << YELLOW_TEXT << "����� �������" << RESET_COLOR << endl;
				cout << BROWN_TEXT << "*********************************************" << RESET_COLOR << endl;
				break;
			}
			else if (popitki == 3) {
				throw runtime_error(RED_TEXT "�� ����� �������� ������! � ��� �������� 3 �������!");
			}
			else if (popitki == 2)
				throw runtime_error(RED_TEXT "�� ����� �������� ������! � ��� �������� 2 �������!");
			else if (popitki == 1)
				throw runtime_error(RED_TEXT "�� ����� �������� ������! � ��� �������� 1 �������!");
		}
		catch (const exception& error) {
			cout << error.what() << endl;
		}
		try {
			if (popitki == 0)
				throw runtime_error(RED_TEXT "�������� ������������ ����� ������� ����� ������." RESET_COLOR);
		}
		catch (const exception& error) {
			cout << error.what() << endl;
			exit(1);
		}
		cout << YELLOW_TEXT << "������� ������: " << RESET_COLOR << "\n� ";
		cin >> password;
		popitki--;
	}

}