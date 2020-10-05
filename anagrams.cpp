//
//  anagrams.cpp
//  project3
//
//  Created by Ashley Kim on 7/26/20.
//  Copyright © 2020 Ashley Kim. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int createDict(istream &dictfile, string dict[]);
int createDict(istream &dictfile, string dict[], int count);
void viewAnswers(const string results[], int size);

int characterMixer(string word, const string dict[], int size, string results[]);
int matchDict(const string dict[], int left, int &right, string &permutationCheck, string results[], int &count);
void loop(int &count, int &size, string results[], const string dict[], string &prefix, string &rest, size_t max, int i);
void printPermutations (string prefix, string rest, const string dict[], string results[], int &size, int &count);
bool duplicate(const string results[], int left, int &right, string &permutationCheck);

/*
void printPermutations(string prefix, string rest, const string dict[], int size, int index, string results[]);
//bool noMatchInResults(string results[], int size, string permutationCheck);
//void permute(string prefix, string rest, const string dict[], string results[], int size, int count);
void Loop(int i, int max, string prefix, string rest, const string dict[], int size, int index, string results[]); */


// use recursion logic


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = createDict(dictfile, dict);
    
    //string test = "sad";
    //cout << matchDict(dict, 0, nwords, test) << endl;
    //cout << nwords << endl;
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = characterMixer(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        viewAnswers(results, numMatches);
    
    return 0;
}

int createDict(istream &dictfile, string dict[], int count){//cout = 0, count = 1, count = 2
    if (count >= MAXDICTWORDS){//false, false, true
        return 0; //0
    }
    
    // if you can read in the 1st one
    if (getline(dictfile, dict[0])){ //true, true
        
        
        // parse through the next value
        return (1 + createDict(dictfile, dict + 1, count + 1)); //return 1 + 1 + 0
    }
    
    // return count
    return 0;
}
//2 words: rat, sad
int createDict(istream &dictfile, string dict[]){
    return createDict(dictfile , dict, 0); //2
}

void viewAnswers(const string results[], int size){
    if (size == 0){
        return;
    }
    cout << "Matching word " << results[0] << endl;
    viewAnswers(results + 1, size - 1);
}

int characterMixer(string word, const string dict[], int size, string results[]){
    int count = 0;
    string check = "";
    printPermutations(check, word, dict, results, size, count);
    return count;
}

// function that checks if word is in dictionary
int matchDict(const string dict[], int left, int &right, string &permutationCheck, string results[], int &count){
    if (left == right){
        return 0;
    }
    if (dict[left] == permutationCheck){
        if (duplicate(results, 0, count, permutationCheck)){
            return 0;
        }
        else {
            results[count] = permutationCheck;
            return 1 + matchDict(dict, left + 1, right, permutationCheck, results, count);
        }
    }
    return matchDict(dict, left + 1, right, permutationCheck, results, count);
}

// return true if duplicate
bool duplicate(const string results[], int left, int &right, string &permutationCheck){
    if (left >= right){
        return false;
    }
    if (*results == permutationCheck){
        return true;
    }
    return duplicate(results + 1, left + 1, right, permutationCheck);
}

void loop(int &count, int &size, string results[], const string dict[], string &prefix, string &rest, size_t max, int i)
{
    if (i >= max){
        return;
    }
    printPermutations(prefix + rest[i], rest.substr(0,i)+rest.substr(i+1), dict, results, size, count);
    //adds character to prefix and deletes the character from rest
    loop(count, size, results, dict, prefix, rest, max, i+1);
    //recursion generated with updated values
    
}

void printPermutations (string prefix, string rest, const string dict[], string results[], int& size, int& count)
{
    if (rest == "") {
        count += matchDict(dict, 0, size, prefix, results, count);
    }
    else
    {
        loop(count, size, results, dict, prefix, rest, rest.size(), 0);
    }
}

