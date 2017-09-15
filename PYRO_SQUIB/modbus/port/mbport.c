#include "mb.h"
#include "adc.h"
#include "string.h"
#include "main.h"
#include "dig_pot.h"
#include "pyro_squib.h"
#include "cfg_info.h"

#pragma anon_unions
typedef struct
{
	union
	{
		float val;
		uint16_t buf[2];
	};
}stFloatToUint16Buf;

typedef struct
{
	union
	{
		uint64_t val;
		uint16_t buf[4];
	};
}stUint64ToUint16Buf;

stFloatToUint16Buf FloatToUint16Buf;
stUint64ToUint16Buf Uint64ToUint16Buf;

#define FLOAT_TO_UINT16_BUF(fl,uint16buf) 	FloatToUint16Buf.val=fl;\
																						(uint16buf)[0]=FloatToUint16Buf.buf[0];\
																						(uint16buf)[1]=FloatToUint16Buf.buf[1];

#define UINT16_BUF_TO_FLOAT(uint16buf,fl) 	FloatToUint16Buf.buf[0]=(uint16buf)[0];\
																						FloatToUint16Buf.buf[1]=(uint16buf)[1];\
																						fl=FloatToUint16Buf.val;

#define UINT64_TO_UINT16_BUF(uint64_val,uint16buf) 	Uint64ToUint16Buf.val=uint64_val;\
																						(uint16buf)[0]=Uint64ToUint16Buf.buf[0];\
																						(uint16buf)[1]=Uint64ToUint16Buf.buf[1];\
																						(uint16buf)[2]=Uint64ToUint16Buf.buf[2];\
																						(uint16buf)[3]=Uint64ToUint16Buf.buf[3];

#define UINT16_BUF_TO_UINT64(uint16buf,uint64_val) 	Uint64ToUint16Buf.buf[0]=(uint16buf)[0];\
																						Uint64ToUint16Buf.buf[1]=(uint16buf)[1];\
																						Uint64ToUint16Buf.buf[2]=(uint16buf)[2];\
																						Uint64ToUint16Buf.buf[3]=(uint16buf)[3];\
																						uint64_val=Uint64ToUint16Buf.val;

void ENTER_CRITICAL_SECTION(void)
{
	//__set_PRIMASK(1);
	__ASM volatile ("cpsid i");

}

void EXIT_CRITICAL_SECTION(void)
{
	//__set_PRIMASK(0);
	__ASM volatile ("cpsie i");
}

extern volatile float ADC_voltage[ADC_CHN_NUM];
extern uint8_t digPotValue[I2C_POT_NUM];
extern stPyroSquib *PyroSquibParam;
extern stADC_PyroBuf ADC_PyroBuf;
extern uint16_t ADC_value[ADC_CHN_NUM];
extern enPyroSquibError			PyroSquibError;  
extern uint8_t PyroSquibStatus;
extern SemaphoreHandle_t xPyroSquib_Semaphore;

#define REG_INPUT_START     1000
#define REG_INPUT_NREGS     20

#define REG_HOLDING_START   2000
#define REG_HOLDING_NREGS   16

#define REG_ADC_0						0
#define REG_ADC_1						2
#define REG_ADC_2						4
#define REG_ADC_3						6
#define REG_ADC_4						8
#define REG_ADC_5						10
#define REG_ADC_6						12
#define REG_ADC_7						14


#define REG_PIR_STATE					16
#define REG_PIR_ERROR					17
#define REG_PIR_IN_LINE				18

static USHORT   usRegInputStart = REG_INPUT_START;
USHORT   usRegInputBuf[REG_INPUT_NREGS];

static USHORT   usRegHoldingStart = REG_HOLDING_START;
USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];


eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode eStatus = MB_ENOERR;
    int iRegIndex;
		float tempADCvalue;

    if ( ( usAddress >= REG_INPUT_START ) &&
         ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = (int) ( usAddress - usRegInputStart );
			
			tempADCvalue=ADC_toVoltage(ADC_value[0]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_0]);
			tempADCvalue=ADC_toVoltage(ADC_value[1]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_1]);
			tempADCvalue=ADC_toVoltage(ADC_value[2]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_2]);
			tempADCvalue=ADC_toVoltage(ADC_value[3]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_3]);
			tempADCvalue=ADC_toVoltage(ADC_value[4]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_4]);
			tempADCvalue=ADC_toVoltage(ADC_value[5]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_5]);
			tempADCvalue=ADC_toVoltage(ADC_value[6]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_6]);
			tempADCvalue=ADC_toVoltage(ADC_value[7]);
			FLOAT_TO_UINT16_BUF(tempADCvalue, &usRegInputBuf[REG_ADC_7]);			

						
				usRegInputBuf[REG_PIR_STATE]=PyroSquibParam->state;
				usRegInputBuf[REG_PIR_ERROR]=PyroSquibError;
				usRegInputBuf[REG_PIR_IN_LINE]=PyroSquibStatus;
			
			
        while ( usNRegs > 0 )
        {
            *pucRegBuffer++ = (unsigned char) ( usRegInputBuf[ iRegIndex ] >> 8 );
            *pucRegBuffer++ = (unsigned char) ( usRegInputBuf[ iRegIndex ] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}




#define REG_PIR_SET_TIME				0
#define REG_PIR_1_SET_CURRENT		1
#define REG_PIR_2_SET_CURRENT		3
#define REG_PIR_3_SET_CURRENT		5
#define REG_PIR_4_SET_CURRENT		7
#define REG_PIR_SET_MASK				9
#define REG_PIR_START						10

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
		uint8_t settings_need_write=0;
		float tempValue;
	
    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldingStart );
        switch ( eMode )
        {
        case MB_REG_READ:	
						usRegHoldingBuf[REG_PIR_SET_TIME]=PyroSquibParam->time;
				
						FLOAT_TO_UINT16_BUF(PyroSquibParam->current[0], &usRegHoldingBuf[REG_PIR_1_SET_CURRENT]);
						FLOAT_TO_UINT16_BUF(PyroSquibParam->current[1], &usRegHoldingBuf[REG_PIR_2_SET_CURRENT]);
						FLOAT_TO_UINT16_BUF(PyroSquibParam->current[2], &usRegHoldingBuf[REG_PIR_3_SET_CURRENT]);
						FLOAT_TO_UINT16_BUF(PyroSquibParam->current[3], &usRegHoldingBuf[REG_PIR_4_SET_CURRENT]);
				
						usRegHoldingBuf[REG_PIR_SET_MASK]=PyroSquibParam->mask;
						usRegHoldingBuf[REG_PIR_START]=0;
				
            while( usNRegs > 0 )
            {
                *pucRegBuffer++ = ( UCHAR ) ( usRegHoldingBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( UCHAR ) ( usRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;
        case MB_REG_WRITE:
						
            while( usNRegs > 0 )
            {
                usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;

								
								switch(iRegIndex)
								{
										case REG_PIR_SET_TIME:
										{
											if(IS_PYRO_SQUIB_TIME(usRegHoldingBuf[REG_PIR_SET_TIME]) 	&&
													(PyroSquibParam->time!=usRegHoldingBuf[REG_PIR_SET_TIME]))
											{												
												PyroSquibParam->time=usRegHoldingBuf[REG_PIR_SET_TIME];
												settings_need_write=1;
											}
										}
										break;
										
										case REG_PIR_1_SET_CURRENT +1:
										{
											UINT16_BUF_TO_FLOAT(&usRegHoldingBuf[REG_PIR_1_SET_CURRENT], tempValue);
											if(IS_PYRO_SQUIB_CURRENT(tempValue)	&& (PyroSquibParam->current[0]!=tempValue))
											{
												PyroSquibParam->current[0]=tempValue;
												settings_need_write=1;
											}
										}
										break;	
										
										case REG_PIR_2_SET_CURRENT +1:
										{
											UINT16_BUF_TO_FLOAT(&usRegHoldingBuf[REG_PIR_2_SET_CURRENT], tempValue);
											if(IS_PYRO_SQUIB_CURRENT(tempValue)	&& (PyroSquibParam->current[1]!=tempValue))
											{
												PyroSquibParam->current[1]=tempValue;
												settings_need_write=1;
											}
										}
										break;	
										
										case REG_PIR_3_SET_CURRENT +1:
										{
											UINT16_BUF_TO_FLOAT(&usRegHoldingBuf[REG_PIR_3_SET_CURRENT], tempValue);
											if(IS_PYRO_SQUIB_CURRENT(tempValue)	&& (PyroSquibParam->current[2]!=tempValue))
											{
												PyroSquibParam->current[2]=tempValue;
												settings_need_write=1;
											}
										}
										break;	
										
										case REG_PIR_4_SET_CURRENT +1:
										{
											UINT16_BUF_TO_FLOAT(&usRegHoldingBuf[REG_PIR_4_SET_CURRENT], tempValue);
											if(IS_PYRO_SQUIB_CURRENT(tempValue)	&& (PyroSquibParam->current[3]!=tempValue))
											{
												PyroSquibParam->current[3]=tempValue;
												settings_need_write=1;
											}
										}
										break;											

										case REG_PIR_SET_MASK:
										{
												if(PyroSquibParam->mask!=usRegHoldingBuf[REG_PIR_SET_MASK])
												{
													PyroSquibParam->mask=usRegHoldingBuf[REG_PIR_SET_MASK];
													settings_need_write=1;
												}
										}
										break;	
										
										case REG_PIR_START:
										{
											 if(usRegHoldingBuf[REG_PIR_START])
											 {
													usRegHoldingBuf[REG_PIR_START]=0;
													xSemaphoreGive( xPyroSquib_Semaphore);
											 }
										}
										break;

								}
								
								iRegIndex++;
                usNRegs--;
            }
						
						if(settings_need_write)
						{
								//StartConfigInfoWrite();
								ConfigInfoWrite();
						}
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    ( void )pucRegBuffer;
    ( void )usAddress;
    ( void )usNCoils;
    ( void )eMode;
    return MB_ENOREG;
}


eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    ( void )pucRegBuffer;
    ( void )usAddress;
    ( void )usNDiscrete;
    return MB_ENOREG;
}
