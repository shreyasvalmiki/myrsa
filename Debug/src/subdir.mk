################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Crypt.cpp \
../src/Cryptography.cpp \
../src/KeyGen.cpp \
../src/TestSSL.cpp 

OBJS += \
./src/Crypt.o \
./src/Cryptography.o \
./src/KeyGen.o \
./src/TestSSL.o 

CPP_DEPS += \
./src/Crypt.d \
./src/Cryptography.d \
./src/KeyGen.d \
./src/TestSSL.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


