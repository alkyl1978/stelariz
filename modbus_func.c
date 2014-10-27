#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "include/servo.h"
#include "include/led.h"
#include "include/dvig.h"
#include "include/dat_scor.h"
#include "mb.h"


extern volatile unsigned int serv_X_Angle;
extern volatile unsigned int serv_Y_Angle;
extern volatile unsigned int serv_Z_Angle;

extern volatile unsigned long serv_X_0;
extern volatile unsigned long serv_Y_0;
extern volatile unsigned long serv_Z_0;

volatile unsigned char flag;

eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
   switch(eMode)
    {
      case MB_REG_READ: 
        {
          *pucRegBuffer=flag;
          break;
        }
    case MB_REG_WRITE:
      {
    	  flag=*pucRegBuffer;
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
	USHORT count,usAddr;
	count=usNRegs;
	usAddr=usAddress;
    switch(eMode)
    {
      case MB_REG_READ: 
        {
          while(count)
          {
        	if(usAddr==1)
        	{
        		*pucRegBuffer++=(serv_X_Angle>>8)&0xff;
        	    *pucRegBuffer++=serv_X_Angle&0xff;
        	}
        	if(usAddr==2)
        	{
        	    *pucRegBuffer++=(serv_Y_Angle>>8)&0xff;
        	    *pucRegBuffer++=serv_Y_Angle&0xff;
        	}
        	if(usAddr==3)
        	{
        	    *pucRegBuffer++=(serv_Z_Angle>>8)&0xff;
        	    *pucRegBuffer++=serv_Z_Angle&0xff;
        	}
        	count--;
        	usAddr++;
          }
          break;
        }
    case MB_REG_WRITE:
      {

    	  while (count)
    	  {
    	  if(usAddr==1)
    	  {
    		  serv_X_Angle=*pucRegBuffer>>8;
    		  pucRegBuffer++;
    		  serv_X_Angle|=*pucRegBuffer&0xff;
    		  pucRegBuffer++;
    		  serv_X_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_X_Angle;
    		   ROM_TimerMatchSet(SERV_X_TIMER_BASE, SERV_X_TIMER, serv_X_0);
    	  }
    	  if(usAddr==2)
    	  {
    		  serv_Y_Angle=*pucRegBuffer>>8;
    		  pucRegBuffer++;
    		  serv_Y_Angle|=*pucRegBuffer&0xff;
    		  pucRegBuffer++;
    		  serv_Y_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Y_Angle;
    		  ROM_TimerMatchSet(SERV_Y_TIMER_BASE, SERV_Y_TIMER, serv_Y_0);
    	  }
    	  if(usAddr==3)
    	  {
    		  serv_Z_Angle=*pucRegBuffer>>8;
    		  pucRegBuffer++;
    		  serv_Z_Angle|=*pucRegBuffer&0xff;
    		  pucRegBuffer++;
    		  serv_Z_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Z_Angle;
    		  ROM_TimerMatchSet(SERV_Z_TIMER_BASE, SERV_Z_TIMER, serv_Z_0);
    	  }
    	  count--;
    	  usAddr++;
    	  }
          break;
      }
    }
    return MB_ENOERR;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOERR;
}
