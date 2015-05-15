//#include "stm32f0xx_it.h"
//#include "core_cm4.h"
//#include "core_cmFunc.h"
//#include "startup.h"
#include "main.h"

extern void *_estack; ///< This is global variable from linker script

/* We gave 'weak' attribute, so these functions can be aliased into a single
 * function
 */
void __attribute__((weak)) Reset_Handler(void);     /* Reset Handler */
void __attribute__((weak)) NMI_Handler(void);       /* NMI Handler */
void __attribute__((weak)) FaultHandler(void); /* Hard Fault Handler */
void __attribute__((weak)) MemManage_Handler(void); /* MPU Fault Handler */
void __attribute__((weak)) BusFault_Handler(void);  /* Bus Fault Handler */
void __attribute__((weak)) UsageFault_Handler(void);/* Usage Fault Handler */
void __attribute__((weak)) SVC_Handler(void);       /* SVCall Handler */
void __attribute__((weak)) DebugMon_Handler(void);  /* Debug Monitor Handler */
void __attribute__((weak)) PendSV_Handler(void);    /* PendSV Handler */
void __attribute__((weak)) SysTick_Handler(void);   /* SysTick Handler */
void __attribute__((interrupt)) Default_Handler(void);
void __attribute__((interrupt)) FaultHandler(void);


__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   &_estack,
   Reset_Handler,
   NMI_Handler,
   FaultHandler, 		// 0x0c
   0,           			 // 0x10
   0,
   0,
   0,
   0,
   0,
   0,
   SVC_Handler, 		// 0x2c
   0,
   0,
   PendSV_Handler, 	// 0x38
   SysTick_Handler,
   Default_Handler,                     /* Window WatchDog              */
   0,                                   	  /* Reserved                     */
   Default_Handler,                     /* RTC through the EXTI line    */
   Default_Handler,  	//0x4c             /* FLASH                        */
   Default_Handler,                     /* RCC                          */
   Default_Handler,                     /* EXTI Line 0 and 1            */
   Default_Handler,                     /* EXTI Line 2 and 3            */
   Default_Handler,                     /* EXTI Line 4 to 15            */
   0,                                   	  /* Reserved                     */
   Default_Handler,                     /* DMA1 Channel 1               */
   Default_Handler,                     /* DMA1 Channel 2 and Channel 3 */
   Default_Handler,                     /* DMA1 Channel 4 and Channel 5 */
   Default_Handler,                     /* ADC1                         */
   Default_Handler,  		  /* TIM1 Break, Update, Trigger and Commutation */
   Default_Handler,                     /* TIM1 Capture Compare         */
   0,                                  	   /* Reserved                     */
   Default_Handler,                     /* TIM3                         */
   Default_Handler,                     /* TIM6                         */
   0,                                   		/* Reserved                     */
   Default_Handler ,                    /* TIM14                        */
   Default_Handler ,                    /* TIM15                        */
   Default_Handler ,                    /* TIM16                        */
   Default_Handler ,                    /* TIM17                        */
   Default_Handler ,                    /* I2C1                         */
   Default_Handler ,                    /* I2C2                         */
   Default_Handler ,                    /* SPI1                         */
   Default_Handler ,                    /* SPI2                         */
   Default_Handler ,                    /* USART1                       */
   Default_Handler ,                    /* USART2                       */
   0,                                   	  /* Reserved                     */
   0,                                  	  /* Reserved                     */
   0,                                   	  /* Reserved                     */                             /*  Reserved for user TRIM value*/
};

#pragma weak NMI_Handler        = Default_Handler /* NMI handler */
#pragma weak HardFault_Handler  = FaultHandler /* Hard Fault handler */
#pragma weak MemManage_Handler  = Default_Handler /* MPU Fault Handler */
#pragma weak BusFault_Handler   = FaultHandler /* Bus Fault Handler */
#pragma weak UsageFault_Handler = FaultHandler /* Usage Fault Handler */
#pragma weak SVC_Handler        = FaultHandler /* SVCall Handler */
#pragma weak DebugMon_Handler   = Default_Handler /* Debug Monitor Handler */
#pragma weak PendSV_Handler     = FaultHandler /* PendSV Handler */
#pragma weak SysTick_Handler    = Default_Handler /* SysTick Handler */

void Default_Handler(void) {
__asm__("BKPT");
 while (1);
}
/**
*  Thanks for this piece of code from Erich Styger: http://mcuoneclipse.com/about/
*  http://mcuoneclipse.com/2012/12/28/a-processor-expert-component-to-help-with-hard-faults/*
*/
void HardFault_HandlerC(unsigned long *hardfault_args){
  volatile unsigned long stacked_r0 ;
  volatile unsigned long stacked_r1 ;
  volatile unsigned long stacked_r2 ;
  volatile unsigned long stacked_r3 ;
  volatile unsigned long stacked_r12 ;
  volatile unsigned long stacked_lr ;
  volatile unsigned long stacked_pc ;
  volatile unsigned long stacked_psr ;
  volatile unsigned long _CFSR ;
  volatile unsigned long _HFSR ;
  volatile unsigned long _DFSR ;
  volatile unsigned long _AFSR ;
  volatile unsigned long _BFAR ;
  volatile unsigned long _MMAR ;

  stacked_r0 = ((unsigned long)hardfault_args[0]) ;
  stacked_r1 = ((unsigned long)hardfault_args[1]) ;
  stacked_r2 = ((unsigned long)hardfault_args[2]) ;
  stacked_r3 = ((unsigned long)hardfault_args[3]) ;
  stacked_r12 = ((unsigned long)hardfault_args[4]) ;
  stacked_lr = ((unsigned long)hardfault_args[5]) ;
  stacked_pc = ((unsigned long)hardfault_args[6]) ;
  stacked_psr = ((unsigned long)hardfault_args[7]) ;

  // Configurable Fault Status Register
  // Consists of MMSR, BFSR and UFSR
  _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;

  // Hard Fault Status Register
  _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;

  // Debug Fault Status Register
  _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;

  // Auxiliary Fault Status Register
  _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;

  // Read the Fault Address Registers. These may not contain valid values.
  // Check BFARVALID/MMARVALID to see if they are valid values
  // MemManage Fault Address Register
  _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
  // Bus Fault Address Register
  _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;

  __asm("BKPT #0\n") ; // Break into the debugger
}
void FaultHandler(void) {
	__asm volatile (
	    " movs r0,#4       \n"
	    " movs r1, lr      \n"
	    " tst r0, r1       \n"
	    " beq _MSP         \n"
	    " mrs r0, psp      \n"
	    " b _HALT          \n"
	  "_MSP:               \n"
	    " mrs r0, msp      \n"
	  "_HALT:              \n"
	    " ldr r1,[r0,#20]  \n"
	    " b HardFault_HandlerC \n"
	    " bkpt #0          \n"
	  );
}




