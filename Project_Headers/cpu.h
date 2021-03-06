/*!
 @file cpu.h
 @brief Declara constantes y funciones para el manejo del cpu
 */
#ifndef CPU_H
#define CPU_H

#include "derivative.h"
#include "error.h"
#include "led.h"

//* Constantes enviadas a la funcion CPU_PrenderRTC y determinan en que tiempo el RTC interrumpe
#define RTC_1MS       0x08
#define RTC_MED       0x0E
#define RTC_1SEG      0x0F
#define RTC_1MIN      0x00

//* Constantes utilizadas para indicar el tipo de paquete transmitido o recibido por el transceiver
#define flag_dato	  	0x00  	//  00000000
#define flag_ultimo		0x01  	//  00000001
#define flag_ack      	0x02 	//  00000010
#define flag_muerte 	0x04  	//  00000100
#define flag_inicio 	0x08  	//  00001000
#define flag_turno    	0x0C 	//  00010000

//! Indica el tama�o del paquete. id: 1 byte, flag: 1 byte, nrosec: 1 byte, payload: 31 bytes, checksum: 1 byte 
#define tam_paquete 35      //Antes 33
//! Indica el tama�o del dato con id. id: 1 byte, payload: 31 bytes
#define tam_datoconid 32    //Antes 30
//! Indica el tama�o del dato. payload: 31 bytes, checksum: 1 byte
#define tam_dato 32
//! Cantidad de datos maxima almacenados en el buffer de escritura previo a la escritura en la sd.
#define cantidad_datos 16   //antes 14 //Antes 15
/*#define Pin_GetVal() ( \
    (bool)((getReg8(PTAD) & 0x40))       \
  )*/
//! Cantidad de dispositivos moviles en funcionamiento. Utilizado en el momento de enviar turnos para la transmision de datos
#define CANT_DISP 0x12
//#define CORRIENDO 0
//#define FIN       1

//! La variable ban_transceiver tomara este valor cuando el transceiver no haya recibido un dato nuevo 
#define Buffer_Vacio 3
//!La variable ban_transceiver tomara este valor cuando el transceiver haya recibido un dato nuevo
#define HAYPAQUETE	4

//extern byte nro_sec;


//! Inicializacion del CPU
/*
 Configura regsitros SOPT1, SOPT1, SPMSC1, SPMSC2, SPMSC3. Configura el clock. Inicializa variables globales
 @return 1 _ERR_OK Se inicializo correctamente
 */
error Init_CPU(void);

//! Produce un delay
/*
 Produce un delay de 100uS multiplicado por el valor recibido como parametro
 @param[in] us100 Indica el multiplicador que definira la longitud del delay 
 */
void Cpu_Delay100US(word);

//! Permite iniciar el RTC
/*! Se configura el RTC de la siguiente manera:
        RTIF=1: This status bit indicates the RTC counter register reached the value in the RTC modulo register.
                Writing a logic 1 clears the bit and the real-time interrupt request.
        RTCLKS=00: Real-Time Clock Source Select. 00 Real-time clock source is the 1-kHz low power oscillator (LPO)
        RTIE=1: Real-Time Interrupt Enable. 1 Real-time interrupt requests are enabled.
        RTCPS=pasado en variable: Real-Time Clock Prescaler Select. These four read/write bits select binary-based or decimal-based divide-by values for the clock source.
    @param[in] cps modifica la parte baja del RTCSC que corresponde al Clock Prescaler Select
    @param[in] modulo modifica RTCMOD
*/
void CPU_PrenderRTC(byte,byte);

//! Permite deshabilitar el RTC
/*!
    Se deshabilitan las interrupciones del RTC (RTIE=0)
    RTCSC=0x80
*/
void CPU_ApagarRTC(void);
#endif
