/*
 * This malloc uses an explict list where new blocks are allocated using
 * a free list. This free list works as a LIFO stack, where the last
 * block freed up to the list is the first block to be filled. The free
 * list is maintained through a doubly linked list that puts a successor
 * pointer and a previous pointer in each free block that get
 * overwritten when the block is allocated. Free blocks are also
 * coalesced with adjacent blocks before being freed and added to the
 * free list. During reallocation, if the new block size is small enough to
 * free up a new block, the remainder is freed and added to the free
 * list.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "MTM416+SPP216",
    /* First member's full name */
    "Michael Martinsky",
    /* First member's email address */
    "mtm416@lehigh.edu",
    /* Second member's full name (leave blank if none) */
    "Sean Purcell",
    /* Second member's email address (leave blank if none) */
    "spp216@lehigh.edu"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4
#define DSIZE 8
#define FREESIZE 24  //HDR+PREV+SUCC+FTR = 16, + minimum 8 = 24
#define CHUNKSIZE (1<<10)+24

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size)|(alloc))

/* Read and write a word at address p */
#define GET(p) (*(unsigned int *)(p))
#define PUT(p,val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* our block: [HDR (4) | PREV POINTER (4) | SUCC POINTER (4) | FREE (8+) | FTR]
 *                     ^
 *                     bp
 *                     */
/* Gets successor/predecessor in free list*/
#define SUCCP(bp) (*(char **)(bp + WSIZE))
#define PREVP(bp) (*(char **)(bp))

