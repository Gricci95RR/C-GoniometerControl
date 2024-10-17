/**
 * @file GUIDataHandler.hpp
 * @author Gianmarco Ricci CERN BE/CEM/MRO 2024
 * @brief GUIDataHandler Class.
 *
 * @version 0.1
 * @date 24/04/2024
 *
 */

#include <iostream>
#include <memory>

#include "logging.hpp"

class GUIDataHandler {
public:
    // Constructor
    GUIDataHandler(std::shared_ptr<Logging> clientlogging):
    	clientlogging_(clientlogging),
		request_control_mode_(0), request_stop_motion_(0), request_waveform_(0),
	    request_stop_waveform_(0), request_warn_reset_(0),
	    request_hyst_comp_(0), voltage_ref_(0), yaw_ref_(0), waveform_number_(1){

    }

    ~GUIDataHandler() {

	}

    /* -- Functions to set the struct fields -- */

    /**
     * @brief Sets the controls data.
     *
     * Sets the controls data including state, yaw angle, yaw angle standard deviation,
     * and error axis values.
     *
     * @param state The state of the controls data.
     * @param yawAngle The yaw angle value.
     * @param yawAngleStdDeviation The standard deviation of the yaw angle.
     * @param warningLevel
     * @param errorAxis1 Error value for axis 1.
     * @param errorAxis2 Error value for axis 2.
     */
	void setControlsData(const std::string& state, float yawAngle, int warningLevel, float yawAngleStdDeviation, int errorAxis1, int errorAxis2) {
		controlsData_.state = state;
		controlsData_.yawAngle = yawAngle;
		controlsData_.warningLevel = warningLevel;
		controlsData_.yawAngleStdDeviation = yawAngleStdDeviation;
		controlsData_.errorAxis1 = errorAxis1;
		controlsData_.errorAxis2 = errorAxis2;
	}

	/**
	 * @brief Sets the general settings data.
	 *
	 * Sets the general settings data including yaw offset, AAR offset, protection settings,
	 * voltage limits, and speed limits.
	 *
	 * @param yawOffset Yaw offset value.
	 * @param AAROffset AAR offset value.
	 * @param controlInstabilityProtection Control instability protection setting.
	 * @param interferometerInstabilityProtection Interferometer instability protection setting.
	 * @param minVoltage Minimum voltage.
	 * @param maxVoltage Maximum voltage.
	 * @param openLoopMaxSpeed Maximum speed in open loop mode.
	 * @param closedLoopMaxSpeed Maximum speed in closed loop mode.
	 * @param minPIDLimit Minimum PID limit.
	 * @param maxPIDLimit Maximum PID limit.
	 */
	void setGeneralSettingsData(float yawOffset,
	                            float AAROffset,
	                            int controlInstabilityProtection,
	                            int interferometerInstabilityProtection,
	                            float minVoltage,
	                            float maxVoltage,
	                            float openLoopMaxSpeed,
	                            float closedLoopMaxSpeed,
	                            float minPIDLimit,
	                            float maxPIDLimit) {
		generalSettingsData_.yawOffset = yawOffset;
		generalSettingsData_.AAROffset = AAROffset;
		generalSettingsData_.controlInstabilityProtection = controlInstabilityProtection;
		generalSettingsData_.interferometerInstabilityProtection = interferometerInstabilityProtection;
		generalSettingsData_.minVoltage = minVoltage;
		generalSettingsData_.maxVoltage = maxVoltage;
		generalSettingsData_.openLoopMaxSpeed = openLoopMaxSpeed;
		generalSettingsData_.closedLoopMaxSpeed = closedLoopMaxSpeed;
		generalSettingsData_.minPIDLimit = minPIDLimit;
		generalSettingsData_.maxPIDLimit = maxPIDLimit;
	}

