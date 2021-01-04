#pragma once
#include <string>
#include <Windows.h>
using namespace std;

struct Data {
	string site;
	string login;
	string password;
};

string GetConfig();
void NewConfig();
void ReadingData(Data* (&d), int& n); 
void SavingData(Data* (&d), int& n); 
void Start(Data* (&d), int& n);
void MasterChange(Data* (&d), int& n);
void Buffer(Data* (&d), int& n);
void AddData(Data* (&d), int& n); 
void ChangeLogin(Data* (&d), int& n);
void ChangePassword(Data* (&d), int& n);
void CheckPassword(Data* (&d), int& n); 
void CheckSites(Data* (&d), int& n);
void CheckLogins(Data* (&d), int& n);
void DeletePassword(Data* (&d), int& n); 
void DeleteAll(Data* (&d), int& n); 
void Copy(Data* (&d_new), Data* (&d_old), int& n);
void CopyEl(Data& d_new, Data& d_old);
void Sorting(Data* (&d), int& n);
string myhash(Data* (&d), string argument, int a);
string mydehash(Data* (&d), string argument, int a);
