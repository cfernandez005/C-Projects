//Lab 15b, Write a Function for the Shortest Route
//Chris Fernandez
//Editor: Notepad++
//Compiler: g++

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#include <cstdlib>

void titleLines()
{
  cout << "Lab 15b, Write a Function for the Shortest Route" << endl;
  cout << "Author: Chris Fernandez" << endl;
  cout << "Editor: Notepad++" << endl;
  cout << "Compiler: g++" << endl;
  cout << "File: " << __FILE__<< endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl;
  cout << endl << endl;
}

struct Vertex
{
  string name;

  bool isVisited;
  list<pair<int, double> > adjacentVertices;
  int prev;
  double cost;
};

struct Container
{
  int vertex;
  int prev;
  double cost;

  bool operator<(const Container& v) const
  {
    return cost > v.cost;
  }
};

pair<stack<int>, double> getCheapestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
  pair<stack<int>, double> result;
  list<pair<int, double> >::iterator it; // to iterate over adjacentVertices
// TO DO -- write this function--------------------------------------------------------------------------------------------------
  for (int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
    database[i].prev = -1;
    database[i].cost = 0;
  }
  priority_queue<Container> pQueue;
  Container startVertex;
  startVertex.vertex = iStart;
  startVertex.prev = -1;
  startVertex.cost = 0;
  
  pQueue.push(startVertex);
  
  while (!pQueue.empty())
  {
    Container peek = pQueue.top();
    pQueue.pop();
    
    if (database[peek.vertex].isVisited == true)
      continue;
      
    database[peek.vertex].isVisited = true;
    database[peek.vertex].cost = peek.cost;
    database[peek.vertex].prev = peek.prev;
    
    if (peek.vertex == iEnd)
      break;
    
    for (it = database[peek.vertex].adjacentVertices.begin(); it != database[peek.vertex].adjacentVertices.end(); it++)
    {
      Container neighbor;
      neighbor.vertex = (*it).first;
      neighbor.cost = peek.cost +(*it).second;
      neighbor.prev = peek.vertex;
      pQueue.push(neighbor);
  } }
     
  result.second = database[iEnd].cost;
  for (int i = iEnd; i != database[iStart].prev; i = database[i].prev)
    result.first.push(i);
  
  return result;
}


int main()
{
  titleLines();

  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";  

  // process the input file
  vector<Vertex> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity, cost;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    getline(fin, cost);
    fin.ignore(1000, 10); // skip the separator
// TO DO -- code to eliminate whitespace-----------------------------------------------------------------------
    fromCity.erase(remove_if(fromCity.begin(), fromCity.end(), ::isspace), fromCity.end());
    toCity.erase(remove_if(toCity.begin(), toCity.end(), ::isspace), toCity.end());

    // add vertices for new cities included in the edge
    int iToVertex = -1, iFromVertex = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the vertex if it is new
      Vertex fromVertex;
      fromVertex.name = fromCity;
      database.push_back(fromVertex);
    }
    iFromVertex = i; 

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the vertex if it is new
      Vertex toVertex;
      toVertex.name = toCity;
      database.push_back(toVertex);
    }
    iToVertex = i; 

    // store bi-directional edges
    double edgeCost = atof(cost.c_str());
    database[iFromVertex].adjacentVertices.push_back(pair<int, double>(iToVertex, edgeCost));
    database[iToVertex].adjacentVertices.push_back(pair<int, double>(iFromVertex, edgeCost));
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    string fromCity, toCity;
    cout << "\nEnter the source city [blank to exit]: ";
    getline(cin, fromCity);
    if (fromCity.length() == 0) break;

    // find the from city
    int iFrom;
    bool foundFrom = false;
    for (iFrom = 0; iFrom < database.size(); iFrom++)
      if (database[iFrom].name == fromCity)
      {
        foundFrom = true;
        break;
      }

    cout << "Enter the destination city [blank to exit]: ";
    getline(cin, toCity);
    if (toCity.length() == 0) break;

    // find the destination city
    int iTo;
    bool foundTo = false;
    for (iTo = 0; iTo < database.size(); iTo++)
      if (database[iTo].name == toCity)
      {
        foundTo = true;
        break;
      }

    if (foundFrom == true && foundTo == true)
    {
      pair<stack<int>, double> result = getCheapestRoute(iFrom, iTo, database);
      cout << "\nTotal miles: " << result.second << endl;
      cout << "Route: ";
      if (!result.first.empty()){cout << database[result.first.top()].name; result.first.pop();}
      while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();}      
      cout << endl << endl;
    }
    else if (foundFrom == true && foundTo == false)
    {
      cout << "\nSssuuuua, ooo this is awkward. That destination city doesn't exist on the .txt\n";
      cout << "ProTips: capitalize the first letter; Don't space multi-word city names\n" << endl;
    }
    else if (foundFrom == false && foundTo == true)
    {
      cout << "\nSssuuuuuua, oooo this is awkward. That source city doesn't exist on the .txt\n";
      cout << "ProTips: capitalize the first letter; Don't space multi-word city names\n" << endl;
    }
    else
    {
      cout << "\nSssuuuuuuua, ooooo this is awkward. Those cities don't exist on the .txt\n";
      cout << "ProTips: capitalize the first letter; Don't space multi-word city names\n" << endl;
} } }
