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

#include "help.h"

// +++++++++++++++++++++++++++++
// +++ define help text here +++
// +++++++++++++++++++++++++++++
#define _HELP_  "\n\rHelp for >BasicUart_1 (FreeSoC2)<:\n\r\th,H help\n\r"
#define _HELP1_ "\tL: LED on, l: LED off\n\r"
#define _HELP2_ "\tI: test empty loop int, i: test empty loop volatile int\n\r"
#define _HELP3_ "\tJ: test loop global int assignment, j: test loop local int assignment\n\r"

/**
 * Put help strings on output
 * @param funcPutString
 *        e.g. UART_UartPutString
 * @see http://www.lab4inf.fh-muenster.de/lab4inf/docs/Prog-in-C/11-Zeiger-auf-Funktionen.pdf
 * @see Fpp_t
 * @version 1.0
 * @author Ralf S. Mayer
 * @date 2017-03-06
 */
void prtHelp( Fpp_t funcPutString ) {
    #ifdef _HELP_
        funcPutString( _HELP_ );
    #endif //
    #ifdef _HELP1_
        funcPutString( _HELP1_ );
    #endif //
    #ifdef _HELP2_
        funcPutString( _HELP2_ );
    #endif //
    #ifdef _HELP3_
        funcPutString( _HELP3_ );
    #endif //
    #ifdef _HELP4_
        funcPutString( _HELP4_ );
    #endif // 
    #ifdef _HELP5_
        funcPutString( _HELP5_ );
    #endif // 
    #ifdef _HELP6_
        funcPutString( _HELP6_ );
    #endif // 
    #ifdef _HELP7_
        funcPutString( _HELP7_ );
    #endif // 
    #ifdef _HELP8_
        funcPutString( _HELP8_ );
    #endif // 
    #ifdef _HELP9_
        funcPutString( _HELP9_ );
    #endif // 
    #ifdef _HELP10_
        funcPutString( _HELP10_ );
    #endif // 
    #ifdef _HELP11_
        funcPutString( _HELP11_ );
    #endif // 
    #ifdef _HELP12_
        funcPutString( _HELP12_ );
    #endif // 
    // etc. for more _HELPn_
}

/* [] END OF FILE */
