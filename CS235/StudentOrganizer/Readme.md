Write in C++ a student data storing program.
Student record consists of unsigned int student_ID, string name, and unsigned short age.
Students records should persist between program launches. In other words, if I start your program today and enter a bunch of student records then tomorrow, when I start this program again, all yesterdays records should be available. It means that all student records must be stored in file on a hard disc.
The program runs in terminal window and knows the following commands:
ADD  student_ID  name  age
Adds a student record with corresponding fields. The order of parameters is fixed. Parameters supplied in different order cause error. For example:
ADD 67412  Smith,John  21
ADD   8723333 "Ann Smith"   33
 
FIND  condition
Prints all records satisfying the condition. More details on conditions below. See below the example of command and potential output:
FIND  age = 21
67412           Smith,John            21
761              Mary Doe             21
33221212    Jack-Mark            21

FIND  id>1000000
33221212    Jack-Mark            21

           FIND  name = Jack-Mark
           33221212    Jack-Mark            21
           FIND  name = "Ann Smith"
           8723333     Ann Smith            33
           229             Ann Smith            19
REMOVE  condition
For example:
REMOVE   id< 50000   

STOP
Exits the application.
Here are additional specifications and requirements
Separators include space and tab symbols. There can be leading and trailing separator symbols in each command. Command components can be separated by any combination of any separators.
Each condition has a format field_name relationship_operator value.
Valid field names are id, name, age.
Valid relationship operators are =,  >, < .
Valid values for numeric fields are sequences of digits (without signs, decimal point, or any separator)
Valid values for string fields are
sequences of printable characters without any spaces, tabs, double quotation marks ("), symbols < > =. 
sequences of printable characters fully enclosed in double quotation marks. Can contain spaces and tabs but cannot contain double quotation marks other than the enclosing ones. Enclosing double quotation marks aren't a part of a string.
For string comparisons, use default C++ string comparison.
In conditions, parts can be separated by spaces and tabs.
We implement only one condition per command.
STOP operation causes all previously-made changes to be saved to a hard disk.
Ignore an input if it is incorrect and print a warning that the input was ignored. Input can be incorrect if the command is wrong, if given id value overflows unsigned int or age value overflows unsigned short, or any unrecognized situation occurs.
All input is case-sensitive.
 
Implementation requirements:
There must be a special class for parsing. In that class, operator() should be defined to take a string and return a vector of separate tokens. It should work like this
MyParser  parser;
std::string  user_command = "  ADD   8723333 \"Ann Smith\"   33   ";
std::vector<std::string>  parsed_command;
parsed_command = parser(user_command);
// at this point parsed_command == {"ADD", "8723333", "Ann Smith", "33"}
It would be wise to store a list of separator symbols (in our case ' ' and '\t') separately inside a parser class, instead of hard-coding them right in the parsing function.
There must be a special manager class that has separate functions for ADD, FIND, REMOVE, and STOP. These functions are called to do the corresponding task and take arguments needed for it.
There should be a hard disk management class with at least
a function responsible for taking a filename and returning a vector of student records read from that file
a function responsible for taking a filename and a vector of student records and writing student records in a specified file. If the file already exists, it should be overwritten.
That disk management component should be used to deal with data on a hard disk.
Function main() shouldn't have code for implementing instructions or implementing parsing or anything like that. Function main() should look like that
int main()
{
    MyManager  engine;

    std::vector<char>  separators{' ', '\t'};
    MyParser  parser{separators}; // its ok to not have a parametrized constructor and have a fixed set of separators inside a class
    std::string  userInput;
    bool  shouldStop{false};
    while(!shouldStop)
    {
          getline(cin, userInput); // pay attention, pure cin doesn't allow spaces or tabs in userInput
          shouldStop = engine.process( parser(userInput) );
    }

   return 0;
}
