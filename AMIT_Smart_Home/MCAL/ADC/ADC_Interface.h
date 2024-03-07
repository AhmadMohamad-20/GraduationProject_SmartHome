/*
 * Author   : Ahmed Mohamed Aboud
 * Linkedin :https://www.linkedin.com/in/ahmed-mohamed-aboud-33b2471b1/
 * File Name: ADC_Interface.h
 * Date: 22 Dec 2023
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define TIMEOUT 0xFF;

#define ADC_IDLE 1
#define ADC_BUSY 2

#define NORMAL_ASYNC	1
#define CHAIN_ASYNC		2

#define MAX_NUM 3

typedef struct
{
	uint8 channelID[MAX_NUM];
	uint8 ADC_Reading[MAX_NUM];
	uint8 ADC_error[MAX_NUM];
}ADC_chainSync_t;

typedef struct
{
	uint8 channelID[MAX_NUM];
	uint8 ADC_Reading[MAX_NUM];
	uint8 ADC_error[MAX_NUM];
	void (*pfADC_CallBack[MAX_NUM])(void);
}ADC_chainAsync_t;


static uint8 *ADC_value = 0;


void setCallBack_ADC(void (*funcPtr)(void));

void ADC_init(void);

uint8 ADC_startConversionSync(uint8 copy_ADC_channels, uint8 *copy_ADC_data);
void ADC_startConversionAsync(uint8 copy_ADC_channels);
uint8 ADC_startChainConversionSync(ADC_chainSync_t *chainSync);
void ADC_startChainConversionAsync(ADC_chainAsync_t *chainAsync);
#endif /* ADC_INTERFACE_H_ */
