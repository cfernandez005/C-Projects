//Lab 13, Write a Customer Service Simulation
//Chris Fernandez
//Editor: Notepad++
//Compiler: g++

#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
#include <iostream>
using namespace std;

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>

void titleLines()
{
  cout << "Lab 13, Write a Customer Service Simulation" << endl;
  cout << "Author: Chris Fernandez" << endl;
  cout << "Editor: Notepad++" << endl;
  cout << "Compiler: g++" << endl;
  cout << "File: " << __FILE__<< endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl;
  cout << endl << endl;
}

struct customer
{
  int arival;
  int service;
  int completion;
  char ID;
};

struct event
{
  int clockTime;
  int serverNum;
  
  bool operator<(const event& e) const
  {
    return clockTime > e.clockTime;
  }
};

int getRandomNumberOfServiceRequests(double);

int main()
{
  titleLines();
  srand(time(0));
  rand();
  char buf[21];
  
  ifstream fin;
  fin.open("simulation.txt");
  if (!fin.good())
  {
    cout << "  Say what now? Yea, that file couldn't be found..opened..something" << endl;
    throw "I/O error";
  }
  
  int lineNum = 0;
  int serverNum;
  double avgArival;
  int maxWait;
  int minSer;
  int maxSer;
  int arivalStop;
  
  while (fin.good())
  {
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    
    if (lineNum == 0)
      serverNum = atoi(buf);
    if (lineNum == 1)
      avgArival = atof(buf);
    if (lineNum == 2)
      maxWait = atoi(buf);
    if (lineNum == 3)
      minSer = atoi(buf);
    if (lineNum == 4)
      maxSer = atoi(buf);
    if (lineNum == 5)
      arivalStop = atoi(buf);
    
    lineNum++;
  }
fin.close();

cout << "     Given File Data\n";
cout << "--------------------------\n";
cout << "Number of Servers: "<< serverNum << endl;
cout << "Customer arival rate: " << avgArival << endl;
cout << "Wait list capacity: " << maxWait << endl;
cout << "Minimum service wait: " << minSer << endl;
cout << "Maximum service wait: " << maxSer << endl;
cout << "Closing time: " << arivalStop << endl;
cout << "--------------------------\n\n";

  queue<customer> cQ;
  priority_queue<event> e;
  stack<customer> cS;
  int turnedAway = 0;
  
  customer* serverArray;
  serverArray = new customer[serverNum];
  bool* busyArray;
  busyArray = new bool[serverNum];
  
  for (int i = 0; i < serverNum; i++)
    busyArray[i] = false;
  
  int customerCount = 0;
  for (int time = 0;; time++)
  {
    if (!e.empty())
      while (e.top().clockTime == time)
      {
        int server = e.top().serverNum;
        e.pop();
        serverArray[server].completion = time;
        cS.push(serverArray[server]);
        busyArray[server] = false;
      }
    
    if (time < arivalStop)
    {
      int arivalNum = getRandomNumberOfServiceRequests(avgArival);
      for (int i = 0; i < arivalNum; i++)
      {
        if ( cQ.size() >= maxWait)
          turnedAway++;
        else
        {
          customer newPerson;
          newPerson.arival = time;
          newPerson.service = 0;
          newPerson.completion = 0;
          newPerson.ID = (char)('A' + (customerCount++ % 26));
          cQ.push(newPerson);
    } } }  
      
    for (int i = 0; i < serverNum; i++) 
      if (busyArray[i] == false && !cQ.empty())
      {
        serverArray[i] = cQ.front();
        cQ.pop();
        serverArray[i].service = time;
        busyArray[i] = true;
        event newService;
        int serviceTimeInterval = rand() % (maxSer -minSer) +minSer;
        newService.clockTime = time + serviceTimeInterval;
        newService.serverNum = i;
        e.push(newService);
      }
    
    queue<customer> temp = cQ;
    cout << "   Time: " << time << endl;
    cout << "   -----------------------------\n";
    cout << "   line  now serving  wait queue\n";
    cout << "   ----  -----------  -------------\n";
    cout.setf(ios::left, ios::adjustfield);
    for (int i = 0; i < serverNum; i++)
    {
      cout << "    " << setw(3) << i;
      if (busyArray[i] == true)
        cout << "         " << serverArray[i].ID;
      else
        cout << "          ";
      cout << "       ";
      while(!temp.empty())
      {
        cout << temp.front().ID;
        temp.pop();
      }  
      cout << endl;
    } 
    
    stack<customer> iterator = cS;
    int allArives = 0;
    int allCompletes = 0;
    int count = 0;
    while (!iterator.empty())
    {
      allArives += iterator.top().arival;
      allCompletes += iterator.top().completion;
      count++;
      iterator.pop();
    }
    
    cout.setf(ios::fixed|ios::showpoint);
    if (count == 0)
      cout << "   Average Customer Time: 0\n";
    else
    {
    double ariveToCompleteAverage = ((double)allCompletes /count) -((double)allArives/count);
    cout << "   Average Customer Time: " << setprecision(3) << ariveToCompleteAverage << endl;
    }
    
    double turnedAwayRate = ((double)turnedAway/time);
    if (time == 0 || turnedAwayRate == 0)
      cout << "   Rate of Rejection: 0\n\n";
    else
    {
    double turnedAwayRate = ((double)turnedAway/time);
    cout << "   Rate of Rejection: " << setprecision(3) << turnedAwayRate << endl << endl;
    }
    
    cout << "Enter any key to continue or X to quit: ";
    cin.getline(buf, 21);
    if (buf[0] == 'x' || buf[0] == 'X')
      break;
    cout << endl << endl;
  }
  
  cout << "\n\n   ...well then, we're done here" << endl;
  delete [] serverArray;
  delete [] busyArray;
}


int getRandomNumberOfServiceRequests(double averageRequestsPerTimeStep)
{
  int requests = 0;
  double probOfnRequests = exp(-averageRequestsPerTimeStep);
  for (double randomValue = (double)rand() / RAND_MAX; 
    (randomValue -= probOfnRequests) > 0.0; 
    probOfnRequests *= averageRequestsPerTimeStep / (double)++requests);
  return requests;
}