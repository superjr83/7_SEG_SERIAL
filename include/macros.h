
#ifndef MACROS_H
#define	MACROS_H

#include <stdint.h> 

  // FUNÇÃO: união de Variaveis de 8 bits a uma de 16 ou 32 bits
   #define  __UNI_LO(Param,Param2)       ((uint8_t *)&Param)[0] = ((uint8_t *)&Param2)[0]
   #define  __UNI_HI(Param,Param2)       ((uint8_t *)&Param)[1] = ((uint8_t *)&Param2)[0] 
   #define  __UNI_HIGH(Param, Param2)    ((uint8_t *)&Param)[2] = ((uint8_t *)&Param2)[0]
   #define  __UNI_HIGUEST(Param, Param2) ((uint8_t *)&Param)[3] = ((uint8_t *)&Param2)[0]
   
   // FUNÇÃO: pega partes de uma Variavel de 16/32 bits
   #define __LO(Param)      ((uint8_t *)&Param)[0]
   #define __HI(Param)      ((uint8_t *)&Param)[1]
   #define __HIGHER(Param)  ((uint8_t *)&Param)[2]
   #define __HIGUEST(Param) ((uint8_t *)&Param)[3]

   // FUNÇÃO: manupulação de bits individuais em Variaveis de 1/2/3/4 bytes
   #define  __TST_BIT(Var, Bit)    ((Var) &   (1UL << (Bit)))
   #define  __SET_BIT(Var, Bit)    ((Var) |=  (1UL << (Bit)))
   #define  __CLR_BIT(Var, Bit)    ((Var) &= ~(1UL << (Bit)))
   #define  __TGL_BIT(Var, Bit)    ((Var) ^=  (1UL << (Bit)))
   
   // FUNÇÃO: Separa cada casa Decimail de um numero inteiro
   #define __CONVERT_UNI(value)     (value %10)
   #define __CONVERT_DEZ(value)     (((value / 100) * (-100) + value) / 10)
   #define __CONVERT_CEN(value)     (((value / 1000) * (-1000) + value ) / 100)
   #define __CONVERT_MIL(value)     (((value / 10000) * (-10000) + value ) / 1000)
   #define __CONVERT_DMIL(value)    (((value / 100000) * (-100000) + value ) / 10000)
   #define __CONVERT_CMIL(value)    (((value / 1000000) * (-1000000) + value ) / 100000)

   // FUNÇÃO: Conversão BCD --> DEC    DEC --> BCD 
   #define __BCD_TO_DEC(Bcd) (uint8_t)((Bcd >> 4) * 10 + (Bcd & 0x0F))
   #define __DEC_TO_BCD(Dec) (uint8_t)(((Dec / 10) << 4) + (Dec % 10))

#endif	/* MACROS_H */
