#include "parsing.h"
#include <string>
#include <fstream>
using namespace std;

//не master (a==0) -> расшифровка мастер-паролем
//master (a==1) -> расшифровка кодовым словом

string myhash(Data* (&d), string argument, int a) { 
	string s_vvod = argument;
	string code;
	if (a == 0) { 
		string h_master = d[0].password; 
		code = mydehash(d, h_master, 1); 
	}
	else code = "travka"; 
	int j = 0, i = 0, v, flag = 0;
	int n1 = code.length();
	int n2 = s_vvod.length();
	int* int_code = new int[n1];
	for (int k = 0; k < n1; k++) {
		if (code[k] >= 'A' && code[k] <= 'Z')
			int_code[k] = (int)(code[k] - 'A');
		if (code[k] >= 'a' && code[k] <= 'z')
			int_code[k] = (int)(code[k] - 'a');
		if (code[k] >= '0' && code[k] <= '9')
			int_code[k] = (int)(code[k] - '0');
	}
	while (j < n1 && i < n2) {
		if (s_vvod[i] >= 'A' && s_vvod[i] <= 'Z' || s_vvod[i] >= 'a' && s_vvod[i] <= 'z') {
			v = s_vvod[i] + int_code[j];
			if (s_vvod[i] >= 'A' && s_vvod[i] <= 'Z')
				if (v > 90) v = v - 26;
			if (s_vvod[i] >= 'a' && s_vvod[i] <= 'z')
				if (v > 122) v = v - 26;
			j++;
		}
		else {
			v = s_vvod[i] + flag;
			while (v > 57) v = v - 10;
			flag++;
		}
		s_vvod[i] = static_cast<char>(v);
		if (j == n1) j = 0;
		i++;
	}
	return s_vvod;
}

string mydehash(Data* (&d), string argument, int a) {
	string s_vvod = argument; 
	string code;
	if (a == 0) {
		string h_master = d[0].password; 
		code = mydehash(d, h_master, 1); 
	}
	else code = "travka"; 
	int j = 0, i = 0, v, flag = 0;
	int n1 = code.length();
	int n2 = s_vvod.length();
	int* int_code = new int[n1];
	for (int k = 0; k < n1; k++) {
		if (code[k] >= 'A' && code[k] <= 'Z')
			int_code[k] = (int)(code[k] - 'A');
		if (code[k] >= 'a' && code[k] <= 'z')
			int_code[k] = (int)(code[k] - 'a');
		if (code[k] >= '0' && code[k] <= '9')
			int_code[k] = (int)(code[k] - '0');
	}
	while (j < n1 && i < n2) {
		if (s_vvod[i] >= 'A' && s_vvod[i] <= 'Z' || s_vvod[i] >= 'a' && s_vvod[i] <= 'z') {
			v = s_vvod[i] - int_code[j];
			if (s_vvod[i] >= 'A' && s_vvod[i] <= 'Z')
				while (v < 65) v = v + 26;
			if (s_vvod[i] >= 'a' && s_vvod[i] <= 'z')
				while (v < 97) v = v + 26;
			j++;
		}
		else {
			v = s_vvod[i] - flag;
			while (v < 48) v = v + 10;
			flag++;
		}
		s_vvod[i] = static_cast<char>(v);
		if (j == n1) j = 0;
		i++;
	}
	return s_vvod;
}