#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include "register.h"
#include <string.h>

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024
#define NUM_REGISTERS 16

unsigned short *reg[NUM_REGISTERS];
unsigned short *base_address = NULL;

char* registers_map(const char* file_path, int file_size, int* fd) {
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1) {
        perror("Error opening or creating file");
        return NULL;
    }

    if (ftruncate(*fd, file_size) == -1) {
        perror("Error setting file size");
        close(*fd);
        return NULL;
    }

    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
        perror("Error mapping file");
        close(*fd);
        return NULL;
    }

    base_address = (unsigned short *)map;

    for (int i = 0; i < NUM_REGISTERS; i++){
        reg[i] = (unsigned short *)(base_address + i);
    }

    return map;
}

int registers_release(void* map, int file_size, int fd) {
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

//  FUNÇÕES DO R0
uint16_t getDisplayOn() {return *reg[0] & 0x01;}
const char* convertedGetDisplayOn(){
    int displayOn = getDisplayOn();

    if (displayOn == 1) {
        return "Display On";
    }
    return "Display Of";
}
void setDisplayOn(int v) {
    if(v > 1 || v < 0) return;
    *reg[0] = v ? (*reg[0] | 0x01) : (*reg[0] & ~0x01);
}

uint16_t getDisplayMode() {return (*reg[0] & 0x0006) >> 1;}   //0x0006 == 0000 0000 0000 0110

const char* convertedGetDisplayMode(){
    int displayMode = getDisplayMode();

    switch (displayMode) {
        case 0b00: // Modo estático
            return "Static";
            break;
        case 0b01: // Modo deslizante
            return "Sliding";
            break;
        case 0b10: // Modo intermitente
            return "Flashing";
            break;
        case 0b11: // Modo deslizante e intermitente
            return "Sliding and Flashing";
            break;
        default:
            break;
    }
}
void setDisplayMode(int mode) {
    if(mode > 4 || mode < 1) return;

    *r0 &= ~(0x3 << 1);

    switch (mode) {
        case 1: 
            *reg[0] |= (0x0 << 1);
            break;
        case 2:
            *reg[0] |= (0x1 << 1);
            break;
        case 3:
            *reg[0] |= (0x2 << 1);
            break;
        case 4:
            *reg[0] |= (0x3 << 1);
            break;
    }
}

uint16_t getDisplaySpeed() {return (*reg[0] >> 3) & 0x3F;}
const char* convertedGetDisplaySpeed(){
    int displaySpeed = getDisplaySpeed();

    static char displaySpeedString[7];  //aceita no maximo 5 caracteres + 'ms'

    snprintf(displaySpeedString, sizeof(displaySpeedString), "%d ms", displaySpeed * 100);

    return displaySpeedString;
}
void setDisplaySpeed(int speed) {
    if (speed < 0 || speed > 63) return;
    *reg[0] &= ~(0x3F << 3);
    *reg[0] |= (speed & 0x3F) << 3;
}

uint16_t getOperationLedOn() {return (*reg[0] >> 9) & 0x01;}
const char* convertedGetOperationLedOn(){
    int operationLed = getOperationLedOn();

    if(operationLed == 1){
        return "LED On";
    }
    return "LED Off";
}
void setOperationLedOn(int v) {
    if (v > 1 || v < 0) return;
    *reg[0] &= ~0x0200;
    *reg[0] |= (v << 9) & 0x0200;
}

uint16_t getStatusLedColor() {return (*reg[0] >> 10) & 0x07;}
const char* convertedGetStatusLedColor(){
    // 4 - vermelho     2 - verde  //6 - amarelo
    int statusColor = getStatusLedColor();

    switch (statusColor)
    {
    case 2:
        return "Verde [High/Medium]";
        break;
    case 4:
        return "Vermelho [Critical]";
        break;
    case 6:
        return "Amarelo [Low]";
        break;
    default:
        return "Unknown";   //se mudarem o LED manualmente para outras cores
        break;
    }

}
void setStatusLedColor(int *r, int *g, int *b) {
    if(*r>1 || *r<0 || *g>1 || *g<0 || *b>1 || *b<0) return;

    *reg[0] &= ~(0x07 << 10);
    *reg[0] |= (*b > 0.5) << 10;
    *reg[0] |= (*g > 0.5) << 11;
    *reg[0] |= (*r > 0.5) << 12;  
}

//  FUNÇÕES DO R1/R2
void getDisplayColor(uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = *reg[1] & 0xFF;
    *g = (*reg[1] >> 8) & 0xFF;
    *b = *reg[2] & 0xFF;
}
void setDisplayColor(uint8_t r, uint8_t g, uint8_t b) {
    if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) return;
    *reg[1] = r & 0xFF;
    *reg[1] |= (g << 8) & 0xFF00;
    *reg[2] = b & 0xFF;
}

