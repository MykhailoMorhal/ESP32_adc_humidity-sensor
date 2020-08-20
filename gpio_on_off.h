#ifndef MAIN_GPIO_ON_OFF_H_
#define MAIN_GPIO_ON_OFF_H_

/*----------------------------------------------------------------------
                                Functions
*----------------------------------------------------------------------*/

/**
 * @brief Init amplifier lv3 lv4
 */
void gpio33_ini_amplifier_lv3_lv4(void);

/**
 * @brief Init amplifier lv1 lv1
 */
void gpio25_ini_amplifier_lv1_lv2(void);

/**
 * @brief Print status ESP
 */
void gpio19_show_status_ESP(void);

/**
 * @brief Print status battery
 */
void gpio19_show_low_battery(void);



#endif /* MAIN_GPIO_ON_OFF_H_ */