	/**
	 * @brief Sets the control settings data.
	 *
	 * Sets the control settings data including prefilter, filters, compensation,
	 * and parameters.
	 *
	 * @param prefilterNumerator_arg0 Argument 0 of the prefilter numerator.
	 * @param prefilterNumerator_arg1 Argument 1 of the prefilter numerator.
	 * @param prefilterNumerator_arg2 Argument 2 of the prefilter numerator.
	 * @param prefilterNumerator_arg3 Argument 3 of the prefilter numerator.
	 * @param prefilterDenominator_arg0 Argument 0 of the prefilter denominator.
	 * @param prefilterDenominator_arg1 Argument 1 of the prefilter denominator.
	 * @param filter1Numerator_arg0 Argument 0 of the filter 1 numerator.
	 * @param filter1Numerator_arg1 Argument 1 of the filter 1 numerator.
	 * @param filter1Numerator_arg2 Argument 2 of the filter 1 numerator.
	 * @param filter1Numerator_arg3 Argument 3 of the filter 1 numerator.
	 * @param filter1Denominator_arg0 Argument 0 of the filter 1 denominator.
	 * @param filter1Denominator_arg1 Argument 1 of the filter 1 denominator.
	 * @param filter2Numerator_arg0 Argument 0 of the filter 2 numerator.
	 * @param filter2Numerator_arg1 Argument 1 of the filter 2 numerator.
	 * @param filter2Denominator Denominator of filter 2.
	 * @param filter3Numerator_arg0 Argument 0 of the filter 3 numerator.
	 * @param filter3Numerator_arg1 Argument 1 of the filter 3 numerator.
	 * @param filter3Denominator Denominator of filter 3.
	 * @param hysteresisCompensation Hysteresis compensation setting.
	 * @param compensationOffset Compensation offset.
	 * @param quadraticParameters_arg0 Argument 0 of the quadratic parameters.
	 * @param quadraticParameters_arg1 Argument 1 of the quadratic parameters.
	 * @param fParameters_arg0 Argument 0 of the f parameters.
	 * @param fParameters_arg1 Argument 1 of the f parameters.
	 * @param kParameters_arg0 Argument 0 of the k parameters.
	 * @param kParameters_arg1 Argument 1 of the k parameters.
	 */
	void setControlSettingsData(float prefilterNumerator_arg0, float prefilterNumerator_arg1, float prefilterNumerator_arg2, float prefilterNumerator_arg3,
								float prefilterDenominator_arg0, float prefilterDenominator_arg1,
								float filter1Numerator_arg0, float filter1Numerator_arg1, float filter1Numerator_arg2, float filter1Numerator_arg3,
								float filter1Denominator_arg0, float filter1Denominator_arg1,
								float filter2Numerator_arg0, float filter2Numerator_arg1,
								float filter2Denominator,
								float filter3Numerator_arg0, float filter3Numerator_arg1,
								float filter3Denominator,
								int hysteresisCompensation,
								float compensationOffset,
								float quadraticParameters_arg0, float quadraticParameters_arg1,
								float fParameters_arg0, float fParameters_arg1,
								float kParameters_arg0, float kParameters_arg1) {
		controlSettingsData_ = {{prefilterNumerator_arg0, prefilterNumerator_arg1, prefilterNumerator_arg2, prefilterNumerator_arg3},
		                        {prefilterDenominator_arg0, prefilterDenominator_arg1},
		    					{filter1Numerator_arg0, filter1Numerator_arg1, filter1Numerator_arg2, filter1Numerator_arg3},
		    					{filter1Denominator_arg0, filter1Denominator_arg1},
		    					{filter2Numerator_arg0, filter2Numerator_arg1},
								filter2Denominator,
		    					{filter3Numerator_arg0, filter3Numerator_arg1},
								filter3Denominator,
								hysteresisCompensation,
								compensationOffset,
		    					{quadraticParameters_arg0, quadraticParameters_arg1},
		    					{fParameters_arg0, fParameters_arg1},
		    					{kParameters_arg0, kParameters_arg1}
		};
	}

    /* -- Functions to send messages to GUI -- */

    /**
     * @brief Serializes the ControlsDataStruct object into a JSON-formatted string.
     *
     * This function takes a ControlsDataStruct object and converts it into a JSON-formatted string representation.
     * The string includes key-value pairs representing the state, yaw angle, yaw angle standard deviation,
     * error on axis 1, and error on axis 2. The precision of floating-point values is fixed at 6 decimal places.
     *
     * @param data The ControlsDataStruct object to be serialized.
     * @return A JSON-formatted string representing the serialized ControlsDataStruct object.
     */
    std::string serializeControlsData() {
        std::stringstream ss;
        ss << "{\"Controls\": {";  // Object starts
        ss << "\"state\": \"" << controlsData_.state << "\", ";
        ss << "\"warninglevel\": \"" << controlsData_.warningLevel << "\", ";
        ss << "\"yawAngle\": " << std::fixed << std::setprecision(6) << controlsData_.yawAngle << ", "; // Assuming precision of 6
        ss << "\"yawAngleStdDeviation\": " << std::fixed << std::setprecision(6) << controlsData_.yawAngleStdDeviation << ", ";
        ss << "\"errorAxis1\": " << controlsData_.errorAxis1 << ", ";
        ss << "\"errorAxis2\": " << controlsData_.errorAxis2;
        ss << "}}";  // Object ends
        return ss.str();
    }