/*
// what doesn't work
void printPermutations(string prefix, string rest, const string dict[], int size, int index, string results[]){
    if (rest == "") {
        //cout << prefix << endl;
        if (matchDict(dict, 0, size, prefix)){
            cout << prefix << endl;
        }
    }
    else {
        for (int i = 0; i < rest.size(); i++){
            string newprefix = prefix + rest[i];
            string newrest = rest.substr(0,i) + rest.substr(i+1);
            printPermutations(newprefix, newrest, dict, size, index, results);
        }
    }
}

void printPermutations(string prefix, string rest, const string dict[], int size, int index, string results[]){
    if (rest == "") {
        //cout << prefix << endl;
        if (matchDict(dict, 0, size, prefix)){
            cout << prefix << endl;
        }
    }
    else {
        Loop(0, rest.size(), prefix, rest, dict, size, index, results);
    }
}

void Loop(int i, size_t max, string prefix, string rest, const string dict[], int size, int index, string results[]) {
    if (i >= max)
        return;
    string newprefix = prefix + rest[i];
    string newrest = rest.substr(0,i) + rest.substr(i+1);
    printPermutations(newprefix, newrest, dict, size, index, results);
    Loop(i + 1, max, newprefix, newrest, dict, size, index, results);
}

// function that checks if word is in dictionary
bool matchDict(const string dict[], int left, int right, string permutationCheck){
    if (left == right){
        return false;
    }
    if (dict[left] == permutationCheck){
        return true;
    }
    return matchDict(dict, left + 1, right, permutationCheck);
}


// function that checks if word is in dictionary
bool matchDict(const string dict[], int left, int right, string permutationCheck){
    if (right < 1){
        return false;
    }
    if (dict[left] == permutationCheck){
        return true;
    }
    if (dict[right] == permutationCheck){
        return true;
    }
    return matchDict(dict, left + 1, right - 1, permutationCheck);
}


int characterMixer(string word, const string dict[], int size, string results[]){
    int count = 0;
    if (size == 0 || count == MAXRESULTS){
        return count;
    }
    size--;
    
    string check = "";
    int index = 0;
    printPermutations(check, word, dict, size, index, results);
    return 0;
}


// finding all the possibilities
// write as nonrecursive solution
// see what permutations
// break off one character at a time to make possible combinations
// finding all combinations of the smaller rest
// recursively call function to start with full rest and empty prefix


// take from the rest string and add to the prefix
// swap the two values
void printPermutations(string prefix, string rest, const string dict[], string results[], int size){
    int count = 0;
    permute(prefix, rest, dict, results, size, count);
 
    if (rest == "") {
        //cout << prefix << endl;
        if (matchDict(dict, prefix) && noMatchInResults(results, size, prefix)){
            //cout << prefix << endl;
            results[count] = prefix;
            count++;
        }
    }
    else {
        for (int i = 0; i < rest.size(); i++){
            string newprefix = prefix + rest[i];
            string newrest = rest.substr(0,i) + rest.substr(i+1);
            printPermutations(newprefix, newrest, dict, results, size);
        }
    }
}

void permute(string prefix, string rest, const string dict[], string results[], int size, int count){
    //size = 0;
    if (rest == "") {
        cout << prefix << endl;
 
        if (matchDict(dict, prefix, size)){
            cout << prefix << endl;
        }
        if (noMatchInResults(results, prefix)){
            cout << prefix << endl;
            //results[count] = prefix;
            //count++;
        }
    }
    else {
        for (int i = 0; i < rest.size(); i++){
            string newprefix = prefix + rest[i];
            string newrest = rest.substr(0,i) + rest.substr(i+1);
            permute(newprefix, newrest, dict, results, size, count);
        }
    }
}

// function that checks if word is in dictionary
bool matchDict(const string dict[], string permutationCheck, int size){
    for (int i = 0; i < size; i++){
        if (permutationCheck == dict[i]){
            return true;
        }
    }
    return false;
}


// function check no duplicates
bool noMatchInResults(string results[],  string permutationCheck){
    for (int i = 0; i < size; i++){
        if (results[i] == permutationCheck){
            return false;
        }
    }
    return true;
} */

