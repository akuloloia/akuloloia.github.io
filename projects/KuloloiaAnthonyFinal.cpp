/*
Kuloloia, Anthony 
ICS 212
11/29/14
Final project
*/

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

#define MAX_SIZE 1048576
#define DIGEST_INTS 5

//SHA class
class SHA1
{
  //data members
protected:
  unsigned int fileSize;
  unsigned char iBuffer[MAX_SIZE];
  unsigned int blockCount;
  unsigned int message[MAX_SIZE];

public:
  //read data from input file
  unsigned int readFile(unsigned char buffer[], char inputFile[])
  {
    //variables for function
    char c;
    int i1 = 0;
    int i2 = 0;
    iBuffer[MAX_SIZE];

    //checks size of file (in bytes)
    ifstream file(inputFile, ios::binary | ios::ate);
    fileSize = file.tellg();
    
    //opens file
    ifstream is(inputFile);
    
    //if the size of the file is smaller than 1 megabyte, it continues the program
    if(fileSize<=MAX_SIZE)
      {
	//loop through file to get single character input
	while(is.get(c))
	  {
	    buffer[i1] = c;
	    //stores to the buffer used for this class as well.
	    iBuffer[i1] = c;
	    i1++;
	  }      
	//close file
	is.close();
      
    
	/*checks array for correct character input
	cout << "Checking for correct characters in array..."<<endl;
	while(i2 < fileSize)
	  {
	    cout << buffer[i2];
	    i2++;
	  }
	cout<<endl<<endl;
	*/

	//appends 1 bit to the end of message (1 is used to represent the bit 0x80)
	c = 0x80;
	iBuffer[fileSize] = c;
      }

    //if file is too big, relay message
    else
      {
	cout<<"File exceeds size intended for use with this program."<<endl;
      }
    return fileSize;
  }

  //calculate block count
  unsigned int calculateBlocks(unsigned int sizeOfFileInBytes)
  {
    //calculate block count with this equation
    blockCount = ((((8 * sizeOfFileInBytes) + 1) + 1) / 512) + 1;
    
    //determines if the file needs an extra block
    if((((8 * sizeOfFileInBytes) + 1) %512) > (512 -64))
      {
	blockCount = blockCount + 1;
      }
    return blockCount;
  }

  //converts char array to one integer
  void convertCharArrayToIntArray(unsigned int sizeOfFileInBytes, unsigned int blockCount)
  {
    //variables
    int i = 0; //serves as an iterator for appending a packed integer into the message array
    int a = 0;
    unsigned int packed;
    int loop = 1;

    //pack characters into integer array
    a = 0;
    while(a < sizeOfFileInBytes+1)
      {
	if(a<4*loop)
	  {
	    //every 4th character taken in is packed together with the previous 3 integers and stored to a space in the message array
	    if(a==((4*loop)-1))
	      {
		packed = packed | iBuffer[a];
		message[i] = packed;
		i++;
		loop++;
		packed = 0;
	      }
	    //the first integer it reads will pass through this statement
	    else if(a == 0)
	      {
		packed = iBuffer[a];
		packed = packed << 8;
	      }
	    //if the hex value 0x80 is by itself, it is packed together with 6 other 0s and stored to the message array
	    else if(i == sizeOfFileInBytes/4 && iBuffer[a] == 0x80)
	      {
		packed = packed | iBuffer[a];
		packed = packed << 24;
		message[i] = packed;
		i++;
		loop++;
		packed = 0;
	      }
	    //if the above requirements are not met, the character taken in will use the following statement
	    else
	      {
		packed = packed | iBuffer[a];
		packed = packed <<8;
	      }
	  }
	a++;
      }

    //pad message with the integer 0 until it hits the second to the last space in array
    while(i<16*blockCount)
      {
	message[i] = 0;
	i++;
      }
  }
    

  //adds size of file to last index of block
  void addBitCountToLastBlock(unsigned int sizeOfFileInBytes, unsigned int blockCount)
  {
    //calculate size of file in bits (multiply bytes by 8)
    unsigned int sizeOfFileInBits = sizeOfFileInBytes * 8;
    
    //calculate index of last block ( multiply by 16 then subtract one)
    unsigned int indexOfEndOfLastBlock = (blockCount * 16) - 1;

    //add to message array
    message[indexOfEndOfLastBlock] = sizeOfFileInBits; 
  }

