
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "rtx_os.h"
#include "rtx_lib.h"
#include "stm32f4xx.h"                  // Device header
#include "cmsis_os2.h"

void SystemCoreClockConfigure(void) {

  RCC->CR |= ((uint32_t)RCC_CR_HSION);                     /* Enable HSI */
  while ((RCC->CR & RCC_CR_HSIRDY) == 0);                  /* Wait for HSI Ready */

  RCC->CFGR = RCC_CFGR_SW_HSI;                             /* HSI is system clock */
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);  /* Wait for HSI used as system clock */

  FLASH->ACR  = FLASH_ACR_PRFTEN;                          /* Enable Prefetch Buffer */
  FLASH->ACR |= FLASH_ACR_ICEN;                            /* Instruction cache enable */
  FLASH->ACR |= FLASH_ACR_DCEN;                            /* Data cache enable */
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;                     /* Flash 5 wait state */

  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                         /* HCLK = SYSCLK */
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;                        /* APB1 = HCLK/4 */
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;                        /* APB2 = HCLK/2 */

  RCC->CR &= ~RCC_CR_PLLON;                                /* Disable PLL */

  /* PLL configuration:  VCO = HSI/M * N,  Sysclk = VCO/P */
  RCC->PLLCFGR = ( 16ul                   |                /* PLL_M =  16 */
                 (384ul <<  6)            |                /* PLL_N = 384 */
                 (  3ul << 16)            |                /* PLL_P =   8 */
                 (RCC_PLLCFGR_PLLSRC_HSI) |                /* PLL_SRC = HSI */
                 (  8ul << 24)             );              /* PLL_Q =   8 */

  RCC->CR |= RCC_CR_PLLON;                                 /* Enable PLL */
  while((RCC->CR & RCC_CR_PLLRDY) == 0) __NOP();           /* Wait till PLL is ready */

  RCC->CFGR &= ~RCC_CFGR_SW;                               /* Select PLL as system clock source */
  RCC->CFGR |=  RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);  /* Wait till PLL is system clock src */
}



int osKernelConfigStatus;
int main (void)
{
  uint32_t button_msk = (1U << Buttons_GetCount()) - 1;
  osKernelInitialize();
  SystemCoreClockConfigure();                              /* configure System Clock */
  
}