#include "songList.h"
using namespace std;

// default constructor
SongList::SongList() {
	this->head = nullptr;
	this->size = 0;
}
// copy constructor
SongList::SongList(const SongList & src) {
  // create new node and set its data (new song)
  this->head = new Node();
  this->head->data = new Song(*(src.head->data));
  // create current nodes for this and src
  Node * current = src.head;
  Node * thisCurrent = this->head;
  // cycle thru list
  while(current->next != nullptr) {
    // create new node and set its data (new song)
    thisCurrent->next = new Node();
    thisCurrent->next->data = new Song(*(current->next->data));
    // advance to next node
    current = current->next;
    thisCurrent = thisCurrent->next;
  }
}
// destructor
SongList::~SongList() {
	Node * current = this->head;
	while (current != nullptr) {
		this->head = this->head->next;
		delete current->data;
		delete current;
		current = this->head;
	}
}
// copy assignment operator
SongList & SongList::operator = (const SongList & src) {
  if (&src != this) {
    Node * current = this->head;
  	while (current != nullptr) {
  		this->head = this->head->next;
  		delete current->data;
  		delete current;
  		current = this->head;
  	}
    // create new node and set its data (new song)
    this->head = new Node();
    this->head->data = new Song(*(src.head->data));
    // create current nodes for this and src
    current = src.head;
    Node * thisCurrent = this->head;
    // cycle thru list
    while(current->next != nullptr) {
      // create new node and set its data (new song)
      thisCurrent->next = new Node();
      thisCurrent->next->data = new Song(*(current->next->data));
      // advance to next node
      current = current->next;
      thisCurrent = thisCurrent->next;
    }
  }
	return *this;
}
// overloaded outpu operator
ostream & operator << (ostream & out, const SongList & src) {
  src.display();
  return out;
}
// display all songs
void SongList::display() const {
  cout << endl << endl;
	Node * current = this->head;
	cout << left;
	cout << setw(30) << "NAME";
	cout << setw(20) << "ARTIST";
	cout << setw(8) << "LENGTH";
	cout << setw(10) << "LIKES" << endl;
	while (current != nullptr) {
		current->data->display();
		current = current->next;
	}
	cout << endl << endl;
}
// add song to list in proper place : sort by likes
void SongList::addSong(Song * s) {
	Node * n = new Node();
	n->data = s;
	Node * current = this->head;
	Node * previous = nullptr;

	// if list is empty
	if (current == nullptr) {
		// insert at start of list
		this->head = n;
		n->next = nullptr;
	}
	// else list is not empty
	else {
		// traverse to right spot in list
		while (current != nullptr) {
			if (n->data->getLikes() < current->data->getLikes()) {
				break;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
		// if inserting at start of list
		if (current == head) {
			n->next = this->head;
			this->head = n;
		}
		// if inserting at end of list
		else if (current == nullptr) {
			previous->next = n;
			n->next = nullptr;
		}
		// else regular insertion
		else {
			previous->next = n;
			n->next = current;
		}
	}
	this->size += 1;
}
// display artist (songs sorted by likes)
bool SongList::displayArtist(char * artistName) const {
  Node * current = this->head;
  bool found = false;
  char * artist = nullptr;
  cout << endl;
  while (current != nullptr) {
    artist = current->data->getArtist();
    if (strcmp(artistName, artist) == 0) {
      cout << *(current->data);
      found = true;
    }
    if (artist != nullptr) {
      delete [] artist;
      artist = nullptr;
    }
    current = current->next;
  }
  cout << endl;
  return found;
}
// edit likes for a given song
bool SongList::editLikes(char * songName, int likes) {
  Node * current = this->head;
  char * name = nullptr;
  bool found = false;
  while (current != nullptr) {
    name = current->data->getName();
    if (strcmp(name, songName) == 0) {
      current->data->setLikes(likes);
      Song * newSong = new Song(*(current->data));
      this->removeSong(songName);
      this->addSong(newSong);
      if (name != nullptr) {
        delete [] name;
        name = nullptr;
      }
      return true;
    }
    if (name != nullptr) {
      delete [] name;
      name = nullptr;
    }
    current = current->next;
  }
  cout << endl;
	return found;
}
// generic remove song given song name
bool SongList::removeSong(char * songName) {
  Node * current = this->head;
  Node * previous = nullptr;
  bool found = false;
  char * song = nullptr;
  while (current != nullptr) {
    song = current->data->getName();
    if (strcmp(song, songName) == 0) {
      // song found. remove it
      if (current == this->head) {
        // remove first node
        this->head = this->head->next;
        delete current->data;
        delete current;
        current = this->head;
        found = true;
        this->size--;
      }
      else if (current->next == nullptr) {
        // remove last node
        previous->next = nullptr;
        delete current->data;
        delete current;
        current = nullptr;
        found = true;
        this->size--;
      }
      else {
        // regular removal
        previous->next = current->next;
        delete current->data;
        delete current;
        // reset current
        current = previous->next;
        found = true;
        this->size--;
      }
    }
    else {
      previous = current;
      current = current->next;
    }
    if (song != nullptr) {
      delete [] song;
      song = nullptr;
    }
  }
  cout << endl;
	return found;
}
// remove songs under a given like threshold
bool SongList::removeSongsUnder(int numLikes) {
  Node * current = this->head;
  Node * previous = nullptr;
  bool found = false;
  while (current != nullptr) {
    if (current->data->getLikes() < numLikes) {
      // song found. remove it
      if (current == this->head) {
        // remove first node
        this->head = this->head->next;
        delete current->data;
        delete current;
        current = this->head;
        found = true;
        this->size--;
      }
      else if (current->next == nullptr) {
        // remove last node
        previous->next = nullptr;
        delete current->data;
        delete current;
        current = nullptr;
        found = true;
        this->size--;
      }
      else {
        // regular removal
        previous->next = current->next;
        delete current->data;
        delete current;
        // reset current
        current = previous->next;
        found = true;
        this->size--;
      }
    }
    else {
      previous = current;
      current = current->next;
    }
  }
  cout << endl;
	return found;
}
// get lenght of the list
int SongList::getSize() const {
	return this->size;
}
