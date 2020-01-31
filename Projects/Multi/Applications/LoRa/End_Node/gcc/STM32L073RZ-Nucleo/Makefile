# STM32 Makefile for GNU toolchain and openocd
#
# This Makefile fetches the Cube firmware package from ST's' website.
# This includes: CMSIS, STM32 HAL, BSPs, USB drivers and examples.
#
# Usage:
#	make cube		Download and unzip Cube firmware
#	make program		Flash the board with OpenOCD
#	make openocd		Start OpenOCD
#	make debug		Start GDB and attach to OpenOCD
#	make dirs		Create subdirs like obj, dep, ..
#	make template		Prepare a simple example project in this dir
#
# Copyright	2015 Steffen Vogel
# License	http://www.gnu.org/licenses/gpl.txt GNU Public License
# Author	Steffen Vogel <post@steffenvogel.de>
# Link		http://www.steffenvogel.de
#
# edited for the STM32F4-Discovery

# A name common to all output files (elf, map, hex, bin, lst)
TARGET     = end_node

# Take a look into $(CUBE_DIR)/Drivers/BSP for available BSPs
# name needed in upper case and lower case
BOARD      = STM32L073RZ-Nucleo
BOARD_UC   = STM32L0XX_NUCLEO
BOARD_MC   = STM32L0xx_Nucleo
BOARD_LC   = stm32l0xx_nucleo
RADIO      = sx1272
COMPONENT  = sx1272mb2das

OCDFLAGS   = -f openocd.cfg
GDBFLAGS   = -iex 'set auto-load safe-path ./'

#EXAMPLE   = Templates
APP_ROOT   = ../..

# MCU family and type in various capitalizations o_O
MCU_FAMILY = stm32l0xx
MCU_FAM_MC = STM32L0xx
MCU_LC     = stm32l073xx
MCU_MC     = STM32L073xx
MCU_UC     = STM32L073RZ

# path of the ld-file inside the example directories
LDFILE     = $(APP_ROOT)/SW4STM32/$(BOARD)/$(COMPONENT)/$(MCU_UC)Tx_FLASH.ld
#LDFILE     = $(EXAMPLE)/TrueSTUDIO/$(BOARD_UC)/$(MCU_UC)_FLASH.ld

# Your C files from the /src directory
SRCS       = main.c
SRCS	+= $(BOARD_LC).c
SRCS      += system_$(MCU_FAMILY).c
SRCS      += $(MCU_FAMILY)_it.c
SRCS      += $(MCU_FAMILY)_hw.c
SRCS      += $(MCU_FAMILY)_hal_msp.c
SRCS      += bsp.c
SRCS      += debug.c
SRCS      += hw_gpio.c
SRCS      += hw_rtc.c
SRCS      += hw_spi.c
SRCS      += vcom.c

# Basic HAL libraries
SRCS      += $(MCU_FAMILY)_hal_spi.c
SRCS      += $(MCU_FAMILY)_hal_uart.c
SRCS      += $(MCU_FAMILY)_hal_uart_ex.c
SRCS      += $(MCU_FAMILY)_hal_adc.c
SRCS      += $(MCU_FAMILY)_hal_adc_ex.c
SRCS      += $(MCU_FAMILY)_hal_rcc.c
SRCS      += $(MCU_FAMILY)_hal_rcc_ex.c
SRCS      += $(MCU_FAMILY)_hal.c
SRCS      += $(MCU_FAMILY)_hal_cortex.c
SRCS      += $(MCU_FAMILY)_hal_gpio.c
SRCS      += $(MCU_FAMILY)_hal_dma.c
SRCS      += $(MCU_FAMILY)_hal_pwr.c
SRCS      += $(MCU_FAMILY)_hal_pwr_ex.c
SRCS      += $(MCU_FAMILY)_hal_rtc.c
SRCS      += $(MCU_FAMILY)_hal_rtc_ex.c
SRCS      += $(MCU_FAMILY)_hal_tim.c
SRCS      += $(MCU_FAMILY)_hal_tim_ex.c
SRCS      += $(MCU_FAMILY)_hal_i2c.c
SRCS      += $(MCU_FAMILY)_ll_tim.c
# LoRa
SRCS      += lora.c
SRCS      += LoRaMac.c
SRCS      += LoRaMacCrypto.c
SRCS      += Region.c
#SRCS      += RegionAS923.c
#SRCS      += RegionAU915.c
#SRCS      += RegionCN470.c
#SRCS      += RegionCN779.c
SRCS      += RegionCommon.c
#SRCS      += RegionEU433.c
SRCS      += RegionEU868.c
#SRCS      += RegionIN865.c
#SRCS      += RegionKR920.c
#SRCS      += RegionUS915.c
#SRCS      += RegionUS915-Hybrid.c
SRCS      += delay.c
SRCS      += low_power.c
SRCS      += timeServer.c
SRCS      += utilities.c
SRCS      += aes.c
SRCS      += cmac.c

