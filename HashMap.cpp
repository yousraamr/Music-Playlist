//
//  Hashmap.cpp
// 
//  Hashmap using channing with array and linked list
//
//  Project Data structures
// 
//  Created by Mariam Jan, Yousra Amr, Rawan Jalal, Jana Ahmed, Mariam Mohamed
// 
//  presented to Dr Ashraf AbdelRaouf
//
//
#include "Hashmap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <SDL.h>
using namespace std;

//-- Definition of the class constructor

Hashmap::Hashmap() : mySize(0), myCapacity(INITIAL_CAPACITY)
{
    //readFromFile();
    arr = new NodePointer[myCapacity]();
    for (int i = 0; i < myCapacity; ++i) {
        arr[i] = nullptr;
    }
    readFromFile();
}


//-- Definition of the destructor    
Hashmap::~Hashmap()
{
    for (int i = 0; i < myCapacity /*mySize*/; ++i)
    {
        NodePointer current = arr[i];
        while (current != nullptr)
        {
            NodePointer temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] arr;
}

//-- Definition of hashfunction
int Hashmap::hashFunction(string key)
{
    return stoi(key) % myCapacity;
}


//-- Definition of insert
void Hashmap::insert(ElementType key, ElementType title, ElementType artist, ElementType album, double duration, ElementType songPath)
{
    int index = hashFunction(key);
    NodePointer newNode = new Node(key, title, artist, album, duration, songPath);
    cout << arr[index] << endl;
    if (arr[index] == nullptr) {
        arr[index] = newNode;
    }
    else {
        NodePointer current = arr[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    mySize++;
    writeToFile();
}


//-- Definition of search
string Hashmap::search(string key)
{
    for (int i = 0; i < myCapacity; ++i) {
        NodePointer current = arr[i];
        while (current != nullptr) {
            if (current->key == key) {
                return "Song found";
            }
            current = current->next;
        }
    }
    return "Song not found";

}




//-- Definition of erase
void Hashmap::erase(string key)
{
    int index = hashFunction(key);
    NodePointer current = arr[index];
    NodePointer prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev != nullptr) {
            prev->next = current->next;
        }
        else {
            arr[index] = current->next;
        }
        delete current;
        mySize--;
    }
    writeToFile();
}


// Definition of empty
bool Hashmap::empty()
{
    return mySize == 0;
}


//-- Definition of display
void Hashmap::display(ostream& out) const
{
    for (int i = 0; i < myCapacity /*mySize*/; ++i) {
        out << "Index " << i << ": ";
        NodePointer current = arr[i];
        while (current != nullptr) {
            out << "[" << "Key: " << current->key << "_Title: " << current->title << "_Artist: " << current->artist << "_Album: " << current->album << "_songpath: " << current->songPath << "_Duration: " << current->duration << "] ";
            current = current->next;
        }
        out << endl;
    }
}


//-- Definition of shuffle
void Hashmap::shuffle()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = myCapacity - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

// --Definition of countNodes
int Hashmap::countNodes()
{
    int nodeCount = 0;
    for (int i = 0; i < myCapacity /*mySize*/; ++i) {
        NodePointer current = arr[i];
        while (current != nullptr) {
            nodeCount++;
            current = current->next;
        }
    }
    return nodeCount;
}

//-- Definition of get Node By Key

string Hashmap::getsongPathByKey(string key)
{
    int index = hashFunction(key);
    Node* currentNode = arr[index];

    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode->songPath;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}


//-- Definition of play function
int Hashmap::playSong(string key)
{
    string songpath = getsongPathByKey(key);
    if (!songpath.empty()) {
        // Load music file
        const char* musicFile = songpath.c_str(); // Convert string to const char*

        // Initialize SDL
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return -1;
        }

        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8* wavBuffer;

        if (SDL_LoadWAV(musicFile, &wavSpec, &wavBuffer, &wavLength) == NULL) {
            std::cout << "Failed to load music file! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return -1;
        }

        SDL_AudioDeviceID audioDevice;
        SDL_AudioSpec desiredSpec;
        desiredSpec.freq = wavSpec.freq;
        desiredSpec.format = AUDIO_S16;
        desiredSpec.channels = wavSpec.channels;
        desiredSpec.samples = 4096;
        desiredSpec.callback = nullptr;

        audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, nullptr, 0);
        if (audioDevice == 0) {
            std::cout << "Failed to open audio: " << SDL_GetError() << std::endl;
            SDL_FreeWAV(wavBuffer);
            SDL_Quit();
            return -1;
        }

        SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
        SDL_PauseAudioDevice(audioDevice, 0);

        bool paused = false;
        cout << "Press 1 to pause." << endl;
        cout << "Press 2 to exit song." << endl;
        cout << "Press 3 to play the next song." << endl; // Added option for next song

        while (true) {
            if (_kbhit()) {
                char userInput = _getch();

                if (userInput == '2') {
                    break;
                }

                if (userInput == '1') {
                    if (!paused) {
                        SDL_PauseAudioDevice(audioDevice, 1);
                        cout << "Song paused. Press '1' to resume..." << endl;
                        paused = true;
                    }
                    else {
                        SDL_PauseAudioDevice(audioDevice, 0);
                        cout << "Song resumed." << endl;
                        paused = false;
                    }
                }

                if (userInput == '3') {
                    SDL_CloseAudioDevice(audioDevice);
                    SDL_FreeWAV(wavBuffer);
                    SDL_Quit();
                    int nextKey = stoi(key) + 1; // Simulated logic for the next song's key
                    return playSong(to_string(nextKey)); // Play the next song
                }
            }

            SDL_Delay(100); // Reduce CPU usage
        }

        SDL_CloseAudioDevice(audioDevice);
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
    }
    else {
        return -1;
    }
}



