#include "StudOrganizer.h"
#include <iostream>
#include <fstream>
// #include "ctype.h"

MyStudent::MyStudent(unsigned int my_stud_id, std::string my_name, unsigned short my_age) : id{my_stud_id}, name{my_name}, age{my_age} {}
MyStudent::~MyStudent()
{
}

unsigned int MyStudent::get_id()
{
    return id;
}
std::string MyStudent::get_name()
{
    return name;
}
unsigned short MyStudent::get_age()
{
    return age;
}
MyParser::MyParser() {}
MyParser::~MyParser() {}
MyManager::MyManager() {}
MyManager::~MyManager()
{
    for (MyStudent *student : student_book)
    {
        delete student;
    }
}
FileManager::FileManager() {}
FileManager::~FileManager() {}
std::vector<std::string> MyParser::operator()(std::string input)
{

    unsigned short counter = 0;
    std::string temp = "";
    std::vector<std::string> commands{};
    if (input.empty())
    {
        return commands;
    }

    bool name = false;
    int qcounter = 0;
    for (char i : input)
    {

        counter++;
        if (i == '"' && qcounter < 2)
        {
            name = !name;
            qcounter++;
        }
        if (name == true)
        {
            temp += i;
        }
        else if (name == false)
        {
            if ((i == separators[0] || i == separators[1]) && temp != "")
            {
                commands.push_back(temp);
                temp = "";
            }
            else if (i != separators[0] && i != separators[1])
            {
                temp += i;
                if (counter == input.length())
                {
                    commands.push_back(temp);
                }
            }
        }
    }

    return commands;
}
void MyManager::Condition(std::vector<std::string> &commands)
{
    unsigned int counter = 0;
    std::string condition = "";
    if (commands.size() > 2)
    {
        for (size_t i = 1; i < commands.size(); i++)
        {
            condition.append(commands[i]);
            counter++;
        }
        for (size_t i = 0; i < counter; i++)
        {
            commands.pop_back();
        }
    }
    else
    {
        condition = commands[1];
        commands.pop_back();
    }

    std::string temp;

    std::string comparator;
    for (size_t i = 0; i < condition.length(); i++)
    {

        if (condition[i] != comparators[0] && condition[i] != comparators[1] && condition[i] != comparators[2])
        {
            temp += condition[i];
            if (i == condition.length() - 1)
            {

                commands.push_back(temp);
                temp = "";
            }
        }
        else if ((condition[i] == comparators[0] || condition[i] == comparators[1] || condition[i] == comparators[2]))
        {
            if (temp != "")
            {
                commands.push_back(temp);

                temp = "";
            }

            comparator.append(1, condition[i]);
            commands.push_back(comparator);

            comparator = "";
        }
    }
}
void MyManager::ADD(const std::vector<std::string> &commands)
{
    for (char i : commands[1])
    {
        if (isdigit(i) == false || std::stoi(commands[1]) > WINT_MAX)
        {

            return;
        }
    }
    for (char i : commands[3])
    {
        if (isdigit(i) == false || std::stoi(commands[3]) > WCHAR_MAX)
        {

            return;
        }
    }
    std::string name = "";
    if (commands[2][0] == '"' && commands[2][commands[2].length() - 1] == '"')
    {
        for (size_t i = 1; i < commands[2].length() - 1; i++)
        {
            if (isalpha(commands[2][i]) == true && (commands[2][i] == '-' || commands[2][i] == ',' || commands[2][i] == ' '))
            {

                return;
            }
            else
            {
                if (commands[2][i] == '"')
                {
                    std::cout << "bad comment!!!\n";
                    return;
                }
                name += commands[2][i];
            }
        }
    }
    else
    {
        for (size_t i = 0; i < commands[2].length(); i++)
        {
            if (isalpha(commands[2][i]) == true && (commands[2][i] == '-' || commands[2][i] == ',' || commands[2][i] == ' '))
            {
                std::cout << 5;
                return;
            }
            else
            {
                name += commands[2][i];
            }
        }
    }
    unsigned int id = std::stoi(commands[1]);
    unsigned short age = std::stoi(commands[3]);
    MyStudent *ptr = new MyStudent(id, name, age);
    student_book.push_back(ptr);
}
void MyManager::FIND(const std::vector<std::string> &commands)
{

    if (commands[1] == "id")
    {
        for (char i : commands[3])
        {
            if (isdigit(i) == false || std::stoi(commands[3]) > WINT_MAX)
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
        if (commands[2] == "<")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_id() < (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else if (commands[2] == "=")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_id() == (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else if (commands[2] == ">")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_id() > (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else
        {
            std::cout << "bad comment!!!\n";
        }
    }
    else if (commands[1] == "name")
    {
        for (char i : commands[3])
        {
            if (isalpha(i) == false && (i != '-' && i != ',' && i != ' ' && i != '"'))
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
        if (commands[2] != "=")
        {
            std::cout << "bad comment!!!\n";
            return;
        }
        else if (commands[2] == "=")
        {
            std::string cmd_name = "";
            for (char i : commands[3])
            {
                if (i != '"')
                {
                    cmd_name += i;
                }
            }

            for (MyStudent *student : student_book)
            {
                if (student->get_name() == cmd_name)
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
    }
    else if (commands[1] == "age")
    {
        for (char i : commands[3])
        {
            if (isdigit(i) == false || std::stoi(commands[3]) > WCHAR_MAX)
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
        if (commands[2] == "<")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_age() < (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else if (commands[2] == "=")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_age() == (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else if (commands[2] == ">")
        {
            for (MyStudent *student : student_book)
            {
                if (student->get_age() > (unsigned int)std::stoi(commands[3]))
                {
                    std::cout << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << std::endl;
                }
            }
        }
        else
        {
            std::cout << "bad comment!!!\n";
            return;
        }
    }
    else
    {
        std::cout << "bad comment!!! \n";
    }
}
void MyManager::REMOVE(const std::vector<std::string> &commands)
{

    if (commands[1] == "id")
    {
        for (char i : commands[3])
        {
            if (isdigit(i) == false || std::stoi(commands[3]) > WINT_MAX)
            {
                std::cout << "bad comment!!!\n";
                return;
            }
            if (commands[2] == "<")
            {
                for (size_t i = 0; i < student_book.size(); i++)
                {
                    MyStudent *student = student_book[i];
                    if (student->get_id() < (unsigned int)stoi(commands[3]))
                    {
                        delete student;
                        student_book.erase(student_book.begin() + i);
                    }
                }
            }
            else if (commands[2] == "=")
            {
                for (size_t i = 0; i < student_book.size(); i++)
                {
                    MyStudent *student = student_book[i];
                    if (student->get_id() == (unsigned int)stoi(commands[3]))
                    {
                        delete student;
                        student_book.erase(student_book.begin() + i);
                    }
                }
            }
            else if (commands[2] == ">")
            {
                for (size_t i = 0; i < student_book.size(); i++)
                {
                    MyStudent *student = student_book[i];
                    if (student->get_id() > (unsigned int)stoi(commands[3]))
                    {
                        delete student;
                        student_book.erase(student_book.begin() + i);
                    }
                }
            }
            else
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
    }
    else if (commands[1] == "name")
    {
        for (char i : commands[3])
        {
            if (isalpha(i) == false && (i != '-' && i != ',' && i != ' ' && i != '"'))
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
        if (commands[2] != "=")
        {
            std::cout << "bad comment!!!\n";
            return;
        }
        else
        {
            std::string cmd_name = "";
            for (char i : commands[3])
            {
                if (i != '"')
                {
                    cmd_name += i;
                }
            }

            for (size_t i = 0; i < student_book.size(); i++)
            {
                MyStudent *student = student_book[i];
                if (student->get_name() == cmd_name)
                {
                    delete student;
                    student_book.erase(student_book.begin() + i);
                }
            }
        }
    }
    else if (commands[1] == "age")
    {
        for (char i : commands[3])
        {
            if (isdigit(i) == false || std::stoi(commands[3]) > WCHAR_MAX)
            {
                std::cout << "bad comment!!!\n";
                return;
            }
        }
        if (commands[2] == "<")
        {
            for (size_t i = 0; i < student_book.size(); i++)
            {
                MyStudent *student = student_book[i];
                if (student->get_age() < (unsigned int)stoi(commands[3]))
                {
                    delete student;
                    student_book.erase(student_book.begin() + i);
                }
            }
        }
        else if (commands[2] == "=")
        {
            for (size_t i = 0; i < student_book.size(); i++)
            {
                MyStudent *student = student_book[i];
                if (student->get_age() == (unsigned int)stoi(commands[3]))
                {
                    delete student;
                    student_book.erase(student_book.begin() + i);
                }
            }
        }
        else if (commands[2] == ">")
        {
            for (size_t i = 0; i < student_book.size(); i++)
            {
                MyStudent *student = student_book[i];
                if (student->get_age() > (unsigned int)stoi(commands[3]))
                {
                    delete student;
                    student_book.erase(student_book.begin() + i);
                }
            }
        }
        else
        {

            std::cout << "bad comment!!!\n";
            return;
        }
    }
    else
    {
        std::cout << "bad comment!!! \n";
    }
}

bool MyManager::process(std::vector<std::string> commands)
{
    if (commands.size() == 1 && commands[0] != "STOP")
    {
        std::cout << "bad comment!!!\n";
        return false;
    }
    FileManager FM;

    if (counter == (unsigned int)0)
    {
        FM.read_file(student_book);

        counter++;
    }
    if (commands.empty())
    {
        return false;
    }
    if (commands.size() > 4)
    {
        std::cout << "bad comment!!!\n";
        return false;
    }
    if (commands[0] == "STOP")
    {

        FM.write_file(student_book);
        return true;
    }
    else if (commands[0] == "ADD")
    {

        ADD(commands);
        return false;
    }
    else if (commands[0] == "FIND")
    {
        Condition(commands);
        if (commands.size() > 4)
        {
            std::cout << "bad comment!!!\n";
            return false;
        }
        FIND(commands);
        return false;
    }
    else if (commands[0] == "REMOVE")
    {
        Condition(commands);
        if (commands.size() > 4)
        {
            std::cout << "bad comment!!!\n";
            return false;
        }
        REMOVE(commands);
        return false;
    }
    else
    {
        std::cout << "bad comment!!!\n";
        return false;
    }
}

void FileManager::read_file(std::vector<MyStudent *> &stud_vect)
{
    std::ifstream student_list("student_book.txt");
    std::vector<std::string> students;
    std::string line;
    if (!student_list.is_open())
    {
        return;
    }
    else
    {
        while (std::getline(student_list, line))
        {
            students.push_back(line);
        }
    }

    std::vector<std::string> temp_stud;
    MyParser parse;
    unsigned int id;
    std::string name;
    unsigned short age;
    for (size_t i = 0; i < students.size(); i++)
    {
        temp_stud = parse(students[i]);
        id = stoi(temp_stud[0]);
        name = temp_stud[1];
        age = stoi(temp_stud[2]);
        MyStudent *ptr = new MyStudent(id, name, age);
        stud_vect.push_back(ptr);
    }
    student_list.close();
}
void FileManager::write_file(const std::vector<MyStudent *> &stud_vect)
{

    std::ofstream student_list("student_book.txt", std::ofstream::trunc);

    if (!student_list.is_open())
    {
        std::cout << "unable to write to file";
    }
    else
    {
        for (MyStudent *student : stud_vect)
        {
            student_list << student->get_id() << '\t' << student->get_name() << '\t' << student->get_age() << "\n";
        }
    }
    student_list.close();
    return;
}