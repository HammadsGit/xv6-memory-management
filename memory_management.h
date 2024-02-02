//
// Created by Hammad Shahid on 21/11/2022.
//
#include <stdint.h>
#ifndef XV6_RISCV_COMP2211_MEMORY_MANAGEMENT_H
#define XV6_RISCV_COMP2211_MEMORY_MANAGEMENT_H



//declaring the two functions in the header file.
void* _malloc(int size);
void _free(void *ptr);




//creating a struct for the linked list
//This struct is 12 bytes 4 bytes for the size, 4 bytes for the free and 4 bytes for the pointer to the next struct.
struct block_metadata{
    int size;
    int free;
    struct block_metadata *next;


};

void * split_Block( struct block_metadata *blk, int size);
void combine(struct block_metadata *ptr);


#define BLOCK_SIZE sizeof(struct block_metadata)
#endif //XV6_RISCV_COMP2211_MEMORY_MANAGEMENT_H
