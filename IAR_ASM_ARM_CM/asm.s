
		PUBLIC  __iar_program_start
        PUBLIC  __vector_table

        SECTION .text:CODE:REORDER(2)
        
        ;; Keep vector table even if it's not referenced
        REQUIRE __vector_table
        
        code16;THUMB
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
//#include ""
//#include ""
//#include ""
//#include ""
//#include ""
//#include ""


//==========================================
loopEnd: B loopEnd
//==========================================
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)
        
        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     __iar_program_start

        DCD     NMI_Handler
        DCD     HardFault_Handler
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler

		SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB

NMI_Handler
HardFault_Handler
__default_handler
        CALL_GRAPH_ROOT __default_handler, "interrupt"
        NOCALL __default_handler
        B __default_handler

        END
