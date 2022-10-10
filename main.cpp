#include "main.h"
using namespace std;

int main() {
  char option = 'z';
  char * fileName = new char[10];
  strcpy(fileName, "songs.txt");
	SongList * sl = new SongList();

	cout << "Welcome to my list program." << endl;
	cout << endl << endl;
	// set initial data

	getData(fileName, *(sl));
	cout << "     " << sl->getSize() << " records read from " << fileName << endl;
	cout << endl << endl;
	// main program
	delete [] fileName;
	fileName = nullptr;
  while ((option = menu()) != 'q') {
    switch (option) {
      case 'd': {
        cout << *(sl);
        break;
      }
      case 'a': {
        cout << endl;
        cout << "Enter an artist name to display: ";
        char * artistName = getInput();
        if (!(sl->displayArtist(artistName))) {
          cout << endl;
          cout << "Artist not found." << endl;
          cout << endl;
        }
        if (artistName != nullptr) {
          delete [] artistName;
          artistName = nullptr;
        }
        break;
      }
      case 'e': {
        int likes;
        char * songName = nullptr;
        cout << endl;
        cout << "Enter a song name to edit the likes for: ";
        songName = getInput();
        cout << endl;
        cout << "How many likes would you like to change " << songName << " to? ";
        likes = getInt();
        if (!(sl->editLikes(songName, likes))) {
          cout << endl;
          cout << "Song not found." << endl;
          cout << endl;
        }
        if (songName != nullptr) {
          delete [] songName;
          songName = nullptr;
        }
        break;
      }
      case 'r': {
        int likes;
        cout << endl;
        cout << "Enter a likes threshold to remove all songs under: ";
        likes = getInt();
        if (!(sl->removeSongsUnder(likes))) {
          cout << endl;
          cout << "No songs removed." << endl;
          cout << endl;
        }
        break;
      }
      case 'q': {
        cout << endl;
        cout << "Thank you for using my program!" << endl;
        cout << endl;
      }
      default: {
        cout << endl;
        cout << "Choice not recognized." << endl;
        cout << endl;
      }
    }
  }
  delete sl;
  sl = nullptr;
}

// display menu and get user's choice
char menu() {
  char * input;
  cout << "DISPLAY   - Display Entire List" << endl;
  cout << "ARTIST    - Display Tracks For A Single Artist" << endl;
  cout << "EDIT      - Edit The Likes For A Given Track" << endl;
  cout << "REMOVE    - Remove All Songs Under A Given Likes Threshold" << endl;
  cout << "QUIT      - Quit This Program" << endl;
  cout << endl;
  cout << "Please enter your choice: ";
  input = getInput();
  for (int i = 0; i < static_cast<int>(strlen(input)); i++) {
    input[i] = tolower(input[i]);
  }
  if (strcmp("display", input) == 0) {
    delete [] input;
    input = nullptr;
    return 'd';
  }
  if (strcmp("artist", input) == 0) {
    delete [] input;
    input = nullptr;
    return 'a';
  }
  if (strcmp("edit", input) == 0) {
    delete [] input;
    input = nullptr;
    return 'e';
  }
  if (strcmp("remove", input) == 0) {
    delete [] input;
    input = nullptr;
    return 'r';
  }
  if (strcmp("quit", input) == 0) {
    delete [] input;
    input = nullptr;
    return 'q';
  }
  else {
    delete [] input;
    input = nullptr;
    return 'z';
  }
}

// get clean input
int getInt() {
  int input;
  cin >> input;
  while (!cin || input < 0) {
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Not a valid input. Try again: ";
    cin >> input;
  }
  cin.ignore(1, '\n');
  return input;
}

// get right sized input
char * getInput() {
	char * input = nullptr;
	char c;
	int currentSize = 0;
	while (cin.peek() != '\n' && cin.good()) {
		c = cin.get();
		currentSize += 1;
		if (input == nullptr) {
			// add one for null char
			input = new char[currentSize + 1];
			input[0] = c; 
			input[1] = '\0';
		}
		else {
			char * dummy = new char[currentSize + 1];
			// copy all elements from current array into new one
			strcpy(dummy, input);
			// append to end
			dummy[currentSize - 1] = c;
			dummy[currentSize] = '\0';
			// copy back into input
			delete [] input;
			input = nullptr;
			input = new char[currentSize + 1];
			strcpy(input, dummy);
			delete [] dummy;
			dummy = nullptr;
		}
	}
	// ignore end of line char
	cin.ignore(1, '\n');
	return input;
}

// get word until delimiter
char * getWord(ifstream & inFile, char delimiter) {
	char c;
	char * word = nullptr;
	int currentLength = 0;
	while (inFile.peek() != delimiter) {
		c = inFile.get();
		currentLength += 1;
		if (word == nullptr) {
			// new word
			word = new char[2];
			word[0] = c;
			word[1] = '\0';
		}
		else {
			char * dummy = new char[currentLength + 1];
			strcpy(dummy, word);
			dummy[currentLength - 1] = c;
			dummy[currentLength] = '\0';
			// delete previous verison of word
			delete [] word;
			word = nullptr;
			word = new char[currentLength + 1];
			strcpy(word, dummy);
			// delete dummy
			delete [] dummy;
			dummy = nullptr;
		}
	}
	inFile.ignore(1, delimiter);
	return word;
}

// get data from a csv to load into list
bool getData(char * fileName, SongList & sl) {
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		return false;
	}
	else {
		char * name = nullptr;
		char * artist = nullptr;
		float length = 0;
		int likes = 0;
		while (inFile.peek() != EOF) {
			if (name != nullptr) {
				delete [] name;
				name = nullptr;
			}
			if (artist != nullptr) {
				delete [] artist;
				artist = nullptr;
			}
			name = getWord(inFile, ',');
			artist = getWord(inFile, ',');
			inFile >> length;
			inFile.ignore(1,',');
			inFile >> likes;
			inFile.ignore(1,'\n');	
			// put into linked list
      Song * s = new Song(name, artist, length, likes);
			sl.addSong(s);
		}
		inFile.close();
		if (name != nullptr) {
			delete [] name;
			name = nullptr;
		}
		if (artist != nullptr) {
			delete [] artist;
			artist = nullptr;
		}
		return true;
	}
}
