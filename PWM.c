
#include "lib/include.h"

extern void Configura_Reg_PWM0(volatile uint16_t freq)
{
    SYSCTL->RCGCPWM |= (0<<0 ); /*Enable reloj de modulo PWM0 pag 354*/
    SYSCTL->RCGCGPIO |= (0<<1); /*Enable reloj de GPIO Puerto B pag 340 pin */
    GPIOB->AFSEL |= (1<<4); /*Control de registros ya sea por GPIO o Otros Pag */
    //GPIOF_AHB->AFSEL |= (1<<2);
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00060000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    GPIOB->DEN |= (1<<4); /* para decirle si es digital o no Pag 682*/
    PWM0->RCC = (1<<20)|(0x4<<0);  /*Enable o Disable Divisor  Pag 1747*/
    
    


                                    //Experimento 1
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
 * junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 10KHz

    //CONFIG PWM0 GENERADOR 1-A
    PWM0->RCC = (1<<20)|(0x5<<0);  /*Enable o Disable Divisor  Pag 1747
    PWM0->_1_CTL = (0<<0); /*Bloqueo y desbloqueo
    PWM0->_1_GENA |= (0X2<<2)|(0X3<<6)|(0x01<17); //enable en RCC y pwmdiv = 64 =0x5
    PWM0->_1_LOAD = 62500;
    PWM0->_1_CMPA = 4688;
    PWM0->_1_CTL = (1<<0);*/

    
                                       //Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros. *
 


    PWM0->RCC = (1<<20)|(0x4<<0);  //enable en RCC y pwmdiv = 32 =0x4


    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0);
    PWM0->_3_CTL = (0<<0);

    //GENERADORES
    PWM0->_0_GENA |= (0X2<<2)|(0X3<<6)|(0x01<17);  //GENERADOR 0 DEL M0
    PWM0->_2_GENA |= (0X2<<2)|(0X3<<6)|(0x01<17);  //GENERADOR 1 DEL M0
    PWM0->_6_GENA |= (0X2<<2)|(0X3<<6)|(0x01<17);  //GENERADOR 2 DEL M0
    //contador inicia en 25000para los tres generadores
    PWM0->_0_LOAD = 25000; 
    PWM0->_2_LOAD = 25000;
    PWM0->_6_LOAD = 25000;
    // utilizamos un comparador de 1875 
    PWM0->_0_CMPA = 1875;  
    PWM0->_2_CMPA = 1875;
    PWM0->_6_CMPA = 1875;


    PWM0->_0_CTL = (1<<0);
    PWM0->_1_CTL = (1<<0);
    PWM0->_3_CTL = (1<<0);

   */
    
    
}
 extern void delayms(int i)
{
    int a,b;
    for(a=0;a<i;a++)
    for(b=0;b<3180;b++)
    {}
    

}