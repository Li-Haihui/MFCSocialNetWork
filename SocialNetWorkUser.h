#ifndef _SOCIAL_NETWORK_USER_H_
#define _SOCIAL_NETWORK_USER_H_

#include <vector>
#include <string>

using namespace std;

class User
{
private:
    string name;
    string address;
    string phone;
    string birthdate;
    vector<User*> contacts;
    vector<string> messages;
    vector<User*> groups;
public:
    User(string n, string a, string p, string b);
    void setName(string na) { name = na; }
    void setAddress(string addr) { address = addr; }
    void setPhone(string ph) { phone = ph; }
    void setBirthdate(string birth) { birthdate = birth; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    string getBirthdate() const { return birthdate; }
    bool addContact(User* u);
    void removeContact(User* u);
    vector<User*> getContacts() const { return contacts; }
    void addMessage(string msg);
    void removeMessage(int index);
    void editMessage(int index, string newMsg);
    vector<string> getMessages() const { return messages; }
    void joinGroup(User* u);
    void leaveGroup(User* u);
    vector<User*> getGroups() const { return groups; }
};

#endif // !_SOCIAL_NETWORK_USER_H_

