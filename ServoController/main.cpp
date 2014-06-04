#include "ClientSocket.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "ServoController.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

const int PORT_APP = 33333;                                                     //port for app communication
const int PORT_VISION = 44444;                                                  //port for vision/AI communication
const int PORT_SEND = 55555;                                                    //port for sending commands to AI

ServoController* sc;                                                             //main servo controller instance
pthread_mutex_t sc_mutex;                                                       //mutex for servo controller

//send message to vision/AI program on localhost over port 55555
bool sendToVision(std::string msg) {
    try {
        ClientSocket client_socket("127.0.0.1", PORT_SEND);

        try {
            client_socket << msg;                                               //send message to AI
        } catch (SocketException&) {
        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught: " << e.description() << "\n";
        return false;                                                           //failed to send
    }
    return true;
}

//split string by token to separate and queue mangled commands
std::vector<std::string> tokenize(std::string input, char token) {
    std::vector<std::string> results;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == token) {
            input[i] = ' ';                                                     //dirty hax, see below
        }
    }
    
    std::stringstream ss(input);
    std::string segment;
    while (ss >> segment) {
        results.push_back(segment);                                             //stringstream splits by ' ' character
    }
    
    return results;
}

//command to command no. function
int translateCommand(std::string comm){
    //NOTE: move this to main?
    std::vector<std::string> commands;
    commands.push_back("MOV_F_S");
    commands.push_back("MOV_F_E");
    commands.push_back("MOV_B_S");
    commands.push_back("MOV_B_E");
    commands.push_back("MOV_L_S");
    commands.push_back("MOV_L_E");
    commands.push_back("MOV_R_S");
    commands.push_back("MOV_R_E");
    //TODO: add more commands
    for (int i = 0; i < commands.size(); i++){
        if (comm.compare(commands[i]) == 0) {
            return i;                                                           //command found, return command number
        }
    }
    
    return -1;                                                                  //command not found/recognized
}

//server thread for app communication
void* serverThreadManual(void* arg) {
    std::cout << "[MANUAL] Server running...\n";

    try {
        ServerSocket server(PORT_APP);                                          //declare socket to read from
        while (true) {
            ServerSocket new_sock;
            server.accept(new_sock);                                            //acquire socket
            
            std::ostringstream oss;                                             //string stream for logging
            oss << "[MANUAL] ";

            try {
                while (true) {
                    std::string data;
                    new_sock >> data;                                           //read message from socket into data
                    
                    std::vector<std::string> splitcomms = tokenize(data, '#');  //split commands in case they get mangled in a horrible networking accident
                    
                    for (int i = 0; i < splitcomms.size(); i++) {               //for each command:
                    data = splitcomms[i];

                        int command = translateCommand(data);                   //command to command number
                        if (command == -1) {                                    //command not in standard list
                            if (data.compare("REQ_INFO") == 0) {                //info request
                                pthread_mutex_lock(&sc_mutex);                  //lock servo controller
                                oss << "Received command: " << data << "\n";
                                new_sock << sc->getInfo();                       //send info back to app
                                pthread_mutex_unlock(&sc_mutex);                //unlock servo controller
                            } else {
                                //theoretically this should never happen unless something gets messed up good
                                oss << "WARNING: Unrecognized command (" << data << ") - ignored.\n";
                            }
                        } else {
                            pthread_mutex_lock(&sc_mutex);                      //lock servo controller
                            oss << "Received command: " << data << " - " << command << "\n";
                            sc->setState(command);                               //send command to servo controller
                            pthread_mutex_unlock(&sc_mutex);                    //unlock servo controller
                        }
                    }
                    
                }
            } catch (SocketException&) {
            }
            
            oss.flush();
            std::cout << oss.str();                                             //print log line
            
            usleep(10000);                                                      //pause thread 10 ms to reduce cpu load

        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}

//server thread for vision/AI communication
void* serverThreadAuto(void* arg) {
    std::cout << "[AUTO] Server running...\n";

    try {
        ServerSocket server(PORT_VISION);
        while (true) {
            ServerSocket new_sock;
            server.accept(new_sock);
            
            std::ostringstream oss;
            oss << "[AUTO] ";

            try {
                while (true) {
                    std::string data;
                    new_sock >> data;
                    
                    std::vector<std::string> splitcomms = tokenize(data, '#');
                    
                    for (int i = 0; i < splitcomms.size(); i++) {
                    data = splitcomms[i];

                        int command = translateCommand(data);
                        if (command == -1) {
                            oss << "WARNING: Unrecognized command (" << data << ") - ignored.\n";
                        } else {
                            pthread_mutex_lock(&sc_mutex);
                            oss << "Received command: " << data << " - " << command << "\n";
                            sc->setState(command);
                            pthread_mutex_unlock(&sc_mutex);
                        }
                    }
                }
            } catch (SocketException&) {
            }
            
            oss.flush();
            std::cout << oss.str();
            
            usleep(10000);

        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}

int main(int argc, char** argv) {
    sc = new ServoController();
    
    pthread_t tsm, tsa;                                                         //manual and auto server threads
    pthread_create(&tsm, NULL, &serverThreadManual, NULL);
    pthread_create(&tsa, NULL, &serverThreadAuto, NULL);
    pthread_join(tsm, NULL);
    pthread_join(tsa, NULL);
    
    pthread_mutex_destroy(&sc_mutex);
    
    delete sc;

    return 0;
}