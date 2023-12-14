#include "Savin.h"


string hashPassword(const string& password) {
	hash<string> hasher;
	size_t hashValue = hasher(password);
	return to_string(hashValue);
}


//-------------------------------------------------------------------------------------------------------------------------

void createFileForOwner(const char* inputFilename, const char* outputFilename) {
	char ownerNameToFilter[100];
	vector<CarRecord> records;

	do {
		cout << YELLOW_TEXT << "������� ��� ��������� ��� ������������ ����� (������: �������.�.): " << RESET_COLOR;
		cin.getline(ownerNameToFilter, sizeof(ownerNameToFilter));

		if (isOwnerNameExists(inputFilename, ownerNameToFilter, records)) {
			break;
		}
		else {
			cout << RED_TEXT << "��� ��������� " << ownerNameToFilter << " �� ������� �����." << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "������ ����������� ������ ���?" << endl;
			cout << "1 - ��\n"
				<< "2 - ���\n"
				<< "�����... \n� " << RESET_COLOR;
			int tryAgain;
			cin >> tryAgain;

			if (tryAgain != 1) {
				return;
			}

			cin.ignore();
		}

	} while (true);

	ofstream outFile(outputFilename, ios::binary);

	if (!outFile.is_open()) {
		cerr << RED_TEXT << "������ �������� ����� ��� ������." << RESET_COLOR << endl;
		return;
	}

	for (const auto& record : records) {
		outFile.write(reinterpret_cast<const char*>(&record), sizeof(CarRecord));
	}

	outFile.close();

	cout << GREEN_TEXT << "���� ��� ��������� " << ownerNameToFilter << " �����������." << RESET_COLOR << endl;
}



//-----------------------------------------------------------------------------------------------------

void displayBrandList(const char* filename) {
	ifstream inFile(filename, ios::binary);

	if (!inFile.is_open()) {
		cerr << RED_TEXT << "������ �������� �����." << RESET_COLOR << endl;
		return;
	}

	CarRecord currentRecord;
	map<string, int> brandCount;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		// ���������� map ��� �������� ���������� ������ �����
		brandCount[currentRecord.brand]++;
	}

	inFile.close();

	cout << YELLOW_TEXT << "������ ����� ����������� � �� ����������:" << RESET_COLOR << endl;

	for (const auto& pair : brandCount) {
		cout << YELLOW_TEXT << "�����: " << pair.first << ", ����������: " << pair.second << RESET_COLOR << endl;
	}
}




void displayFileContent(const char* filename) {
	ifstream inFile(filename, ios::binary);

	if (!inFile.is_open()) {
		cerr << RED_TEXT << "������ �������� �����." << RESET_COLOR << endl;
		return;
	}

	CarRecord currentRecord;

	cout << YELLOW_TEXT << "���������� ����� '" << filename << "':" << RESET_COLOR << endl;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		cout << YELLOW_TEXT << "�����: " << setw(15) << left << currentRecord.brand
			<< " | �����: " << setw(15) << left << currentRecord.carNumber
			<< " | ��������: " << setw(20) << left << currentRecord.ownerName
			<< " | ����� ������ (�^3): " << setw(15) << left << currentRecord.techSpec1
			<< " | ����������� ����� � ������ (��): " << setw(15) << left << currentRecord.techSpec2
			<< " | ����������� ����� ��� ����� (��): " << setw(15) << left << currentRecord.techSpec3 << RESET_COLOR << endl;
	}

	inFile.close();
}


//--------------------------------------------------------------------------------------------------------------------------


bool isValidCarNumber(const char* carNumber) {
	// �������� ������� ������ ������: �000��00 ��� �000��000
	// ��� � - ����� �����, 0 - ����� �����

	regex pattern1("^[������������][0-9]{3}[������������]{2}[0-9]{2}$");
	regex pattern2("^[������������][0-9]{3}[������������]{2}[0-9]{3}$");

	return regex_match(carNumber, pattern1) || regex_match(carNumber, pattern2);
}



bool isOwnerNameExists(const char* filename, const char* ownerName, vector<CarRecord>& records) {
	ifstream inFile(filename, ios::binary);

	if (!inFile.is_open()) {
		cerr << RED_TEXT << "������ �������� �����." << RESET_COLOR << endl;
		return false;
	}

	CarRecord currentRecord;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		if (strcmp(currentRecord.ownerName, ownerName) == 0) {
			records.push_back(currentRecord);
		}
	}

	inFile.close();
	return !records.empty(); // ���������� true, ���� ������� ������ � ��������� �������� ���������
}

