#include "pch.h"

#include "SocialNetworkApp.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>


#include "SocialNetWorkUser.h"

using json = nlohmann::json;

SocialNetwork& SocialNetwork::getInstance() {
    static SocialNetwork inst;
    return inst;
}

void SocialNetwork::setAppDate(string pdate) {
    date = pdate;
}

bool SocialNetwork::registerUser(string name, string address, string phone, string birthdate) {
    User* newUser = new User(name, address, phone, birthdate);
    if (users.size() < 8) {
        users.push_back(newUser);
        return true;
    }
    else {
        return false;
    }
}

void SocialNetwork::removeUser(User* u) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i] == u) {
            users.erase(users.begin() + i);
            break;
        }
    }
}

void SocialNetwork::fixUser(string name, User *u) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getName() == name) {
            users[i]->setName(u->getName());
            users[i]->setAddress(u->getAddress());
            users[i]->setPhone(u->getPhone());
            users[i]->setBirthdate(u->getBirthdate());
        }
    }
}

void SocialNetwork::addContact(User* u1, User* u2) {
    u1->addContact(u2);
    u2->addContact(u1);
}

void SocialNetwork::removeContact(User* u1, User* u2) {
    u1->removeContact(u2);
    u2->removeContact(u1);
}

void SocialNetwork::sendMessage(User* u, string msg) {
    u->addMessage(msg);
    vector<User*> contacts = u->getContacts();
    for (int i = 0; i < contacts.size(); i++) {
        contacts[i]->addMessage(msg);
    }
}

void SocialNetwork::removeMessage(User* u, int index) {
    u->removeMessage(index);
    vector<User*> contacts = u->getContacts();
    for (int i = 0; i < contacts.size(); i++) {
        contacts[i]->removeMessage(index);
    }
}

void SocialNetwork::editMessage(User* u, int index, string newMsg) {
    u->editMessage(index, newMsg);
    vector<User*> contacts = u->getContacts();
    for (int i = 0; i < contacts.size(); i++) {
        contacts[i]->editMessage(index, newMsg);
    }
}

void SocialNetwork::joinGroup(User* u1, User* u2) {
    u1->joinGroup(u2);
    u2->joinGroup(u1);
}

void SocialNetwork::leaveGroup(User* u1, User* u2) {
    u1->leaveGroup(u2);
    u2->leaveGroup(u1);
}

void SocialNetwork::sendGroupMessage(User* sender, User* group, const string& message) {
    if (sender == nullptr || group == nullptr) {
        cout << "Invalid sender or group." << endl;
        return;
    }

    vector<User*> groupMembers = group->getGroups();

    for (User* member : groupMembers) {
        if (member != sender) {
            sendMessage(member, message);
        }
    }

    cout << "Group message sent successfully." << endl;
}

vector<string> SocialNetwork::getGroupMessages(User* user, User* group) {
    vector<string> groupMessages;

    if (user == nullptr || group == nullptr) {
        cout << "Invalid user or group." << endl;
        return groupMessages;
    }

    vector<User*> groupMembers = group->getGroups();

    for (User* member : groupMembers) {
        if (member != user) {
            vector<string> messages = member->getMessages();
            for (const string& message : messages) {
                groupMessages.push_back(message);
            }
        }
    }

    return groupMessages;
}

bool SocialNetwork::isBirthday(User* u) {
    if (date == u->getBirthdate()) {
        return true;
    }
    return false;
}

void SocialNetwork::exportData(string filename) {
    json data;
    for (int i = 0; i < users.size(); i++) {
        User* u = users[i];
        json user;
        user["name"] = u->getName();
        user["address"] = u->getAddress();
        user["phone"] = u->getPhone();
        user["birthdate"] = u->getBirthdate();

        // Export contacts
        vector<User*> contacts = u->getContacts();
        json contactsJson;
        for (int j = 0; j < contacts.size(); j++) {
            contactsJson.push_back(contacts[j]->getName());
        }
        user["contacts"] = contactsJson;

        // Export messages
        vector<string> messages = u->getMessages();
        json messagesJson;
        for (int j = 0; j < messages.size(); j++) {
            messagesJson.push_back(messages[j]);
        }
        user["messages"] = messagesJson;

        // Export groups
        vector<User*> groups = u->getGroups();
        json groupsJson;
        for (int j = 0; j < groups.size(); j++) {
            groupsJson.push_back(groups[j]->getName());
        }
        user["groups"] = groupsJson;

        data.push_back(user);
    }

    ofstream file(filename);
    file << data.dump(4);
    file.close();
}
    
void SocialNetwork::importData(string filename) {
    ifstream file(filename);
    json data;
    file >> data;
    file.close();

    for (int i = 0; i < data.size(); i++) {
        json userJson = data[i];
        string name = userJson["name"];
        string address = userJson["address"];
        string phone = userJson["phone"];
        string birthdate = userJson["birthdate"];

        User* newUser = new User(name, address, phone, birthdate);

        // Import contacts
        json contactsJson = userJson["contacts"];
        for (int j = 0; j < contactsJson.size(); j++) {
            string contactName = contactsJson[j];
            for (int k = 0; k < users.size(); k++) {
                if (users[k]->getName() == contactName) {
                    addContact(newUser, users[k]);
                    break;
                }
            }
        }

        // Import messages
        json messagesJson = userJson["messages"];
        for (int j = 0; j < messagesJson.size(); j++) {
            string message = messagesJson[j];
            sendMessage(newUser, message);
        }

        // Import groups
        json groupsJson = userJson["groups"];
        for (int j = 0; j < groupsJson.size(); j++) {
            string groupName = groupsJson[j];
            for (int k = 0; k < users.size(); k++) {
                if (users[k]->getName() == groupName) {
                    joinGroup(newUser, users[k]);
                    break;
                }
            }
        }

        users.push_back(newUser);
    }
}


