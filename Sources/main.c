/*
 @file main.c
 !@brief 
 */

#include <hidef.h>
#include "derivative.h"
#include "error.h"
#include "cpu.h"
#include "led.h"
#include "sd.h"
#include "transceiver.h"
   
//! Define una constante utilizada como parametro en la funcion Cpu_Delay100US 
#define UNSEG 10000

//! Buffer donde se iran almacenando los datos recibidos desde el transceiver para luego escribirlos en la sd
UINT8 Buffer_Escritura[cantidad_datos][tam_datoconid]; // Vector para la transmision
//! Buffer de recepción que almacena un dato recibido desde el transceiver
byte Buffer_Rx[tam_paquete]; // vectores para recepcion de datos
//! Bandera que informa si hay un dato disponible en el buffer de recepcion
byte ban_transceiver/*, ban_sd*/;
//! Variable que indica el valor del numero de secuencia del paquete que se recibio
byte nro_sec;

extern byte timer_turno;

void main(void) {  
    error temp=0, escribir=0;                   
    long intentos=0;
    
//---Inicializacion---//    
    ban_transceiver=Buffer_Vacio;
    //ban_sd=Buffer_Vacio;
    temp=Init_CPU();
    temp=Init_Trans();
    //temp=Init_SD();
    temp=Init_LED();
    temp=Transceiver_Prender(); 
    //temp=SD_Prender();
    temp=(error) SD_Init();
    LED_BrillarR(2,UNSEG);
    LED_BrillarV(2,UNSEG);
    EnableInterrupts;
    CPU_PrenderRTC(RTC_1SEG,5);
    timer_turno=0;
    
//---Comienza el trabajo---// 
    
    for(;;){
    	EnableInterrupts;
        if(timer_turno==0){    // transmitimos 1 turno cada 2seg si no hay ninguna conexion activa.
            nro_sec=0;
            timer_turno=1;
            (void)Transceiver_EnviarTurno();
        }
        if(ban_transceiver==HAYPAQUETE){
        	DisableInterrupts;
        	ban_transceiver=Buffer_Vacio;
        	if(Transceiver_ControlarPaquete()==_ERR_OK)
        		(void)Transceiver_EnviarACK(Buffer_Rx[0],Buffer_Rx[2]);
            else
            	intentos++;
            EnableInterrupts;
        }
        __RESET_WATCHDOG();
    }
}