void changeRecordByCarNumber(const char* filename, const char* carNumberToChange, const char* newBrand, const char* newCarNumber, int newTechSpec1, int newTechSpec2, int newTechSpec3, const char* newCarNumber2) {
	ifstream inFile(filename, ios::binary);
	ofstream outFile("temp.txt", ios::binary); // ��������� ���� ��� ������ ���������� �������

	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << RED_TEXT << "������ �������� ������." << RESET_COLOR << endl;
		return;
	}

	CarRecord currentRecord;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		if (strcmp(currentRecord.carNumber, carNumberToChange) == 0) {
			// ��������� ���� ����� ������ � �������� ������� ����������
			strcpy_s(currentRecord.brand, newBrand);
			strcpy_s(currentRecord.carNumber, newCarNumber2);
			currentRecord.techSpec1 = newTechSpec1;
			currentRecord.techSpec2 = newTechSpec2;
			currentRecord.techSpec3 = newTechSpec3;
		}

		outFile.write(reinterpret_cast<const char*>(&currentRecord), sizeof(CarRecord));
	}

	inFile.close();
	outFile.close();

	// ������ ��������� ����� ���������
	remove(filename);
	rename("temp.txt", filename);

	cout << GREEN_TEXT << "������ � ������� ���������� " << carNumberToChange << " ������� �������� � �����." << RESET_COLOR << endl;
}

void changeInfo() {
	char ownerNameToChange[100];
	char newBrand[100];
	char newCarNumber[20];
	char newCarNumber2[20];
	int newTechSpec1, newTechSpec2, newTechSpec3;

	do {
		cout << YELLOW_TEXT << "������� ��� ��������� ��� ��������� ������ (������: �������.�.): " << RESET_COLOR;
		cin.getline(ownerNameToChange, sizeof(ownerNameToChange));

		vector<CarRecord> recordsToChange;

		if (isOwnerNameExists("car_records.txt", ownerNameToChange, recordsToChange)) {
			cout << YELLOW_TEXT << "������� ��������� ���������� � ��� ��������� '" << ownerNameToChange << "':\n" << RESET_COLOR;

			for (const auto& record : recordsToChange) {
				cout << YELLOW_TEXT << "�����: " << record.brand << ", �����: " << record.carNumber << RESET_COLOR << endl;
			}

			while (true) {
				cout << YELLOW_TEXT << "������� ����� ����������, ������� �� ������ ��������: " << RESET_COLOR;
				cin.getline(newCarNumber, sizeof(newCarNumber));

				if (isValidCarNumber(newCarNumber)) {
					bool found = false;
					for (const auto& record : recordsToChange) {
						if (strcmp(record.carNumber, newCarNumber) == 0) {
							found = true;
							break;
						}
					}

					if (found) {
						break;
					}
					else {
						cout << RED_TEXT << "���������� � ������� " << newCarNumber << " �� ������. ����������, ������� �����." << RESET_COLOR << endl;
					}
				}
				else {
					cout << RED_TEXT << "������������ ������ ������ ������. ����������, ������� �����. ������: �111��11" << RESET_COLOR << endl;
				}
			}

			for (const auto& record : recordsToChange) {
				if (strcmp(record.carNumber, newCarNumber) == 0) {
					cout << YELLOW_TEXT << "������� ����� ����� ����������: " << RESET_COLOR;
					cin.getline(newBrand, sizeof(newBrand));

					while (true) {
						cout << YELLOW_TEXT << "������� ����� ����� ���������� (����������� ��������� ����� �������� ��������): " << RESET_COLOR;
						cin.getline(newCarNumber2, sizeof(newCarNumber2));

						if (isValidCarNumber(newCarNumber2)) {
							break;
						}
						else {
							cout << RED_TEXT << "������������ ������ ������ ������. ����������, ������� �����. ������: �111��11" << RESET_COLOR << endl;
						}
					}

					cout << YELLOW_TEXT << "������� ����� ����� ������ (�^3): " << RESET_COLOR;
					cin >> newTechSpec1;

					cout << YELLOW_TEXT << "������� ����� ����������� ����� � ������ (��): " << RESET_COLOR;
					cin >> newTechSpec2;

					cout << YELLOW_TEXT << "������� ����� ����������� ����� ��� ����� (��): " << RESET_COLOR;
					cin >> newTechSpec3;

					changeRecordByCarNumber("car_records.txt", newCarNumber, newBrand,
						newCarNumber, newTechSpec1, newTechSpec2, newTechSpec3, newCarNumber2);
					break;
				}
			}

			break;
		}
		else {
			cout << RED_TEXT << "��� ��������� " << ownerNameToChange << " �� ������� � �����." << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "������ ����������� ������ ���?" << endl;
			cout << "1 - ��\n"
				<< "2 - ���\n"
				<< "�����... \n� " << RESET_COLOR;
			int tryAgain;
			cin >> tryAgain;

			if (tryAgain != 1) {
				break;
			}

			cin.ignore();
		}

	} while (true);
}

//------------------------------------------------------------------------------

bool isCarNumberExists(const char* filename, const char* newCarNumber) {
	ifstream inFile(filename, ios::binary);

	if (!inFile.is_open()) {
		cerr << RED_TEXT << "������ �������� �����." << RESET_COLOR << endl;
		return false;
	}

	CarRecord currentRecord;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		if (strcmp(currentRecord.carNumber, newCarNumber) == 0) {
			inFile.close();
			return true; // ����� ���������� ������
		}
	}

	inFile.close();
	return false; // ����� ���������� �� ������
}

