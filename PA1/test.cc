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
	

	
	// this will just be a symmetric key, likely just one line of characters 
	string keyfile(argv[4]);
	string filename(argv[2]);
	string file(argv[3]);
	
    ifstream key(keyfile);
    ifstream in(filename);
    //ofstream tmp("tmp.txt");
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
	
	
	
	// Begin Coding
	// First Word = Sebastian 
	// Key = COMPUTER76543210
	// Compare: S XOR C => 16 => 00010000
	// whitespace = 32 = 00100000
	
	string k;
	getline(key,k);
	key.close();
	
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
		
		// keysize for Block Encryption Mode would be 128 bits (16 bytes) and can be of any length for Stream Encryption Mode
		
		cout << s << "\n";
		out << s;
	}
	
	if (strcmp(argv[5],"E") == 0 && strcmp(argv[1],"B") == 0) {
		string s = "";
		int i = 0;
		char c;
		while (in.get(c)) {
			if (i >= 16) {
				i = 0;
			}
			
			char E = c ^ k[i];
			if (i == 0) {
				cout << bitset<8>(E).to_string() << endl;
			}
			cout << "\n" << E << " " << c << " " << k[i] << " " << static_cast<int>(E) << "\n" ;
			s += E;
			i++;
			
			if (in.peek() == EOF) {
				break;
			}
			
		}
		cout << "\n\n" << s.length() << " " << static_cast<int>(s[0]) << "\n\n" ;
		
		auto start = s.begin();
		auto end = s.end();
		end--;
		cout << "\n\nHERE:" << static_cast<int>(*start) << " | " << static_cast<int>(*end) << " END\n\n" ;
		cout << "\n\nHERE:" << *start%2 << " | " << *end%2 << " END\n\n" ;
		cout << s << "\n";
		/*
		16 89
		42 89
		47 89
		49 51
		38 44
		32 44
		44 44
		Exit
		*/
		
		// keysize for Block Encryption Mode would be 128 bits (16 bytes) and can be of any length for Stream Encryption Mode
		
		//int j = 0;
		while (start != end) {
			/*
			if (j > 0) {
				out << " ";
			}
			*/
			cout << "\n" << static_cast<int>(*start) << " " << static_cast<int>(*end) << "\n";
			if (*start%2) {
				char tmp = *end;
				*end = *start;
				*start = tmp;
				end--;
			}
			
			//out << bitset<8>(*start).to_string();
			out << *start;
			start++;
			//j++;
		}

		for (auto it = start; it != s.end(); ++it) {
			//out << " " << bitset<8>(*it).to_string();
			out << *it;
		}
		/*
		if (i != 0 && i != 16) {
			for (;i < 16; i++) {
				//out << " " << hex << showbase << 129;
				//out << " " << bitset<8>(129).to_string();
			}
		}
		*/
		cout << s << "\n";
	}
	
	// Decrypt Bock Cipher
	// swap->decrypt(using XOR)->remove padding(if required)
	
	if (strcmp(argv[5],"D") == 0 && strcmp(argv[1],"B") == 0) {
		string s = "";
		char c;
		while (in.get(c)) {
			s += c;
			if (in.peek() == EOF) {
				break;
			}
		}

		cout << "\n\nTHERE BITCH\n" << s << "\n\n";
		
		auto start = s.begin();
		auto end = s.end();
		end--;
		while (start != end) {
			cout << "\n\n" << static_cast<int>(*start) << " " << *start << " " << static_cast<int>(*end) << " " << *end;
			if (*start%2) {
				char tmp = *end;
				*end = *start;
				*start = tmp;
				end--;
			}
			if (end == start) {
				break;
			}
			start++;
		}
		
		/*
		16 42 47 49 38 32 44 51 89
		    *  /  1  &     ,  3  Y
		
		16 89  
		42 89
		47 89
		49 51
		38 44
		32 44
		44 44
		
		16 42 89 51 38 32 44 49 47
		    *  Y  3  &     ,  1  /
		
		
		
		
		
		Exit
		*/
		
		/*
		while (start != end) {
			if (*end%2) {
				char tmp = *end;
				*end = *start;
				*start = tmp;
				start++;
			}
			end--;
		}
		*/
		//Missing Code
		cout << "\n\nHERE BITCH\n" << s << "\n\n";
		int i = 0;
		for (auto it = s.begin(); it != s.end(); ++it) {
			if (i >= 16) {
				i = 0;
			}
			char E = *it ^ k[i];
			out << E;
			i++;
		}
		cout << s << "\n";
	}
	
	
	
	in.close();
	out.close();
	
	
	return 0;
}


// Input File is in multiples of 8 bits
// Input File is in ASCII (0-127) range

// Output File must be in 128-bit blocks in block mode
// This means you must pad blocks that are not 128 bits in length
// Each padding byte should be 0X81
// Padding can be done in multiples of 8 bits or 1 byte
// You will be using the byte value 0x81 in hex or 129 in decimal
// 0X81 falls outside the ASCII range and allows us to distinguish padding
// bytes from plaintext bytes.

// Output File must be in 8 bit multiples in stream mode
// If the Input File is empty, the Output File should be empty



// Description of the Algorithms

// Block Cipher
// This encrypts the data
// Encryption (3 Step Process): pad(if required)->encrypt(using XOR)->swap

// Swap:
// Will use pointers to navigate through the bytes
// Start and End Pointers
// Start from LeftMost byte then calculate the following : 
// (ASCII value of the byte or character)mod2
// This would give you either 0 or 1.

   // If the value is 0 you do not swap anything and move to the next byte of the ciphertext by incrementing the 'start' pointer.

   // If the value is 1 you swap the byte pointed by the 'start' pointer with that pointed by the 'end' pointer.
   // Then increment the 'start' pointer to the next byte (8-bits).
   // Then decrement the 'end' pointer to the next lower byte (8-bits).
   
// If the keysize is exhausted, you restart from the first byte of the key.
// This process is carried on until the 'start' and the 'end' pointers collide. 
// The swap process stops and produces the required encrypted output.

// Decryption: Will occur in the reverse order.
// swap->decrypt(using XOR)->remove padding(if required)

// Block Size = 128 bits (must be padded with 0X81 if not)
// 0x81 = 129 = 10000001 



// Stream Cipher
// XOR data with "COMPUTER76543210"
// LetMost Bit of the First Byte is = 0
// Decryption and Encryption use the same process!



// Key = "COMPUTER76543210"

// "COMPUTER"
// 01000011 01001111 01001101 01010000 01010101 01010100 01000101 01010010 

// "76543210"
// 00110111 00110110 00110101 00110100 00110011 00110010 00110001 00110000

// Each ASCII value is 8 bits or 1 byte long
// Each KEY is 16 bytes long
// Bit Values: 128 64 32 16 8 4 2 1 
