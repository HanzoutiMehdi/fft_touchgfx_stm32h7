
# Helper macros to convert spaces into question marks and back again
e :=
sp := $(e) $(e)
qs = $(subst ?,$(sp),$1)
sq = $(subst $(sp),?,$1)

# Get name of this Makefile (avoid getting word 0 and a starting space)
makefile_name := $(wordlist 1,1000,$(MAKEFILE_LIST))

# Get path of this Makefile
makefile_path := $(call qs,$(dir $(call sq,$(abspath $(call sq,$(makefile_name))))))

# Get path where the Application is
application_path := $(call qs,$(abspath $(call sq,$(makefile_path)..)))

# Change makefile_name to a relative path
makefile_name := $(subst $(call sq,$(application_path))/,,$(call sq,$(abspath $(call sq,$(makefile_name)))))

# Get relative path to makefile from application_path
makefile_path_relative := $(subst $(call sq,$(application_path))/,,$(call sq,$(abspath $(call sq,$(makefile_path)))))

board_name := STM32H750_DK_ExtMemBoot

build_root_path := gcc/build
object_output_path := $(build_root_path)/$(board_name)
binary_output_path := $(build_root_path)/bin

.PHONY: all clean flash

all: $(filter clean,$(MAKECMDGOALS))
all clean assets:
	@cd "$(application_path)" && $(MAKE) -r -f $(makefile_name) -s $(MFLAGS) _$@_

flash intflash: all
	@cd "$(application_path)" && $(MAKE) -r -f $(makefile_name) -s $(MFLAGS) _$@_

ifeq ($(OS),Windows_NT)
UNAME := MINGW32_NT-6.2
else
UNAME := $(shell uname -s)
endif

Drivers_path := ../Drivers

source := \
	Src/fmc.c \
	Src/main.c \
	Src/memory_msp.c \
	Src/qspi.c \
	Src/stm32h7xx_it.c \
	Src/system_stm32h7xx.c

drivers := \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
	$(Drivers_path)/BSP/Components/mt25tl01g/mt25tl01g.c

asm_source_files := \
	$(makefile_path_relative)/startup_stm32h750xx.s

board_include_paths := \
  Inc \
	$(Drivers_path)/STM32H7xx_HAL_Driver/Inc \
	$(Drivers_path)/CMSIS/Include \
	$(Drivers_path)/CMSIS/Device/ST/STM32H7xx/Include \
	$(Drivers_path)/BSP/STM32H750B-DK \
	$(Drivers_path)/BSP/Components


include_paths := $(board_include_paths)
stm32cubeProgrammer := STMicroelectronics\\STM32Cube\\STM32CubeProgrammer\\bin\\STM32_Programmer_CLI.exe
ifneq ("$(shell find "$(PROGRAMFILES)\\$(stm32cubeProgrammer)" 2> /dev/null )","")
# STM32CubeProgrammer is placed in Program Files (x86)
st_stm32cube_programmer := "$(PROGRAMFILES)\\$(stm32cubeProgrammer)"
else
# STM32CubeProgrammer is placed in Program Files
st_stm32cube_programmer := "$(PROGRAMW6432)\\$(stm32cubeProgrammer)"
endif

target_executable := bootloader.elf
target_hex := bootloader.hex
target_bin := bootloader.bin

assembler         := arm-none-eabi-gcc
assembler_options += -g  \
                    -fno-exceptions\
                    $(no_libs) -mthumb -mno-thumb-interwork  \
                     -Wall
assembler_options += $(float_options)

c_compiler         := arm-none-eabi-gcc
c_compiler_options += -g \
                    -mthumb -fno-exceptions \
                    -mno-thumb-interwork -std=c99 \
                    $(no_libs) \
                    -Os -fno-strict-aliasing -fdata-sections -ffunction-sections

c_compiler_options += $(float_options)

cpp_compiler         := arm-none-eabi-g++
cpp_compiler_options += -g -mthumb \
                    $(no_libs) \
                    -mno-thumb-interwork -fno-rtti -fno-exceptions  \
                    -Os -fno-strict-aliasing -fdata-sections -ffunction-sections

