#include "test_def.h"


/*
 * APIs
 * 
 * extern STATUS McSpiTrans(SPI_HARDWARE *  devInfo, SPI_TRANSFER *  pPkg, INT32);
 */

#define GPIO_4_8                (0x68) 

#define SPI_PORT_1              1
#define SPI_PORT_2              2
#define SPI_PORT_3              3
#define SPI_PORT_4              4

#define SPI_DIGITAL_IO          SPI_PORT_2

#define SPI_SLAVE_0             0
#define SPI_SLAVE_1             1
#define SPI_SLAVE_2             2
#define SPI_SLAVE_3             3
#define SPI_EHERNETIP_CH        SPI_SLAVE_0  //slave 0
#define SPI_DIGITAL_INPUTS_CH   SPI_SLAVE_0  //slave 0
#define SPI_DIGITAL_OUTPUTS_CH  SPI_SLAVE_1  //slave 1
#define SPI_ANALOG_INPUTS_CH    SPI_SLAVE_0  //slave 0
#define SPI_ANALOG_OUTPUTS_CH   SPI_SLAVE_1  //slave 1

#define NUM_BITS_PERTRANSFER_32 32
#define NUM_BITS_PERTRANSFER_16 16
#define NUM_BITS_PERTRANSFER_8  8

#define SPI_CLK_MODE0           0     // POL = 0, PHA = 0
#define SPI_CLK_MODE1           1     // POL = 0, PHA = 1
#define SPI_CLK_MODE2           2     // POL = 1, PHA = 0
#define SPI_CLK_MODE3           3     // POL = 1, PHA = 1

#define SPI_FULL_DUPLEX         0x20

#define DOUT_LINE_MAX 	        8

#define DAC_CONFIG_CH_A    		0x0000
#define DAC_CONFIG_CH_B   		0x4000
#define DAC_CONFIG_MASK    		0x3FFF
#define DAC_CONFIG_PWR_NORM 	0x0000
#define DAC_CONFIG_PWR_DOWN 	0x2000
#define DAC_CONFIG_SPD_SLOW 	0x0000
#define DAC_CONFIG_SPD_FAST 	0x1000
#define DAC_MAX_VALUE      		0x3FF

typedef enum
{
    LINE_LOW,
    LINE_HIGH
} LINE_VALUE;

enum
{
    DAC_CH_A = 0,
    DAC_CH_B,
    DAC_CH_MAX
};

//Sine Wave
//static UINT16 Aout_tx1[28] = {0x800, 0x97C, 0xAE9, 0xC3A, 0xD61, 0xE53, 0xF07, 0xF76, 0xF9C, 0xF76, 0xF07, 0xE53, 0xD61, 0xC3A, 0xAE9, 0x97C, 0x800, 0x684, 0x517, 0x3C6, 0x29F, 0x1AD, 0x0F9, 0x1AD, 0x29F, 0x3C6, 0x517, 0x684}; 
static UINT16 Aout_tx1[14] = {0xF9C, 0xF76, 0xF07, 0xE53, 0xD61, 0xC3A, 0xAE9, 0x97C, 0x800, 0x684, 0x517, 0x3C6, 0x29F, 0x1AD}; 

UINT8 Aout_tx2[3] = {0x06, 0x0, 0x0};  //single ended CH0
UINT8 Ain_rx2[3] = {0x0, 0x0, 0x0};

UINT16 SpiAout_txBuf = 0;
UINT16 SpiAout_rxBuf = 5555;
UINT16 Dac_config    = 0;

/**************************************************************************//**
* \brief   - This function is to disable /IO_RESET pin,
* 			 which will be enable the devices connected
*
* \param   - None.
*
* \return  - GPIO_OK or GPIO_ERROR.
*
******************************************************************************/

STATUS GpioIOResetDis(void)
{	
    if(GpioAlloc(GPIO_4_8) != OK)
    {
        printf("failed to allocate reset pin\n");
        return ERROR;
    }

    if(GpioSetDir(GPIO_4_8, GPIO_DIR_OUTPUT) != OK)
    {
        printf("failed to switch reset pin to output dircetion\n");
        goto exit;
    }

    if(GpioSetValue(GPIO_4_8, GPIO_VALUE_LOW) != OK)
    {
        printf("failed to output low level to reset pin\n");
        goto exit;
    }

    MsDelay(1000);
    if(GpioSetValue(GPIO_4_8, GPIO_VALUE_HIGH) != OK)
    {
        printf("failed to output high level to reset pin\n");
        goto exit;
    }

exit:
    if(GpioFree(GPIO_4_8) != OK)
    {
        printf("failed to free reset pin\n");
        return ERROR;
    }

    return OK;
}

