/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RNWF_INTERFACE_H
#define	RNWF_INTERFACE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "../../uart/uart_drv_interface.h"


typedef enum
{   
    RNWF_FAIL =  0,
    RNWF_PASS =  1,
    RNWF_BUSY = -1,   
    RNWF_TIMEOUT = -2,                   
}RNWF_RESULT_t;

typedef enum
{           
    RNWF_INTERFACE_FREE,
    RNWF_INTERFACE_BUSY
}RNWF_INTERFACE_STATE_t;

extern const uart_drv_interface_t UART0;

// TODO Insert appropriate #include <>

#define RNWF_INTERFACE_LEN_MAX    2048

extern RNWF_INTERFACE_STATE_t   g_interface_state;


// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations
#define RNWF_INTERFACE_TIMEOUT      1

#define RNWF_INTERFACE_DEBUG        1

#define RNWF_IS_INTERFACE_BUSY()      if(g_interface_state == RNWF_INTERFACE_BUSY)return RNWF_INTERFACE_BUSY;
#define RNWF_SET_INTERFACE_BUSY()     (g_interface_state = RNWF_INTERFACE_BUSY)             
#define RNWF_SET_INTERFACE_FREE()     (g_interface_state = RNWF_INTERFACE_FREE)         


#define RNWF_AT_CMD     "AT"
#define RNWF_AT_EOL     "\r\n"
#define RNWF_AT_DONE    "OK"
#define RNWF_AT_ERROR     "ERROR"


#define RNWF_ARG_DELIMETER          ":"

/*  Wi-Fi Event Code*/
#define RNWF_EVENT_AUTO_IP        "+WSTAAIP:"
#define RNWF_EVENT_LINK_UP        "+WSTALU:"
#define RNWF_EVENT_LINK_LOSS      "+WSTALD:"
#define RNWF_EVENT_ERROR          "+WSTAERR:"

/*  SCAN Event Code*/
#define RNWF_EVENT_SCAN_IND       "+WSCNIND:"
#define RNWF_EVENT_SCAN_DONE      "+WSCNDONE:"

/*  DHCP Event Code*/
#define RNWF_EVENT_DHCP_CFG       "+DHCPSC:"

/*  DNS Event Code */
#define RNWF_EVENT_DNS_RESOLVE    "+DNSRESOLV:"
#define RNWF_EVENT_DNS_ERROR      "+DNSERR:"

/*  INFO Event Code */
#define RNWF_EVENT_INFO           "+INFO:"

/* SOCKET Event Code */
#define RNWF_EVENT_SOCK_CONNECTED   "+SOCKIND:"
#define RNWF_EVENT_SOCK_TCP_RECV    "+SOCKRXT:"
#define RNWF_EVENT_SOCK_UDP_RECV    "+SOCKRXU:"
#define RNWF_EVENT_SOCK_CLOSE       "+SOCKCL:"
#define RNWF_EVENT_SOCK_TLS_SUCCESS "+SOCKTLS:"
#define RNWF_EVENT_SOCK_ERROR       "+SOCKERR:"


// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation


RNWF_RESULT_t RNWF_CMD_RSP_Send(const char *delimeter, uint8_t *response, const char *format, ...);

RNWF_RESULT_t rnwf_interface_print(const char *format, ...);
RNWF_RESULT_t rnwf_interface_write(uint8_t *buffer, uint16_t length);
RNWF_RESULT_t rnwf_interface_read(uint8_t *buffer, uint16_t length);
uint8_t *rnwf_interface_parse(uint8_t *buffer, uint8_t length);
RNWF_RESULT_t RNWF_RESP_Wait(const char *rsp_str, uint8_t *buffer);


RNWF_RESULT_t RNWF_EVENT_Handler(void);
RNWF_RESULT_t RNWF_IF_SW_Reset(void);

#define RNWF_IF_RAW_WRITE           rnwf_interface_write
#define RNWF_IF_WRITE               rnwf_interface_print
#define RNWF_IF_READ()              rnwf_interface_read(g_interface_recv_buffer, RNWF_INTERFACE_LEN_MAX)
#define RNWF_IF_PARSE(len)          rnwf_interface_parse(g_interface_recv_buffer, len)
#define RNWF_IF_RSP_WAIT            RNWF_RESP_Wait  
#define RNWF_IF_CMD_WAIT()          RNWF_RESP_Wait(RNWF_AT_DONE, (uint8_t *)NULL)


#define RNWF_IF_SEND_WAIT(CMD)       rnwf_interface_print(CMD); \
                                    return RNWF_RESP_Wait(RNWF_AT_DONE, (uint8_t *)NULL)
                                    

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* RNWF_INTERFACE_H */

