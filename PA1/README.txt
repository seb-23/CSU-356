So the purpose of this program is to use Stream and Block Ciphers to 
encrypt and/or decrypt sensitive data. 

Ciphers.cc 
contains the necessary tools to convert plaintext to ciphertext and vice
versa using a stream or block cipher.

The program requires 5 arguments to run properly.
1st argument: 'B' or 'S'    (Block or Stream)
2nd argument: Input Filename
3rd argument: Output Filename
4th argument: Keyfile       (Contains Symmetric Key)
5th argument: 'E' or 'D'    (Encryption or Decryption)

In Terminal Run:
1st command: cmake . && make
2nd command: ./ciphers (then some arguments)
example: ./ciphers B input output keyfile E

The Keyfile provided has the following symmetric key:
COMPUTER76543210

The following files are needed to run the program:
Ciphers.cc
CMakeLists.txt
README.txt
keyfile

















Here Are Some Extra Notes I Jotted Down For the Purposes of Creating 
The Assingment. Read Them If You Find Them Useful:

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
