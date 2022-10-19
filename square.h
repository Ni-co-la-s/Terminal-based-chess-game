#pragma once
#include <iostream>
#include <string>


/**
 * @brief Represent a square of the hessboard
 **/
class Square
{
public:
    /** @brief Constructor from coordinates **/
	Square(const int& y, const int& x);
    /** @brief Constructor from algebraic notations **/
	Square(std::string str);
	~Square(){}

    /**
     * @brief Convert the square to algebraic notations
	 **/
	std::string to_string() const;

    /**
     * @brief Get the row
	 **/
	int get_row() const;
    
	/**
     * @brief Get the column
	 **/
	int get_col() const;

private:
/** @brief row on the chessboard **/
	int y;
/** @brief column on the chessboard **/
	int x;

};