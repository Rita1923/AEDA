################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AgenciaViagens.cpp \
../Alojamento.cpp \
../Cliente.cpp \
../Itinerario.cpp \
../Pacote.cpp \
../Troco.cpp \
../Viagem.cpp \
../main.cpp 

OBJS += \
./AgenciaViagens.o \
./Alojamento.o \
./Cliente.o \
./Itinerario.o \
./Pacote.o \
./Troco.o \
./Viagem.o \
./main.o 

CPP_DEPS += \
./AgenciaViagens.d \
./Alojamento.d \
./Cliente.d \
./Itinerario.d \
./Pacote.d \
./Troco.d \
./Viagem.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


