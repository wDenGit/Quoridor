#include "generalwindow.h"
#include <QDebug>

using namespace std;

void generalWindow::create_windows(){
    QSharedPointer<generalWindow> general = this->getSelf_qshared_ptr();
    for (auto window: windows){
        window->registerObserver(general);
    }
}

generalWindow::generalWindow(QSharedPointer<MainWindow> w, QSharedPointer<menuWindow> m){
    windows.push_back(w);
    windows.push_back(m);
}

void generalWindow::run_game(){
    // windows[WINDOW_MENU]->getSelf()->show();
    windows[WINDOW_CONNECT]->getSelf()->show();
}

generalWindow::~generalWindow(){}

void generalWindow::switch_window(int windowToShow){
    windows[windowToShow]->getSelf()->show();
    //qDebug() << windowToShow << " : "<< windows[windowToShow]->getSelf()->metaObject()->className();
    for(int i=0; i< (int) windows.size(); i++){
        //qDebug() << "for " << i <<" : "<<windows[i]->getSelf()->metaObject()->className();
        if(i != windowToShow){
            windows[i]->getSelf()->hide();
        }
    }
}

 /*
 This function change the current window with the specified window...
 Args:
     -> (int) windowToShow : the new window to show
 */
 void generalWindow::update(int windowToShow){
     switch (windowToShow)
     {
     case WINDOW_CONNECT:
         this->switch_window(windowToShow);
         break;

     case WINDOW_MENU:
         this->switch_window(windowToShow);
        break;
    }
}
