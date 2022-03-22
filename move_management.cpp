#include "move_management.hpp"

#include <algorithm>    // find()
#include <iostream>     // DEBUG

using namespace std;

bool ControlMove::checkAlignment(std::shared_ptr<Case> case_main, std::shared_ptr<Case> neighborsPawnCase, std::shared_ptr<Case> neighborsWallCase) {
    //on envoie le mur autour de NeighborsPawnCase qui est alligné avec case_main et qui ne se trouve pas entre les case_main & neighborsPawnCase 
    bool res = false;
    Point neiNeighborsPos = neighborsWallCase->getPos();
    if(neiNeighborsPos.x == case_main->getPos().x || neiNeighborsPos.y == case_main->getPos().y){
        vector<std::shared_ptr<Case>> wall_neigh = case_main->getWallCaseNeighbors();
        // shared_ptr<Case> wall_neigh_beg = wall_neigh.front();
        // shared_ptr<Case> wall_neigh_end = wall_neigh.back();
        if (std::find(wall_neigh.begin(), wall_neigh.end(), neighborsWallCase) == wall_neigh.end()){
            res = true;
        }
    }
    return res;
}

bool ControlMove::isAligner(std::shared_ptr<Case> case1, std::shared_ptr<Case> case2, std::shared_ptr<Case> wall) {
    return ((case1->getPos().x == case2->getPos().x && case1->getPos().x == wall->getPos().x && case2->getPos().x == wall->getPos().x) ||
            (case1->getPos().y == case2->getPos().y && case1->getPos().y == wall->getPos().y && case2->getPos().y == wall->getPos().y));
}

bool ControlMove::isWallBetween(std::shared_ptr<Case> pawnCase1, std::shared_ptr<Case> pawnCase2, std::shared_ptr<Case> wallCase) {
    vector<std::shared_ptr<Case>> wallCase1 = pawnCase1->getWallCaseNeighbors();
    vector<std::shared_ptr<Case>> wallCase2 = pawnCase2->getWallCaseNeighbors();

    if ((std::find(wallCase1.begin(), wallCase1.end(), wallCase) != wallCase1.end()) &&
        (std::find(wallCase2.begin(), wallCase2.end(), wallCase) != wallCase2.end() ))
        return true;
    else
        return false;
}
        
void ControlMove::printPos(vector<std::shared_ptr<Case>> vec) {
    for(size_t i = (int) 0; i < vec.size(); i++) {
        Point pos = vec[i]->getPos();
        //cout << pos.x << " " << pos.y << endl;
    }
}

