-The following assignment asked to implement an adjacency list and dijkstras algorith to find the shortest path from a starting node to each node in the list To start the project I first created a Node class to represent each vertex that is placed into the graph. I gave it private members int src, num, and double cost. I also made a edge class to represent each of the edges that were given into the graph. Each edge has an int src, dst, and double weight. Inside the main graph class I created a vector<vector<node*>> alist to hold the nodes that are entered into the graph, and vector<edge*> to hold the edges and their weights. To check if two nodes are connected search through the edge pointer list and return true if an edge is found. To return the weight, find the edge and return the weight.

-I implemented dijkstras algorithm in graph.h. I took in 4 parameters, a binaryHeap, int src, vector<vector>path, and vector cost. I fill in path with vector{-1} for each vertex in the graph. Therefore if a vertex is unreachable then the -1 will imply that. Cost is filled with large number representing infinity. This will be replaced when a new short path is found to that vertex. The hardest part of the assignment was figuring out how to get the algorithm to work with the binary heap however after watching https://www.youtube.com/watch?v=CerlT7tTZfY&t=582s&ab_channel=MaryElaineCaliff (video on how dijkstras agorithm works using priority queues, I was able to learn what goes into the queue and what to pop and when.

-CreateGraphAndTest.cc i read from the text files using ifstream and used a parser to split up the numbers and values. The very first number in the file is used to create the graph and is used to create the number of nodes. This is the same for FindPaths.cc.


# Assignment-5-Code

To compile type:

 `make all`

To clean object files and executables type:

 `make clean`
 
To run the create and test graph routine, type:
`./CreateGraphAndTest <GRAPH_FILE> <ADJECENCY_QUERYFILE>`

where `<GRAPH_FILE>` is the file used to create the graph and
`<ADJECENCY_QUERYFILE>` is the file used to check if vertices
are adjacent

Example:
`./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt`

To run the find paths in graph routine, type:
`./FindPaths <GRAPH_FILE> <STARTING_VERTEX>`

where `<GRAPH_FILE>` is the file used to create the graph and 
`<STARTING_VERTEX>` is the vertex in the graph as the starting
point for the paths

Example:
`./FindPaths Graph2.txt 1`
