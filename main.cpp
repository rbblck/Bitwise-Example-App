//
//  main.cpp
//  Engine
//
//  Created by Robert Black on 10/02/2021.
//

#include <iostream>
#include <string>
#include <bitset>

using namespace std;

//Function to rotae binary numbers (4 bits) from the assignment.
int rotateLeft (int value, int amount) {
    
    //four bit rotate left
    const int OVER_FLOW = 0b10000;
    
    while (amount > 0) {
        
        value = value << 1;
        
        if (((value & OVER_FLOW) == OVER_FLOW)) {
            value = value & 0b1111;  //remove overflow bit
            value = value | 0b0001;  //set the rightmost bit
            
        }
        
        amount--;
    }
    
    return value;
    
}

int main(int argc, const char * argv[]) {
    
    //Spacing for the ASCII art for top margine.
    cout << endl;
    cout << endl;
    
    //Set the event binary literals to be rotated left by a number
    //dictated by the firing order on each loop.
    int inValvesOpen =  0b0010;
    int outValvesOpen = 0b0100;
    int pistonUp =      0b1010;
    int cylinderFire =  0b1000;

    //Loop to iterate all four firing events and show the engine
    //back at the origanal stae on the 5th iteration.
    for (int i = 0; i < 5; i++) {
        
        //Strings to make the ACCII art template to be updated below
        //to show current firing events.
        string d1 = "     1        2        3        4     ";
        string d2 = "    ___      ___      ___      ___    ";
        string d3 = "  X|   |X  X|   |X  X|   |X  X|   |X  ";
        string d4 = "   |   |    |   |    |   |    |   |   ";
        string d5 = "    ---      ---      ---      ---    ";
        string d6 = "     ?        ?        ?        ?     ";
        
        //String offset, however, the caracters are replaced by accessing
        //The string arrat (char* []).
        int offset = 0;
        
        //Position mask set to the first cylinder.
        int positionMask =  0b1000;
        
        //Loop to apply the state of each of the 4 cylinders.
        for (int c = 0; c < 4; c++) {
            //Resets all the caracters to apply next cyliners state
            //characters.
            char stateLabel = 'C';
            char inValve = 'x';
            char outValve = 'x';
            char upPiston = ' ';
            char downPiston = 'T';
            char chamber = ' ';
            
            //Using the mask, check if the current mask position equals
            //the appropriate event to occur and update the charater
            //variables above.
            if (((cylinderFire & positionMask) == positionMask)) {
                chamber = '*';
                stateLabel = 'P';
            }
            
            if (((inValvesOpen & positionMask) == positionMask)) {
                stateLabel = 'I';
                inValve = 'o';
            }
            
            if (((outValvesOpen & positionMask) == positionMask)) {
                outValve = 'o';
                stateLabel = 'E';
            }
            
            if (((pistonUp & positionMask) == positionMask)) {
                upPiston = 'T';
                downPiston = ' ';
            }
            
            //Update the appropriate strings by accessing the string arrays
            //char* [].
            d3[(offset + 2) + (c * 9)] = inValve;
            d3[(offset + 4) + (c * 9)] = chamber;
            d3[(offset + 5) + (c * 9)] = upPiston;
            d3[(offset + 6) + (c * 9)] = chamber;
            d3[(offset + 8) + (c * 9)] = outValve;
            d4[(offset + 5) + (c * 9)] = downPiston;
            d6[(offset + 5) + (c * 9)] = stateLabel;
            
            //Shift the position binary right to move on to the next cylinder
            //over the 4 iterations.
            positionMask >>= 1;

        }
        
        //Display the updated ASCII art for the current engine state.
        cout << d1 << endl;
        cout << d2 << endl;
        cout << d3 << endl;
        cout << d4 << endl;
        cout << d5 << endl;
        cout << d6 << endl;
        cout << endl;
        cout << endl;
        
        //Array created with the number of moves left to simulate the firing
        //sequence "1, 3, 2, 4".
        int firingOrderArray[4] = {2, 1, 2, 3};
        
        //This uses remainder of 4 and the current iteration number 'i'
        //to extract the 'firingOrderArray' index (0 - 3).
        int firingArrayAccessIndex = i % 4;
        
        //The number access in the 'firingOrderArray' is used to start the firing order in
        //the right position by rotaing the 4 binary variables to simulate a firing order
        //of "1, 3, 2, 4".
        inValvesOpen = rotateLeft(inValvesOpen, firingOrderArray[firingArrayAccessIndex]);
        outValvesOpen = rotateLeft(outValvesOpen, firingOrderArray[firingArrayAccessIndex]);
        pistonUp = rotateLeft(pistonUp, firingOrderArray[firingArrayAccessIndex]);
        cylinderFire = rotateLeft(cylinderFire, firingOrderArray[firingArrayAccessIndex]);

    }
    
    return 0;
}
