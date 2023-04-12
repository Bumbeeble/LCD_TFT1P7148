; generated by Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
; commandline ArmCC [--c99 --split_sections --debug -c -S -o.\objects\bsp_usart.s --depend=.\objects\bsp_usart.d --cpu=Cortex-M4.fp.sp --apcs=interwork -O0 --diag_suppress=9931 -I..\Firmware\GD32F4xx_standard_peripheral\Include -I..\Firmware\CMSIS -I..\Firmware\CMSIS\GD\GD32F4xx\Include -I..\User -I..\Hardware\led -I..\Hardware\usart -I..\Hardware\key -I..\App -I.\RTE\_GD32F450 -Ih:\Users\Bumbe\AppData\Local\Arm\Packs\GigaDevice\GD32F4xx_DFP\2.1.0\Device\F4XX\Include -Ih:\Keil_v5\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=530 -DGD32F450 -D_RTE_ --omf_browse=.\objects\bsp_usart.crf ..\Hardware\usart\bsp_usart.c]
        THUMB
        REQUIRE8
        PRESERVE8

        AREA ||i.fputc||, CODE, READONLY, ALIGN=1

fputc PROC
        PUSH     {r4-r6,lr}
        MOV      r4,r0
        MOV      r5,r1
        UXTB     r0,r4
        BL       usart_send_data
        MOV      r0,r4
        POP      {r4-r6,pc}
        ENDP


        AREA ||i.usart_gpio_config||, CODE, READONLY, ALIGN=2

