#pragma once
#include <iostream>
#include <string>
#include "piece.h"


/**
 * @brief Represent a chessboard.
 **/
class Chessboard
{
public:

	Chessboard();

    /** @brief Copie constructor **/
    Chessboard( Chessboard *chessboard2);
    ~Chessboard();

    /**
     * @brief Display the chessboard.
     **/
    void print () const; 

    /**
     * @brief Do the move passed in parameters, if possible. 
 	 * @param move_to_test move to test (concatenation of origin square and destination or "O-O"/"O-O-O")
 	 * @return true if the move was made, false otherwise
	 **/
    bool move (std::string move_to_test ) const;

    /**
     * @brief Test whether the piece can be put at the square specified.
 	 * @param piece piece to put
 	 * @param square square on which to put the piece
 	 * @return true if the piece can be placed, false otherwise
	 **/
    bool test_place_piece(Piece * piece, Square const & square) const;

    /**
     * @brief Place the piece at the specified square.
 	 * @param piece piece to put
 	 * @param square square on which to put the piece
	 **/
    void place_piece(Piece * piece, Square const & square) const ;

    /**
     * @brief Test whether the square is empty.
 	 * @param square square to test
 	 * @return true if the square is empty, false otherwise
	 **/
    bool is_square_empty(Square const & square) const;
    
    /**
     * @brief Get a piece on the chessboard.
 	 * @param i row
 	 * @param j column
 	 * @return the piece at these coordinates
	 **/
    Piece* get_piece(int i,int j);

    /**
     * @brief Delete a piece on the chessboard.
 	 * @param i row
 	 * @param j column
	 **/
    void delete_piece(int i, int j);

    /**
     * @brief Color of the piece on the square, if it exists.
 	 * @param square square on the chessboard
 	 * @return color of the piece at this position
	 **/
    Color color_square(Square const & square) const;
	

private:
    /** @brief Chessboard represented as a 2D array of Piece*. **/
	Piece *** chessboard;


};

