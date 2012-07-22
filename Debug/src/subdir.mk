################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm.cpp \
../src/Connector.cpp \
../src/Laser.cpp \
../src/Sick.cpp \
../src/TS.cpp \
../src/TSOA.cpp 

OBJS += \
./src/Algorithm.o \
./src/Connector.o \
./src/Laser.o \
./src/Sick.o \
./src/TS.o \
./src/TSOA.o 

CPP_DEPS += \
./src/Algorithm.d \
./src/Connector.d \
./src/Laser.d \
./src/Sick.d \
./src/TS.d \
./src/TSOA.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-3.0/ -O0 -g3 -Wall -c -fmessage-length=0 `pkg-config --cflags playerc++` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


