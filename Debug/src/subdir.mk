################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deck.cpp \
../src/Hand.cpp \
../src/Player.cpp \
../src/Table.cpp \
../src/shark.cpp 

OBJS += \
./src/Deck.o \
./src/Hand.o \
./src/Player.o \
./src/Table.o \
./src/shark.o 

CPP_DEPS += \
./src/Deck.d \
./src/Hand.d \
./src/Player.d \
./src/Table.d \
./src/shark.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


