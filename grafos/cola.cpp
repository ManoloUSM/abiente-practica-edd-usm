#include "cola.h"

#define MAXSIZE 1000

tCola::tCola() {
    maxSize = MAXSIZE + 1;
    final = 0;
    frente = 1;
    queueArray = new tElemCola[maxSize];
}

tCola::~tCola() {
    delete[] queueArray;
}

void tCola::clear() {
    final = 0;
    frente = 1;
}

int tCola::enqueue(tElemCola item) {
    if ((final+2) % maxSize == frente) {
        return 0;
    }
    final = (final+1) % maxSize;
    queueArray[final] = item;
    return 1;
}

void tCola::dequeue() {
    if (size() != 0) {
        frente = (frente+1) % maxSize;
    }
}

tElemCola tCola::frontValue() {
    if (size() != 0) {
        return queueArray[frente];
    }
    return -1;
}

int tCola::size() {
    return ((final+maxSize) - frente + 1) % maxSize;
}