#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include "observer.hpp"
#include <QWidget>

class AbstractWindow: public Subject{
    private:
        QWidget* self;
    public:
        AbstractWindow(QWidget* parent_widget){self = parent_widget;};
        virtual ~AbstractWindow() = default;
        virtual QWidget* getSelf() = 0;
};

#endif // ABSTRACTWINDOW_H
