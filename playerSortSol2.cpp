/*
 * This program uses topKSort to sort the player data and runs
 * the search for the top K numbers of each stat. TopKSort repeatedly
 * removes the maximum value from a vector and adds it to the result
 * vector in order to return the top K stats wanted.
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
using namespace std;

/*
 * This function is the helper to buildVevctors and it adds each
 * of the correct parts of each line in the file to the corresponding
 * vector.
 */
void loadVectorHelper2(Vector<string>& playerVec, Vector<string>& names, Vector<double>& heights, Vector<double>& GPAS, Vector<double>& goals, Vector<double>& shootingP,
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
void buildVectors2(Vector<double>& heights, Vector<string>& names, Vector<double>& GPAS, Vector<double>& goals, Vector<double>& shootingP, Vector<double>& assists){
    ifstream in;

    if (!openFile(in, "playerData.txt"))
        error("Cannot open file named playerData.txt");

    Vector<string> lines;
    readEntireFile(in, lines);

    for(string line: lines){
        Vector<string> playerVec = stringSplit(line, ",");
        loadVectorHelper2(playerVec, names, heights, GPAS, goals, shootingP, assists);

    }
}

/*
 * This function returns the max value in the vector passed in.
 */
double removeMaxVal(Vector<double>& vec){
    double compare;
    double temp = vec[0];
    double max;

    for(int j = 0; j < vec.size(); j++){
        compare = vec[j];
        if(temp < compare && compare > max){
            max = compare;
        }else if(temp > max){
            max = temp;
        }
    }

    vec.removeValue(max);

    return max;
}

/*
 * This function returns the top K numbers from the given vector. K is
 * passed in as 'topK' and the function calls the removeMaxVal helper
 * and adds the max value to the vector until it reaches size k. Big O is
 * O(n^2).
 */
Vector<double> topKSort(Vector<double> vec, int topK){
    Vector<double> result;

    while(result.size() != topK){
        if(vec.size() == 0){
            break;
        }else{
            double currVal = removeMaxVal(vec);
            result.add(currVal);
        }
    }
    return result;
}



/*
 * This function calls each of the above functions and runs the search engine
 * for the chosen stats. The sorting algorithm in this search function is the
 * remove max value sort function.
 */
void searchRoster2(){

    Vector<string> names;
    Vector<double> heights;
    Vector<double> GPAS;
    Vector<double> goals;
    Vector<double> shootingP;
    Vector<double> assists;
    Vector<double> resultV;

    buildVectors2(heights, names, GPAS, goals, shootingP, assists);

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
                resultV = topKSort(heights, stringToInteger(line2));
                cout << "Top "<< line2<< " heights(inches) on the team: "<<resultV << endl;
            }else if (line1 == "B") {
                resultV = topKSort(GPAS, stringToInteger(line2));
                cout << "Top "<< line2<< " GPAS on the team: "<<resultV << endl;
            }else if (line1 == "C") {
                resultV = topKSort(goals, stringToInteger(line2));
                cout << "Top "<< line2<< " goals on the team: "<<resultV << endl;
            }else if (line1 == "D") {
                resultV = topKSort(shootingP, stringToInteger(line2));
                cout << "Top "<< line2<< " shooting %s on the team: "<<resultV << endl;
            }else if (line1 == "E") {
                resultV = topKSort(assists, stringToInteger(line2));
                cout << "Top "<< line2<< " assists on the team: "<<resultV << endl;
            }else if(line1 == "F"){
                cout<< "All names on the team: "<< names<<endl;
            }else {
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

PROVIDED_TEST("testing the find max function"){
    Vector<double> test = {4.1, 2.7, 8.7, 8.0, 5, 9};

    double max = removeMaxVal(test);

    EXPECT_EQUAL(max, 9);
}

PROVIDED_TEST("Test topKSort with single value vector") {
    Vector<double> v = {4};
    Vector<double> expected = {4};
    Vector<double> result;

    result = topKSort(v, v.size());

    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("testing the topK sort function"){
    Vector<double> test = {4.1, 2.7, 8.7, 8.0, 5, 9};

    Vector<double> result = topKSort(test, 3);

    Vector<double> expected = {9, 8.7, 8.0};
    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("testing the topK sort function"){
    Vector<double> test = {4.1, 2.7, 8.7, 8.0, 5, 9};

    Vector<double> result = topKSort(test, 7);

    Vector<double> expected = {9, 8.7, 8.0, 5, 4.1, 2.7};
    EXPECT_EQUAL(result, expected);
}

PROVIDED_TEST("Test the Big O of topKSort") {
    Vector<double> v;
    int numElements = 10000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, topKSort(v, v.size()));
}

PROVIDED_TEST("Test the Big O of topKSort") {
    Vector<double> v;
    int numElements = 20000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, topKSort(v, v.size()));
}

PROVIDED_TEST("Test the Big O of topKSort") {
    Vector<double> v;
    int numElements = 40000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, topKSort(v, v.size()));
}

PROVIDED_TEST("Test the Big O of topKSort") {
    Vector<double> v;
    int numElements = 80000;

    for (int i = 0; i < numElements; i++) {
        double num = randomInteger(0, 10);
        v.add(num);
    }
    TIME_OPERATION(numElements, topKSort(v, v.size()));
}

