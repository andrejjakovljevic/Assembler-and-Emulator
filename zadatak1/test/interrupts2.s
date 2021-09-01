# file: interrupts.s
.section ivt
 .word isr_reset
 .skip 2 # isr_error
 .word isr_timer
 .word isr_terminal
 .skip 8
.extern myStart, myCounter, myChar, myBit
.section isr
.equ term_out, 0xFF00
.equ term_in, 0xFF02
.equ asciiCode, 84 # ascii(’T’)
# prekidna rutina za reset
isr_reset:
 jmp myStart                  
# prekidna rutina za tajmer
isr_timer:
 push r0	                    
 push r1
 ldr r0, myChar    				
 str r0, term_out							
 ldr r1, $1
 add r0, r1
 str r0, myChar
 pop r1
 pop r0												
 iret													
# prekidna rutina za terminal
isr_terminal:
 push r0											
 push r1											
 ldr r0, term_in
 ldr r1, $116
 cmp r0, r1
 jne %skipuj
 ldr r1, $0x2000
 str r1, myBit
 skipuj:							
 ldr r1, $97
 cmp r0, r1
 jne %ne_gasi
 halt
 ne_gasi:
 str r0, term_out							
 pop r1
 pop r0
 iret
.end
