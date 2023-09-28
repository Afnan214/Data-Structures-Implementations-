#include "members.h"

NUMBER::NUMBER(const std::string &name, const int long long &val) : num_name{name}, value{val} {}
NUMBER::NUMBER(const std::string &name) : num_name{name}, value{NULL} {}
NUMBER::~NUMBER() {}
STRING::STRING(const std::string &name, const std::string &str) : str_name{name}, message{str} {}
STRING::STRING(const std::string &name) : str_name{name} {}
STRING::~STRING() {}
std::string STRING::get_name()
{
    return str_name;
}
std::string STRING::get_message()
{
    return message;
}
void STRING::set_message(const std::string &mess)
{
    message = mess;
}
int long long NUMBER::get_value()
{
    return value;
}
void NUMBER::set_value(const int long long &val)
{
    value = val;
}
std::string NUMBER::get_name()
{
    return num_name;
}
MyParser::MyParser() {}
MyParser::~MyParser() {}
MyManager::MyManager() {}
MyManager::~MyManager()
{
    for (NUMBER *num : number_list)
    {
        delete num;
    }
    for (STRING *str : string_list)
    {
        delete str;
    }
}

std::vector<std::string> MyParser::operator()(const std::string &input)
{

    unsigned short counter = 0;
    std::string temp = "";
    std::vector<std::string> commands{};
    if (input.empty())
    {
        return commands;
    }
    std::string str = "";
    bool string = false;
    bool hash = false;
    int qcounter = 0;
    for (char i : input)
    {

        counter++;
        if (i == '"' && qcounter < 2)
        {
            string = !string;
            qcounter++;
        }
        if (string == true)
        {
            temp += i;
        }
        if (i == '#' && string == false)
        {
            hash = true;
        }
        else if (string == false && hash == false)
        {
            if ((i == separators[0] || i == separators[1] || i == '=') && temp != "")
            {
                commands.push_back(temp);
                if (i == '=')
                {
                    str.push_back(i);
                    commands.push_back(str);
                    str = "";
                }
                temp = "";
            }

            else if ((i != separators[0]) && (i != separators[1]))
            {
                temp += i;
                if (counter == input.length() - 1) //
                {
                    commands.push_back(temp);
                }
            }
        }
    }

    return commands;
}
bool MyManager::process(std::vector<std::string> commands)
{
    counter++;

    if (commands.size() == 0)
    {
        return true;
    }
    if (is_keyword(commands[0]))
    {
        if (commands[0] == "NUMBER")
        {
            if (!is_proper_name(commands[1]))
            {
                std::cout << "error in line " << counter << "\n";
                return false;
            }
            if ((commands.size() == 2 && is_proper_name(commands[1])))
            {
                NUMBER *ptr = new NUMBER(commands[1]);
                number_list.push_back(ptr);
                return true;
            }
            else if (is_proper_name(commands[1]) && commands[2] == "=")
            {
                std::vector<std::string> copy = commands;
                copy.erase(copy.begin(), copy.begin() + 3);
                if (evaluate_expression(copy) == NULL)
                {
                    std::cout << "error in line " << counter << "\n";
                    return false;
                }
                else
                {
                    NUMBER *ptr = new NUMBER(commands[1], evaluate_expression(copy));
                    number_list.push_back(ptr);
                    return true;
                }
            }
            else
            {
                std::cout << "error in line " << counter << "\n";
                return false;
            }
        }
        else if (commands[0] == "STRING")
        {
            if (!is_proper_name(commands[1]))
            {
                std::cout << "error in line " << counter << "\n";
                return false;
            }
            if ((commands.size() == 2 && is_proper_name(commands[1])))
            {
                STRING *ptr = new STRING(commands[1]);
                string_list.push_back(ptr);
                return true;
            }
            else if (is_proper_name(commands[1]) && commands[2] == "=")
            {
                if (commands.size() != 4)
                {
                    std::cout << "error in line " << counter << "\n";
                    return false;
                }
                else
                {
                    if (commands[3][0] != '"' && commands[3][commands[3].size() - 1] != '"')
                    {
                        std::cout << "error in line " << counter << "\n";
                        return false;
                    }
                    else
                    {
                        std::string temp = "";
                        for (char i : commands[3])
                        {
                            if (i != '"')
                            {
                                temp += i;
                            }
                        }
                        STRING *ptr = new STRING(commands[1], temp);
                        string_list.push_back(ptr);
                        temp = "";
                        return true;
                    }
                }
            }
        }
        else
        {
            if (commands.size() > 2)
            {
                std::cout << "error in line " << counter << "\n";
                return false;
            }

            if (is_string_literal(commands[1]))
            {

                std::cout << evaluate_string(commands[1]);
                return true;
            }
            else if (is_var_name(commands[1]))
            {
                print_val(commands[1]);
                return true;
            }
            else
            {
                if (is_number_literal(commands[1]))
                {
                    std::cout << commands[1];
                    return true;
                }
            }
        }
    }
    else if (is_var_name(commands[0]))
    {
        if (commands[1] != "=")
        {
            std::cout << "error in line " << counter << "\n";
            return false;
        }
        if (is_num_var_name(commands[0]))
        {
            if (commands.size() == 3)
            {
                if (!is_number_literal(commands[2]) && !is_num_var_name(commands[2]))
                {
                    std::cout << "error in line 9 " << counter << "\n";
                    return false;
                }
                equal_operator_number(commands[0], commands[2]);
                return true;
            }
            else if (commands.size() > 3)
            {
                std::vector<std::string> copy = commands;
                copy.erase(copy.begin(), copy.begin() + 2);
                if (evaluate_expression(copy) != NULL)
                {
                    equal_operator_number(commands[0], std::to_string(evaluate_expression(copy)));
                    return true;
                }
                else
                {
                    std::cout << "error in line 10 " << counter << "\n";
                    return false;
                }
            }
        }

        else if (is_str_var_name(commands[0]))
        {
            if (commands.size() != 3)
            {
                std::cout << "error in line 11 " << counter << "\n";
                return false;
            }
            else
            {
                if (!is_str_var_name(commands[2]) && !is_string_literal(commands[2]))
                {
                    std::cout << "error in line 12 " << counter << "\n";
                    return false;
                }
                equal_operator_string(commands[0], commands[2]);
                return true;
            }
        }
        else
        {
            std::cout << "error in line 13 " << counter << "\n";
            return false;
        }
    }
    else
    {
        return true;
    }
    std::cout << "error in line 14 " << counter << "\n";
    return false;
}

