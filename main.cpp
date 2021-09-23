#include "song.h"
#include "playlist.h"
#include "Survey.h"
#include "BST.h"
#include "Node.h"
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;


Survey readSurvey();
vector<string>getGenres(string genreNums);
void readFiles(vector<song>&);
void shellSortWithTimeOutput(vector<song>);
int Shellsort(song arr[], int n);
void merge(song arr[], int left, int mid, int right);
void mergeSort(song arr[], int left, int right);
void mergeArrayWithTimeOutput(vector<song>);
void mergeSortPlaylist(vector<song>playlist);
void generatePlaylist(Survey results, vector<song>SongCatalog);
void print();


int main() {
     
    cout << "Welcome to the Potential Carnival!" << endl;
    cout << endl;
    cout << "Crunching Music Data" << endl;
    cout << ". . . " << endl;
    //*****Generates SongCatalog*****
    vector<song> SongCatalog;
    readFiles(SongCatalog);
    cout << endl;

    cout << "Sorting Music Data " << endl;
    cout << ". . . " << endl;
    cout << endl;
    shellSortWithTimeOutput(SongCatalog);
    mergeArrayWithTimeOutput(SongCatalog);
    cout << endl;
    
    //*****Survey*****
    cout << "Now let's answer some question so that we can generate a playlist for you!" << endl;
    Survey results = readSurvey(); //reads in survey results
    cout << "Thank you for completing the survey! " << endl;

    //****Generates Playlist*****
    cout << "Generating Playlist Now " << endl;
    cout << " . . . " << endl;
    generatePlaylist(results, SongCatalog);

        
    cout << endl;
    cout << "Thank you for using the Potential Carnival!" << endl;
    cout << "And special thanks to spotify for providing the data!" << endl;
    print();

    return 0;
}