vector<std::shared_ptr<Case>>  ControlMove::checkMovement(std::shared_ptr<Case> case_main) {
    // Est
    vector<std::shared_ptr<Case>> res;
    vector<std::shared_ptr<Case>> neighborsWallCase = case_main->getWallCaseNeighbors();
    vector<std::shared_ptr<Case>> neighborsPawnCase = case_main->getPawnCaseNeighbors();
    //cout << "size: " << neighborsPawnCase.size() << endl;
    for (size_t i = 0; i  < neighborsPawnCase.size(); ++i) {
        //cout << "Je regarde : x=" << neighborsPawnCase[i]->getPos().x << ", y=" << neighborsPawnCase[i]->getPos().y << endl;
        // si on a un murs -> continue
        if (! neighborsWallCase[i]->isEmpty()) continue;

        // si case libre -> ajout a res + continue
        if (neighborsPawnCase[i]->isEmpty()) {
            //cout << "je push x=" <<  neighborsPawnCase[i]->getPos().x << " ,y=" << neighborsPawnCase[i]->getPos().y << endl; 
            res.push_back(neighborsPawnCase[i]);
            continue;
        }
        // si case pas libre
        // -> cas 1: on essaie de passer par dessus, il faut qu'il n'y ai pas de murs derriere
        bool isCase1 = false;
        vector<std::shared_ptr<Case>> neighborsPawnCaseOfNeighbor = neighborsPawnCase[i]->getPawnCaseNeighbors();
        vector<std::shared_ptr<Case>> neighborsWallCaseOfNeighbor = neighborsPawnCase[i]->getWallCaseNeighbors();
        for (size_t j=0; j < neighborsPawnCaseOfNeighbor.size(); j++) {
            //cout << " -- Je regarde: x=" << neighborsPawnCaseOfNeighbor[j]->getPos().x << ", y=" << neighborsPawnCaseOfNeighbor[j]->getPos().y << endl;
            std::shared_ptr<Case> wall = neighborsWallCaseOfNeighbor[j];
            if (this->isAligner(case_main, neighborsPawnCase[i], wall) && 
                (! this->isWallBetween(case_main, neighborsPawnCase[i], wall))) {
                if (wall->isEmpty()) {
                    res.push_back(neighborsPawnCaseOfNeighbor[j]);
                    isCase1 = true;
                }
                // NE PAS SUPPRIMER, ca porte chance
            }
        }
        // verifie si cas 1 verifié, car si cas 1, on ne doit pas regarder le cas 2
        if (isCase1)    continue;

        // -> cas 2: si on ne peux pas passer par dessus, on essaie les 2 cotés
        for (size_t j=0; j < neighborsPawnCaseOfNeighbor.size(); j++) {
            std::shared_ptr<Case> possiblePawnCase = neighborsPawnCaseOfNeighbor[j];
            std::shared_ptr<Case> possibleWallCase = neighborsWallCaseOfNeighbor[j];
            //cout << "----- je suis x=" <<  possiblePawnCase->getPos().x << " ,y=" << possiblePawnCase->getPos().y << endl;
            // si murs -> tampis
            if (! possibleWallCase->isEmpty()) continue;

            // si alligné avec case principal -> tampis
            if (this->isAligner(case_main, possiblePawnCase, possibleWallCase)) continue;

            // sinon on ajoute
            //cout << "je push x=" <<  possiblePawnCase->getPos().x << " ,y=" << possiblePawnCase->getPos().y << endl;
            res.push_back(possiblePawnCase);
        }
    }
    return res;
}

// TODO supprimer ?
// void ControlMove::printNeighbors(Point pos) {
//     //cout << "Dans printNeighbors" << endl;
//     shared_ptr<Case> case_main = board->getCase(pos);
//     vector<shared_ptr<Case>> pawnCaseNeighbours = case_main->getPawnCaseNeighbors();
//     vector<shared_ptr<Case>> wallCaseNeighbours = case_main->getWallCaseNeighbors();
//     for(size_t i = 0; pawnCaseNeighbours.size() > i; ++i) {
//         Point posNeigh = pawnCaseNeighbours[i]->getPos();
//         //cout << posNeigh.x << " " << posNeigh.y << endl;
//     }
//     //cout << "Mur neighbors" << endl;
//     for(size_t i = 0; wallCaseNeighbours.size() > i; ++i){
//         Point posNeigh = wallCaseNeighbours[i]->getPos();
//         //cout << posNeigh.x << " " << posNeigh.y << endl;
//     }
// }

vector<Point> ControlMove::sendMovePossible(Point p){
    vector<Point> listPossiblePositions;
    return listPossiblePositions;}  
        
// TODO supprimer ?
// bool ControlMove::movePawn(Point pos_init, Point pos_dest) {
//     bool posPossible = false;
//     shared_ptr<Case> case_main = board->getCase(pos_init);
//     vector<shared_ptr<Case>> ListMovementPossible = checkMovement(case_main);
//     for(size_t caseIndex = 0; caseIndex < ListMovementPossible.size(); caseIndex++) {
//         Point posCase = ListMovementPossible[caseIndex]->getPos();
//         if((posCase.x == pos_dest.x) &&  (posCase.y == pos_dest.y)) {
//             posPossible = true;
//         }
//         if(posPossible) {
//             shared_ptr<Case> caseDest = board->getCase(pos_dest);
//             return posPossible;
//         }
//     }
//     return posPossible;
// }
