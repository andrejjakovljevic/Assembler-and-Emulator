# file: main.s
.global myStart
.global myCounter
.global myChar
.global myBit
.section myCode
.equ tim_cfg, 0xFF10
myStart:
 ldr r0, $0x1
 str r0, tim_cfg
wait:
 ldr r0, myCounter
 ldr r1, $5
 cmp r0, r1
 ldr r1, myBit
 or psw, r1
 jne wait
 halt
.section myData
myCounter:
 .word 0
myChar:
 .word 0x41
myBit:
 .word 0
.end
