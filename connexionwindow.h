#ifndef CONNEXIONWINDOW_H
#define CONNEXIONWINDOW_H

#include <QDialog>

namespace Ui {
class connexionWindow;
}

class connexionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit connexionWindow(QWidget *parent = nullptr);
    ~connexionWindow();

private:
    Ui::connexionWindow *ui;

private slots:
    void retour_pressed();
};

#endif // CONNEXIONWINDOW_H