//-- Definition of moveSong To Position
void Hashmap::moveSongToPosition(string key, int desiredIndex)
{
    if (desiredIndex < 0 || desiredIndex >= myCapacity) {
        cout << "Desired index is out of bounds." << endl;
        return;
    }

    int currentIndex = hashFunction(key);
    if (currentIndex == desiredIndex) {
        cout << "Song is already at the desired index." << endl;
        return;
    }

    // Remove the node with the given key from its current position
    NodePointer current = arr[currentIndex];
    NodePointer prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Song with the given key not found in the hash map." << endl;
        return;
    }

    if (prev != nullptr) {
        prev->next = current->next;
    }
    else {
        arr[currentIndex] = current->next;
    }

    // Insert the node at the desired index as the first node
    current->next = arr[desiredIndex]; // Link the current node to the existing list
    arr[desiredIndex] = current; // Set current node as the first node at desired index

}




//-- Definition of writeToFile
void Hashmap::writeToFile()
{
    ofstream file("Playlist.txt");
    if (file.is_open()) {
        for (int i = 0; i < myCapacity; ++i) {
            NodePointer current = arr[i];
            while (current != nullptr) {
                file << current->key << ",\"" << current->title << "\",\"" << current->artist << "\",\"" << current->album << "\"," << current->duration << " " << current->songPath << "\"" << endl;
                current = current->next;
            }
        }
        file.close();
        cout << "Data written to file successfully." << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }


}


//-- Definition of readToFile
void Hashmap::readFromFile()
{
    ifstream file("Playlist.txt");
    if (file.is_open()) {
        string key;
        string title, artist, album, songPath;
        double duration;

        while (file >> key >> title >> artist >> album >> duration >> songPath) {
            insert(key, title, artist, album, duration, songPath);
        }

        if (file.eof()) {
            cout << "Data read from file successfully." << endl;
        }
        else if (file.fail()) {
            cout << "Error: Failed to read data from file due to a formatting error." << endl;
        }
        else if (file.bad()) {
            cout << "Error: Critical i/o error occurred while reading the file." << endl;
        }

        file.close();
    }
    else {
        cout << "Error: Unable to open file." << endl;
    }
    /*
    ifstream file("Playlist.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);

            string key;
            string title, artist, album, songPath;
            double duration;

            if (iss >> key getline(iss >> ws, key, ',')) {
                // Extract the key
                getline(iss >> ws, title, ',');  // Read the title until a comma, ignoring leading whitespace
                getline(iss >> ws, artist, ','); // Read the artist until a comma, ignoring leading whitespace
                getline(iss >> ws, album, ',');// Read the album until a comma, ignoring leading whitespace
                iss >> duration>> songPath;
                // Insert the data if successfully extracted
                insert(key, title, artist, album, duration, songPath);
            }
            else {
                cout << "Error: Formatting issue while reading data from the file." << endl;
                break;
            }
        }

        if (file.eof()) {
            cout << "Data read from file successfully." << endl;
        }
        else {
            cout << "Error: Failed to read data from file completely or unexpected issue occurred." << endl;
        }

        file.close();
    }
    else {
        cout << "Error: Unable to open file." << endl;

    }*/
}