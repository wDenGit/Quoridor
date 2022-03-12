#include "menu_connection.hpp"
#include "main_menu.hpp"
#include "../common/socketlib.hpp"

#include <iostream>
#include <unistd.h> // sleep()

using namespace std;

void MenuConnection::run() {
    int input = -1;
    while(input != options::exit) {
        this->DisplayMenuConnection();
        input = this->askInput(options::max_input);
        switch(input){
            case options::goToConnection: {
                this->AskInfo();
                int userId = this->connection();
                if(userId > 0) {
                    MainMenu mainMenu = MainMenu(userId, client_socket);
                    mainMenu.run();
                }
                else{
                    cout<<"Pseudo ou mot de passe incorrect"<<endl;
                    sleep(2);
                }  
                break;
            }

            case options::goToCreateAccount:
                this->AskInfo();
                if(this->createAccount() == 0) {
                    cout<<"Votre compte a été créé"<<endl;
                }
                else{
                    cout<<"Ce pseudo est déja utilisé."<<endl;
                }            
                sleep(2); 
                break;
        }   
    }
}

void MenuConnection::DisplayMenuConnection() {
    clear(0);
    cout<<"Quoridor"<<endl;
    cout<<endl;
    cout<<"1.Connection"<<endl;
    cout<<"2.Crée un compte"<<endl;
    cout<<"3.Quitter"<<endl;
}

void MenuConnection::AskInfo() {
    clear(0);
    cout<<"Pseudo : ";
    cin>>pseudo;
    cout<<"Password : ";
    cin>>password;
    cout<<endl;
    clear(0); 
}

int MenuConnection::createAccount() {
    packet p{CREATIONACCOUNT, this->pseudo + " " + this->password};
    send_packet(this->client_socket, &p);
    // attend reponse
    receive_packet(this->client_socket, &p);
    return stoi(p.request);
}

int MenuConnection::connection() {
    packet p{CONNECTION, this->pseudo + " " + this->password};
    send_packet(this->client_socket, &p);
    // attend reponse
    receive_packet(this->client_socket, &p);
    return stoi(p.request);
}