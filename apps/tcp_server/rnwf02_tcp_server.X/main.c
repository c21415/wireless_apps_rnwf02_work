 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdarg.h>

#include "mcc_generated_files/system/system.h"

#include "mcc_generated_files/library/rnwf02/rnwf_interface.h"
#include "mcc_generated_files/library/rnwf02/rnwf_wifi_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_net_service.h"
#include "mcc_generated_files/library/rnwf02/rnwf_utility_service.h"


/*
    Main application
*/


int main(void)
{
    uint8_t man_id[32];
    
    SYSTEM_Initialize();

    printf("%s", "##################################\n");
    printf("%s", "  Welcome RNWF02 TCP Server Demo  \n");
    printf("%s", "##################################\n");

    RNWF_IF_SW_Reset();
    
    RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_MAC_ID, man_id);
    //RNWF_UTILITY_SrvCtrl(RNWF_UTILITY_RESET, NULL);
            
    RNWF_WIFI_STA_PARAM_t wifi_sta_cfg = {"wsn", "brucenegley", RNWF_WPA2_MIXED};
    
    //RNWF_WIFI_SysCtrl(RNWF_WIFI_PASSIVE_SCAN, NULL);
    
    RNWF_WIFI_SysCtrl(RNWF_STA_DISCONNECT, NULL);        
    
    //printf("Disconnect -> %d", RNWF_WIFI_SysCtrl(RNWF_STA_DISCONNECT, NULL));
    
    RNWF_WIFI_SysCtrl(RNWF_STA_SET_PARAMS, &wifi_sta_cfg);
    
    RNWF_WIFI_SysCtrl(RNWF_STA_CONNECT, NULL);
    
    while(1)
    {
        
        
        RNWF_CMD_RSP_Send(NULL, NULL, NULL);
    }    
}