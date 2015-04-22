//**************************   INCLUDES   *******************************


//#include "Init.h"
#include "derivative.h"
#include "Error.h"
#include "CPU.h"
#include "LED.h"
#include "SD.h"

//*************************   DEFINICIONES   ****************************


#define TIMERACK 10
#define ACK 65
#define TIMER_DATO 10 
#define POS_LAT 15
#define POS_LONG 25





//**************************   FUNCIONES   ******************************

//! Inicializacion del Transceiver

error Init_Trans(void);

//! Coloca un 1 en la pata SET

error Transceiver_SetAlto(void);

//! Coloca un 0 en la pata SET

error Transceiver_SetBajo(void);

//! Prende el transceiver
/*! Coloca un "1" en PTAD_PTAD1 que está conectado al Enable del Transceiver*/

error Transceiver_Prender(void);

//! Apaga el transceiver
/*! Coloca un "0" en PTAD_PTAD1 que está conectado al Enable del Transceiver*/

error Transceiver_Apagar(void);

//! Permite transmitir un caracter
/*!
    @param[in]
    @li @c Recibe el caracter que se desea transmitir

    SCI2S1: This register has eight read-only status flags.
        _TDRE:  Transmit Data Register Empty Flag — TDRE is set out of reset and when a transmit data value transfers from
        (bit7)  the transmit data buffer to the transmit shifter, leaving room for a new character in the buffer. To clear TDRE,
                read SCIxS1 with TDRE = 1 and then write to the SCI data register (SCIxD).
                    0 Transmit data register (buffer) full.
                    1 Transmit data register (buffer) empty.
        _TC:    Transmission Complete Flag — TC is set out of reset and when TDRE = 1 and no data, preamble, or break
        (bit6)      character is being transmitted.
                    0 Transmitter active (sending data, a preamble, or a break).
                    1 Transmitter idle (transmission activity complete).
                TC is cleared automatically by reading SCIxS1 with TC = 1 and then doing one of the following three things:
                    • Write to the SCI data register (SCIxD) to transmit new data
                    • Queue a preamble by changing TE from 0 to 1
                    • Queue a break character by writing 1 to SBK in SCIxC2

    SCI2D:  SCI Data Register (SCIxD) This register is actually two separate registers. Reads return the contents of the
            read-only receive data buffer and writes go to the write-only transmit data buffer. Reads and writes of this register
            are also involved in the automatic flag clearing mechanisms for the SCI status flags

    La función consiste en:
        Cargar el byte en SCI2D
        Esperar que el buffer se vacie
        Esperar que se complete la transmision
*/

error Transceiver_EnviarByte(byte);

//! Permite recibir un caracter
/*!
    SCI2S1_RDRF (bit5): Receive Data Register Full Flag — RDRF becomes set when a character transfers from the receive shifter
                        into the receive data register (SCIxD). To clear RDRF, read SCIxS1 with RDRF = 1 and then read the SCI
                        data register (SCIxD).
                            0 Receive data register empty.
                            1 Receive data register full.

    La función consiste en:
        Controlar si se recibio un dato
        Copiar el caracter desde SCI2D

*/

error Transceiver_RecibirByte(byte *);

//error Transceiver_Enviar(dato buf[][tam_dato]);

//! Permite recibir datos transmitidos por los moviles
/*!
 	 Se va almacenando en un buffer los bytes recibidos en el registro SCI2D, hasta que se alcanza el tamaño de datos definido
 	 @param[in] buf buffer donde se ira almacenando el dato
 	 @return Indica si hubo un error
    	@li @c 15 El dato esta completo
    	@li @c 1 El dato todavia no se completo
 */

error Transceiver_Recibir(byte buf[tam_dato]);

//! Envia ACK de una determinada trama recibida
/*!
 	 Se envia el id del movil, el flag de ACK, el numero de secuencia del paquete y se completa la trama con 0xFF
 	 @param[in] id del movil
 	 @param[in] nro_sec del paquete perteneciente a la trama de datos
 */

error Transceiver_EnviarACK(byte,byte);

//error Transceiver_RecibirACK(void);


//error Transceiver_EnviarERROR(void);

//! Realiza el control para saber si el dato recibido es correcto o no

error Transceiver_ControlarDato(void);

//! Control del paquete recibido
/*!
  Cotrola si el paquete nuevo tiene un numero de secuencia distinto al ultimo recibido, si es asi, se escribe el dato nuevo
  en un buffer de escritura. Cuando este ultimo se llena, se escribe el buffer en la tarjeta SD
 	 @return Indica si hubo un error
    	@li @c 13 El dato es incorrecto
    	@li @c 1 No hubo error
 */

error Transceiver_ControlarPaquete(void);

//! Se encarga de enviar turnos para transmision
/*!
   Envia id, flag de turno y numero de secuencia (0x00), el resto del paquete se completa con 0xCD
   Cada nueva llamada a la funcion envia un turno diferente
 */

error Transceiver_EnviarTurno(void);
