/*
Kuloloia, Anthony 
ICS 212
11/22/14
Assignment 23
*/

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

//entry class
class Entry
{
protected:
  //data members
  string english;
  string japanese;
  string sortField;

public:
  //constructor
  Entry()
  {
    english = "";
    japanese = "";
    sortField = "";
  }

  //set functions
  void setEnglish(string e)
  {
    english = e;
  }
  
  void setJapanese(string j)
  {
    japanese = j;
  }

  void setSortField(string s)
  {
    sortField = s;
  }

  //get functions
  string getEnglish()
  {
    return english;
  }

  string getJapanese()
  {
    return japanese;
  }
  
  string getSortField()
  {
    return sortField;
  }

  friend bool operator<(const Entry e1, const Entry e2)
  {
    if(e1.sortField<e2.sortField)
      {
	return true;
      }
    else
      {
	return false;
      }
  }
};


int main(int commandlineArg, char *inputArg[])
{
  //variables
  char inputFile[20];
  string input;
  vector<Entry> eVect;
  Entry e;
  
   
  //checks if user entered input file into commandline argument
  if(commandlineArg<1)
    {
      cout<<"No file was entered"<<endl;
    }
  else
    {
      strcpy(inputFile, inputArg[1]);
      
      //uses ifstream class for file input
      ifstream fileInputStream(inputFile);
      
      //if it can't locate file or open it, the program will end
      if(fileInputStream==NULL)
	{
	  cout << "The file, " << inputFile << " does not exist in current directory or cannot be opened";
	  return 1;
	}
      
      //read in one line at a time
      while(!fileInputStream.eof())
	{
	  //store one line from fileInputStream to line
	  getline(fileInputStream, input);
         
	  //variable for english and japanese parts of input, number to use for substring, and length of input string
	  string eInput, jInput, sortF;
	  int splitStr = 0;
	  int length = 0;
	     
	  //finds tab in string and stores that position to splitStr
	  splitStr = input.find('\t');
	     
	  //store english portion to a variable
	  eInput = input.substr(0, splitStr);
	     
	  //add one to splitStr variable to omit \t character and store japanese part to variable
	  jInput = input.substr(splitStr+1);

	  //set sort field to english part and set all characters to lowercase
	  sortF = eInput;
	  transform(sortF.begin(), sortF.end(), sortF.begin(), ::tolower);   

	  //remove any characters enclosed in brackets
	  int beginB = sortF.find('[');
	  int endB = sortF.find(']');
	  if(beginB<0)
	    {
	    }
	  else
	    {
	      sortF.erase(beginB, endB+1);
	    }

	  //remove any characters enclosed in parenthesis
	  int beginP = sortF.find('(');
	  int endP = sortF.find(')');
	  if(beginP<0)
	    {
	    }
	  else
	    {
	      sortF.erase(beginP, (endP+1));
	      beginP = sortF.find_last_of('(');
	      endP = sortF.find_last_of(')');
	      if(beginP>0)
		{
		  sortF.erase(beginP, endP-beginP+1);
		}
	    }
	  
	  //remove any spaces in front of words
	  if(sortF[0] == ' ')
	    {
	      sortF = sortF.substr(1, sortF.length());
	    }
	  else
	    {
	    }
 
	  //set entry variables english, japanese, and sortfield parts
	  e.setEnglish(eInput);
	  e.setJapanese(jInput);
	  e.setSortField(sortF);
	  
	  //push onto vector
	  eVect.insert(eVect.begin(), e);

	  sort(eVect.begin(), eVect.end());
	  
	}//end of while loop


      //print vector
      for(int i = 0; i<eVect.size();i++)
	{
	  cout<<setiosflags(ios::left);
	  cout<<setw(40)<<eVect[i].getEnglish();
	  cout<<"\t";
	  cout<<setw(40)<<eVect[i].getJapanese()<<endl;
	}

      return 0;
    }
}
   

