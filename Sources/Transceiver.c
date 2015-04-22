#include "Transceiver.h"


int index_col;
int index_fil;

extern byte Buffer_Rx[tam_paquete];
extern UINT8 Buffer_Escritura[cantidad_datos][tam_datoconid];
extern byte dir_escritura[4];
//extern byte ban_sd;

error Init_Trans(void){
    byte i, CadenaInit[19]="WR 455000 3 9 3 0\r\n"; //configuracion del transceiver f=455MHz, Data Rate 9600bps, output power 100mw
    												//UART data rate 9600bps, no checkout
    SCI2BDH = 0x00;
    SCI2BDL = 0x6D;
    // SCIC1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0
    SCI2C1 = 0x00;                // Configure the SCI
    // SCIC3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=1,NEIE=0,FEIE=0,PEIE=0
    SCI2C3 = 0x08;                // Disable error interrupts
    // SCIC2: TIE=0,TCIE=0,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0
    SCI2C2 = 0x2C;
    // PIN set como salida
    PTADD_PTADD0 = 1;
    // PIN enable comosalida
    PTADD_PTADD1 = 1;
    
    (void) Transceiver_Prender();
    (void) Transceiver_SetBajo();
    
    for(i=0; i<19; i++){
    	(void)Transceiver_EnviarByte(CadenaInit[i]);
    }
    
    while(SCI2S1_RDRF == 0x00){
    	asm{
    		NOP
    	}
    }
    
    return _ERR_OK;
}

//***********************************************************************   TRANSCEIVER_SETALTO
  

error Transceiver_SetAlto(){
    PTAD_PTAD0 = 1;

    return _ERR_OK;
}


//***********************************************************************   TRANSCEIVER_SETBAJO


error Transceiver_SetBajo(){
    PTAD_PTAD0 = 0;
    return _ERR_OK;
}


//***********************************************************************   TRANSCEIVER_PRENDER


error Transceiver_Prender(){
     PTAD_PTAD1 = 1; //Enable 1
    return Transceiver_SetAlto();
}


//***********************************************************************   TRANSCEIVER_APAGAR


error Transceiver_Apagar(){
    PTAD_PTAD1 = 0; //Enable 0
    return Transceiver_SetBajo();
}


//***********************************************************************   TRANSCEIVER_ENVIARBYTE


error Transceiver_EnviarByte(byte d){
    (void)SCI2S1;         
    SCI2D=d;
    while(SCI2S1_TDRE == 0){
    }
    while(SCI2S1_TC == 0) {            //Esperamos que se transmita el caracter  
    }
    return _ERR_OK;
}


//***********************************************************************   TRANSCEIVER_RECIBIRBYTE


error Transceiver_RecibirByte(byte *Rxdat){
    if(SCI2S1_RDRF != 0x00){           //si hay algo en el buffer de recepcion lo guardo 
        (void)SCI2S1;
        *Rxdat=SCI2D;
        return _ERR_OK;
    }else
        return _ERR_RXEMPTY;
}



//***********************************************************************   TRANSCEIVER_RECIBIR


error Transceiver_Recibir(byte buf[tam_dato]){

static int j=0;

   
   buf[j]=SCI2D;
   j++;
   if(j == tam_dato){ 
      return _ERR_DATO_LLENO;
      }
      
      return _ERR_OK;            
}
       




//***********************************************************************   TRANSCEIVER_ENVIARACK


error Transceiver_EnviarACK(byte id,byte nro_sec){
    int i;
    (void)SCI2S1;
    (void)Transceiver_EnviarByte(id);
    (void)Transceiver_EnviarByte(flag_ack);
    (void)Transceiver_EnviarByte(nro_sec);
    for(i=0;i<tam_dato;i++){
    	(void)Transceiver_EnviarByte(0xFF);
    }
    return _ERR_OK;
}



//***********************************************************************   TRANSCEIVER_CONTROLARDATO

	    
error Transceiver_ControlarDato(void){
    byte e=3;
    byte suma=0;
    
    if(Buffer_Rx[POS_LAT] == 'S' || Buffer_Rx[POS_LAT] == 'N'){
        while(e<tam_paquete-1){
            if(e!=POS_LAT && e!=POS_LONG)
                suma=suma+(Buffer_Rx[e]-0x30);
            e++;
        }
        if(Buffer_Rx[tam_paquete-1]==suma)
            return _ERR_OK;
    }
    return _ERR_DATO; 
}


error Transceiver_ControlarPaquete(void){

		  byte k;
          
          if(nro_sec != Buffer_Rx[2]){
          	
             nro_sec=Buffer_Rx[2];
          
             if(Transceiver_ControlarDato() != _ERR_OK)
            	 return _ERR_ACK;      
          
          
             Buffer_Escritura[index_fil][0]=Buffer_Rx[0];// GUARDAMOS EL ID
                  
             for(k=3;k<tam_paquete-1;k++)// copiamos los datos controlados al buffer para q se escriba una vez lleno
            	 Buffer_Escritura[index_fil][k-2]=Buffer_Rx[k];
                  
             index_fil++;
                  
             if(index_fil>=cantidad_datos){
               	
            	 index_fil=0;
            	 (void)SD_Escribir(dir_escritura,Buffer_Escritura); // cuando esto ocurre se desabilitan              
            	 (void)SD_CalculaDireccion(dir_escritura,Buffer_Escritura);
            	 //ban_sd=Buffer_Lleno;
              }
          }//cierra el if de nro sec
return _ERR_OK;
}




error Transceiver_EnviarTurno(void){ //quien modifica el valor del id?? siempre se manda el mismo (deberia descomentar lo comentado?)
    static byte i=0x10;
    byte j=0;
    if(i>CANT_DISP)
        i=0x10;
    (void)Transceiver_EnviarByte(i); //ID
    (void)Transceiver_EnviarByte(flag_turno); //flag
    (void)Transceiver_EnviarByte(0x00); //nro de secuencia
    for(j=0;j<tam_dato;j++)
      (void)Transceiver_EnviarByte(0xCD); //payload
    i++;
    LED_BrillarR(1,500);
    return _ERR_OK;
}
