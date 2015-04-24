/*
 @file error.h
 !@brief Declara constantes para el manejo de errores
 */

//! Define el tipo de dato 'error' como un entero
#define error int

//! Define constantes para identificar los distintos tipos de errores
#define _ERR_OK 1
#define _ERR_COMAS 2
#define _ERR_TRAMA_CRUDO 3
#define _ERR_TRAMA_NO_FIXED 4
#define _ERR_TIMER 5
#define _ERR_BAUDRATE 6
#define _ERR_DIR 7
#define _ERR_OVF 8
#define _ERR_RXEMPTY 9
#define _ERR_COMMON 10
#define _ERR_TXFULL 11
#define _ERR_DATO 12
#define _ERR_ACK 13
#define _ERR_BUFFER_LLENO 14
#define _ERR_DATO_LLENO 15
#define _ERR_DISTINTO 16
