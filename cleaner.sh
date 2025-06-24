#!/bin/bash

# Script clean projects from useless files, examples, includes and etc
# First parameter is directory name

cd $1
find ./Drivers/CMSIS/Device/ST/STM32F4xx/Include/ -maxdepth 1 -type f ! -name "stm32f4xx.h" ! -name "stm32f429xx.h" ! -name "system_stm32f4xx.h"
find ./Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/arm/ -maxdepth 1 -type f ! -name "startup_stm32f429xx.s"
find ./Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/ -maxdepth 1 -type f ! -name "startup_stm32f429xx.s"
find ./Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/ -maxdepth 1 -type f ! -name "startup_stm32f429xx.s"
find ./Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/linker/ -maxdepth 1 -type f ! -name "stm32f429xx_sram.icf" ! -name "stm32f429xx_flash.icf"
rm -rf ./Drivers/CMSIS/DSP/Examples/