void deleteRecordByCarNumber(const char* filename, const char* carNumberToDelete) {
	ifstream inFile(filename, ios::binary);
	ofstream outFile("temp.txt", ios::binary);

	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << RED_TEXT << "������ �������� ������." << RESET_COLOR << endl;
		return;
	}

	CarRecord currentRecord;

	while (inFile.read(reinterpret_cast<char*>(&currentRecord), sizeof(CarRecord))) {
		if (strcmp(currentRecord.carNumber, carNumberToDelete) != 0) {
			outFile.write(reinterpret_cast<const char*>(&currentRecord), sizeof(CarRecord));
		}
	}

	inFile.close();
	outFile.close();

	remove(filename);
	rename("temp.txt", filename);

	cout << GREEN_TEXT << "������ � ������� ���������� " << carNumberToDelete << " ������� ������� �� �����." << RESET_COLOR << endl;
}

void delInfo() {
	char carNumberToDelete[20];
	do {

		while (true) {
			cout << YELLOW_TEXT << "������� ����� ���������� ��� �������� ������ (����������� ��������� ����� �������� ��������): " << RESET_COLOR;
			cin.getline(carNumberToDelete, sizeof(carNumberToDelete));

			if (isValidCarNumber(carNumberToDelete)) {
				break;
			}
			else {
				cout << RED_TEXT << "������������ ������ ������ ������. ����������, ������� �����. ������: �111��11" << RESET_COLOR << endl;
			}
		}

		if (isCarNumberExists("car_records.txt", carNumberToDelete)) {
			cout << YELLOW_TEXT << "�� �������, ��� ������ ������� ������ � ������� " << carNumberToDelete << "?" << endl;
			cout << "1 - ��\n"
				<< "2 - ���\n"
				<< "�����... \n� " << RESET_COLOR;
			int confirmation;
			cin >> confirmation;

			if (confirmation == 1) {
				cin.ignore();
				deleteRecordByCarNumber("car_records.txt", carNumberToDelete);
			}
			else {
				cout << GREEN_TEXT << "�������� ��������." << RESET_COLOR << endl;
			}

			break;
		}
		else {
			cout << RED_TEXT << "������ � ������� " << carNumberToDelete << " �� ������� � �����." << RESET_COLOR << endl;
			cout << YELLOW_TEXT << "������ ����������� ������ �����?" << endl;
			cout << "1 - ��\n"
				<< "2 - ���\n"
				<< "�����... \n� " << RESET_COLOR;
			int tryAgain;
			cin >> tryAgain;

			if (tryAgain != 1) {
				break;
			}

			cin.ignore();
		}

	} while (true);
}


//-------------------------------------------------------------------------

void addRecordToFile(const char* filename, const CarRecord& record) {
	ofstream outFile(filename, ios::binary | ios::app);

	if (!outFile.is_open()) {
		cerr << RED_TEXT << "������ �������� ����� ��� ���������� ������." << RESET_COLOR << endl;
		return;
	}

	outFile.write(reinterpret_cast<const char*>(&record), sizeof(CarRecord));

	outFile.close();
}


void addInfo() {
	CarRecord newRecord;
	cin.ignore();

	cout << YELLOW_TEXT << "������� ����� ����������: " << RESET_COLOR;
	cin.getline(newRecord.brand, sizeof(newRecord.brand));

	while (true) {
		cout << YELLOW_TEXT << "������� ����� ���������� (����������� ��������� ����� �������� ��������): " << RESET_COLOR;
		cin.getline(newRecord.carNumber, sizeof(newRecord.carNumber));

		if (isValidCarNumber(newRecord.carNumber)) {
			break;
		}
		else {
			cout << RED_TEXT << "������������ ������ ������ ������. ����������, ������� �����. ������: �111��11" << RESET_COLOR << endl;
		}
	}

	cout << YELLOW_TEXT << "������� ��� ���������(������: �������.�.): " << RESET_COLOR;
	cin.getline(newRecord.ownerName, sizeof(newRecord.ownerName));

	cout << YELLOW_TEXT << "������� ����� ������ (�^3): " << RESET_COLOR;
	cin >> newRecord.techSpec1;

	cout << YELLOW_TEXT << "������� ����������� ����� � ������ (��): " << RESET_COLOR;
	cin >> newRecord.techSpec2;

	cout << YELLOW_TEXT << "������� ����������� ����� ��� ����� (��): " << RESET_COLOR;
	cin >> newRecord.techSpec3;

	addRecordToFile("car_records.txt", newRecord);

	cout << GREEN_TEXT << "������ ������� ��������� � ����." << RESET_COLOR << endl;
}


//--------------------------------------------------------------------------------------------------------------------