//  FUNÇÕES DO R3
uint16_t getBatteryLevel(){return *reg[3] & 0x3;}

const char* convertedGetBatteryLevel() {
    int batteryLevel = getBatteryLevel();
    const char* batteryString;

    switch (batteryLevel)
    {
    case 0:
        batteryString = "critical";
        break;
    case 1:
        batteryString = "low";
        break;
    case 2:
        batteryString = "medium";
        break;
    case 3:
        batteryString = "high";
        break;
    default:
        break;
    }

    return batteryString;
}

void setBatteryLevel(uint16_t batteryLevel) {
    *reg[3] &= 0xFFFC;       
    *reg[3] |= (batteryLevel & 0x3); 

    int r, g, b;
    int level = getBatteryLevel();
    switch (level) {
        case 0:
            r = 1;
            g = 0;
            b = 0;
            break;
        case 1:
        case 2:
            r = 1;
            g = 1;
            b = 0;
            break;
        case 3:
            r = 0;
            g = 1;
            b = 0;
            break;
        default:
            return;
    }

    setStatusLedColor(&r, &g, &b);
}

float getTemperature(){
    uint16_t maskedValue = (*reg[3] & 0xFFC0) >> 6;

    int signBit = maskedValue & 0x0200;     //0x0200 == 0000 0010 0000 0000 [bit 9]

    //converte o valor para int16_t [lida com valores negativos em complemento de 2]
    int16_t temperature = (int16_t)(maskedValue & 0x01FF);    //0x01FF == 0000 0001 1111 1111

    if (signBit){
       temperature |= 0xFE00;    //0xFE00 == 1111 1110 0000 0000
    }
    
    float tempFloat = (float)temperature/10;

    return tempFloat;
}

void setTemperature(int temperature){ 
    int16_t tempValue;

    if( temperature >= 0 && temperature <= 999)
        tempValue = (int16_t)(temperature);
    else {   //temperatura negativa
        tempValue = (int16_t)(-temperature);
        tempValue = ~tempValue + 1; //complemento de dois [inverte os bits e soma 1]
        tempValue |= 0x8000;    //0x8000 == 1000 0000 0000 0000 [adiciona bit de sinal]
    }

    *reg[3] &= ~(0xFFC0); //0xFFC0 == 1111 1111 1100 0000 [limpando bits 6-15]

    *reg[3] |= (((uint16_t)tempValue) << 6) & 0xFFC0; //desloca tempValue para os bits 6-15 e faz um AND com a mascara, depois faz um OR com o registrador 
}

uint16_t getDisplayCount() {return (*reg[r3] >> 2) & 0xF;}
void restartDisplayCount() {
    *reg[r3] &= ~(0xF << 2);
    *reg[r3] |= (0 & 0xF) << 2;
};

//  FUNÇÕES DO R4-R15
void setDisplayString(const char *msg) {
    int length = strlen(msg);  
    resetDisplayString();

    for (int i = 0; i < length; i++) {
        *(reg[4] + i) = msg[i];
    }
}

void resetDisplayString() {
    memset(reg[4], 0, 12 * sizeof(unsigned short));
}

void resetRegisters() {
    setDisplayOn(1);
    setDisplayMode(1);
    setDisplaySpeed(2);
    setOperationLedOn(1);
    setDisplayColor(255,255,255);
    setBatteryLevel(11);
    restartDisplayCount();
    setTemperature(250);
}
