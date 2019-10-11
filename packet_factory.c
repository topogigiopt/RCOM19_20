#include "packet_factory.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "llmacros.h"

char packet[255];

char* stuffing(const char* array) {
  char* aux_array = malloc(STRSIZE * 2);
  unsigned int i, j;
  for (i = 0, j = 0; i < STRSIZE; i++, j++) {
    if (array[i] == 0x7E) {
      aux_array[j] = 0x7D;
      aux_array[j + 1] = 0x5E;
      j++;
    } else {
      aux_array[j] = array[i];
    }
  }
  return aux_array;
}

char* makeBcc(const char* data_field) {
  char* Bcc = malloc(1);

  Bcc[0] = data_field[0];

  for (int i = 1; i < STRSIZE; i++) {
    Bcc[0] = Bcc[0] ^ data_field[i];
  }

  return Bcc;
}

void makeSET(char* setarr){
  setarr[0] = FLAG_RCV;
  setarr[1] = A_SND;
  setarr[2] = C_SND;
  setarr[3] = BCC_SND;
  setarr[4] = FLAG_RCV;
}

void makeUA(char* uaarr) {
  uaarr[0] = FLAG_RCV;
  uaarr[1] = A_RCV;
  uaarr[2] = C_RCV;
  uaarr[3] = BCC_RCV;
  uaarr[4] = FLAG_RCV;
}


void makePacket(const char* header, const char* data_field){
  strcat(packet,header);

  // Data_field
  strcat(packet,stuffing(data_field));

  //Bcc for data
  strcat(packet, makeBcc(data_field));

  char flag[1] = {0x7e};

  strcat(packet, flag);
}