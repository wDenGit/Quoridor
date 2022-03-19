#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    make_button();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::make_button(){

    //QVector<QSharedPointer<QPushButton>> buttons;
    //gridLayout = new QGridLayout;
    //this->setLayout(gridLayout);
    int x = 0;
    int y = 0;
    /*for(int i = 0; i<10; i++){

        QPushButton *b2 = new QPushButton("B", this);
        b2->setGeometry( x, 100, 100, 30);
        x+=100;
            //buttons.push_back(QSharedPointer<QPushButton>::create("A"));
            //gridLayout->addWidget(b2,0,i,1,1);



    }*/

    for(int i = 0; i<17; i++){
        buttons.push_back({});
        if(i%2 == 0){
            for(int j = 0; j<17; j++){
                if(j%2 == 0){
                    buttons[i].push_back(QSharedPointer<QPushButton>::create("",this));
                    buttons[i][j]->setGeometry( x, y, 35, 35);
                    x+=35;
                }
                else{
                    buttons[i].push_back(QSharedPointer<QPushButton>::create("",this));
                    buttons[i][j]->setGeometry( x, y, 15, 35);
                    x+=15;
                }
                //QPushButton *b2 = new QPushButton("", this);
                
            }
            y+=35;
            x=0;
        }
        else{
            for(int j = 0; j<17; j++){
                if(j%2 == 0){
                    buttons[i].push_back(QSharedPointer<QPushButton>::create("",this));
                    buttons[i][j]->setGeometry( x, y, 35, 15);
                    x+=35;
                }
                else{
                    buttons[i].push_back(QSharedPointer<QPushButton>::create("",this));
                    buttons[i][j]->setGeometry( x, y, 15, 15);
                    x+=15;
                }
                //QPushButton *b2 = new QPushButton("", this);
                
            }
            y+=15;
            x=0;

        }

    }
    ssize_t taille = buttons.size();
    qDebug()<<taille;


}