    /**
     * @brief Serializes the GeneralSettingsDataStruct object into a JSON-formatted string.
     *
     * This function takes a GeneralSettingsDataStruct object and converts it into a JSON-formatted string representation.
     * The string includes key-value pairs representing various general settings such as yaw offset, AAR offset,
     * control instability protection, etc. The precision of floating-point values is fixed at 6 decimal places.
     *
     * @param data The GeneralSettingsDataStruct object to be serialized.
     * @return A JSON-formatted string representing the serialized GeneralSettingsDataStruct object.
     */
    std::string serializeGeneralSettingsData() {
        std::stringstream ss;
        ss << "{\"General settings\": {";  // Object starts
        ss << "\"yawOffset\": " << std::fixed << std::setprecision(6) << generalSettingsData_.yawOffset << ", ";
        ss << "\"AAROffset\": " << std::fixed << std::setprecision(6) << generalSettingsData_.AAROffset << ", ";
        ss << "\"controlInstabilityProtection\": " << generalSettingsData_.controlInstabilityProtection << ", ";
        ss << "\"interferometerInstabilityProtection\": " << generalSettingsData_.interferometerInstabilityProtection << ", ";
        ss << "\"minVoltage\": " << std::fixed << std::setprecision(6) << generalSettingsData_.minVoltage << ", ";
        ss << "\"maxVoltage\": " << std::fixed << std::setprecision(6) << generalSettingsData_.maxVoltage << ", ";
        ss << "\"openLoopMaxSpeed\": " << std::fixed << std::setprecision(6) << generalSettingsData_.openLoopMaxSpeed << ", ";
        ss << "\"closedLoopMaxSpeed\": " << std::fixed << std::setprecision(6) << generalSettingsData_.closedLoopMaxSpeed << ", ";
        ss << "\"minPIDLimit\": " << std::fixed << std::setprecision(6) << generalSettingsData_.minPIDLimit << ", ";
        ss << "\"maxPIDLimit\": " << std::fixed << std::setprecision(6) << generalSettingsData_.maxPIDLimit;
        ss << "}}";  // Object ends
        return ss.str();
    }

    /**
     * @brief Serializes the ControlSettingsDataStruct object into a JSON-formatted string.
     *
     * This function takes a ControlSettingsDataStruct object and converts it into a JSON-formatted string representation.
     * The string includes key-value pairs representing various control settings such as prefilter numerator,
     * filter numerator, compensation offset, etc. Array elements are serialized within square brackets.
     * The precision of floating-point values is fixed at 6 decimal places.
     *
     * @param data The ControlSettingsDataStruct object to be serialized.
     * @return A JSON-formatted string representing the serialized ControlSettingsDataStruct object.
     */
    std::string serializeControlSettingsData() {
        std::stringstream ss;
        ss << "{\"Control settings\": {";  // Object starts
        ss << "\"prefilterNumerator\": [" << controlSettingsData_.prefilterNumerator[0] << ", " << controlSettingsData_.prefilterNumerator[1] << ", "
           << controlSettingsData_.prefilterNumerator[2] << ", " << controlSettingsData_.prefilterNumerator[3] << "], ";
        ss << "\"prefilterDenominator\": [" << controlSettingsData_.prefilterDenominator[0] << ", " << controlSettingsData_.prefilterDenominator[1] << "], ";
        ss << "\"filter1Numerator\": [" << controlSettingsData_.filter1Numerator[0] << ", " << controlSettingsData_.filter1Numerator[1] << ", "
           << controlSettingsData_.filter1Numerator[2] << ", " << controlSettingsData_.filter1Numerator[3] << "], ";
        ss << "\"filter1Denominator\": [" << controlSettingsData_.filter1Denominator[0] << ", " << controlSettingsData_.filter1Denominator[1] << ", "
           << controlSettingsData_.filter1Denominator[2] << ", " << controlSettingsData_.filter1Denominator[3] << "], ";
        ss << "\"filter2Numerator\": [" << controlSettingsData_.filter2Numerator[0] << ", " << controlSettingsData_.filter2Numerator[1] << "], ";
        ss << "\"filter2Denominator\": " << controlSettingsData_.filter2Denominator << ", ";
        ss << "\"filter3Numerator\": [" << controlSettingsData_.filter3Numerator[0] << ", " << controlSettingsData_.filter3Numerator[1] << "], ";
        ss << "\"filter3Denominator\": " << controlSettingsData_.filter3Denominator << ", ";
        ss << "\"hysteresisCompensation\": " << controlSettingsData_.hysteresisCompensation << ", ";
        ss << "\"compensationOffset\": " << std::fixed << std::setprecision(6) << controlSettingsData_.compensationOffset << ", ";
        ss << "\"quadraticParameters\": [" << controlSettingsData_.quadraticParameters[0] << ", " << controlSettingsData_.quadraticParameters[1] << "], ";
        ss << "\"fParameters\": [" << controlSettingsData_.fParameters[0] << ", " << controlSettingsData_.fParameters[1] << "], ";
        ss << "\"kParameters\": [" << controlSettingsData_.kParameters[0] << ", " << controlSettingsData_.kParameters[1] << "]";
        ss << "}}";  // Object ends
        return ss.str();
    }