Survey readSurvey() {
    //returns survey object of results so that playlist can be generated and accounts for input errors
    bool invalidResult = false;
    bool surveyComplete = false;
    Survey results;

    while(!surveyComplete) {

        bool invalidResult = false;

        while (invalidResult == false) {
            cout << endl;

            cout << "What do you want to name your playlist?" << endl;
            getline(cin, results.playlistName);

            cout << "What are your favorite genres?" << endl;
            cout << "Input should be a list of lowercase letters without spaces, ex: R&B and Jazz  is 'dg'. " << endl;
            string genreNums;
            cout << "a.)Pop" << endl << "b.)Hip-Hop" << endl << "c.)Rap" << endl << "d.)R&B" << endl << "e.)Rock"
                 << endl << "f.)Electronic" << endl << "g.)Alternative" << endl << "h.)Instrumental" << endl <<
                 "i.)Country" << endl << "j.)Jazz" << endl << "k.)Classical" << endl << "l.)Reggae" << endl <<
                 "m.)Foreign" << endl << "n.)No preference, I enjoy all types" << endl;
            cin >> genreNums;
            results.favGenres = getGenres(genreNums);
            if (results.favGenres.size() == 0) {
                invalidResult = true;
                cout << "You're answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            string genre;
            cout << endl;
            cout << "If you had to pick one, which is your favorite genre?" << endl;
            cout << "Type out the corresponding letter, ex Jazz: 'j' " << endl;
            cout << "a.)Pop" << endl << "b.)Hip-Hop" << endl << "c.)Rap" << endl << "d.)R&B" << endl << "e.)Rock"
            << endl << "f.)Electronic" << endl << "g.)Alternative" << endl << "h.)Instrumental" << endl << 
            "i.)Country" << endl << "j.)Jazz" << endl << "k.)Classical" << endl << "l.)Reggae" << endl << 
            "m.)Foreign" << endl;
            cin >> genre;
            if(genre.size() > 1) {
            invalidResult = true;
            cout << "Your answer was not formatted correctly!" << endl;
            cout << "Generating another survey... "<< endl;
            break;
            }
            results.favGenre = getGenres(genre)[0];


            string ans;
            cout << endl;
            cout << "Do you prefer songs that are more instrumental (less lyrics, more music) or songs with more lyrics?"
                 << endl;
            cout << "Enter 1 if instrumental, 2 if more lyrics" << endl;
            cin >> ans;
            if (ans == "1")
                results.isInstrumental = true;
            else if (ans == "2")
                results.isInstrumental = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << endl;
            cout << "Do you prefer songs that are more energetic or more calming?" << endl;
            cout << "Enter 1 if energetic, 2 if more calming" << endl;
            cin >> ans;
            if (ans == "1")
                results.isEnergetic = true;
            else if (ans == "2")
                results.isEnergetic = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << endl;
            cout << "Do you want explicit songs to be included?" << endl;
            cout << "Enter 1 if yes, 2 if not" << endl;
            cin >> ans;
            if (ans == "1")
                results.includeExplicit = true;
            else if (ans == "2")
                results.includeExplicit = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << endl;
            cout << "Do you prefer songs with a faster or slower tempo?" << endl;
            cout << "Enter 1 if faster, 2 if slower" << endl;
            cin >> ans;
            if (ans == "1")
                results.fastTempo = true;
            else if (ans == "2")
                results.fastTempo = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << endl;
            cout << "What decade(s) of music do you prefer?" << endl;
            cout << "1.) 1920-1950 2.) 1960-1970 3.) 1980-1990 4.) 2000-2020 " << endl;
            cout << "Enter the corresponding numbers in a line without any spaces, ex: 1980 - 1990 & 2000 - 2020 '34' " << endl;
            cin >> ans;
            for(int i = 0; i < 4; i ++)
            {
                results.favDecades.push_back(false);
            }
            for(int i = 0; i < ans.size(); i ++)
            {
                bool valid = false;
                if (int(ans[i]) == 49)
                {
                    results.favDecades[0] = true;
                    valid = true;
                }
                if (int(ans[i]) == 50)
                {
                    results.favDecades[1] = true;
                    valid = true;
                }
                if (int(ans[i]) == 51)
                {
                    results.favDecades[2] = true;
                    valid = true;
                }
                if (int(ans[i]) == 52)
                {
                    results.favDecades[3] = true;
                    valid = true;
                }
                if(!valid || ans.size() > 4) {
                    invalidResult = true;
                    cout << "Your answer was not formatted correctly!" << endl;
                    cout << "Generating another survey... " << endl;
                    break;
                }

            }

            cout << endl;
            cout << "Do you prefer happy or sad music?" << endl;
            cout << "Enter 1 if happy, 2 if sad" << endl;
            cin >> ans;
            if (ans == "1")
                results.isHappy = true;
            else if (ans == "2")
                results.isHappy = false;
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

            cout << endl;
            cout << "Do you prefer louder (1) or quieter music (2)?" << endl;
            cout << "Enter 1 if louder, 2 if quieter" << endl;
            cin >> ans;
            if (ans == "1")
            {
                results.isLoud = true;
                invalidResult = true;
                surveyComplete = true;
            }
            else if (ans == "2")
            {
                results.isLoud = false;
                invalidResult = true;
                surveyComplete = true;
            }
            else {
                invalidResult = true;
                cout << "Your answer was not formatted correctly!" << endl;
                cout << "Generating another survey... "<< endl;
                break;
            }

        }
    }

    return results;
}

//given input to answer the question of what genres that user prefers, return string of genres. 
vector<string>getGenres(string genreNums) {
    vector<string>favGenres;
    for (int i = 0; i < genreNums.size(); i++) {
        bool valid = false;
        if(int(genreNums[i]) == 110) {
            string arr [] = {"pop", "hip hop", "rap", "r&b", "rock", "electro", "alternative",
                         "instrumental", "country", "jazz", "classical", "reggae", "foreign"};
            for(int i = 0; i < 13; i ++)
            {
                favGenres.push_back(arr[i]);
            }

            valid = true;
            break;
        }
        if (int(genreNums[i]) == 97)
        {
            favGenres.push_back("pop");
            valid = true;
        }
        if (int(genreNums[i]) == 98)
        {
            favGenres.push_back("hip hop");
            valid = true;
        }
        if (int(genreNums[i]) == 99)
        {
            favGenres.push_back("rap");
            valid = true;
        }
        if (int(genreNums[i]) == 100)
        {
            favGenres.push_back("r&b");
            valid = true;
        }

        if (int(genreNums[i]) == 101)
        {
            favGenres.push_back("rock");
            valid = true;
        }
        if (int(genreNums[i]) == 102)
        {
            favGenres.push_back("electro");
            valid = true;
        }
        if (int(genreNums[i]) == 103)
        {
            favGenres.push_back("alternative");
            valid = true;
        }
        if (int(genreNums[i]) == 104)
        {
            favGenres.push_back("instrumental");
            valid = true;
        }
        if (int(genreNums[i]) == 105)
        {
            favGenres.push_back("country");
            valid = true;
        }
        if (int(genreNums[i]) == 106)
        {
            favGenres.push_back("jazz");
            valid = true;
        }
        if (int(genreNums[i]) == 107)
        {
            favGenres.push_back("classical");
            valid = true;
        }
        if (int(genreNums[i]) == 108)
        {
            favGenres.push_back("reggae");
            valid = true;
        }
        if (int(genreNums[i]) == 109)
        {
            favGenres.push_back("foreign");
            valid = true;
        }
        if(!valid)
        {
            favGenres.empty();
            return favGenres;
        }
    }
    return favGenres;
}

//reads in file and parses song and also assigns artist and genres
void readFiles(vector<song> &SongCatalog) {
    ifstream file;
    string line;
    string lineObj;
    char delim = ',';

    file.open("./data_w_genres.csv");
    std::getline(file, line); // to get columns;

    unordered_map<string, vector<string> > genreMap;
    string lineObj2;

    while(!file.eof()) {
        std::getline(file, line);
        istringstream iss(line);

        std::getline(iss, lineObj, delim);
        string temp = lineObj;

        std::getline(iss, lineObj, '\n');
        if(lineObj[1] != ']') {
            if(lineObj[0] == '\"') {
                istringstream  iss2(lineObj);
                std::getline(iss2, lineObj2, delim);
                genreMap[temp].push_back(lineObj2.substr(3, lineObj2.size()-4));
                std::getline(iss2, lineObj2, delim);
                while(lineObj2.find(']') == -1) {
                    genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-3));
                    std::getline(iss2, lineObj2, delim);
                }
                genreMap[temp].push_back(lineObj2.substr(2, lineObj2.size()-6));
            }
            else {
                genreMap[temp].push_back(lineObj.substr(2, lineObj.size()-5));
            }
        }
    }

    file.close();

    file.open("./OfficialDataset.csv");
    std::getline(file, line); // to get columns;
    song tempSong;
    string artistName;

    while(!file.eof())
    {
        std::getline(file,line);
        istringstream iss(line);

        std::getline(iss, lineObj, delim);

        unordered_map<string, vector<string> >::iterator it;

        if(lineObj[0] == '\"' && lineObj[lineObj.size()-2] != ']') //artist multiple
        {
            artistName = lineObj.substr(3, lineObj.size()-4);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                tempSong.genres = genreMap[artistName];
            }
            tempSong.artists.push_back(artistName);
            std::getline(iss, lineObj, delim);
            while(lineObj.find(']') == -1) {
                artistName = lineObj.substr(2, lineObj.size()-3);
                it=genreMap.find(artistName);
                if(it!=genreMap.end()) {
                    for(int i = 0; i < genreMap[artistName].size(); i++) {
                        if(find(tempSong.genres.begin(), tempSong.genres.end(), genreMap[artistName][i]) == tempSong.genres.end()) {
                            tempSong.genres.push_back(genreMap[artistName][i]);
                        }
                    }
                }
                tempSong.artists.push_back(artistName);
                std::getline(iss, lineObj, delim);
            }
            artistName = lineObj.substr(2, lineObj.size()-5);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                for(int i = 0; i < genreMap[artistName].size(); i++) {
                    if(find(tempSong.genres.begin(), tempSong.genres.end(), genreMap[artistName][i]) == tempSong.genres.end()) {
                        tempSong.genres.push_back(genreMap[artistName][i]);
                    }
                }
            }
            tempSong.artists.push_back(artistName);
        }
        else //single artist
        {
            artistName = lineObj.substr(2, lineObj.size() - 4);
            it=genreMap.find(artistName);
            if(it!=genreMap.end()) {
                tempSong.genres = genreMap[artistName];
            }
            tempSong.artists.push_back(artistName);
        }

        std::getline(iss, lineObj, delim);
        tempSong.danceability = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.duration = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.energy = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.explicitness = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.instrumentalness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.loudness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        int counter = count(lineObj.begin(), lineObj.end(), '\"');
        if(lineObj[0]=='\"' && counter%2 == 1) {
            tempSong.songName = lineObj;
            std::getline(iss, lineObj, delim);
            counter = count(lineObj.begin(), lineObj.end(), '\"');
            while (counter%2==0)
            {
                tempSong.songName += lineObj;
                std::getline(iss, lineObj, delim);
                counter = count(lineObj.begin(), lineObj.end(), '\"');
            }
            tempSong.songName += lineObj;
        }
        else {
            tempSong.songName = lineObj;
        }

        std::getline(iss, lineObj, delim);
        tempSong.popularity = stoi(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.speechiness = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.tempo = stof(lineObj);

        std::getline(iss, lineObj, delim);
        tempSong.valence = stof(lineObj);

        std::getline(iss, lineObj, '\n');
        tempSong.year = stoi(lineObj);

        SongCatalog.push_back(tempSong);
        tempSong.artists.clear();
    }
    file.close();
    return;
}

