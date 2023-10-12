/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 14/9/2023       ******************/
/************** SWC  : SPI             ******************/
/************** Version : 1.0          ******************/
/********************************************************/
#ifndef SPI_INTERFACE_h
#define SPI_INTERFACE_h

void SPI_VoidInit(void);

u8 SPI_u8TransRecieve(u8 Copy_u8TransmittedByte,u8 *Copy_pu8RecievedByte);

void SPI_voidSlaveSendByte(u8 Copy_u8DataByte);

u8 SPI_u8RecByte(u8 *Copy_pu8RecByte);


#endif
