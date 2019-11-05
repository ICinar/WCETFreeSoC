/* ========================================
 *
 * Copyright Ralf S. Mayer, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include <string.h>     // eg. strtok
#include <stdlib.h>     // eg. atoi, atol, atof
#include <unistd.h>
// own includes
#include "swsign.h"
#include "help.h"
#include "etCount.h"    // execution time counter

int gj;                 // a global var

/**
 * Control the User LED on board
 * @param sts 0: off, 1: on
 */
inline void usrLED( uint8 sts ) {
    Pin_USR_LED_Write( sts );
}

/**
 * \def USERLED_ONOFF
 * switch user LED on or off
 * @param x  1: on, 0: off
 */
#define USERLED_ONOFF(x) ( Pin_USR_LED_Write(x) )

// +++ globals +++
char buffer[128];       //!< buffer (global) for sprintf
uint8 _verboseFlag = 1; //!< verbosity flag

uint8 flagUART_RX = 0;          //!< flag (global) itr has occured
static char cRx = 0;            //!< caharcter from UART, visible within main.c

/** 
 * UART RX interrupt service routine.
 *
 * Collect a characters from UART into a global input variable.
 * @see cRx
 */
CY_ISR( MyIsrUartRX ) {
    cRx = UART_GetChar();     // copy char
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++   Candidates for new include and implementation file   ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ------------------------------------------------------------------------------------

/**
 * Basic project with UART, RX-Interrupt, user-Button and -LED. With HW realization
 * of execution time counter. See the TopDesign and the macros in etCount.h
 * for FreeSoC2-5LP
 * 
 * Help and diverse functionalities
 * @see help.c
 *
 * @author Ralf S. Mayer
 * @date 2018-04-27
 * @version 1.1
 */
int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */   
    UART_Start();                       // start UART
    isr_UART_RX_StartEx( MyIsrUartRX ); // enable itr uart
    
    
    // +++ Initialize Counter and Registers +++
    Control_Reg_Write( CNT_DISABLE_RESET );  // reset, disable
    uint16 cnt, cnt1, cnt2,cnt3, cnt4;       // counter values
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    sprintf( buffer, "\n\rWelcome! %s\n\r", _VERSTR_);
    UART_PutString( buffer );
    // help text
    prtHelp( UART_PutString );
        
    // +++ Test the execution time counter +++
    CNT_START_RES;      // reset and start counter
    CNT_LAP( cnt );     // get counter value
    CyDelay(1);         // test delay in ms
    CNT_LAP( cnt1 );    // get counter value
    CyDelay(2);         // test delay in ms
    CNT_LAP( cnt2 );    // get counter value
    CyDelay(5);         // test delay in ms
    CNT_LAP( cnt3 );    // get counter value
    CyDelay(10);        // test delay in ms
    CNT_LAP_STOP( cnt4 );   // get counter value, stop counter
    CNT_START_RES;      // reset and start counter
    sprintf( buffer, "Delay 0, 1, 2, 5, 10ms: %d, %d, %d, %d, %d\n\r",
        cnt, cnt1, cnt2, cnt3, cnt4 );
    UART_PutString( buffer );
    CNT_LAP_STOP( cnt );   // get counter value, stop counter
    sprintf( buffer, "Time for 'printf' %d\n\r", cnt );
    UART_PutString( buffer );
    // --- End Test the execution time counter ---
    
    char cInput = 0;        // UART RX char copy
    int i;
    volatile int vi;
    int lj;                 // a lokal var
    
    // Main loop
    for(;;)     // forever
    {
        /* Place your application code here. */
        // uart char received?
        if ( cRx != 0 ) {           // char received
            isr_UART_RX_Disable();  // disable Itr
            cInput = cRx;           // copy char
            cRx = 0;                // reset
            isr_UART_RX_Enable();   // enable Itr
        }

        if ( cInput != 0 ) {        // has input
            switch ( cInput ) {     // handle input
                case 'h':
                case 'H':
                    prtHelp( UART_PutString );
                    break;
                    
                case 'L':
                    usrLED( 1u );   // on
                    break;
                case 'l':
                    usrLED( 0u );   // off
                    break;
                    
                case 'I':
                    CNT_START_RES;  // reset counter
                    for ( i = 0; i < 10000; i++ );
                    CNT_LAP_STOP( cnt );   // get counter value, stop counter
                    sprintf( buffer, "Time for loop i 0...10000: %d\n\r", cnt );
                    UART_PutString( buffer );
                    break;
                case 'i':
                    CNT_START_RES;  // reset counter
                    for ( vi = 0; vi < 10000; vi++ );
                    CNT_LAP_STOP( cnt );   // get counter value, stop counter
                    sprintf( buffer, "Time for loop vi 0...10000: %d\n\r", cnt );
                    UART_PutString( buffer );
                    break;
                case 'J':
                    CNT_START_RES;  // reset counter
                    for ( i = 0; i < 10000; i++ ) {
                        gj = i;
                    }
                    CNT_LAP_STOP( cnt );   // get counter value, stop counter
                    sprintf( buffer, "Time for loop global=i 0...10000: %d\n\r", cnt );
                    UART_PutString( buffer );
                    break;
                case 'j':
                    CNT_START_RES;  // reset counter
                    for ( i = 0; i < 10000; i++ ) {
                        lj = i;
                    }
                    CNT_LAP_STOP( cnt );   // get counter value, stop counter
                    sprintf( buffer, "Time for loop local=i 0...10000: %d\n\r", cnt );
                    UART_PutString( buffer );
                    break;
                    
                default:    // repeat char
                    UART_PutChar( cInput );
                    break;
            } // end switch
            cInput = 0;             // reset, don't forget!
        }
        
        // for Test Only!
        if ( !Pin_USR_SW1_Read() ) { // Button pressed
            usrLED( 1u );   // on
            CyDelay( 50 );
            usrLED( 0u );   // off          
        }
            
    } // end for ever
} // end main

/* [] END OF FILE */
