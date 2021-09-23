//
// Created by Maia Gervasone on 4/17/21.
//

#ifndef POTENTIAL_CARNIVAL_SURVEY_H
#define POTENTIAL_CARNIVAL_SURVEY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Survey {
public:
    string playlistName;
    vector<string> favGenres;
    string favGenre;
    bool isInstrumental; //0 = Lyrics; 1 = Instrumental
    bool isEnergetic; //0 = Calming; 1 = Energetic
    bool includeExplicit; //0 = No; 1 = Yes
    bool fastTempo; //0 = slow; 1 = fast
    vector<bool> favDecades; //
    bool isHappy; //0 = sad/angry; 1 = happy
    bool isLoud; //0 = quiet; 1 = loud
};

#endif //POTENTIAL_CARNIVAL_SURVEY_H
