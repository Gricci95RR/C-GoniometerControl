/**
 * @file logging.hpp
 * @author Gianmarco Ricci CERN BE/CEM/MRO 2024
 * @brief Logging Class.
 *
 * @version 0.1
 * @date 24/04/2024
 *
 * @copyright Ã‚Â© Copyright CERN 2018. All rights reserved. This software is released under a CERN proprietary software license.
 * Any permission to use it shall be granted in writing. Requests shall be addressed to CERN through mail-KT@cern.ch
 *
 */
#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Logging {
public:
	/**
	 * @brief Constructor for the Logging class.
	 *
	 * Initializes a Logging object with the specified buffer size. The buffer size
	 * determines the maximum number of yaw angles that can be stored in the buffer.
	 *
	 * @param bufferSize The size of the buffer.
	 */
	Logging(size_t bufferSize) : bufferSize_(bufferSize) {
	    YawAngle_.resize(bufferSize);
	}

	~Logging() {
	    // Destructor implementation
	}

    /**
     * @brief Adds an element to the buffer.
     *
     * Adds the specified value to the end of the buffer. If the buffer size
     * exceeds the desired size, the oldest element is removed.
     *
     * @param value The value to be added to the buffer.
     */
    void addElement(const float& value) {
        YawAngle_.push_back(value); // Add value to the end
        // If the buffer size exceeds the desired size, remove the oldest element
        if (YawAngle_.size() > bufferSize_) {
            YawAngle_.erase(YawAngle_.begin());
        }
    }

    /**
     * @brief Prints the contents of the buffer to the standard output.
     */
    void printBuffer() {
        for (auto& element : YawAngle_) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints the start of the logging JSON.
     */
    void printStartLogging () {
        std::cout << "{\"" << "Logging" << "\": ["; // print start
    }

    /**
     * @brief Prints the end of the logging JSON.
     */
    void printEndLogging () {
        std::cout << "]}" << std::endl; // print end
    }

    /**
     * @brief Prints a separator for logging JSON elements.
     */
    void printSeparatorLogging () {
        std::cout << ", "; // print separator
    }

    /**
     * @brief Prints a data item for logging JSON.
     *
     * @param data The data item to be printed.
     */
    void printDataLogging(float data) {
        std::cout << data; // print item
    }

    /**
	 * @brief Prints a data item for logging JSON.
	 *
	 * @param data The data item to be printed.
	 */
	void printDataLogging(long int data) {
		std::cout << data; // print item
	}

    /**
     * @brief Starts the logging process.
     *
     * Sets the flag to start logging and resets the counter.
     */
    void startLogging() {
        startLogging_ = true;
        counterLogging_ = 0;
    }

    /**
     * @brief Ends the logging process.
     *
     * Sets the flag to end logging.
     */
    void endLogging() {
        startLogging_ = false;
    }

	/**
	 * @brief Calculates the logging length based on the input seconds.
	 *
	 * This function calculates the logging length in seconds based on the input
	 * duration in seconds using the formula: loggingLen = (2000 * loggingLeninSec) + 1.
	 *
	 * @param loggingLeninSec The duration of logging in seconds.
	 * @return The calculated logging length.
	 */
	int CalculateLoggingLength(int loggingLeninSec) {
	    int loggingLen = (2000 * loggingLeninSec) + 1;
	    return loggingLen;
	}

	/**
	 * @brief Logs data for a specified duration.
	 *
	 * This function logs data for a specified duration, printing start and end logging messages,
	 * as well as printing data (yaw angle and output voltage) along with separators between them.
	 *
	 * @param yawAngle The yaw angle to be logged.
	 * @param outputVoltage The output voltage to be logged.
	 * @param loggingLeninSec The duration of logging in seconds.
	 */
    void logData(float yawAngle, float outputVoltage, int loggingLeninSec) {
    	int loggingLen = CalculateLoggingLength(loggingLeninSec);
		if (startLogging_ && counterLogging_ == 0) {
			printStartLogging();
			counterLogging_++;
		} else if (startLogging_ && counterLogging_ < loggingLen) {
			printDataLogging(yawAngle);
			printSeparatorLogging();
			printDataLogging(outputVoltage);
			if (counterLogging_ < loggingLen - 1) { // Check if it's not the last item
				printSeparatorLogging();
			}
			counterLogging_++;
		} else if (startLogging_ && counterLogging_ == loggingLen) {
			printEndLogging();
			endLogging();
		}
	}

    /**
     * @brief Computes the standard deviation of the yaw angles in the buffer.
     *
     * This function calculates the standard deviation of the yaw angles stored
     * in the buffer. It first computes the mean of the yaw angles and then
     * calculates the variance. Finally, it returns the square root of the variance
     * as the standard deviation.
     *
     * @return The standard deviation of the yaw angles.
     */
    float computeStandardDeviationYawAngle() {
        float mean = this->computeMean();
        float variance = 0.0;

        for (float value : YawAngle_) {
            variance += (value - mean) * (value - mean);
        }
        variance /= YawAngle_.size();

        return std::sqrt(variance);
    }

    /**
     * @brief Computes the mean of the yaw angles in the buffer.
     *
     * This function calculates the mean of the yaw angles stored in the buffer.
     *
     * @return The mean of the yaw angles.
     */
    float computeMean() {
        float sum = 0.0;
        for (float value : YawAngle_) {
            sum += value;
        }
        return sum / YawAngle_.size();
    }

    /**
     * @brief Gets the current logging status.
     *
     * @return True if logging has started, false otherwise.
     */
    bool getStartLogging() const {
        return startLogging_;
    }

    /**
     * @brief Sets the logging status.
     *
     * @param value The value to set the logging status to.
     */
    void setStartLogging(bool value) {
        startLogging_ = value;
    }

private:
    size_t bufferSize_;  /**< Size of the buffer for storing yaw angles. */
    std::vector<float> YawAngle_;  /**< Vector to store yaw angles. */
    bool startLogging_ = false;  /**< Flag indicating whether logging has started. When true, logging is active; when false, logging is inactive. */
    int counterLogging_ = 0;  /**< Counter for logging events. */
};

#endif /* LOGGING_HPP */
