#pragma once
#include "song.h"
using namespace std;

class SongList {
	private:
		struct Node {
			Node * next;
			Song * data;
		};
		Node * head;
		int size;
	public:
		// default constructor
		SongList();
		// copy constructor
		SongList(const SongList & src);
		// destructor
		~SongList();
		// recursive destructor
		void recursiveDestroy(Node *& head);
		// copy assignment operator
		SongList & operator = (const SongList & src);	
    // overloaded output operator
    friend ostream & operator << (ostream & out, const SongList & src);
		// display entire list
		void display() const;
		// display recursively
		void display(Node * head) const;
		// add song to list in proper place
		bool addSong(Song * s);
		// display artist (songs sorted by likes)
		bool displayArtist(char * artistName) const; 
		// edit likes for a given song
		bool editLikes(char * songName, int likes);
    // generic remove song for given song name
    bool removeSong(char * songName);
		// remove songs under a given like threshold
		bool removeSongsUnder(int numLikes);
		// get length of list
		int getSize() const;
		// add song via parameters
		bool addSong(char * title, char * artist, float length, int likes);
};
