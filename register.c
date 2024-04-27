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

// R0 (0) Liga/Desliga o display
uint16_t getDisplayOn() {return *r0 & 0x0001; }
void setDisplayOn(int v) {
    if(v > 1 || v < 0) return;
    *r0 = v ? (*r0 | 0x01) : (*r0 & ~0x01);
}

// R0 (1-2) Selecionar o modo de exibição
uint16_t getDisplayMode() {}
void setDisplayMode(int mode) {}

// R0 (3-8) Define velocidade de atualização do display em valores múltiplos de 100 milisegundos para modo de exibição não estático
uint16_t getDisplaySpeed() {}
void setDisplaySpeed(int speed) {}

// R0 (9) Liga/Desliga o LED de operação
uint16_t getOperationLedOnOff() {}
void setOperationLedOnOff(int v) {
    if (v > 1 || v < 0) return;
    //0x0200 == 0000 0010 0000 0000 
    *r0 &= ~0x0200;
    *r0 |= (v << 9) & 0x0200;

}

// R0 (10-12) Liga/Desliga o LED de status e define cor
uint16_t getStatusLedColor() {return *r0 & 0x0E00;}
void setStatusLedColor(int *red, int *green, int *blue) {
    if(*red>1 || *red<0 || *green>1 || *green<0 || *blue>1 || *blue<0) return;

    *r0 |= (*red > 0.5) << 10;
    *r0 |= (*green > 0.5) << 11;
    *r0 |= (*blue > 0.5) << 12;
}


//  FUNÇÕES DO R1



//  FUNÇÕES DO R2


//  FUNÇÕES DO R3

// R3(0-1)  Nível da bateria
uint16_t getBatteryLevel() {return *r3 & 0x003;}    //mask 0x003 == 0011
void setBatteryLevel(uint16_t batteryLevel) {
    *r3 &= 0xFFFC;        //0xFFFC == 1111 1111 1111 1100  //limpa os dois primeiros bits
    *r3 |= (batteryLevel & 0x0003); //faz um AND do (batterylevel) com (0000 0000 0000 0011)
}
 


