// COMSC-210 | Midterm #1 | Andrei Buchatskiy
// IDE used : Visual Studio Code

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        // change data type to string (just realized I gotta go through every function and change the int to string)
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // gotta change the print function to match the example
    void print() {
        cout << "\tResulting line:" << endl;
        Node* current = head;
        if (!current) {
            cout << "\t\tNo one is in line" << endl;
            return;
        }
        while (current) {
            cout << "\t\t" << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // front_val(): gives me the person at the front of the lines name in order to display to user
    // arguments: nothing
    // return: string
    string front_val(){
        // check if list is empty
        if(head == nullptr){
            return "";
        } 
        // if not empty then return the string at the head
        return head->data;
    }
    
    // back_val(): gives me the name at the back of the line
    // arguments: nothing
    // return: string
    string back_val(){
        // check if list is empty
        if(tail == nullptr){
            return "";
        }
        // if not empty return the string at the back
        return tail->data;
    }

    // to_vec(): gives me the linked list as a vector
    // arguemnts: nothing
    // returns: vector
    vector<string> to_vec(){
        // walk from the head to the tail and input value into a vector
        Node* current = head;
        vector<string> list;

        // check if list is empty
        if(!head){
            return list;
        }
        // walk through the list and make a vector
        while (current) {
            list.push_back(current->data);
            current = current->next;
        }

        return list;
    }

    // I noticed that people can still get served if the ilst is empty so i need to add something to check if list is empty before doing that
    // empty(): returns a bool wether the lsit is empty or not
    // argumetns: none
    // return: bool
    bool empty(){
        // check wether the head is null or not
        return head == nullptr;
    }
};

// names(): Start with a function to load names in from my given file
// arguments: nothing
// returns: vector of strings
vector<string> names(){
    vector<string> names;
    ifstream file("names.txt");
    string name;

    // check if the file was found first
    if(!file){
        cout << "Error: File could not be opened";
        return names;
    }

    // Loop through and get names
    while (getline(file, name)) {
        // make sure that the name is valid
        if (name != ""){
             names.push_back(name);
        }
    }

    // wait i still needa randomize now
    for(int i = 0; i < names.size();i++){
        // pick a random position
        int randI = rand() % names.size();

        // every day Im shuffling doo doo doo doo (shuffle the positions around to make it random)
        string temp = names[i];
        names[i] = names[randI];
        names[randI] = temp;
    }

    return names;
}

int main() {
    // seed the random
    srand(time(0));

    // set variabels for the probabilities given
    const int SERVED = 40;
    const int JOIN = 60;
    const int END_LEAVE = 20;
    const int ANY_LEAVE = 10;
    const int VIP = 10;

    // create values for getting a number from 100 to 1
    const int MAX = 100;
    const int MIN = 1;

    // load in the names
    vector<string> nameList = names();
    // create a doubly linked list for the line
    DoublyLinkedList line;

    // since the names are in a random order imma create an index tracker for when i need to get names so I dont get repeats
    int index = 0;
    // store opens add 5 people
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++){
        // get a name from the list
        string name = nameList[index];
        index++; // add to the index

        // add the chosen name to the line
        line.push_back(name);
        // display
        cout << "\t" << name << " joins the line" << endl;
    }
    // call print
    line.print();

    // lets loop for 20 time stamps (starting at minute 2 and going to minute 20 as shown in the example)
    for (int min = 2; min <= 20; min++){
        // output what time step we are on
        cout << "Time step #" << min << ":" << endl;

        // VIP gets prio so I should start with that actually
        int chance = rand() % MAX + MIN;
        if(chance <= VIP){
            // they insta go to the front of the line
            line.push_front(nameList[index]);
            index++;

            // display
            cout << "\t" << line.front_val() << " (VIP) joins the front of the line" << endl;
        }

        // check if someone was served, 40% chance of this also create the chance variable for our probability checking
        chance = rand() % MAX + MIN;
        // also check if line is empty before serving someone
        if(chance <= SERVED && !line.empty()){
            // i needa make a function to get the front person and back persons name to display
            cout << "\t" << line.front_val() << " is served" << endl;

            // serving should remove from the list
            line.pop_front();
        }

        // check if someone new is joining
        chance = rand() % MAX + MIN;
        if(chance <= JOIN){
            // push back a new name from the list
            line.push_back(nameList[index]);
            index++;

            // call the back_val function to get the new person who joined
            cout << "\t" << line.back_val() << " joins the line" << endl;
        }

        // check if someone at the end wants to leave
        // also check if line is empty before seeing if the person will leave
        chance = rand() % MAX + MIN;
        if(chance <= END_LEAVE && !line.empty()){
            cout << "\t" << line.back_val() << " (at the rear) left the line" << endl;
            // eliminate the person at the back
            line.pop_back();
        }

        // nested for function to loop through the list and check if each person wants to leave
        // i need to get the linked list into a vector so i can sort through each person and check if they want to leave
        vector<string> currentLine = line.to_vec();
        for(auto p : currentLine){
            chance = rand() % MAX + MIN;
            if(chance <= ANY_LEAVE){
                cout << "\t" << p << " left the line" << endl;

                // get rid of the person in the linked list
                line.delete_val(p);
            }
        }
        // print at the end of each interval
        line.print();
    }
    return 0;
}
