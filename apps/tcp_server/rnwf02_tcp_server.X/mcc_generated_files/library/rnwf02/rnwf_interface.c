/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "rnwf_interface.h"
#include "rnwf_wifi_service.h"
#include "rnwf_net_service.h"
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
RNWF_INTERFACE_STATE_t   g_interface_state = RNWF_INTERFACE_FREE;

uint8_t g_interface_send_buffer[RNWF_INTERFACE_LEN_MAX];
uint8_t g_interface_recv_buffer[RNWF_INTERFACE_LEN_MAX];

uint8_t g_if_buffer[RNWF_INTERFACE_LEN_MAX];

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
int global_data;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */


/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */

void rnwf_interface_async_handler(uint8_t *p_msg, uint32_t len)
{      
    
    if(strstr((char *)p_msg, RNWF_EVENT_AUTO_IP))
    {
        printf("IP Address %s\r\n", p_msg+13);
        RNWF_NET_SOCKET_t tcp_server_socket = {
        .bind_type = RNWF_BIND_LOCAL,
        .sock_port = 6666,
        .sock_type = RNWF_SOCK_TCP,
        };

        RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &tcp_server_socket);
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_DHCP_DONE, p_msg+13);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_LOSS))
    {
        printf("STA link Loss %s\r\n", p_msg+8);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_UP))
    {
        printf("STA link Up %s\r\n", p_msg+11);        
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_ERROR))
    {
        printf("STA Connect fail %s\r\n", p_msg+11);
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_IND))
    {
        printf("%s\r\n", p_msg+11);
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_DONE))
    {     
        printf("%s\r\n", p_msg+9);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DHCP_CFG))
    {
        printf("DHCP Configuration\r\n");
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DNS_RESOLVE))
    {
        printf("DNS Resolution\r\n");
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DNS_ERROR))
    {
        printf("DNS Error \r\n");
        
    }
    
    if(strstr((char *)p_msg, RNWF_EVENT_INFO))        
    {
        printf("Task Info");
    }
    
    
}

RNWF_RESULT_t rnwf_interface_write(uint8_t *buffer, uint16_t length)
{                           
    while(length)
    {
        if(UART0.IsTxReady()) 
        {
            UART0.Write(*buffer++); 
            length--;
        }
    }      
    return RNWF_PASS;    
}

RNWF_RESULT_t rnwf_interface_print(const char *format, ...)
{    
    uint8_t *p_frame = g_interface_send_buffer;
    size_t len;
    va_list args = {0};   
    //memset(g_interface_send_buffer, 0, RNWF_INTERFACE_LEN_MAX);
    /* Get the variable arguments in va_list */
    va_start( args, format );                  
    len = vsnprintf((char *)g_interface_send_buffer, RNWF_INTERFACE_LEN_MAX, format, args);        
    va_end(args); 
    printf("cmd[%d] -> %s", len, p_frame);
        
    while(*p_frame != '\0')
    {
        if(UART0.IsTxReady()) 
        {
            UART0.Write(*p_frame++); 
            while(!UART0.IsTxDone());
        }
    }
    
    
    
    
    
    
    return RNWF_PASS;    
}


/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
RNWF_RESULT_t rnwf_interface_read(uint8_t *buffer, uint16_t length)
{
    RNWF_RESULT_t result = RNWF_FAIL;
    memset(buffer, 0, length);    
    
    RNWF_SET_INTERFACE_BUSY();
    while(RNWF_INTERFACE_TIMEOUT) //later make it timeout
    {        
        if(UART0.IsRxReady())
        {              
            if(strstr((char *)buffer, "\r\n"))
            {           
                printf("rsp[%d] <- %s", result, buffer);
                break;                
            }            
            if(result < length)
            {
                buffer[result++] = UART0.Read();                  
            }
            else
            {
                //truncate the buffer till '\r\n'            
                buffer[result-2] = buffer[result-1];
                result = result-1;    //
            }            
        }
    }        
    RNWF_SET_INTERFACE_FREE();
    return result;
    
}