# DHT11
SRCS	+= tim2.c
SRCS	+= DHT11_by_us.c

# Drivers/BSP/Components
# SRCS      += HTS221_Driver.c
# SRCS      += HTS221_Driver_HL.c
# SRCS      += LPS25HB_Driver.c
# SRCS      += LPS25HB_Driver_HL.c
# SRCS      += LPS22HB_Driver.c
# SRCS      += LPS22HB_Driver_HL.c
SRCS      += $(RADIO).c

# Drivers/BSP/...
SRCS      += $(COMPONENT).c

# Directories

CUBE_DIR   = ../../../../../../..

BSP_DIR    = $(CUBE_DIR)/Drivers/BSP/
HAL_DIR    = $(CUBE_DIR)/Drivers/$(MCU_FAM_MC)_HAL_Driver
CMSIS_DIR  = $(CUBE_DIR)/Drivers/CMSIS

DEV_DIR    = $(CMSIS_DIR)/Device/ST/$(MCU_FAM_MC)

COMP_DIR   = $(BSP_DIR)/Components
MWARE_DIR  = $(CUBE_DIR)/Middlewares/Third_Party

CUBE_URL   = http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stm32cubel0.zip

# that's it, no need to change anything below this line!

###############################################################################
# Toolchain

PREFIX     = arm-none-eabi
CC         = $(PREFIX)-gcc
AR         = $(PREFIX)-ar
OBJCOPY    = $(PREFIX)-objcopy
OBJDUMP    = $(PREFIX)-objdump
SIZE       = $(PREFIX)-size
GDB        = gdb-multiarch

OCD        = openocd

###############################################################################
# Options

# Defines
DEFS       = -D$(MCU_MC) -DUSE_HAL_DRIVER
DEFS	+= -DUSE_FULL_LL_DRIVER
DEFS	+= -DUSE_DHT11


# LoRa
DEFS       += -DUSE_STM32L0XX_NUCLEO
DEFS       += -DREGION_EU868
# Debug specific definitions for semihosting
DEFS       += -DUSE_DBPRINTF
DEFS	+= -DTRACE
DEFS	+= -DDEBUG

# Include search paths (-I)
INCS       = -I$(APP_ROOT)/inc
INCS      += -I$(CUBE_DIR)/Drivers/BSP/$(BOARD_MC)
# INCS      += -I$(CMSIS_DIR)/Include
INCS      += -I$(DEV_DIR)/Include
INCS      += -I$(HAL_DIR)/Inc

INCS      += -I$(COMP_DIR)/Common
INCS      += -I$(COMP_DIR)/hts221
INCS      += -I$(COMP_DIR)/lps22hb
INCS      += -I$(COMP_DIR)/lps25hb
INCS      += -I$(COMP_DIR)/$(RADIO)
INCS	  += -I$(CMSIS_DIR)/Include
# LoRa
INCS      += -I$(MWARE_DIR)/Lora/Crypto
INCS      += -I$(MWARE_DIR)/Lora/Core
INCS      += -I$(MWARE_DIR)/Lora/Mac
INCS      += -I$(MWARE_DIR)/Lora/Mac/region
INCS      += -I$(MWARE_DIR)/Lora/Phy
INCS      += -I$(MWARE_DIR)/Lora/Utilities
INCS 	+= -I$(BSP_DIR)/$(BOARD_MC)
INCS 	+= -I$(BSP_DIR)/$(COMPONENT)
# Library search paths
# LIBS       = -L$(CMSIS_DIR)/Lib

DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -Os
# Compiler flags
# CFLAGS	= $(DEBUG_FLAGS)
CFLAGS 	= $(RELEASE_FLAGS)
CFLAGS    += -Wall -std=c99
CFLAGS    += -mcpu=cortex-m0plus -mthumb
#CFLAGS    += -Wextra
CFLAGS    += -Wno-unused-parameter -Wno-missing-field-initializers
CFLAGS    += -fmessage-length=0 -fno-exceptions -fno-builtin -funsigned-char
CFLAGS    += -MMD -fno-delete-null-pointer-checks -fomit-frame-pointer
#CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    += -ffunction-sections -fdata-sections
CFLAGS    += $(INCS) $(DEFS)