    /* -- Functions for reading messages from GUI  -- */

    /**
     * @brief Checks if the value associated with a given key in a JSON string matches an expected value.
     *
     * This function searches for the specified key in the provided JSON string and extracts its associated value.
     * It then converts the extracted value to an integer and compares it with the expected value.
     * If the key is not found or the extracted value does not match the expected value, the function returns false.
     * Otherwise, it returns true.
     *
     * @param jsonString The JSON string to search for the key and its associated value.
     * @param key The key to search for in the JSON string.
     * @param expectedValue The expected value to compare with the value associated with the key.
     * @return True if the value associated with the key matches the expected value, false otherwise.
     */
    bool checkValueForKey(const std::string& jsonString, const std::string& key, int expectedValue) {
        // Find the position of the key in the string
        size_t keyPos = jsonString.find("\"" + key + "\"");
        // If the key is not found, return false
        if (keyPos == std::string::npos) {
            return false;
        }
        // Find the position of the colon after the key
        size_t colonPos = jsonString.find(":", keyPos);
        // Find the position of the comma after the value of the key
        size_t commaPos = jsonString.find(",", colonPos);
        // Extract the substring representing the value of the key
        std::string valueString = jsonString.substr(colonPos + 1, commaPos - colonPos - 1);
        // Convert the extracted substring to an integer
        int value = std::stoi(valueString);
        // Return true if the value matches the expected value, false otherwise
        return (value == expectedValue);
    }

    /**
     * @brief Returns the value associated with a given key in a JSON-formatted string.
     *
     * This function searches for the specified key in the provided JSON string and extracts its associated value.
     * If the key is found, the function returns the value as a string. If the key is not found, the function
     * returns the string "None".
     *
     * @param jsonString The JSON-formatted string to search for the key and its associated value.
     * @param key The key to search for in the JSON string.
     * @return The value associated with the key as a string if the key is found, or "None" if the key is not found.
     */
    std::string returnValueForKey(const std::string& jsonString, const std::string& key) {
        // Find the position of the key in the string
        size_t keyPos = jsonString.find("\"" + key + "\"");
        // If the key is not found, return false
        if (keyPos == std::string::npos) {
            return "None";
        }
        // Find the position of the colon after the key
        size_t colonPos = jsonString.find(":", keyPos);
        // Find the position of the comma after the value of the key
        size_t commaPos = jsonString.find(",", colonPos);
        // Extract the substring representing the value of the key
        std::string valueString = jsonString.substr(colonPos + 1, commaPos - colonPos - 1);
        // Convert the extracted substring to an integer
        std::string value = valueString;
        // Return true if the value matches the expected value, false otherwise
        return value;
    }

    /**
     * @brief Returns the value at a specified index of an array associated with a given key in a JSON-formatted string.
     *
     * This function searches for the specified key in the provided JSON string and extracts the associated array.
     * It then retrieves the value at the specified index in the array and returns it as a string. If the key is not
     * found or the index is out of bounds, the function returns the string "None".
     *
     * @param jsonString The JSON-formatted string to search for the key and its associated array.
     * @param key The key to search for in the JSON string.
     * @param index The index of the value to retrieve from the associated array.
     * @return The value at the specified index of the array associated with the key as a string if the key is found
     * and the index is valid, or "None" if the key is not found or the index is out of bounds.
     */
    std::string returnValueArrayForKey(const std::string& jsonString, const std::string& key, int index) {
        // Find the position of the key in the string
        size_t keyPos = jsonString.find("\"" + key + "\"");

        // If the key is not found, return "None"
        if (keyPos == std::string::npos) {
            return "None";
        }

        // Find the position of the colon after the key
        size_t colonPos = jsonString.find(":", keyPos);

        // Find the position of the opening square bracket after the colon
        size_t arrayStartPos = jsonString.find("[", colonPos);

        // Find the position of the closing square bracket after the opening square bracket
        size_t arrayEndPos = jsonString.find("]", arrayStartPos);

        // Extract the substring representing the array
        std::string arrayString = jsonString.substr(arrayStartPos + 1, arrayEndPos - arrayStartPos - 1);

        // Count the number of commas in the array to determine the number of elements
        int count = 0;
        for (size_t i = 0; i < arrayString.length(); ++i) {
            if (arrayString[i] == ',') {
                count++;
            }
        }

        // Split the array string into individual elements
        size_t startPos = 0;
        size_t endPos = arrayString.find(",");
        std::string element;
        for (int i = 0; i <= count; ++i) {
            // Extract the current element
            if (endPos == std::string::npos) {
                element = arrayString.substr(startPos);
            } else {
                element = arrayString.substr(startPos, endPos - startPos);
            }

            // Trim any leading or trailing whitespace
            size_t firstNonSpace = element.find_first_not_of(" \t\r\n");
            size_t lastNonSpace = element.find_last_not_of(" \t\r\n");
            if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
                element = element.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
            }

            // If the index matches the current element, return it
            if (i == index) {
                return element;
            }

            // Update start and end positions for the next iteration
            startPos = endPos != std::string::npos ? endPos + 1 : std::string::npos;
            endPos = arrayString.find(",", startPos);
        }

