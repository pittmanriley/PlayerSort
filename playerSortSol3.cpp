/*
 * This program uses insertionSort to sort the player data and runs
 * the search for the top K numbers of each stat. InsertionSort
 * iterates through the vector and sorts the vector while looping
 * through.
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
void loadVectorHelper3(Vector<string>& playerVec, Vector<string>& names, Vector<double>& heights, Vector<double>& GPAS, Vector<double>& goals,
                      Vector<double>& shootingP, Vector<double>& assists){

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
void buildVectors3(Vector<double>& heights, Vector<string>& names, Vector<double>& GPAS, Vector<double>& goals, Vector<double>& shootingP,
                  Vector<double>& assists){
    ifstream in;

    if (!openFile(in, "playerData.txt"))
        error("Cannot open file named playerData.txt");

    Vector<string> lines;
    readEntireFile(in, lines);
    for(string line: lines){
        Vector<string> playerVec = stringSplit(line, ",");
        loadVectorHelper3(playerVec, names, heights, GPAS, goals, shootingP, assists);

    }
}

/*
 * This function returns the top K numbers from the given vector. K is
 * passed in as 'num'.
 */
Vector<double> topKStats3(Vector<double>& v, int topKNum){
    Vector<double> result;
    int i = 1;
    while(result.size() != topKNum){
        if(i < v.size()){
            result.add(v[v.size() - (i)]);
            i ++;
        }else{
            break;
        }
    }

    return result;
}

/*
 * This function iteratively sorts the vector. The Big O is at worst O(n^2)
 * and at best O(n).
 */
void insertionSort(Vector<double>& vec){
    for(int i = 1; i < vec.size(); i++){
        double temp = vec[i];

        double slide = i;
        while(slide >= 1 && vec[slide - 1] > temp){
            vec[slide] = vec[slide - 1];
            slide --;
        }
        vec[slide] = temp;
    }
}


/*
 * This function calls each of the above functions and runs the search engine
 * for the chosen stats. The sorting algorithm in this search function is insertion
 * sort.
 */
void searchRoster3(){

    Vector<string> names;
    Vector<double> heights;
    Vector<double> GPAS;
    Vector<double> goals;
    Vector<double> shootingP;
    Vector<double> assists;
    Vector<double> topK;
    Vector<double> sorted;

    buildVectors3(heights, names, GPAS, goals, shootingP, assists);

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
                insertionSort(heights);
                topK = topKStats3(heights, stringToInteger(line2));
                cout << "Top "<< line2<< " heights(inches) on the team: "<<topK << endl;
            }else if (line1 == "B") {
                insertionSort(GPAS);
                topK = topKStats3(GPAS, stringToInteger(line2));
                cout << "Top "<< line2<< " GPAS on the team: "<<topK << endl;
            }else if (line1 == "C") {
                insertionSort(goals);
                topK = topKStats3(goals, stringToInteger(line2));
                cout << "Top "<< line2<< " goals on the team: "<<topK << endl;
            } else if (line1 == "D") {
                insertionSort(shootingP);
                topK = topKStats3(shootingP, stringToInteger(line2));
                cout << "Top "<< line2<< " shooting %s on the team: "<<topK << endl;
            }else if (line1 == "E") {
                insertionSort(assists);
                topK = topKStats3(assists, stringToInteger(line2));
                cout << "Top "<< line2<< " assists on the team: "<<topK << endl;
            }else if(line1 == "F"){
                cout<< "All names on the team: "<< names<<endl;
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

PROVIDED_TEST("Test buildVectors") {
    Vector<string> names;
    Vector<double> heights;
    Vector<double> GPAS;
    Vector<double> goals;
    Vector<double> shootingP;
    Vector<double> assists;

    buildVectors3(heights, names, GPAS, goals, shootingP, assists);


}

PROVIDED_TEST("Test insertion sort with single value vector") {
    Vector<double> v = {4};
    Vector<double> expected = {4};

    insertionSort(v);

    EXPECT_EQUAL(v, expected);
}

PROVIDED_TEST("testing insertion sort"){
    Vector<double> test = {3, 8, 6, 4, 9, 6, 2};
    Vector<double> expected = {2, 3, 4, 6, 6, 8, 9};
    insertionSort(test);
    EXPECT_EQUAL(test, expected);

    Vector<double> expect = {9, 8, 6};
    Vector<double> result = topKStats3(test, 3);


    EXPECT_EQUAL(result, expect);

}

PROVIDED_TEST("testing insertion sort"){
    Vector<double> test = {2, 3, 4, 6, 8, 9};
    Vector<double> expected = {9, 8, 6};

    Vector<double> result = topKStats3(test, 3);

    EXPECT_EQUAL(result, expected);
}


PROVIDED_TEST("Test the Big O of insertionSort") {
    Vector<double> v;
    int numElements = 10000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, insertionSort(v));
}

PROVIDED_TEST("Test the Big O of insertionSort") {
    Vector<double> v;
    int numElements = 20000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, insertionSort(v));
}

PROVIDED_TEST("Test the Big O of insertionSort") {
    Vector<double> v;
    int numElements = 40000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, insertionSort(v));
}

PROVIDED_TEST("Test the Big O of insertionSort") {
    Vector<double> v;
    int numElements = 80000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, insertionSort(v));
}
