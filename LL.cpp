#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
    Node(const T& data); //Node Constructor - Assume each quan
    pair<T, int>& GetData(); //Node Data Getter
    void SetData(const pair<T, int>&); //Node Data Setter
    Node<T>* GetNext(); //Node m_next getter
    void SetNext(Node<T>* next); //Node m_next setter
private:
    pair <T, int> m_data; //Holds templated data
    Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node(const T& data) {
    m_data = make_pair(data, 1);
    m_next = nullptr;
}

template <class T>
pair<T, int>& Node<T>::GetData() {
    return m_data;
}

template <class T>
void Node<T>::SetData(const pair<T, int>& data) {
    m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
    return m_next;
}

template <class T>
void Node<T>::SetNext(Node<T>* next) {
    m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
public:
    // Name: LL() (Linked List) - Default Constructor
    // Desc: Used to build a new linked list
    // Preconditions: None
    // Postconditions: Creates a new linked list where m_head points to nullptr
    LL();

    // Name: ~LL() - Destructor
    // Desc: Used to destruct a LL
    // Preconditions: There is an existing LL with at least one node
    // Postconditions: A LL is deallocated (including dynamically allocated nodes)
    //                 to have no memory leaks!
    ~LL();

    // Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
    LL(const LL&);

    // Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
    LL<T>& operator= (const LL&);

    // Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
    Node<T>* Find(const T& data);

    // Name: Insert
    // Desc: Either inserts a node to the linked list OR increments frequency of first
    //       Takes in data. If "first" (of pair) NOT in list, adds node
    //       If "first" (of pair) is already in list, increments quantity
    //       Inserts "first" in order with no duplicates
    // Preconditions: Requires a LL.
    // Postconditions: Node inserted in LL based on first value (or quantity incremented)
    void Insert(const T&);

    // Name: RemoveAt
    // Desc: Removes a node at a particular position based on data passed (matches first)
    // Preconditions: LL with at least one node. 
    // Postconditions: Removes first node with passed value (in first)
    void RemoveAt(const T&);

    // Name: Display
    // Desc: Display all nodes in linked list
    // Preconditions: Outputs the LL
    // Postconditions: Displays the pair in each node of LL 
    void Display();

    // Name: GetSize
    // Desc: Returns the size of the LL
    // Preconditions: Requires a LL
    // Postconditions: Returns m_size
    int GetSize();

    // Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
    template <class U>
    friend ostream& operator<<(ostream& output, const LL<U>&);

    // Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
    pair<T, int>& operator[] (int x);//Overloaded [] operator to pull data from LL

private:
    Node <T>* m_head; //Node pointer for the head
    int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here

template<class T>
LL<T>::LL() {
    m_head = nullptr;
    m_size = 0;
}

template<class T>
LL<T>::~LL() {
    Node<T>* curr = m_head;
    m_size = 0;
    while (curr != nullptr) {
        Node<T>* next = curr->GetNext();
        delete curr;
        curr = nullptr;
        curr = next;
    }
}


// Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
template<class T>
LL<T>::LL(const LL& source) {
    m_size = source.m_size;
    m_head = nullptr;
    Node<T>* currSource = source.m_head;
    Node<T>* currCpy = m_head;
    if (currSource != nullptr) {
        currCpy = new Node<T>(currSource->GetData().first);
        currCpy->SetData(currSource->GetData());

        currSource = currSource->GetNext();

        while (currSource != nullptr) {
            // create and set the next copy node 
            Node<T>* temp = new Node<T>(currSource->GetData().first);
            temp->SetData(currSource->GetData());
            currCpy->SetNext(temp);

            // moves to the next node 
            currCpy = currCpy->GetNext();
            currSource = currSource->GetNext();

            // deallocate pointers
            currCpy->SetNext(nullptr);
            temp = nullptr;
            delete temp;
        }
    }

}

// Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
template<class T>
LL<T>& LL<T>::operator=(const LL& source) {
    if (this != &source) {
        m_size = source.m_size;
        Node<T>* currSource = source.m_head;
        Node<T>* currCpy;

        if (currSource != nullptr) {
            m_head = new Node<T>(currSource->GetData().first);
            m_head->SetData(currSource->GetData());
            currCpy = m_head;
            currSource = currSource->GetNext();

            while (currSource != nullptr) {
                // create and set the next copy node 
                Node<T>* temp = new Node<T>(currSource->GetData().first);
                temp->SetData(currSource->GetData());
                currCpy->SetNext(temp);

                // moves to the next node 
                currCpy = currCpy->GetNext();
                currSource = currSource->GetNext();

                // deallocate pointers
                temp = nullptr;
                delete temp;
            }
        }
    }

    return *this;
}

// Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
template<class T>
Node<T>* LL<T>::Find(const T& val) {
    Node<T>* curr = m_head;
    T currVal;
    int low = 0;
    int high = GetSize() - 1;
    int mid = 0;
    // binary search
    /************************/
    if (m_size == 0) {
        return nullptr;
    }
    while (low <= high && curr != nullptr) {
        mid = (low + high) / 2;
        // find the mid node
        for (unsigned int num = 0; num < mid; num++) {
            curr = curr->GetNext();
        }
        currVal = curr->GetData().first;
        if (currVal == val) {
            return curr;
        }
        else if (val > currVal) {
            low = mid + 1;
            
        }
        else {
            high = mid - 1;
        }
        curr = m_head;
    }
    /**********************/
    return nullptr;
}

template<class T>
void LL<T>::Insert(const T& key) {
    Node<T>* getNode = Find(key);
    T first;
    int second;
    pair<T, int> pair;

    // If the size of the list is zero
    // set the node to m_head 
    if (m_size == 0) {
        getNode = new Node<T>(key);
        m_head = getNode;
        m_size++;
    }
    // See if you can find the node in the list
    // If it is already in the list, increment the quantity 
    else if (getNode != nullptr) {
        first = getNode->GetData().first;
        second = getNode->GetData().second;
        pair = make_pair(first, ++second);

        getNode->SetData(pair);
    }

    else {
        // Add the new node in the list in alphabetical order
        getNode = new Node<T>(key);

        Node<T>* curr = m_head;
        Node<T>* prev = m_head;
        bool isFound = false;

        while (curr != nullptr && !isFound) {
            // if the new node is placed
            // in alphabetical order
            if (key < curr->GetData().first) {
                // inserting at beginning of linked list
                // (already contains m_head)
                if (curr == m_head) {
                    getNode->SetNext(curr);
                    m_head = getNode;
                }
                // middle of linked list
                else {
                    getNode->SetNext(curr);
                    prev->SetNext(getNode);
                }

                isFound = true;
            }
            // continue traversing 
            else {
                prev = curr;
                curr = curr->GetNext();
            }

        }
        // end of the list
        if (!isFound) {
            prev->SetNext(getNode);
        }
        m_size++;
    }

}

template<class T>
void LL<T>::RemoveAt(const T& keyVal) {
    Node<T>* curr = m_head;
    Node<T>* prev = m_head;
    bool isFound = false;
    // binary search
    /***********************/
    T currVal;
    int low = 0;
    int high = GetSize() - 1;
    int mid = 0;
    while (low <= high && curr != nullptr && !isFound) {
        mid = (low + high) / 2;
        // find the mid node
        for (unsigned int num = 0; num < mid; num++) {
            prev = curr;
            curr = curr->GetNext();
        }
        currVal = curr->GetData().first;

        // if node found
        if (currVal == keyVal) {
            isFound = true;
        }
        else if (keyVal > currVal) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
        if (!isFound) {
            curr = m_head;
            prev = m_head;
        }
        
    }
    /***********************/
    // if the keyval is at m_head
    if (curr == m_head && isFound) {
        curr = curr->GetNext();
        m_head = curr;
        prev->SetNext(nullptr);
        delete prev;
    }
    // if the node is found 
    else if (isFound){
        prev->SetNext(curr->GetNext());
        curr->SetNext(nullptr);
        delete curr;
    }
}

template<class T>
void LL<T>::Display() {
    Node<T>* curr = m_head;
    T first;
    int second;
    
    while (curr != nullptr) {
        first = curr->GetData().first;
        second = curr->GetData().second;
        cout << first << ": " << second << endl;
        curr = curr->GetNext();
    }
}

template<class T>
int LL<T>::GetSize() { return m_size; }

// Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
template<class U>
ostream& operator<<(ostream& output, const LL<U>& source) {
    Node<U>* curr = source.m_head;
    while (curr != nullptr) {
        output << curr->GetData().first << ": " << curr->GetData().second << endl;
        curr = curr->GetNext();
    }
    return output;
}

// Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
template<class T>
pair<T, int>& LL<T>::operator[] (int x) { 
    int num = 0;
    Node<T>* curr = m_head;
    while (curr != nullptr) {
        if (num == x) {
            return curr->GetData();
        }
        curr = curr->GetNext();
        num++;
    }
    return curr->GetData();
}
//****************************************************************


// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)


/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  LL <string>* newLL1 = new LL<string>();
  //Push 4 nodes into LL
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Display();
  //  delete newLL1;
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  LL <string>* newLL2 = new LL<string>(*newLL1);
  cout << "*******Original*********" << endl;
  newLL1->Display();
  cout << "*******Copy*********" << endl;
  newLL2->Display();

  //Test Overloaded Assignment Operator
  LL <string>* newLL3 = new LL<string>();
  newLL3 = newLL1;
  cout << "*******Assignment*********" << endl;
  newLL3->Display();
  cout << endl;
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 Overloaded" << endl;
  cout << *newLL1;
  cout << "RemoveAt(candy)" << endl;
  newLL1->RemoveAt("candy");
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  return 0;
}
*/



