#include <stdio.h>
#include "algorithm.h"


//============Create a .csv file based on the generated data================

// Function to create and write data to a CSV file
void download_data(char* fileName, THREE_AXIS_INFO* data, int* steps) {
    // Create or open the file for writing
    FILE *filePointer = fopen(fileName, "w");

    // Writing the column headers for angles
    fprintf(filePointer, "\"X-Angle(бу)\",\"Y-Angle(бу)\",\"Z-Angle(бу)\"\n");

    // Writing the sensor data
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        fprintf(filePointer, "%lf,%lf,%lf\n", data[i].x, data[i].y, data[i].z);
    }

    // Writing steps count for each minute
    for (int i = 0; i < 5; i++) {
        fprintf(filePointer, "\"%d Minute(s) Steps: \",%d\n", i + 1, steps[i]);
    }

    // Closing the file
    fclose(filePointer);
}


//========================logic function========================
int* logic(void) {
    // Generate a set of data over 5 minutes
    THREE_AXIS_INFO* originalData = createdata();

    // Filter the generated data
    THREE_AXIS_INFO* filteredData = Filtering(originalData);

    // Identify the primary axis
    int primaryAxis = findprimaryaxis(filteredData);

    // Obtain thresholds based on the original data and primary axis
    double* thresholds = threshold_algorithm(originalData, primaryAxis);

    // Output dynamic thresholds to a CSV file
    FILE *thresholdsFile = fopen("th.csv", "w");
    fprintf(thresholdsFile, "\"Thresholds\",\"Primary Axis\"\n");

    for (int i = 0; i < SAMPLE_SIZE / Window_size; i++) {
        if (i == 0) {
            fprintf(thresholdsFile, "%lf,%d\n", thresholds[i], primaryAxis);
        } else {
            fprintf(thresholdsFile, "%lf\n", thresholds[i]);
        }
    }

    fclose(thresholdsFile);

    // Determine steps based on processed data, primary axis, and thresholds
    int* steps = step_algorithm(filteredData, primaryAxis, thresholds);

    // Output original data to CSV
    download_data("ori.csv", originalData, steps);

    // Output filtered data to CSV
    download_data("fil.csv", filteredData, steps);

    // Display steps for each minute on the screen
    for (int k = 0; k < 5; k++) {
        printf("Steps in %d Minute(s): %d\n", k + 1, steps[k]);
    }

    return steps;
}


int main(){
    logic();
	return 0;
}
/**

* @References:
[1]nerajbobra. (2020). Embedded_pedometer [Online].
Available from: https://github.com/nerajbobra/embedded_pedometer (Accessed: December 11, 2023).

[2]Hepingood. (2023). Adxl345 [Online].
Available from: https://github.com/hepingood/adxl345 (Accessed: December 11, 2023).

[3]Analog Devices. (2022). Step Counting Using the ADXL367 [Online].
Available from: https://www.analog.com/en/products/adxl367.html (Accessed: December 11, 2023).

[4]Zhao, N. (2010). Full-Featured Pedometer Design Realized with 3-Axis Digital Accelerometer. Analog Dialogue. [Online].
Available from: https://www.analog.com/en/analog-dialogue/articles/pedometer-design-3-axis-digital-acceler.html (Accessed: December 11, 2023).

[5]Sky.J. (2018). Step counting algorithm based on three-axis accelerometer. [Online].
Available from: https://blog.csdn.net/Dancer__Sky/article/details/81504778 (Accessed: December 11, 2023).


*/