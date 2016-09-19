//Lab Term Project, Write a Final Version of DvcSchedule
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
  cout << "Lab Term Project, Write a Final Version of DvcSchedule" << endl;
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
  cout << "    ::SUPAR KAWAII DATABASE::\n\n";

  char* token;
  char buf[1000];
  const char* const tab = "\t";
  
  map<string, map<string, int> > subCode;
  set<string> dubs;
  
  ifstream fin;
  clock_t startTime = clock();
  cout << "loading"; //beginning to loading dot
  
  fin.open("dvc-schedule.txt");
  if (!fin.good())
  {
    cout << "\n\nNani! The file's not even there. Nande?!?" << endl; 
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
    {
      if (subCode.count(subjectCode))
      {
        if (subCode[subjectCode].count(course))
          subCode[subjectCode][course]++;
        else
          subCode[subjectCode][course] = 1;
      }
      else
      {
        map<string, int> newCourse;
        newCourse[course] = 1;
        subCode[subjectCode] = newCourse;
     } }
    else
      dubsCheckEm++;
      
    lineNum++;
  }
  fin.close();
  cout << endl << endl; //for loading dots
   
  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;      

  map<string, map<string, int> >::iterator it;
  map<string, int>::iterator itchan;
  
  cout << " Subject| #of courses\n";
  cout << "-----------------------------\n";
  cout.setf(ios::left,ios::adjustfield);
  for (it = subCode.begin(); it != subCode.end(); it++)
  {
    if ((*it).second.size() == 1)
      cout << "  " << setw(5) << (*it).first << "  " << (*it).second.size() << " course" << endl;
    else
      cout << "  " << setw(5) << (*it).first << "  " << (*it).second.size() << " courses" << endl;
    
    for (itchan = (*it).second.begin(); itchan != (*it).second.end(); itchan++)
    {
      if ((*itchan).second == 1)
        cout << "    " << setw(11) << (*itchan).first << "  " << setw(2) << (*itchan).second << " class" << endl;
      else
        cout << "    " << setw(11) << (*itchan).first << "  " << setw(2) << (*itchan).second << " classes" << endl;
    }
    cout << endl;
  }
  
  cout << "\nSubject count: " << subCode.size() << endl;
  cout << "Duplicate course count: " << dubsCheckEm << endl;
  cout.setf(ios::fixed|ios::showpoint);
  cout << "Program's runtime: " << setprecision(4) << elapsedSeconds << endl;
  cout << endl;
}