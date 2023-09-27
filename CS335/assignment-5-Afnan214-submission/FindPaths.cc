/*
Afnan Ebrahim
HW Assignment 5
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "graph.h"
using namespace std;
/*
  uses a parser to take in a string an place each value into a vector of doubles and returns that vector
*/
vector<double> parse(const string& s)
{
  vector<double> connections;
  string number;
  if(s.empty())
  {
    return connections;
  }
  for(size_t i = 0; i< s.size(); i++)
  {
    if(isdigit(s[i])|| s[i] == '.')
    {
      number+= s[i];
    }
    else if(s[i] == ' '|| s[i] == '\t')
    {
      connections.push_back(stod(number));
      number = "";
    }
    if(i == s.size()-1 && number!="")
    {
      connections.push_back(stod(number));
    }
  }
  return connections;
}

/*
  this creates vector for the path and cost which will be passed into dijkstras algorithm
  it also creates the heap of nodes that will also be passed in.

*/
void shortest_path(graph &adj_graph, const int& src)
{
  
  vector<Node> empty;
  BinaryHeap<Node> priority{empty};
  vector<vector<int>> path;
  vector<double> cost;
  adj_graph.dijkstra(priority, src, path, cost);
  
  for(size_t i = 0; i< path.size(); i++)
  {
    if(path[i][0]==-1)
    {
      
      cout<<i+1<<": "<<"not_possible"<< endl;
    }
    else
    {
      
      cout<<i+1<<": ";
      for(size_t j = 0; j< path[i].size(); j++)
      {
        cout<<path[i][j]<<' ';
      }
      cout<< "cost: "<<cost[i]<< endl;
    }
  }
}
/*
  read from txt file using ifstream...
  use getline to read each line into a string s.
  if it is the first line read the first number into string and change it to an integer
  use this integer to create the adjacency graph
  then read every line till the end of file is reached... 
  as each line is read it is parsed and returned as a vector of double values. these values are entered into the graph

*/
void create_graph(const string& graph_filename, const int & src)
{
  ifstream graph_file(graph_filename);
  if(graph_file.fail())
  {
    cout<<"error opening file. \n";
    return;
  }
  string s;
  getline(graph_file,s);
  int num_nodes;
  if(isdigit(s[0]))
  {
    num_nodes = stoi(s);
  }
  graph adj_graph{num_nodes};
  vector<double> links;
  while (!graph_file.eof())
  {
    getline(graph_file, s);
    links = parse(s);
    for(size_t i = 2; i< links.size(); i+=2)
    {
      adj_graph.add_edge(links[0], links[i-1], links[i]);
    }
  }
  shortest_path(adj_graph, src);
}
int pathfindDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
    const string graph_filename(argv[1]);
    const string starting_vertex(argv[2]);
    create_graph(graph_filename, stoi(starting_vertex));
    
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
