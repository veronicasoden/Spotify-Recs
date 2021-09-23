#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iterator>
#include "playlist.h"
#include "song.h"
#include "BST.h"
#include "Survey.h"
#include "Node.h"
#include "BST.h"

using namespace std;

//playlist constructor
playlist::playlist(vector<song> catalog, Survey surveyRes, int cap) {
    this->playName = surveyRes.playlistName;

    this->likedGenres = surveyRes.favGenres;
    this->mainGenre = surveyRes.favGenre;
    this->songTimes = surveyRes.favDecades;
    this->instrumental = surveyRes.isInstrumental;
    this->explicits = surveyRes.includeExplicit;
    this->fastTempo = surveyRes.fastTempo;
    this->happy = surveyRes.isHappy;
    this->loud = surveyRes.isLoud;

    this->tree = new BST();

    this->avgBasicness = 0;
    this->avgDanceability = 0;

    int genreCount = 0;
    int points = 0;

    vector<song>::iterator it = catalog.begin();
    while(it != catalog.end()) {
        //add points for genres, 2 points if main genre, cap at 5 points for genres
        //if they like all genres dont need to enter for loop
        if(likedGenres.size() >= 13) {
            points = 5;
            genreCount = 5;
        }
        else {
            for(int i = 0; i < it->genres.size(); i++) {
                if (genreCount > 4) {
                    break;
                }
                if (it->genres[i].find(mainGenre) != string::npos) {
                    points += 2;
                    genreCount += 2;
                }
                //if ascii value is < 0 = not valid ascii
                else if(mainGenre == "foreign") {
                    for(int k = 0; k < it->songName.length(); k++) {
                        if(int((it->songName)[k]) < 0) {
                            points+=2;
                            genreCount+=2;
                            break;
                        }
                    }
                }
                else {
                    for (int j = 0; j < likedGenres.size(); j++) {
                        //if ascii value is < 0 = not valid ascii 
                        if (likedGenres[j] == "foriegn") {
                            for (int k = 0; k < it->songName.length(); k++) {
                                if (int((it->songName)[k]) < 0) {
                                    points++;
                                    genreCount++;
                                    break;
                                }
                            }
                        }
                        if (it->genres[i].find(likedGenres[j]) != string::npos) {
                            points++;
                            genreCount++;
                        }
                    }
                }
            }
        }
        //song time period : 1st = 1920-1950, 2nd = 1960-1970, 3rd = 1980-1990, 4th = 2000-2020
        if(songTimes[0] && (it->year < 1960)) {
            points+=3;
        }
        else if(songTimes[1] && (it->year < 1980) && (it->year >= 1960)) {
            points+=3;
        }
        else if(songTimes[2] && (it->year < 2000) && (it->year >= 1980)) {
            points+=3;
        }
        else if(songTimes[3] && (it->year >= 2000)) {
            points+=3;
        }
        //instrumental bool = instrumental data and speechiness data
        if(instrumental) {
            if(it->instrumentalness >= 0.6) {
                points++;
            }
        }
        else {
            if(it->instrumentalness < 0.6) {
                points++;
            }
        }
        //fast tempo bool = tempo data
        if(fastTempo) {
            if(it->tempo >= 100) {
                points++;
            }
        }
        else {
            if(it->tempo < 100) {
                points++;
            }
        }
        //happy bool = valence (high) data
        if(happy) {
            if(it->valence >= 0.5) {
                points+=2;
            }
        }
        else {
            if(it->valence < 0.5) {
                points+=2;
            }
        }
        //loud bool = loud data
        if(loud) {
            if(it->loudness >= -12) {
                points++;
            }
        }
        else {
            if(it->loudness < -12) {
                points++;
            }
        }
        //explicit bool = explicit data
        if(!explicits) {
            if(it->explicitness) {
                points = 0;
            }
        }
        //how fit it is according to user survey inputs
        it->fitness = points;

        if(points >= cap) {
            if(!this->tree->insert(it.base())) {
                cout << "Error for: " << it->songName << endl;
                break;
            }
            //calculate fun outputs
            this->avgBasicness += it->popularity;
            this->avgDanceability += it->danceability;
            for(int i =0; i < it->artists.size(); i++) {
                map<string, int>::iterator it2 = mostCommonArtist.find(it->artists[i]);
                if(it2 != mostCommonArtist.end()) {
                    mostCommonArtist[it->artists[i]]++;
                }
                else {
                    mostCommonArtist[it->artists[i]] = 1;
                }
            }
        }
        it++;
        points = 0;
        genreCount = 0;
    }
    if(this->tree->size > 1) {
        this->avgBasicness = floor(this->avgBasicness / this->tree->size);
        this->avgDanceability = (this->avgDanceability / this->tree->size);
    }
    return;
}

//shuffles songs using random generator to insert random songs into new tree unbalanced BST
//and then calling post order traversal again
void playlist::shuffle() {
    vector<song> songsToShuffle = this->songQ;
    delete(this->tree);
    this->tree = new BST();
    int insertSong = rand() % songsToShuffle.size();
    while(songsToShuffle.size()) {
        if(!this->tree->insert(&songsToShuffle[insertSong])) {
            cout << "Error for: " << songsToShuffle[insertSong].songName << endl;
            break;
        }
        songsToShuffle.erase(songsToShuffle.begin() + insertSong);
        if(!songsToShuffle.empty()) {
            insertSong = rand() % songsToShuffle.size();
        }
    }
    this->songQ = this->tree->traversePostOrder(this->tree->root);
    return;
}

map<string, int> playlist::topArtists(void) {
    map<string, int> top5Artists;
    if(this->mostCommonArtist.size()) {
        int c = 0;
        map<string, int>::iterator it;
        map<string, int>::iterator it2;
        for (it = mostCommonArtist.begin(); it != mostCommonArtist.end(); it++) {
            if(top5Artists.size() < 5) {
                top5Artists[it->first] = it->second;
                for(it2 = top5Artists.begin(); it2 != top5Artists.end(); it2++) {
                    c = min(c, it2->second);
                }
            }
            else if(it->second > c) {
                for(it2 = top5Artists.begin(); it2 != top5Artists.end(); it2++) {
                    if(it->second > it2->second) {
                        top5Artists.erase(it2->first);
                        top5Artists[it->first] = it->second;
                        c = it->second;
                        break;
                    }
                }
                for(it2 = top5Artists.begin(); it2 != top5Artists.end(); it2++) {
                    c = min(c, it2->second);
                }
            }
        }
    }
    return top5Artists;
}
