/*!
 @file transceiver.h
 @brief Declara constantes y funciones para el manejo del transceiver
 */

#include "derivative.h"
#include "error.h"
#include "cpu.h"
#include "led.h"
#include "sd.h"

//! Define la posicion en que se encuentra LAT en el vector que guarda el dato
#define POS_LAT 15
//! Define la posicion en que se encuentra LONG en el vector que guarda el dato
#define POS_LONG 25

//! Define la direccion de la pata del micro conectada al set del transceiver
#define TransceiverSet_Direccion PTADD_PTADD0
//! Define la pata del micro conectada al set del transceiver
#define TransceiverSet PTAD_PTAD0
//! Define la direccion de la pata del micro conectada al enable del transceiver
#define TransceiverEnable_Direccion PTADD_PTADD1
//! Define la pata del micro conectada al enable del transceiver
#define TransceiverEnable PTAD_PTAD1

//! Inicializacion del Transceiver
/*!
 Configura el puerto serial mediante registros SCIxBDH, SCIxC1, SCIxC2, SCIxC3. 
 Configura pins de set y enable como salida. Configura set en bajo y enable en alto
 Configura los parametros del transceiver f=455MHz, Data Rate 9600bps, output power 100mw, UART data rate 9600bps, no checkout
 @return Indica si los parametros del transceiver se configuraron correctamente
 	 @li @c 1 _ERR_OK Los parametros del transceiver se configuraron correctamente
 	 @li @c 16 _ERR_DISTINTO Los parametros del transceiver no se configuraron correctamente
 */
error Init_Trans(void);

//! Coloca un 1 en la pata Set del Transceiver
/*!
 @return 1 _ERR_OK
 */
error Transceiver_SetAlto(void);

//! Coloca un 0 en la pata Set del Transceiver
/*!
 @return 1 _ERR_OK
 */
error Transceiver_SetBajo(void);

//! Prende el transceiver
/*! 
Coloca un "1" en el Enable y un '1' en el Set del Transceiver
@return 1 _ERR_OK
*/
error Transceiver_Prender(void);

//! Apaga el transceiver
/*! 
Coloca un "0" en el Enable y un '0' en el Set del Transceiver
@return 1 _ERR_OK
*/
error Transceiver_Apagar(void);

//! Permite transmitir un caracter
/*!
Carga el dato a transmitir en el registro SCI2D. Espera a que el buffer se vacie. Espera a que la transmision se complete
@param[in] byte Recibe el caracter que se desea transmitir
@return 1 _ERR_OK
*/
error Transceiver_EnviarByte(byte);

//! Permite recibir un caracter
/*! Controla el bit SCI2S1_RDRF para saber si hay un dato en el buffer de recepcion. Si hay un dato lo almacena.
@param[out] Rxdat Almacena el byte recibido
@return Indica si hubo un dato en el buffer de recepcion
	@li @c 1 _ERR_OK Habia un dato y se guardo
	@li @c 9 _ERR_RXEMPTY No habia un dato
*/
error Transceiver_RecibirByte(byte *);

//error Transceiver_Enviar(dato buf[][tam_dato]);

//! Permite recibir datos transmitidos por los moviles
/*!
 	 Se va almacenando en un buffer los bytes recibidos en el registro SCI2D, hasta que se alcanza el tamaño de datos definido
 	 @param[out] buf buffer donde se ira almacenando el dato
 	 @return Indica si hubo un error
    	@li @c 15 El dato esta completo
    	@li @c 1 El dato todavia no se completo
 */
//error Transceiver_Recibir(byte buf[tam_dato]);

//! Envia ACK de una determinada trama recibida
/*!
 	 Se envia el id del movil, el flag de ACK, el numero de secuencia del paquete y se completa la trama con 0xFF
 	 @param[in] id del movil
 	 @param[in] nro_sec del paquete perteneciente a la trama de datos
 */
error Transceiver_EnviarACK(byte,byte);

//! Realiza el control para saber si el dato recibido es correcto o no
/*
Realiza un control del checksum
@return Indica si el checksum es correcto o no 
	@li @c 1 _ERR_OK El checksum es correcto
	@li @c 12 _ERR_DATO El checksum no es correcto
 */
error Transceiver_ControlarDato(void);

//! Control del paquete recibido
/*!
Cotrola si el paquete nuevo tiene un numero de secuencia distinto al ultimo recibido, si es asi, controla que el dato sea correcto y lo escribe
en un buffer de escritura. Cuando este ultimo se llena, se escribe el buffer en la tarjeta SD
@return Indica si hubo un error
    	@li @c 13 _ERR_ACK El dato es incorrecto
    	@li @c 1 _ERR_OK No hubo error
 */
error Transceiver_ControlarPaquete(void);

//! Se encarga de enviar turnos para transmision
/*!
   Envia id, flag de turno y numero de secuencia (0x00), el resto del paquete se completa con 0xCD
   Cada nueva llamada a la funcion envia un turno diferente y titila el led rojo
   @return 1 _ERR_OK
 */
error Transceiver_EnviarTurno(void);
