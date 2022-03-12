#include "board_view.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <memory>


using namespace std;

void BoardView::draw() const {
    int ligne=1;
    for(size_t i= 0; i < board->getSize(); i++) {
        // ecriture du numero de ligne
        cout << ligne;
        if (ligne<10)
            cout << "  ";
        else
            cout << " ";
        ligne++;

        // dessine notre ligne
        for(size_t j = 0; j < board->getSize(); j++) {
            if(board->getBoard()[i][j]->isPawnCase()) {
                cout << "[";
                if(! board->getBoard()[i][j]->isEmpty())
                    // cout << "O]";
                    cout << board->getBoard()[i][j]->getPlayer_1() << "]";
                else
                    cout << " ]";
            }
            else {
                if(! board->getBoard()[i][j]->isEmpty())
                    cout << " X ";
                else
                    cout << "   ";
            }
        }
        cout << endl;
    }
    cout << "    a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q" << endl;
}
