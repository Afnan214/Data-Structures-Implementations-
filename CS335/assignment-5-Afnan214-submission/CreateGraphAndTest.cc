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
  read from the file query_file
  use parser to parse each line
  returns 2 values one will be the src node and the other will be dst node
  check if the two nodes are connected
*/
void query_list(const string& query_filename,  graph &adj_graph)
{
  //read file
  ifstream query_file(query_filename);
  if(query_file.fail())     //if unable to open return error
  {
    cout<<"error openeing query file. \n";
    return;
  }
  vector<double> connection;    
  string s;
  //read till end of file
  while(!query_file.eof())
  {
    getline(query_file, s);
    if(!s.empty())
    {
      connection = parse(s);
      cout<< connection[0]<< ' '<< connection[1]<< ": ";
      if(adj_graph.check_connection(connection[0], connection[1]))
      {
        cout<< "connected "<< adj_graph.get_edge_weight(connection[0],connection[1])<<'\n';
      }
      else
      {
        cout<< "not_connected\n";
      }
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
void create_list(const string& graph_filename,const string& query_filename)
{
  ifstream graph_file(graph_filename);
  if(graph_file.fail())
  {
    cout<<"error opening graph file. \n";
    return;
  }
  string s;
  getline(graph_file,s);
  int num_nodes;
  if(isdigit(s[0]))             //if it is a digit turn it into an integer
  {
    num_nodes = stoi(s);
  }
  else                          // else return error
  {
    cout<< "first number is not an integer... ERROR \n";
    return;
  }
  graph adj_graph{num_nodes};   //create graph of N nodes(vertexes)
  vector<double> links;
  //while !end of file keep reading
  while (!graph_file.eof())
  {
    getline(graph_file, s);
    links = parse(s);
    for(size_t i = 2; i< links.size(); i+=2)
    {
      adj_graph.add_edge(links[0], links[i-1], links[i]);
    }
  }
  query_list(query_filename, adj_graph);

}
int graphTestDriver(int argc, char **argv) {
    
    // Begin your code here. Feel free to add any helper functions or classes you need,
    // as long as we only have to call this function to run the specified assignment.
    const string graph_filename(argv[1]);
    const string query_filename(argv[2]);
    create_list(graph_filename, query_filename);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    graphTestDriver(argc, argv);

    return 0;
}
