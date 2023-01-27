
#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    /*
    Habilitar el modulo 0 del ADC con dos canales analogicos 
    en el puerto E a una velocidad de conversion de 250ksps
    dandole la mayor prioridad al secuenciador 2 con evento
    de procesador 
    */
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (0<<5)|(0<<4)|(1<<3)|(0<<2)|(0<<1)|(0<<0)|(0<<12)|(0<<8);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    
    GPIOD->DIR = (0<<2) | (0<<0) | (0<<1); //PD2(5) , PD0(7) Y PD1(6)

    GPIOD->AFSEL =  (1<<2) | (1<<0 ) | (1<<1);

    GPIOD->DEN = (0<<2) | (0<<0 ) | (0<<1);
    
    GPIOD->PCTL = GPIOE->PCTL & (0xFFFFF000);
    
    GPIOD->AMSEL = (1<<2) | (1<<0 ) | (1<<1);
   

    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x3;//1Msps //VELOCIDAD DE MUESTREO
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores ss3/ss2/ss1/ss0
    ADC0->SSPRI = 0x3210;//establecer prioridades
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0<<0)  ; //evento de muestras
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX0 = (5<<0)|(7<<4)|(6<<8);//1,5,7,11,6,8
    ADC0->SSCTL0 = (1<<1) | (1<<2) | (1<<5) | (1<<6) | (1<<9) | (1<<10);

    ADC0->IM |= (1<<2); /* Unmask ADC0 sequence 2 interrupt pag 1082*/
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (0<<3) | (0<<2) | (0<<1) | (1<<0);
    ADC0->PSSI |= (1<<0) ;
}
extern void ADC0_InSeq2(uint16_t Result[6]){
        //uint16_t Rojo;
    //ADC Processor Sample Sequence Initiate (ADCPSSI)

       ADC0->PSSI |= (1<<0)|(1<<3);
       while((ADC0->RIS & (1<<0))==0){}; // espera al convertidor
       Result[0] = ADC0->SSFIFO0&0xFFF; //  Leer  el resultado almacenado en la pila2
       Result[1] = ADC0->SSFIFO0&0xFFF;
       Result[2] = ADC0->SSFIFO0&0xFFF;
       duty[0] =(Result[0]*37500)/4096;
       duty[1] = (Result[1]*25000)/4096;
       
       ADC0->ISC = 0x0004;  //Conversion finalizada

}