        // If index is out of bounds, return "None"
        return "None";
    }

    /**
     * @brief Handles the controls tab based on the received string.
     *
     * @param receivedString The string containing the control data received from the GUI.
     */
    void handleControlsTab(std::string receivedString) {
    	std::cout << "function handleControlsTab called" << std::endl;
    	if (this->checkValueForKey(receivedString, "StartM", 1)) {
    		std::cout << "StartM Pressed value> 1" << std::endl;
    		float setpoint   = std::stof(this->returnValueForKey(receivedString, "SP (V/urad)"));
    		std::cout << "setpoint  = " << setpoint << std::endl;
    		std::string mode = (this->returnValueForKey(receivedString, "Mode"));
    		std::cout << "mode  = " << mode << std::endl;
    		this->setVoltageRef(setpoint);
    		this->setYawRef(setpoint);
    		this->setRequestStartMotion(1);
    		std::cout << "ok  StartM" << std::endl;
    	}
    	if (this->checkValueForKey(receivedString, "StartM", 0)) {
    		std::cout << "StartM value: 0 ------" << std::endl;
    		this->setRequestStartMotion(0);
    	}
    	if (this->checkValueForKey(receivedString, "StopM", 1)) {
    		std::cout << "StopM PRESSED value: 1 ------" << std::endl;
    		this->setRequestStopMotion(1);
    	}
    	if (this->checkValueForKey(receivedString, "StopM", 0)) {
    		std::cout << "StopM value: 0 ------" << std::endl;
    		this->setRequestStopMotion(0);
    		std::cout << "ok  StopM 0" << std::endl;
    	}
    	if (this->checkValueForKey(receivedString, "Re warn reset", 1)) {
    		std::cout << "Re contr prot PRESSED value: 1 ------" << std::endl;
    		this->setRequestWarnReset(1);
    	}
    	if (this->checkValueForKey(receivedString, "Re warn reset", 0)) {
    	    std::cout << "Re contr prot PRESSED value: 0 ------" << std::endl;
    	    this->setRequestWarnReset(0);
    	}
    	if (this->checkValueForKey(receivedString, "Mode", 0)) {
			std::cout << "Stand by started ------" << std::endl;
			this->setRequestControlMode(1);
    	}
    	if (this->checkValueForKey(receivedString, "Mode", 1)) {
    		std::cout << "Open Loop Started ------" << std::endl;
    		this->setRequestControlMode(2);
    	}
    	if (this->checkValueForKey(receivedString, "Mode", 2)) {
    		std::cout << "Closed Loop Started ------" << std::endl;
    		this->setRequestControlMode(3);
    	}
    }

    /**
     * @brief Handles the General Settings tab based on the received string.
     *
     * @param receivedString The string containing the General Settings data received from the GUI.
     */
    void handleGeneralSettingsTab(std::string receivedString) {
    	std::cout << "function handleGeneralSettingsTab called" << std::endl;
    	if (this->checkValueForKey(receivedString, "Write general settings", 1)) {
    		this->setGeneralSettingsData(std::stof(this->returnValueForKey(receivedString, "yawOffset")),
    		                                         std::stof(this->returnValueForKey(receivedString, "AAROffset")),
    		                                         std::stoi(this->returnValueForKey(receivedString, "controlInstabilityProtection")),
    		                                         std::stoi(this->returnValueForKey(receivedString, "interferometerInstabilityProtection")),
    		                                         std::stof(this->returnValueForKey(receivedString, "minVoltage")),
    		                                         std::stof(this->returnValueForKey(receivedString, "maxVoltage")),
    		                                         std::stof(this->returnValueForKey(receivedString, "openLoopMaxSpeed")),
    		                                         std::stof(this->returnValueForKey(receivedString, "closedLoopMaxSpeed")),
    		                                         std::stof(this->returnValueForKey(receivedString, "minPIDLimit")),
    		                                         std::stof(this->returnValueForKey(receivedString, "maxPIDLimit"))
    		);

    	}
    }

    /**
     * @brief Handles the Control Settings tab based on the received string.
     *
     * @param receivedString The string containing the Control Settings data received from the GUI.
     */
    void handleControlSettingsTab(std::string receivedString) {
    	std::cout << "function handleControlSettingsTab called" << std::endl;
    	if (this->checkValueForKey(receivedString, "Write control settings", 1)) {
    		this->setControlSettingsData(
    		        	 std::stof(this->returnValueArrayForKey(receivedString, "prefilterNumerator", 0)),
    		             std::stof(this->returnValueArrayForKey(receivedString, "prefilterNumerator", 1)),
    		             std::stof(this->returnValueArrayForKey(receivedString, "prefilterNumerator", 2)),
    		             std::stof(this->returnValueArrayForKey(receivedString, "prefilterNumerator", 3)),
    		             std::stof(this->returnValueArrayForKey(receivedString, "prefilterDenominator", 0)),
    		             std::stof(this->returnValueArrayForKey(receivedString, "prefilterDenominator", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter1Numerator", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter1Numerator", 1)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter1Numerator", 2)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter1Numerator", 3)),
    				     std::stof(this->returnValueArrayForKey(receivedString, "filter1Denominator", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter1Denominator", 1)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter2Numerator", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter2Numerator", 1)),
    					 std::stof(this->returnValueForKey(receivedString, "filter2Denominator")),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter3Numerator", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "filter3Numerator", 1)),
    					 std::stof(this->returnValueForKey(receivedString, "filter3Denominator")),
    					 std::stoi(this->returnValueForKey(receivedString, "hysteresisCompensation")),
    					 std::stof(this->returnValueForKey(receivedString, "compensationOffset")),
    					 std::stof(this->returnValueArrayForKey(receivedString, "quadraticParameters", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "quadraticParameters", 1)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "fParameters", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "fParameters", 1)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "kParameters", 0)),
    					 std::stof(this->returnValueArrayForKey(receivedString, "kParameters", 1))
    		        );
    	}
    }

    /**
     * @brief Handles the Expert procedures tab based on the received string.
     *
     * @param receivedString The string containing the control data received from the GUI.
     */
    void handleExpertProceduresTab(std::string receivedString) {
        std::cout << "function handleExpertProceduresTab called" << std::endl;
        if (this->checkValueForKey(receivedString, "Profile motion Start", 1)) {
            int waveformID = std::stoi(this->returnValueForKey(receivedString, "waveformID"));
            clientlogging_->startLogging();
            this->setWaveformNumber(waveformID);
            this->setRequestWaveform(1);
        }
        if (this->checkValueForKey(receivedString, "Profile motion Start", 0)) {
            this->setRequestWaveform(0);
        }
        if (this->checkValueForKey(receivedString, "Profile motion Stop", 1)) {
            std::cout << "Profile motion Stop PRESSED ------" << std::endl;
            clientlogging_->endLogging();
            this->setRequestStopWaveform(1);
        }
        if (this->checkValueForKey(receivedString, "Profile motion Stop", 0)) {
            this->setRequestStopWaveform(0);
        }
        if (this->checkValueForKey(receivedString, "Ramp cycles motion Start", 1)) {
            float numberCycles = std::stof(this->returnValueForKey(receivedString, "numberCycles"));
            float rampRate = std::stof(this->returnValueForKey(receivedString, "rampRate"));
            this->setNumberCycles(numberCycles);
            this->setRampRate(rampRate);
            this->setWaveformNumber(4);  // in order to start the motion this parameter should be set to 4
            std::cout << "Ramp cycles motion Start PRESSED ------" << std::endl;
            clientlogging_->startLogging();
            this->setRequestWaveform(1);
        }
        if (this->checkValueForKey(receivedString, "Ramp cycles motion Start", 0)) {
            this->setRequestWaveform(0);
        }
        if (this->checkValueForKey(receivedString, "Ramp cycles motion Stop", 1)) {
            std::cout << "Ramp cycles motion Stop PRESSED ------" << std::endl;
            clientlogging_->endLogging();
            this->setRequestStopWaveform(1);
        }
        if (this->checkValueForKey(receivedString, "Ramp cycles motion Stop", 0)) {
            this->setRequestStopWaveform(0);
        }
        if (this->checkValueForKey(receivedString, "Logging", 1)) {
            std::cout << "Logging STARTED ------" << std::endl;
            clientlogging_->startLogging();
        }
    }


    /**
     * @brief Interprets the received string and delegates handling to corresponding tab handling functions.
     *
     * This function serves as a central dispatcher for interpreting the received string and delegating the handling
     * of specific tabs to their respective functions. It calls the following functions sequentially:
     * - handleControlsTab: Handles the controls tab based on the received string.
     * - handleGeneralSettingsTab: Handles the general settings tab based on the received string.
     * - handleControlSettingsTab: Handles the control settings tab based on the received string.
     * - handleExpertProceduresTab: Handles the expert procedures tab based on the received string.
     *
     * @param receivedString The string containing the data received from an external source.
     */
    void interpreter(std::string receivedString) {
    	handleControlsTab(receivedString);
    	handleGeneralSettingsTab(receivedString);
    	handleControlSettingsTab(receivedString);
    	handleExpertProceduresTab(receivedString);
    }

    // Getter and Setter for request_closed_loop_
	int getRequestControlMode() const { return request_control_mode_; }
	void setRequestControlMode(int value) { request_control_mode_ = value; }

	// Getter and Setter for request_stop_motion_
	int getRequestStopMotion() const { return request_stop_motion_; }
	void setRequestStopMotion(int value) { request_stop_motion_ = value; }

	// Getter and Setter for request_start_motion_
	int getRequestStartMotion() const { return request_start_motion_; }
	void setRequestStartMotion(int value) { request_start_motion_ = value; }

	// Getter and Setter for request_waveform_
	int getRequestWaveform() const { return request_waveform_; }
	void setRequestWaveform(int value) { request_waveform_ = value; }

	// Getter and Setter for request_stop_waveform_
	int getRequestStopWaveform() const { return request_stop_waveform_; }
	void setRequestStopWaveform(int value) { request_stop_waveform_ = value; }

	// Getter and Setter for request_warn_reset_
	int getRequestWarnReset() const { return request_warn_reset_; }
	void setRequestWarnReset(int value) { request_warn_reset_ = value; }

	// Getter and Setter for request_hyst_comp_
	int getRequestHystComp() const { return request_hyst_comp_; }
	void setRequestHystComp(int value) { request_hyst_comp_ = value; }

	// Getter and Setter for voltage_ref_
	float getVoltageRef() const { return voltage_ref_; }
	void setVoltageRef(float value) { voltage_ref_ = value; }

	// Getter and Setter for yaw_ref_
	float getYawRef() const { return yaw_ref_; }
	void setYawRef(float value) { yaw_ref_ = value; }

	// Getter and Setter for waveform_number_
	int getWaveformNumber() { return waveform_number_; }
	void setWaveformNumber(int value) { waveform_number_ = value; }

	// Getter for numberCycles_
	float getNumberCycles() const {
		return numberCycles_;
	}

	// Setter for numberCycles_
	void setNumberCycles(float numberCycles) {
		numberCycles_ = numberCycles;
	}

	// Getter for rampRate_
	float getRampRate() const {
		return rampRate_;
	}

	// Setter for rampRate_
	void setRampRate(float rampRate) {
		rampRate_ = rampRate;
	}

	/* Getter funtions GeneralSettingsDataStruct */
	float getYawOffset() const { return generalSettingsData_.yawOffset; }
	float getAAROffset() const { return generalSettingsData_.AAROffset; }
	int getControlInstabilityProtection() const { return generalSettingsData_.controlInstabilityProtection; }
	int getInterferometerInstabilityProtection() const { return generalSettingsData_.interferometerInstabilityProtection; }
	float getMinVoltage() const { return generalSettingsData_.minVoltage; }
	float getMaxVoltage() const { return generalSettingsData_.maxVoltage; }
	float getOpenLoopMaxSpeed() const { return generalSettingsData_.openLoopMaxSpeed; }
	float getClosedLoopMaxSpeed() const { return generalSettingsData_.closedLoopMaxSpeed; }
	float getMinPIDLimit() const { return generalSettingsData_.minPIDLimit; }
	float getMaxPIDLimit() const { return generalSettingsData_.maxPIDLimit; }

	/* Getter funtions ControlSettingsDataStruct  */
    float getPrefilterNumerator(int index) const {
        return controlSettingsData_.prefilterNumerator[index];
    }
    float getPrefilterDenominator(int index) const {
        return controlSettingsData_.prefilterDenominator[index];
    }
    float getFilter1Numerator(int index) const {
        return controlSettingsData_.filter1Numerator[index];
    }
    float getFilter1Denominator(int index) const {
        return controlSettingsData_.filter1Denominator[index];
    }
    float getFilter2Numerator(int index) const {
        return controlSettingsData_.filter2Numerator[index];
    }
    float getFilter2Denominator() const {
        return controlSettingsData_.filter2Denominator;
    }
    float getFilter3Numerator(int index) const {
        return controlSettingsData_.filter3Numerator[index];
    }
    float getFilter3Denominator() const {
        return controlSettingsData_.filter3Denominator;
    }
    int getHysteresisCompensation() const {
        return controlSettingsData_.hysteresisCompensation;
    }
    float getCompensationOffset() const {
        return controlSettingsData_.compensationOffset;
    }
    float getQuadraticParameters(int index) const {
        return controlSettingsData_.quadraticParameters[index];
    }
    float getFParameters(int index) const {
        return controlSettingsData_.fParameters[index];
    }
    float getKParameters(int index) const {
        return controlSettingsData_.kParameters[index];
    }

