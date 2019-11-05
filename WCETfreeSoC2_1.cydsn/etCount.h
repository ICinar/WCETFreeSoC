/* ========================================
 *
 * Copyright Ralf S. Mayer, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#ifndef _ETCOUNT_H_
#define _ETCOUNT_H_

#include <project.h>        // include project context

#define CNT_ENABLE_SHIFT    (0)         //!< bit shift in Control_Reg for counter enable
#define CNT_RESET_SHIFT     (1)         //!< bit shift in Control_Reg for counter reset
#define CNT_ENABLE_NORESET  (1 << CNT_ENABLE_SHIFT) //!< counter enable, noreset
#define CNT_DISABLE_NORESET (0)         //!< counter disable, noreset
#define CNT_DISABLE_RESET   (1 << CNT_RESET_SHIFT)  //!< counter disable, reset

//static uint16 cntSts = 0;               //!< value from Status_Reg(ister), i.e. counter value
#define STS_LO_MASK         (0x00FF)    //!< mask for counter status low byte
#define STS_HI_MASK         (0xFF00)    //!< mask for counter status high byte
#define STS_HI_SHIFT        (8)         //!< shift for counter status high byte
//#define SET_STS_LO(u)       cntSts |= STS_LO_MASK & u;  //!< get counter low byte
//#define SET_STS_HI(o)       cntSts |= STS_HI_MASK & (o << STS_HI_SHIFT); //!< get counter hi byte

/**
 * \def GET_COUNTER
 * Get status of counter realized in PSoC
 * @param var uint16 variable to get counter value 2 bytes
 * @param u low byte
 * @param o high byte
 * @return val
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define GET_COUNTER(var, u, o) var = (STS_LO_MASK & u) | (STS_HI_MASK & (o << STS_HI_SHIFT))
    
/**
 * \def CNT_START_RES
 * Reset and start counter realized in PSoC.
 * @see Control_Reg_Write
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define CNT_START_RES       Control_Reg_Write( CNT_DISABLE_RESET ); \
                            Control_Reg_Write( CNT_ENABLE_NORESET ) 
    
/**
 * \def CNT_RESTART
 * Restart counter realized in PSoC without reset
 * @see Control_Reg_Write
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define CNT_RESTART         Control_Reg_Write( CNT_ENABLE_NORESET )
    
/**
 * \def CNT_STOP
 * Stop counter realized in PSoC without reset
 * @see Control_Reg_Write
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define CNT_STOP            Control_Reg_Write( CNT_DISABLE_NORESET )
    
/**
 * \def CNT_LAP
 * Stop and get lap of counter realized in PSoC with restart after reading
 * @param var uint16 variable to get counter value 2 bytes
 * @return val 
 * @see Control_Reg_Write
 * @see GET_COUNTER
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define CNT_LAP(var)        Control_Reg_Write( CNT_DISABLE_NORESET ); \
                            GET_COUNTER(var, StatusReg_0_Read(), StatusReg_1_Read() ); \
                            CNT_RESTART
    
/**
 * \def CNT_LAP_STOP
 * Get lap of counter realized in PSoC. Counter remains stopped after reading
 * @param var uint16 variable to get counter value 2 bytes
 * @return val 
 * @see Control_Reg_Write
 * @see GET_COUNTER
 * @author Ralf S. Mayer
 * @date 2018-04-27
 */
#define CNT_LAP_STOP(var)   Control_Reg_Write( CNT_DISABLE_NORESET ); \
                            GET_COUNTER(var, StatusReg_0_Read(), StatusReg_1_Read() );
 

#endif // _ETCOUNT_H_
/* [] END OF FILE */
