#include <iostream>
#include <string>
#include "game.h"

#define NBCOL 8

using namespace std;

Game::Game()
    :turn(White)
    {
        chessboard= new Chessboard;
    }


Game::~Game()
{
    delete chessboard;
}

void Game::print() {
    chessboard->print();
}

void display_message_or_not(std::string s, bool b){
    if(b==true){
        cerr<<s<<endl;
    }
}

void Game::next_turn(){
    if(turn==Black){
        turn=White;
    }
    else if (turn==White){
        turn=Black;
    }
}

bool Game::is_in_check(Chessboard* chessboard, Color turn){
    string s;
    if (turn==Black){
        s="\u265A";
    }
    if (turn==White){
        s="\u2654";
    }
    int x,y;
    bool king=false;

    // Get position of the king
    for(int k=0; k<NBCOL; k++){
        for(int i=0; i<NBCOL; i++){
            if(chessboard->get_piece(k,i)!=nullptr){
                if(chessboard->get_piece(k,i)->get_name()==s ){
                y=k;
                x=i;
                king=true;
                }
            }
        }
    }

    // If no more king (can happen during checkmate), return true
    if(king==false){
        return true;
    }
    

    // When we find a piece that can reach the king, return true
    // Otherwise, return false

    for(int k=0; k<NBCOL; k++){
        for(int i=0; i<NBCOL; i++){
            if(chessboard->get_piece(k,i)!=nullptr){
                if (is_valid(Square(k,i), Square(y,x), false)==true ){
                    if (chessboard->get_piece(k,i)->get_color()!=turn&&chessboard->get_piece(k,i)->is_legal(Square(y,x))){
                        return true;
                    }
                }
            }       
        }
    }
    return false;
}


bool Game::is_in_checkmate(Chessboard * chessboard, Color turn){
    // If no check, no checkmate
    if(!(is_in_check(chessboard, turn))){
        return false;
    }

    // We test all possibilities of moves on the chessboard (8^4)
    // If after one of them, there is no more check, false
    // Otherwise true
    for(int k=0; k<NBCOL; k++){
        for(int i=0; i<NBCOL; i++){
            if(chessboard->get_piece(k,i)!=nullptr){
                for(int y=0; y<NBCOL; y++){
                    for(int x=0; x<NBCOL; x++){
                        Chessboard *chessboard2=new Chessboard(chessboard);

                        if (is_valid(Square(k,i), Square(y,x), false)==true ){

                            if (chessboard->get_piece(k,i)->get_color()==turn&&chessboard->get_piece(k,i)->is_legal(Square(y,x))){
                                chessboard2->move(Square(k,i).to_string()+Square(y,x).to_string());
                                if(!is_in_check(chessboard2, turn)){
                                    delete chessboard2;  
                                    chessboard->get_piece(k,i)->print();
                                    cout<<k<<i<<"to"<<x<<y; 
                                    return false;
                                }
                            }
                        }
                        delete chessboard2;                       
                    }
                }
            }       
        }
    }   
     
    return true;
}




bool Game::stalemate(Chessboard * chessboard, Color turn){
    // If in check, false
    if((is_in_check(chessboard, turn))){
        return false;
    }

    // We test all the moves for all pieces
    // If one of them is possible, return false, otherwise return true.
    for(int k=0; k<NBCOL; k++){
        for(int i=0; i<NBCOL; i++){

            if(chessboard->get_piece(k,i)!=nullptr){
                for(int y=0; y<NBCOL; y++){
                    for(int x=0; x<NBCOL; x++){
                        Chessboard *chessboard2=new Chessboard(chessboard);

                        if (is_valid(Square(k,i), Square(y,x), false)==true ){

                            if (chessboard->get_piece(k,i)->get_color()!=turn
                                        &&chessboard->get_piece(k,i)->is_legal(Square(y,x))){
                                chessboard2->move(Square(k,i).to_string()+Square(x,y).to_string());
                                delete chessboard2;
                                
                                return false;
                                
                            }                    
                        }
                    delete chessboard2;                        
                    }
                }
            }       
        }
    }   
     
    return true;
}




 

