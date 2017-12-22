#include "Song.h"
#include <set>
#include <fstream>

double get_norm(double, int, int);
std::string getStrRep(int note);

Song::Song() {
	matrix.resize(21);
	for (auto &x : matrix)
		x.resize(21);

	std::ifstream file("file1");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			file >> matrix[i][j];
		}
	}
	file.close();
	
	double sum;
	int k, val;
	int startingNote = 12;
	int currentNote = startingNote;
	song += "I[NYLON_STRING_GUITAR] " + getStrRep(currentNote + 48) + "i "; 
	for (int i = 0; i < SONG_LENGTH; i++) {
		sum = 0;
		k = 0;
		val = rand() % 1000;
		while (sum < val) {
			if (k >= 48) {
				currentNote = startingNote;
				sum = val + 1;
				k = 0;
			}
			sum += matrix[k][currentNote] * 1000.0;
			k++;
		}
		currentNote = k - 1;
		song += getStrRep(currentNote + 48) + "i ";
	}
}

Song::Song(Scale scale, int startingNote, std::vector<int> instruments) { 
	//matrix contains probability values for notes 36-84, i.e. 48 x 48 matrix
	matrix.resize(48);
	for (auto &x : matrix)
		x.resize(48);
	
	std::string pattern;

	switch ( scale ) {
		case MAJ:
			pattern = "2212221";
			break;
		case MINPEN:
			pattern = "22323";
			break;
		case NATMIN:
			pattern = "2122122";
			break;
	}

	int scaleLen = pattern.size();
	std::set<int> notes;

	int key = startingNote % 12;

	double sum, scalingFactor;
	int k, val;
	std::string temp;

	int currentNote = startingNote;

	for (int i = 0; i < scaleLen; i++) {
		temp = pattern[i];
		key = key + stoi(temp);
		notes.insert(key % 12);
	}

	for (int i = 0; i < 48; i++) {
		if (notes.find(i % 12) != notes.end()) {
			for (int j = 0; j < 48; j++) {
				if ((notes.find(j % 12) != notes.end()) && (abs(j - i) < 13))
					matrix[j][i] = 1;
			}
		}
	}

	for (int i = 0; i < 48; i++) {
		sum = 0;
		if (notes.find(i % 12) != notes.end()) {
			for (int j = 0; j < 48; j++) {
				if (matrix[j][i] == 1) {
					matrix[j][i] = get_norm((scaleLen), i, j);
					sum += matrix[j][i];
				}
			}
			scalingFactor = 1 / sum;
			for (int j = 0; j < 48; j++) {
				matrix[j][i] = matrix[j][i] * scalingFactor;
			}
		}
	}

	int numInstruments = instruments.size();

	std::vector<std::string> dur = { "h", "q", "i", "s" };
	int pos;

	currentNote = abs(currentNote - 36);
	song += getStrRep(currentNote + 36);
	pos = rand() % 4;
	song += dur[pos] + " ";

	for (int i = 1; i < SONG_LENGTH; i++) {
		for (int j = 0; j < numInstruments; j++) {
			temp = "V";
			temp += std::to_string(j) + " I[" + std::to_string(instruments[j]) + "] ";

			sum = 0;
			k = 0;
			val = rand() % 1000;
			while (sum < val) {
				sum += matrix[k % 48][currentNote % 48] * 1000.0;
				k++;
			}
			if (k == 0)
				k = 1;
			currentNote = k - 1;
			pos = rand() % 4;
			song += temp + getStrRep(currentNote + 36) + dur[pos] + " ";
		}
	}
	song[song.size() - 1] = 'V';
	song += "V30";
	//std::cout << song << std::endl;
	//build matrix according to scale, as instructed to by passed paramter
}

void Song::play() {
	CFugue::Player player;
	player.Play(song.c_str());
}

double get_norm(double sigma, int mu, int index) {
	double scale = 1 / (sqrt(2 * PI*(pow(sigma, 2))));
	double exp = (-1 * pow((index - mu), 2)) / (2 * pow(sigma, 2));

	return(scale*pow(E, exp));
}

std::string getStrRep(int note) {
	std::string rep = " [";
	std::string temp = std::to_string(note);
	
	rep += temp;
	rep += "]";

	return rep;
}
