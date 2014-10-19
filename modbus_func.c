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
          break;
        }
    case MB_REG_WRITE:
      {
          break;
      }
    }
   return MB_ENOERR;
}


eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    return MB_ENOERR;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    switch(eMode)
    {
      case MB_REG_READ: 
        {
          break;
        }
    case MB_REG_WRITE:
      {
          break;
      }
    }
    adres=usAddress;
    reg=usNRegs;
    return MB_ENOERR;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOERR;
}