bool MyManager::is_keyword(const std::string &first_word)
{
    for (size_t i = 0; i < keywords.size(); i++)
    {
        if (first_word == keywords[i])
        {
            return true;
        }
    }
    return false;
}
bool MyManager::is_var_name(const std::string &first_word)
{
    for (STRING *name : string_list)
    {
        if (first_word == name->get_name())
        {
            return true;
        }
    }
    for (NUMBER *name : number_list)
    {
        if (first_word == name->get_name())
        {
            return true;
        }
    }
    return false;
}
bool MyManager::is_str_var_name(const std::string &first_word)
{
    for (STRING *name : string_list)
    {
        if (first_word == name->get_name())
        {
            return true;
        }
    }
    return false;
}
bool MyManager::is_num_var_name(const std::string &first_word)
{
    for (NUMBER *name : number_list)
    {
        if (first_word == name->get_name())
        {
            return true;
        }
    }
    return false;
}
bool MyManager::is_string_literal(const std::string &str)
{
    if (str[0] == '"' && str[str.size() - 1] == '"')
    {
        return true;
    }
    else
        return false;
}
bool MyManager::is_number_literal(const std::string &num)
{
    bool is_number = true;
    for (char c : num)
    {
        if (isdigit(c) == 0)
        {
            is_number = false;
        }
    }
    if (is_number)
    {
        return true;
    }
    return false;
}
std::string MyManager::evaluate_string(const std::string &str)
{
    std::string evaluated_str = "";
    bool new_line = false;
    for (size_t i = 0; i < str.size() - 1; i++)
    {
        if (str[i] == '\\' && str[i + 1] == 'n')
        {
            std::cout << '\n';
            new_line = true;
        }
        else if ((i != 0 && i != str.length() - 1))
        {
            if (new_line)
            {
                new_line = false;
            }
            else
            {
                evaluated_str += str[i];
            }
        }
    }
    return evaluated_str;
}
void MyManager::print_val(const std::string &var_name)
{
    for (STRING *name : string_list)
    {
        if (var_name == name->get_name())
        {
            std::cout << evaluate_string(name->get_message());
            return;
        }
    }
    for (NUMBER *name : number_list)
    {
        if (var_name == name->get_name())
        {
            std::cout << name->get_value();
            return;
        }
    }
}
bool MyManager::is_proper_name(const std::string &name)
{

    if (name[0] != '_' && (isalpha(name[0]) == 0))
    {

        return false;
    }
    for (size_t i = 0; i < name.length(); i++)
    {
        if ((name[i] != '_') && (isdigit(name[i]) == false) && (isalpha(name[i]) == false))
        {

            return false;
        }
    }
    return true;
}
void MyManager::equal_operator_string(const std::string &orig, const std::string &new_val)
{
    if (is_var_name(new_val))
    {
        for (STRING *original : string_list)
        {
            if (original->get_name() == orig)
            {
                for (STRING *n_val : string_list)
                {
                    if (n_val->get_name() == new_val)
                    {
                        original->set_message(n_val->get_message());
                    }
                }
            }
        }
    }
    else if (is_string_literal(new_val))
    {
        for (STRING *original : string_list)
        {
            if (original->get_name() == orig)
            {
                original->set_message(new_val);
            }
        }
    }
}
void MyManager::equal_operator_number(const std::string &orig, const std::string &new_val)
{
    if (is_var_name(new_val))
    {
        for (NUMBER *original : number_list)
        {
            if (original->get_name() == orig)
            {
                for (NUMBER *n_val : number_list)
                {
                    if (n_val->get_name() == new_val)
                    {
                        original->set_value(n_val->get_value());
                    }
                }
            }
        }
    }
    else if (is_number_literal(new_val))
    {
        for (NUMBER *original : number_list)
        {
            if (original->get_name() == orig)
            {
                original->set_value(stoi(new_val));
            }
        }
    }
}
int MyManager::evaluate_expression(std::vector<std::string> operations)
{
    std::string str_of_operations = "";
    for (std::string i : operations)
    {
        str_of_operations += i;
    }
    std::vector<std::string> values;
    values = operation_parser(str_of_operations);
    for (size_t i = 0; i < values.size(); i++)
    {
        for (NUMBER *name : number_list)
        {
            if (name->get_name() == values[i])
            {
                values[i] = std::to_string(name->get_value());
            }
        }
        for (char c : values[i])
        {
            if ((isdigit(c) == 0) && (c != '+') && (c != '-') && (c != '*'))
            {
                return NULL;
            }
        }
    }

    bool prev_operator = false;
    int temp;
    for (size_t i = 0; i < values.size(); i++)
    {
        if (values[i] == "+" || values[i] == "*" || values[i] == "-")
        {
            if (prev_operator)
            {
                return NULL;
            }
            prev_operator = true;
        }
        else
        {
            prev_operator = false;
        }
    }

    size_t i = 0;
    if (values[0] == "*" || values[values.size() - 1] == "*")
    {
        return NULL;
    }
    else
    {
        while (i < values.size() - 1)
        {

            if (values[i] == "*")
            {
                temp = stoi(values[i - 1]) * stoi(values[i + 1]);
                values[i] = std::to_string(temp);
                values.erase(values.begin() + (i - 1));
                values.erase(values.begin() + (i));
                i = i - 2;
            }
            i++;
        }
    }

    size_t j = 0;
    while (j < values.size() - 1)
    {
        if (values[j] == "+" || values[j] == "-")
        {

            if (values[j] == "+")
            {

                temp = stoi(values[j - 1]) + stoi(values[j + 1]);
                values[j] = std::to_string(temp);
                values.erase(values.begin() + (j - 1));
                values.erase(values.begin() + (j));
                j = j - 1;
            }
            else if (values[j] == "-")
            {
                temp = stoi(values[j - 1]) - stoi(values[j + 1]);
                values[j] = std::to_string(temp);
                values.erase(values.begin() + (j - 1));
                values.erase(values.begin() + (j));
                j = j - 1;
            }
        }
        j++;
    }

    return stoi(values[0]);
}
std::vector<std::string> MyManager::operation_parser(std::string str_of_operations)
{
    std::string temp = "";
    std::vector<std::string> parsed;
    for (size_t i = 0; i < str_of_operations.size(); i++)
    {
        if (str_of_operations[i] != operators[0] && str_of_operations[i] != operators[1] && str_of_operations[i] != operators[2])
        {
            temp += str_of_operations[i];
            if (i == str_of_operations.size() - 1)
            {
                parsed.push_back(temp);
            }
        }

        else
        {
            if (temp != "")
            {
                parsed.push_back(temp);
                std::string oper;
                oper.push_back(str_of_operations[i]);
                parsed.push_back(oper);
                oper = "";
                temp = "";
            }
        }
    }

    return parsed;
}