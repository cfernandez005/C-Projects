//Lab 15a, Write a Function for Depth-First Search, DFS
//Chris Fernandez
//Editor: Notepad++
//Compiler: g++

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

void titleLines()
{
  cout << "Lab 15a, Write a Function for Depth-First Search, DFS" << endl;
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
  list<int> adjacentVertices;
};

queue<int> doBreadthFirstSearch(int iOriginVertex, vector<Vertex>& database)
{
  queue<int> vertexQueue; // vertices to consider, by index
  queue<int> searchOrder; // return this queue of indices

  for (int i = 0; i < database.size(); i++) database[i].isVisited = false;
  if (iOriginVertex < 0 || iOriginVertex >= database.size()) return searchOrder; // empty queue -- no such city

  database[iOriginVertex].isVisited = true;
  searchOrder.push(iOriginVertex);
  vertexQueue.push(iOriginVertex);

  while (!vertexQueue.empty())
  {
    // TO DO -- write this code block----------------------------------------------------------------
    int peek = vertexQueue.front();
    vertexQueue.pop();
    
    for (list<int>::iterator it = database[peek].adjacentVertices.begin(); it != database[peek].adjacentVertices.end(); it++)
      if (database[*it].isVisited == false)
      {
        database[*it].isVisited = true;
        searchOrder.push(*it);
        vertexQueue.push(*it);
      }
  }

  return searchOrder;
}

queue<int> doDepthFirstSearch(int iOriginVertex, vector<Vertex>& vertices)
{
  queue<int> searchOrder;
  // TO DO -- write this function---------------------------------------------------------------------
  if (iOriginVertex < 0 || iOriginVertex >= vertices.size()) return searchOrder;
  stack<int> vertexStack;
  
  for (int i = 0; i < vertices.size(); i++) vertices[i].isVisited = false;
  vertexStack.push(iOriginVertex);
  
  while (!vertexStack.empty())
  {
    int peek = vertexStack.top();
    vertexStack.pop();
    
    if (vertices[peek].isVisited == false)
    {
      vertices[peek].isVisited = true;
      searchOrder.push(peek);
      
      for (list<int>::reverse_iterator it = vertices[peek].adjacentVertices.rbegin(); it != vertices[peek].adjacentVertices.rend(); it++)
        if (vertices[*it].isVisited == false)
          vertexStack.push(*it);
  } }
  
  return searchOrder;
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
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator
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
    database[iFromVertex].adjacentVertices.push_back(iToVertex);
    database[iToVertex].adjacentVertices.push_back(iFromVertex);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if (startCity.length() == 0) break;

    // find the start city
    int i;
    bool found = false;
    for (i = 0; i < database.size(); i++)
      if (database[i].name == startCity)
      {
        found = true;
        break;
      }

    if (found == true)
    {
      // BFS result
      cout << "\nBFS";
      queue<int> q = doBreadthFirstSearch(i, database);
      while(!q.empty())
      {
        cout  << '-'<< database[q.front()].name;
        q.pop();
      }
      cout << endl << endl;

      cout << "DFS";
      q = doDepthFirstSearch(i, database);
      while(!q.empty())
      {
        cout  << '-'<< database[q.front()].name;
        q.pop();
      }
      cout << endl << endl;
    }
    else
    {
      cout << "\nSssuuuuuua, oooo this is awkward. That city doesn't exist on the .txt\n";
      cout << "ProTips: capitalize the first letter; Don't space multi-word city names\n" << endl;
} } }  
