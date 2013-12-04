################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lib/Prime.cpp \
../src/lib/RSA.cpp \
../src/lib/SSLKey.cpp 

OBJS += \
./src/lib/Prime.o \
./src/lib/RSA.o \
./src/lib/SSLKey.o 

CPP_DEPS += \
./src/lib/Prime.d \
./src/lib/RSA.d \
./src/lib/SSLKey.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


