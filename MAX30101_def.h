#include "stdint.h"

/*Errors */
#define MAX30101_OK              			  INT8_C(0)
#define MAX30101_E_NULL_PTR             INT8_C(-1)
#define MAX30101_E_COM_FAIL             INT8_C(-2)

#define MAX30101_ADDRESS          		0x57 //7-bit I2C Address
#define READ_ADDRESS                  0xAF //7-bit I2C Address
#define WRITE_ADDRESS                 0xAE //7-bit I2C Address
static const uint8_t  powerLevel = 		0x1F;
static const uint8_t  MULTI_LED_1 = 	0x11;
static const uint8_t  FIFO_CONF=			0x73;
/* Configuration register map of the max30101*/
// Status Registers
static const uint8_t MAX30101_INTSTAT1 =			0x00;
static const uint8_t MAX30101_INTSTAT2 =			0x01;
static const uint8_t MAX30101_INTENABLE1 =		0x02;
static const uint8_t MAX30101_INTENABLE2 =		0x03;

// FIFO Registers
static const uint8_t MAX30101_FIFOWRITEPTR = 	0x04;
static const uint8_t MAX30101_FIFOOVERFLOW = 	0x05;
static const uint8_t MAX30101_FIFOREADPTR = 	0x06;
static const uint8_t MAX30101_FIFODATA =			0x07;

// Configuration Registers
static const uint8_t MAX30101_FIFOCONFIG = 			0x08;
static const uint8_t MAX30101_MODECONFIG = 			0x09;
static const uint8_t MAX30101_PARTICLECONFIG = 	0x0A;    // Note, sometimes listed as "SPO2" config in datasheet (pg. 11)
static const uint8_t MAX30101_LED1_PULSEAMP = 	0x0C;
static const uint8_t MAX30101_LED2_PULSEAMP = 	0x0D;
static const uint8_t MAX30101_LED3_PULSEAMP = 	0x0E;
static const uint8_t MAX30101_LED_PROX_AMP = 		0x10;
static const uint8_t MAX30101_MULTILEDCONFIG1 = 0x11;
static const uint8_t MAX30101_MULTILEDCONFIG2 = 0x12;

// Die Temperature Registers
static const uint8_t MAX30101_DIETEMPINT = 			0x1F;
static const uint8_t MAX30101_DIETEMPFRAC = 		0x20;
static const uint8_t MAX30101_DIETEMPCONFIG = 	0x21;

// Proximity Function Registers
static const uint8_t MAX30101_PROXINTTHRESH = 	0x30;

// Part ID Registers
static const uint8_t MAX30101_REVISIONID = 			0xFE;
static const uint8_t MAX30101_PARTID = 					0xFF;    // Should always be 0x15. Identical to MAX30102.

// MAX30101 Commands
// Interrupt configuration (pg 13, 14)
static const uint8_t MAX30101_INT_A_FULL_MASK =			0x7F;
static const uint8_t MAX30101_INT_A_FULL_ENABLE = 	0x80;
static const uint8_t MAX30101_INT_A_FULL_DISABLE = 	0x00;

static const uint8_t MAX30101_INT_DATA_RDY_MASK = 		0xBF;
static const uint8_t MAX30101_INT_DATA_RDY_ENABLE =		0x40;
static const uint8_t MAX30101_INT_DATA_RDY_DISABLE = 	0x00;

static const uint8_t MAX30101_INT_ALC_OVF_MASK = 			0xDF;
static const uint8_t MAX30101_INT_ALC_OVF_ENABLE = 		0x20;
static const uint8_t MAX30101_INT_ALC_OVF_DISABLE = 	0x00;

static const uint8_t MAX30101_INT_PROX_INT_MASK = 		0xEF;
static const uint8_t MAX30101_INT_PROX_INT_ENABLE = 	0x10;
static const uint8_t MAX30101_INT_PROX_INT_DISABLE = 	0x00;

static const uint8_t MAX30101_INT_DIE_TEMP_RDY_MASK = 		0xFD;
static const uint8_t MAX30101_INT_DIE_TEMP_RDY_ENABLE = 	0x02;
static const uint8_t MAX30101_INT_DIE_TEMP_RDY_DISABLE =	0x00;
// FIFO configuration commands (page 18)
static const uint8_t MAX30101_SAMPLEAVG_MASK =	0x1F;
static const uint8_t MAX30101_SAMPLEAVG_1 = 		0x00; //1 samples averaged per fifo sample
static const uint8_t MAX30101_SAMPLEAVG_2 = 		0x20; //2 samples averaged per fifo sample
static const uint8_t MAX30101_SAMPLEAVG_4 = 		0x40; //4 samples averaged per fifo sample
static const uint8_t MAX30101_SAMPLEAVG_8 = 		0x60; //8 samples averaged per fifo sample
static const uint8_t MAX30101_SAMPLEAVG_16 = 		0x80; //16 samples averaged per fifo sample
static const uint8_t MAX30101_SAMPLEAVG_32 = 		0xA0; //32 samples averaged per fifo samples

