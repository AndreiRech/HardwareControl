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
#define NUM_REGISTERS 16

extern unsigned short *reg[NUM_REGISTERS];
extern unsigned short *base_address;

char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);

// DEFINIÇÃO DAS FUNÇÕES [ R0 ]
// DisplayOn
uint16_t getDisplayOn();
const char* convertedGetDisplayOn();
void setDisplayOn(int v);

// DisplayMode
uint16_t getDisplayMode();
const char* convertedGetDisplayMode();
void setDisplayMode(int mode);

// DisplaySpeed
uint16_t getDisplaySpeed();
const char* convertedGetDisplaySpeed();
void setDisplaySpeed(int speed);

// OperationLedOn
uint16_t getOperationLedOn();
const char* convertedGetOperationLedOn();
void setOperationLedOn(int v);

// StatusLedColor
uint16_t getStatusLedColor();
const char* convertedGetStatusLedColor();
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
const char* convertedGetBatteryLevel();
void setBatteryLevel(uint16_t level);

// DisplayCount
int getDisplayCount();
void restartDisplayCount();
void increaseDisplayCount();

// Temperature
float getTemperature();
void setTemperature(int temperature);


// DEFINIÇÃO DAS FUNÇÕES [ R4 - R15 ]
// DisplayString
void setDisplayString(const char *msg);
void resetDisplayString();


// DEFINIÇÃO DE FUNÇÕES AUXILIARES
// PrintRegisterValues
void registersValues();

#endif