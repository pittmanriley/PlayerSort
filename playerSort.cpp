/*
 * This program uses quickSort to sort the player data and runs
 * the search for the top K numbers of each stat. Quicksort
 * recursively sorts the data from greatest to least with the help
 * of a partition function.
 */
#include "testing/MemoryDiagnostics.h"
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
#include <string_view>
#include <string>
#include "math.h"
using namespace std;

/*
 * This function is the helper to buildVevctors and it adds each
 * of the correct parts of each line in the file to the corresponding
 * vector.
 */
void loadVectorHelper(Vector<string>& playerVec, Vector<string>& names,
                      Vector<double>& heights, Vector<double>& GPAS,
                      Vector<double>& goals, Vector<double>& shootingP,
                      Vector<double>& assists){

    names.add(playerVec[0]);
    GPAS.add(stringToReal(playerVec[1]));
    heights.add(stringToReal(playerVec[2]));
    goals.add(stringToReal(playerVec[3]));
    shootingP.add(stringToReal(playerVec[4]));
    assists.add(stringToReal(playerVec[5]));
}

/*
 * This function reads each line from the file and calls loadVectorHelper
 * to add the correct part of each line to the corresponding vector.
 */
void buildVectors(Vector<double>& heights, Vector<string>& names,
                  Vector<double>& GPAS, Vector<double>& goals,
                  Vector<double>& shootingP, Vector<double>& assists){
    ifstream in;

    if (!openFile(in, "playerData.txt"))
        error("Cannot open file named playerData.txt");

    Vector<string> lines;
    readEntireFile(in, lines);
    for(string line: lines){
        Vector<string> playerVec = stringSplit(line, ",");
        loadVectorHelper(playerVec, names, heights, GPAS, goals, shootingP, assists);

    }
}

/*
 * This function returns the top K numbers from the given vector. K is
 * passed in as 'num'.
 */
Vector<double> topKStats(Vector<double>& v, int num){
    Vector<double> result;
    int i = 0;

    while(result.size() != num){
        if(i < v.size()){
            result.add(v[i]);
            i ++;
        }else{
            break;
        }
    }

    return result;
}

/*
 * This function is the helper to the quickSort function and it adds each
 * value to the proper vector based on if it is greater or smaller than the
 * pivot.
 */
void partition(Vector<double>& v, Vector<double>& bigger, Vector<double>& smaller, double pivot) {
   for (int i = 1; i < v.size(); i++) {
       if (v[i] >= pivot) {
           bigger.add(v[i]);
       } else {
           smaller.add(v[i]);
       }
   }
}

/*
 * This function recursively sorts the vector in decreasing order (greatest
 * to least) with the help of its partition function. Big O is O(n log n).
 */
Vector<double> quickSort(Vector<double> v) {
    Vector<double> smaller;
    Vector<double> bigger;

    // base case
    if (v.size() < 2) {
        return v;
    }

    double pivot = v[0];
    partition(v, bigger, smaller, pivot);

    bigger = quickSort(bigger);
    // can use a same here!
    smaller = quickSort(smaller);

    bigger.add(pivot);

    return bigger + smaller;
}

/*
 * This function calls each of the above functions and runs the search engine
 * for the chosen stats. The sorting algorithm in this search function is the
 * recursive quickSort function.
 */
