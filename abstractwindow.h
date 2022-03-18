#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include "observer.hpp"

class AbstractWindow: public Subject{
    public:
        AbstractWindow() = default;
        virtual ~AbstractWindow() = default;
        // virtual void show() = 0;
        // virtual void hide() = 0;
};

#endif // ABSTRACTWINDOW_H
