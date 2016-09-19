//COMSC-165 Term Project
//Chris Fernandez
//Editor: Notepad++
//Compiler: g++

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::ios;

#include <iomanip>
using std::setw;

#include <algorithm>
using std::swap;

#include <fstream>
using std::fstream;

#include <cstdlib>
#include <cstring>
#include <cctype>

void titleLines()
{
  cout << "COMSC-165 Term Project" << endl;
  cout << "Author: Chris Fernandez" << endl;
  cout << "Editor: Notepad++" << endl;
  cout << "Compiler: g++" << endl;
  cout << endl << endl;
}

struct course
{
  char classTitle[11];
  char term[7];
  double unit;
  char grade;
  course* next;
};

void print(course*);
int numPrint(course*);
course* deleteH(course*, int);
course* sort(course*, int);
int sortUnit(course*, course*);
int sortGrade(course*, course*);
int sortDescription(course*, course*);
int sortTerm(course*, course*);
course* restoreList(course*);
void saveList(course*);


int main()
{
  titleLines();
  cout << "             ::Course Database 2013::\n\n";

  char buf[21];
  char choice;
  char restore;
  course* head = 0;
  course* tail = 0;
  
  cout << "Would you like to recall data from the\n   previous list? (Enter 'Y' for yes, 'N' for no): ";
  cin >> restore;
  cin.ignore(1000,'\n');
  cout << endl;
  while (restore != 'N' && restore != 'n')
  {
    if (restore == 'Y' || restore == 'y')
    {
      head = restoreList(head);
      
      course* p, *prev;
      for (p = head, prev = 0; p; prev = p, p = p->next);
      tail = prev;
      
      break;
    }
    else
    {
      cout << endl;
      cout << "   Excuse me MA'AM, but that isn't an option" << endl << endl << endl;
      cout << "To restore course data from previous lists (Enter Y)\n     To start fresh with a new list (Enter N):";
      cin >> restore;
      cout << endl;
    }    
  }
  
  print(head);
	cout << endl;
  
  
  while(true)
  {
    cout << "            Main Menu" << endl << endl;
    cout << "Would you like to," << endl;
    cout << "         (A) add a course" << endl;
    cout << "         (D) delete a course" << endl;
    cout << "         (S) resort the list" << endl;
    cout << "         (F) print the list" << endl;
    cout << "         (Q) quit" << endl;
    cout << "Enter the letter adjacent to your choice: ";
    cin >> choice;
	cin.ignore(1000,'\n');
	cout << endl;
  
	  if (choice == 'A' || choice == 'a')
	  {
	    course* n = new course;
	  
	    cout << endl;
        cout << "Enter a course (such as COMSC-165): ";
        cin.getline(n->classTitle, 11);
	    if (cin.fail())
	    {
	      cin.clear();
        cin.ignore(1000,'\n');	
      }
	  cout << endl;
	  
	  for (int i = 0; i < 11; i++)
        n->classTitle[i] = toupper(n->classTitle[i]);
		
	  
      cout << "Enter the term in which course occurred or is occurring\n   (examples FA2010, SP2009, or SU2011): ";
      cin.getline(n->term, 7);
	  if (cin.fail())
	  {
	      cin.clear();
        cin.ignore(1000,'\n');	
      }
	  cout << endl;
	  
      for (int i = 0; i < 7; i++)
        n->term[i] = toupper(n->term[i]);

  
      cout << "Enter the amount of units the course is worth: ";
      cin >> buf;
      n->unit = atof(buf);
      cout << endl;
  
      cout << "Enter the letter grade received for said course: ";
      cin >> n->grade;
      cin.ignore(1000,'\n');	
      while (n->grade != 'A' && n->grade != 'a' && n->grade != 'B' && n->grade != 'b'
           && n->grade != 'C'&& n->grade != 'c' && n->grade != 'D' && n->grade != 'd'
           && n->grade != 'F'&& n->grade != 'f' && n->grade != 'X'&& n->grade != 'x')
      {
	      cout << endl;
        cout << "Enter the LETTER grade received for said course\n          (A, B, C, D, F, or X(for in progress): ";
        cin >> n->grade;
      }
      n->grade = toupper(n->grade);
      cout << endl;
      
      
      course* p = 0, * prev = tail;
      
      n->next = 0;
      if (tail)
        tail->next = n;
      else
        head = n;
      tail = n;
      
      print(head);
      cout << endl;
	  }

    else if (choice == 'D' || choice == 'd')
    {
      while (true)
      {
        int kill; 
        int t = numPrint(head);
      
        cout << "Enter the number of the course you wish to delete\n(or enter the number '0' return to the main menu): ";
        cin >> buf;
        kill = atoi(buf);
        cout << endl << endl;
      
        if (kill > 0 && kill < t)
        { 
          head = deleteH(head, kill);
        
          course* p = head;
          head = head->next;
          delete p;
          if (!head) 
            tail = 0;
               
          cout << "             Revised list";
          print(head);
        
          cout << "   Press any key to continue:";
          cin.get();
          cout << endl << endl << endl;  
          break;
        }
      
        if (kill >= t || kill < 0)
        {
          cout << "   What? That wasn't even on the list\n    Get out of my FACE with that!" << endl;
        }
        
        else
        {
          break;
          cout << endl << endl;
        }  
      }  
    }
	
    else if (choice == 'S' || choice == 's')
    {
      int resort;
      
      while (true)
      {
        cout << endl << endl;
        cout << "How would you like to resort the list?" << endl;
        cout << "   1. Course name, alphabetically" << endl;
        cout << "   2. Term, chronologically" << endl;
        cout << "   3. Units, least to greatest" << endl;
        cout << "   4. Grade, highest to lowest" << endl;
        cout << "   5. Pleasantly content, don't resort anything" << endl << endl;
        cout << "Enter the number of your deepest desire: ";
        cin >> buf;
        resort = atoi(buf);
        cout << endl;
      
        if (resort == 1 || resort == 2 || resort == 3 || resort == 4)
        {
          head = sort(head, resort);
          cout << endl;
          cout << "             Resorted list";
          print(head);
          
          cout << "   Press any key to continue:";
          cin.get();
          cout << endl << endl << endl;
          break;
        }
        else if (resort == 5)
        {
          cout << endl << endl;
          break;
        }  
        else
          cout << endl;
          cout << "   Well I'd love to, but that isn't an option" << endl;
      }    
    }
    
    else if (choice == 'F' || choice == 'f')
    {
      print(head);
      cout << "   Press any key to continue:";
      cin.get();
      cout << endl << endl << endl;
    }
    
    else if (choice == 'Q' || choice == 'q')
    {
      saveList(head);
      cout << endl;
      cout << "   Eh, you'll be back. They always come back..." << endl;
      break;
    }
    
    else
    {
      cout << endl;
      cout << "   That isn't an option, SIR!" << endl << endl << endl;
    }
  }
  
  while (head)
  { 
    course* next = head->next;
    delete head;
    head = next;
  }
}  


