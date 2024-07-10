	AREA    Bootloader_Section, DATA, READONLY
; Includes the binary file ../ExtMem_Boot/bootloader.bin from the current source folder
        INCBIN  ../ExtMem_Boot/bootloader.bin
        END