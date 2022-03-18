#include "game.hpp"
#include "../common/socketlib.hpp"
#include "../common/common.hpp"

#include <unistd.h> // sleep()

#define nb_wall 20

using namespace std;


Game::Game(int sock, int myKey, std::vector<int> keys):   nb_players{(const int) keys.size()}, accKey{myKey}, board{make_shared<Board>(9)}, 
                                                          boardController{this->board}, boardView{board}, sock{sock} {
                            
    this->initPlayers(keys);
    this->initPawn();
}


void Game::playGame(){
    int order=0; 
    boardView.draw();
    int winner;
    while ((winner = board->checkWinner()) == -1) {
        this->clearTerminal();
        boardView.draw();
        if (order == myOrder) {   // a moi de jouer
            string userInput = this->askAndCheckUserInput();
            if (userInput == "exit") {   // si l'user écrit exit, il quitte la partie
                this->cancelGame();
                return;
            }
            // on fait notre move + l'envoie
            boardController.makeMove(this->players[order], userInput);
            packet p{MOVE, userInput};
            send_packet(this->sock, &p);
        }
        else{
            // si un autre joueur annule la partie -> return
            if (! waitOtherPlayerInput(this->players[order])) return;
        }
        order = (order + 1) % this->nb_players;
    }
    this->tellServerGameFinish(winner);
}


string Game::askAndCheckUserInput() {
    string userInput;
    while (true) {
        userInput = this->askMove();
        // si on veut exit -> renvoie "exit"
        if (userInput == "exit")    
            break;
        // si notre coup est valide -> renvoie le coup
        if (this->boardController.checkMove(this->players[myOrder], userInput))
            break;
        this->clearTerminal();
        this->boardView.draw();
        cout << "Mauvais coup." << endl;
    }
    return userInput;
}

string Game::askMove() {
    string toReturn;
    cout << "Pour bouger votre pion (le pion [" << this->myOrder << "]): <lettre><nombre>" << endl;
    cout << "Pour placer un murs: <lettre><nombre> <lettre><nombre>" << endl;
    cout << "Ou écrivez 'exit', pour quittez la partie." << endl;
    cout << "Votre coup: ";
    ws(cin);
    getline(cin, toReturn);
    //cout << "toReturn: " << toReturn << endl;
    return toReturn;
}

// return true, if we get move | return false if otherPlayer cancel the current game
bool Game::waitOtherPlayerInput(shared_ptr<Player> otherPlayer) {
    cout << "C'est a " << otherPlayer->getPseudo() << " de jouer. "<< endl;
    packet move_opposant;
    receive_packet(this->sock, &move_opposant);
    if (move_opposant.typeRequest == STOPCURRENTGAME) {
        cout << "Partie annulé." << endl;
        sleep(2);
        return false;
    }
    boardController.makeMove(otherPlayer, move_opposant.request);
    return true;
}

// send packet to server telling him if we won or not
void Game::tellServerGameFinish(int winner) {
    packet end_game{GAMEFINISH};
    if (myOrder == winner) 
        end_game.request = to_string(1); // 1 -> j'ai gagné
    else 
        end_game.request = to_string(0); // 0 -> j'ai perdu
    send_packet(this->sock, &end_game);
    cout << "Le joueur " << this->players[winner]->getPseudo() << " a gagné." << endl;
    sleep(3);
}


void Game::initPlayers(vector<int> othersKey) {
    int order=0;
    for (auto &key: othersKey) {
        if(key == this->accKey){
            this->myOrder=order;
        }
        // on va demander le pseudo du joueur au server
        packet p{GETPSEUDO, to_string(key)};
        send_packet(this->sock, &p);
        receive_packet(this->sock, &p);
        this->players.push_back({make_shared<Player>(key, order, p.request, nb_wall/this->nb_players)});
        order++;
    }
}

void Game::initPawn() {
    vector<Point> pos_init_player = {{0,8},{16,8},{8,0},{8,16}};
    for (int i=0; i < this->nb_players; i++) {
        shared_ptr<Pawn> p = make_shared<Pawn>(players[i]->getPlayerOrder());
        players[i]->setPawn(p);
        this->board->putPawn(p, pos_init_player[i]);
    }
}

// when we decide to stop the current game
void Game::cancelGame() {
    packet cancelGame{STOPCURRENTGAME};
    send_packet(this->sock, &cancelGame);
    cout << "Partie annulé" << endl;
    sleep(2);
}
    
void Game::clearTerminal() {
    cout << "\x1B[2J\x1B[H";
}