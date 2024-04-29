#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include "register.h"

unsigned short *base_address = NULL;
unsigned short *r0;
unsigned short *r1;
unsigned short *r2;
unsigned short *r3;
unsigned short *r4;
unsigned short *r5;
unsigned short *r6;
unsigned short *r7;
unsigned short *r8;
unsigned short *r9;
unsigned short *r10;
unsigned short *r11;
unsigned short *r12;
unsigned short *r13;
unsigned short *r14;
unsigned short *r15;

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024

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
    r0 = base_address + 0x00;
    r1 = base_address + 0x01;
    r2 = base_address + 0x02;
    r3 = base_address + 0x03;
    r4 = base_address + 0x04;
    r5 = base_address + 0x05;
    r6 = base_address + 0x06;
    r7 = base_address + 0x07;
    r8 = base_address + 0x08;
    r9 = base_address + 0x09;
    r10 = base_address + 0x0a;
    r11 = base_address + 0x0b;
    r12 = base_address + 0x0c;
    r13 = base_address + 0x0d;
    r14 = base_address + 0x0e;
    r15 = base_address + 0x0f;

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
uint16_t getDisplayOn() {return *r0 & 0x01;}
void setDisplayOn(int v) {
    if(v > 1 || v < 0) return;
    *r0 = v ? (*r0 | 0x01) : (*r0 & ~0x01);
}

uint16_t getDisplayMode() {}
void setDisplayMode(int mode) {}

uint16_t getDisplaySpeed() {return (*r0 >> 3) & 0x3F;}
void setDisplaySpeed(int speed) {
    if (speed < 0 || speed > 63) return;
    *r0 &= ~(0x3F << 3);
    *r0 |= (speed & 0x3F) << 3;
}

uint16_t getOperationLedOnOff() {return (*r0 >> 9) & 0x01;}
void setOperationLedOnOff(int v) {
    if (v > 1 || v < 0) return;
    *r0 &= ~0x0200;
    *r0 |= (v << 9) & 0x0200;
}

uint16_t getStatusLedColor() {return (*r0 >> 10) & 0x07;}
void setStatusLedColor(int *red, int *green, int *blue) {
    if(*red>1 || *red<0 || *green>1 || *green<0 || *blue>1 || *blue<0) return;

    *r0 &= ~(0x07 << 10);
    *r0 |= (*blue > 0.5) << 10;
    *r0 |= (*green > 0.5) << 11;
    *r0 |= (*red > 0.5) << 12;  
}

//  FUNÇÕES DO R1/R2
void getDisplayColor(uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = *r1 & 0xFF;
    *g = (*r1 >> 8) & 0xFF;
    *b = *r2 & 0xFF;
}
void setDisplayColor(uint8_t r, uint8_t g, uint8_t b) {
    if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0) return;
    *r1 = r & 0xFF;
    *r1 |= (g << 8) & 0xFF00;
    *r2 = b & 0xFF;
}

//  FUNÇÕES DO R3
uint16_t getBatteryLevel() {return *r3 & 0x3;}
void setBatteryLevel(uint16_t batteryLevel) {
    *r3 &= 0xFFFC;       
    *r3 |= (batteryLevel & 0x3); 

    int red, green, blue;
    int level = getBatteryLevel();
    switch (level) {
        case 0:
            red = 1;
            green = 0;
            blue = 0;
            break;
        case 1:
        case 2:
            red = 1;
            green = 1;
            blue = 0;
            break;
        case 3:
            red = 0;
            green = 1;
            blue = 0;
            break;
        default:
            return;
    }

    setStatusLedColor(&red, &green, &blue);
}