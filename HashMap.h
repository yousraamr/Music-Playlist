#pragma once
//
//  Hashmap.h
//  Hashmap using channing with array and linked list
//
//  Project Data structures
// 
//  Created by Mariam Jan, Yousra Amr, Rawan Jalal, Jana Ahmed, Mariam Mohamed
// 
//  presented to Dr Ashraf AbdelRaouf
//
//
#include <iostream>
using namespace std;
typedef string ElementType;
const int INITIAL_CAPACITY = 10;
class Hashmap
{
private:
    int mySize;
    int myCapacity;
    class Node {
    public:
        //------ Node DATA MEMBERS
        ElementType key;
        ElementType title;
        ElementType artist;
        ElementType album;
        ElementType songPath;
        double duration;
        Node* next;

        //-- Explicit-value constructor:

        Node(ElementType k, ElementType t, ElementType a, ElementType al, double d, ElementType sp) :key(k), title(t), artist(a), album(al), duration(d), songPath(sp), next(nullptr) {}
    };//--- end of Node class


    typedef Node* NodePointer;
    NodePointer* arr;

public:
    //------ Hashmap OPERATIONS
    Hashmap();
    /*--------------------------------------------------------------------
     Default constructor: builds an empty Hashmap object.
     Precondition:  None
     Postcondition: mySize= 0, myCapacity= INITIAL_CAPACITY),arr =nullptr
     --------------------------------------------------------------------*/
    ~Hashmap();
    /*--------------------------------------------------------------------
     Destructor
     Precondition:  This Hashmap's lifetime is over.
     Postcondition: This Hashmap has been destroyed.
     --------------------------------------------------------------------*/
    int hashFunction(ElementType key);
    /*--------------------------------------------------------------------
     Hash function
     Precondition:  key
     Postcondition: return key after implementing the hash function
     --------------------------------------------------------------------*/
    bool empty();
    /*--------------------------------------------------------------------
     Check if this Hashmap is empty
     Precondition:  None.
     Postcondition: true is returned if this Hashmap is
     empty, false if not.
     --------------------------------------------------------------------*/
    void insert(ElementType key, ElementType title, ElementType artist, ElementType album, double duration, ElementType songPath);
    /*--------------------------------------------------------------------
     Insert a value into a list at a given index.
     Postcondition:  key,title,artist,album has been inserted
     into the Hashmap.
     --------------------------------------------------------------------*/
    void erase(ElementType key);
    /*--------------------------------------------------------------------
     Remove a value from a Hashmap at a given key.
     Postcondition: key,title,artist,album at Hashmap with key
     has been removed.
     --------------------------------------------------------------------*/
    void display(ostream& out) const;
    /*--------------------------------------------------------------------
     Display the contensts of this Hashmap.
     Precondition:  ostream out is open
     Postcondition: Elements of this Hashmap have been output to out.
     --------------------------------------------------------------------*/
    string search(ElementType key);
    /*--------------------------------------------------------------------
     Search for an song in this hashmap.
     Precondition:  None
     Postcondition: key of node containing song is returned
     --------------------------------------------------------------------*/
    void shuffle();
    /*--------------------------------------------------------------------
     method is to introduce randomness into the order of elements
     stored in the HashMap.
     --------------------------------------------------------------------*/
    int countNodes();
    /*--------------------------------------------------------------------
     Count the elements of this Hashmap.
     Precondition:  None
     Postcondition: Number of elements in this Hashmap is returned.
     --------------------------------------------------------------------*/
    string getsongPathByKey(ElementType key);
    /*--------------------------------------------------------------------
    return songPath
    --------------------------------------------------------------------*/
    int playSong(ElementType key);
    /*--------------------------------------------------------------------
    playSong function
    --------------------------------------------------------------------*/
    void moveSongToPosition(ElementType key, int desiredIndex);
    /*--------------------------------------------------------------------
     move the song according to the user opinion
     -------------------------------------------------------------------*/
    void writeToFile();
    /*--------------------------------------------------------------------
    function to write in files
    --------------------------------------------------------------------*/
    void readFromFile();
    /*--------------------------------------------------------------------
    function to write in files
    --------------------------------------------------------------------*/

    /*Hashmap(const Hashmap& origlist);
     const Hashmap& operator=(const Hashmap& other);
     */


};
