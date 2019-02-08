/* The c file containing the requireed functionalities to initialize the sensor */
#include "MAX30101.h"

#include "nrf_delay.h"
#include "nrf_drv_twi.h"

static const uint8_t MAX30101_CONF_FIFO = MAX30101_SAMPLEAVG_8 | MAX30101_ROLLOVER_ENABLE | MAX30101_A_FULL_29; 

static const uint8_t MAX30101_CONF_MODE=MAX30101_MODE_REDONLY;


void setup(nrf_drv_twi_t const * p_instance)
{
	  // Configuration register setting
	  uint8_t reg[2] = {0x08, 0x73};
	  nrf_drv_twi_tx(p_instance, MAX30101_ADDRESS, reg, sizeof(reg), false);
	
		
		//Setting the FIFO configuration register
		nrf_delay_ms(5);
	  uint8_t reg1[2]= {0x09, 0x02};
    nrf_drv_twi_tx(p_instance, MAX30101_ADDRESS, reg1, sizeof(reg1), true);
		
		nrf_delay_ms(5);
 
		//LED Pulse applitude register to set the current in the led	
		regwrite8(p_instance,MAX30101_LED1_PULSEAMP,powerLevel);
    nrf_delay_ms(5);

     // Multi Led mode configuration register is setupt to only RED	
    regwrite8(p_instance,MAX30101_MULTILEDCONFIG1,MULTI_LED_1);
		nrf_delay_ms(5);

	
}

/*API to read the data from the register*/
int8_t max30101_get_regs(uint8_t reg_addr, uint8_t *data, uint16_t length, const struct max30101_dev *dev)
{
	int8_t rslt = MAX30101_OK;
	if ((dev == NULL) || (dev->read == NULL))
	  {
		  rslt = MAX30101_E_NULL_PTR;
	  }
	else
	  {
				rslt = dev->read(dev->id, reg_addr, data, length);
		    dev->delay_ms(1);
	      if (rslt != MAX30101_OK)
			    rslt = MAX30101_E_COM_FAIL;
	  }
		
		return rslt;
}

/*API to write the data from the register*/
int8_t max30101_set_regs(uint8_t reg_addr, uint8_t *data, uint16_t length, const struct max30101_dev *dev)
{
	int8_t rslt = MAX30101_OK;
	if ((dev == NULL) || (dev->read == NULL))
	  {
		  rslt = MAX30101_E_NULL_PTR;
	  }
	else
	  {
				rslt = dev->write(dev->id, reg_addr, data, length);
		    dev->delay_ms(1);
	      if (rslt != MAX30101_OK)
			    rslt = MAX30101_E_COM_FAIL;
	  }
		
		return rslt;
}

/**@brief Function for writing the data to max30101 .
 *
 * @param[in] p_instance  TWI instance.
 * @param[in] RegAddr     Register Address to be written.
 * @param[in] data        Data to be written to the register.
 */
void regwrite8(nrf_drv_twi_t const * p_instance, uint8_t RegAddr, uint8_t data)
{
	uint8_t reg[2] = {RegAddr, data};
	nrf_drv_twi_tx(p_instance, MAX30101_ADDRESS, reg, sizeof(reg), false);
	nrf_delay_ms(5);
}

/**@brief Function for reading the data from max30101 .
 *
 * @param[in] p_instance  TWI instance.
 * @param[in] RegAddr     Register Address .
 * @param[in] data        Pointer to the location where to store the data.
 */
void regread8(nrf_drv_twi_t const * p_instance, uint8_t RegAddr, uint8_t *data)
{

	nrf_drv_twi_tx(p_instance, MAX30101_ADDRESS, &RegAddr, sizeof(RegAddr), false);
	nrf_delay_ms(5);
	nrf_drv_twi_rx(p_instance, MAX30101_ADDRESS, data, sizeof(RegAddr));
	nrf_delay_ms(5);
}