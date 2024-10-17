/**
 * @file utils.hpp
 * @author Gianmarco Ricci CERN BE/CEM/MRO 2024
 * @brief Utility functions and global variables for the project.
 *
 * @version 0.1
 * @date 5/02/2024
 * 
 */

#include <stdio.h>
#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h"
#include "xtime_l.h"
#include <stdbool.h>
#include <iostream>
#include <bitset>
#include <sstream>
#include "Xscugic.h"
#include "Xil_exception.h"
#include "xttcps.h"
#include <iomanip>
#include "xuartps.h"
#include <memory>

#include "controller.h"
#include "goniometer_fw0.h"
#include "goniometer_sim.h"

#include "logging.hpp"
#include "GUIDataHandler.hpp"

#define TTC_DEVICE_ID	    XPAR_XTTCPS_0_DEVICE_ID
#define TTC_INTR_ID		    XPAR_XTTCPS_0_INTR
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define BAUD_RATE 921600
#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR // Example UART base address

/* Global Variables */
Xuint32 *axis1_interferometer = (Xuint32 *)0xA0000000; // reg address that holds axis 1 interferometer displacement (first 32 bits)
Xuint32 *axis2_interferometer = (Xuint32 *)0xA0010000; // reg address that holds axis 2 interferometer displacement (first 32 bits)
Xuint32 *dac_word             = (Xuint32 *)0xA0030000; // reg address that holds the data word to be sent to the DAC

std::string displacementReadAxis1_hex;
std::string displacementReadAxis2_hex;
long int displacementReadAxis1_decimal;
long int displacementReadAxis2_decimal;
Xuint32 axis1_error_Signal;
Xuint32 axis2_error_Signal;

/**
 * @struct TmrCntrSetup
 * @brief Structure to hold timer counter setup parameters.
 */
typedef struct {
	const uint32_t OutputHz;  /* Output frequency */
    unsigned int Interval;	  /* Interval value */
	u8 Prescaler;	          /* Prescaler value */
	u16 Options;	          /* Option settings */
} TmrCntrSetup;
/**
 * @brief Table to store timer counter setup settings.
 */
static TmrCntrSetup SettingsTable[1] = {
	{2000, 0, 0, 0},	/* Ticker timer counter initial setup, only output freq */
};
/**
 * @brief Global variable for GIC (Generic Interrupt Controller).
 */
static XScuGic Intc;
/**
 * @brief Global variable for Timer.
 */
static XTtcPs Timer;

/**
 * @brief XUartPs object for UART communication.
 *
 * This object represents an instance of the Xilinx UART driver (XUartPs)
 * used for UART communication.
 *
 * Example usage:
 * @code
 * XUartPs uart; // Declare an instance of XUartPs
 * @endcode
 *
 * @note Before using the XUartPs object, appropriate initialization
 *       and configuration steps may be required.
 *
 * @see XUartPs_Init
 * @see XUartPs_CfgInitialize
 */
XUartPs uart;

/**
 * @brief Start time for measuring elapsed time.
 *
 * This variable represents the start time used for measuring the elapsed time.
 */
XTime start_time;

/**
 * @brief End time for measuring elapsed time.
 *
 * This variable represents the end time used for measuring the elapsed time.
 */
XTime end_time;

/**
 * @brief Array to store the elapsed time for each iteration of a timer interrupt.
 *
 * This array is used to store the elapsed time in microseconds for each iteration
 * of a timer interrupt. The elapsed time for each iteration is stored in a separate
 * element of the array.
 */
//uint32_t s_elapsed[1024];  /*< Array used to store the elapsed time in microseconds for each iteration of a timer interrupt */
//static size_t s_elapsed_idx = 0;  /*< Variable used as an index to store the elapsed time values in the s_elapsed array */

/**
 * @brief float value to store the output Voltage requested to the DAC.
 *
 */
float outputVoltage;

/**
 * @brief Size of the buffer for logging.
 *
 * This constant defines the size of the buffer used for logging.
 */
const size_t bufferSize = 20;

