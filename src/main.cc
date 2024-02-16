// William Galvin, 2023
// Usage:
// make && ./songrams "<some phrase here>"

#include "Trie.h"
#include "StrUtils.h"

#include <iostream> 
#include <fstream> 
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::unordered_map;

#define N_SONGS 1000000
#define DELIM "|"
#define DELIM_LEN 1

struct Song {
	string title;
	string artist;
};

// Read from file song names, which are then stored in songs as return parameter
//	Hashmap artisits maps song title -> artist
//	File_name contains text where each line is a song title and artist, separated by DELIM
void get_songs(vector<string>& songs, unordered_map<string, Song>& artisits, string file_name);

int main(int argc, char** argv) {

	if (argc != 2) {
		print_usage(argv[0]);
		exit(-1);
	}

	string target = trim(argv[1]);

	vector<string> songs;
	unordered_map<string, Song> artists;
	get_songs(songs, artists, "data/titles.txt");

	Trie trie;
	trie.add(" ");
	for (auto& song : songs) {
		trie.add(song);
	}

	vector<string> results = trie.search(target);	
	for (auto& u_title : results) {
		if (u_title == " ") {
			continue;
		}
		cout << artists[u_title].title << endl << artists[u_title].artist << endl;
	}
}

void get_songs(vector<string>& songs, unordered_map<string, Song>& artists, string file_name) {
	songs.reserve(N_SONGS);
	
	string tmp;
	ifstream titles(file_name);
	while (getline(titles, tmp)) {
		size_t idx = tmp.find(DELIM);
		string title = tmp.substr(0, idx);
		string artist = tmp.substr(idx + DELIM_LEN, tmp.length());
		
		if (title.length() >= 1) {
			songs.push_back(title);
			artists[to_upper(title)] = {title, artist};
		}
	}
}
