#pragma once
#include "WProgram.h"

typedef struct {
  int   maxSize;
  byte* storage;
  int   frontPosition;
  int   currentSize;
} queue;

queue* newQueue(int size);
byte Qfront(queue* q);
bool Qempty(queue* q);
bool Qfull(queue* q);
bool Qpush(queue* q, byte x);
bool Qpop(queue* q);
