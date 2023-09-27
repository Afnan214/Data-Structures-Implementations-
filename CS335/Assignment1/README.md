[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8318006&assignment_repo_type=AssignmentRepo)
# Assignment 1
## README Description of project
  My solution to the problem makes proper use of each of the big five elements, which implements a redefined constructor, copy-constructor, copy-assignment, move-constuctor, move-assignment, and destructor. The defaults that are usually provided won't work because of the data field "sequence_" which points to the beginning of a dynamically allocated array of certain size, usually declared or given by the user when being read from user input. 
  At first when approaching the big 5 functions I was trying to take the information from the textbook and basically convert it to fit the assignment. In which case I made sequence_ = rhs.sequence when dealing with the copy constructor, until I realized that I was meant to create a deep copy which instead of just copying the pointer, it copies the elements that the rhs.sequence pointer is pointing to, thus realizing the importance of deep copy vs shallow copy.
  Overloading operator>> was probably the most difficult for me. It takes in the input from the user and transfers the input and stores the information into the object that the input is being called on. This was difficult at first for me because I didn't realize that I could call some_points.sequence_ directly as I did in the project. Instead I jumped to making mutator function which I would call and it would take an array as a parameter and would take an array and the size as a parameter and would create the dynamically allocated array that way. However I later realized the friend keyword allows us to access the private elements directly. Therefore leading me to creating the dynamically allocated array and storing the values of the user input directly in the operator>> function instead of creating a setter function.
  
## Information about the repository

This repository contains the following:
- Starter code: `points2d.h`, `points2d.cc`,`test_input_file.txt`, `expected_output.txt`, `Makefile` and `README.md`
- Assignment specification: `Fall22-Assignment1.pdf`
- Testing Document: `Testing_Document.pdf`

## Running the assignment

You will use this exact `Makefile` for your Assignment 1. Failure to do so will result in *deduction* of points.

To compile on terminal, type:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points2d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points2d < test_input_file.txt
```
