//Lab Term Project part2, Cross-listed Courses
//Chris Fernandez
//Editor: Notepad++
//Compiler: g++

#include <fstream>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <iostream>
using namespace std;

#include <ctime>
#include <cstring>

void titleLines()
{
  cout << "Lab Term Project part2, Cross-listed Courses" << endl;
  cout << "Author: Chris Fernandez" << endl;
  cout << "Editor: Notepad++" << endl;
  cout << "Compiler: g++" << endl;
  cout << "File: " << __FILE__<< endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl;
  cout << endl << endl;
}

int main()
{
  titleLines();
  cout << "             Ok, this is getting ridiculous.\n  Not ONLY are there dulpicate entries in this database,\n";
  cout << "    but now there are cross-listed courses as well...\n              WHO'S RUNNING THIS TXT FILE!?!\n\n";

  char* token;
  char buf[1000];
  const char* const tab = "\t";
  
  map<string, string> crossList1;
  map<string, string> crossList2;
  set<string> dubs;
  
  ifstream fin;
  clock_t startTime = clock();
  cout << "loading"; //beginning to loading dot
  
  fin.open("dvc-schedule.txt");
  if (!fin.good())
  {
    cout << "\n\nNani! The file's not even there. Nande Onii-Chaaaaaaaaaaaaaaaaaaaan?!?" << endl; 
    throw "I/O error";
  }  

  int dubsCheckEm = 0;
  int lineNum = 0;
  while (fin.good())
  {
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue;
    
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue;
    const string subjectCode(course.begin(), course.begin() + course.find('-'));
    
    if (lineNum % 1000 == 0)  //loading dots
      cout << '.' << flush;
    
    if (dubs.insert(term+section).second)
      crossList1.insert(pair<string, string>(term+" "+section, course));
    else
      dubsCheckEm++;
    
    if(crossList1[term+" "+section] != course)
      crossList2.insert(pair<string, string>(term+" "+section, course));
      
    lineNum++;
  }
  fin.close();
  cout << endl << endl << endl; //for loading dots
   
  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;      

  map<string, string >::iterator it1;
  map<string, string>::iterator it2;
  
  cout << "The following courses share a cross-listed section\n";
  cout << "  number for the same term aaaaaaand shouldn't be\n";
  cout << "---------------------------------------------------\n";
  for (it1 = crossList1.begin(); it1 != crossList1.end(); it1++)
    for (it2 = crossList2.begin(); it2 != crossList2.end(); it2++)
      if ((*it1).first == (*it2).first)
      {
        cout << "    Listing: " << (*it1).second << " " << (*it1).first << endl;
        cout << "      Matches: " << (*it2).second << " " << (*it2).first << endl << endl;
      }

  cout << "Duplicate course count: " << dubsCheckEm << endl;
  cout.setf(ios::fixed|ios::showpoint);
  cout << "Program's runtime: " << setprecision(4) << elapsedSeconds << endl;
}
