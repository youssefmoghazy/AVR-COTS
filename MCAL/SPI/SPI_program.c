/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 14/9/2023       ******************/
/************** SWC  : SPI             ******************/
/************** Version : 1.0          ******************/
/********************************************************/

#include "../../lib/BIT_Math/BIT_MATH.h"
#include "../../lib/STD_TYPES/STD_TYPES.h"
#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"

void SPI_VoidInit(void)
{
	#if(SPI_u8_MODE==SPI_u8_MASTER_MODE)
	/*Data order =MSB first */
	CLR_BIT(SPI_u8_SPCR_REG,DORD);
	/*CHOOSE CLOCK POLARTY AND CLOCK PHASE=>FALLING,RAISING / SETUP ,SAMPLE */
	SET_BIT(SPI_u8_SPCR_REG,CPOL);
	SET_BIT(SPI_u8_SPCR_REG,CPHA);
	/*SELECT MASTER MODE */
	SET_BIT(SPI_u8_SPCR_REG,MSTR);
	/*SELECT CLK => FOCS/64 */
	SET_BIT(SPI_u8_SPCR_REG,SPR1);
	CLR_BIT(SPI_u8_SPCR_REG,SPR0);
	CLR_BIT(SPI_u8_SPSR_REG,0);
	#elif(SPI_u8_MODE==SPI_u8_SLAVE_MODE)
	/*Data order =MSB first */
	CLR_BIT(SPI_u8_SPCR_REG,DORD);
	/*CHOOSE CLOCK POLARTY AND CLOCK PHASE=>FALLING,RAISING / SETUP ,SAMPLE */
	SET_BIT(SPI_u8_SPCR_REG,CPOL);
	SET_BIT(SPI_u8_SPCR_REG,CPHA);
	/*SELECT SLAVE MODE */
	CLR_BIT(SPI_u8_SPCR_REG,MSTR);
//select clock prescaler
	SET_BIT(SPI_u8_SPCR_REG,SPR1);
	CLR_BIT(SPI_u8_SPCR_REG,SPR0);
	CLR_BIT(SPI_u8_SPSR_REG,0);
	#endif
	/*ENABLE SPI*/
	SET_BIT(SPI_u8_SPCR_REG,SPE);
}

u8 SPI_u8TransRecieve(u8 Copy_u8TransmittedByte,u8 *Copy_pu8RecievedByte)
{
	u8 Local_u8Errorstate= STD_TYPES_NOK;
	if(Copy_pu8RecievedByte!=NULL)
	{
		/*SEND BYTE*/
		SPI_u8_SPDR_REG=Copy_u8TransmittedByte;
		/*CHECK IF THE TRANSMISSION IS COMPLETED */
		while((GET_BIT(SPI_u8_SPSR_REG,SPIF))==0);
		/* READ BYTE */
		*Copy_pu8RecievedByte=SPI_u8_SPDR_REG;
		Local_u8Errorstate=STD_TYPES_OK;
	}
	return Local_u8Errorstate;
}

void SPI_voidSlaveSendByte(u8 Copy_u8DataByte)
{
	SPI_u8_SPDR_REG=Copy_u8DataByte;
}

u8 SPI_u8RecByte(u8 *Copy_pu8RecByte)
{
	u8 Local_u8Errorstate= STD_TYPES_NOK;
	if(Copy_pu8RecByte!=NULL)
	{
		/*CHECK IF THE TRANSMISSION IS COMPLETED */
		while((GET_BIT(SPI_u8_SPSR_REG,SPIF))==0);
		/*READ DATA*/
		*Copy_pu8RecByte=SPI_u8_SPDR_REG;

		Local_u8Errorstate=STD_TYPES_OK;
	}

	return Local_u8Errorstate;
}
