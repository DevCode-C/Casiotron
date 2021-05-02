CC = arm-none-eabi-gcc
MACH = cortex-m0
HEADERS = -I ../half0/Inc -I ../cmsisf0/registers -I ../cmsisf0/Core -I . -I tasks
VPATH = ../half0/Src ../cmsisf0/startups tasks
CFLAGS = $(HEADERS) -g3 -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=c11 -Wall -O0 -DSTM32F072xB -DUSE_HAL_DRIVER
LDFLAGS = -g3 -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs --specs=nano.specs -T STM32F072RBTx_FLASH.ld 
LDFLAGS += -Wl,-Map=Output/$(TARGET).map -Wl,--gc-sections
OBJS = main.o ints.o msps.o clock.o serial.o lcd.o startup_stm32f072xb.o system_stm32f0xx.o 
OBJS += stm32f0xx_hal.o stm32f0xx_hal_cortex.o stm32f0xx_hal_gpio.o stm32f0xx_hal_rcc.o 
OBJS += stm32f0xx_hal_uart.o stm32f0xx_hal_dma.o stm32f0xx_hal_uart_ex.o stm32f0xx_hal_rtc.o 
OBJS += stm32f0xx_hal_rtc_ex.o stm32f0xx_hal_pwr.o stm32f0xx_hal_pwr_ex.o stm32f0xx_hal_wwdg.o 
OBJS += stm32f0xx_hal_spi.o stm32f0xx_hal_spi_ex.o 
TARGET = Proyecto

all: $(TARGET)

$(TARGET): $(addprefix Output/,$(TARGET).elf)
	arm-none-eabi-objcopy -Oihex $< Output/$(TARGET).hex
	arm-none-eabi-objdump -S $< >Output/$(TARGET).lst
	arm-none-eabi-size --format=berkeley $<

Output/$(TARGET).elf: $(addprefix Output/Objs/,$(OBJS))
	@$(CC) $(LDFLAGS) -o $@ $^

Output/Objs/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

Output/Objs/%.o: %.s
	arm-none-eabi-as -mcpu=$(MACH) -mthumb -o $@ $^ 

.PHONY : clean
clean :
	@rm -rf Output/Objs/*.o Output/*.elf Output/*.lst Output/*.hex Output/*.lst Output/*.map 
load :
	@openocd -f board/st_nucleo_f0.cfg
debug:
	@arm-none-eabi-gdb Output/$(TARGET).elf