; generated by Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
; commandline ArmCC [--c99 --split_sections --debug -c -S -o.\objects\gd32f4xx_usart.s --depend=.\objects\gd32f4xx_usart.d --cpu=Cortex-M4.fp.sp --apcs=interwork -O0 --diag_suppress=9931 -I..\Firmware\GD32F4xx_standard_peripheral\Include -I..\Firmware\CMSIS -I..\Firmware\CMSIS\GD\GD32F4xx\Include -I..\User -I..\Hardware\led -I..\Hardware\usart -I..\Hardware\key -I..\App -I.\RTE\_GD32F450 -Ih:\Users\Bumbe\AppData\Local\Arm\Packs\GigaDevice\GD32F4xx_DFP\2.1.0\Device\F4XX\Include -Ih:\Keil_v5\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=530 -DGD32F450 -D_RTE_ --omf_browse=.\objects\gd32f4xx_usart.crf ..\Firmware\GD32F4xx_standard_peripheral\Source\gd32f4xx_usart.c]
        THUMB
        REQUIRE8
        PRESERVE8

        AREA ||i.usart_address_config||, CODE, READONLY, ALIGN=1

usart_address_config PROC
        LDR      r2,[r0,#0x10]
        BIC      r2,r2,#0xf
        STR      r2,[r0,#0x10]
        LDR      r2,[r0,#0x10]
        AND      r3,r1,#0xf
        ORRS     r2,r2,r3
        STR      r2,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_baudrate_set||, CODE, READONLY, ALIGN=2

usart_baudrate_set PROC
        PUSH     {r4-r10,lr}
        MOV      r4,r0
        MOV      r5,r1
        MOVS     r7,#0
        MOV      r8,r7
        MOV      r9,r7
        MOVS     r6,#0
        LDR      r1,|L1.224|
        SUBS     r0,r4,r1
        CMP      r4,r1
        BEQ      |L1.132|
        BGT      |L1.52|
        LDR      r0,|L1.228|
        ADD      r0,r0,r4
        CBZ      r0,|L1.92|
        CMP      r0,#0x400
        BEQ      |L1.102|
        CMP      r0,#0x800
        BEQ      |L1.112|
        CMP      r0,#0xc00
        BNE      |L1.152|
        B        |L1.122|
|L1.52|
        CMP      r0,#0x400
        BEQ      |L1.142|
        CMP      r0,#0x9800
        BEQ      |L1.72|
        CMP      r0,#0x9c00
        BNE      |L1.152|
        B        |L1.82|
|L1.72|
        MOVS     r0,#3
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.82|
        MOVS     r0,#3
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.92|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.102|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.112|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.122|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.132|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.142|
        MOVS     r0,#2
        BL       rcu_clock_freq_get
        MOV      r7,r0
        B        |L1.154|
|L1.152|
        NOP      
|L1.154|
        NOP      
        LDR      r0,[r4,#0xc]
        AND      r0,r0,#0x8000
        CBZ      r0,|L1.194|
        LSLS     r0,r7,#1
        ADD      r0,r0,r5,LSR #1
        UDIV     r6,r0,r5
        MOV      r0,#0xfff0
        AND      r8,r6,r0
        UBFX     r9,r6,#1,#3
        ORR      r0,r8,r9
        STR      r0,[r4,#8]
        B        |L1.220|
|L1.194|
        ADD      r0,r7,r5,LSR #1
        UDIV     r6,r0,r5
        MOV      r0,#0xfff0
        AND      r8,r6,r0
        AND      r9,r6,#0xf
        ORR      r0,r8,r9
        STR      r0,[r4,#8]
|L1.220|
        POP      {r4-r10,pc}
        ENDP

|L1.224|
        DCD      0x40007800
|L1.228|
        DCD      0xbfffbc00

        AREA ||i.usart_block_length_config||, CODE, READONLY, ALIGN=1

usart_block_length_config PROC
        LDR      r2,[r0,#0x84]!
        BIC      r2,r2,#0xff000000
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        MOV      r3,#0xff000000
        AND      r3,r3,r1,LSL #24
        ORRS     r2,r2,r3
        STR      r2,[r0],#-0x84
        BX       lr
        ENDP


        AREA ||i.usart_break_frame_coherence_config||, CODE, READONLY, ALIGN=1

usart_break_frame_coherence_config PROC
        LDR      r2,[r0,#0xc0]!
        BIC      r2,r2,#4
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        AND      r3,r1,#4
        ORRS     r2,r2,r3
        STR      r2,[r0],#-0xc0
        BX       lr
        ENDP


        AREA ||i.usart_data_first_config||, CODE, READONLY, ALIGN=1

usart_data_first_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x80]
        BIC      r1,r1,#0x800
        ORRS     r1,r1,r2
        STR      r1,[r0,#0x80]
        BX       lr
        ENDP


        AREA ||i.usart_data_receive||, CODE, READONLY, ALIGN=1

usart_data_receive PROC
        MOV      r1,r0
        LDR      r0,[r1,#4]
        UBFX     r0,r0,#0,#9
        BX       lr
        ENDP


        AREA ||i.usart_data_transmit||, CODE, READONLY, ALIGN=1

usart_data_transmit PROC
        UBFX     r2,r1,#0,#9
        STR      r2,[r0,#4]
        BX       lr
        ENDP


        AREA ||i.usart_deinit||, CODE, READONLY, ALIGN=2

usart_deinit PROC
        PUSH     {r4,lr}
        MOV      r4,r0
        LDR      r1,|L7.212|
        SUBS     r0,r4,r1
        CMP      r4,r1
        BEQ      |L7.168|
        BGT      |L7.40|
        LDR      r0,|L7.216|
        ADD      r0,r0,r4
        CBZ      r0,|L7.78|
        CMP      r0,#0x400
        BEQ      |L7.96|
        CMP      r0,#0x800
        BEQ      |L7.132|
        CMP      r0,#0xc00
        BNE      |L7.204|
        B        |L7.150|
|L7.40|
        CMP      r0,#0x400
        BEQ      |L7.186|
        CMP      r0,#0x9800
        BEQ      |L7.60|
        CMP      r0,#0x9c00
        BNE      |L7.204|
        B        |L7.114|
|L7.60|
        MOV      r0,#0x904
        BL       rcu_periph_reset_enable
        MOV      r0,#0x904
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.78|
        MOV      r0,#0x811
        BL       rcu_periph_reset_enable
        MOV      r0,#0x811
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.96|
        MOV      r0,#0x812
        BL       rcu_periph_reset_enable
        MOV      r0,#0x812
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.114|
        MOV      r0,#0x905
        BL       rcu_periph_reset_enable
        MOV      r0,#0x905
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.132|
        MOV      r0,#0x813
        BL       rcu_periph_reset_enable
        MOV      r0,#0x813
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.150|
        MOV      r0,#0x814
        BL       rcu_periph_reset_enable
        MOV      r0,#0x814
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.168|
        MOV      r0,#0x81e
        BL       rcu_periph_reset_enable
        MOV      r0,#0x81e
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.186|
        MOV      r0,#0x81f
        BL       rcu_periph_reset_enable
        MOV      r0,#0x81f
        BL       rcu_periph_reset_disable
        B        |L7.206|
|L7.204|
        NOP      
|L7.206|
        NOP      
        POP      {r4,pc}
        ENDP

        DCW      0x0000
|L7.212|
        DCD      0x40007800
|L7.216|
        DCD      0xbfffbc00

        AREA ||i.usart_disable||, CODE, READONLY, ALIGN=1

usart_disable PROC
        LDR      r1,[r0,#0xc]
        BIC      r1,r1,#0x2000
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_dma_receive_config||, CODE, READONLY, ALIGN=1

usart_dma_receive_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x40
        ORRS     r1,r1,r2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_dma_transmit_config||, CODE, READONLY, ALIGN=1

usart_dma_transmit_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x80
        ORRS     r1,r1,r2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_enable||, CODE, READONLY, ALIGN=1

usart_enable PROC
        LDR      r1,[r0,#0xc]
        ORR      r1,r1,#0x2000
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_flag_clear||, CODE, READONLY, ALIGN=1

usart_flag_clear PROC
        PUSH     {r4,lr}
        ADD      r2,r0,r1,LSR #6
        LDR      r2,[r2,#0]
        AND      r4,r1,#0x1f
        MOVS     r3,#1
        LSLS     r3,r3,r4
        BICS     r2,r2,r3
        ADD      r3,r0,r1,LSR #6
        STR      r2,[r3,#0]
        POP      {r4,pc}
        ENDP


        AREA ||i.usart_flag_get||, CODE, READONLY, ALIGN=1

usart_flag_get PROC
        PUSH     {r4,lr}
        MOV      r2,r0
        ADD      r0,r2,r1,LSR #6
        LDR      r0,[r0,#0]
        AND      r4,r1,#0x1f
        MOVS     r3,#1
        LSLS     r3,r3,r4
        ANDS     r0,r0,r3
        CBZ      r0,|L13.26|
        MOVS     r0,#1
|L13.24|
        POP      {r4,pc}
|L13.26|
        MOVS     r0,#0
        B        |L13.24|
        ENDP


        AREA ||i.usart_guard_time_config||, CODE, READONLY, ALIGN=1

usart_guard_time_config PROC
        LDR      r2,[r0,#0x18]
        BIC      r2,r2,#0xff00
        STR      r2,[r0,#0x18]
        LDR      r2,[r0,#0x18]
        MOV      r3,#0xff00
        AND      r3,r3,r1,LSL #8
        ORRS     r2,r2,r3
        STR      r2,[r0,#0x18]
        BX       lr
        ENDP


        AREA ||i.usart_halfduplex_disable||, CODE, READONLY, ALIGN=1

usart_halfduplex_disable PROC
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#8
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_halfduplex_enable||, CODE, READONLY, ALIGN=1

usart_halfduplex_enable PROC
        LDR      r1,[r0,#0x14]
        ORR      r1,r1,#8
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_hardware_flow_coherence_config||, CODE, READONLY, ALIGN=1

usart_hardware_flow_coherence_config PROC
        LDR      r2,[r0,#0xc0]!
        BIC      r2,r2,#1
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        AND      r3,r1,#1
        ORRS     r2,r2,r3
        STR      r2,[r0],#-0xc0
        BX       lr
        ENDP


        AREA ||i.usart_hardware_flow_cts_config||, CODE, READONLY, ALIGN=1

usart_hardware_flow_cts_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x200
        ORRS     r1,r1,r2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_hardware_flow_rts_config||, CODE, READONLY, ALIGN=1

usart_hardware_flow_rts_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x100
        ORRS     r1,r1,r2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_interrupt_disable||, CODE, READONLY, ALIGN=1

usart_interrupt_disable PROC
        PUSH     {r4,lr}
        ADD      r2,r0,r1,LSR #6
        LDR      r2,[r2,#0]
        AND      r4,r1,#0x1f
        MOVS     r3,#1
        LSLS     r3,r3,r4
        BICS     r2,r2,r3
        ADD      r3,r0,r1,LSR #6
        STR      r2,[r3,#0]
        POP      {r4,pc}
        ENDP


        AREA ||i.usart_interrupt_enable||, CODE, READONLY, ALIGN=1

usart_interrupt_enable PROC
        PUSH     {r4,lr}
        ADD      r2,r0,r1,LSR #6
        LDR      r2,[r2,#0]
        AND      r4,r1,#0x1f
        MOVS     r3,#1
        LSLS     r3,r3,r4
        ORRS     r2,r2,r3
        ADD      r3,r0,r1,LSR #6
        STR      r2,[r3,#0]
        POP      {r4,pc}
        ENDP


        AREA ||i.usart_interrupt_flag_clear||, CODE, READONLY, ALIGN=1

usart_interrupt_flag_clear PROC
        PUSH     {r4,lr}
        ADD      r2,r0,r1,LSR #22
        LDR      r2,[r2,#0]
        UBFX     r4,r1,#16,#5
        MOVS     r3,#1
        LSLS     r3,r3,r4
        BICS     r2,r2,r3
        ADD      r3,r0,r1,LSR #22
        STR      r2,[r3,#0]
        POP      {r4,pc}
        ENDP


        AREA ||i.usart_interrupt_flag_get||, CODE, READONLY, ALIGN=1

usart_interrupt_flag_get PROC
        PUSH     {r4-r6,lr}
        MOV      r2,r0
        MOVS     r3,#0
        MOVS     r4,#0
        UBFX     r0,r1,#6,#10
        LDR      r0,[r2,r0]
        AND      r6,r1,#0x1f
        MOVS     r5,#1
        LSLS     r5,r5,r6
        AND      r3,r0,r5
        ADD      r0,r2,r1,LSR #22
        LDR      r0,[r0,#0]
        UBFX     r6,r1,#16,#5
        MOVS     r5,#1
        LSLS     r5,r5,r6
        AND      r4,r0,r5
        CBZ      r4,|L23.52|
        CBZ      r3,|L23.52|
        MOVS     r0,#1
|L23.50|
        POP      {r4-r6,pc}
|L23.52|
        MOVS     r0,#0
        B        |L23.50|
        ENDP


        AREA ||i.usart_invert_config||, CODE, READONLY, ALIGN=1

usart_invert_config PROC
        CMP      r1,#6
        BCS      |L24.98|
        TBB      [pc,r1]
        DCB      0x03,0x18,0x0a,0x1f
        DCB      0x11,0x26
        LDR      r2,[r0,#0x80]
        ORR      r2,r2,#0x400
        STR      r2,[r0,#0x80]
        B        |L24.100|
        LDR      r2,[r0,#0x80]
        ORR      r2,r2,#0x200
        STR      r2,[r0,#0x80]
        B        |L24.100|
        LDR      r2,[r0,#0x80]
        ORR      r2,r2,#0x100
        STR      r2,[r0,#0x80]
        B        |L24.100|
        LDR      r2,[r0,#0x80]
        BIC      r2,r2,#0x400
        STR      r2,[r0,#0x80]
        B        |L24.100|
        LDR      r2,[r0,#0x80]
        BIC      r2,r2,#0x200
        STR      r2,[r0,#0x80]
        B        |L24.100|
        LDR      r2,[r0,#0x80]
        BIC      r2,r2,#0x100
        STR      r2,[r0,#0x80]
        B        |L24.100|
|L24.98|
        NOP      
|L24.100|
        NOP      
        BX       lr
        ENDP


        AREA ||i.usart_irda_lowpower_config||, CODE, READONLY, ALIGN=1

usart_irda_lowpower_config PROC
        LDR      r2,[r0,#0x14]
        BIC      r2,r2,#4
        STR      r2,[r0,#0x14]
        LDR      r2,[r0,#0x14]
        AND      r3,r1,#4
        ORRS     r2,r2,r3
        STR      r2,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_irda_mode_disable||, CODE, READONLY, ALIGN=1

usart_irda_mode_disable PROC
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_irda_mode_enable||, CODE, READONLY, ALIGN=1

usart_irda_mode_enable PROC
        LDR      r1,[r0,#0x14]
        ORR      r1,r1,#2
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_lin_break_detection_length_config||, CODE, READONLY, ALIGN=1

usart_lin_break_detection_length_config PROC
        LDR      r2,[r0,#0x10]
        BIC      r2,r2,#0x20
        STR      r2,[r0,#0x10]
        LDR      r2,[r0,#0x10]
        AND      r3,r1,#0x20
        ORRS     r2,r2,r3
        STR      r2,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_lin_mode_disable||, CODE, READONLY, ALIGN=1

usart_lin_mode_disable PROC
        LDR      r1,[r0,#0x10]
        BIC      r1,r1,#0x4000
        STR      r1,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_lin_mode_enable||, CODE, READONLY, ALIGN=1

usart_lin_mode_enable PROC
        LDR      r1,[r0,#0x10]
        ORR      r1,r1,#0x4000
        STR      r1,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_mute_mode_disable||, CODE, READONLY, ALIGN=1

usart_mute_mode_disable PROC
        LDR      r1,[r0,#0xc]
        BIC      r1,r1,#2
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_mute_mode_enable||, CODE, READONLY, ALIGN=1

usart_mute_mode_enable PROC
        LDR      r1,[r0,#0xc]
        ORR      r1,r1,#2
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_mute_mode_wakeup_config||, CODE, READONLY, ALIGN=1

usart_mute_mode_wakeup_config PROC
        LDR      r2,[r0,#0xc]
        BIC      r2,r2,#0x800
        STR      r2,[r0,#0xc]
        LDR      r2,[r0,#0xc]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_oversample_config||, CODE, READONLY, ALIGN=1

usart_oversample_config PROC
        LDR      r2,[r0,#0xc]
        BIC      r2,r2,#0x8000
        STR      r2,[r0,#0xc]
        LDR      r2,[r0,#0xc]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_parity_check_coherence_config||, CODE, READONLY, ALIGN=1

usart_parity_check_coherence_config PROC
        LDR      r2,[r0,#0xc0]!
        BIC      r2,r2,#2
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        AND      r3,r1,#2
        ORRS     r2,r2,r3
        STR      r2,[r0],#-0xc0
        BX       lr
        ENDP


        AREA ||i.usart_parity_config||, CODE, READONLY, ALIGN=1

usart_parity_config PROC
        LDR      r2,[r0,#0xc]
        BIC      r2,r2,#0x600
        STR      r2,[r0,#0xc]
        LDR      r2,[r0,#0xc]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_prescaler_config||, CODE, READONLY, ALIGN=1

usart_prescaler_config PROC
        LDR      r2,[r0,#0x18]
        BIC      r2,r2,#0xff
        STR      r2,[r0,#0x18]
        LDR      r2,[r0,#0x18]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0x18]
        BX       lr
        ENDP


        AREA ||i.usart_receive_config||, CODE, READONLY, ALIGN=1

usart_receive_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0xc]
        BIC      r1,r1,#4
        ORRS     r1,r1,r2
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_receiver_timeout_disable||, CODE, READONLY, ALIGN=1

usart_receiver_timeout_disable PROC
        LDR      r1,[r0,#0x80]
        BIC      r1,r1,#1
        STR      r1,[r0,#0x80]
        BX       lr
        ENDP


        AREA ||i.usart_receiver_timeout_enable||, CODE, READONLY, ALIGN=1

usart_receiver_timeout_enable PROC
        LDR      r1,[r0,#0x80]
        ORR      r1,r1,#1
        STR      r1,[r0,#0x80]
        BX       lr
        ENDP


        AREA ||i.usart_receiver_timeout_threshold_config||, CODE, READONLY, ALIGN=1

usart_receiver_timeout_threshold_config PROC
        LDR      r2,[r0,#0x84]!
        AND      r2,r2,#0xff000000
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        ORRS     r2,r2,r1
        STR      r2,[r0],#-0x84
        BX       lr
        ENDP


        AREA ||i.usart_sample_bit_config||, CODE, READONLY, ALIGN=1

usart_sample_bit_config PROC
        LDR      r2,[r0,#0x14]
        BIC      r2,r2,#0x800
        STR      r2,[r0,#0x14]
        LDR      r2,[r0,#0x14]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_send_break||, CODE, READONLY, ALIGN=1

usart_send_break PROC
        LDR      r1,[r0,#0xc]
        ORR      r1,r1,#1
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_smartcard_autoretry_config||, CODE, READONLY, ALIGN=1

usart_smartcard_autoretry_config PROC
        LDR      r2,[r0,#0x80]!
        BIC      r2,r2,#0xe
        STR      r2,[r0,#0]
        LDR      r2,[r0,#0]
        MOVS     r3,#0xe
        AND      r3,r3,r1,LSL #1
        ORRS     r2,r2,r3
        STR      r2,[r0],#-0x80
        BX       lr
        ENDP


        AREA ||i.usart_smartcard_mode_disable||, CODE, READONLY, ALIGN=1

usart_smartcard_mode_disable PROC
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x20
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_smartcard_mode_enable||, CODE, READONLY, ALIGN=1

usart_smartcard_mode_enable PROC
        LDR      r1,[r0,#0x14]
        ORR      r1,r1,#0x20
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_smartcard_mode_nack_disable||, CODE, READONLY, ALIGN=1

usart_smartcard_mode_nack_disable PROC
        LDR      r1,[r0,#0x14]
        BIC      r1,r1,#0x10
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_smartcard_mode_nack_enable||, CODE, READONLY, ALIGN=1

usart_smartcard_mode_nack_enable PROC
        LDR      r1,[r0,#0x14]
        ORR      r1,r1,#0x10
        STR      r1,[r0,#0x14]
        BX       lr
        ENDP


        AREA ||i.usart_stop_bit_set||, CODE, READONLY, ALIGN=1

usart_stop_bit_set PROC
        LDR      r2,[r0,#0x10]
        BIC      r2,r2,#0x3000
        STR      r2,[r0,#0x10]
        LDR      r2,[r0,#0x10]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_synchronous_clock_config||, CODE, READONLY, ALIGN=1

usart_synchronous_clock_config PROC
        PUSH     {r4-r6,lr}
        MOV      r4,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0x10]
        BIC      r1,r1,#0x700
        AND      r5,r4,#0x100
        AND      r6,r2,#0x200
        ORRS     r5,r5,r6
        AND      r6,r3,#0x400
        ORRS     r5,r5,r6
        ORRS     r1,r1,r5
        STR      r1,[r0,#0x10]
        POP      {r4-r6,pc}
        ENDP


        AREA ||i.usart_synchronous_clock_disable||, CODE, READONLY, ALIGN=1

usart_synchronous_clock_disable PROC
        LDR      r1,[r0,#0x10]
        BIC      r1,r1,#0x800
        STR      r1,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_synchronous_clock_enable||, CODE, READONLY, ALIGN=1

usart_synchronous_clock_enable PROC
        LDR      r1,[r0,#0x10]
        ORR      r1,r1,#0x800
        STR      r1,[r0,#0x10]
        BX       lr
        ENDP


        AREA ||i.usart_transmit_config||, CODE, READONLY, ALIGN=1

usart_transmit_config PROC
        MOV      r2,r1
        MOVS     r1,#0
        LDR      r1,[r0,#0xc]
        BIC      r1,r1,#8
        ORRS     r1,r1,r2
        STR      r1,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||i.usart_word_length_set||, CODE, READONLY, ALIGN=1

usart_word_length_set PROC
        LDR      r2,[r0,#0xc]
        BIC      r2,r2,#0x1000
        STR      r2,[r0,#0xc]
        LDR      r2,[r0,#0xc]
        ORRS     r2,r2,r1
        STR      r2,[r0,#0xc]
        BX       lr
        ENDP


        AREA ||.arm_vfe_header||, DATA, READONLY, NOALLOC, ALIGN=2

        DCD      0x00000000

;*** Start embedded assembler ***

#line 1 "..\\Firmware\\GD32F4xx_standard_peripheral\\Source\\gd32f4xx_usart.c"
	AREA ||.rev16_text||, CODE
	THUMB
	EXPORT |__asm___16_gd32f4xx_usart_c_988c0849____REV16|
#line 114 "..\\Firmware\\CMSIS\\core_cmInstr.h"
|__asm___16_gd32f4xx_usart_c_988c0849____REV16| PROC
#line 115

 rev16 r0, r0
 bx lr
	ENDP
	AREA ||.revsh_text||, CODE
	THUMB
	EXPORT |__asm___16_gd32f4xx_usart_c_988c0849____REVSH|
#line 128
|__asm___16_gd32f4xx_usart_c_988c0849____REVSH| PROC
#line 129

 revsh r0, r0
 bx lr
	ENDP

;*** End   embedded assembler ***

        EXPORT usart_address_config [CODE]
        EXPORT usart_baudrate_set [CODE]
        EXPORT usart_block_length_config [CODE]
        EXPORT usart_break_frame_coherence_config [CODE]
        EXPORT usart_data_first_config [CODE]
        EXPORT usart_data_receive [CODE]
        EXPORT usart_data_transmit [CODE]
        EXPORT usart_deinit [CODE]
        EXPORT usart_disable [CODE]
        EXPORT usart_dma_receive_config [CODE]
        EXPORT usart_dma_transmit_config [CODE]
        EXPORT usart_enable [CODE]
        EXPORT usart_flag_clear [CODE]
        EXPORT usart_flag_get [CODE]
        EXPORT usart_guard_time_config [CODE]
        EXPORT usart_halfduplex_disable [CODE]
        EXPORT usart_halfduplex_enable [CODE]
        EXPORT usart_hardware_flow_coherence_config [CODE]
        EXPORT usart_hardware_flow_cts_config [CODE]
        EXPORT usart_hardware_flow_rts_config [CODE]
        EXPORT usart_interrupt_disable [CODE]
        EXPORT usart_interrupt_enable [CODE]
        EXPORT usart_interrupt_flag_clear [CODE]
        EXPORT usart_interrupt_flag_get [CODE]
        EXPORT usart_invert_config [CODE]
        EXPORT usart_irda_lowpower_config [CODE]
        EXPORT usart_irda_mode_disable [CODE]
        EXPORT usart_irda_mode_enable [CODE]
        EXPORT usart_lin_break_detection_length_config [CODE]
        EXPORT usart_lin_mode_disable [CODE]
        EXPORT usart_lin_mode_enable [CODE]
        EXPORT usart_mute_mode_disable [CODE]
        EXPORT usart_mute_mode_enable [CODE]
        EXPORT usart_mute_mode_wakeup_config [CODE]
        EXPORT usart_oversample_config [CODE]
        EXPORT usart_parity_check_coherence_config [CODE]
        EXPORT usart_parity_config [CODE]
        EXPORT usart_prescaler_config [CODE]
        EXPORT usart_receive_config [CODE]
        EXPORT usart_receiver_timeout_disable [CODE]
        EXPORT usart_receiver_timeout_enable [CODE]
        EXPORT usart_receiver_timeout_threshold_config [CODE]
        EXPORT usart_sample_bit_config [CODE]
        EXPORT usart_send_break [CODE]
        EXPORT usart_smartcard_autoretry_config [CODE]
        EXPORT usart_smartcard_mode_disable [CODE]
        EXPORT usart_smartcard_mode_enable [CODE]
        EXPORT usart_smartcard_mode_nack_disable [CODE]
        EXPORT usart_smartcard_mode_nack_enable [CODE]
        EXPORT usart_stop_bit_set [CODE]
        EXPORT usart_synchronous_clock_config [CODE]
        EXPORT usart_synchronous_clock_disable [CODE]
        EXPORT usart_synchronous_clock_enable [CODE]
        EXPORT usart_transmit_config [CODE]
        EXPORT usart_word_length_set [CODE]

        IMPORT ||Lib$$Request$$armlib|| [CODE,WEAK]
        IMPORT rcu_periph_reset_enable [CODE]
        IMPORT rcu_periph_reset_disable [CODE]
        IMPORT rcu_clock_freq_get [CODE]

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