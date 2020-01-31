target extended localhost:3333
monitor arm semihosting enable
monitor reset halt
load
monitor reset init
tbreak main
continue
