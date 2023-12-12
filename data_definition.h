#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SAMPLE_SIZE 15000
#define FILTER_ORDER 5
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


#define pi 3.1415926535


typedef struct {
	double x;
	double y;
	double z;
} THREE_AXIS_INFO;


//// ==============Function to generate random acceleration data=====================
//THREE_AXIS_INFO* GenerateAccelerationData(void) {
//    // Initialize an array to store the generated data
//    static THREE_AXIS_INFO acceleration_data[SAMPLE_SIZE];
//    srand((unsigned int)time(NULL));
//    // Generate the data
//    for (int i = 0; i < SAMPLE_SIZE; i++) {
//        // Generate random acceleration values within a certain range (-5 to 5 m/s^2)
//        acceleration_data[i].x = -5 + (rand() % 10001) / 1000.0;
//        acceleration_data[i].y = -5 + (rand() % 10001) / 1000.0;
//        acceleration_data[i].z = sqrt(acceleration_data[i].x * acceleration_data[i].x + acceleration_data[i].y * acceleration_data[i].y);
//    }
//    // Return the generated acceleration data
//    return acceleration_data;
//}
//
//// ================Function to convert acceleration data to angular deviation data===================
//THREE_AXIS_INFO* ConvertToAngularDeviation(THREE_AXIS_INFO* acceleration_data) {
//    // Initialize an array to store the converted angular deviation data
//    static THREE_AXIS_INFO angular_deviation_data[SAMPLE_SIZE];
//    // Convert each set of acceleration data to angular deviation data
//    for (int i = 0; i < SAMPLE_SIZE; i++) {
//        // Calculate pitch angle
//        angular_deviation_data[i].x = atan2(acceleration_data[i].y, sqrt(acceleration_data[i].x * acceleration_data[i].x + acceleration_data[i].z * acceleration_data[i].z)) * 180.0 / pi;
//        // Calculate roll angle
//        angular_deviation_data[i].y = atan2(-acceleration_data[i].x, sqrt(acceleration_data[i].y * acceleration_data[i].y + acceleration_data[i].z * acceleration_data[i].z)) * 180.0 / pi;
//        // Calculate yaw angle (assuming z-axis represents yaw)
//        angular_deviation_data[i].z = atan2(acceleration_data[i].z, sqrt(acceleration_data[i].x * acceleration_data[i].x + acceleration_data[i].y * acceleration_data[i].y)) * 180.0 / pi;
//    }
//    // Return the converted angular deviation data
//    return angular_deviation_data;
//}

//================Generate data(angles) in 5 minutes with a sampling cycle 20ms==============

// Function to generate three-axis information
THREE_AXIS_INFO* createdata(void) {
    // Array to store generated data
    static THREE_AXIS_INFO dataInfo[SAMPLE_SIZE];

    // Set seed for randomization based on current time
    srand((unsigned int)time(NULL));

    // Generate the data
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        // Angle of body swinging back and forth during walking
        dataInfo[i].x = (double)(-15 + rand() % (30 + 1)) + (double)((double)(rand() % (99 + 1)) / 100);

        // Angle of body swinging left and right during walking
        dataInfo[i].y = (double)(-15 + rand() % (30 + 1)) + (double)((double)(rand() % (99 + 1)) / 100);

        // Angle of body spinning during walking
        double tempX = dataInfo[i].x / 180 * pi;
        double tempY = dataInfo[i].y / 180 * pi;
        double tempZ = acos(1 / sqrt(tan(tempX) * tan(tempX) + tan(tempY) * tan(tempY) + 1)) / pi * 180;
        dataInfo[i].z = tempZ;
    }

    // Return the created data
    return dataInfo;
}


// =========================Function to filter out noise from the original data====================
THREE_AXIS_INFO* Filtering(THREE_AXIS_INFO* inputData) {
    // Array to store the filtered data
    static THREE_AXIS_INFO filteredData[SAMPLE_SIZE];

    // Variables for data processing
    int dataIndex = 0;
    int filterIndex = 0;
    double sumX, sumY, sumZ;
    sumX = sumY = sumZ = 0;

    // Iterating through the input data
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        // Temporary summation of data components
        sumX += inputData[i].x;
        sumY += inputData[i].y;
        sumZ += inputData[i].z;

        filterIndex++;

        // Calculating mean values after FILTER_ORDER steps
        if (filterIndex % FILTER_ORDER == 0) {
            filterIndex = 0;
            for (int j = FILTER_ORDER * dataIndex; j < FILTER_ORDER * (dataIndex + 1); j++) {
                // Assigning mean values to the filtered data
                filteredData[j].x = sumX / FILTER_ORDER;
                filteredData[j].y = sumY / FILTER_ORDER;
                filteredData[j].z = sumZ / FILTER_ORDER;
            }
            dataIndex++;
            sumX = sumY = sumZ = 0;
        }
    }

    // Return the filtered data
    return filteredData;
}



//==================Pick up one primary axis by comparing variances=======================

// Function to determine the primary axis based on variance analysis
int findprimaryaxis(THREE_AXIS_INFO* inputData) {
    // Variables to store sums and variances
    double sumX, sumY, sumZ;
    sumX = sumY = sumZ = 0;

    // Calculate the sums of x, y, and z components
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        sumX += inputData[i].x;
        sumY += inputData[i].y;
        sumZ += inputData[i].z;
    }

    // Calculate the mean values
    sumX /= SAMPLE_SIZE;
    sumY /= SAMPLE_SIZE;
    sumZ /= SAMPLE_SIZE;

    // Variables to store variances
    double varX, varY, varZ;
    varX = varY = varZ = 0;

    // Calculate variances
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        varX += (inputData[i].x - sumX) * (inputData[i].x - sumX);
        varY += (inputData[i].y - sumY) * (inputData[i].y - sumY);
        varZ += (inputData[i].z - sumZ) * (inputData[i].z - sumZ);
    }

    varX /= SAMPLE_SIZE;
    varY /= SAMPLE_SIZE;
    varZ /= SAMPLE_SIZE;

    // Find the maximum variance
    double maxVariance = varX;
    maxVariance = maxVariance >= varY ? maxVariance : varY;
    maxVariance = maxVariance >= varZ ? maxVariance : varZ;

    // find the primary axis based on maximum variance
    if (maxVariance == varX) {
        return X_AXIS;
    } else if (maxVariance == varY) {
        return Y_AXIS;
    } else {
        return Z_AXIS;
    }
}


