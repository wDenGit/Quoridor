#include "board.hpp"


#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

/*****************
 *      Case     *
 *****************/



Case::Case(int type, int x, int y){
    if (type == wall)
        caseType = wall;
    else if (type == pawn)
        caseType = pawn;
    pos.x = x;
    pos.y = y;
}

int Case::getPlayer_1(){
    if(!(entity == nullptr)){
        return entity->getPlayer();
    }
    return 0;
}

void Case::put(shared_ptr<Entity> newEntity) {
    entity = newEntity;
}


/*****************
 *     Board     *
 *****************/

// private methods
void Board::initializeNeighbors() {
    for (int x=0; x<((size*2)-1); x = x+2)
        for (int y=0; y<((size*2)-1); y = y+2) {
            // creer le vecteur de voisin des cases jouables
            vector<shared_ptr<Case>> newPawnCaseNeighbors;
            for (auto &shift: vector<Point>({
            {-2, 0},    // Nord
            {0, 2},     // Est
            {2, 0},     // Sud
            {0, -2},    // Ouest
            })) {
                int neighborx = x+shift.x;
                int neighbory = y+shift.y;
                if (neighborx >= 0 &&   // check if incide in range
                    neighborx < ((size*2)-1) &&
                    neighbory >= 0 &&
                    neighbory < ((size*2)-1))
                        newPawnCaseNeighbors.push_back(board[neighborx][neighbory]);
            }
            board[x][y]->setPawnNeighbors(newPawnCaseNeighbors);

            // creer le vecteur de voisin des cases jouables
            vector<shared_ptr<Case>> newWallCaseNeighbors;
            for (auto &shift: vector<Point>({
            {-1, 0},    // Nord
            {0, 1},     // Est
            {1, 0},     // Sud
            {0, -1},    // Ouest
            })) {
                int neighborx = x+shift.x;
                int neighbory = y+shift.y;
                if (neighborx >= 0 &&   // check if incide in range
                    neighborx < ((size*2)-1) &&
                    neighbory >= 0 &&
                    neighbory < ((size*2)-1))
                        newWallCaseNeighbors.push_back(board[neighborx][neighbory]);
            }
            board[x][y]->setWallNeighbors(newWallCaseNeighbors);
        }
}

Board::Board(int caseNumber): size{caseNumber} {
    for (int i=0; i < ((size*2)-1); i++) {
        board.push_back({});
        for(int j=0; j < ((size*2)-1); j++) {
            if(j%2==0 && i%2==0)
                board[i].push_back(make_shared<Case>(Case::pawn, i, j));
            else
                board[i].push_back(make_shared<Case>(Case::wall, i, j));
        }
    }
    initializeNeighbors();
}
        
bool Board::checkEmptyCase(Point pos) const {
    return this->board[pos.x][pos.y]->isEmpty();
}

bool Board::checkCaseType(Point pos) const {
    return this->board[pos.x][pos.y]->isPawnCase();
}

int Board::checkWinner(){
    int winner = -1;
    vector<int> pos_to_win = {16, 0, 16, 0};
    int board_size = this->getSize();
    for(int i = 0; i < 4; i++){
        if(i == 0 || i == 1){
            for(int j = 0; j < board_size; j+=2){
                //if(i == 0 || i == 1)
                if(!(this->board[pos_to_win[i]][j]->isEmpty())){
                    int ifPlayer = this->board[pos_to_win[i]][j]->getPlayer_1();
                //else if(i == 2 || i == 3)
                //if(!(this->board[j][pos_to_win[i]].isEmpty())){
                //  int ifPlayer = this->board[j][pos_to_win[i]].getPlayer_1();                            --> try for better code
                    if(ifPlayer == (i)){
                        winner = ifPlayer;

                        return winner;
                    }                   
                }
            }
        }
        else if(i == 2 || i == 3){
            for(int j = 0; j < board_size; j+=2){                
                if(!(this->board[j][pos_to_win[i]]->isEmpty())){
                    int ifPlayer = this->board[j][pos_to_win[i]]->getPlayer_1();

                    if(ifPlayer == (i)){
                        winner = ifPlayer;
                        return winner;
                    }                   
                }
            }
        }
    }
    return winner;
}

void Board::putWall(shared_ptr<Wall> newWall, Point pos1, Point pos2, Point pos3) {
    assert((! this->board[pos1.x][pos1.y]->isPawnCase()) && (! this->board[pos2.x][pos2.y]->isPawnCase()) && (! this->board[pos3.x][pos3.y]->isPawnCase()));
    this->board[pos1.x][pos1.y]->put(newWall);
    this->board[pos2.x][pos2.y]->put(newWall);
    this->board[pos3.x][pos3.y]->put(newWall);
}

void Board::putPawn(shared_ptr<Pawn> newPawn, Point pos) {
    assert(this->board[pos.x][pos.y]->isPawnCase());
    this->board[pos.x][pos.y]->put(newPawn);
    newPawn->setPos(pos);
    int player = newPawn->getPlayer();
    this->pawns[player] = pos;
}

void Board::removePawn(Point p_pawn){
    //Test temp for only one player...
    this->board[p_pawn.x][p_pawn.y]->setEmpty();
}

        
shared_ptr<Case> Board::getCase(Point pos){
    /*
    Getter for the case object
    Args:
        - Point pos: The position of the wanted case
        - return board[pos.x][pos.y]: The case object
    */
    return this->board[pos.x][pos.y];
}

void Board::removeWall(Point pos1, Point pos2, Point pos3)
{
    this->board[pos1.x][pos1.y]->setEmpty();
    this->board[pos2.x][pos2.y]->setEmpty();
    this->board[pos3.x][pos3.y]->setEmpty();
}
