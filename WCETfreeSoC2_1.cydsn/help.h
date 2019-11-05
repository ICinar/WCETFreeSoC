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
/**
 * Signature of the project
 * @author Ralf S. Mayer
 * @version 1.0
 * @date 2017-03-05
 */

#ifndef _HELP_H_
#define _HELP_H_
    
/**
* Declare a Function with const char* as Parameter and void as return.
*/
typedef void(*Fpp_t)(const char*);

/** @brief Print Help */
void prtHelp( Fpp_t funcPutString );
//    /** @brief Print Help */
//    void printHelp( void(*fpp)(const char*) );
    
#endif // _HELP_H_

/* [] END OF FILE */
