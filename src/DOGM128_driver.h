/**
 * @file   DOGM128_driver.h  <br>
 * @author Frank Pernice <br>
 * @date   October 2013  <br>
 * @brief  Header file containing all driver code necessary to use the DOGM128
 *         with the ATMega128 (though other MCU's are not ruled out) <br>
 * @defgroup DOGM128_driver EA DOGM128 Driver
 * @{
 *
 * This header file contains all header files otherwise described in this 
 * library. To maximize space, the user may remove some, but not all, of these
 * files (by commenting out its inclusion in this file and detaching it from
 * the project) depending on how the DOG module is being used. The file 
 * dependencies are listed below <BR>
 *
 * DOGM128_user_config.h
 * - none                   \n(MUST NOT BE OMITTED) 
 * 
 * DOGM128_common.h file       
 * - DOGM128_user_config.h  \n(MUST NOT BE OMITTED) 
 * 
 * DOGM128_characters.h   
 * - DOGM128_common.h
 *
 * DOGM128_pixel.h
 * - DOGM128_common.h
 *
 * DOGM128_point.h
 * - DOGM128_pixel.h
 *
 * DOGM128_lines.h    
 * - DOGM128_point.h
 *
 * DOGM128_rectangle.h   
 * - DOGM128_point.h                               
 * - DOGM128_lines.h
 *
 * DOGM128_arc.h     
 * - DOGM128_point.h                               
 * - DOGM128_lines.h
 *
 * This relationship is further illustrated by the diagram below:
 * @image html DOGM128-hierarchy.png "EA DOGM128 Library File Hierarchy"
 */

/* Used to prevent multiple inclusion of the header file */
#ifndef DOGM128_DRIVER_ATMEGA128_H
#define DOGM128_DRIVER_ATMEGA128_H

/*----------------------------------------------------------------------------*/
/* INCLUDES                                                                   */
/*----------------------------------------------------------------------------*/
#include "DOGM128_common.h"
#include "DOGM128_characters.h"
#include "DOGM128_pixel.h"
#include "DOGM128_lines.h"
#include "DOGM128_point.h"
#include "DOGM128_rectangle.h"
#include "DOGM128_arc.h"

#endif /* DOGM128_DRIVER_ATMEGA128_H */

/** @} */ /* DOGM128_driver */