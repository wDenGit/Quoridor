#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <memory>
#include <QVector>
#include <QSharedPointer>

using namespace std;

struct Observer{
    Observer() = default;
    virtual ~Observer() {};
    virtual void update(int windowToShow) = 0;
};

class Subject{
    QVector<QSharedPointer<Observer>>  observers;
public:
    void registerObserver(QSharedPointer<Observer> obs){
        observers.push_back(obs);
    }
    void removeObserver(QSharedPointer<Observer> obs){
        remove(begin(observers),end(observers),obs);
    }

    /*
    This method update all of the registered observers...
    */
    void notifyObservers(int windowToShow) const {
        for (auto &observer:observers)
            observer->update(windowToShow);
    }
};
#endif // OBSERVER_H
