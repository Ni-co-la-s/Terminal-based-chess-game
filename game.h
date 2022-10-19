#pragma once
#include <iostream>
#include <string>
#include "chessboard.h"

/**
 * @brief Handle all aspects of the game.
 * Has methods to instantiate and finish the game.
 **/
class Game
{
public:
	Game();
    ~Game();
    
    /**
     * @brief Handle the game from beginning to stopping conditions.
     * 
     **/
    void game() ; 
    /**
     * @brief Switch the argument turn from Black to White or vice-versa.
     **/
    void next_turn() ;
    /**
     * @brief Display the chessboard.
     **/
    void print() ;
    
    /**
     * @brief Test whether a move is valid in the context of the game.
 	 * @param origin origin square
 	 * @param destination destination square
 	 * @param with_message if true, print the error message, does not otherwise
 	 * @return true if the move is valid, false otherwise
	 **/
    bool is_valid(Square origin,Square destination, bool with_message);
    
    /**
     * @brief Test if the player specified in parameter is in check.
 	 * @param chessboard chessboard to test
 	 * @param turn player who has the current move
 	 * @return true if he is in check, false otherwise
	 **/
    bool is_in_check(Chessboard* chessboard, Color player);
    
    /**
     * @brief Test if the player specified in parameter is in checkmate.
 	 * @param chessboard chessboard to test
 	 * @param turn player who has the current move
 	 * @return true if he is in checkmate, false otherwise
	 **/
    bool is_in_checkmate(Chessboard * chessboard, Color turn);

    /**
     * @brief Handle the move input from the player, then the move.
	 **/ 
    bool move();

    /**
     * @brief Test if it is a stalemate.
 	 * @param chessboard chessboard to test
 	 * @param turn player who has the current move
 	 * @return true if there is a stalemate, false otherwise
	 **/
    bool stalemate(Chessboard * chessboard, Color turn);

private:
    /** @brief game chessboard **/
	Chessboard *chessboard;
    /** @brief player who has the current move **/
    Color turn;
    /** @brief last piece having been moved **/
    Piece * last_moved_piece;

};

/**
 * @brief if b=true, display the string, otherwise does not.
 * @param s string to print
 * @param b boolean
 **/ 
void display_message_or_not(std::string s, bool b);