static const uint8_t MAX30101_ROLLOVER_MASK = 		0xEF;
static const uint8_t MAX30101_ROLLOVER_ENABLE = 	0x10; // FIFO roll over enable register enable
static const uint8_t MAX30101_ROLLOVER_DISABLE =  0x00;

static const uint8_t MAX30101_A_FULL_MASK = 		0xF0;
static const uint8_t MAX30101_A_FULL_29 = 	    0x03; //29 unread data samples in fifo when interrupt is generated
// Mode configuration commands (page 19)
static const uint8_t MAX30101_SHUTDOWN_MASK = 	0x7F;
static const uint8_t MAX30101_SHUTDOWN = 				0x80;
static const uint8_t MAX30101_WAKEUP = 					0x00;

static const uint8_t MAX30101_RESET_MASK = 			0xBF;
static const uint8_t MAX30101_RESET = 					0x40;

static const uint8_t MAX30101_MODE_MASK = 			0xF8;
static const uint8_t MAX30101_MODE_REDONLY = 		0x02;
static const uint8_t MAX30101_MODE_REDIRONLY = 	0x03;
static const uint8_t MAX30101_MODE_MULTILED = 	0x07;



// Particle sensing configuration commands (pgs 19-20)
static const uint8_t MAX30101_ADCRANGE_MASK = 	0x9F;
static const uint8_t MAX30101_ADCRANGE_2048 = 	0x00;
static const uint8_t MAX30101_ADCRANGE_4096 = 	0x20;
static const uint8_t MAX30101_ADCRANGE_8192 = 	0x40;
static const uint8_t MAX30101_ADCRANGE_16384 = 	0x60;

static const uint8_t MAX30101_SAMPLERATE_MASK = 0xE3;
static const uint8_t MAX30101_SAMPLERATE_50 = 	0x00;
static const uint8_t MAX30101_SAMPLERATE_100 = 	0x04;
static const uint8_t MAX30101_SAMPLERATE_200 = 	0x08;
static const uint8_t MAX30101_SAMPLERATE_400 = 	0x0C;
static const uint8_t MAX30101_SAMPLERATE_800 = 	0x10;
static const uint8_t MAX30101_SAMPLERATE_1000 = 0x14;
static const uint8_t MAX30101_SAMPLERATE_1600 = 0x18;
static const uint8_t MAX30101_SAMPLERATE_3200 = 0x1C;

static const uint8_t MAX30101_PULSEWIDTH_MASK = 0xFC;
static const uint8_t MAX30101_PULSEWIDTH_69 = 	0x00;
static const uint8_t MAX30101_PULSEWIDTH_118 = 	0x01;
static const uint8_t MAX30101_PULSEWIDTH_215 = 	0x02;
static const uint8_t MAX30101_PULSEWIDTH_411 = 	0x03;

//Multi-LED Mode configuration (pg 22)
static const uint8_t MAX30101_SLOT1_MASK = 		0xF8;
static const uint8_t MAX30101_SLOT2_MASK = 		0x8F;
static const uint8_t MAX30101_SLOT3_MASK = 		0xF8;
static const uint8_t MAX30101_SLOT4_MASK = 		0x8F;

static const uint8_t SLOT_NONE = 						0x00;
static const uint8_t SLOT_RED_LED = 				0x01;
static const uint8_t SLOT_IR_LED = 					0x02;
static const uint8_t SLOT_GREEN_LED = 			0x03;
static const uint8_t SLOT_NONE_PILOT = 			0x04;
static const uint8_t SLOT_RED_PILOT =				0x05;
static const uint8_t SLOT_IR_PILOT = 				0x06;
static const uint8_t SLOT_GREEN_PILOT = 		0x07;

/*****************************************************************************/
/* type definitions  */
typedef int8_t (*bmi160_com_fptr_t)(uint8_t dev_addr, uint8_t reg_addr,
		uint8_t *data, uint16_t len);

typedef void (*bmi160_delay_fptr_t)(uint32_t period);

/*************************** Data structures *********************************/

/*
 *  @brief This structure holds the information for
 *  FIFO Configuration register.
 */

