#include <iostream>
#include <string>
#include <cmath>
#include "piece.h"
using namespace std;



Piece::Piece(const Color& color, const std::string& name,  const Square& position)
: color(color), name(name), position(position), nb_moves(0)
{}

void Piece::print(){
    cout << name;
}

Square Piece::get_pos(){
    return position;
}

string Piece::get_name(){
    return name;
}
Color Piece::get_color(){
    return color;
}
int Piece::get_nb_moves(){
    return nb_moves;
}

void Piece::set_pos(Square pos){
    position=pos;
}

void Piece::incr_nb_moves() {
    nb_moves++;
}

void Piece::set_nb_moves(int nb) {
    nb_moves=nb;
}

void Piece::set_couleur(Color c){
    color=c;
}

void Piece::set_nom(string s){
    name=s;
}

bool King::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a king
    if( abs(x1-x2)<=1 && abs(y1-y2)<=1){
        return true;
    }



    return false;
    
}

bool Bishop::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a bishop
    if(abs(x1-x2)== abs(y1-y2)){
        return true;
    }

    return false;
    
}



bool Rook::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a rook
    if(x1==x2 || y1==y2){
        return true;
    }

    return false;
    
}

bool Queen::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a queen
    if((x1==x2 || y1==y2) || abs(x1-x2)== abs(y1-y2)){
        return true;
    }

    return false;
    
}

bool Pawn::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a pawn
    if (color==White){    
    
        // Move in diagonal (takes)
        if(x2==x1+1 || x2==x1-1){
            if(y2==y1+1){
                return true;
            }
        }

        // Advance one case
        if(x1==x2 && y2==y1+1 ){
            
            return true;
    
        }
        
        // Advance two cases (if first move)
        if(nb_moves==0 && x1==x2 && y2==y1+2 ){
            
            return true;
        }
    }
    if (color==Black){

        // Move in diagonal (takes)
        if(x2==x1+1 || x2==x1-1){
            if(y2==y1-1){
                return true;
            }
        }
        // Advance one case
        if(x1==x2 && y2==y1-1 ){
            return true;
        }

        // Advance two cases (if first move)
        if(nb_moves==0 && x1==x2 && y2==y1-2 ){
            return true;
        }
    }
    return false;
    
}

bool Knight::is_legal(Square destination) const{
    int y1(position.get_row());
    int x1(position.get_col());
    int y2(destination.get_row());
    int x2(destination.get_col());
    
    // If the square is not on the chessboard, error
    if(x2 <0|| x2>7 || y2<0 || y2>7  ){
        return false; 
    }
    // If the origin and destination squares are identical, error
    if (x1==x2 && y1==y2){
        return false;
    }
    // Test whether the move is legal for a knight
    if( abs((x1-x2)*(y1-y2))==2 ){
        return true;
    }
    return false;
    
}