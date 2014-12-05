#include "my_malloc.h"


/* You *MUST* use this macro when calling my_sbrk to allocate the 
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you will receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* make sure this always points to the beginning of your current
 * heap space! if it does not, then the grader will not be able
 * to run correctly and you will receive 0 credit. remember that
 * only the _first_ call to my_malloc() returns the beginning of
 * the heap. sequential calls will return a pointer to the newly
 * added space!
 * Technically this should be declared static because we do not
 * want any program outside of this file to be able to access it
 * however, DO NOT CHANGE the way this variable is declared or
 * it will break the autograder.
 */
void* heap;

/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
 */

//global var to track times we call SBRK
int numSBRK = 0;

void* my_malloc(size_t size)
{
  //account for mem metadata takes up
  int blockSize = size + sizeof(metadata_t);
  if (blockSize > 2048) {
    ERRNO = SINGLE_REQUEST_TOO_LARGE;
    return NULL;
  }
  // Initialize heap, if attempt fails return null
  if (!heap){
    heap = my_sbrk(SBRK_SIZE);
    freelist[7] = (metadata_t *) heap;
    freelist[7]->next = NULL;
    freelist[7]->prev = NULL; 
    freelist[7]->in_use = 0;
    freelist[7]->size = 2048;
    numSBRK++;
  }
  if (!heap){
    ERRNO = OUT_OF_MEMORY;
    return NULL;
  }
  //find correct index to check in freelist
  int index = getIndex(blockSize);
  metadata_t *next;
  metadata_t *head;

  //CASE: correct size exists in our freelist
  if (freelist[index]) {
    head = freelist[index];
    next = head->next;
    //front now in use, no next/prev
    head->in_use = 1;
    head->next = NULL;
    head->prev = NULL;
    //check for more,clear prev, set to null if ends
    if (next) {
      next->prev = NULL;
      freelist[index] = next; //update freelist[index] pointer
    } else {
      freelist[index] = NULL;
    }
    // Return the ptr 
    return offsetPtr(head, 1);
  }

  //CASE: no free block of correct size available
  int available = index;
  //increment index until we have a suitable block
  while (!freelist[available]) {
    available++;
  }
  //CASE: Need more memory, call my_sbrk
  if (numSBRK == 4){
    ERRNO = OUT_OF_MEMORY;
    return NULL;
  }
  if (available == 8 && numSBRK < 4) {
    metadata_t *newHeap = my_sbrk(SBRK_SIZE);
    numSBRK++;
    if (!newHeap)
    {
      ERRNO = OUT_OF_MEMORY;
      return NULL;
    }
    // initialize new 2048 block
    newHeap->in_use = 0;
    newHeap->size = 2048;
    newHeap->next = NULL;
    newHeap->prev = NULL;
    // add new block to freelist
    if (freelist[7])
    {
      freelist[7]->next = newHeap;
    }
    else
    { 
      freelist[7] = newHeap;
      available--;
    }
  }

  //CASE: found block commence buddy system
  metadata_t *curr, *newBlock;
  //iterate until we have correct sized block
  while (available != index) {
    curr = freelist[available];
    // split block size
    curr->size /= 2; 
    newBlock = (metadata_t *) ((char *) curr + curr->size);
    newBlock->size = curr->size;

    //merge into freelist
    if (freelist[available]->next) {
        freelist[available] = freelist[available]->next;
        freelist[available]->prev = NULL;
    } else {
        freelist[available] = NULL;
    }
    //continue moving up free list for buddy system
    --available;

    //move new sized buddies into correct freelist index
    curr->next = newBlock;
    newBlock->prev = curr;
    freelist[available] = curr;
  }

  //select freeblock for user
  metadata_t *ret_meta = freelist[index];

  //update freelist for the block we are taking out
  if (freelist[index]->next) {
    freelist[index] = freelist[index]->next;
    freelist[index]->prev = NULL;
  } else {
    freelist[index] = NULL;
  }

  //set return block
  ret_meta->next = NULL;
  ret_meta->in_use = 1;

  //return offset of block
  ERRNO = NO_ERROR;
  return offsetPtr(ret_meta, 1);

}

/* 
* Retrieve index by multiplying power of 2 until can hold mem
* @param memory value of size_t to hold at correct index
* @return int index of freelist of capable size to hold mem
*/
int getIndex(size_t mem) {
  int index = 0;
  int memory = 16;
  //my_malloc enforces we don't go past 2048
  while (memory < mem) {
    memory *= 2;
    index++;
  }
  return index;
}

void* my_calloc(size_t num, size_t size)
{
  void* mem = my_malloc(num*size);
  //check if my_malloc() occurs correctly
  if (mem == NULL){
    ERRNO = OUT_OF_MEMORY;
    return NULL;
  }
  char* begin = mem;
  //fill the array with zeros
  int count = 0;
  while (count < (num*size)){
    *begin = 0; //deref and set it to 0
    begin++; //increment into array
    count++; //appraoch termination
  }

  ERRNO = NO_ERROR;
  return heap;
}

/*
* Return correct pointer location based on metadata_t*
* @param metadata_t* ptr pointing into our memory
* @param int offset boolean value to add or subtract size of metadata_t*
* @return void* pointing to correct location based on params
*/
void* offsetPtr(metadata_t* ptr, int offset) {
  char *offset_ptr = (char *) ptr;
  if (offset){
    return offset_ptr + sizeof(metadata_t);
  }
  else
  {
    return offset_ptr - sizeof(metadata_t);
  }
}

