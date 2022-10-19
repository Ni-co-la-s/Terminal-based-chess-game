#include <iostream>
#include <string>
#include "square.h"

using namespace std;


Square::Square(const int& y, const int& x)
: y(y), x(x)
{}

Square::Square(std::string str)
:y(str[1]-'1'), x(str[0]-'a')		
{}

int Square::get_row() const {
    return y;
}

int Square::get_col() const {
    return x;
}

string Square::to_string() const{
    string xc(1,('a'+x));
    string yc(1,('1'+y));
    string str;
    str=xc+yc;
    return str;
}