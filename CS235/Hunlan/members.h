#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
class NUMBER
{
public:
    NUMBER(const std::string &name, const int long long &val);
    NUMBER(const std::string &name);
    ~NUMBER();
    int long long get_value();
    void set_value(const int long long &val);
    std::string get_name();

protected:
    std::string num_name;
    int long long value;
};
class STRING
{
public:
    STRING(const std::string &name, const std::string &str);
    STRING(const std::string &name);
    ~STRING();
    std::string get_name();
    std::string get_message();
    void set_message(const std::string &mess);

protected:
    std::string str_name;
    std::string message;
};
class MyManager
{
public:
    MyManager();
    ~MyManager();
    bool process(std::vector<std::string> commands);
    bool is_keyword(const std::string &first_word);
    bool is_proper_name(const std::string &name);
    bool is_var_name(const std::string &first_word);
    bool is_str_var_name(const std::string &first_word);
    bool is_num_var_name(const std::string &first_word);
    int evaluate_expression(std::vector<std::string> operations);
    void print_val(const std::string &var_name);
    bool is_string_literal(const std::string &str);
    bool is_number_literal(const std::string &num);
    void equal_operator_string(const std::string &orig, const std::string &new_val);
    void equal_operator_number(const std::string &orig, const std::string &new_val);
    std::string evaluate_string(const std::string &str);
    std::vector<std::string> operation_parser(std::string str_of_operations);

protected:
    int counter = 0;
    std::vector<NUMBER *> number_list;
    std::vector<STRING *> string_list;
    std::vector<std::string> keywords{"NUMBER", "STRING", "PRINT"};
    std::vector<char> operators{'+', '*', '-'};
};
class MyParser
{
public:
    MyParser();
    ~MyParser();
    std::vector<std::string> operator()(const std::string &input);

private:
    std::vector<char> separators{' ', '\t'};
};