struct max30101_fifo_config
{
	/*! Sample Averaging 
    Adjacent samples (in each individual channel) can be averaged and decimated
    on the chip by setting this register	*/
	uint8_t sample_avg;
	
	/*! This bit controls the behavior of the FIFO when the FIFO 
	    becomes completely filled with data */
	uint8_t fifo_roll_ovr;
	
		/*!This register sets the number of data samples (3 bytes/sample)
     	remaining in the FIFO when the interrupt is issued*/
	uint8_t fifo_a_full;
	
};
/*
 *  @brief This structure holds the information for
 *  MODE Configuration register.
 */

struct max30101_mode_config
{
	/*! Shutdown Control	*/
	uint8_t shdn;
	
	/*! Reset Control  */
	uint8_t reset_control;
	
	/*!Mode Control[2:0]
	    0) 000  Do not use
	    1) 001  Do not use
      2) 010  Heart Rate mode Red Only
      3) 011  SpO2 mode red and IR
      4) 100  Do not use
      5) 101  Do not use
      6) 110  Do not use
	    7) 111  Multi-Led Mode Green,Red, and/or IR 
	  */
	uint8_t mode_control;
	
};

/*
 *  @brief This structure holds the information for
 *  SpO2 Configuration register.
 */

struct max30101_spo2_config
{
	/*! SpO2 ADC Range Control[1:0]
    This register sets the SpO2 sensor ADC’s full-scale range.	
      0) 00  2048nA
	    1) 01  4096nA
      2) 10  8192nA
      3) 11  16384nA
    */	
	uint8_t adc_range;
	
	/*! Sample Rate Control[2:0] 
     These bits define the effective sampling rate with one sample 4
     consisting of one IR pulse/conversion and one RED pulse/
     conversion	
	    0) 000  50
	    1) 001  100
      2) 010  200
      3) 011  400
      4) 100  800
      5) 101  1000
      6) 110  1600
	    7) 111  3200 
	*/
	uint8_t smpl_rate;
	
	/*!Led Pulse width control[1:0]
	    These bits set the LED pulse width
	    0) 000  69   ADC resolution 15
	    1) 001  118  ADC resolution 16
      2) 010  215  ADC resolution 17
      3) 011  411  ADC resolution 18
	  */
	uint8_t led_pulse_width;
	
};

/*
 *  @brief This structure holds the information for
 *  pulse amplitude of the each led Configuration registers.
 *  These bits set the current level of each LED 
 */

struct max30101_pulse_ampl
{
	/*! LED1_Pulse_Amplitude[7:0]
    */	
	uint8_t led1_pa;
	
	/*! LED2_Pulse_Amplitude[7:0]
	*/
	uint8_t led2_pa;
	
	/*!LED3_Pulse_Amplitude[7:0]
	  */
	uint8_t led3_pa;
	
};

/*
 *  @brief This structure holds the information for
 *  Multi-Led mode Control Register Configuration registers.
      0) 000  None
	    1) 001  LED1(RED)    LED1_PA
      2) 010  LED2(IR)     LED2_PA
      3) 011  LED3(Green)  LED3_PA
      4) 100  None
      5) 101  None
      6) 110  None
	    7) 111  None 
	*/ 
 

struct max30101_multi_led_mode
{
	/*!SLOT1
    */	
	uint8_t slot1;
	
	/*!SLOT2
	*/
	uint8_t slot2;
	
	/*!SLOT3
	  */
	uint8_t slot3;
	
	/*!SLOT3
	  */
	uint8_t slot4;
	
};

/*
   * Structure to initialiize and configure the MAx30101
*/
struct max30101_dev
{
	/*! Chip Id */
	uint8_t chip_id;
	/*! Revision Id */
	uint8_t rev_id;
		/*! Device Id */
	uint8_t id;
	/*structure to initialize the fifo configuration 
	register.*/
	struct max30101_fifo_config fifo_cfg;
	
	/*structure to initialize the mode configuration 
	register.*/
	struct max30101_mode_config max30101_mode;

	/*structure to initialize the SpO2 configuration 
	register.*/
	struct max30101_spo2_config spo2_cfg;
	
	/*structure to initialize the SpO2 configuration 
	register.*/
	struct max30101_pulse_ampl pulse_ampl_cfg;
	
		/*structure to initialize the SpO2 configuration 
	register.*/
	struct max30101_multi_led_mode multi_led_mode;
	
	/*! Read function pointer */
	bmi160_com_fptr_t read;
	
	/*! Write function pointer */
	bmi160_com_fptr_t write;
	
	/*!  Delay function pointer */
	bmi160_delay_fptr_t delay_ms;
};

