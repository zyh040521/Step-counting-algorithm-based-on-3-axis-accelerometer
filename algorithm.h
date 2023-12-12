#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data_definition.h"


// correspond to the Application Note
#define Window_size 50
// correspond to the Application Note
#define Threshold_order 6


// Function to calculate thresholds based on the primary axis
double* threshold_algorithm(THREE_AXIS_INFO* inputData, int primaryAxis) {
    // Array to store the generated thresholds
    static double thresholds[SAMPLE_SIZE / Window_size];

    // Variables for threshold generation
    int dataIndex = 0;
    int countIndex = 0;
    double maxVal, minVal;
    maxVal = -90;
    minVal = 90;

    // Iterating through the data
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        // Finding the maximum and minimum values based on the primary axis
        switch (primaryAxis) {
            case X_AXIS: {
                maxVal = maxVal >= inputData[i].x ? maxVal : inputData[i].x;
                minVal = minVal <= inputData[i].x ? minVal : inputData[i].x;
                break;
            }
            case Y_AXIS: {
                maxVal = maxVal >= inputData[i].y ? maxVal : inputData[i].y;
                minVal = minVal <= inputData[i].y ? minVal : inputData[i].y;
                break;
            }
            default: {
                maxVal = maxVal >= inputData[i].z ? maxVal : inputData[i].z;
                minVal = minVal <= inputData[i].z ? minVal : inputData[i].z;
                break;
            }
        }

        countIndex++;

        // Calculating mean threshold after Window_size steps
        if (countIndex % Window_size == 0) {
            countIndex = 0;
            // Storing the calculated threshold
            thresholds[dataIndex] = (maxVal + minVal) / 2;
            dataIndex++;
            maxVal = -90;
            minVal = 90;
        }
    }

    // Returning the generated thresholds
    return thresholds;
}


// Function to determine steps based on thresholds and primary axis
int* step_algorithm(THREE_AXIS_INFO* inputData, int primaryAxis, double* thresholds) {
    // Array to store the steps counted for every minute
    static int stepsCount[5];

    // Variables for steps calculation
    int steps = 0;
    bool activated = false;
    int highLevelCount = 0;
    int minuteCount = 0;

    // Comparing values with thresholds
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        double currentValue;

        // Extracting the value based on the primary axis
        switch (primaryAxis) {
            case X_AXIS: {
                currentValue = inputData[i].x;
                break;
            }
            case Y_AXIS: {
                currentValue = inputData[i].y;
                break;
            }
            default: {
                currentValue = inputData[i].z;
                break;
            }
        }

        // Comparing with the corresponding threshold
        if (currentValue >= thresholds[i / Window_size]) {
            if (!activated) {
                activated = true;
                highLevelCount = 0;
            }
            highLevelCount++;
        } else {
            if (activated) {
                activated = false;
                if (highLevelCount >= Threshold_order) {
                    steps++;
                }
            }
        }

        // Checking if a minute has passed
        minuteCount++;
        if (minuteCount % 3000 == 0) {
            stepsCount[minuteCount / 3000 - 1] = steps;
        }
    }

    // Returning the calculated steps per minute
    return stepsCount;
}