# Linker flags
LDFLAGS    = -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -T$(LDFILE)

# Enable Semihosting
LDFLAGS   += --specs=rdimon.specs -lc -lrdimon

# Source search paths
VPATH      = $(APP_ROOT)/src
 VPATH     += $(BSP_DIR)/$(COMPONENT)
VPATH     += $(HAL_DIR)/Src
VPATH     += $(DEV_DIR)/Source
VPATH     += $(DEV_DIR)/Source/Templates
VPATH	+= $(BSP_DIR)/$(BOARD_MC)

# Components
# VPATH     += $(COMP_DIR)/hts221
# VPATH     += $(COMP_DIR)/lps25hb
# VPATH     += $(COMP_DIR)/lps22hb
VPATH     += $(COMP_DIR)/$(RADIO)

# LoRa
VPATH     += $(MWARE_DIR)/Lora/Crypto
VPATH     += $(MWARE_DIR)/Lora/Core
VPATH     += $(MWARE_DIR)/Lora/Mac
VPATH     += $(MWARE_DIR)/Lora/Mac/region
VPATH     += $(MWARE_DIR)/Lora/Phy
VPATH     += $(MWARE_DIR)/Lora/Utilities

OBJS       = $(addprefix obj/,$(SRCS:.c=.o))
DEPS       = $(addprefix dep/,$(SRCS:.c=.d))

# Prettify output
V = 1
ifeq ($V, 0)
	Q = @
	P = > /dev/null
endif

###################################################

.PHONY: all dirs program debug template clean

all: $(TARGET).bin

-include $(DEPS)

dirs: dep obj
dep obj src:
	@echo "[MKDIR]   $@"
	$Qmkdir -p $@

obj/%.o : %.c | dirs
	@echo "[CC]      $<"
	@$Q$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(TARGET).elf: $(OBJS)
	@echo -e "[LD]     LDFLAGS=$(LDFLAGS)\n ASSEMBLY=$(APP_ROOT)/SW4STM32/$(BOARD)/startup_$(MCU_LC).s $(TARGET).elf"
	$Q$(CC) $(CFLAGS) $(LDFLAGS) $(APP_ROOT)/SW4STM32/$(BOARD)/startup_$(MCU_LC).s $^ -o $@
	@echo "[OBJDUMP] $(TARGET).lst"
	$Q$(OBJDUMP) -St $(TARGET).elf >$(TARGET).lst
	@echo "[SIZE]    $(TARGET).elf"
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	@echo "[OBJCOPY] $(TARGET).bin"
	$Q$(OBJCOPY) -O binary $< $@

openocd:
	$(OCD) $(OCDFLAGS) -c "init; reset halt"

program: all
	$(OCD) $(OCDFLAGS) -c "init" -c  "program $(TARGET).elf verify reset exit"

GDBCMD = $(GDB) $(GDBFLAGS) $(TARGET).elf
debug:
	@if ! nc -z localhost 3333; then \
		echo "\n\t[Error] OpenOCD is not running! Start it with: 'make openocd'\n"; exit 1; \
	else \
		if command -v ddd >/dev/null; then \
			rm -rf "~/.ddd"; \
			ddd --debugger "$(GDBCMD)" >/dev/null 2>&1 & \
		else \
			$(GDBCMD); \
			echo "\n\n\n\nTry installing ddd, it can simplify your life! ;)\n"; \
		fi \
	fi

cube:
	rm -fr $(CUBE_DIR)
	wget -O /tmp/cube.zip $(CUBE_URL)
	unzip /tmp/cube.zip
	mv STM32Cube* $(CUBE_DIR)
	chmod -R u+w $(CUBE_DIR)
	rm -f /tmp/cube.zip

template: cube src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Src/* src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Inc/* src
	cp -i $(DEV_DIR)/Source/Templates/gcc/startup_$(MCU_LC).s src
	cp -i $(CUBE_DIR)/Projects/$(BOARD)/$(LDFILE) $(MCU_LC).ld

clean:
	@echo "[RM]      $(TARGET).bin"; rm -f $(TARGET).bin
	@echo "[RM]      $(TARGET).elf"; rm -f $(TARGET).elf
	@echo "[RM]      $(TARGET).map"; rm -f $(TARGET).map
	@echo "[RM]      $(TARGET).lst"; rm -f $(TARGET).lst
	@echo "[RMDIR]   dep"          ; rm -fr dep
	@echo "[RMDIR]   obj"          ; rm -fr obj

