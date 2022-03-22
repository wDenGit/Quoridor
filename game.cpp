#include "game.h"
#include "ui_game.h"


game::game(QWidget *parent) :
    board(std::make_shared<Board>(9)),
    boardController(this->board),
    QDialog(parent),
    ui(new Ui::game),
    player(std::make_shared<Player>(0, 0, "", 20))
{
    ui->setupUi(this);
    std::shared_ptr<Pawn> p = std::make_shared<Pawn>(0);
    player->setPawn(p);
    this->board->putPawn(p, {0, 8});
}

game::~game()
{
    delete mapper;
    delete_buttons();
    delete ui;

}

void game::make_buttons(){
    //crée les buttons et les connectes a play_game()
    int x = 50;
    int y = 0;
    int y_indice = 10;
    int x_indice = 68;
    mapper = new QSignalMapper();
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(play_game(QString)));
    for(int i = 0; i<17; i++){
        buttons.push_back({});
        QLabel *label_numbers = new QLabel(this);
        QLabel *label_letters = new QLabel(this);

        label_numbers->setText(QString::number(i+1));
        label_letters->setText(letters[i]);

        label_numbers->setGeometry(20,y_indice,20,20);
        label_letters->setGeometry(x_indice,625,20,20);

        if(i%2 == 0){
            for(int j = 0; j<17; j++){
                if(j%2 == 0){
                    buttons[i].push_back(new QPushButton("",this));
                    buttons[i][j]->setGeometry( x, y, 45, 45);
                    x+=45;
                    connect(buttons[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
                    mapper->setMapping(buttons[i][j], letters[j]+QString::number(i+1));
                }
                else{
                    buttons[i].push_back(new QPushButton("",this));
                    buttons[i][j]->setGeometry( x, y, 25, 45);
                    x+=25;
                    connect(buttons[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
                    mapper->setMapping(buttons[i][j], letters[j]+QString::number(i+1));
                }
            }
            y+=45;
            x=50;
            y_indice+=35;
            x_indice+=35;
        }
        else{
            for(int j = 0; j<17; j++){
                if(j%2 == 0){
                    buttons[i].push_back(new QPushButton("",this));
                    buttons[i][j]->setGeometry( x, y, 45, 25);
                    x+=45;
                    connect(buttons[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
                    mapper->setMapping(buttons[i][j], letters[j]+QString::number(i+1));
                }
                else{
                    buttons[i].push_back(new QPushButton("",this));
                    buttons[i][j]->setGeometry( x, y, 25, 25);
                    x+=25;
                }
            }
            y+=25;
            x=50;
            y_indice+=35;
            x_indice+=35;
        }

    }
    //ssize_t taille = buttons.size();
    //qDebug()<<taille;


}

void game::play_game(QString move){
    if(board->checkWinner() == -1){
        stringMove += move.toStdString();
        sizeMove++;
        std::cout<<stringMove<<" : " <<sizeMove <<std::endl;
        if(boardController.checkMove(player, stringMove)){
            qDebug("true");
            boardController.makeMove(player, stringMove);
            updateButtons();
            stringMove = "";
            sizeMove=0;
        }
        else if(sizeMove >= 2 || isCasePawn(stringMove)){
            qDebug("false");
            stringMove = "";
            sizeMove=0;

        }
        else{
            stringMove+=" ";
        }
    }
}

void game::updateButtons() const{
    //Board boardState = this->board->getBoard();

    for(unsigned int i = 0; i < board->getBoard().size(); i++){
        for(unsigned int j = 0; j < board->getBoard().size(); j++ ){
            if(!(board->getBoard()[i][j]->isEmpty()) && board->getBoard()[i][j]->isPawnCase()){
                buttons[i][j]->setText("0");
            }
            else if(!(board->getBoard()[i][j]->isEmpty())){
                buttons[i][j]->setText("X");
            }
            else{
                buttons[i][j]->setText("");
            }
        }
    }
}


void game::delete_buttons(){
    // delete les buttons
    for(int i = 0; i < 17; i++){
        for(int j = 0; j < 17; j++){
            delete buttons[i][j];
        }
    }
}

bool game::isCasePawn(std::string move){
    Point point = boardController.stringToPoint(move);
    if(board->getBoard()[point.x][point.y]->isPawnCase()){
        return true;
    }
    return false;
}
