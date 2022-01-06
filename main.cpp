/*
 * File: main.cpp
 * --------------
 * Sample QT project
 */

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "console.h"
#include "testing/SimpleTest.h"
#include "testing/playerSort.h"
#include "testing/playerSort_sol2.h"
#include "testing/playerSort_sol3.h"
using namespace std;

/*
 * This sample main brings up testing menu.
 */
int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    string input = getLine("Which sort do you want to run (A = quicksort B = remove max sort C = insertion sort): ");
    if(input == "B"){
        searchRoster2();
    }else if(input == "A"){
        searchRoster();
    }else if(input == "C"){
        searchRoster3();
    }
    cout << "All done, exiting" << endl;
    return 0;
}

PROVIDED_TEST("Sample use of SimpleTest")
{
    EXPECT_EQUAL(1 + 1, 2);
}