usart_gpio_config PROC
        PUSH     {r4,lr}
        MOV      r4,r0
        MOV      r0,#0xc00
        BL       rcu_periph_clock_enable
        MOV      r0,#0xc00
        BL       rcu_periph_clock_enable
        MOV      r0,#0x1104
        BL       rcu_periph_clock_enable
        MOV      r2,#0x200
        MOVS     r1,#7
        LDR      r0,|L1.172|
        BL       gpio_af_set
        MOV      r2,#0x400
        MOVS     r1,#7
        LDR      r0,|L1.172|
        BL       gpio_af_set
        MOV      r3,#0x200
        MOVS     r2,#1
        MOVS     r1,#2
        LDR      r0,|L1.172|
        BL       gpio_mode_set
        MOV      r3,#0x400
        MOVS     r2,#1
        MOVS     r1,#2
        LDR      r0,|L1.172|
        BL       gpio_mode_set
        MOV      r3,#0x200
        MOVS     r2,#2
        MOVS     r1,#0
        LDR      r0,|L1.172|
        BL       gpio_output_options_set
        MOV      r3,#0x400
        MOVS     r2,#2
        MOVS     r1,#0
        LDR      r0,|L1.172|
        BL       gpio_output_options_set
        LDR      r0,|L1.176|
        BL       usart_deinit
        MOV      r1,r4
        LDR      r0,|L1.176|
        BL       usart_baudrate_set
        MOVS     r1,#0
        LDR      r0,|L1.176|
        BL       usart_parity_config
        MOVS     r1,#0
        LDR      r0,|L1.176|
        BL       usart_word_length_set
        MOVS     r1,#0
        LDR      r0,|L1.176|
        BL       usart_stop_bit_set
        LDR      r0,|L1.176|
        BL       usart_enable
        MOVS     r1,#8
        LDR      r0,|L1.176|
        BL       usart_transmit_config
        MOVS     r0,#1
        LDR      r1,|L1.180|
        STRB     r0,[r1,#0xcc]
        POP      {r4,pc}
        ENDP

        DCW      0x0000
|L1.172|
        DCD      0x40020000
|L1.176|
        DCD      0x40011000
|L1.180|
        DCD      usart_tx

        AREA ||i.usart_handler||, CODE, READONLY, ALIGN=2

usart_handler PROC
        PUSH     {r4,lr}
        MOVS     r1,#7
        LDR      r0,|L2.112|
        BL       usart_flag_get
        CBNZ     r0,|L2.14|
|L2.12|
        POP      {r4,pc}
|L2.14|
        LDR      r0,|L2.116|
        LDRB     r0,[r0,#0xca]  ; usart_tx
        CMP      r0,#1
        BLE      |L2.92|
        LDR      r0,|L2.116|
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        LDR      r2,|L2.116|
        LDRB     r1,[r2,r0]
        LDR      r0,|L2.112|
        BL       usart_data_transmit
        LDR      r0,|L2.116|
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        ADDS     r0,r0,#1
        LDR      r1,|L2.116|
        STRB     r0,[r1,#0xc8]
        MOV      r0,r1
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        CMP      r0,#0xc8
        BLT      |L2.70|
        MOVS     r0,#0
        STRB     r0,[r1,#0xc8]
|L2.70|
        MOVS     r0,#0
        LDR      r1,|L2.116|
        STRB     r0,[r1,#0xcb]
        MOV      r0,r1
        LDRB     r0,[r0,#0xca]  ; usart_tx
        SUBS     r0,r0,#1
        STRB     r0,[r1,#0xca]
        B        |L2.106|
|L2.92|
        MOVS     r0,#0
        LDR      r1,|L2.116|
        STRB     r0,[r1,#0xca]
        MOVS     r0,#1
        STRB     r0,[r1,#0xcc]
|L2.106|
        NOP      
        B        |L2.12|
        ENDP

        DCW      0x0000
|L2.112|
        DCD      0x40011000
|L2.116|
        DCD      usart_tx

        AREA ||i.usart_send_data||, CODE, READONLY, ALIGN=2

usart_send_data PROC
        PUSH     {r4,lr}
        MOV      r4,r0
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xcb]  ; usart_tx
        CBZ      r0,|L3.14|
|L3.12|
        POP      {r4,pc}
|L3.14|
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xc9]  ; usart_tx
        LDR      r1,|L3.148|
        STRB     r4,[r1,r0]
        MOV      r0,r1
        LDRB     r0,[r0,#0xc9]  ; usart_tx
        ADDS     r0,r0,#1
        STRB     r0,[r1,#0xc9]
        MOV      r0,r1
        LDRB     r0,[r0,#0xc9]  ; usart_tx
        CMP      r0,#0xc8
        BLT      |L3.52|
        MOVS     r0,#0
        STRB     r0,[r1,#0xc9]
|L3.52|
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xca]  ; usart_tx
        ADDS     r0,r0,#1
        LDR      r1,|L3.148|
        STRB     r0,[r1,#0xca]
        MOV      r0,r1
        LDRB     r0,[r0,#0xca]  ; usart_tx
        CMP      r0,#0xc8
        BLT      |L3.82|
        MOVS     r0,#1
        STRB     r0,[r1,#0xcb]
|L3.82|
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xcc]  ; usart_tx
        CBZ      r0,|L3.144|
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        LDR      r2,|L3.148|
        LDRB     r1,[r2,r0]
        LDR      r0,|L3.152|
        BL       usart_data_transmit
        LDR      r0,|L3.148|
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        ADDS     r0,r0,#1
        LDR      r1,|L3.148|
        STRB     r0,[r1,#0xc8]
        MOV      r0,r1
        LDRB     r0,[r0,#0xc8]  ; usart_tx
        CMP      r0,#0xc8
        BLT      |L3.136|
        MOVS     r0,#0
        STRB     r0,[r1,#0xc8]
|L3.136|
        MOVS     r0,#0
        LDR      r1,|L3.148|
        STRB     r0,[r1,#0xcc]
|L3.144|
        NOP      
        B        |L3.12|
        ENDP

|L3.148|
        DCD      usart_tx
|L3.152|
        DCD      0x40011000

        AREA ||i.usart_send_string||, CODE, READONLY, ALIGN=1

usart_send_string PROC
        PUSH     {r4,lr}
        MOV      r4,r0
        B        |L4.14|
|L4.6|
        LDRB     r0,[r4],#1
        BL       usart_send_data
|L4.14|
        CBZ      r4,|L4.22|
        LDRB     r0,[r4,#0]
        CMP      r0,#0
        BNE      |L4.6|
|L4.22|
        POP      {r4,pc}
        ENDP


        AREA ||.arm_vfe_header||, DATA, READONLY, NOALLOC, ALIGN=2

        DCD      0x00000000

        AREA ||.bss||, DATA, NOINIT, ALIGN=0

usart_tx
        %        205

;*** Start embedded assembler ***

#line 1 "..\\Hardware\\usart\\bsp_usart.c"
	AREA ||.rev16_text||, CODE
	THUMB
	EXPORT |__asm___11_bsp_usart_c_01d26bc0____REV16|
#line 114 "..\\Firmware\\CMSIS\\core_cmInstr.h"
|__asm___11_bsp_usart_c_01d26bc0____REV16| PROC
#line 115

 rev16 r0, r0
 bx lr
	ENDP
	AREA ||.revsh_text||, CODE
	THUMB
	EXPORT |__asm___11_bsp_usart_c_01d26bc0____REVSH|
#line 128
|__asm___11_bsp_usart_c_01d26bc0____REVSH| PROC
#line 129

 revsh r0, r0
 bx lr
	ENDP

;*** End   embedded assembler ***

        EXPORT fputc [CODE]
        EXPORT usart_gpio_config [CODE]
        EXPORT usart_handler [CODE]
        EXPORT usart_send_data [CODE]
        EXPORT usart_send_string [CODE]
        EXPORT usart_tx [DATA,SIZE=205]

        IMPORT ||Lib$$Request$$armlib|| [CODE,WEAK]
        IMPORT usart_data_transmit [CODE]
        IMPORT usart_flag_get [CODE]
        IMPORT rcu_periph_clock_enable [CODE]
        IMPORT gpio_af_set [CODE]
        IMPORT gpio_mode_set [CODE]
        IMPORT gpio_output_options_set [CODE]
        IMPORT usart_deinit [CODE]
        IMPORT usart_baudrate_set [CODE]
        IMPORT usart_parity_config [CODE]
        IMPORT usart_word_length_set [CODE]
        IMPORT usart_stop_bit_set [CODE]
        IMPORT usart_enable [CODE]
        IMPORT usart_transmit_config [CODE]

        ATTR FILESCOPE
        ATTR SETVALUE Tag_ABI_PCS_wchar_t,2
        ATTR SETVALUE Tag_ABI_enum_size,1
        ATTR SETVALUE Tag_ABI_optimization_goals,6
        ATTR SETSTRING Tag_conformance,"2.09"
        ATTR SETVALUE AV,18,1

        ASSERT {ENDIAN} = "little"
        ASSERT {INTER} = {TRUE}
        ASSERT {ROPI} = {FALSE}
        ASSERT {RWPI} = {FALSE}
        ASSERT {IEEE_FULL} = {FALSE}
        ASSERT {IEEE_PART} = {FALSE}
        ASSERT {IEEE_JAVA} = {FALSE}
        END