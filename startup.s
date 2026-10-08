.syntax unified
.cpu cortex-m3
.thumb

.global _estack
.global Reset_Handler

.global vPortSVCHandler
.global xPortPendSVHandler
.global xPortSysTickHandler

.global main


/* =========================================================
 * Vector table
 * ========================================================= */

.section .isr_vector, "a", %progbits

.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word 0
.word 0
.word 0
.word 0
.word vPortSVCHandler
.word DebugMon_Handler
.word 0
.word xPortPendSVHandler
.word xPortSysTickHandler


/* =========================================================
 * Reset Handler
 * ========================================================= */

.section .text.Reset_Handler
.thumb_func
.type Reset_Handler, %function

Reset_Handler:

    /* -----------------------------------------------------
     * Copy .data from Flash to RAM
     * ----------------------------------------------------- */

    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

    cmp r1, r2
    beq data_done

data_copy:
    ldr r3, [r0]
    str r3, [r1]

    adds r0, r0, #4
    adds r1, r1, #4

    cmp r1, r2
    bcc data_copy

data_done:


    /* -----------------------------------------------------
     * Clear .bss
     * ----------------------------------------------------- */

    ldr r1, =_sbss
    ldr r2, =_ebss

    movs r3, #0

    cmp r1, r2
    beq bss_done

bss_clear:
    str r3, [r1]

    adds r1, r1, #4

    cmp r1, r2
    bcc bss_clear

bss_done:


    /* -----------------------------------------------------
     * Call main()
     * ----------------------------------------------------- */

    bl main


    /* -----------------------------------------------------
     * main() should never return
     * ----------------------------------------------------- */

Loop:
    b Loop

.size Reset_Handler, .-Reset_Handler


/* =========================================================
 * Default interrupt handlers
 * ========================================================= */

.section .text.Default_Handler
.thumb_func

NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:
DebugMon_Handler:

Default_Handler:
    b Default_Handler
