/*
 @file cpu.c
 !@brief Define variables e implementa funciones necesarias para el manejo del cpu
 */

//#pragma MESSAGE DISABLE C5703 

#include "derivative.h"
#include "cpu.h"
//#include "Error.h"

//byte ban_TxTurno;
//byte ban_Turno;
byte timer_turno;
int c;
//int d;

extern int index_col;
extern byte Buffer_Rx[tam_paquete]; 
extern byte ban_transceiver;


error Init_CPU(void){
    SOPT1 = 0x23;      // SOPT1: COPE=0,COPT=1,STOPE=1,??=0,??=0,??=0,BKGDPE=1,RSTPE=1                
    SOPT2 = 0x10;      // SOPT2: COPCLKS=0,??=0,??=0,SPIFE=1,SPIPS=0,ACIC2=0,IICPS=0,ACIC1=0                
    SPMSC1 = 0x1C;     // SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=1,??=0,BGBE=0               
    SPMSC2 = 0x02;     // SPMSC2: LPR=0,LPRS=0,LPWUI=0,??=0,PPDF=0,PPDACK=0,PPDE=1,PPDC=0
    SPMSC3 = 0x00;     // SPMSC3: LVDV=0,LVWV=0,LVWIE=0    
    //  System clock initialization
    if (*(unsigned char*)0xFFAF != 0xFF) { // Test if the device trim value is stored on the specified address
        ICSTRM = *(unsigned char*)0xFFAF;  // Initialize ICSTRM register from a non volatile memory
        ICSSC = (unsigned char)((*(unsigned char*)0xFFAE) & (unsigned char)0x01); // Initialize ICSSC register from a non volatile memory
    }
    // ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=1
    ICSC1 = 0x07;                        // Initialization of the ICS control register 1 
    // ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0
    ICSC2 = 0x00;                        // Initialization of the ICS control register 2
    while(!ICSSC_IREFST) {               // Wait until the source of reference clock is internal clock
    }
    // ICSSC: DRST_DRS=1,DMX32=0
    ICSSC = 0x40;   // Initialization of the ICS status and control 
    while((ICSSC & 0xC0) != 0x40) {      // Wait until the FLL switches to High range DCO mode 
    }
    // Configuracion del RTC
    // RTIF=1, RTCLKS=11, RTIE=1, RTCPS=0110
    //RTCSC =0xF6;
    // RTCMOD=0x01
    //RTCMOD=0x0A;
    //ban_TxTurno=CORRIENDO;
    //ban_Turno=FIN;
    timer_turno=4;
    c=0;
    //d=0;
    return _ERR_OK;
}


void Cpu_Delay100US(word us100){
    asm{
        loop:
          // 100 us delay block begin
          //
          // Delay
          //   - requested                  : 100 us @ 16MHz,
          //   - possible                   : 1600 c, 100000 ns
          //   - without removable overhead : 1592 c, 99500 ns
          pshh                               // (2 c: 125 ns) backup H
          pshx                               // (2 c: 125 ns) backup X
          ldhx #$00C5                        // (3 c: 187.5 ns) number of iterations
          label0:
          aix #-1                            // (2 c: 125 ns) decrement H:X
          cphx #0                            // (3 c: 187.5 ns) compare it to zero
          bne label0                         // (3 c: 187.5 ns) repeat 197x
          pulx                               // (3 c: 187.5 ns) restore X
          pulh                               // (3 c: 187.5 ns) restore H
          nop                                // (1 c: 62.5 ns) wait for 1 c
          nop                                // (1 c: 62.5 ns) wait for 1 c
          nop                                // (1 c: 62.5 ns) wait for 1 c
          // 100 us delay block end
          aix #-1                            // us100 parameter is passed via H:X registers
          cphx #0
          bne loop                           // next loop
          rts
    }
}


void CPU_PrenderRTC(byte cps,byte modulo){
    // Configuracion del RTC
    // RTIF=1, RTCLKS=00, RTIE=1, RTCPS=pasado en variable
    //RTCSC=0x80;
    RTCSC =0x90 | (cps & 0x0F);
    RTCMOD=(byte)modulo;
}

void CPU_ApagarRTC(){
  RTCSC=0x80;
}

interrupt VectorNumber_Vrtc void ISR_RTC(void){
    
    RTCSC = RTCSC | 0x80;   //limpiamos la bandera de interrupcion.
        
    timer_turno--;
    
    index_col=0;
             
}

interrupt VectorNumber_Vsci2rx void ISR_TRANSCEIVER(void){
    error result=0;
       
    timer_turno=4;
    
    (void)SCI2S1;

    Buffer_Rx[index_col]=SCI2D; // guardamos los bytes recibidos
    index_col++;
    if(index_col==tam_paquete){
    	ban_transceiver=HAYPAQUETE;
    	LED_BrillarV(1,300);
    	index_col=0;
    	c++;
    	if(c==16)
    		c=0;
    	
    }
    
}

interrupt VectorNumber_Vsci2err void ISR_OVR(void){
	(void)SCI2S1;
	(void)SCI2D;
}
