################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/task_handler/task_handler.c 

OBJS += \
./User/task_handler/task_handler.o 

C_DEPS += \
./User/task_handler/task_handler.d 


# Each subdirectory must supply rules for building sources it contributes
User/task_handler/%.o: ../User/task_handler/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\CH32V307VCT6-Task-Handler\Debug" -I"C:\MRS_DATA\workspace\CH32V307VCT6-Task-Handler\Core" -I"C:\MRS_DATA\workspace\CH32V307VCT6-Task-Handler\User" -I"C:\MRS_DATA\workspace\CH32V307VCT6-Task-Handler\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