uint8_t *rnwf_interface_parse(uint8_t *buffer, uint8_t length)
{
    //if(buffer[0] == '\r')
    buffer[length-2] = '\0'; 
    if(strstr((char *)buffer, "\r+"))
    {    
        rnwf_interface_async_handler(buffer, length); 
        return NULL;
    }      
    
    return buffer;
}


RNWF_RESULT_t RNWF_IF_SW_Reset(void)
{    
    
    return RNWF_CMD_RSP_Send(NULL, NULL, "\r\n", NULL);
    //uint8_t dummy_buffer[0x30] = {'\r', '\n', '\0'};
    //rnwf_interface_write(dummy_buffer, 2);        
    //rnwf_interface_read(dummy_buffer, 0x30);  
    //return RNWF_PASS;
}


RNWF_RESULT_t RNWF_EVENT_Handler(void)
{    
    RNWF_IF_PARSE(RNWF_IF_READ()); 
    return RNWF_PASS;
}


RNWF_RESULT_t RNWF_RESP_Wait(const char *rsp_str, uint8_t *buffer)
{
    uint8_t *p_rsp;
    do
    {
        if((p_rsp = RNWF_IF_PARSE(RNWF_IF_READ())) != NULL)            
        {                               
            if(strstr((char *)p_rsp, RNWF_AT_CMD))
            {                             
                continue;
            }
            if(strstr((char *)p_rsp, rsp_str))
            {                           
                if(buffer != NULL)
                {                    
                    strcpy((char *)buffer, (char *)p_rsp+strlen(rsp_str));
                }
            }
            if(strstr((char *)p_rsp, RNWF_AT_ERROR))
            {                
                return RNWF_FAIL;
            }
        }  
    }
    while(1);//timeout  
    return RNWF_TIMEOUT;    
}

RNWF_NET_SOCKET_t tcp_server_socket = {
        .bind_type = RNWF_BIND_LOCAL,
        .sock_port = 6666,
        .sock_type = RNWF_SOCK_TCP,
        };

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

void RNWF_IF_ASYNC_Handler(uint8_t *p_msg)
{    
    uint16_t arg_len = 0;
    char *p_arg = (char *)(strstr((char *)p_msg, RNWF_ARG_DELIMETER) + 1);
    while(p_arg[arg_len] != '\0')
    {
        (p_arg[arg_len] == ',') ? p_arg[arg_len++] = ' ':arg_len++;        
    }
    printf("Async Arguments-> %s\n", p_arg);
    
    if(strstr((char *)p_msg, RNWF_EVENT_SOCK_CONNECTED))
    {        
        sscanf((char *)p_arg, "%s %*s", tcp_server_socket.sock_client); 
        printf("remote_socket = %s", tcp_server_socket.sock_client);
    }
    
    if(strstr((char *)p_msg, RNWF_EVENT_SOCK_TCP_RECV))
    {
        uint16_t rx_len = 0;   
        uint16_t rx_offset;
        uint8_t rx_data[128]; 
        sscanf((char *)p_arg, "%*d %d", &rx_len); 
        rx_offset = RNWF_NET_SOCK_Read(&tcp_server_socket, rx_len, rx_data, RNWF_ASCII_MODE);
        if(rx_offset)
        {            
            RNWF_NET_SOCK_Write(&tcp_server_socket, rx_len, &rx_data[rx_offset]);
        }
    }
    if(strstr((char *)p_msg, RNWF_EVENT_AUTO_IP))
    {
        printf("IP Address %s\r\n", p_msg+13);
        

        RNWF_NET_SOCK_SrvCtrl(RNWF_NET_SOCK_TCP_OPEN, &tcp_server_socket);
        if(gWifi_CallBack_Handler)
            gWifi_CallBack_Handler(RNWF_DHCP_DONE, p_msg+13);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_LOSS))
    {
        printf("STA link Loss %s\r\n", p_msg+8);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_LINK_UP))
    {
        printf("STA link Up %s\r\n", p_msg+11);        
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_ERROR))
    {
        printf("STA Connect fail %s\r\n", p_msg+11);
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_IND))
    {
        printf("%s\r\n", p_msg+11);
    }
    if(strstr((char *)p_msg, RNWF_EVENT_SCAN_DONE))
    {     
        printf("%s\r\n", p_msg+9);
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DHCP_CFG))
    {
        printf("DHCP Configuration\r\n");
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DNS_RESOLVE))
    {
        printf("DNS Resolution\r\n");
        
    }
    if(strstr((char *)p_msg, RNWF_EVENT_DNS_ERROR))
    {
        printf("DNS Error \r\n");
        
    }
    
    if(strstr((char *)p_msg, RNWF_EVENT_INFO))        
    {
        printf("Task Info");
    }
}



