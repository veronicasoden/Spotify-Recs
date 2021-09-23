//
// Created by Veronica  Soden  on 4/17/21.
//

#ifndef PROJ3_SONG_H
#define PROJ3_SONG_H

#include <string>
#include <vector>

using namespace std;

class song
{
public:
    vector<string> artists; //if more than one it's " if one it starts with bracket [ and name is still ex: ['artist name']
    //if more than one artist: "['artist 1', 'artist 2']"
    float danceability;
    int duration;
    float energy;
    bool explicitness;
    float instrumentalness;
    float loudness;
    string songName;
    int popularity;
    float speechiness;
    float tempo;
    float valence;
    int year;
    vector<string> genres;

    int fitness;
};

#endif //PROJ3_SONG_H