//uses shellsort to sort the songs in the song catalog by duration
int Shellsort(song arr[], int n)
{
/* From Lecture Slides on Shellsort in Module 6
 * 1. Set the initial value of gapto n / 2
 * 2. while gap > 0
 * 3. foreach array element from position gap to the last element
 * 4. Insert this element where it belongs in its subarray.
 * 5. if gap is 2, set it to 1
 * 6. else gap = gap / 2.2.
 */

    int gap = n/2;
    while(gap > 0)
    {
        for (int i = gap; i < n; i += 1)
        {

            song temp = arr[i];


            int j;
            for (j = i; j >= gap && arr[j - gap].duration > temp.duration; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
        gap = gap/2;
    }
    return 0;
}

void shellSortWithTimeOutput(vector<song>SongCatalog)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    song *arr = &SongCatalog[0];
    for (size_t i = 0; i < SongCatalog.size(); ++i) {
        arr[i] = SongCatalog[i];
    }
    Shellsort(arr, SongCatalog.size());
    end = std::chrono::system_clock::now();  
    std::chrono::duration<double> elapsed_seconds = end - start;
  
    std::cout << "elapsed time to do shell sort: " << elapsed_seconds.count() << "s\n";
}

//uses mergesort to sort the songs in the song catalog by duration
void merge(song arr[], int left, int mid, int right) {
    int temp1 = mid - left + 1;
    int temp2 = right - mid;
 
    // Create temp arrays
    song L[temp1], R[temp2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < temp1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < temp2; j++) {
        R[j] = arr[mid + 1 + j];
    }
 
    // Merge the temp arrays:
    int i = 0;  //First subarray
    int j = 0;  //Second subarray
    int k = left;  //Merged subarray
 
    while (i < temp1 && j < temp2) {
        if (L[i].duration <= R[j].duration) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    //If there are any, copy the remaining elements of L[]
    while (i < temp1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    //If there are any, copy the remaining elements of R[]
    while (j < temp2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(song arr[], int left, int right) {
    if (left >= right) {
        return;  //returns recursively
    }
    int mid = left + (right - left)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

void mergeArrayWithTimeOutput(vector<song>SongCatalog)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    song *mergeArray = &SongCatalog[0];
    for (size_t i = 0; i < SongCatalog.size(); ++i) {
        mergeArray[i] = SongCatalog[i];
    }
    int arr_size = sizeof(SongCatalog.size()) / sizeof(mergeArray[0]);
    mergeSort(mergeArray, 0, arr_size);

    end = std::chrono::system_clock::now();  
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time to do merge sort: " << elapsed_seconds.count() << "s\n";
}

//merge sort via popularity
void mergePopularity(song arr[], int left, int mid, int right) {
    int temp1 = mid - left + 1;
    int temp2 = right - mid;
 
    // Create temp arrays
    song L[temp1], R[temp2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < temp1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < temp2; j++) {
        R[j] = arr[mid + 1 + j];
    }
 
    // Merge the temp arrays:
    int i = 0;  //First subarray
    int j = 0;  //Second subarray
    int k = left;  //Merged subarray
 
    while (i < temp1 && j < temp2) {
        if (L[i].popularity <= R[j].popularity) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    //If there are any, copy the remaining elements of L[]
    while (i < temp1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    //If there are any, copy the remaining elements of R[]
    while (j < temp2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortPopularity(song arr[], int left, int right) {
    if (left >= right) {
        return;  //returns recursively
    }
    int mid = left + (right - left)/2;
    mergeSortPopularity(arr, left, mid);
    mergeSortPopularity(arr, mid+1, right);
    mergePopularity(arr, left, mid, right);
}

//asks user if they want their playlist to be sorted by popularity
void mergeSortPlaylist(vector<song>playlist){

    bool validInput = false;
    bool AnswerAgain = false;
    
    while(!validInput)
    {
        if(AnswerAgain)
        {
            cout << "Invalid Answer! Please write 'yes' or 'no'" << endl;
            AnswerAgain = false;
        }

       
    cout << "Would you like to sort your playlist from least to most popular?" << endl;
    cout << "Please answer 'yes' or 'no" << endl;
    string ans;
    cin >> ans;
    if(ans == "yes")
    {
            cout << "Sorting Playlist...." << endl;
          
            song *mergeArray = &playlist[0];
            for (size_t i = 0; i < playlist.size(); ++i) 
                mergeArray[i] = playlist[i];
      
            int arr_size = sizeof(playlist.size()) / sizeof(mergeArray[0]);

            mergeSortPopularity(mergeArray, 0, arr_size);
            validInput = true;
        }
        if (ans == "no")
        {   
         cout << "Okay! Generating Randomized Playlist" << endl;
         validInput = true;
        }

        if(!validInput)
            AnswerAgain = true;

    }
    

}

void generatePlaylist(Survey results, vector<song>SongCatalog)
{

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    int fitCap = 13;
    playlist *playlistObj = new playlist(SongCatalog, results, fitCap);
    while(playlistObj->tree->size < 10) {
        delete playlistObj;
        playlistObj =  new playlist(SongCatalog, results, --fitCap); //generates playlist
    }
    //generates vector songQ by post order traversal
    playlistObj->songQ = playlistObj->tree->traversePostOrder(playlistObj->tree->root);
    playlistObj->shuffle();
    cout << "How would you like your playlist to be sorted?" << endl;
    mergeSortPlaylist(playlistObj->songQ);

    cout << "Writing Plalist Data to files! It will be found under './playlist.txt' " << endl;
    //outputs the playlist to the text file so that one can read the songs at anytime on the document. 

    ofstream myfile;
    myfile.open ("./playlist.txt");
    myfile << results.playlistName << endl;
    myfile << "********************************"  << endl;
    for(int i = 0; i < playlistObj->songQ.size(); i ++)
    {
        myfile << playlistObj->songQ.at(i).songName << " by ";
        string artists;
        for(int x = 0; x < playlistObj->songQ.at(i).artists.size(); x++)
        {
            artists += playlistObj->songQ.at(i).artists[x];
            artists += " ";
        }
        myfile << artists << endl;
    }


    //outputs some stats about the playlist generated. 
    myfile << "--------------------------------------------------------------------------------" << endl;
    myfile << "Here are some statistics about your playlist: " << endl;
    myfile << "Average Popularity (out of 100): " << playlistObj->avgBasicness << endl;
    myfile << "Average Danceability (out of 0.99): " << playlistObj->avgDanceability << endl;
    myfile << "---------------------------------------------------------------------------------" << endl;
    myfile << "Most Common Artists: " << endl ;
    map<string, int> top5Artists = playlistObj->topArtists();
    for (std::map<string,int>::iterator it= top5Artists.begin(); it!= top5Artists.end(); ++it)
        myfile << "Artist: " << it->first << "| Frequency: " << it->second << '\n';

    myfile << "----------------------------------------------------------------------------------" << endl;  

     
    myfile.close();

    end = std::chrono::system_clock::now();  
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time to generate playlist: " << elapsed_seconds.count() << "s\n";

    cout << endl;

    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Your playlist has been generated!, Here are some statistics about your playlist: " << endl;
    cout << "Average Popularity (out of 100): " << playlistObj->avgBasicness << endl;
    cout << "Average Danceability (out of 0.99): " << playlistObj->avgDanceability << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Most Common Artists: " << endl ;
    for (std::map<string,int>::iterator it= top5Artists.begin(); it!= top5Artists.end(); ++it)
        cout << "Artist: " << it->first << " | Frequency " << it->second << '\n';

    cout << "--------------------------------------------------------" << endl;  

}

void print()
{

cout << "  ``   ``  ``   ``  ``  ```  ``  ``` `.--:///++++++++++///:--.` ```  ``  ```  ``  ``   ``  ``   ``" << endl;  
cout << " ``  ```  ``  ```  ``  ``   ``  .-:/++oooooooooooooooooooooooooo++/:-.  ``   ``  ``  ```  ``  ```  `` " << endl;  
cout << "   ``   ``  ``   ``  ``  ```.-/+oooooooooooooooooooooooooooooooooooooo+/-.```  ``  ``   ``  ``   ``   " << endl;  
cout << " ``   ``  ``  ``   ``  ``-/+oooooooooooooooooooooooooooooooooooooooooooooo+/-`   ``   ``  ``  ``   `` " << endl;  
cout << " ``   ``  ``  ``   ```-/+oooooooooooooooooooooooooooooooooooooooooooooooooooo+/-```   ``  ``  ``   `` " << endl;  
cout << "   ``   ``  ``   ``.:+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+:.``   ``  ``   ``   " << endl;  
cout << " ``  ```  ``  ```./oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/.```  ``  ```  ``" << endl;  
cout << "  ``   ``  ```-/oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/-```  ``   ``  " << endl;  
cout << " ``  ```  `` ./oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/. ``  ```  ``" << endl;  
cout << "   ``   `` `/+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+/` ``   ``  " << endl;  
cout << " ``  ```  -+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+-  ```  ``" << endl;  
cout << "   ``   `:oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:`   ``  " << endl;  
cout << "        /oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/ " << endl;  
cout << " ``  `.+oooooooooooooooooooo+++++////::::::::::::/:////+++++oooooooooooooooooooooooooooooooooo+.`  ``" << endl;  
cout << "   ```+ooooooooooooo++//:--..```` ```  ``  ``   ``  ``````...--:://++oooooooooooooooooooooooooo/```  " << endl;  
cout << " ``  /ooooooooooo+:..` ``   ``  ``   ``  ``  ```  ``  ```  ``  ``  `..-:/++ooooooooooooooooooooo/  ``" << endl;  
cout << "   `/ooooooooooo+.`  ``  ```  ``  ```  ``  ``   ``  ``   ``  ``  ```  ``  `.-:/+ooooooooooooooooo:`  " << endl;  
cout << " ``-oooooooooooo:  ``  ``   ``  ``   ``  ``  ```  ``  ```  ``  ``   ``  ``   ```.:/+oooooooooooooo-``" << endl;  
cout << "  `+oooooooooooo+.`  ``  `````..--::://///////////::::--...````  ```  ``  ```  ``  `-/+ooooooooooo+` " << endl;  
cout << " `-oooooooooooooo+/-...-:/+++oooooooooooooooooooooooooooooo+++/::-.```  ``   ``  ``  `.+ooooooooooo-`" << endl;  
cout << " `+ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo++:-.```   ``  ``  :ooooooooooo+`" << endl;  
cout << " .oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+/-.```     `+oooooooooooo." << endl;  
cout << " :oooooooooooooooooooooooooo+++/::::------.-------::://+++oooooooooooooooooooo+/-.```:+ooooooooooooo:" << endl;  
cout << " /ooooooooooooooooooo+/:--.`` ``  ```  ``  ``   ``  ``  ``..-::/+ooooooooooooooooooooooooooooooooooo/" << endl;  
cout << " +oooooooooooooooooo/` ``   ``  ``   ``  ``  ```  ``  ```  ``  ```.-:+oooooooooooooooooooooooooooooo+" << endl;  
cout << " +ooooooooooooooooo+```  ```  ``  ```  ``  ``   ``  ``   ``  ``  ```  `.-/+ooooooooooooooooooooooooo+" << endl;  
cout << " +oooooooooooooooooo-  ``   ```.--:::///////////::::-...`  ``  ``   ``  ````-/oooooooooooooooooooooo+" << endl;  
cout << " /ooooooooooooooooooo/:--:/++oooooooooooooooooooooooooooo++/:-.` ```  ``  ``` `:oooooooooooooooooooo/" << endl;  
cout << " :oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+/:-.`  ``   `` :ooooooooooooooooooo:" << endl;  
cout << " .ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+/-.``    `/ooooooooooooooooooo." << endl;  
cout << " `+ooooooooooooooooooooooooooooo++/////::::::://///+++oooooooooooooooooo++:-..-+ooooooooooooooooooo+`" << endl;  
cout << " `-oooooooooooooooooooo+/::--.`````````  ``  ```  `````..-::/+ooooooooooooooooooooooooooooooooooooo-`" << endl;  
cout << "  `+oooooooooooooooooo:` ```  ``  ```  ``  ``   ``  ``   ``  `..:/+ooooooooooooooooooooooooooooooo+` " << endl;  
cout << " ``-oooooooooooooooooo```   ``  ````.....--.....``.`` ```  ``  `````-/+ooooooooooooooooooooooooooo-``" << endl;  
cout << "   `/ooooooooooooooooo+-..---://++++++++ooooooo+++++++/::-.` ``  ```  `.-+ooooooooooooooooooooooo/`  " << endl;  
cout << " `` `/oooooooooooooooooo++ooooooooooooooooooooooooooooooooo++/:-.`  ``  ``+ooooooooooooooooooooo/  ``" << endl;  
cout << "   ```+ooooooooooooooooooooooooooooooooooooooooooooooooooooooooo++:-` `` `+oooooooooooooooooooo+```  " << endl;  
cout << " ``  `.+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+/::/+oooooooooooooooooooo+.   ``" << endl;  
cout << "    ` `/oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/` `    " << endl;  
cout << "   ``   `:oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:`   ``  " << endl;  
cout << " ``  ```  -+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+-  ```  ``" << endl;  
cout << "   ``   `` `/oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/` ``   ``  " << endl;  
cout << " ``  ```  `` ./oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/. ``  ```  ``" << endl;  
cout << "   ``   ``  ```-+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+-```  ``   ``  " << endl;  
cout << " ``  ```  ``  ```-/oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo/.```  ``  ```  ``" << endl;  
cout << "   ``   ``  ``   ``.:+oooooooooooooooooooooooooooooooooooooooooooooooooooooooooo+:.``   ``  ``   ``  " << endl;  
cout << " ``   `   ``  ``   ```-/+oooooooooooooooooooooooooooooooooooooooooooooooooooo+/-```   `   ``  ``   ``" << endl;  
cout << " ``   ``  ``  ``   ``  ``-/+oooooooooooooooooooooooooooooooooooooooooooooo+/-``  ``   ``  ``  ``   ``" << endl;  
cout << "   ``   ``  ``   ``  ``   ``.-/+oooooooooooooooooooooooooooooooooooooo+/-.```  ``  ``   ``  ``   ``  " << endl;  
cout << " ``  ```  ``  ```  ``  ``   ``  .-:/++oooooooooooooooooooooooooo++/:-.  ``   ``  ``  ```  ``  ```  ``" << endl;  
cout << "  ``   ``  ``   ``  ``  ```  ``  ``` `.--:///++++++++++///:--.` ```  ``  ```  ``  ``   ``  ``   ``  " << endl;  

}