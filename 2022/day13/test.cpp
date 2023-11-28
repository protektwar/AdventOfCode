#include <iostream>
#include <variant>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

struct Value;
struct Value{
    std::variant<int, std::vector<Value>> value;
};

std::string fromValue(Value value)
{
    if (std::holds_alternative<int>(value.value)){
        return std::to_string(std::get<int>(value.value));
    }
    auto vector = std::get<std::vector<Value>>(value.value);
    if (vector.empty()){
        return "[]";
    }
    std::string text = "[" + fromValue(vector.at(0));
    for (int i = 1; i < vector.size(); i++) {
        text += "," + fromValue(vector.at(i));
    }
    return text + "]";
}

int main(void)
{
    {
//    std::variant<int, std::vector<Value>> value; 
    std::variant<int, std::string> value; 
    value = 1;
//    std::cout << value << "\n";
    if (std::holds_alternative<int>(value)) {
        std::cout << std::get<int>(value) << "\n";
    }
    value = "abcd";
    if (std::holds_alternative<std::string>(value)) {
        std::cout << std::get<std::string>(value) << "\n";
    }
    }
    Value value{std::vector<Value>{{1}}}; //-> [1]
    Value value1{1};
    Value value2{std::vector<Value>{std::vector<Value>{{1}}}};
    

    std::cout << fromValue(value2)<< std::endl;
    return 1;
}
