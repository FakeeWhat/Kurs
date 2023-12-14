#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <functional>
#define GREEN_TEXT "\033[0;32m"
#define RED_TEXT     "\033[1;31m"
#define YELLOW_TEXT  "\033[1;33m"
#define BLUE_TEXT    "\033[1;34m"
#define RESET_COLOR  "\033[0m"
#define BROWN_TEXT     "\033[0;33m"

using namespace std;

struct CarRecord {
	char brand[100];
	char carNumber[20];
	char ownerName[100];
	int techSpec1;
	int techSpec2;
	int techSpec3;
};

string hashPassword(const string& password);

void createFileForOwner(const char* inputFilename, const char* outputFilename);

void addInfo();

void delInfo();

void changeInfo();

void displayBrandList(const char* filename);

void displayFileContent(const char* filename);

bool isValidCarNumber(const char* carNumber);

void changeRecordByCarNumber(const char* filename, const char* carNumberToChange, const char* newBrand, const char* newCarNumber, int newTechSpec1, int newTechSpec2, int newTechSpec3, const char* newCarNumber2);

bool isOwnerNameExists(const char* filename, const char* ownerName, vector<CarRecord>& records);

bool isCarNumberExists(const char* filename, const char* carNumber);

void deleteRecordByCarNumber(const char* filename, const char* carNumberToDelete);

void addRecordToFile(const char* filename, const CarRecord& record);

void password();

void Menu();
