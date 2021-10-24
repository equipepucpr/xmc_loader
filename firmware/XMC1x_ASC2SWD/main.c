/**************************************************************************
** 								                                                        *
**  INFINEON XMC1000 Bootloader, ASCLoader                                *
**                                                                        *
**  Flash loader program running on XMC1000 board                         *
**                                                                        *
**  DESCRIPTION :                                                         *
**      -Communication with PC via BSL protocol                           *
**      -Implementation of flash functions:         		                  *
**		  -Erase flash                                                      *
**		  -Program flash		                                                *
**      -Read flash       			                                          *
**		  -Change BMI value                                                 *
**		  -Using P1.3 (RX) and P1.2 (TX) for ASC communication              *
**  	                                                                    *
**  VERSION : V1.1							                                          *
**                                                                        *
**  COMPILER: DAVE4 (GCC)                                                 *
**  							                                                        *
**************************************************************************/

/**************************************************************************
 * @file     main.c
 * @brief    Main file for the XMC1000 Bootloader
 *
 * @version  V1.1
 * @date     25 May 2015, DAVE4 project
 *
 * @note
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * @par
 * Infineon Technologies AG (Infineon) is supplying this software for use
 * with Infineon’s microcontrollers. This file can be freely distributed
 * within development tools that are supporting such microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS
 * SOFTWARE.INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
 * INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ***************************************************************************

********************* Version History **************************************
****************************************************************************
V1.0 , May 2013, First version
V1.1 , May 2015, Second version: Read Flash function, Segger rework
***************************************************************************/

#include <XMC1300.h>
#include "xmc1000_flasher.h"
//#include "XMC1000_RomFunctionTable.h"

BYTE HeaderBlock[HEADER_BLOCK_SIZE];
unsigned int DataRx[69] = {0};    // make sure the DataRx[] is 4 byte aligned
BYTE* p;


void SendByte(BYTE data)
{
	while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
	USIC0_CH0->IN[0] = data;

	//while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
    //USIC0_CH1->IN[0] = data;
}

void SendWord(DWORD* BUF)
{
	for (int i=0;i<4;i++)
	{
		while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
		USIC0_CH0->IN[0] = ((*BUF>>8*i) & 0xFF);
		//while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
		//USIC0_CH1->IN[0] = ((*BUF>>8*i) & 0xFF);
	}
}

