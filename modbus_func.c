#include "mb.h"
USHORT adres;
USHORT reg;
#define REG_COILS_START     1000
#define REG_COILS_SIZE      16

static unsigned char ucRegCoilsBuf[REG_COILS_SIZE / 8];


eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
  unsigned short  usBitOffset;
  short           iNCoils = ( short )usNCoils;
  if( ( usAddress >= REG_COILS_START ) && ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
   {
    usBitOffset = ( unsigned short )( usAddress - REG_COILS_START ); 
    switch(eMode)
      {
        case MB_REG_READ: 
          {
            while( iNCoils > 0 )
                {
                   *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,( unsigned char )( iNCoils >8 ? 8 :iNCoils ) );
                    iNCoils -= 8;
                    usBitOffset += 8;
                }

            break;
          }
        case MB_REG_WRITE:
        {
           while( iNCoils > 0 )
                {
                   xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,( unsigned char )( iNCoils > 8 ? 8 : iNCoils ),*pucRegBuffer++ );
                    iNCoils -= 8;
                }

            break;
        }
      }
   }
   return MB_ENOREG;
}


eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    return MB_ENOREG;
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
    return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
