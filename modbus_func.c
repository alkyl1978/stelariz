#include "mb.h"

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
	USHORT count;
	count=usNRegs<<2;
	while (count)
	{
		*pucRegBuffer++=0;
		 count--;
	}
    return MB_ENOERR;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
	USHORT count;
	count=usNRegs<<2;
    switch(eMode)
    {
      case MB_REG_READ: 
        {
          while (count)
          {
        		*pucRegBuffer++=0;
        		count--;
          }
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

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	*pucRegBuffer=0;
	pucRegBuffer++;
	*pucRegBuffer=0;
    return MB_ENOERR;
}