/**
 * @brief Pointer to a Logging object.
 *
 * This shared pointer points to a Logging object used for logging operations.
 */
std::shared_ptr<Logging> loggingObj =
        std::make_shared<Logging>(bufferSize);

/**
 * @brief Pointer to a GUIDataHandler object.
 *
 * This shared pointer points to a GUIDataHandler object used for handling GUI data.
 */
std::shared_ptr<GUIDataHandler> GUIDataHandlerObj =
        std::make_shared<GUIDataHandler>(loggingObj);

/**
 * @brief Counter used for frequency control of interrupts.
 *
 * This variable represents a counter used for frequency control of interrupts.
 * It is incremented or reset based on certain conditions to adjust interrupt
 * frequency.
 */
volatile int counter = 0;

/**
 * @brief Divider value for adjusting interrupt frequency.
 *
 * This variable represents the value used to divide the frequency of interrupts.
 * The frequency of interrupts (f_sending) is calculated as f_interrupts divided
 * by this divider value.
 */
int divider = 2000;

/**
 * @brief Flag to indicate if data processing is required.
 *
 * This flag is set to true by the interrupt service routine (ISR) to signal that
 * data needs to be processed in the main loop. The main loop checks this flag and
 * performs the necessary data processing tasks when the flag is set.
 *
 * @note The variable is marked as volatile to prevent optimization issues by the
 * compiler since it is accessed by both the ISR and the main loop.
 *
 * @warning Ensure that the ISR only sets the flag and does not perform
 * extensive processing to avoid increasing ISR execution time. The actual data
 * processing should be handled in the main loop where more complex operations
 * can be safely performed.
 *
 * @see TickHandler() for the ISR that sets this flag.
 */
volatile bool processDataFlag = false;

/* -- UART functions -- */

/**
 * @brief Reads data from UART and processes it.
 *
 * This function reads data from the specified UART interface and processes it.
 * It checks if there is data available to read and proceeds to read characters
 * until a termination condition ('}}') is met. Once a complete string is received,
 * it processes the string. If no data is available for reading, the function does
 * nothing.
 *
 * @param uart Pointer to the XUartPs structure representing the UART interface.
 *
 * @see XUartPs_IsReceiveData
 * @see XUartPs_RecvByte
 */
void readUART(XUartPs *uart) {
    static std::string receivedString;
    static const std::string endMarker = "}}";
    // Check if data is available to read
    while (XUartPs_IsReceiveData(uart->Config.BaseAddress)) {
        // Read data from UART
        char receivedChar = XUartPs_RecvByte(uart->Config.BaseAddress);
        // Append received character to the string
        receivedString += receivedChar;
        // Check if endMarker is present at the end of receivedString
        if (receivedString.size() >= endMarker.size() &&
            receivedString.compare(receivedString.size() - endMarker.size(), endMarker.size(), endMarker) == 0) {
            // Process receivedString
            GUIDataHandlerObj->interpreter(receivedString);
            // Clear the string for the next message
            receivedString.clear();
        }
    }
}

/**
 * @brief Set up UART interface and initialize it.
 *
 * This function initializes the UART interface with the specified configuration.
 * It sets up the UART interface according to the configuration provided,
 * initializes it, and sets the baud rate. If initialization fails, an error
 * message is printed.
 *
 * @return XUartPs An initialized XUartPs structure representing the UART interface.
 *
 * @see XUartPs_LookupConfig
 * @see XUartPs_CfgInitialize
 * @see XUartPs_SetBaudRate
 */
XUartPs setUpUART() {
	XUartPs uart;
	XUartPs_Config *config;
	// Initialize UART
	config = XUartPs_LookupConfig(XPAR_PSU_UART_0_DEVICE_ID);
	if (config == NULL) {
		printf("Error: Unable to lookup UART configuration.\n");
	}

	if (XUartPs_CfgInitialize(&uart, config, config->BaseAddress) != XST_SUCCESS) {
		printf("Error: UART initialization failed.\n");
	}
	// Set the baud rate for UART0
	XUartPs_SetBaudRate(&uart, BAUD_RATE);
	return uart;
}

