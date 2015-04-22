#include "derivative.h"
#include "Error.h"
#include "LED.h"


//* Valor enviado a la funcion CPU_PrenderRTC para que el RTC interrumpa en 1 ms
#define RTC_1MS       0x08
//* Valor enviado a la funcion CPU_PrenderRTC para que el RTC interrumpa en 
#define RTC_MED       0x0E
//* Valor enviado a la funcion CPU_PrenderRTC para que el RTC interrumpa en 1 s
#define RTC_1SEG      0x0D
//* Valor enviado a la funcion CPU_PrenderRTC para que el RTC interrumpa en 1 m
#define RTC_1MIN      0x00

//! Utilizada para indicar que un paquete recibido en el transceiver es del tipo dato
#define flag_dato   0x00  //  00000000
//! Utilizada para indicar que un paquete recibido en el transceiver es el ultimo
#define flag_ultimo 0x01  //  00000001
//! Utilizada para indicar que un paquete enviado a traves del transceiver es del tipo ack
#define flag_ack      0x02    //  00000010
//! Utilizada para indicar que un paquete recibido en el transceiver es un paquete proveniente de un dispositivo que entro en proceso de muerte
#define flag_muerte 0x04  //  00000100
//! Utilizada para indicar que un paquete recibido en el transceiver es el primero
#define flag_inicio 0x08  //  00001000
//! Utilizada para indicar que un paquete enviado a traves del transceiver es del tipo turno
#define flag_turno    0x0C    //  00010000

//! Indica el tamaño del paquete. id: 1 byte, flag: 1 byte, nrosec: 1 byte, payload: 31 bytes, checksum: 1 byte 
#define tam_paquete 35      //Antes 33
//! Indica el tamaño del dato con id. id: 1 byte, payload: 31 bytes
#define tam_datoconid 32    //Antes 30
//! Indica el tamaño del dato. payload: 31 bytes, checksum: 1 byte
#define tam_dato 32
//! Cantidad de datos maxima almacenados en el buffer de escritura previo a la escritura en la sd.
#define cantidad_datos 16   //antes 14 //Antes 15
/*#define Pin_GetVal() ( \
    (bool)((getReg8(PTAD) & 0x40))       \
  )*/
//! Cantidad de dispositivos moviles en funcionamiento. Utilizado en el momento de enviar turnos para la transmision de datos
#define CANT_DISP 0x11
//#define CORRIENDO 0
//#define FIN       1

//! La variable ban_transceiver tomara este valor cuando el transceiver no haya recibido un dato nuevo 
#define Buffer_Vacio 3

//!La variable ban_transceiver tomara este valor cuando el transceiver haya recibido un dato nuevo
#define HAYPAQUETE	4

extern byte nro_sec;


//! Inicializacion del CPU

error Init_CPU(void);

//! Produce un delay de 100uS multiplicado por el valor recibido

void Cpu_Delay100US(word);

//! Permite iniciar el RTC
/*!
    @param[in]
    @li @c modifica RTCSC
    @li @c modifica RTCMOD

    Configuracion del RTC
        RTIF=1: This status bit indicates the RTC counter register reached the value in the RTC modulo register.
                Writing a logic 1 clears the bit and the real-time interrupt request.
        RTCLKS=00: Real-Time Clock Source Select. 00 Real-time clock source is the 1-kHz low power oscillator (LPO)
        RTIE=1: Real-Time Interrupt Enable. 1 Real-time interrupt requests are enabled.
        RTCPS=pasado en variable: Real-Time Clock Prescaler Select. These four read/write bits select binary-based or decimal-based divide-by
values for the clock source.

    RTCSC=0x80; NO DEBERIA SER 0x90?
*/

void CPU_PrenderRTC(byte,byte);

//! Permite deshabilitar el RTC
/*!
    Se deshabilitan las interrupciones del RTC (RTIE=0)
    RTCSC=0x80
*/

void CPU_ApagarRTC(void);
