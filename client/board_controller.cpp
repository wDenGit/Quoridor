#include "board_controller.hpp"

#include <ctype.h>
#include <cmath> 
#include <bits/stdc++.h>

using namespace std;

bool BoardController::checkMove(shared_ptr<Player> player, string move) {
    vector<Point> parsedMove = moveParser(move);
    // si move vide -> false
    if (parsedMove.size() == 0)    return false;

    // cas d'un déplacement de pion
    if (parsedMove.size() == 1) {
        if (! board->checkCaseType(parsedMove[0]) ) return false;
        shared_ptr<Case> myCase = this->board->getCase(player->getPawn()->getPos());
        vector<shared_ptr<Case>> possible_moves = this->controlMove.checkMovement(myCase);
        for (auto &moves: possible_moves) {
            //cout << "Possible x: " << moves->getPos().x << ", y: " << moves->getPos().y <<endl;
            if (moves->getPos().x == parsedMove[0].x && moves->getPos().y == parsedMove[0].y) // mon coup est possible
                return true;
        }
        // coup pas possible
        return false;
    }

    // cas placement d'un mur
    else {
        if(player->hasWall() && this->checkWall(parsedMove)) {  // verifie que l'on met notre mur sur une case valide
             parsedMove.push_back(this->fillWallPoint(parsedMove));
             if (this->checkPath(parsedMove[0], parsedMove[1], parsedMove[2], make_shared<Wall>()))
                 return true;
             else
                return false;
            return true;
        }
        else {
            return false;
        }
    }
}

void BoardController::makeMove(shared_ptr<Player> player, string move) { 
    /*
    The waitMove method allows the player to write a move in the terminal that is then verified to see if it is valid...
    Args:
        - int player: The player number
    Todo:
        []: Add the missing cases
            -[]: What if parsed size >= 4?
            -[]: return Bool to int pour gérer cas
        
    */
    shared_ptr<Pawn> pion = player->getPawn();
    vector<Point> parsedMove = moveParser(move);
    int parsedSize = parsedMove.size();
    if (parsedSize == 1){
        board->removePawn(pion->getPos());
        board->putPawn(pion, parsedMove[0]);
    }

    else{
        parsedMove.push_back(fillWallPoint(parsedMove));
        board->putWall(player->getWall(), parsedMove[0], parsedMove[1], parsedMove[2]);
    }

}


Point BoardController::stringToPoint(string pos) {
    // Passage du int en string
    Point ret;
    string letter, sNumber;
    if (pos.size() == 2) {
        letter = pos.substr(0,1);
        sNumber = pos.substr(1,2);
    }
    else if(pos.size() == 3) {
        letter = pos.substr(0,1);
        sNumber = pos.substr(1,3);
    }
    ret.y = ( (int) letter[0] ) - 97;
    ret.x = stoi(sNumber) - 1;
    return ret;
}


vector<Point> BoardController::moveParser(string s) {
    // Parse l'input
    vector<string> resString = removeSpace(s);
    vector<Point> resPoint;
    vector<Point> nullPoint;
    int stringSize = s.size();
    if (stringSize <= 1) return nullPoint;
    if (!(resString.size() == 1 || resString.size() == 2)) {
        return nullPoint;
    }
    for (size_t i = 0; i < resString.size(); ++i){
        string letter, number;
        
        if (resString[i].size() == 2){
            letter = resString[i].substr(0,1);
            number = resString[i].substr(1,2);
        }
        else if(resString[i].size() == 3){
            letter = resString[i].substr(0,1);
            number = resString[i].substr(1,3);
        }  
        if (!(checkValideLetter(letter) && checkValideNumber(number))){
            return resPoint;
        }
    }
    
    for (size_t i=0; i < resString.size(); ++i){
        resPoint.push_back(stringToPoint(resString[i]));
    }

    
    return resPoint;
}

bool BoardController::checkWall(vector<Point> wallPoint){
    if ((! checkWallSyntax(wallPoint)) || (! checkWallGoodPos(wallPoint))) return false;
    // si notre murs traverse une case pion
    if (this->board->checkCaseType(this->fillWallPoint(wallPoint))) return false;
    return true;
}
        
// ajoute le 3eme point a notre vecteur de murs

bool BoardController::checkWallSyntax(vector<Point> wallPoint){
    bool res = false;
    if ((abs(wallPoint[0].x - wallPoint[1].x) == 2 )|| (
        (abs(wallPoint[0].y - wallPoint[1].y) == 2))) {
        if ((wallPoint[0].x == wallPoint[1].x) || 
            (wallPoint[0].y == wallPoint[1].y))
                res = true;
    }
    return res;
}

