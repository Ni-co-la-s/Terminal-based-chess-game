#include <iostream>
#include <string>
#include "chessboard.h"

using namespace std;
#define NBCOL 8

Chessboard::Chessboard () 
{ 
    // Allocation of the chessboard
    chessboard=new Piece**[NBCOL];

    for (int i=0; i<NBCOL;i++){
            chessboard[i]=new Piece*[NBCOL];
    }

    for (int i=0; i<NBCOL; i++){
        for (int j=0; j<NBCOL; j++){
             chessboard[i][j]= nullptr;        
        }
    }

 
    // Allocation of the major and minor pieces
    chessboard[0][0] = new Rook    (White,"\u2656",  Square(0,0));
    chessboard[0][1] = new Knight(White,"\u2658",  Square(0,1));
    chessboard[0][2] = new Bishop     (White,"\u2657",  Square(0,2));
    chessboard[0][3] = new Queen   (White,"\u2655",  Square(0,3));
    chessboard[0][4] = new King     (White,"\u2654",  Square(0,4));
    chessboard[0][5] = new Bishop     (White,"\u2657",  Square(0,5));
    chessboard[0][6] = new Knight(White,"\u2658",  Square(0,6));
    chessboard[0][7] = new Rook    (White,"\u2656",  Square(0,7));
    chessboard[7][0] = new Rook    (Black, "\u265C",  Square(7,0));
    chessboard[7][1] = new Knight(Black, "\u265E",  Square(7,1));
    chessboard[7][2] = new Bishop     (Black, "\u265D",  Square(7,2));
    chessboard[7][3] = new Queen   (Black, "\u265B",  Square(7,3));
    chessboard[7][4] = new King     (Black, "\u265A",  Square(7,4));
    chessboard[7][5] = new Bishop     (Black, "\u265D",  Square(7,5));
    chessboard[7][6] = new Knight(Black, "\u265E",  Square(7,6));
    chessboard[7][7] = new Rook    (Black, "\u265C",  Square(7,7));

    // Allocation of the pawns
    for (unsigned int i(0);i<NBCOL;i++) {
         chessboard[1][i] =  new Pawn(White, "\u2659", Square(1,i));
         chessboard[6][i] =  new Pawn(Black,  "\u265F", Square(6,i));
    }
    


}


Chessboard::Chessboard (Chessboard * chessboard2){

    // Allocation of the chessboard
    chessboard=new Piece**[NBCOL];

    for (int i=0; i<NBCOL;i++){
            chessboard[i]=new Piece*[NBCOL];
    }

    for (int i=0; i<NBCOL; i++){
        for (int j=0; j<NBCOL; j++){
             chessboard[i][j]= nullptr;        
        }
    }


    // Copie of the pieces one by one
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
             Piece * p=chessboard2->get_piece(i,j);
             
            if(p!=nullptr){
                if(p->get_name()==  "\u2656"){
                        chessboard[i][j] = new Rook    (White,"\u2656",  Square(i,j));
                }
                else if(p->get_name()== "\u2658"){
                        chessboard[i][j] = new Knight(White,"\u2658",  Square(i,j));
                }
                else if(p->get_name()== "\u2657"){
                        chessboard[i][j] = new Bishop     (White,"\u2657",  Square(i,j));
                }
                else if(p->get_name()== "\u2655"){
                        chessboard[i][j] = new Queen   (White,"\u2655",  Square(i,j));
                }
                else if(p->get_name()==  "\u2654"){
                        chessboard[i][j] = new King     (White,"\u2654",  Square(i,j));
                }

                else if(p->get_name()==  "\u265E"){
                        chessboard[i][j] = new Knight(Black, "\u265E",  Square(i,j));
                }
                else if(p->get_name()== "\u265D"){
                        chessboard[i][j] = new Bishop     (Black, "\u265D",  Square(i,j));
                }
                else if(p->get_name()== "\u265B"){
                        chessboard[i][j] = new Queen   (Black, "\u265B",  Square(i,j));
                }
                else if(p->get_name()== "\u265A"){
                        chessboard[i][j] = new King     (Black, "\u265A",  Square(i,j));
                }
                else if(p->get_name()== "\u265C"){
                        chessboard[i][j] = new Rook    (Black, "\u265C",  Square(i,j));
                }
                else if(p->get_name()== "\u2659"){
                        chessboard[i][j] =  new Pawn(White, "\u2659", Square(i,j));
                }
                else if(p->get_name()== "\u265F"){
                        chessboard[i][j] =  new Pawn(Black,  "\u265F", Square(i,j));
                }

                

             }


        }
    }
 

}



Chessboard::~Chessboard(){
    // Deallocation of the chessboard
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
             delete chessboard[i][j];        
        }
        delete[](chessboard[i]);
    }
    delete[](chessboard);

}



bool  Chessboard::is_square_empty(Square const & square) const{
    
    if (chessboard[square.get_row()][square.get_col()]!=nullptr){
            return false;
    }
    return true;

}


bool Chessboard::test_place_piece(Piece * piece, Square const & square) const{
      
     
      // 1- if the square is empty
      if (is_square_empty(square)) {
              place_piece(piece,square);
              return true;
      }
      else {
            Piece *content_square = chessboard[square.get_row()][square.get_col()];
             // 2- if the square has an opposite piece
            if (content_square->get_color() != piece->get_color()) {
                place_piece(piece,square);

                return true;
              }
              else {
                  return false;
              }
        }

        return true;
}

void Chessboard::place_piece(Piece * piece, Square const & square) const {
        // Delete the existinf piece and put the new one
        delete chessboard[square.get_row()][square.get_col()];
        chessboard[square.get_row()][square.get_col()]=piece;
        chessboard[piece->get_pos().get_row()][piece->get_pos().get_col()]=nullptr;
        // Update the attributes of the piece
        piece->set_pos(square);
        piece->incr_nb_moves();

}


void Chessboard::print () const {

        string space5 = string(5,' ');
        cout << endl;
        cout << "     a     b     c     d     e     f     g     h    "<< endl;
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        for (int i(NBCOL-1);i>=0;i--) {
                cout << i+1 << " ";
                for (int j(0);j<NBCOL;j++) {
                        cout << "|" ;
                        if (chessboard[i][j]) { 
                          cout << "\u0020\u0020"; 
                          chessboard[i][j]-> print();
                          cout << "\u0020" << " ";
                        }
                        else 
                                cout << space5; 
                }
                cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
                cout << endl;
        }
}


bool Chessboard::move (string move_to_test ) const{
        Square origin(move_to_test.substr(0,2));
        Square destination(move_to_test.substr(2,2));
        // If origin square is empty, return false
        if(is_square_empty(origin)){
                return false;
        }
        // If move is legal
        else if(chessboard[origin.get_row()][origin.get_col()]->is_legal(destination) ){
                if (test_place_piece(chessboard[origin.get_row()][origin.get_col()], destination)==true){     
                        return true;                    
                }
        }

        return false;
                
}

Color Chessboard::color_square(Square const & square) const{
        return chessboard[square.get_row()][square.get_col()]->get_color();
}

Piece *Chessboard::get_piece(int i, int j){
        return chessboard[i][j];
}

void Chessboard::delete_piece(int i, int j){
        delete chessboard[i][j];
        chessboard[i][j]=nullptr;
}
