#pragma once
#include <iostream>
#include <string>
#include "color.h"
#include "square.h"

/**
 * @brief Abstract class representing the common traits of pieces
 **/
class Piece
{


    
public:


	Piece(const Color& color, const std::string& name,  const Square& position);
    virtual ~Piece(){}

    /**
     * @brief Get the name of the piece (in ASCII)
     **/
    std::string get_name();  

    /**
     * @brief Get the position of the piece
     **/
    Square get_pos();

    /**
     * @brief Get the color of the piece
     **/
    Color get_color();

    /**
     * @brief Get the number of moves having been made by the piece
     **/
    int get_nb_moves();

    /**
     * @brief Set the position of the piece
     **/
    void set_pos(Square pos);

    /**
     * @brief Increment the number of moves made by the piece
     **/
    void incr_nb_moves() ;

    /**
     * @brief Set the number of moves made by the piece
     **/
    void set_nb_moves(int nb) ;

    /**
     * @brief Set the color of the piece
     **/
    void set_couleur(Color c);

    /**
     * @brief Set the name of the piece
     **/  
    void set_nom(std::string s);

    /**
     * @brief Display the name of the piece
     **/
    void print();

    /**
     * @brief Abstract method testing if a move is legal
     **/
    virtual bool is_legal (Square dest) const=0;

protected:

    /** @brief color of the piece **/
    Color color;
    /** @brief name of the piece (in ASCII) **/
	std::string name;
    /** @brief current position of the piece **/
    Square position;
    /** @brief number of moves already made by the piece **/
    int nb_moves;

	



};


/**
 * @brief Class representing a king.
 **/
class King  : public Piece
{
public: 
    King( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};

/**
 * @brief Class representing a queen.
 **/
class Queen  : public Piece
{
public: 
    Queen( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};

/**
 * @brief Class representing a bishop.
 **/
class Bishop  : public Piece
{
public: 
    Bishop( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};

/**
 * @brief Class representing a rook.
 **/
class Rook  : public Piece
{
public: 
    Rook( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};

/**
 * @brief Class representing a pawn.
 **/
class Pawn  : public Piece
{
public: 
    Pawn( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};

/**
 * @brief Class representing a knight.
 **/
class Knight  : public Piece
{
public: 
    Knight( const Color& color, const std::string& name, const Square& position )
    : Piece(color, name, position)
    {}

    bool is_legal(Square dest) const override;

};