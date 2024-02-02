
//
// Created by Hammad Shahid on 21/11/2022.
//

#include "memory_management.h"
#include "kernel/types.h"
#include "user/user.h"

struct block_metadata *head = 0;
struct block_metadata *previous = 0;

//combine small free blocks.
void combine(struct block_metadata *ptr)
{

    //make current the head.
    struct block_metadata *current_ptr = head;

    //make the next block null for now.
    struct block_metadata *next = 0;

    //make previous block null for now.
    struct block_metadata *previous = 0;


    //traverse through the nodes and find the previous node.
    while (current_ptr->next != ptr)
    {
        current_ptr = current_ptr->next;
    }

    // make the previous pointer equal to it self.
    previous = current_ptr;

    //if the previous node and the current and the next node are free, then combine all three.
    if (previous->free == 1 && ptr->free == 1 && next->free == 1)
    {
        previous->size += ptr->size + next->size + sizeof(struct block_metadata) * 2;
        previous->next = next->next;
    }

    //if the current and the next node are free then combine the 2.
    else if (ptr->free == 1 && next->free == 1)
    {
        ptr->size += current_ptr->size + sizeof(struct block_metadata);
        ptr->next = next->next;
    }

        //if the current and the previous node are free then combine the 2.
    else if (previous->free == 1 && ptr->free == 1)
    {
        previous->size += ptr->size + sizeof(struct block_metadata);
        previous->next = ptr->next;
    }
}

void *split_Block(struct block_metadata *split_block, int size)
{

    // set the address of the new block
    struct block_metadata *newBlock = ((void *)split_block + sizeof(struct block_metadata) + size);
    // set the  size of the new block.
    newBlock->size = split_block->size - (sizeof(struct block_metadata) + size);
    // set the next node of the block to the node, split block was pointing too.
    newBlock->next = split_block->next;
    // set the value to be free since it is free.
    newBlock->free = 1;

    // set the size of the block that contains the data.
    split_block->size = size;
    // set the next to the rest of the free space.
    split_block->next = newBlock;

    // return the block that contains the data.
    return split_block;
}

void *_malloc(int size)
{
    // if size is less than 0 return NUll.
    if (size <= 0)
    {
        return 0;
    }

    // at the beginning block is null.
    struct block_metadata *block = 0;

    // if it's the first call, set the head.
    if (head == 0)
    {
        block = (struct block_metadata *)sbrk(BLOCK_SIZE + size);
        block->size = size;
        block->next = 0;
        block->free = 0;

        head = block;
    }
    else
    {

        // set the current_ptr to head.
        struct block_metadata *current_ptr = head;

        //traverse through the nodes and find the free one to put in the block requested.
        while (current_ptr && !(current_ptr->free != 0 && current_ptr->size >= size))
        {
            // gets the free space to put in the current_ptr.
            current_ptr = current_ptr->next;
        }

        //if we find a free block.
        if (current_ptr != 0)
        {
            //if the free block we find is greater than size of the block requested plus the struct then split it.
            if (current_ptr->size > size + sizeof(struct block_metadata))
            {
                //split the block.
                current_ptr = split_Block(current_ptr, size);
            }

            //make block equal to allocated block.
            block = current_ptr;
            //make the block not free anymore. 1 is for free and 0 is for not free.
            block->free = 0;
        }
        else
        {
            //if we don't find a free block, allocate the address of the block.
            block = (struct block_metadata *)sbrk(BLOCK_SIZE + size);

            //make the previous block's next node equal to the current block.
            previous->next = block;
            //make block size equal to the requested size.
            block->size = size;
            //make the block next node null, since this is being added on the end.
            block->next = 0;
            // make the block not free, 1 is for free and 0 is for not free.
            block->free = 0;
        }
    }

    //make previous equal to block.
    previous = block;
    //return the block itself not the header.
    return (block + 1);
}

// free implementation.
void _free(void *ptr)
{

    //ptr -1 because we have the block and we need the header.
    struct block_metadata *block_pointer = (struct block_metadata *)ptr - 1;

    //if block is not free, then we make it free.
    if (block_pointer->free != 1)
    {
        block_pointer->free = 1;
    }
    // if block_ptr is not the head and the next pointer is not next, then we combine the empty blocks.
    if (block_pointer != head && block_pointer->next != 0)
    {
        //combine the previous or the next empty block.
        combine(block_pointer);
    }
}