void searchRoster(){

    Vector<string> names;
    Vector<double> heights;
    Vector<double> GPAS;
    Vector<double> goals;
    Vector<double> shootingP;
    Vector<double> assists;
    Vector<double> topK;
    Vector<double> sorted;

    buildVectors(heights, names, GPAS, goals, shootingP, assists);

    cout << "Enter which stat you would like to see:" << endl;
    cout << "A for height" << endl;
    cout << "B for GPA" << endl;
    cout << "C for goals" << endl;
    cout << "D for shooting percentage" << endl;
    cout << "E for assists" << endl;
    cout << "F for names" << endl << endl;
    string line1 = getLine("Enter a stat you'd like to view (RETURN/ENTER to quit): ");
    string line2;
    if(line1 != "F"){
        line2 = getLine("Enter the top N of this stat you'd like to see (RETURN/ENTER to quit): ");
    }
    while (line1 != "" || line2 != ""){
            //sort the requested vector
            if (line1 == "A") {
                sorted = quickSort(heights);
                topK = topKStats(sorted, stringToInteger(line2));
                cout << "Top "<< line2<< " heights(inches) on the team: "<<topK << endl << endl;
            }else if (line1 == "B") {
                sorted = quickSort(GPAS);
                topK = topKStats(sorted, stringToInteger(line2));
                cout << "Top "<< line2<< " GPAS on the team: "<<topK << endl << endl;
            }else if (line1 == "C") {
                sorted = quickSort(goals);
                topK = topKStats(sorted, stringToInteger(line2));
                cout << "Top "<< line2<< " goals on the team: "<<topK << endl << endl;
            }else if (line1 == "D") {
                sorted = quickSort(shootingP);
                topK = topKStats(sorted, stringToInteger(line2));
                cout << "Top "<< line2<< " shooting %s on the team: "<<topK << endl << endl;
            }else if (line1 == "E") {
                sorted = quickSort(assists);
                topK = topKStats(sorted, stringToInteger(line2));
                cout << "Top "<< line2<< " assists on the team: "<<topK << endl << endl;
            }else if(line1 == "F"){
                cout<< "All names on the team: "<< names <<endl << endl;
            }else{
                line1 = getLine("This option is not a possibility, please re-enter a letter from capital A-F(RETURN/ENTER to quit): ");
                if(line1 != "F"){
                    line2 = getLine("Enter the top N of this stat you'd like to see (RETURN/ENTER to quit): ");
                }
            }
            line1 = getLine("Enter a stat you'd like to view (RETURN/ENTER to quit): ");
            if(line1 != "F"){
                line2 = getLine("Enter the top N of this stat you'd like to see (RETURN/ENTER to quit): ");
            }
    }
}


/* Implement tests below */

PROVIDED_TEST("Test quickSort with vector of same values") {
    Vector<double> v = {4, 4, 4, 4, 4, 4};
    Vector<double> expected = {4, 4, 4, 4, 4, 4};
    Vector<double> result;

    result = quickSort(v);

    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("Test buildVectors") {
    Vector<string> names;
    Vector<double> heights;
    Vector<double> GPAS;
    Vector<double> goals;
    Vector<double> shootingP;
    Vector<double> assists;

    buildVectors(heights, names, GPAS, goals, shootingP, assists);

    cout << "heights: " << "{" << heights << "}" << endl;
    cout << "names: " << "{" << names << "}" << endl;
    cout << "GPAs: " << "{" << GPAS << "}" << endl;
    cout << "goals: " << "{" << goals << "}" << endl;
    cout << "shootingP: " << "{" << shootingP << "}" << endl;
    cout << "assists: " << "{" << assists << "}" << endl;
}

PROVIDED_TEST("Test quickSort with single value vector") {
    Vector<double> v = {4};
    Vector<double> expected = {4};
    Vector<double> result;

    result = quickSort(v);

    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("Test quickSort with small vector") {
    Vector<double> v = {4, 2, 3, 9, 2, 8, 10};
    Vector<double> expected = {10, 9, 8, 4, 3, 2, 2};
    Vector<double> result;

    result = quickSort(v);

    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("Test reverse quickSort with large vector") {
    Vector<double> v = {};
    Vector<double> expected = {};
    Vector<double> result;
    Stack<double> stack;

    for (int i = 0; i < 100; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
        expected.add(num);
    }

    expected.sort();
    int size = expected.size();
    for (int i = 0; i < size; i++) {
        double num = expected.remove(0);
        stack.push(num);
    }
    while (!stack.isEmpty()) {
        double num = stack.pop();
        expected.add(num);
    }

    result = quickSort(v);

    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("Test the Big O of quicksort") {
    Vector<double> v;
    int numElements = 1000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, quickSort(v));
}

PROVIDED_TEST("Test the Big O of quicksort") {
    Vector<double> v;
    int numElements = 2000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, quickSort(v));
}

PROVIDED_TEST("Test the Big O of quicksort") {
    Vector<double> v;
    int numElements = 4000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, quickSort(v));
}

PROVIDED_TEST("Test the Big O of quicksort") {
    Vector<double> v;
    int numElements = 8000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, quickSort(v));
}


