# Walking Analytics Library

This repository provides algorithms and data structures for analyzing walking patterns. It utilizes accelerometer data and angle information to compute step counts and body movements during walking.

## Data Definition

### THREE_AXIS_INFO Structure

- `x`: Angle information for forward and backward body swing
- `y`: Angle information for left and right body swing
- `z`: Angle information for spinning motion during walking

### createdata

Generates simulated accelerometer data and converts it into angle information.

### Filtering

Filters out noisy data by applying a mean filter to the raw data, reducing unnecessary fluctuations.

### findprimaryaxis

Determines the primary swing axis by calculating the variance of angle data across the three dimensions.


## Algorithms

### threshold_algorithm

Calculates thresholds to classify data into high and low-level movements.

### step_algorithm

Computes the number of steps taken based on thresholds and swing periods.

## Main

### logic Function

Contains the sequential invocation of all algorithms in the library, generating and analyzing simulated angle data.

## Usage

1. Import the Walking Analytics Library into your project.
2. Use the `logic` function with accelerometer data to retrieve step counts and swing patterns.

## Dependencies

- No external dependencies required.

## Run
To compile the program, use the following command:

```bash
gcc main.c -o pedometer -lm
./pedometer

