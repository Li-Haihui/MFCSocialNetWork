#include "pch.h"

#include "SocialNetWorkUser.h"

#include <ctime>
#include <fstream>


User::User(string n, string a, string p, string b) 
    : name(n), address(a), phone(p), birthdate(b) {
}


void User::removeContact(User* u) {
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i] == u) {
            contacts.erase(contacts.begin() + i);
            break;
        }
    }
}

void User::removeMessage(int index) {
    if (index >= 0 && index < messages.size()) {
        messages.erase(messages.begin() + index);
    }
}
void User::editMessage(int index, string newMsg) {
    if (index >= 0 && index < messages.size()) {
        messages[index] = newMsg;
    }
}

void User::leaveGroup(User* u) {
    for (int i = 0; i < groups.size(); i++) {
        if (groups[i] == u) {
            groups.erase(groups.begin() + i);
            break;
        }
    }
}

bool User::addContact(User* u) {
    if (contacts.size() < 3) {
        contacts.push_back(u);
        return true;
    }
    else {
        return false;
    }
    
}

void User::addMessage(string msg) {
    messages.push_back(msg);
}

void User::joinGroup(User* u) {
    groups.push_back(u);
}


