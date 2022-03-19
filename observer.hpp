#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

struct Observer{
    virtual void update()=0;
};

class Subject{
    vector <Observer *> observers;
public:
    void registerObserver(Observer *observer){
        observers.push_back(observer);
    }
    void removeObserver(Observer *observer){
        remove(begin(observers),end(observers),observer);
    }
    void notifyObservers() const {
        for (auto &observer:observers)
            observer->update();
    }
};
#endif // OBSERVER_H
