/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

//-- librairie standard --// 
#include <stdbool.h>

//-- libraiire system --// 
#include "peripheral/ports/plib_ports.h"

//-- librairie BSP --// 
#include "Mc32DriverLcd.h"      //--> LCD 
#include "Mc32Delays.h"         //--> delay 

//-- librairie autres 
#include "app.h"




// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void CallBackTimer1()
{
    //-- deux approches pour les changement d'état --//  
    //- 1 => changement de la machine d'état dans le call back -> 
    //       solution acceptable, mais non optimale
    if(appData.state == APP_STATE_WAIT)
    {
        appData.state = APP_STATE_SERVICE_TASKS; 
    }
    
    //- 2 => gestion  des flack dans le callBack 
    appData.tmr1EvtHasOcurred = true;
    
}



/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    
    //-- initialisation LCD --// 
    lcd_init(); 
    
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks (void)
{
    //-- déclaration variables --// 
    bool appInitialized = false;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //-- backlight ON --// 
            lcd_bl_on();
            
            //-- msg user --// 
            printf_lcd("DEMO SLO 25-26");
            
            //-- MAJ du flag d'initialisation --// 
            appInitialized = true; 
            
            if (appInitialized == true)
            {
                //-- remettre le flag à zéro (false)
                appInitialized = false; 
                
                //-- MAJ de la machine d'état --// 
                appData.state = APP_STATE_SERVICE_TASKS; 
            }
            break;
        }

        
        case APP_STATE_SERVICE_TASKS:
        {
            //-- partie 2 
            //-- algo - faire clignoter une leds toutes les 100ms via timer 1 
            BSP_LEDToggle(BSP_LED_6); 
            
            //-- partie 1 
            //-- algo faire clignoter une led sur 100ms sans timer1 -> LED7  --//
            PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10); 
            delay_ms(50); 
            PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10);
            delay_ms(50); 
            
            //-- MAJ de la machine d'état 
            appData.state = APP_STATE_WAIT; 
            
            break;
        }
        
        case APP_STATE_WAIT : 
        {
            //-- check du timer 1 -- 
            if (appData.tmr1EvtHasOcurred == true){
                appData.tmr1EvtHasOcurred = false;
                appData.state = APP_STATE_SERVICE_TASKS; 
            }
            
            break; 
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}





 

/*******************************************************************************
 End of File
 */