bool Game::is_valid(Square origin,Square destination, bool with_message){

    Piece *piece=chessboard->get_piece(origin.get_row(), origin.get_col());
    if (piece==nullptr){
        return false;
    }
    string s=piece->get_name();
    int y1=origin.get_row();
    int y2=destination.get_row();
    int x1=origin.get_col();
    int x2=destination.get_col();


    if (s=="\u2659"||s=="\u265F"){ //pawn
        if (piece->get_color()==White){
            if(y2==y1+1 && (x2==x1+1 || x2==x1-1)){
                             
                

                if (chessboard->get_piece(y2,x2)!=nullptr ){
                    return true;                                                                           
                }
                else {
                     
                    if (chessboard->get_piece(y1,x2)!=nullptr 
                            && chessboard->get_piece(y1,x2)->get_nb_moves()==1
                            && last_moved_piece==chessboard->get_piece(y1,x2)){

                        if(chessboard->get_piece(y1,x2)->get_name()=="\u265F"){
                            chessboard->delete_piece(y1,x2);
                            return true;
                        }                                                                          
                    }
                }
                return false;
                
            }
            if(x2==x1+1 && y2==y1){
                if (chessboard->get_piece(y2,x2)!=nullptr){
                   return(false);                                       
                }
            }
            if(x2==x1+2 && y2==y1){
                if (chessboard->get_piece(y2,x2)!=nullptr 
                        && chessboard->get_piece(y2,x2-1)!=nullptr){
                   return(false);                                       
                }
            }



        }

        else if (piece->get_color()==Black){
            if(y2==y1-1 && (x2==x1+1 || x2==x1-1)){
                if (chessboard->get_piece(y2,x2)!=nullptr){
                    return true;
                }
                else {
                       

                    if (chessboard->get_piece(y1,x2)!=nullptr){
                        if(chessboard->get_piece(y1,x2)->get_name()=="\u265E"){
                            chessboard->delete_piece(y1,x2);

                            return true;
                        }                                                                          
                    }
                }
                return false;
            }
        
            if(x2==x1-1 && y2==y1){
                if (chessboard->get_piece(y2,x2)!=nullptr){
                   return(false);                                       
                }
            }
            if(x2==x1-2 && y2==y1){
                if (chessboard->get_piece(y2,x2)!=nullptr ||    
                        chessboard->get_piece(y2,x2+1)!=nullptr){
                   return(false);                                       
                }
            }
        }

    }

    

    else if (s!="\u2658" || s!="\u265E"){
        if((x2-x1)==(y2-y1) && (x2-x1)>0){
            for (int k=1;k<x2-x1; k++){
                if (chessboard->get_piece(y1+k,x1+k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if((x2-x1)==(y2-y1) && (x2-x1)<0){
            for (int k=1;k<x1-x2; k++){
                if (chessboard->get_piece(y1-k,x1-k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if((x2-x1)==-(y2-y1) && (x2-x1)>0 ){
            for (int k=1;k<x2-x1; k++){
                if (chessboard->get_piece(y1-k,x1+k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if((x2-x1)==-(y2-y1) && (x2-x1)<0){
            for (int k=1;k<x1-x2; k++){
                if (chessboard->get_piece(y1+k,x1-k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }


        if(x2==x1 && (y2-y1)>0){
            for (int k=1;k<y2-y1; k++){
                if (chessboard->get_piece(y1+k,x1)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if(x2==x1 && (y2-y1)<0){
            for (int k=1;k<y1-y2; k++){
                if (chessboard->get_piece(y1-k,x1)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if(y2==y1 && (x2-x1)>0){
            for (int k=1;k<x2-x1; k++){
                if (chessboard->get_piece(y1,x1+k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }
        if(y2==y1 && (x2-x1)<0){
            for (int k=1;k<x1-x2; k++){
                if (chessboard->get_piece(y1,x1-k)!=nullptr){
                    
                    display_message_or_not("This piece can not go over another",with_message);
                    return(false);
                }
                
            }
        }

    }

    return true;



    
    
    
    
}


bool Game::move(){

    string move;


    bool is_notation_valid=false;

    while(!(is_notation_valid)){

        bool check=is_in_check(chessboard, turn);
        if(check){
            cout <<"You are in check"<<endl;
        }
        cout << "Input your move ";
        if(turn==0){
            cout <<"black player";
        }
        if (turn==1){
            cout << "white player";
        }

        cout << endl;
            


        cin >> move;

        if(move=="/quit"){
            return true;

        }

   



        else if (move=="O-O-O"){

            if (turn==White){
                if(chessboard->get_piece(0,4)!=nullptr && chessboard->get_piece(0,0)!=nullptr){

                    if(chessboard->get_piece(0,4)->get_name()=="\u2654" 
                            && chessboard->get_piece(0,4)->get_nb_moves()==0 ){
                        
                        if(chessboard->get_piece(0,0)->get_name()=="\u2656" 
                                && chessboard->get_piece(0,0)->get_nb_moves()==0 ){
                            
                            if(chessboard->get_piece(0,1)==nullptr &&chessboard->get_piece(0,2)==nullptr
                                    && chessboard->get_piece(0,3)==nullptr){
                            
                                chessboard->place_piece(chessboard->get_piece(0,0),Square(0,2));
                                chessboard->place_piece(chessboard->get_piece(0,4),Square(0,1));  
                                is_notation_valid=true;                    
                            }
                        }

                    }
                }
            }
            if(turn==Black){
                if(chessboard->get_piece(7,4)!=nullptr && chessboard->get_piece(7,0)!=nullptr){
            
                    if(chessboard->get_piece(7,4)->get_name()=="\u265A"  
                            && chessboard->get_piece(7,4)->get_nb_moves()==0 ){
                        
                        if(chessboard->get_piece(7,0)->get_name()== "\u265C" 
                                && chessboard->get_piece(7,0)->get_nb_moves()==0 ){

                            if(chessboard->get_piece(7,1)==nullptr
                                    &&chessboard->get_piece(7,2)==nullptr&& chessboard->get_piece(7,3)==nullptr){

                                chessboard->place_piece(chessboard->get_piece(7,0),Square(7,2));
                                chessboard->place_piece(chessboard->get_piece(7,4),Square(7,1)); 
                                is_notation_valid=true;                     
                            }
                        }

                    }
                }
            }
        }

        else if (move=="O-O"){
            if (turn==White){
                if(chessboard->get_piece(0,4)!=nullptr && chessboard->get_piece(0,7)!=nullptr){
                    
                    if(chessboard->get_piece(0,4)->get_name()=="\u2654" 
                            && chessboard->get_piece(0,4)->get_nb_moves()==0 ){

                        if(chessboard->get_piece(0,7)->get_name()=="\u2656" 
                                && chessboard->get_piece(0,7)->get_nb_moves()==0 ){
                            
                            if(chessboard->get_piece(0,5)==nullptr &&chessboard->get_piece(0,6)==nullptr){
                                chessboard->place_piece(chessboard->get_piece(0,7),Square(0,5));
                                chessboard->place_piece(chessboard->get_piece(0,4),Square(0,6)); 
                                is_notation_valid=true;          
                            }
                        }

                    }
                }
            }
            if(turn==Black){
                if(chessboard->get_piece(7,4)!=nullptr && chessboard->get_piece(7,7)!=nullptr){

                    if(chessboard->get_piece(7,4)->get_name()=="\u265A" 
                            && chessboard->get_piece(7,4)->get_nb_moves()==0 ){
                        
                        if(chessboard->get_piece(7,7)->get_name()== "\u265C" 
                                && chessboard->get_piece(7,7)->get_nb_moves()==0 ){

                            if(chessboard->get_piece(7,5)==nullptr &&chessboard->get_piece(7,6)==nullptr){

                                chessboard->place_piece(chessboard->get_piece(7,7),Square(7,5));
                                chessboard->place_piece(chessboard->get_piece(7,4),Square(7,6));   
                                is_notation_valid=true;               
                            }
                        }

                    }
                }
            }
        }

        else if (move.length()!=4 || move[0]<'a' || move[0]>'h'|| move[2]<'a' || move[2]>'h'
                || move[1]<'1' || move[1]>'8' || move[3]<'1' || move[3]>'8'
                || (move[0]==move[2] && move[1]==move[3]))  {
            cerr <<"Invalid input";
            cerr<< "(ex:\"a1a2\") or O-O/O-O-O for short and long castle"<<endl;
        }

        

        else{
            Chessboard *chessboard2=new Chessboard(chessboard);


            Square origin(move.substr(0,2));

            Square destination(move.substr(2,2));




            if(chessboard->get_piece(origin.get_row(),origin.get_col())==nullptr){
                cerr << "Error: the origin square is empty"<<endl;
            }

            else if (chessboard->get_piece(origin.get_row(),origin.get_col())!=nullptr
                    && chessboard->color_square(origin)!=turn){
                cerr << "Error: this is not your piece"<<endl;   
                
            }

            else{
            

                
                if(check){

                    if(is_valid(origin, destination, true)==true){
                        chessboard2->move(move);
                        
                        if (is_in_check(chessboard2, turn)){
                            cerr << "Error: this move does not get you out of check"<<endl;

                        }  


                        else{
                            chessboard->move(move);
                            last_moved_piece=chessboard->get_piece(origin.get_row(),origin.get_col()); 
                            is_notation_valid=true;                       
                        }

                    }
       

                }


                else if (chessboard->get_piece(origin.get_row(),origin.get_col())!=nullptr){ 
                    if(chessboard->color_square(origin)!=turn){
                        cerr << "Error: this is not your piece"<<endl;  
                    }       
                    else if(is_valid(origin, destination, true)==true ){
                            if (!chessboard->get_piece(origin.get_row(),origin.get_col())->is_legal(destination)){
                                cerr<<"Error: this move is not legal for this piece"<<endl;
                            }
                            else{
                                chessboard2->move(move);
                                if (is_in_check(chessboard2, turn)){
                                    cerr << "Error: this move would put you in check"<<endl;
                                }  
                                else{
                                    last_moved_piece=chessboard->get_piece(origin.get_row(),origin.get_col());

                                    chessboard->move(move);
                                    is_notation_valid=true;   
                                }                    

                            }
                    }
                }




            }

            
            delete chessboard2;
        }


    }



    return false;

     
}




void Game::game() {
    bool b=false;


    
    while (b!=true){


        print();
        if (is_in_checkmate(chessboard, turn)){
            cout<<"Checkmate: player "<<endl;
            if(turn==White){
                cout<<"white win!";
            }
            else{
                cout<<"black win!";
            }
            b=true;
        }
        else if(stalemate(chessboard, turn)){
            cout<<"Stalemate"<<endl;
            b=true;           
        }
        else{
            b=move();
            
            next_turn();
        }
    
    }

    for (int k=0; k<NBCOL;k++){

        for (int j=0; j<NBCOL;j++){
            Piece * p=chessboard->get_piece(k,j);
     
            if (p==nullptr){
                cout<<",";
            }
            else {
                if(p->get_name()==  "\u2656"){
                        cout<<"wR,";
                }
                else if(p->get_name()== "\u2658"){
                        cout<<"wN,";
                }
                else if(p->get_name()== "\u2657"){
                        cout<<"wB,";
                }
                else if(p->get_name()== "\u2655"){
                        cout<<"wQ,";
                }
                else if(p->get_name()==  "\u2654"){
                        cout<<"wK,";
                }
                else if(p->get_name()==  "\u265E"){
                        cout<<"bN,";
                }
                else if(p->get_name()== "\u265D"){
                        cout<<"bB,";
                }
                else if(p->get_name()== "\u265B"){
                        cout<<"bQ,";
                }
                else if(p->get_name()== "\u265A"){
                        cout<<"bK,";
                }
                else if(p->get_name()== "\u265C"){
                        cout<<"bR,";
                }
                else if(p->get_name()== "\u2659"){
                        cout<<"wP,";
                }
                else if(p->get_name()== "\u265F"){
                        cout<<"bP,";
                }
            }

        }
    }

    cout <<endl;

}