/* Given block ptr bp, compute addreess of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(HDRP(bp) - WSIZE))


static char *freePtr = 0;
static char *heap_listp = 0;
static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static void place_free(void *bp);
static void free_remove(void *bp);
//static void printMemBlock(void *bp);
//static void printAll();
//static void blockConsistent(void *bp);

 // MODIFIED 
 //mm_init - initialize the malloc package. 
 // Allocates 2 blocks of free space on the heap
 // Keeps an initial padding word followed by a prologue block to handle
 // edge cases
 // Adds an epilogue header at the end for edge cases
 // makes first free block the head of the free list
 // No successor or previous pointer yet
 //
int mm_init(void)
{
    if((heap_listp = mem_sbrk(2*FREESIZE)) == NULL){
    	return -1;
    }

    PUT(heap_listp, 0);				 // Alignment padding
    PUT(heap_listp + WSIZE, PACK(FREESIZE, 1)); // Prologue header
    PUT(heap_listp + DSIZE, 0);		 // Predecessor
    PUT(heap_listp + WSIZE*3, 0);		 // Successor
    PUT(heap_listp + FREESIZE, PACK(FREESIZE, 1)); // Prologue footer
    PUT(heap_listp + FREESIZE + WSIZE, PACK(0, 1)); 	 // Epiloge header 
    freePtr = heap_listp + DSIZE;
    place_free(freePtr);
    
    //Extend the empty heap with a free block of CHUNKSIZE bytes.
    if(extend_heap(CHUNKSIZE/WSIZE) == NULL)
    	return -1;
    return 0;
}

//
// extend_heap - adds a certain chunk of space to the heap
// 
// returns pointer to beginning of new space
static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	//Allocate an even number of words to maintain alignment
	size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
	// can't allocate less than 24 words
	if (size < FREESIZE){
	  size = FREESIZE;
	}
	if((int)(bp = mem_sbrk(size)) == -1){
		return NULL;
	}
	
	//Initialize the free block header/footer and the epilogue header
	PUT(HDRP(bp), PACK(size, 0));	      // Free block header 
	PUT(FTRP(bp), PACK(size, 0));	      // New block footer 
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); // New epilogue header
	
	// coalesce with adjacent blocks
	return coalesce(bp);
}

//
// coalesce - merge with any free surrounding blocks
//
// add combined free block to list at end
// return pointer to free block
static void *coalesce(void *bp) 
{
	// if block is first in list, special case
	int firstCase = (PREV_BLKP(bp) == bp);
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))) || firstCase;
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));
	
	// !alloc = free block
	// previous full, next free
	if (prev_alloc && !next_alloc) 
	{
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		free_remove(NEXT_BLKP(bp));
		PUT(HDRP(bp), PACK(size,0));
		PUT(FTRP(bp), PACK(size,0));
	}
        // previous free, next full
	else if (!prev_alloc && next_alloc) 
	{
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		bp = PREV_BLKP(bp);
		free_remove(bp);
		PUT(HDRP(bp), PACK(size,0));
		PUT(FTRP(bp), PACK(size, 0));
	}
	
	//both free
	else if (!prev_alloc && !next_alloc)
	{
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
		free_remove(PREV_BLKP(bp));
		free_remove(NEXT_BLKP(bp));
		bp = PREV_BLKP(bp);
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size,0));
	}
	place_free(bp);
	return bp;
}


 // 
 // find_fit - first fit style within a free list
 //
 // start at top of free list stack
 // check each block in succession if big enough
 // if none fit, return NULL and extend heap
 static void *find_fit(size_t asize)
 {
   void *bp;
   
   //Free Fit
   for (bp = freePtr; GET_ALLOC(HDRP(bp)) == 0; bp = SUCCP(bp)){
     if (asize <= GET_SIZE(HDRP(bp))) {
       free_remove(bp);
       return bp;
     }
   }
   return NULL;
 }

 //
 // place
 // 
 // get size of free block
 // if remaining room big enough for a replacement free block, split
 // if not, place in free block
 // remove previously free block from free list
 static void place(void *bp, size_t asize)
 {
   size_t csize = GET_SIZE(HDRP(bp));

   if ((csize - asize) >= FREESIZE){
     PUT(HDRP(bp), PACK(asize, 1));
     PUT(FTRP(bp), PACK(asize, 1));
     free_remove(bp);
     bp = NEXT_BLKP(bp);
     PUT(HDRP(bp), PACK(csize-asize, 0));
     PUT(FTRP(bp), PACK(csize-asize, 0));
     coalesce(bp); // if next block free
   }
   else{
     PUT(HDRP(bp), PACK(csize, 1));
     PUT(FTRP(bp), PACK(csize, 1));
     free_remove(bp);
   } 
 }

 //
 //mm_malloc - Allocate a block by incrementing the brk pointer.
 //   
 // Always allocate a block whose size is a multiple of the alignment.
 // If fit found, place in found block
 // if no fit, need to extend heap
 // place block in new heap space
void *mm_malloc(size_t size)
{
   
    size_t asize;
    size_t extendsize;
    char *bp;
    // pointless
    if (size <= 0){
      return NULL;
    }

    asize = MAX(ALIGN(size)+DSIZE, FREESIZE);

    if ((bp = find_fit(asize))){
      place(bp, asize);
      return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL){
      return NULL;
	}
    place(bp, asize);
    return bp;
}

 //
 //mm_free - Freeing a block 
 //
 // changes header and footer alloc tag to 0
 // coalesces block
 // coalesce will remove from free list
void mm_free(void *bp)
{
	// not allocated
	if (bp == NULL){
	  return;
	}

	size_t size = GET_SIZE(HDRP(bp));

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

 //
 //mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 //
 // null pointer makes it malloc
 // 0 size makes it free
 // if new size fits in old block with room to spare for free block,
 // split old block into alloc and free
 // if block doesn't fit, call malloc to allocate new block
 // copy payload and free old block
void *mm_realloc(void *ptr, size_t size)
{
    // from prompt
    if (ptr == NULL){
      mm_malloc(size);
    }
    // from prompt
    if (size == 0){
      mm_free(ptr);
    }
    // size of old allocated block
    size_t oldsize = GET_SIZE(HDRP(ptr));
    // desired size
    
    size_t asize = MAX(ALIGN(size)+DSIZE, FREESIZE);
    // block already fits
    if (asize <= oldsize)
    {
	 if ((oldsize - asize) >= FREESIZE)
	 {
  	   PUT(HDRP(ptr), PACK(asize, 1));
  	   PUT(HDRP(ptr) + asize - 1, PACK(asize, 1));
  	   PUT(ptr+asize, PACK(oldsize-asize, 0)); // if next block free
  	   PUT(ptr+oldsize-2, PACK(oldsize-asize, 0)); // if next block free
	   coalesce(ptr+asize);
  	 }
	return ptr;
    }
    // block doesn't fit
    void *bp = mm_malloc(size);
    // heap out of room
    if (!bp){
      return 0;
    }

    // copy payload
    memcpy(bp, ptr, MIN(size, oldsize));
    // free old block
    mm_free(ptr);
    return bp;
}

//
// place_free - general stack addition algorithm
//
static void place_free(void *bp){
  // general double linked list
   SUCCP(bp) = freePtr;
   PREVP(freePtr) = bp;
   PREVP(bp) = NULL;
   // new top of stack
   freePtr = bp;
}

// free_remove - general stack removal algorithm
static void free_remove(void *bp){
  // not top of stack
  if(PREVP(bp) != NULL){
    SUCCP(PREVP(bp)) = SUCCP(bp);
  }
  // top of stack
  else{
    freePtr = SUCCP(bp);
  }
  PREVP(SUCCP(bp)) = PREVP(bp);
}

//---------------Check Functions-----------

// printMemblock - prints info about the block
/*static void printMemBlock(void *bp){
  int hdrS = GET_SIZE(HDRP(bp));
  int ftrS = GET_SIZE(FTRP(bp));
  int hdrA = GET_ALLOC(HDRP(bp));
  int ftrA = GET_ALLOC(FTRP(bp));
  //allocated block
  if (hdrA){
    printf("%p: hdrS = %d, hdrA = %d, ftrS = %d, ftrA = %d\n", bp, hdrS, hdrA, ftrS, ftrA);
  }
  else{
    printf("%p: hdrS = %d, hdrA = %d, ftrS = %d, ftrA = %d, PREVP = %p, SUCCP = %p\n", bp, hdrS, hdrA, ftrS, ftrA, PREVP(bp), SUCCP(bp));
  } 
}

//
// printAll - prints out free list
//
static void printAll(){
  void *bp;
  for (bp = freePtr; GET_ALLOC(HDRP(bp)) == 0; bp = SUCCP(bp)){
    printMemBlock(bp);
  }
  printf("----------------------\n");
}*/

//
// checks block consistency used when freeing
/*static void blockConsistent(void *bp){
  if (GET_SIZE(HDRP(bp)) != GET_SIZE(FTRP(bp))){
    printf("Sizes do not match");
  }
  if (GET_ALLOC(HDRP(bp)) != GET_ALLOC(FTRP(bp))){
    printf("Allocs do not match");
  }
}*/
