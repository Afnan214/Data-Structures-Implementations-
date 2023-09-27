#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <list>
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
// This file is for your graph implementation.
// Add everything you need in between the "ifndef and "endif" statements.
// Do not put anything outside those statements

/*
    This is the node class... or can be seen as vertex class
    int src---> is used in Dijkstras function
    src--> will return the number of the node that lead to this node.(used in dijkstras)
    num--> is the number of this node (nodes identifier)
    cost--> this will hold the cost taken to get to this node from a src node (used in dijkstras)
*/
class Node{
public:
    Node(){}            //constructor
    Node(int num)       //constructor on giving node identifier info
    {
        this->num = num;
    }
    Node(int num, double cost)      //constructor giving the identifier and the cost 
    {
        this->num = num;
        this->cost = cost;
    }
    Node(int src, int num, double cost)         //constructor giving the src node, identifier, and the cost
    {
        this->src = src;
        this->num = num;
        this->cost = cost;
    }
    /*
        the next couple functions are used to overload the comparison operators so that 
        the binary heap knows to compare the node costs or weights and not the identifiers or the src nodes...
    */
    friend bool operator <(Node const& lhs, Node const& rhs)
    {
        return lhs.cost < rhs.cost;
    }
    friend bool operator >(Node const& lhs, Node const& rhs)
    {
        return lhs.cost> rhs.cost;
    }
    friend bool operator ==(Node const& lhs, Node const& rhs)
    {
        return lhs.cost == rhs.cost;
    }
    //get num(or identifier of this noed)
    int get_num()
    {
        return num;
    }
    //get src (get the number of the node that lead to this node)
    int get_src()
    {
        return src;
    }
    //get cost (get the weigth of the path taken to get to this node from some start_src node)
    double get_cost()
    {
        return cost;
    }
    void set_visited(bool visited)
    {
        
    }
private:
    int num, src;
    double cost;
    bool visited;
};
/*
    this is the edge class
    stores src node ---->dst and the weight of the edge
*/
class edge
{
public:
    //constructor 
    edge(int src, int dst, double weight)
    {
        this->src = src;
        this->dst = dst;
        this->weight = weight;
    }
    //gets src 
    int get_src()
    {
        return src;
    }
    //gets dst 
    int get_dst()
    {
        return dst;
    }
    //gets the weight of this edge
    double get_weight()
    {
        return weight;
    }
private:
    int src, dst;
    double weight;
};
/*
    adjacency list representation using vector<vector<Node*>>...
    the rows represent the nodes... so 7 nodes= 7 rows
                                    so 5 nodes= 5 rows
    and the columns represent the adjacent nodes next to this first node
    alist[i][0] is the src node and all elements after are the nodes connected to this first node
    
    also makes use of vector of edge pointers to hold each of the edges that were added.
*/
class graph{
private:
    vector<vector<Node*>> alist;
    vector<edge*> edges;
    int num_nodes;
public:    
    // constructor pushes back a vector holding a pointer to a new node identified as i+1 == 1, 2, 3, 4, 5 ... num_nodes
    graph(int num_nodes)
    {
        this->num_nodes = num_nodes;
        for(int i = 0; i< num_nodes;i++)
        {
            alist.push_back(vector<Node*>{new Node{i+1}});
            
        }    
    }
    //deconstructor
    ~graph()
    {
        for(auto edge: edges)
        {
            delete edge;
        }
        for(auto i: alist)
        {
            for(auto j: i)
            {
                delete j;
            }
        }
    }
    // adds edge ptr into the edges vector
    // adds the dst node to the vector of vector of node pointers
    void add_edge (int src, int dst, double weight)
    {
        edge* edge_ptr = new edge{src, dst , weight};
        edges.push_back(edge_ptr);          //edges gets src...dst...and weight
        Node* Node_ptr = new Node{dst};
        alist[src-1].push_back(Node_ptr); //the vector of nodes adjacent to the src node gets this new adjacent node
    }
    /*
        gets the edge taht starts from src and ends at dst
        if it is found then return true
        else return false
    */
    bool check_connection(const int &src, const int& dst)
    {
        for(auto edge: edges)
        {
            if(edge->get_src() == src && edge-> get_dst() == dst)
            {
                return true;
            }
        }
        return false;
    }
    /*
        gets the weight of the edge starting ad src ---> dst
    */
    double get_edge_weight(int src, int dst)
    {
        for(auto edge: edges)
        {
            if(edge->get_src() == src && edge-> get_dst() == dst)
            {
                return edge->get_weight();
            }
        }
        return 0.0;
    }
    /*
        The following function takes a heap, starting vertex, an vector of vector<int> path, and a vector<double> cost
        cost will be filled with the cost taken to get to this specific node from src
                                                                to get cost 1... cost[0]
                                                                to get cost 2... cost[1]
                                                                .
                                                                .
                                                                .
                                                                to get cost 7... cost[6]
                                                                
        path will hold the path taken to get to the node---->   to get to 1... path[0]...  1
                                                                to get to 2... path[1]...  1 2
                                                                to get to 3... path[2]...  1 4 3
                                                                .
                                                                .
                                                                .
                                                                to get to 7... path[6]...  1 4 7
    */
    void dijkstra(BinaryHeap<Node> &priority, const int& src, vector<vector<int>>& path, vector<double>& cost)
    {
        /*
            cost is filled with large numbers representing "infinity"

            this first for loop is used to fill in the vector of vectors of ints with -1 
            so if a path is not reached it will return a -1 which translates to "not_possible"
        */
        for(size_t i = 0; i< alist.size(); i++)
        {
            cost.push_back(INT32_MAX);  //place large numbers representing cost
            path.push_back(vector<int>{-1});
        }
        //this if statement checks if src node connects to anything to prevent
        //segmentation fault in my code
        //if the node doesnt connect to anything return.
        if(alist[src-1].size() == 1)
        {
            return;
        }
        vector<int> visited{};          //array of visited nodes kept track of using integers
        Node start{src, 0};             //enters src Node into the heap which is 
        priority.insert(start);         //popped in the first iteration of the while loop
        int current_node = src;         //current_node used in the for loop is set to src
        int dst;
        double weight = 0.0;            //initial weight is set to 0
        double c_p_weight;              // "current-path-weight"
        
        while(!priority.isEmpty())      //as long as the heap has elements to pop, keep going
        {   
            Node del_src = priority.findMin();         //temp node to pop the src node from the heap
            if(del_src.get_num() == src)               //if the src element is in pq
            {                                          //delete it
                priority.deleteMin();                  //set cost to 0
                cost[src-1] = 0;                       //set path to itself
                path[src-1] = vector<int>{src};
            }
            
            //for each node adjacent to the current_node being visited
            for(size_t i = 1; i< alist[current_node-1].size(); i++)
            {
                
                //if adjacent node has not been visited
                vector<int>::iterator it = find(visited.begin(), visited.end(), alist[current_node-1][i]->get_num());       // used in the following if statement
                //checks if the adjacent node has been visited
                //if it was visited ---> skip
                //if it wasnt visited ---> do this...
                if(it == visited.end()|| visited.empty())
                {
                    /*
                        get the current paths weight and set it to c_p_weight
                        create temporary Node to put into priority queue
                        node->src == current_node
                        node->num == dst (the adjacent node)
                        node->cost == c_p_weight + weight (weight is updated ever iteration of the while loop)
                    */
                    dst = alist[current_node-1][i]->get_num();
                    
                    for(auto edge: edges)
                    {
                        if(edge->get_src() == current_node && edge->get_dst() == dst)
                        {
                            c_p_weight = edge->get_weight();                // gets the weight of current node to adjacent node
                        }
                    }
                    Node util{current_node, dst, weight+ c_p_weight};
                    priority.insert(util);
                }
            
            }
            /*
                now that the adjacent nodes have been added to the heap
                we get the minimum_value and set it equal to current_min_node
                -then pop the node from the heap
                -use the information to update values in the path and cost vectors
            */
            Node current_min_node = priority.findMin();
            priority.deleteMin();
            //this if statement checks to see if the cost retrieved from the heap 
            //is lower than the cost that is currently stored in the cost vector
            if(current_min_node.get_cost()< cost[current_min_node.get_num()-1])
            {
                //if the new value is lower, the update cost and set it to the min_node cost
                //update the path to be equal to the path of the src of the current_min_node + the current_min_node->number
                cost[current_min_node.get_num()-1] = current_min_node.get_cost();
                path[current_min_node.get_num()-1] = path[current_min_node.get_src()-1];
                path[current_min_node.get_num()-1].push_back(current_min_node.get_num());
            }
            //update weight to be equal to the cost of the current_min_node
            //place the current node we just finished visiting into the visited vector
            //update current_node to the next node ----> current_min_node->num
            weight = current_min_node.get_cost();
            visited.push_back(current_node);
            current_node = current_min_node.get_num();

        }
        
    }
};




#endif