/* -- Interferometer functions -- */

/**
 * @brief Check the sanity of a given displacement string.
 *
 * This function checks whether the provided displacement string begins with "0021d".
 *
 * @param displacementRead The displacement string to be checked.
 * @return true if the displacement string starts with "0021d", false otherwise.
 */
bool sanityCheck (std::string displacementRead) {
	if (displacementRead.substr(0, 4) == "002d") {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief Converts a hexadecimal string to binary.
 *
 * This function takes a hexadecimal string as input and converts it to a binary string.
 * It first converts the hexadecimal string to an integer and then converts the integer
 * to a binary string using std::bitset.
 *
 * @param hexString The input hexadecimal string.
 * @return The binary representation of the hexadecimal string.
 */
std::string hexToBinary(const std::string& hexString) {
    // Convert hex string to integer
    long int decimalValue;
    std::stringstream(hexString) >> std::hex >> decimalValue;

    // Convert decimal value to binary string
    std::bitset<48> binaryValue(decimalValue);
    return binaryValue.to_string();
}

/**
 * @brief Converts a hexadecimal string to decimal.
 *
 * This function takes a hexadecimal string as input and converts it to a decimal number.
 * It uses std::stringstream to perform the conversion.
 *
 * @param hexString The input hexadecimal string.
 * @return The decimal representation of the hexadecimal string.
 */
long int hexToDecimal(const std::string& hexString) {
    // Use stringstream to convert the hex string to decimal
    long int decimalNumber;
    std::stringstream(hexString) >> std::hex >> decimalNumber;

    return decimalNumber;
}

/**
 * @brief Converts a 32-bit hexadecimal number to a string with leading zeros.
 *
 * This function takes a 32-bit hexadecimal number (Xuint32) as input and converts it
 * to a string representation with leading zeros. The resulting string is 8 characters long.
 *
 * @param hexNumber The input 32-bit hexadecimal number.
 * @return The string representation of the hexadecimal number with leading zeros.
 */
std::string hexToStringWithLeadingZeros(const Xuint32& hexNumber) {
    // Convert the Xuint32 hexNumber to a string with leading zeros
    std::stringstream ss;
    ss << std::setw(8) << std::setfill('0') << std::hex << hexNumber;
    std::string hexString = ss.str();

    return hexString;
}

/**
 * @brief Reads the displacement and error signals from the interferometers for two axes.
 *
 * This function reads the first 32 bits and the last 16 bits of the displacement data from
 * the interferometers for two axes. It then combines these bits, converts them to a hexadecimal
 * string, and subsequently to a decimal value. Additionally, it reads the error signals
 * for both axes.
 *
 * @details
 * For each axis, the function performs the following steps:
 * - Reads the first 32 bits of displacement data from the interferometer.
 * - Reads the last 16 bits of displacement data from the interferometer.
 * - Converts these bits to a hexadecimal string with leading zeros.
 * - Combines the hexadecimal strings.
 * - Converts the combined hexadecimal string to a decimal value.
 * - Reads the error signal from the interferometer.
 *
 */
void readHeads() {
	Xuint32 first32bitsAxis1  = *(axis1_interferometer);
	Xuint32 last16bitsAxis1   = *(axis1_interferometer+1);
	displacementReadAxis1_hex = hexToStringWithLeadingZeros(last16bitsAxis1).substr(4, 4) +
								hexToStringWithLeadingZeros(first32bitsAxis1);
	displacementReadAxis1_decimal = hexToDecimal(displacementReadAxis1_hex);
	axis1_error_Signal            = *(axis1_interferometer+2);  // Error signal

	Xuint32 first32bitsAxis2  = *(axis2_interferometer);
	Xuint32 last16bitsAxis2   = *(axis2_interferometer+1);
	displacementReadAxis2_hex = hexToStringWithLeadingZeros(last16bitsAxis2).substr(4, 4) +
								hexToStringWithLeadingZeros(first32bitsAxis2);
	displacementReadAxis2_decimal = hexToDecimal(displacementReadAxis2_hex);
	axis2_error_Signal            = *(axis2_interferometer+2);  // Error signal
}

std::string getMachineStateName(MachineStates state) {
    switch (state) {
        case StandBy:
            return "StandBy";
        case OpenLoop:
            return "OpenLoop";
        case ClosingTheLoop:
            return "ClosingTheLoop";
        case OpeningTheLoop:
            return "OpeningTheLoop";
        case ClosedLoop:
            return "ClosedLoop";
        default:
            return "Unknown State";
    }
}

/**
 * @brief Updates the data to be sent to the GUI with the latest control and settings information.
 *
 * This function prepares and sends updated data for various tabs in the GUI. It gathers
 * control information, general settings, and control settings data, and updates the GUI
 * accordingly.
 *
 * @details
 * - Controls Tab: Updates control-related information including the yaw angle standard deviation.
 * - General Settings Tab: Updates general settings information.
 * - Control Settings Tab: Updates control-specific settings.
 *
 * @note This function should be called after `RTOneStep` to ensure that the data being sent
 * is up-to-date.
 */
void updateDataToSend() {
	//  Controls Tab informations
	GUIDataHandlerObj->setControlsData(getMachineStateName(goniometer_fw0_Y.machine_output.machine_state),
			                           goniometer_fw0_Y.yaw,
									   goniometer_fw0_Y.safety_output.warning_level,
									   loggingObj->computeStandardDeviationYawAngle(),
									   axis1_error_Signal,
									   axis2_error_Signal
									   );

	//  General settings Tab informations
	GUIDataHandlerObj->setGeneralSettingsData(
						   0.0f,
						   0.0f,
						   goniometer_fw0_Y.safety_output.warning_level,
						   0,
						   0.0f,
						   max_voltage_rate,
						   0.0f,
						   max_yaw_rate,
						   min_ctrl_variance,
						   max_ctrl_variance
						   );

	//  Control settings Tab
	GUIDataHandlerObj->setControlSettingsData(
											prefilter_num[0], prefilter_num[1], prefilter_num[2], prefilter_num[3],
											prefilter_den[0], prefilter_den[1],
											pid_num[0], pid_num[1], 0.0f, 0.0f,
											pid_den[0], pid_den[1],
											lead_filter_num[0], lead_filter_num[1],
											lead_filter_den[0],
											notch_filter_num[0], notch_filter_num[1],
											notch_filter_den[0],
						                     0,
						                     0.0f,
						                     0.0f, 0.0f,
						                     0.0f, 0.0f,
						                     0.0f, 0.0f
											 );
}

/* -- DAC functions -- */

/**
 * @brief Limits a number within specified thresholds.
 *
 * This function takes an input number and limits it within a specified range.
 * If the input number is less than -1.0, it is clamped to -1.0.
 * If the input number is greater than 7.5, it is clamped to 7.5.
 * If the input number falls within the range [-1.0, 7.5], it remains unchanged.
 *
 * @param number The input number to be clamped within the thresholds.
 * @return The clamped number, which is within the range [-1.0, 7.5].
 */
float isNumberWithinThresholds(float number) {
    if (number < -1.0f)  {
        return -1;
    } else if (number > 7.5f) {
        return 7.5;
    }
    else {
        return number;
    }
}

/**
 * @brief Calculate a data word based on input voltages.
 *
 * This function calculates a data word based on the given input voltages and a
 * specific formula.
 *
 * @param VRef_positive The positive reference voltage.
 * @param VRef_negative The negative reference voltage.
 * @param Vout The output voltage to be converted.
 *
 * @return The calculated data word as a 32-bit unsigned integer (uint32_t).
 */
uint32_t  calculateDataWord(float VRef_positive, float VRef_negative, float Vout) {
    uint32_t dataWord;
    Vout = isNumberWithinThresholds(Vout);
    dataWord = (262144 * (Vout - VRef_negative)) / (VRef_positive - VRef_negative);
    return dataWord;
}

/* -- Interrupt functions -- */

/* Functions */


void rt_OneStep(void);
void rt_OneStep(void) {
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(goniometer_fw0_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Read Inteferometric Heads */
  readHeads();

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set Sensor inputs here */
  goniometer_fw0_U.sensor_input.dist1 = goniometer_sim_Y.dist_1; //displacementReadAxis1_decimal;
  goniometer_fw0_U.sensor_input.dist2 = goniometer_sim_Y.dist_2; //displacementReadAxis2_decimal;
  goniometer_fw0_U.sensor_input.error1 = axis1_error_Signal;
  goniometer_fw0_U.sensor_input.error2 = axis2_error_Signal;
  /* Set User inputs here */
  goniometer_fw0_U.request_control_mode = GUIDataHandlerObj->getRequestControlMode();
  goniometer_fw0_U.request_start_motion = GUIDataHandlerObj->getRequestStartMotion();
  goniometer_fw0_U.request_stop_motion = GUIDataHandlerObj->getRequestStopMotion();
  goniometer_fw0_U.request_start_waveform = GUIDataHandlerObj->getRequestWaveform();
  goniometer_fw0_U.request_stop_waveform = GUIDataHandlerObj->getRequestStopWaveform();
  goniometer_fw0_U.request_warn_reset = GUIDataHandlerObj->getRequestWarnReset();
  goniometer_fw0_U.request_hyst_comp = 0;
  goniometer_fw0_U.voltage_ref = GUIDataHandlerObj->getVoltageRef();
  goniometer_fw0_U.yaw_ref = GUIDataHandlerObj->getYawRef();
  goniometer_fw0_U.waveform_number = GUIDataHandlerObj->getWaveformNumber();
  /* Expert Procedures Inputs */
  //goniometer_fw0_U.slope_ramp   = GUIDataHandlerObj->getRampRate();
  //goniometer_fw0_U.cycle_number = GUIDataHandlerObj->getNumberCycles();

  /**/
  goniometer_sim_U.control_output.voltage_cmd = goniometer_fw0_Y.control_output.voltage_cmd;

  /* General Settings Inputs */
  // GUIDataHandlerObj->getYawOffset();
  // GUIDataHandlerObj->getAAROffset();
  // goniometer_fw0_Y.safety_output.warning_level = GUIDataHandlerObj->getControlInstabilityProtection();
  // GUIDataHandlerObj->getMinVoltage();
  // GUIDataHandlerObj->getMaxVoltage();
  //max_voltage_rate = GUIDataHandlerObj->getOpenLoopMaxSpeed();
  //max_yaw_rate     = GUIDataHandlerObj->getClosedLoopMaxSpeed();
  //min_ctrl_variance = GUIDataHandlerObj->getMinPIDLimit();
  //max_ctrl_variance = GUIDataHandlerObj->getMaxPIDLimit();

  /* Control Settings Inputs
  prefilter_num[0] = GUIDataHandlerObj->getPrefilterNumerator(0);
  prefilter_num[1] = GUIDataHandlerObj->getPrefilterNumerator(1);
  prefilter_num[2] = GUIDataHandlerObj->getPrefilterNumerator(2);
  prefilter_num[3] = GUIDataHandlerObj->getPrefilterNumerator(3);
  prefilter_den[0] = GUIDataHandlerObj->getPrefilterDenominator(0);
  prefilter_den[1] = GUIDataHandlerObj->getPrefilterDenominator(1);
  pid_num[0]          = GUIDataHandlerObj->getFilter1Numerator(0);
  pid_num[1]       	  = GUIDataHandlerObj->getFilter1Numerator(1);
  pid_den[0]          = GUIDataHandlerObj->getFilter1Denominator(0);
  pid_den[1]          = GUIDataHandlerObj->getFilter1Denominator(1);
  lead_filter_num[0]  = GUIDataHandlerObj->getFilter2Numerator(0);
  lead_filter_num[1]  = GUIDataHandlerObj->getFilter2Numerator(1);
  lead_filter_den[0]  = GUIDataHandlerObj->getFilter2Denominator();
  notch_filter_num[0] = GUIDataHandlerObj->getFilter3Numerator(0);
  notch_filter_num[1] = GUIDataHandlerObj->getFilter3Numerator(1);
  notch_filter_den[0] = GUIDataHandlerObj->getFilter3Denominator();
  */

  /* Step the model */
  goniometer_fw0_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

void rt_OneStepSim(void);
void rt_OneStepSim(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(goniometer_sim_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  goniometer_sim_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/**
 * @brief Callback function for the timer interrupt.
 *
 * @param CallBackRef Reference to the callback context.
 */
static void TickHandler(void *CallBackRef) {
	/* START Calculating elapsed time in microseconds */
	XTime_GetTime(&end_time);
	/*----------------------------------------*/
	u32 StatusEvent;
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);

	/* Call Controller function */
	rt_OneStep();
	/* Call Simul Controller function */
	rt_OneStepSim();

	/* Process data flag */
	processDataFlag = true;

	/* STOP Calculating elapsed time in microseconds */
	uint64_t elapsed_ticks = end_time - start_time;
	uint32_t elapsed_micros = (elapsed_ticks * 1000000) / COUNTS_PER_SECOND;
	//std::cout << "Elapsed Micros         : " << elapsed_micros << std::endl;
	start_time = end_time;
	/*----------------------------------------*/
}

/**
 * @brief Sets up the interrupt system for the timer.
 *
 * This function initializes the timer, sets up options, calculates interval,
 * configures the interrupt controller, and enables interrupts.
 *
 * @param GicInstancePtr Pointer to the GIC (Generic Interrupt Controller) instance.
 * @param TtcPsInt Pointer to the timer instance.
 * @return Status of the setup operation. XST_SUCCESS on success, XST_FAILURE on failure.
 */
static int SetupInterruptSystem(XScuGic *GicInstancePtr, XTtcPs *TtcPsInt) {
	int status;
	XTtcPs_Config *Config;

	TmrCntrSetup *TimerSetup;

	TimerSetup = &SettingsTable[TTC_DEVICE_ID];

	XTtcPs_Stop(&Timer);

	/*
	 * Look up the configuration based on the device identifier
	 */
	Config = XTtcPs_LookupConfig(TTC_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	/*
	 * Initialize the device
	 */
	status = XTtcPs_CfgInitialize(&Timer, Config, Config->BaseAddress);
	if (status == XST_DEVICE_IS_STARTED) {
		XTtcPs_Stop(&Timer);
		status = XTtcPs_CfgInitialize(&Timer, Config, Config->BaseAddress);
	}

	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
							  XTTCPS_OPTION_WAVE_DISABLE);

	/*
	 * Set up appropriate options for Ticker: interval mode without
	 * waveform output.
	 */
	XTtcPs_SetOptions(&Timer, TimerSetup->Options);
	XTtcPs_CalcIntervalFromFreq(&Timer, TimerSetup->OutputHz, &(TimerSetup->Interval), &(TimerSetup->Prescaler));
	XTtcPs_SetInterval(&Timer, TimerSetup->Interval);
	XTtcPs_SetPrescaler(&Timer, TimerSetup->Prescaler);

	// --
	XScuGic_Config *IntcConfig; //GIC config
	Xil_ExceptionInit();

	//initialise the GIC
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);

	XScuGic_CfgInitialize(GicInstancePtr, IntcConfig,
					IntcConfig->CpuBaseAddress);

	//connect to the hardware
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
				GicInstancePtr);
	/*
	 * Connect to the interrupt controller
	 */
	status = XScuGic_Connect(GicInstancePtr, TTC_INTR_ID,
			(Xil_ExceptionHandler)TickHandler, (void *)TtcPsInt);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the Timer counter
	 */
	XScuGic_Enable(GicInstancePtr, TTC_INTR_ID);

	/*
	 * Enable the interrupts for the tick timer/counter.
	 */
	XTtcPs_EnableInterrupts(TtcPsInt, XTTCPS_IXR_INTERVAL_MASK);

	/*
	 * Start the tick timer/counter
	 */
	XTtcPs_Start(TtcPsInt);

	// Enable interrupts in the Processor.
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	return status;
}
