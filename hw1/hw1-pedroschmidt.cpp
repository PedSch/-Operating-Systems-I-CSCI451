#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unistd.h>


//Pedro Schmidt
//flag 
//to compile g++ hw1-pedroschmidt.cpp  -std=c++11
using namespace std;

int main()
{
   regex key("(.*)(Contact:)(.*)");
   //PART1
   system("wget -q http://www.senate.gov/general/contact_information/senators_cfm.cfm"); // downloads file "-q" quiet turns off wget output
   
   //PART2
   vector <string> senators;
   int count = 0;
   ifstream my_input_file("senate.input");        // an input file stream object, create and open 
	
   if (!my_input_file.is_open())                  //check if opening was successful
   {
    string line; 
    while (getline(my_input_file, line)) 
    {
     if(regex_match(line.begin(), line.end(), key)) 
      {
		getline(my_input_file, line);
      string temp = line;
		int pos = temp.find("\"");
		temp = temp.substr(pos + 1);
		pos = temp.find("\"");
		temp = temp.substr(0, pos);
				
		senators.push_back(temp);
		count++;
      }
   }
    my_input_file.close();
  }
 	
   for (int i = 0; i < senators.size(); i++) {
   cout << senators[i] << endl;
	}
    
   //PART3
   cout << "Done!" << count << endl;
   system("unlink senate");
   return 0;
}