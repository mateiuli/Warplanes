################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Aircraft.o \
../Application.o \
../Button.o \
../Command.o \
../CommandQueue.o \
../Component.o \
../Container.o \
../DataTables.o \
../Entity.o \
../FadeInState.o \
../FadeOutState.o \
../GameState.o \
../Label.o \
../LoadingState.o \
../MenuState.o \
../ParallelTask.o \
../PauseState.o \
../Player.o \
../Projectile.o \
../SceneNode.o \
../SettingsState.o \
../SpriteNode.o \
../State.o \
../StateStack.o \
../TextNode.o \
../TitleState.o \
../Utility.o \
../World.o \
../main.o 

CPP_SRCS += \
../Aircraft.cpp \
../Application.cpp \
../Button.cpp \
../Command.cpp \
../CommandQueue.cpp \
../Component.cpp \
../Container.cpp \
../DataTables.cpp \
../Entity.cpp \
../FadeInState.cpp \
../FadeOutState.cpp \
../Game.cpp \
../GameState.cpp \
../Label.cpp \
../LoadingState.cpp \
../MenuState.cpp \
../ParallelTask.cpp \
../PauseState.cpp \
../Player.cpp \
../Projectile.cpp \
../SceneNode.cpp \
../SettingsState.cpp \
../SpriteNode.cpp \
../State.cpp \
../StateStack.cpp \
../TextNode.cpp \
../TitleState.cpp \
../Utility.cpp \
../World.cpp \
../main.cpp 

OBJS += \
./Aircraft.o \
./Application.o \
./Button.o \
./Command.o \
./CommandQueue.o \
./Component.o \
./Container.o \
./DataTables.o \
./Entity.o \
./FadeInState.o \
./FadeOutState.o \
./Game.o \
./GameState.o \
./Label.o \
./LoadingState.o \
./MenuState.o \
./ParallelTask.o \
./PauseState.o \
./Player.o \
./Projectile.o \
./SceneNode.o \
./SettingsState.o \
./SpriteNode.o \
./State.o \
./StateStack.o \
./TextNode.o \
./TitleState.o \
./Utility.o \
./World.o \
./main.o 

CPP_DEPS += \
./Aircraft.d \
./Application.d \
./Button.d \
./Command.d \
./CommandQueue.d \
./Component.d \
./Container.d \
./DataTables.d \
./Entity.d \
./FadeInState.d \
./FadeOutState.d \
./Game.d \
./GameState.d \
./Label.d \
./LoadingState.d \
./MenuState.d \
./ParallelTask.d \
./PauseState.d \
./Player.d \
./Projectile.d \
./SceneNode.d \
./SettingsState.d \
./SpriteNode.d \
./State.d \
./StateStack.d \
./TextNode.d \
./TitleState.d \
./Utility.d \
./World.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


