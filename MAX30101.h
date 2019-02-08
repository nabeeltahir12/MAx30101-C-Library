#include "stdint.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "MAX30101_def.h"


//SETUP FUNCTION
void regwrite8(nrf_drv_twi_t const * p_instance, uint8_t RegAddr, uint8_t data);
void regread8(nrf_drv_twi_t const * p_instance, uint8_t RegAddr, uint8_t *data);
void setup(nrf_drv_twi_t const * p_instance);

/*!
 * @brief This API reads the data from the given register address of sensor.
 *
 * @param[in] reg_addr  : Register address from where the data to be read
 * @param[out] data     : Pointer to data buffer to store the read data.
 * @param[in] len       : No of bytes of data to be read.
 * @param[in] dev       : Structure instance of max30101_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error
 */
int8_t max30101_get_regs(uint8_t reg_addr, uint8_t *data, uint16_t length, const struct max30101_dev *dev);

/*!
 * @brief This API writes the given data to the register address
 * of sensor.
 *
 * @param[in] reg_addr  : Register address from where the data to be written.
 * @param[in] data      : Pointer to data buffer which is to be written
 * in the sensor.
 * @param[in] len       : No of bytes of data to write..
 * @param[in] dev       : Structure instance of max30101_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error
 */
int8_t bmi160_set_regs(uint8_t reg_addr, uint8_t *data, uint16_t len, const struct max30101_dev *dev);

/*!
 * @brief This API resets and restarts the device.
 * All register values are overwritten with default parameters.
 *
 * @param[in] dev  : Structure instance of max30101_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
void max30101_init(struct max30101_dev *dev);


int8_t max30101_get_senor_data(const struct max30101_dev *dev);

/*!
 * @brief This API configures the power mode, range and bandwidth
 * of sensor.
 *
 * @param[in] dev    : Structure instance of max30101_dev.
 * @note : Refer user guide for detailed info.
 *
 * @return Result of API execution status
 * @retval zero -> Success / -ve value -> Error.
 */
int8_t max30101_set_sens_conf(struct max30101_dev *dev);

//new function to implement the write and read functions according to the data structure.
