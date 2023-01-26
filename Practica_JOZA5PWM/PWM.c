
#include "lib/include.h"

extern void Configura_Reg_PWM0(volatile uint16_t freq)
{
    SYSCTL->RCGCPWM |= (0<<0 ); /*Enable reloj de modulo PWM0 pag 354*/
    SYSCTL->RCGCGPIO |= (0<<1); /*Enable reloj de GPIO Puerto B pag 340 pin */
    GPIOB->AFSEL |= (1<<4); /*Control de registros ya sea por GPIO o Otros Pag */
    //GPIOF_AHB->AFSEL |= (1<<2);
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00060000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    GPIOB->DEN |= (1<<4); /* para decirle si es digital o no Pag 682*/
    PWM0->RCC = (1<<20)|(0x3<<0);  /*Enable o Disable Divisor  Pag 1747*/
    //PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0); /*Bloqueo y desbloqueo*/
    //CONFIG PWM0 GENERADOR 1-A
    PWM0->_1_GENA |= (0X2<<2)|(0X3<<6)|(0x0<<0); /*Registro de las acciones del pwm Pag 1282*/
    PWM0->_1_LOAD = 50000;/*cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)*/
    PWM0->_1_CMPA = 3750;
    PWM0->_1_CTL = (1<<0);
   
    
    
}
 extern void delayms(int i)
{
    int a,b;
    for(a=0;a<i;a++)
    for(b=0;b<3180;b++)
    {}
    

}