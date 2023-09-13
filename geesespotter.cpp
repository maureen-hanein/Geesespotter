#include "geesespotter_lib.h"
#include <iostream>

char *createBoard(std::size_t xdim, std::size_t ydim){
    int capacity(0);
    capacity = xdim * ydim;
    char *board{new char[capacity]{}};
    for (int i(0); i < capacity; i++){
        board[i]=0;
    }
   return board;

}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for(int i= 0; i< xdim* ydim; i++){
    
        int yloc= i/xdim;
        int xloc= i%xdim;
        if((board[i]& valueMask())==9){
            if(((xloc -1) >=0 )&& ((yloc-1)>=0)) {
                 if((board[xloc-1 + (xdim* (yloc-1))]& valueMask())!=9){
                 ++board[xloc-1 + (xdim* (yloc-1))];
                 }
                 //check top left corner 
            }
             if((yloc-1)>= 0) { 
                if((board[xloc + (xdim* (yloc-1))]& valueMask())!= 9){
               ++board[xloc + (xdim* (yloc-1))];
                }
             }
            if(((xloc+1) <= xdim-1 )&& ((yloc-1)>= 0)) { //check top right 
                if((board[xloc+1 + (xdim* (yloc-1))]& valueMask())!=9){
                ++board[xloc+1 + (xdim* (yloc-1))];
              }
            }
            if((xloc+1) <= xdim-1 ) { //check right side 
            if((board[xloc+1 + (xdim* yloc)]& valueMask())!=9){
                ++board[xloc+1 + (xdim* yloc)];
               }
            }
            if((xloc-1)>= 0){
                if((board[(xloc-1) + (xdim* yloc)] & valueMask())!=9){
                    ++board[(xloc-1) + (xdim* yloc)];
                }
            }
            if(((xloc-1) >=0 )&& (yloc+1 <= ydim-1)) { //check bottom left
                    if((board[xloc-1 + (xdim* (yloc+1))]& valueMask())!=9){
                    ++board[xloc-1 + (xdim* (yloc+1))];
                 }
            }
            if((yloc+1) <= (ydim-1)){
                if((board[xloc + (xdim* (yloc+1))]& valueMask())!=9){
                    ++board[xloc + (xdim* (yloc+1))];
                    //check bottom row
                  } 
            }
        
            if(((xloc +1) <= xdim-1 )&& (yloc+1 <= ydim -1)) { //check bottom right 
                    if((board[xloc+1 + (xdim* (yloc+1))]& valueMask())!=9){
                    ++board[xloc+1 + (xdim* (yloc+1))];
                   }
            }
                
        }
    }
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
for(int i= 0; i< xdim* ydim; i++){
board[i] |= hiddenBit();
 }
}

void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(int i=0; i< xdim * ydim; i++ ){
if (board[i]&markedBit()){
    std::cout<< 'M';
} 
else if(board[i]&hiddenBit()){
    std::cout<< '*';
}
else{
    std::cout<< (board[i]&valueMask());
} 

if((i+1)%(xdim)==0){
    std::cout << std::endl;
}
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int x = xloc;
    int y = yloc;
    int i= x + (xdim* y);

        if(board[i] & markedBit()){
            return 1;
        }
        else if((board[i]& hiddenBit()) != hiddenBit()){
            return 2;
        }
        else if ((board[i]& valueMask())==9){
            board[i] &=~ hiddenBit();
            return 9;
        }
        else if((board[i] & valueMask())==0){
            board[i] &=~ hiddenBit();
                if(((x -1) >=0 )&& ((y-1)>=0)){
                     board[x-1 + (xdim* (y-1))] &=~ hiddenBit();
                    //check top left corner 
                }
                if((y-1)>= 0) {//check top middle
                    board[x + (xdim* (y-1))]&=~ hiddenBit();
                }
                if(((x+1) <= xdim-1 )&& ((y-1)>= 0)) {
                    //check top right
                    board[x+1 + (xdim* (y-1))]&=~ hiddenBit();
                }
                if((x+1) <= xdim-1 ) { 
                    //check right side 
                    board[x+1 + (xdim* y)] &=~ hiddenBit();
                }
                if((x-1)>= 0){// checking left side?
        
                    board[(x-1) + (xdim* y)]&=~ hiddenBit();
                }
                if(((x-1) >=0 )&& (y+1 <= ydim-1)){
                    //check bottom left
                    board[x-1 + (xdim* (y+1))]&=~ hiddenBit();
                }
                if((yloc +1) <= (ydim-1)){
                    board[x + (xdim* (y+1))]&=~ hiddenBit();
                    //check bottom row
                } 
                if(((x +1) <= xdim-1 )&& (y+1 <= ydim -1)){ 
                    //check bottom right 
                    board[x+1 + (xdim* (y+1))]&=~ hiddenBit();
                }
        
                return 0;
            }
        
        else{ 
            board[i]&= valueMask();
        }
        return 0;
    }


int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    int m{0};
    m = xloc + (xdim* yloc);
    if( (!(board[m]&hiddenBit()))){
        return 2;
    }
    else {
       if(!(board[m] & markedBit())){
        board[m] |= markedBit();
       }
       else {
        board[m] ^= markedBit();
       }
       return 0;
    }
   
}


bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    for(int i=0; i < xdim *ydim; i++){
    if(((board[i]& valueMask()) != 9) && (board[i]& hiddenBit())== hiddenBit()){
        return false;
    }
 }
    return true;

 }
