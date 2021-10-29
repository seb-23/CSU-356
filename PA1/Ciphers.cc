#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <bitset>


using namespace std;


int main(int argc, char *argv[]) {
	
	// Set-Up

	if (argc != 6) {
		cerr << "Program: " << argv[0] << "\nError: You must enter 5 arguments and nothing more or less.\n" << endl;
		exit(1);
	}

	if (strcmp(argv[1],"B") && strcmp(argv[1],"S")) {
		cerr << "Program: " << argv[0] << "\nError: You must enter B or S as a fist argument.\n" << endl;
		exit(1);
	}
	
	if (strcmp(argv[5],"E") && strcmp(argv[5],"D")) {
		cerr << "Program: " << argv[0] << "\nError: You must enter E or D as a fist argument.\n" << endl;
		exit(1);
	}
	
	string keyfile(argv[4]);
	string filename(argv[2]);
	string file(argv[3]);
	
    ifstream key(keyfile);
    ifstream in(filename);
    ofstream out(file);
    
	if (!key) {
		throw runtime_error("Unable to open file: " + keyfile);
	}
	if (!in) {
		throw runtime_error("Unable to open file: " + filename);
	}
	if (!out.is_open()){
		throw runtime_error("Unable to open file: " + file);
	}
	
	string k;
	getline(key,k);
	key.close();
	
	
	
	
	
	// Stream Cipher
	
	int length = k.length();
	if (strcmp(argv[1],"S") == 0) {
		string s = "";
		int i = 0;
		char c;
		while (in.get(c)) {
			if (i >= length) {
				i = 0;
			}

			char E = c ^ k[i];
			s += E;
			i++;
			if (in.peek() == EOF) {
				break;
			}
		}
		out << s;
	}
	
	
	
	
	// Encrypt Block Cipher                                              pad(if required)->encrypt(using XOR)->swap
	
	if (strcmp(argv[5],"E") == 0 && strcmp(argv[1],"B") == 0) {
		string s = "";
		int i = 0;
		char c;
		while (in.get(c)) {
			if (i >= 16) {
				i = 0;
			}
			
			char E = c ^ k[i];
			s += E;
			i++;
			
			if (in.peek() == EOF) {
				break;
			}
		}
		for (; i<16; i++) {
			unsigned char pad = 129;
			char E = pad ^ k[i];
			s += E;
		}
		auto start = s.begin();
		auto end = s.end();
		end--;
		int j = 0;
		while (start != end) {
			if (j>=16) {
				j = 0;
			}
			if (k[j]%2) {
				char tmp = *end;
				*end = *start;
				*start = tmp;
				end--;
			}
			if (start == end) {
				break;
			}
			start++;
			j++;
		}
		for (auto it = s.begin(); it != s.end(); ++it) {
			out << *it;
		}
	}
	
	
	
	
	
	// Decrypt Bock Cipher                                               swap->decrypt(using XOR)->remove padding(if required)
	
	if (strcmp(argv[5],"D") == 0 && strcmp(argv[1],"B") == 0) {
		string s = "";
		char c;
		while (in.get(c)) {
			s += c;
			if (in.peek() == EOF) {
				break;
			}
		}
		auto start = s.begin();
		auto end = s.end();
		end--;
		int j = 0;
		
		while (start != end) {
			if (j >= 16) {
				j = 0;
			}
			if (k[j]%2) {
				char tmp = *end;
				*end = *start;
				*start = tmp;
				end--;
			}
			if (end == start) {
				break;
			}
			
			start++;
			j++;
		}
		int i = 0;
		for (auto it = s.begin(); it != s.end(); ++it) {
			if (i >= 16) {
				i = 0;
			}
			char E = *it ^ k[i];
			*it = E;
			i++;
		}
		auto r = s.end();
		r--;
		for (; r!=s.begin(); --r) {
			if (*r > 0) {
				break;
			}
			s.pop_back();
		}
		out << s;
	}
	
	
	in.close();
	out.close();
	
	return 0;
}