/**************************************************************************//**
* \brief   - This function is responsible for receiving Digital IO inputs.
*
* \param   - UINT16 *.
*
* \return  - the 16 bit port value.
*
* \Notes   - On J116:  DIN1    DIN2    DIN3    DIN4    DIN5    DIN6    DIN7    DIN8    DIN9  
* 					   PIN1	   PIN2    PIN3    PIN4    PIN11   PIN12   PIN13   PIN16   PIN19
* 					   
* 			 VIH = 9V with hysteresis		   	
* 
******************************************************************************/

STATUS ScDgtGetDinPort(UINT16 *data)
{	
    SPI_HARDWARE    hw = {0};
    SPI_TRANSFER    pkt = {0};
    UINT16          rxBuf[1];
    UINT16          txBuf[1];

    txBuf[0] = 0x1ff;  //Enable 9 inputs
    // Buffer containing the received data
    rxBuf[0] = 0x0;

    //Receive the serial output
    
    hw.chipSelect   =   SPI_DIGITAL_INPUTS_CH;
    hw.bitWidth     =   NUM_BITS_PERTRANSFER_16;
    hw.devFreq      =   1000000;
    hw.mode         =   SPI_CLK_MODE1 | SPI_FULL_DUPLEX;
    hw.dataLines    =   1;

    pkt.txBuf       = (UINT8 *)txBuf;
    pkt.txLen       = sizeof(txBuf);
    pkt.rxBuf       = (UINT8 *)rxBuf;
    pkt.rxLen       = sizeof(rxBuf);

    if(McSpiTrans(&hw, &pkt, SPI_DIGITAL_IO) != OK)
    {
        printf("failed to transfer data for receiving Digital IO inputs\n");
        return ERROR;
    }

    *data = rxBuf[0];
    return OK;
}

/**************************************************************************//**
* \brief   - This function is responsible for setting Industrial digital IO outputs.
*            Transfer value by SPI.
*
* \param   - line: Set which output line.
* 			 val : Set high or low to the line selected.
*
* \return  - DIO_OK or DIO_ERROR.
* 
* \Notes   - On J116:  DOUT1    DOUT2    DOUT3    DOUT4    DOUT5    DOUT6    DOUT7    DOUT8 
* 					   PIN7	    PIN8     PIN9     PIN10    PIN19    PIN20    PIN21    PIN22
*
*
******************************************************************************/

STATUS ScDgtSetDoutPort(UINT16 line, UINT16 val)
{	
    SPI_HARDWARE    hw = {0};
    SPI_TRANSFER    pkt = {0};

    SpiAout_txBuf = 0;
    if(DOUT_LINE_MAX > line)  //The lines 0-7
    {	
        if(LINE_HIGH == val)
        {
            SpiAout_txBuf |= 1 << (line + 8);   //Set value high
        }
        else if(LINE_LOW == val)
        {
            SpiAout_txBuf &= ~(1 << (line + 8));	//Set value low
        }
        printf("\nSet Digital I/O Output: %04x\n", SpiAout_txBuf);
    }
    else
        printf("\nSet Digital I/O Failed: Invalid Line input\n");
    
    
    hw.chipSelect   =   SPI_DIGITAL_OUTPUTS_CH;
    hw.bitWidth     =   NUM_BITS_PERTRANSFER_16;
    hw.devFreq      =   10000000;
    hw.mode         =   SPI_CLK_MODE0 | SPI_FULL_DUPLEX;
    hw.dataLines    =   1;

    pkt.txBuf       = (UINT8 *)&SpiAout_txBuf;
    pkt.txLen       = sizeof(SpiAout_txBuf);
    pkt.rxBuf       = (UINT8 *)&SpiAout_rxBuf;
    pkt.rxLen       = sizeof(SpiAout_rxBuf);

    if(McSpiTrans(&hw, &pkt, SPI_DIGITAL_IO) != OK)
    {
        printf("failed to transfer date for setting Industrial digital IO outputs\n");
        return ERROR;
    }
    else
    {
        printf("\nDigital Out: %04x\n", SpiAout_rxBuf);
    }
    
    return OK;
}

/**************************************************************************//**
* \brief   - This function is responsible for transmitting Industrial analog IO outputs
*
* \param   - line -- which channel
* 			 val -- what value to set
*
* \return  - UINT16
*
*****************************************************************************/

void AnlgSetDoutValue(UINT16 line, UINT16 val)
{	
    if ((line < DAC_CH_MAX)&&(val <= DAC_MAX_VALUE))
    {
        //Set DAC channel 
        if (DAC_CH_A == line)
        {
            Dac_config = DAC_CONFIG_CH_A;  //config DAC channel A						
        }
        else
        {
            Dac_config = DAC_CONFIG_CH_B;  //config DAC channel B			
        }

        Dac_config |= DAC_CONFIG_PWR_NORM | DAC_CONFIG_SPD_FAST;
        SpiAout_txBuf = (UINT16)(val << 2);
        SpiAout_txBuf |= Dac_config;
    }
}

