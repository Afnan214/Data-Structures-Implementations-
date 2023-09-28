Implement an interpreter for a programming language that I came up with. We call this language HUNLAN.
HUNLAN is very primitive but still it is a programming language. Interpreter we write is very primitive but still it is an interpreter like Python or JavaScript interpreters.
I will take your program and compile it. Then, the resulting executable will be used to run program files, same way you do it in Python. From your source code, I will create an executable named hunlan with the following command
>>> g++  -std=c++17  *.cpp  -o hunlan
Later, I create a plain txt file mycode.hun with the program code in HUNLAN. Then, I execute this code the following way
>>> ./hunlan  mycode.hun
In case the interpreter finds incorrect instruction in the source code, it shows an error message with the line number where the error occurred. The message should look like “ERROR: Bad instruction in Line 28”. Specifying the exact problem isn’t necessary. Program lines are enumerated starting from 1. Empty lines are also enumerated. Lines with comments are also enumerated. In other words, line enumeration happens the same way it happens in any editor and compiler.
You must implement a decent program structure and decent programming style. Whole program in one main function or variable names like o, p, r will be heavily penalized.
 
See below the description of HUNLAN. This language
Accepts one instruction per line
Allows empty lines with no instructions
Everything starting with # till the end of the line is ignored. In other words, # is a symbol of one-line comment.
Is case-sensitive
Separators include spaces and tabs. Instructions can have multiple leading and trailing separators.
 
Has variables of two datatypes: NUMBER and STRING
NUMBER is a 8-Byte integer
STRING is a string
Variable declaration looks like this
datatype  variable_name
Variable naming rules follow C++ variable naming rules
 
There are numeric literals consisting of only digits.
There are string literals consisting of any ASCII characters except double-quotation marks. String literal must be enclosed in double-quotation marks. Enclosing double-quotation marks aren’t a part of a literal. In terms of escape sequences, HUNLAN strings behave exactly like C++  strings.
There’s an assignment operator = .
Assignment of numeric values to string variables is prohibited. Assignment of string values to numeric variables is also prohibited.
 
There are mathematical expressions with numeric variables and literal using operators +, –, * (no division). The precedence rules work as usual.
Usage of string variables or string literals anywhere in expression is prohibited.
Assigning the value of one string variable to another string variable is allowed.
Pay attention, there are no negative value literals in HUNLAN, but negative values of variables and expressions are allowed.
 
There’s a PRINT command that prints one single variable or literal of any type.
Using PRINT with more than one variable or literal is prohibited.
Supplying mathematical expressions to PRINT is prohibited.
 
Multiple variable declarations cause unspecified behaviour. In means that your program can react on it in any way, including crashes, error messages or silent execution of the program further.
"Multiple variable declaration" means declaring variable with the same name more than once. Your program is free to react in any way.