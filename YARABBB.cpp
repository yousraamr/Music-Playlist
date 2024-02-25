//
//  Hashmap.cpp ****main*****
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
#include <SDL.h>
#include<cstdlib>
#include <string>
using namespace std;
void displayMenu()
{
    cout << "====== Playlist Menu ======" << endl;
    cout << "1. Add a song" << endl;
    cout << "2. Search for a song name" << endl;
    cout << "3. Remove a song" << endl;
    cout << "4. Playlist empty or not" << endl;
    cout << "5. Display playlist" << endl;
    cout << "6. Number of songs on the playlist" << endl;
    cout << "7. Play the playlist" << endl;
    cout << "8. If you want to move the song to diff position" << endl;
    cout << "9. Shuffle the songs" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";
}
int main(int argc, char* argv[]) {

    Hashmap playlist;
    int x;
    do {
        displayMenu();
        cin >> x;
        switch (x) {
        case 1: {
            cout << "Enter song number:" << endl;
            cout << "1-Odam Oyoonak" << endl;
            cout << "2-Foo' Ma Elinta Feeh" << endl;
            cout << "3-Shoft El Ayam" << endl;
            cout << "4-Aftah El Tariaa Yabny" << endl;
            cout << "5-Sabah Wu Masaa" << endl;
            int y;
            cin >> y;
            if (y == 1)
            {
                string key = "1";
                double duration = 3.48;
                string title = "Odam Oyoonak", artist = "Amr Diab", album = "Kammel Kalamak", songPath = "C:\\Users\\Administrator\\Desktop\\song\\Amr Diab _ Odam Oyoonak (M4A_128K).wav";
                playlist.insert(key, title, artist, album, duration, songPath);
            }
            else if (y == 2)
            {
                string key = "2";
                double duration = 4.30;
                string title = "Foo' Ma Elinta Feeh", artist = "Amr Diab", album = "El Leila", songPath = "C:\\Users\\Administrator\\Desktop\\song\\Amr Diab -- Foo_ Ma Elinta Feeh(M4A_128K).wav";
                playlist.insert(key, title, artist, album, duration, songPath);
            }
            else if (y == 3)
            {
                string key = "3";
                double duration = 4.42;
                string title = "Shoft El Ayam", artist = "Amr Diab", album = "Shoft El Ayam", songPath = "C:\\Users\\Administrator\\Desktop\\song\\Amr Diab ... Shoft El Ayam(M4A_128K).wav";
                playlist.insert(key, title, artist, album, duration, songPath);
            }
            else if (y == 4)
            {
                string key = "4";
                double duration = 0.16;
                string title = "Aftah El Tariaa Yabny", artist = "Unknown Artist", album = "Unknown", songPath = "C:\\Users\\Administrator\\Desktop\\song\\aftah el tariaa yabny.wav";
                playlist.insert(key, title, artist, album, duration, songPath);
            }
            else if (y == 5)
            {
                string key = "5";
                double duration = 4.39;
                string title = "Sabah Wu Masaa", artist = "Fairuz", album = "Wala Keef", songPath = "C:\\Users\\hp\\Downloads\\sabhu w masa -- fairuz.wav";
                playlist.insert(key, title, artist, album, duration, songPath);
            }
            break;
        }
        case 2:
        {
            cout << "Enter song number:" << endl;
            cout << "1-Odam Oyoonak" << endl;
            cout << "2-Foo' Ma Elinta Feeh" << endl;
            cout << "3-Shoft El Ayam" << endl;
            cout << "4-Aftah El Tariaa Yabny" << endl;
            cout << "5-Sabah Wu Masaa" << endl;
            string key;
            cin >> key;
            string songName = playlist.search(key);
            if (songName != "Song not found") {
                cout << "Song found: " << songName << endl;
            }
            else {
                cout << "Song not found!" << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Which song you want to remove from the PlayList:" << endl;
            cout << "1-Odam Oyoonak" << endl;
            cout << "2-Foo' Ma Elinta Feeh" << endl;
            cout << "3-Shoft El Ayam" << endl;
            cout << "4-Aftah El Tariaa Yabny" << endl;
            cout << "5-Sabah Wu Masaa" << endl;
            string key;
            cin >> key;
            playlist.erase(key);
            cout << "Song removed from the playlist!" << endl;
            break;
        }
        case 4:
        {
            if (playlist.empty()) {
                cout << "Playlist is empty." << endl;
            }
            else {
                cout << "Playlist is not empty." << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Displaying playlist:" << endl;
            playlist.display(cout);
            break;
        }
        case 6:
        {
            int totalNodes = playlist.countNodes();
            cout << "Total number of songs in the playlist is: " << totalNodes << endl;
            break;
        }
        case 7:
        {
            cout << "Which song you want to play:" << endl;
            cout << "1-Odam Oyoonak" << endl;
            cout << "2-Foo' Ma Elinta Feeh" << endl;
            cout << "3-Shoft El Ayam" << endl;
            cout << "4-Aftah El Tariaa Yabny" << endl;
            cout << "5-Sabah Wu Masaa" << endl;
            string key;
            cin >> key;
            int songName = playlist.playSong(key);
            if (songName != -1) {
                cout << "Song found: " << songName << endl;
            }
            else {
                cout << "Song not found!" << endl;
            }

            break;
        }
        case 8:
        {
            cout << "Enter song you want to move and its new order:" << endl;
            cout << "1-Odam Oyoonak" << endl;
            cout << "2-Foo' Ma Elinta Feeh" << endl;
            cout << "3-Shoft El Ayam" << endl;
            cout << "4-Aftah El Tariaa Yabny" << endl;
            cout << "5-Sabah Wu Masaa" << endl;
            string key;
            cin >> key;
            int y;
            cin >> y;
            playlist.moveSongToPosition(key, y);
            cout << "\nPlaylist after moving song with key " << key << " to position " << y << ":" << endl;
            playlist.display(cout);
            break;
        }
        case 9:
        {
            cout << "Shuffling playlist:" << endl;
            playlist.shuffle();
            playlist.display(cout);
            break;
        }
        case 10:
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }


    } while (x != 9);

    return 0;

}

