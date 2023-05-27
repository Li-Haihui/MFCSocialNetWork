#ifndef _SOCIAL_NETWORK_APP_H_
#define _SOCIAL_NETWORK_APP_H_

// #pragma once

#include <vector>
#include <string>


class User;

using namespace std;

class SocialNetwork
{
private:
    vector<User*> users;
    string date;
public:
    static SocialNetwork& getInstance();
    void setAppDate(string pdate);
    bool registerUser(string name, string address, string phone, string birthdate);
    void removeUser(User* u);
    void fixUser(string name, User* u);
    vector<User*> getUsers() const { return users; }

    void createGroup(vector<User*> us) { users = us; }
    void addContact(User* u1, User* u2); 
    void removeContact(User* u1, User* u2); 
    void sendMessage(User* u, string msg);
    void removeMessage(User* u, int index);
    void editMessage(User* u, int index, string newMsg);
    void joinGroup(User* u1, User* u2);
    void leaveGroup(User* u1, User* u2);

    void sendGroupMessage(User* sender, User* group, const string& message);

    vector<string> getGroupMessages(User* user, User* group);

    bool isBirthday(User* u);
    void exportData(string filename);
    void importData(string filename);
};

#endif