/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
RNWF_RESULT_t RNWF_CMD_RSP_Send(const char *delimeter, uint8_t *response, const char *format, ...)
{
    uint8_t *p_frame = g_if_buffer;
    RNWF_RESULT_t result = RNWF_FAIL;
    size_t cmd_len, rsp_len = 0;
    va_list args = {0};   
    //memset(g_interface_send_buffer, 0, RNWF_INTERFACE_LEN_MAX);
    /* Get the variable arguments in va_list */
    
    if(format != NULL)
    {
        RNWF_IS_INTERFACE_BUSY();

        va_start( args, format );                  
        cmd_len = vsnprintf((char *)g_if_buffer, RNWF_INTERFACE_LEN_MAX, format, args);        
        va_end(args); 
#ifdef RNWF_INTERFACE_DEBUG        
        printf("cmd[%d] -> %s", cmd_len, p_frame);
#endif /* RNWF_INTERFACE_DEBUG */        

        while(*p_frame != '\0')
        {
            if(UART0.IsTxReady()) 
            {
                UART0.Write(*p_frame++); 
                while(!UART0.IsTxDone());
            }
        }
        memset(g_if_buffer, 0, cmd_len);
    }
    
        
    while(RNWF_INTERFACE_TIMEOUT) //later make it timeout
    {        
        if(UART0.IsRxReady())
        {              
            if(strstr((char *)g_if_buffer, "\r\n"))
            {           
#ifdef RNWF_INTERFACE_DEBUG       
                printf("rsp[%d] <- %.*s", rsp_len, rsp_len, g_if_buffer);
#endif /* RNWF_INTERFACE_DEBUG */                     
                g_if_buffer[rsp_len-2] = '\0';  
                g_if_buffer[rsp_len-1] = '\0';  
                if(strstr((char *)g_if_buffer, "\r+"))
                {    
                    RNWF_SET_INTERFACE_FREE();
                    RNWF_IF_ASYNC_Handler(g_if_buffer); 
                    RNWF_SET_INTERFACE_BUSY();                    
                }                 
                else if(delimeter != NULL && strstr((char *)g_if_buffer, delimeter))
                {
                    if(response != NULL)
                    {                    
                        strcpy((char *)response, (char *)g_if_buffer+strlen(delimeter));
                    }
                }
                else if(strstr((char *)g_if_buffer, RNWF_AT_ERROR))
                {
                    if(response != NULL)
                    {                    
                        strcpy((char *)response, (char *)g_if_buffer+strlen(RNWF_AT_ERROR));
                    }
                    result = RNWF_FAIL;
                    break;
                }
                else if(strstr((char *)g_if_buffer, RNWF_AT_DONE))
                {
                    result = RNWF_PASS;
                    break;                    
                }                                
                rsp_len = 0;
            }            
            else 
            {                
                if(rsp_len < RNWF_INTERFACE_LEN_MAX)
                {
                    g_if_buffer[rsp_len++] = UART0.Read();                  
                }
                else
                {
                    //truncate the buffer till '\r\n'            
                    g_if_buffer[rsp_len-2] = g_if_buffer[rsp_len-1];
                    rsp_len = rsp_len-1;    //
                }
            }            
        }
    }                
    
    RNWF_SET_INTERFACE_FREE();
    
    return result;
    
    
}

/* *****************************************************************************
 End of File
 */
