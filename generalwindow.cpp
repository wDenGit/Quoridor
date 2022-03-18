#include "generalwindow.h"

using namespace std;

void generalWindow::create_windows(){
    QSharedPointer<generalWindow> general = this->getSelf_qshared_ptr();
    for (auto window: windows){
        window->registerObserver(general);
    }
}

generalWindow::generalWindow(){
    windows.push_back(m);
    windows.push_back(w);
}

void generalWindow::run_game(){
    w->QMainWindow::show();
    // windows[WINDOW_CONNECT]->show();
}

generalWindow::~generalWindow(){

}

void generalWindow::switch_window(int windowToShow){
     //windows[windowToShow]->show();
     //for(int i=0; i< (int) windows.size(); i++){
     //    windows[i]->hide();
    //}
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
