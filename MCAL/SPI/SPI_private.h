/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 14/9/2023       ******************/
/************** SWC  : DIO             ******************/
/************** Version : 1.0          ******************/
/********************************************************/
#ifndef SPI_PRIVATE_h
#define SPI_PRIVATE_h

#define SPI_u8_SPDR_REG			*((volatile u8*)0x2F)

#define SPI_u8_SPSR_REG			*((volatile u8*)0x2E)

#define SPI_u8_SPCR_REG			*((volatile u8*)0x2D)

#define SPI_u8_MASTER_MODE		1
#define SPI_u8_SLAVE_MODE		2
/****************************SPI Control Register – SPCR*******************************/
#define SPIE					7	/*SPI Interrupt Enable*/
/*This bit causes the SPI interrupt to be executed if SPIF bit in the SPSR Register is set
*and the if the global interrupt enable bit in SREG is set.*/

#define SPE						6	/*SPI Enable*/
/*When the SPE bit is written to one, the SPI is enabled. This bit must be set to enable
*any SPI operations.*/

#define DORD					5	/*Data Order*/
/*When the DORD bit is written to one, the LSB of the data word is transmitted first.
*When the DORD bit is written to zero, the MSB of the data word is transmitted first.*/

#define	MSTR					4	/*MSTR: Master/Slave Select*/
#define CPOL					3	/*Clock Polarity*/
#define CPHA					2	/*Clock Phase*/
#define SPR1					1	/*SPR1, SPR0: SPI Clock Rate Select 1 and 0*/
#define SPR0					0
/*************************************************************************************/
/*****************************SPI Status Register – SPSR******************************/

#define SPIF					7	/*SPIF: SPI Interrupt Flag*/
#define WCOL					6	/*WCOL: Write COLlision Flag*/
#define SPI2X					0	/*SPI2X: Double SPI Speed Bit*/

/*************************************************************************************/

#endif
