#include "mb.h"
USHORT adres;
USHORT reg;

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
   switch(eMode)
    {
      case MB_REG_READ: 
        {
        *pucRegBuffer=0;
        pucRegBuffer++;
        *pucRegBuffer=0;
          break;
        }
    case MB_REG_WRITE:
      {
    	  *pucRegBuffer=0;
    	  pucRegBuffer++;
    	  *pucRegBuffer=0;
          break;
      }
    }
   return MB_ENOERR;
}


eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	*pucRegBuffer=0;
	pucRegBuffer++;
	*pucRegBuffer=0;
    return MB_ENOERR;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    switch(eMode)
    {
      case MB_REG_READ: 
        {
        	*pucRegBuffer=0;
        	pucRegBuffer++;
        	*pucRegBuffer=0;
          break;
        }
    case MB_REG_WRITE:
      {
    	  *pucRegBuffer=0;
    	  pucRegBuffer++;
    	  *pucRegBuffer=0;
          break;
      }
    }
    adres=usAddress;
    reg=usNRegs;
    return MB_ENOERR;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	*pucRegBuffer=0;
	pucRegBuffer++;
	*pucRegBuffer=0;
    return MB_ENOERR;
}
