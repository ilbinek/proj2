#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Defines
#define I_0 1.0E-12
#define U_T 25.8563E-3

/*
 * Author: Sotirios Pupakis
 * Created on 18.11.2019
 * Last modified: 18.11.2019
 * Project 1: Project 2 - Iteration computation
 * Login: xpupak01
 * Bonus: None
 * Known bugs: None
 * Version: 1.2
 */

/*
 * Exit codes:
 *  0   -   Everything OK
 * -1   -   Not enough or too many parameters provided
 * -2   -   Error while parsing arguments
 * -3   -   Resistivity is 0
 */

double loadArgument(char *arg);                         // Checks argument and returns it's double value
double diode(double u0, double r, double eps);          // Calculates U_P based on provided parameters
double getUPResult(double U_P, double U_0, double R);   // Returns the result with given U_P
double
calculateAccurateUP(double U_0, double R, double eps);  // Returns U_P that is approximated using bisection method

int main(int argc, char *argv[]) {
    // Check if we got enough arguments
    if (argc != 4) {
        fputs("NOT ENOUGH OR TOO MANY PARAMETERS PROVIDED\n", stderr);
        return -1;
    }

    // Safely loads provided arguments
    double U_0 = loadArgument(argv[1]);
    double R = loadArgument(argv[2]);
    double eps = loadArgument(argv[3]);

    // Check if R is zero
    if (R == 0) {
        fputs("ERROR - R cannot be 0", stderr);
        return -3;
    }

    // Calculate all values
    double U_P = diode(U_0, R, eps);
    double I_P = I_0 * (exp(U_P / U_T) - 1);

    // Print results
    printf("Up=%g V\n", U_P);
    printf("Ip=%g A\n", I_P);
    return 0;
}

/**
 * @param *char argument to be parsed
 * @return parsed double
 * @throws Parsing error if provided argument is of type double
 *
 * Checks argument and returns parsed value
 */
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

/**
 * @param u0 input voltage
 * @param r resistance
 * @param eps max deviation
 * @return calculated U_P
 *
 * Calculates U_P based on provided parameters
 */
double diode(double u0, double r, double eps) {
    // Initialize return variable
    double ret;
    // Get U_P Value
    ret = calculateAccurateUP(u0, r, eps);
    // Return U_P Value
    return ret;
}

/**
 * @param U_0 input voltage
 * @param R resistance
 * @param eps max deviation
 * @return approximated U_P
 *
 * Returns U_P that is approximated using bisection method
 */
double calculateAccurateUP(double U_0, double R, double eps) {
    // Define clamps
    double low = 0.;
    double max = U_0;

    // Variable that will hold the middle of our search
    double mid = U_0;

    // Loop till the difference is smaller or equal to epsilon
    while (fabs(getUPResult(mid, U_0, R)) >= eps) {
        // Calculate middle
        mid = (low + max) / 2;
        // Decide where to assign middle value
        if (getUPResult(mid, U_0, R) * getUPResult(low, U_0, R) < 0) {
            max = mid;
        } else {
            low = mid;
        }
    }
    // Return lower clamp as U_P
    return mid;
}

/**
 * @param U_P voltage that is used
 * @param U_0 input voltage
 * @param R resistivity
 * @return calculated result
 *
 * Returns the result with given U_P
 */
double getUPResult(double U_P, double U_0, double R) {
    double ret;
    // I_0 * (exp(U_P / U_T) - 1) - ((U_0 - U_P) / R) = 0
    ret = I_0 * (exp(U_P / U_T) - 1) - ((U_0 - U_P) / R);
    return ret;
}