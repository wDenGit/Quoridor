#include "player.hpp"
#include <assert.h>

using namespace std;

void Player::setPawn(shared_ptr<Pawn> p) {
    this->pawn = p;
}

int Player::getPlayerOrder() {
    return this->playerOrder;
}

shared_ptr<Pawn> Player::getPawn() {
    return this->pawn;
}

shared_ptr<Wall> Player::getWall() {
    assert(this->hasWall());
    this->wallAvailable --;
    return make_shared<Wall>();
}

bool Player::hasWall() {
    return wallAvailable > 0;
}
