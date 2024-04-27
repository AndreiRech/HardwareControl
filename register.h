#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024

char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);

// DEFINIÇÃO DAS FUNÇÕES [ R0 ]
// DisplayOn
uint16_t getDisplayOn();
void setDisplayOn(int v);

// DisplayMode
uint16_t getDisplayMode();
void setDisplayMode(int mode);

// DisplaySpeed
uint16_t getDisplaySpeed();
void setDisplaySpeed(int speed);

// OperationLedOn
uint16_t getOperationLedOnOff();
void setOperationLedOnOff(int v);

// StatusLedColor
uint16_t getStatusLedColor();
void setStatusLedColor(int *red, int *green, int *blue);

// ResetRegisters
void resetRegisters();


// DEFINIÇÃO DAS FUNÇÕES [ R1 e R2 ]
// DisplayColor
void getDisplayColor(uint8_t *r, uint8_t *g, uint8_t *b);
void setDisplayColor(uint8_t r, uint8_t g, uint8_t b);


// DEFINIÇÃO DAS FUNÇÕES [ R3 ]
// BateryLevel
uint16_t getBatteryLevel();
void setBatteryLevel(uint16_t level);

// DisplayCount
int getDisplayCount();
void restartDisplayCount();
void increaseDisplayCount();

// Temperature
int getTemperature();
void setTemperature(int temperature);


// DEFINIÇÃO DAS FUNÇÕES [ R4 - R15 ]
// DisplayString
void setDisplayString();
void resetDisplayString();


// DEFINIÇÃO DE FUNÇÕES AUXILIARES
// PrintRegisterValues
void registersValues();

#endif