/**************************************************************************//**
* \brief   - This function is responsible for SPI-4 A/D & D/A loop test
*
* \param   - UINT16 channel (A/B)
* 			 
* \return  - UINT16
*
* \Notes   - Short connect the AIN1-AOUT1 & AIN2-AOUT2
*
*****************************************************************************/

STATUS ScLoopADDA(UINT16 channel)
{	
    SPI_HARDWARE    hw = {0};
    SPI_TRANSFER    pkt = {0};
    UINT32          tmp = 0;
    UINT32          cnt = 0;

    while(cnt != sizeof(Aout_tx1)/2)
    {
        hw.chipSelect   =   SPI_ANALOG_OUTPUTS_CH;
        hw.bitWidth     =   NUM_BITS_PERTRANSFER_16;
        hw.devFreq      =   1000000;
        hw.mode         =   SPI_CLK_MODE3 | SPI_FULL_DUPLEX;
        hw.dataLines    =   1;
        
        AnlgSetDoutValue(channel, Aout_tx1[cnt]/4);  // 12 Bits -> 10 Bits

        pkt.txBuf   = (UINT8 *)&SpiAout_txBuf;
        pkt.txLen   = 2;
        pkt.rxBuf   = (UINT8 *)Ain_rx2;
        pkt.rxLen   = 2;
        
        if(McSpiTrans(&hw, &pkt, SPI_PORT_4) != OK)
        {
            printf("failed to transfer data for CH%d D/A Output\n", channel);
            return ERROR;
        }
        else
        {
            printf("CH:%d    D/A Output: 0x%x  (%4dmV)", channel, Aout_tx1[cnt], Aout_tx1[cnt]*5000/4096*2);
        }
        MsDelay(1000);
    
        hw.chipSelect   =   SPI_ANALOG_INPUTS_CH;
        hw.bitWidth     =   NUM_BITS_PERTRANSFER_8;
        hw.devFreq      =   1000000;
        hw.mode         =   SPI_CLK_MODE0 | SPI_FULL_DUPLEX;
        hw.dataLines    =   1;

        Aout_tx2[1] = (UINT8)(channel * 0x40);    //CH0 & CH1
        
        pkt.txBuf   = (UINT8 *)Aout_tx2;
        pkt.txLen   = sizeof(Aout_tx2);
        pkt.rxBuf   = (UINT8 *)Ain_rx2;
        pkt.rxLen   = sizeof(Aout_tx2);
            
        if(McSpiTrans(&hw, &pkt, SPI_PORT_4) != OK)
        {
            printf("failed to transfer data for CH%d A/D Input\n", channel);
            return ERROR;
        }
        
        tmp = (Ain_rx2[1] & 0x1f) << 8;
        tmp += Ain_rx2[2];
        
        printf("    A/D Input: 0x%x  (%4dmV)\n", tmp, tmp*2500/4096*4);
        MsDelay(1000);
        cnt++;
    }

    return OK;
}

/**************************************************************************//**
* \brief   - This function is responsible for SPI Interface test (SPI-2 & SPI-4)
*
* \param   - None
* 			 
* \return  - UINT16
*
*****************************************************************************/
STATUS spi_test(void)
{
    int 	i;
    int	    cnt = 3;
    UINT16	inVal = 0;

    printf("disable /IO_RESET pin to enable devices connected...\n");
    GpioIOResetDis();

    MsDelay(1000);	
    printf("\n* SPI-2 Channel-0  DIGITAL I/O IN TEST: *\n");
    cnt = 3;
    while((cnt--) > 0)
    {
        printf("\nDigital I/O Status(Turn %d):\n", (3 - cnt));
        if(ScDgtGetDinPort(&inVal) != OK)
        {
            return ERROR;
        }
        printf("\tDIN1  DIN2  DIN3  DIN4  DIN5  DIN6  DIN7  DIN8  DIN9 \n\t");
        for(i = 0; i < 9; i++) 
        {
            if(((inVal >> i) & 0x01) == 1 )
                printf(" ON   ");
            else
                printf(" OFF  ");
        }
        printf("\n");
        MsDelay(1000);
    }

    MsDelay(1000);
    printf("\n* SPI-2 Channel-1  DIGITAL I/O OUT TEST: *\n");
    ScDgtSetDoutPort(1, 1);
    MsDelay(1000);
    ScDgtSetDoutPort(2, 1);
    
    MsDelay(1000);
    printf("\n* SPI-4 Channel-0  LOOP D/A - A/D TEST: *\n");		
    ScLoopADDA(DAC_CH_A);
    MsDelay(1000);
    printf("\n* SPI-4 Channel-1  LOOP D/A - A/D TEST: *\n");	
    ScLoopADDA(DAC_CH_B);

    return OK;
}

