//
// Created by Veronica  Soden  on 4/17/21.
//

#ifndef PROJ3_PLAYLIST_H
#define PROJ3_PLAYLIST_H

#include <queue>
#include <vector>
#include <string>
#include <map>
#include "song.h"
#include "BST.h"
#include "Survey.h"

using namespace std;

class playlist {
public:
    BST* tree;
    vector<song> songQ;
    string playName;
    int avgBasicness;
    float avgDanceability;
    map<string, int> mostCommonArtist;

    playlist(vector<song> catalog, Survey surveyRes, int cap);
    void shuffle(void);
    map<string, int> topArtists(void);

private:
    vector<string> likedGenres;
    string mainGenre;
    vector<bool> songTimes;
    bool instrumental;
    bool energy;
    bool explicits;
    bool fastTempo;
    bool happy;
    bool loud;

};

#endif //PROJ3_PLAYLIST_H