void print(course* h)
{
  cout << endl << endl;
  cout << "    Course      Term    Units   Grade\n";
  cout << "  ------------------------------------\n";
  cout.setf(ios::left, ios::adjustfield);
  for (course* i = h; i != 0; i = i->next)
  {
    cout << "   " << setw(12) << i->classTitle << setw(11) << i->term << setw(8) << i->unit << i->grade << endl;
  }
  cout << endl << endl;
}


int numPrint(course* h)
{
  int t = 1;
  cout << endl << endl;
  cout << "      Course      Term    Units   Grade\n";
  cout << "    ------------------------------------\n";
  cout.setf(ios::left, ios::adjustfield);
  for (course* i = h; i != 0; i = i->next, t++)
  {
    cout << "#" << setw(4) << t << setw(12) << i->classTitle << setw(11) << i->term << setw(8) << i->unit << i->grade << endl;
  }
  cout << endl << endl;
  return t;
}


course* deleteH(course* head, int kill)
{
  for (course* i = head; i; i = i->next)
    for (course* q = i->next; q; q = q->next)
      if (kill > 1)
      {
        char temp[11];
        strcpy(temp, i->classTitle);
        strcpy(i->classTitle, q->classTitle);
        strcpy(q->classTitle, temp);
            
        strcpy(temp, i->term);
        strcpy(i->term, q->term);
        strcpy(q->term, temp);
          
        swap(i->unit, q->unit);
        swap(i->grade, q->grade);
        kill--;
      }
  return head;      
}


