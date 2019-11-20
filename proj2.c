#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*
 * Created by Sotirios Pupakis
 * Created on 18.11.2019
 * Last modified: 18.11.2019
 * Project 1: Projekt 2 - Iteration computation
 * Login: xpupak01
 * Bonus: None
 * Known bugs: TBA
 */

/*
 * Exit codes:
 * 0    -   Everything OK
 * -1   -   Not enough or too many parameters provided  -   Line: 29
 * -2   -   Error while parsing arguments               -   Line: 45
 */

double loadArgument(char *arg);     // Checks argument and returns it's double value

int main(int argc, char *argv[]) {
    // Check if we got enough arguments
    if (argc != 4) {
        fputs("NOT ENOUGH OR TOO MANY PARAMETERS PROVIDED\n", stderr);
        return -1;
    }

    // Safely loads provided arguments
    double U0 = loadArgument(argv[1]);
    double R = loadArgument(argv[2]);
    double eps = loadArgument(argv[3]);



    return 0;
}

// Checks argument and returns it's double value
double loadArgument(char *arg) {
    // Creates pointer that will refer to first point of failure in strtod
    char *endptr = NULL;
    // Parses double using strtod function
    double ret = strtod(arg, &endptr);
    // Check if parse was successful
    if (strcmp(endptr, "\0") != 0) {
        // In case of error outputs error message
        fputs("ERROR WHILE PARSING ARGUMENTS", stderr);
        return -2;
    }
    // Returns parsed value
    return ret;
}