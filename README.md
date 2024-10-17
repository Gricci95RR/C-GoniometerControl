# Piezo Goniometer Controller

## Overview

This repository contains a Vitis application designed to interface with an FPGA firmware controlling a piezo goniometer. Developed using **C++**, the application showcases advanced skills in **embedded systems**, **real-time data processing**, and effective communication with hardware. The project integrates robust data logging capabilities through the `Logging` class, which manages real-time logging and analysis, such as calculating the standard deviation of yaw angles, handling UART communication, and managing DAC control. 

Additionally, this project leverages **C++11** features, including **smart pointers** for better memory management and resource handling, enhancing the overall efficiency and safety of the application. Furthermore, **TCL scripting** was employed to streamline the code reconstruction process, enabling more efficient development and deployment on the FPGA.

## Features

- **C++11 Features**: Utilizes modern C++ features like smart pointers (`std::shared_ptr`) for efficient memory management and to prevent memory leaks.
- **UART Communication**: Efficient UART setup and data processing using the `setUpUART()` and `readUART()` functions to handle high-speed communication at 921600 baud.
- **Real-Time Data Logging**: A custom-developed `Logging` class enables the storage and analysis of yaw angle data. It calculates metrics like **mean** and **standard deviation**, logs data in a structured format, and supports JSON output for easy integration with external systems.
- **Interferometer Data Processing**: Handles displacement and error signal readings from interferometers, converting them from hexadecimal to decimal and binary formats using `hexToBinary()`, `hexToDecimal()`, and `readHeads()`.
- **Interrupt-Driven Control**: The system ensures real-time performance with efficient interrupt handling for time-sensitive tasks, managed through the `SetupInterruptSystem()` and `TickHandler()` functions.
- **Modular Design**: The project is structured into independent modules (`utils.hpp`, `logging.hpp`, and `GUIDataHandler.hpp`), ensuring maintainability and scalability for future development.
- **DAC Calculation**: Controls DAC output with precision, ensuring signals remain within safe limits using custom calculation functions like `calculateDataWord()`.
- **TCL Scripting**: Utilizes TCL scripts to automate and streamline the code reconstruction process, facilitating efficient deployment and management of FPGA firmware.

## Key Components

### 1. Main Application

The main application (`main_PiezoGoniometerController.cpp`) initializes the platform, sets up UART, and manages real-time data processing through the integration of the `Logging` class and other utilities developed in `utils.hpp`.

```cpp
int main() {
    init_platform();
    uart = setUpUART();
    goniometer_sim_initialize();
    goniometer_fw0_initialize();

    if (SetupInterruptSystem(&Intc, &Timer) != XST_SUCCESS) {
        xil_printf("SetupInterruptSystem failed\r\n");
        return XST_FAILURE;
    }

    while (1) {
        if (processDataFlag) {
            updateDataToSend();
            readUART(&uart);
            loggingObj->addElement(goniometer_fw0_Y.yaw);
            loggingObj->logData(0.1, 0.3, 10);

            if (!loggingObj->getStartLogging()) {
                if (counter == divider) {
                    std::cout << GUIDataHandlerObj->serializeControlsData() << std::endl;
                    counter = 0;
                } else {
                    counter++;
                }
            }

            processDataFlag = false;
        }
    }
    return 0;
}
```

### 2. `utils.hpp`: Core Utility Functions

The `utils.hpp` file contains various utilities to handle UART communication, interferometer data, and DAC control:

- **Interferometer Data Handling**: `readHeads()` reads displacement and error signals, converting hexadecimal data to a usable decimal format.
- **DAC Control**: `calculateDataWord()` computes the correct data word for DAC output, ensuring the voltage remains within safe limits.

### 3. `logging.hpp`: Real-Time Data Logging

The `Logging` class is central to the application’s data logging and analysis functionality. It logs yaw angle data, computes key statistics (mean and standard deviation), and outputs the data in a structured format, enabling integration with graphical user interfaces or external monitoring systems.

#### Key Methods:
- **addElement()**: Adds new yaw angle data to the buffer, ensuring the buffer remains within the specified size.
- **logData()**: Logs yaw angle and output voltage data for a specified duration, outputting the data in JSON format.
- **computeStandardDeviationYawAngle()**: Computes the standard deviation of yaw angles stored in the buffer, offering insights into system performance.
- **computeMean()**: Calculates the mean of yaw angles stored in the buffer.

### 4. Interrupt-Driven Architecture

The interrupt-driven architecture ensures timely response to hardware events, enabling real-time control of the goniometer. The `SetupInterruptSystem()` function configures the interrupt controller and timer, while the `TickHandler()` function handles interrupt events, allowing the system to process data during each interrupt cycle.

```cpp
static void TickHandler(void *CallBackRef) {
    XTime_GetTime(&end_time);
    XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef));

    rt_OneStep();   // Perform controller step
    rt_OneStepSim(); // Perform simulation step

    processDataFlag = true;

    uint64_t elapsed_ticks = end_time - start_time;
    uint32_t elapsed_micros = (elapsed_ticks * 1000000) / COUNTS_PER_SECOND;
    start_time = end_time;
}
```

## Development Tools

- **Xilinx Vitis IDE**: Used for developing, debugging, and deploying the application on FPGA platforms.
- **FPGA Hardware**: Targeted for Xilinx FPGAs, optimized for real-time control and data processing.
- **C++**: Core programming language used to implement all utilities and application logic, incorporating **C++11** features like smart pointers.
- **Interrupt-driven Programming**: Critical for real-time applications, ensuring immediate handling of hardware events.
- **TCL Scripting**: Utilized for efficient code reconstruction, automating deployment processes, and managing FPGA firmware.

## Author

**Gianmarco Ricci**  
