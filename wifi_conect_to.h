
#ifndef MAIN_WIFI_CONECT_TO_H_
#define MAIN_WIFI_CONECT_TO_H_

/*----------------------------------------------------------------------
                                Include
*----------------------------------------------------------------------*/
#include "scan.h"

/*----------------------------------------------------------------------
                                Functions
*----------------------------------------------------------------------*/

/**
 * @brief Init Wi FI sta
 */
void wifi_init_sta();

/**
 * @brief Init Wi FI softtap (Access Point mode)
 */
void wifi_init_softap();


#endif /* MAIN_WIFI_CONECT_TO_H_ */