course* sort(course* head, int n)
{
  if (n == 1)
  {
    for (course* i = head; i; i = i->next)
      for (course* q = i->next; q; q = q->next)
        if (sortDescription(q, i) < 0)
        {
          char temp[11];
          strcpy(temp, i->classTitle);
          strcpy(i->classTitle, q->classTitle);
          strcpy(q->classTitle, temp);
            
          strcpy(temp, i->term);
          strcpy(i->term, q->term);
          strcpy(q->term, temp);
          
          swap(i->unit, q->unit);
          swap(i->grade, q->grade);
        }
  }

  if (n == 2)
  {
    for (course* i = head; i; i = i->next)
      for (course* q = i->next; q; q = q->next)
        if (sortTerm(q, i) < 0)
        {
          char temp[11];
          strcpy(temp, i->classTitle);
          strcpy(i->classTitle, q->classTitle);
          strcpy(q->classTitle, temp);
            
          strcpy(temp, i->term);
          strcpy(i->term, q->term);
          strcpy(q->term, temp);
          
          swap(i->unit, q->unit);
          swap(i->grade, q->grade);
        }
  }

  if (n == 3)
  {
    for (course* i = head; i; i = i->next)
      for (course* q = i->next; q; q = q->next)
        if (sortUnit(q, i) < 0)
        {
          char temp[11];
          strcpy(temp, i->classTitle);
          strcpy(i->classTitle, q->classTitle);
          strcpy(q->classTitle, temp);
            
          strcpy(temp, i->term);
          strcpy(i->term, q->term);
          strcpy(q->term, temp);
          
          swap(i->unit, q->unit);
          swap(i->grade, q->grade);
        }
  }

  if (n == 4)
  {
    for (course* i = head; i; i = i->next)
      for (course* q = i->next; q; q = q->next)
        if (sortGrade(q, i) < 0)
        {
          char temp[11];
          strcpy(temp, i->classTitle);
          strcpy(i->classTitle, q->classTitle);
          strcpy(q->classTitle, temp);
            
          strcpy(temp, i->term);
          strcpy(i->term, q->term);
          strcpy(q->term, temp);
          
          swap(i->unit, q->unit);
          swap(i->grade, q->grade);
        }
  }
  return head;    
}


int sortDescription(course* a, course* b)
{
  if (strcmp(a->classTitle, b->classTitle) < 0)
    return -1;
  if (strcmp(a->classTitle, b->classTitle) > 0)
    return 1; 
  else
    return sortTerm(a, b);
}


int sortTerm(course* a, course* b)
{
  if (strcmp(a->term, b->term) == 0)
    return strcmp(a->classTitle, b->classTitle);
    
  int ayear = atoi(a->term + 2);
  int byear = atoi(b->term + 2);
  if (ayear < byear)
    return -1;
  if (ayear > byear)
    return 1;
  
  if (strncmp(a->term, "SP", 2) == 0)
    return -1;
  if (strncmp(a->term, "SU", 2) == 0)
    return strncmp(b->term, "SP", 2) ? -1:1;
  return 1;  
}


int sortUnit(course* a, course* b)
{
  if (a->unit < b->unit)
    return -1;
  if (a->unit > b->unit)
    return 1;
  else
    return strcmp(a->classTitle, b->classTitle);
}


int sortGrade(course* a, course* b)
{
  if (a->grade < b->grade)
    return -1;
  if (a->grade > b->grade)
    return 1; 
  else
    return strcmp(a->classTitle, b->classTitle);
}


course* restoreList(course* head)
{
  fstream fin;
  fin.open("courses.dat", ios::binary|ios::in);
  if (!fin)
  {
    cout << endl;
    cout << "   No previous list data could be found\n   ...soo...Moving On" << endl << endl;
    return head;
  }

  int records;
  fin.read((char*)&records, sizeof(int));

  course* newHead = head;
  for (int i = 0; i < records; i++)
  {
    course* t = new course;
    fin.read((char*)t, sizeof(course));
    
    course* p, *prev;
    for(p=newHead, prev=0; p; prev=p, p=p->next); 
	  t->next = p; 
    if (prev) 
      prev->next = t; 
    else 
      newHead = t; 
  }
  fin.close();
  return newHead;
}


void saveList(course* head)
{
  fstream fout;
  fout.open("courses.dat", ios::binary|ios::out);
 
  int records = 0;
  course* p;
  for (p = head; p; p = p->next)
    records++;
 
  fout.write((char*)&records, sizeof(int));
 
  for(p=head; p; p= p->next)
    fout.write((char*)p, sizeof(course));
  
  fout.close();
}