void Flash_ReadWord(DWORD dwAddr, DWORD* buf)
{
	signed int i;
	unsigned char j;
	unsigned char chksum = 0;
	buf = (DWORD*)dwAddr;
	while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.14
	//while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
	chksum = chksum ^ 0x01;
	USIC0_CH0->IN[0] = 0x01;	//Data type header for P0.14/P0.15
	while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
	//USIC0_CH1->IN[0] = 0x01;	//Data type header for P1.3/P1.2
	//while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
	chksum = chksum ^ 0x04;
	USIC0_CH0->IN[0] = 0x04;	//Read Flash Mode for P0.14/P0.15
//	USIC0_CH1->IN[0] = 0x04;	//Read Flash Mode for P1.3/P1.2
	for (i=3;i>=0;i--)			//Send Read Address
	{
		while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
//		while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
		j = ((dwAddr>>8*i) & 0xFF);
		chksum = chksum ^ j;
		USIC0_CH0->IN[0] = j;					//for P0.14/P0.15
//		USIC0_CH1->IN[0] = j;					//for P1.3/P1.2
	}
	for (i=0;i<4;i++)
	{
		while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
//		while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
		j = (((*buf)>>8*i) & 0xFF);
		chksum = chksum ^ j;
		USIC0_CH0->IN[0] = j;                 // send the 4 byte data for P0.14/P0.15
//		USIC0_CH1->IN[0] = j;                 // send the 4 byte data for P1.3/P1.2
	}
	for (i=0;i<5;i++)
	{
		while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P0.14/P0.15
//		while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty for P1.3/P1.2
		chksum = chksum ^ 0x00;
		USIC0_CH0->IN[0] = 0x00;                 // send the unused 5 bytes for P0.14/P0.15
//		USIC0_CH1->IN[0] = 0x00;                 // send the unused 5 bytes for P1.3/P1.2
	}
	while(!((USIC0_CH0->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty P0.14/P0.15
	USIC0_CH0->IN[0] = chksum;                 // send the checksum
//	while(!((USIC0_CH1->TRBSR & (0x01UL << 11)) >> 11) ) {}; //check if Tx FIFO is empty P1.3/P1.2
//	USIC0_CH1->IN[0] = chksum;                 // send the checksum
	return;
}

void EraseSector(DWORD dwSectorAddr, DWORD dwSize)
{

	// check if it is a valid unsigned long address
	if(dwSectorAddr & 3){
		SendByte(BSL_ADDRESS_ERROR);
		return;
	}

	//***************** Check if sector is already empty ************

	if((dwSize & 0x03) || (dwSize==0)) {
		SendByte(BSL_ERASE_ERROR);
		return;
	}

	while(dwSize>0)
	{
		volatile unsigned long* p=(volatile unsigned long*)(dwSectorAddr);
		unsigned long dw=*p;
//		if(0!=dw)
		if(dw != 0xFFFFFFFF)					// check for programmed word
			break;
		dwSectorAddr+=4;
		dwSize-=4;
	}

	//Sector is empty
	if (dwSize == 0) {
		SendByte(BSL_ERASE_SUCCESS);
		return;
	}
	//**************************************************************

  if(0 == XMC1000_FLASH_EraseSector(dwSectorAddr))
		 SendByte(BSL_ERASE_SUCCESS);
	else
		 SendByte(BSL_ERASE_ERROR);
}


_Bool ProgramFlashPage(DWORD dwPageAddr)
{

	// check if it is a valid page start address
	if(dwPageAddr & XMC1000_FLASH_PAGE_START_MASK)
	{
		SendByte(BSL_ADDRESS_ERROR);
		return 0;
	}

	if(0 != XMC1000_FLASH_ProgramPage(dwPageAddr))
	{
		SendByte(BSL_PROGRAM_ERROR);
		return 0;
	}
	else
	{
		SendByte(BSL_SUCCESS); //send ackn here
		return 1;
	}
}


void ChangeBMI(unsigned short BMI)
{

	// call the change BMI routine
	XMC1000_BmiInstallationReq(BMI);;
}


_Bool WaitForDataBlock(void)
{
	UINT i;
	BYTE chksum = 0;
	p = (BYTE*) &DataRx[0];
	p = p+2;       //set Data pointer to Byte 0 of Data Block

	//First byte
	while(((USIC0_CH0->TRBSR & (0x01UL << 3) ) >> 3)){};  //check RXempty flag for P0.14/P0.15
	*p = (USIC0_CH0->OUTR & 0xFF);
//	while(((USIC0_CH1->TRBSR & (0x01UL << 3) ) >> 3)){};  //check RXempty flag for P1.3/P1.2
//	*p = (USIC0_CH1->OUTR & 0xFF);

	//check for EOT block and return if found
	if (*p == EOT_BLOCK) {
		//read remaining 15 bytes of EOT block from interface
		for (i=1; i<HEADER_BLOCK_SIZE-1; i++)
		{
		    while(((USIC0_CH0->TRBSR & (0x01UL << 3) ) >> 3)){};   //check RXempty flag for P0.14/P0.15
           chksum = chksum ^ (USIC0_CH0->OUTR & 0xFF);
//		    while(((USIC0_CH1->TRBSR & (0x01UL << 3) ) >> 3)){};   //check RXempty flag for P1.3/P1.2
//           chksum = chksum ^ (USIC0_CH1->OUTR & 0xFF);
		}

		while(((USIC0_CH0->TRBSR & (0x01UL << 3) ) >> 3)){};		//for P0.14/P0.15
		//compare checksums
		if (chksum != (USIC0_CH0->OUTR & 0xFF)) {					//for P0.14/P0.15
//		while(((USIC0_CH1->TRBSR & (0x01UL << 3) ) >> 3)){};		//for P1.3/P1.2
//		//compare checksums
//		if (chksum != (USIC0_CH1->OUTR & 0xFF)) {					//for P1.3/P1.2
			SendByte(BSL_CHKSUM_ERROR);
			*p = 0xFF; //make block type invalid
			return 0;
		}

		return 0;
	}

	if (*p != DATA_BLOCK) {
		SendByte(BSL_BLOCK_TYPE_ERROR);
		return 0;
	}

	//remaining 263 bytes
	for (i=1; i<PAGE_SIZE+8; i++)
	{
		while(((USIC0_CH0->TRBSR & (0x01UL << 3) ) >> 3)){};		//for P0.14/P0.15
       *(p+i) = (USIC0_CH0->OUTR & 0xFF);							//for P0.14/P0.15
//		while(((USIC0_CH1->TRBSR & (0x01UL << 3) ) >> 3)){};		//for P1.3/P1.2
 //      *(p+i) = (USIC0_CH1->OUTR & 0xFF);							//for P1.3/P1.2
	}


	for (i=1; i<PAGE_SIZE+7; i++)
	    chksum = chksum ^ *(p+i);

	if (chksum != *(p+PAGE_SIZE+7)) {
		SendByte(BSL_CHKSUM_ERROR);
		return 0;
	}
	return 1;

}


_Bool WaitForHeader(void)
{

	UINT i;
	BYTE chksum = 0;

	for (i=0; i<HEADER_BLOCK_SIZE; i++)
	{

		while(((USIC0_CH0->TRBSR & (0x01UL << 3) ) >> 3))	{};	//receive the header information for P0.14/P0.15
       HeaderBlock[i] = (USIC0_CH0->OUTR & 0xFF);
//while(((USIC0_CH1->TRBSR & (0x01UL << 3) ) >> 3))	{};	//receive the header information for P1.3/P1.2
       //HeaderBlock[i] = (USIC0_CH1->OUTR & 0xFF);

	}

	if (HeaderBlock[0] != HEADER_BLOCK) {
		SendByte(BSL_BLOCK_TYPE_ERROR);
		return 0;
	}

	if ((HeaderBlock[1]!=BSL_PROGRAM_FLASH) &&
		(HeaderBlock[1]!=BSL_ERASE_FLASH) &&
		(HeaderBlock[1]!=BSL_READ_FLASH) &&
		(HeaderBlock[1]!=BSL_CHANGE_BMI)) {
		SendByte(BSL_MODE_ERROR);
		return 0;
	}
	for (i=1; i<HEADER_BLOCK_SIZE-1; i++) {
		chksum = chksum ^ HeaderBlock[i];
	}
	if (chksum != HeaderBlock[HEADER_BLOCK_SIZE-1]) {

		SendByte(BSL_CHKSUM_ERROR);
		return 0;
	}

	return 1;
}


int main(void)
{
	ASC_Init();
	ChangeBMI(0xF8C3);
	for (;;) {
		SendByte(BSL_SUCCESS);
	}
}