Point BoardController::fillWallPoint(std::vector<Point> wallPoint){
    Point thirdWall;
    if ((wallPoint[0].x - wallPoint[1].x) == 2){
        thirdWall.x = (wallPoint[1].x) + 1;
        thirdWall.y = wallPoint[1].y;
    }
    else if ((wallPoint[1].x - wallPoint[0].x) == 2){
        thirdWall.x = (wallPoint[0].x) + 1;
        thirdWall.y = wallPoint[1].y;
    }
    else if ((wallPoint[0].y - wallPoint[1].y) == 2){
        thirdWall.y = (wallPoint[1].y) + 1;
        thirdWall.x = wallPoint[1].x;
    }
    else if ((wallPoint[1].y - wallPoint[0].y) == 2){
        thirdWall.y = (wallPoint[0].y) + 1;
        thirdWall.x = wallPoint[1].x;
    }
    return thirdWall;
}



bool BoardController::checkWallGoodPos(vector<Point> wallPoint) {   // apres ajoute notre 3 eme point
    // Verification du bon placement des mures
    shared_ptr<Case> wall1Case = board->getCase(wallPoint[0]);
    shared_ptr<Case> wall2Case = board->getCase(wallPoint[1]);

    // si une des 2 case pas vide -> false
    if ((! wall1Case->isEmpty()) || (! wall2Case->isEmpty()))   return false;
    if ((wall1Case->isPawnCase()) || wall2Case->isPawnCase()) return false;
    // verifie que le murs n'est pas sur une bonne pos
    bool res1 = ((wall1Case->getPos()).x % 2 == 1) && ((wall1Case->getPos()).y % 2 == 1);
    bool res2 = ((wall2Case->getPos()).x % 2 == 1) && ((wall2Case->getPos()).y % 2 == 1);
    return !(res1 && res2);
}


vector<string> BoardController::removeSpace(string str){
    // Enleve les espaces au sein de l'input
    vector<string> res;
    istringstream ss(str);
    string tempPos;
    while (ss >> tempPos)
        res.push_back(tempPos);
    return res;
}

bool BoardController::checkValideLetter(string letter) {
    bool res = false;
    string board_alphabet = "abcdefghijklmnopkq";
    if(board_alphabet.find(letter) != string::npos)
        res = true;
    return res;
}

bool BoardController::checkValideNumber(string number) {
    bool res = false;
    if (! isdigit(number[0])) {return res;} // Dans le cas ou il n'est pas un integer
    int intNumber = stoi(number);
    if(1 <= intNumber && intNumber <= 17) { // Verification si il est dans la bonne intervalle
        res = true;
    }
    return res;
}

bool BoardController::is_in(Point casePos, vector<Point> *posAlreadyVisited){
    for(size_t i=0; i<(*posAlreadyVisited).size();i++){
        if((casePos.x==((*posAlreadyVisited)[i]).x) && (casePos.y==((*posAlreadyVisited)[i]).y)){return true;}
    }
    return false;
}

bool BoardController::searchPath(shared_ptr<Case> casemain, Point dest, vector<Point> *PosAlreadyVisited) {
    

    if((casemain->getPos()).x == dest.x || (casemain->getPos()).y == dest.y) {
        return true;
    }
    else {
        vector<shared_ptr<Case>> PossibleMovements = controlMove.checkMovement(casemain);
        for(auto &moves : PossibleMovements) {
            Point posPossibleMove = moves->getPos();
            if(!(this->is_in(posPossibleMove, PosAlreadyVisited))) { //Si on a pas déjà visiter cette case
                (*PosAlreadyVisited).push_back(posPossibleMove);
                shared_ptr<Case> casePossibleMove = this->board->getCase(posPossibleMove);
                bool res = this->searchPath(casePossibleMove, dest, PosAlreadyVisited);
                
                if(res) {
                    return true;
                }
            }
        } 
    }
    return false;
}

bool BoardController::checkPath(Point pos1, Point pos2, Point pos3, shared_ptr<Wall> wall){
    vector<Point> PosAlreadyVisited;
    bool res = true;
    bool res1, res2, res3, res4 = true;
    Point dest = {-1, -1};
    // cout << "Avant" << endl; PORTE CHANCE
    this->board->putWall(wall, pos1, pos2, pos3);
    // cout << "Apres" << endl;
    array<Point, 4> pawns = this->board->getPawn();
    for(size_t i=0; i < pawns.size(); i++) {
        if(!(this->board->getCase(pawns[i])->isEmpty())){
            
            switch(i) {
                case 0:
                    dest = {((int) this->board->getSize()-1),-1};
                    res1 = searchPath(this->board->getCase(pawns[i]), dest, &PosAlreadyVisited);
                    break;
                case 1:
                    dest = {0, -1};
                    res2 = searchPath(this->board->getCase(pawns[i]), dest, &PosAlreadyVisited);
                    break;
                case 2:
                    dest = {-1, ((int) this->board->getSize()-1)};
                    res3 = searchPath(this->board->getCase(pawns[i]), dest, &PosAlreadyVisited);
                    break;
                case 3:
                    dest = {-1,0};
                    res4 = searchPath(this->board->getCase(pawns[i]), dest, &PosAlreadyVisited);
                    break;
                }
           }
            
        
        PosAlreadyVisited.clear();
        }

    this->board->removeWall(pos1, pos2, pos3);
    res = res1 && res2 && res3 && res4;
    return res;

}
