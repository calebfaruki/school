/**********************************************************************
* Name: Caleb Faruki
* Lab5: Linked List II
* Course: Data Structures
* Date: July 17, 2013
* File: List Class Implementation
**********************************************************************/
#include "List.h"

using namespace std;

List::List() {
    head = NULL;
    tail = NULL; // Head & tail point nowhere.

    empty = true; // List initialized as empty.
    forward = true; // Any new Nodes appended to tail.
    numNodes = 0; // Initial number of nodes
}

List::List(const List &aList): numNodes(aList.numNodes) {
    empty = true;
    forward = true;
    string flag;

    cout << "Copy from head to tail? (y/n): ";
    cin >> flag;
    if(flag=="n")
        forward = false;

    if(!aList.head) {
        head = NULL; //aList is empty. so is this->List.
        tail = NULL;
    } else { // copy 1st Node.
        head = new Node;
        if(forward)
            head->setData(aList.head->getData());
        else // copy in reverse.
            head->setData(aList.tail->getData());
        //copy rest of List.
        Node *newPtr = head; //newPtr points to last Node in new List.
        Node *newNode = NULL; //newNode points to each Node in new List.


        //origPtr points to nodes in original List.
        if(forward) {
            cout << "Copying normally...\n" << endl;
            for(Node *origPtr=aList.head->getNext(); origPtr!=NULL;
                origPtr=origPtr->getNext()) {
                newNode = new Node;
                newNode->setPrev(newPtr); // newNode prev pts to newPtr.
                newPtr->setNext(newNode); // newPtr next pts to newptr.
                newPtr = newPtr->getNext(); // newPtr = newNode.
                newPtr->setData(origPtr->getData()); //copy origPtr.
            } // end for
        } else { // for-loop "initialize" and "increment" fields changed.
            cout << "Copying in reverse order...\n" << endl;
            for(Node *origPtr=aList.tail->getPrev(); origPtr!=NULL;
                origPtr=origPtr->getPrev()) {
                newNode = new Node;
                newNode->setPrev(newPtr);
                newPtr->setNext(newNode);
                newPtr = newPtr->getNext();
                newPtr->setData(origPtr->getData());
            } // end for
        } // end if/else
        tail = newPtr; // after copying, tail set to newPtr.
        newPtr->setNext(NULL); // newPtr nullified
    } // end if/else
    cout << "Done copying!\n" << endl;
} // end copy constructor

List::~List() { // Deletes all nodes
    Node *curr = head;
    Node *prev = NULL;

    if(isEmpty()) {
        cout << "Empty List. No need to destroy." << endl;
    } else { // list not empty
        while(curr) { //traverse list to delete memory
            Node *temp = NULL; // TEMP points to CURR which points to HEAD
            temp = curr;
            if (prev) {
                prev->setNext(curr->getNext()); //set PREV node's NEXT to the NEXT of the CURR node.
            } else {
                head = curr->getNext(); //HEAD is the node NEXT to curr.
            } // end if/else

            curr = curr->getNext(); //move curr ptr to next node.
            delete temp; //delete TEMP which points to previous CURR.
            temp = NULL; //empty memory address contents.
        } // end while
        cout << "Destruction complete." << endl;
    } // end if/else
} // end destructor

bool List::isEmpty() {

    if (!head)  // No head means no nodes.
        empty = true;
    else
        empty = false; //head exists, thus list isn't empty.
    // end if/else

    return empty;
} // end isEmpty()

void List::append(Student *newStudent) {
    Node *newNode = new Node(newStudent); // new Node containing student arg.

    newNode->getData(); // get data of student arg.

    if(isEmpty()) {
    	cout << "List is empty. Inserting first Node.\n" << endl;
        head = newNode;
        tail = newNode; // new Node becomes head & tail.
    } else { 
    	if(forward) { // append to tail of list.
        	tail->setNext(newNode); // NEXT ptr of tail points to newNode.
        	newNode->setPrev(tail); // newNode's PREV points to former tail.
        	tail = newNode; // newNode becomes the new tail.
    	} else { // append as head of list.
    		head->setPrev(newNode); // PREV ptr of head points to newNode.
    		newNode->setNext(head); // newNode's NEXT points to former head.
    		head = newNode; // newNode becomes the new head.
    	} // end if/else
    } // end if/else
    numNodes++;
}

void List::insert(Student * newStudent) {
Node *curr = head; // Initialize for linear search.
int count = 1; // Count thru Nodes till desired position reached.
int position = numNodes;

	cout << "There are " << getNumNodes() << " Nodes in the List.\n"
		 << "After which Node do you want to insert new Node?: ";
	cin >> position;

    cout << endl;

    //Controls boundary exceptions
	if(position >= numNodes) {
		forward = true; // Append to tail.
		append(newStudent);
	} else if(position == 1) { // Position = 1
		forward = false; // Append before head.
		append(newStudent);
	} else {
    	while(count != position) {
	      	curr = curr->getNext(); // Traverse List.
	      	count++; // Increment number Node where CURR points.
	   } // end while

	   Node *newNode = new Node(newStudent);

	   newNode->getData();

	   if(count == position) { // curr points to desired Node.
            newNode->setPrev(curr); // link newNode to curr
		    newNode->setNext(curr->getNext()); // link newNode to curr's next node.
		    curr->getNext()->setPrev(newNode); // link curr's next ptr to newNode.
		    curr->setNext(newNode); // link curr's next ptr to newNode.
	    } // end if
    }
} // end insert()

void List::deleteNode(string f) {
    bool flag = false; // flag=true when name is found.
    Node *curr = head; // CURR pointing to head.
    Node *prev = NULL; // PREV pointing nowhere.

    if (!curr) 
        cout << "List is empty\n" << endl;
    else { // list isn't empty.
        while(curr && !flag) { // traverse the list for name.       
            if (curr->getData()->getFirst() == f) {
                cout << "Record: " << f << " found\n" 
                     << "Deleting...\n" << endl;
                flag = true; // true because Student was found.         
            } else {
                prev = curr; // Prev pts to curr Node.
                curr = curr->getNext();  // Curr pts to next Node.
            } // end if/else
        } // end while
    } // end if/else

    //name is found, delete name
    if(flag) { //unlink CURR from the list.
        //set PREV's next to CURR's next.
        prev->setNext(curr->getNext());
        //set NEXT prev to CURR prev.
        curr->getNext()->setPrev(curr->getPrev());
        delete curr; // delete curr.
        curr = NULL; // empty curr's address
        numNodes--;
    } // end if
} // end deleteNode()

void List::displayAscending() { // Iterative; takes HEAD as arg
    Node *curr = head;
    while(curr) {  // as long as curr isn't NULL
        curr->printNode(curr);
        curr = curr->getNext(); ///curr points to NEXT of THIS node.
    } // end while
    cout << endl;
} // end displayAscending()

void List::displayDescending() {
    printer(tail); // Pass tail node to recursive func. w/o inf. loop.
    cout << endl;
}

void List::printer(Node *curr) {
    if(curr) { // List isn't empty.
        curr->printNode(curr); // Print curr.
        printer(curr->getPrev()); // Call printer of node prev to CURR.
    }
}

void List::input(Student* stuPtr, string first, string mid, 
	string last, string ssn, string age) {
    stuPtr->setStudent(first, mid, last, ssn, age);
} // end input()