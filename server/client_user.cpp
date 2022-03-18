#include "client_user.hpp"

using namespace std;

/*******************************
 *                             *
 *         ClientUser          *
 *                             *
 *******************************/

void ClientUser::setInGameWith(std::vector<std::shared_ptr<ClientUser>> v) {
    for (size_t i=0; i<v.size(); i++) {
        if (v[i].get() == this) {
            v.erase(v.begin() + i);
            this->inGameWith = v;
            return;
        }
    }
}