void my_free(void* ptr)
{
  metadata_t *block = offsetPtr(ptr, 0);
  if (block->in_use == 0){
    ERRNO = DOUBLE_FREE_DETECTED;
    return;
  }
  block->in_use = 0; // no longer in use

  //get buddy of block
  metadata_t *buddy = getBuddy(block);

  //merge buddy while available and not used
  while (buddy && !buddy->in_use) {
    if (buddy->next && buddy->prev) {
      //buddy had a next and prev, update the freelist
      buddy->next->prev = buddy->prev;
      buddy->prev->next = buddy->next;
    } else if (buddy->next) {
      //buddy is head, update the freelist
      buddy->next->prev = NULL;
    } else if (buddy->prev) {
      //buddy is tail, update the freelist
      buddy->prev->next = NULL;
    } else {
      //only buddy exists in freelist index
      freelist[getIndex(buddy->size)] = NULL;
    }
    //use lower addr
    if (buddy < block) {
      block = buddy;
    }
    //double size
    block->size = block->size * 2;
    //find new buddy
    buddy = getBuddy(block);
  }

  //push block to head of new index in freelist
  int index = getIndex(block->size);
  if (freelist[index]) {
    metadata_t *head = freelist[index];
    if (!head){
      block->next = NULL;
      block->prev = NULL;
    } else {
      head->prev = block;
      block->next = head;
    }
  }

  freelist[index] = block;
  ERRNO = NO_ERROR;
  return;
}

int my_log(int n){
  if (n >=16 && n < 32){
    return 4;
  } else if (n >= 32 && n < 64){
    return 5;
  } else if (n >=64 && n < 128){
    return 6;
  } else if (n >=128 && n < 256){
    return 7;
  } else if (n >= 256 && n < 512){
    return 8;
  } else if (n >= 512 && n < 1024){
    return 9;
  } else if (n >= 1024 && n < 2048){
    return 10;
  } else if (n >= 2048 ) {
    return 11;
  }
  return 0;
}

//finds buddy for block
metadata_t* getBuddy(metadata_t* ptr){
  long address = ( ((long)ptr) - ((long) heap));
  int n = my_log(ptr->size);

  //the buddy is second in the pair
  if ((address >> n) & 1){
    //move backwards to find buddy a
    long buddyAddress = address - (1<<n);
    metadata_t* buddyPtr = (metadata_t*) (buddyAddress + (long)heap);
    if (buddyPtr != NULL && buddyPtr->in_use == 0 
      && buddyPtr->size == ptr->size){
      //check they belong to same pair
      if ((address >> (n+1) & 1) == (buddyAddress >> (n+1) & 1)){
        return buddyPtr;
      }
    } else {
      return NULL;
    }
  } else {
    //the buddy is first in the pair
    long buddyAddress = address + (1<<n);
    metadata_t* buddyPtr = (metadata_t*) (buddyAddress + (long)heap);
    if (buddyPtr != NULL&& buddyPtr->in_use == 0 
      && buddyPtr->size == ptr->size){
      //check they belong to same pair
      if ((address >> (n+1) & 1) == (buddyAddress >> (n+1) & 1)){
        return buddyPtr;
      }
    } else {
      return NULL;
    }
  }
  return NULL;


  //using XOR to find buddies, edge cases where it will index out of bounds
  //according to Brandon on piazza?
  
  // int buddy = (int) (size_t)ptr ^ ptr->size;
  // metadata_t *budPtr = (metadata_t *) (size_t) buddy;
  // if (ptr->size == budPtr->size) return budPtr;
  // else return NULL;
}

void* my_memmove(void* dest, const void* src, size_t num_bytes)
{
  //TODO: copy source to a temporary buffer BEFORE replacing dest
  //dest and src may overlap, you will lose the data otherwise
  char* tempMem = my_malloc(sizeof(num_bytes)*num_bytes);
  if (tempMem == NULL){
    ERRNO = OUT_OF_MEMORY;
    return NULL;
  }

  char *destPtr = (char *) dest;
  char *srcPtr = (char *) src;
  if(!num_bytes){
    return destPtr;
  }
  //copy source to temp buffer
  for (int i=0; i<num_bytes; i++) {
    tempMem[i] = srcPtr[i];
  }
  //copy temp buffer into destination
  for (int i = 0; i < num_bytes; i++){
    destPtr[i] = tempMem[i];
  }
  my_free(tempMem);
  ERRNO = NO_ERROR;
  return destPtr;
}

void printFreeList() {
  printError();
  for (int i = 0; i < 8; i++) {
    printf("Size %i: ", 16<<i);
    metadata_t* currNode = freelist[i];
    while (currNode != NULL) {
      printf("(add: %p, prev: %p, next: %p, inUse: %i), ", (void*) currNode, (void*) currNode -> prev, (void*) currNode -> next, currNode -> in_use);
      currNode = currNode->next;
    }
    printf("\n");
  }
  printf("\n");
 }

 void printError() {
  if (ERRNO == NO_ERROR) {
    printf("ERROR: NO ERROR\n");
  } else if (ERRNO == SINGLE_REQUEST_TOO_LARGE) {
    printf("ERROR: SINGLE_REQUEST_TOO_LARGE\n");
  } else if (ERRNO == DOUBLE_FREE_DETECTED) {
    printf("ERROR: DOUBLE_FREE_DETECTED\n");
  } else if (ERRNO == OUT_OF_MEMORY) {
    printf("ERROR: OUT_OF_MEMORY\n");
  }
 }