cpp_compiler_options += $(float_options)

linker         := arm-none-eabi-g++
linker_options += -g -Wl,-static -mthumb $(no_libs) -mno-thumb-interwork \
                  -fno-exceptions -specs=nosys.specs -fno-rtti \
                  -Os -fno-strict-aliasing -Wl,--gc-sections

objcopy := arm-none-eabi-objcopy

archiver := arm-none-eabi-ar

strip := arm-none-eabi-strip

# Additional toolchain configuration for Cortex-M7 targets.

float_options := -mfpu=fpv5-sp-d16 -mfloat-abi=softfp

assembler_options += -mthumb -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq=""
c_compiler_options += -mthumb -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq=""
cpp_compiler_options += -mthumb -mcpu=cortex-m7 -Wno-psabi $(float_options) -DCORE_M7 -D__irq=""
linker_options += -mcpu=cortex-m7 -Wno-psabi $(float_options)

c_compiler_options += -DSTM32H750xx -DUSE_HAL_DRIVER
cpp_compiler_options += -DSTM32H750xx -DUSE_HAL_DRIVER

include_paths += platform/os $(board_include_paths)

object_files := $(source) $(drivers) $(middlewares)
object_files := $(object_files:$(Middlewares_path)/%.c=$(object_output_path)/Middlewares/%.o)
object_files := $(object_files:$(Drivers_path)/%.c=$(object_output_path)/Drivers/%.o)
object_files := $(object_files:%.c=$(object_output_path)/%.o)
dependency_files := $(object_files:%.o=%.d)

object_asm_files := $(asm_source_files:%.s=$(object_output_path)/%.o)
object_asm_files := $(patsubst $(object_output_path)/%,$(object_output_path)/%,$(object_asm_files))

.PHONY: _all_ _clean_ _flash_

_all_: $(binary_output_path)/$(target_executable)

_flash_:
	@$(st_stm32cube_programmer) -c port=SWD -d $(binary_output_path)/bootloader.hex -hardRst

$(binary_output_path)/$(target_executable): $(object_files) $(object_asm_files)
	@echo Linking $(@)
	@mkdir -p $(@D)
	@mkdir -p $(object_output_path)
	@$(file >$(build_root_path)/objects.tmp) $(foreach F,$(object_files),$(file >>$(build_root_path)/objects.tmp,$F))
	@$(linker) \
		$(linker_options) -T $(makefile_path_relative)/STM32H750XBHx_FLASH.ld -Wl,-Map=$(@D)/application.map $(linker_options_local) \
		$(patsubst %,-L%,$(library_include_paths)) \
		@$(build_root_path)/objects.tmp $(object_asm_files) -o $@ \
		-Wl,--start-group $(patsubst %,-l%,$(libraries)) -Wl,--end-group
	@rm -f $(build_root_path)/objects.tmp
	@$(objcopy) -O ihex $@ $(@D)/$(target_hex)
	$(objcopy) -O binary $@ $(@D)/$(target_bin)

$(object_output_path)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(c_compiler) \
		-MMD -MP $(c_compiler_options) $(c_compiler_options_local) $(user_cflags) \
		$(patsubst %,-I%,$(include_paths)) \
		-c $< -o $@

$(object_output_path)/Middlewares/%.o: $(Middlewares_path)/%.c
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(c_compiler) \
		-MMD -MP $(c_compiler_options) $(c_compiler_options_local) $(user_cflags) \
		$(patsubst %,-I%,$(include_paths)) \
		-c $< -o $@

$(object_output_path)/Drivers/%.o: $(Drivers_path)/%.c
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(c_compiler) \
		-MMD -MP $(c_compiler_options) $(c_compiler_options_local) $(user_cflags) \
		$(patsubst %,-I%,$(include_paths)) \
		-c $< -o $@

$(object_output_path)/%.o: %.s
	@echo Compiling ASM $<
	@mkdir -p $(@D)
	@$(assembler) \
		$(assembler_options) \
		$(patsubst %,-I %,$(os_include_paths)) \
		-c $< -o $@

_clean_:
	@echo Cleaning: $(board_name)
	@rm -rf $(build_root_path)