  //display message digest
  void computeMessageDigest(unsigned int blockCount)
  {
    //initialize variables
    unsigned int h[DIGEST_INTS];
    unsigned int t;  //used as iterator
    unsigned int temp;  //will be used as temporary word value
    unsigned int W[80];
    unsigned int A, B, C, D, E;
    unsigned int bCountIt = 0;
    int run = 0;

    //hash defined here
    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;
    h[4] = 0xc3d2e1f0;

    //constants defined here
    unsigned int K[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};

    //continue to run until all blocks are accounted for
   while(bCountIt<blockCount)
      {
	    //divide the message into 16 words
	    for(t=16*bCountIt;t<16*bCountIt+16; t++)
	      {
		W[run] = message[t];
		run++;
	      }
	    run = 0;
      

	//part b of document
	for(t = 16; t < 80; t++)
	  {
	    W[t] = cShift(1, W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
	  }
	
	//part c of document (set A, B, C, D, E to h0, h1, h2, h3, h4, h5 respectively)
	A = h[0];
        B = h[1];
        C = h[2];
        D = h[3];
        E = h[4];
	
	//implement functions from step d
	//first loop
	for(t = 0; t<20; t++)
	  {
	    temp = cShift(5,A) + ((B&C) | ((~B)&D)) + E + W[t] + K[0];
	    E = D;
	    D = C;
	    C = cShift(30, B);
	    B = A;
	    A = temp;
	  }
	
	//second loop
	for(t=20; t<40; t++)
	  {
	    temp = cShift(5,A) + (B^C^D) + E + W[t] + K[1];
	    E = D;
	    D = C;
	    C = cShift(30, B);
	    B = A;
	    A = temp;
	  }
	
	//third loop
	for(t=40; t<60; t++)
	  {
	    temp = cShift(5,A) + ((B&C) | (B&D) | (C&D)) + E + W[t] + K[2];
	    E = D;
	    D = C;
	    C = cShift(30, B);
	    B = A;
	    A = temp;
	  }
	
	//fourth loop
	for(t=60; t<80; t++)
	  {
	    temp = cShift(5,A) + (B^C^D) + E + W[t] + K[3];
	    E = D;
	    D = C;
	    C = cShift(30, B);
	    B = A;
	    A = temp;
	  }

	//display values for a, b , c ,d ,e
	cout<<"Hex values for A, B, C, D, E..."<<endl;
	cout<<hex<<A<< " " <<B<< " " << C << " " << D << " " << E<<endl;

	h[0] += A;
	h[1] += B;
	h[2] += C;
	h[3] += D;
	h[4] += E;
	
	//display message digest to user
	t = 0;
	cout<<"The message digest for block "<<bCountIt + 1<<" is..."<<endl;
	while(t<5)
	  {
	    cout<< hex << h[t] << " ";
	    t++;
	  }
	cout<<endl<<endl;

	//increment iterator
	bCountIt++;
      }
  }

  //circular shift(function needed for computing message digest
  unsigned int cShift(int n, unsigned int X)
  {
    unsigned int shift;
    shift = (X << n) ^ (X>>32-n);
    return shift;
  }

};



int main(int commandlineArg, char *inputArg[])
{

  //variables
  char input[MAX_SIZE];
  SHA1 s;
  unsigned char buffer[MAX_SIZE];
  unsigned int sizeOfFile;
  unsigned blockCount;
   
  cout<<"Enter the name of the input file: ";
  //gets c string
  cin.get(input,MAX_SIZE);
  
  //opens file
  ifstream is(input);
  
  //if file is present in the current directory, it continues the program
  if(is)
    {
      sizeOfFile = s.readFile(buffer, input);
      blockCount = s.calculateBlocks(sizeOfFile);
      s.convertCharArrayToIntArray(sizeOfFile, blockCount);
      s.addBitCountToLastBlock(sizeOfFile, blockCount);
      s.computeMessageDigest(blockCount);
    }
   
  //otherwise it will stop here
  else
    {
      cout<<"Error opening " << input << "." << endl;
    }
  
  
}