private:
    /**
     * @brief Represents the control data tab.
     *
     * This struct holds information related to control data,
     * including the state, yaw angle, standard deviation of yaw angle,
     * and error values for two axes.
     */
    struct ControlsDataStruct {
        std::string state; /**< The state of the control system. */
        float yawAngle; /**< The yaw angle value. */
        float yawAngleStdDeviation; /**< The standard deviation of the yaw angle. */
        int warningLevel;  /**< The warning level of the controller. */
        int errorAxis1; /**< The error value for axis 1. */
        int errorAxis2; /**< The error value for axis 2. */
    };
    ControlsDataStruct controlsData_ = {"init", 0.0f, 0.0f, 0, 0};  /**< Initializes a ControlsDataStruct object. */
    /**
     * @brief Represents the general settings data tab.
     *
     * This struct holds information related to general settings,
     * including offsets, protection settings, voltage limits,
     * and speed and PID limits.
     */
    struct GeneralSettingsDataStruct {
        float yawOffset; /**< The yaw offset value. */
        float AAROffset; /**< The AAR (Automatic Axial Realignment) offset value. */
        int controlInstabilityProtection; /**< The setting for control instability protection. */
        int interferometerInstabilityProtection; /**< The setting for interferometer instability protection. */
        float minVoltage; /**< The minimum voltage limit. */
        float maxVoltage; /**< The maximum voltage limit. */
        float openLoopMaxSpeed; /**< The maximum speed limit in open-loop mode. */
        float closedLoopMaxSpeed; /**< The maximum speed limit in closed-loop mode. */
        float minPIDLimit; /**< The minimum PID limit. */
        float maxPIDLimit; /**< The maximum PID limit. */
    };
    GeneralSettingsDataStruct generalSettingsData_ = {0.0f, 0.0f, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};  /**< Initializes a GeneralSettingsDataStruct object. */
    /**
     * @brief Represents the control settings data.
     *
     * This struct holds information related to control settings,
     * including filter coefficients, compensation parameters,
     * and other control parameters.
     */
    struct ControlSettingsDataStruct {
        float prefilterNumerator[4]; /**< Numerator coefficients for the prefilter. */
        float prefilterDenominator[2]; /**< Denominator coefficients for the prefilter. */
        float filter1Numerator[4]; /**< Numerator coefficients for filter 1. */
        float filter1Denominator[2]; /**< Denominator coefficients for filter 1. */
        float filter2Numerator[2]; /**< Numerator coefficients for filter 2. */
        float filter2Denominator; /**< Denominator coefficient for filter 2. */
        float filter3Numerator[2]; /**< Numerator coefficients for filter 3. */
        float filter3Denominator; /**< Denominator coefficient for filter 3. */
        int hysteresisCompensation; /**< Hysteresis compensation setting. */
        float compensationOffset; /**< Compensation offset value. */
        float quadraticParameters[2]; /**< Quadratic control parameters. */
        float fParameters[2]; /**< F parameters for control. */
        float kParameters[2]; /**< K parameters for control. */
    };
    ControlSettingsDataStruct controlSettingsData_ = {{0.0f, 0.0f, 0.0f, 0.0f}, // prefilterNumerator
                                      	  	  	  	 {0.0f, 0.0f},              // prefilterDenominator
    											     {0.0f, 0.0f, 0.0f, 0.0f},  // filter1Numerator
    											     {0.0f, 0.0f},              // filter1Denominator
    											     {0.0f, 0.0f},              // filter2Numerator
    											     0.0f,                      // filter2Denominator
    											     {0.0f, 0.0f},              // filter3Numerator
    											     0.0f,                      // filter3Denominator
    											     0,                         // hysteresisCompensation
    											     0.0f,                      // compensationOffset
    											     {0.0f, 0.0f},              // quadraticParameters
    											     {0.0f, 0.0f},              // fParameters
    											     {0.0f, 0.0f}               // kParameters
    };
    std::shared_ptr<Logging> clientlogging_;
    int request_control_mode_;
    int request_start_motion_;
    int request_stop_motion_;
    int request_waveform_;
    int request_stop_waveform_;
    int request_warn_reset_;
    int request_hyst_comp_;
    float voltage_ref_;
    float yaw_ref_;
    int waveform_number_;
    float numberCycles_;
    float rampRate_;
};
