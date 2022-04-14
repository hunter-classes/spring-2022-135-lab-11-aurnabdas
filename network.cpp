#include "network.h"
#include "profile.h"
#include <string>
#include <cctype>
#include <iostream>

Network::Network() { 
    numUsers = 0; 

    for(int i = 0; i < MAX_USERS; i++) { 
        for(int j = 0; j < MAX_USERS; j++) { 
            following[i][j] = false;
        }
    }
}

int Network::findID(std::string usrn) { 
    for(int i = 0; i < numUsers; i++) { 
        if(profiles[i].getUsername() == usrn) { 
            return i; 
        }
    }

    return -1;
}

bool Network::addUser(std::string usrn, std::string dspn) { 
    if(numUsers == MAX_USERS) { 
        return false; 
    } else if(findID(usrn) != -1) { 
        return false; 
    }

    for(int i = 0; i < usrn.size(); i++) { 
        if(!isalnum(usrn.at(i))) { 
            return false; 
        }
    }

    profiles[numUsers] = { usrn, dspn };
    numUsers++;
    return true;
}

bool Network::follow(std::string usrn1, std::string usrn2) { 
    // Makes user follow target 
    if(findID(usrn1) == -1 || findID(usrn2) == -1) { 
        return false;
    }

    following[findID(usrn1)][findID(usrn2)] = true;
    return true; 
}

void Network::printDot() { 
    std::cout << "digraph {" << std::endl;
    for(int i = 0; i < numUsers; i++) { 
        std::cout << "  \"@" << profiles[i].getUsername() << "\"" << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < MAX_USERS; i++) { 
        for(int j = 0; j < MAX_USERS; j++) { 
            if(following[i][j] == true) { 
                std::cout << "  \"@" << profiles[i].getUsername() << "\" -> \"" << 
                             "@" << profiles[j].getUsername() << "\"" << std::endl;
            }
        }
    }

    std::cout << "}" << std::endl;
}