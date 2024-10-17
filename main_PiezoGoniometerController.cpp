/**
 * @file main_PiezoGoniometerController.c
 * @author Gianmarco Ricci CERN BE/CEM/MRO 2024
 * @brief Main program entry point for the application.
 *
 * In particular, configures ps7_uart to baud rate 921600 and sets up the interrupt system and timer.
 *
 * @version 0.1
 * @date 05/02/2024
 * 
 * @copyright Ãƒâ€šÃ‚Â© Copyright CERN 2018. All rights reserved. This software is released under a CERN proprietary software license.
 * Any permission to use it shall be granted in writing. Requests shall be addressed to CERN through mail-KT@cern.ch
 * 
 */

#include <stdio.h>
#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h"
#include "sleep.h"
#include <iostream>
#include <thread>

#include "utils.hpp"


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

			/* Data to send */
			updateDataToSend();
			/* Read Uart */
    		readUART(&uart);
    		/* Update logging */
			loggingObj->addElement(goniometer_fw0_Y.yaw);
			loggingObj->logData(0.1, 0.3, 10);
			/* Logging and output handling */
			if (!loggingObj->getStartLogging()) {
				if (counter == divider) {
					// Print the serialized data only when required
					//std::cout << displacementReadAxis1_decimal << std::endl;
					//std::cout << displacementReadAxis2_decimal << std::endl;
					std::cout << GUIDataHandlerObj->serializeControlsData() << std::endl;
					//std::cout << GUIDataHandlerObj->serializeGeneralSettingsData() << std::endl;
					//std::cout << GUIDataHandlerObj->serializeControlSettingsData() << std::endl;
					counter = 0;
				} else {
					counter++;
				}
			}
			/* Reset Flag */
			processDataFlag = false;
    	}

    }
    return 0;
}
