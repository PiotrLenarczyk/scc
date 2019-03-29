        PUBLIC  __iar_program_start
        PUBLIC  __vector_table
	
        SECTION .text:CODE:REORDER(4)  
        REQUIRE __vector_table;;; Keep vector table even if it's not referenced
      
        
        THUMB;code16;THUMB
__iar_program_start
//==========================================
//==========================================
//#include "000_empty.s"
//#include "00_emptyTemplate.s"
//#include "00_REG.s"
//#include "01_B_branch.s"
//#include "02_BL_branchLink.s"
//#include "03_immediate.s"
//#include "04_SWI_debugReturn.s"
//#include "05_ARM_THUMB_mixed.s"
//#include "06_CMP_conditional_execution.s"
//#include "07_gcd()_greatest_common_division.s"
//#include "08_gcd()_optimized.s"
//#include "09_LTORG_litPool.s"
//#include "10_ADR_ADRL_addressGen_addrLoad.s"
//#include "11_EQU_define.s"
//#include "12_DCB_strings.s"
//#include "13_ldrW.s"
//#include "14_defines.s"
//#include "15_SECTION.s"
//#include "16_STM.s"
//#include "17_r8-r12_highRegisters.s"
//#include "18_macro.s"
//#include "19_multiplication.s"
//#include "20_div.s"
#include "21_tmpCompiler.s"
//#include ""
//#include ""
//#include ""


//==========================================
loopEnd: B loopEnd
//==========================================
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(1)
        SECTION .intvec:CODE:NOROOT(2)
        PUBLIC NMI_Handler
        PUBLIC HardFault_Handler        
        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     __iar_program_start
        DCD     NMI_Handler
        DCD     HardFault_Handler
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB
NMI_Handler:
HardFault_Handler:
		B HardFault_Handler
        END
