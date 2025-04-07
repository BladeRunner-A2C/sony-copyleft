/*===================================================================================
 Copyright (c) 2016-17 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ===================================================================================*/

/*===================================================================================
 FILE:  UsefulBuf.c

 DESCRIPTION:  General purpose input and output buffers
 =====================================================================================*/

#include <string.h>
#include "UsefulBuf.h"

#define USEFUL_OUT_BUF_MAGIC  (0x0B0F) // used to catch use of uninitialized or corrupted UOBs



/*
   Public function -- see UsefulBuf.h
 */
int UsefulBuf_Copy(UsefulBuf *pDest, const UsefulBufC Src)
{
   if(Src.len > pDest->len)
      return 1;

   memscpy(pDest->ptr, pDest->len, Src.ptr, Src.len);

   pDest->len = Src.len;

   return 0;
}

/*
   Public function -- see UsefulBuf.h
 */
int UsefulBuf_Compare(const UsefulBufC UB1, const UsefulBufC UB2)
{
   // use the comparisons rather than subtracting lengths to
   // return an int instead of a size_t
   if(UB1.len < UB2.len) {
      return -1;
   } else if (UB1.len > UB2.len) {
      return 1;
   } // else UB1.len == UB2.len

   return memcmp(UB1.ptr, UB2.ptr, UB1.len);
}


/*
 Public function -- see UsefulBuf.h
 */
void UsefulBuf_Set(UsefulBuf *pDest, uint8_t value)
{
   memset(pDest->ptr, value, pDest->len);
}


/*
 returns SIZE_MAX when there is no match
 */
size_t UsefulBuf_FindBytes(UsefulBufC BytesToSearch, UsefulBufC BytesToFind)
{
   if(BytesToSearch.len < BytesToFind.len) {
      return SIZE_MAX;
   }

   for(size_t uPos = 0; uPos <= BytesToSearch.len - BytesToFind.len; uPos++) {
      if(!UsefulBuf_Compare((UsefulBufC){(const uint8_t*)BytesToSearch.ptr + uPos, BytesToFind.len}, BytesToFind)) {
         return uPos;
      }
   }

   return SIZE_MAX;
}


/*
 Public function -- see UsefulBuf.h

 The core of UsefulOutBuf -- put some bytes in the buffer without writing off the end of it.

 THIS FUNCTION DOES POINTER MATH
 */
void UsefulOutBuf_Init(UsefulOutBuf *me, void *pStorage, size_t uStorageSize)
{
   me->magic  = USEFUL_OUT_BUF_MAGIC;
   UsefulOutBuf_Reset(me);

   me->UB.ptr = pStorage;
   me->size   = uStorageSize;

   // Sanity check on the pointer and size to be sure we are not
   // passed a buffer that goes off the end of the address space.
   // Given this test, we know that all unsigned lengths less than
   // me->size are valid and won't wrap in any pointer additions
   // based off of pStorage in the rest of this code.
   const uintptr_t ptrM = UINTPTR_MAX - uStorageSize;
   if(pStorage && (uintptr_t)pStorage > ptrM) // Check #0
      me->err = 1;
}


/*
 Public function -- see UsefulBuf.h

 The core of UsefulOutBuf -- put some bytes in the buffer without writing off the end of it.

 Code Reviewers: THIS FUNCTION DOES POINTER MATH

 This function inserts the source buffer, NewData, into the destination buffer, me->UB.ptr.

 Destination is represented as:
   me->UB.ptr -- start of the buffer
   me->UB.len -- length of valid data in the buffer
   me->size -- size of the buffer UB.ptr

 Source is data:
   NewData.ptr -- start of source buffer
   NewData.len -- length of source buffer

 Insertion point:
   uInsertionPos.

 Steps:

 0. Corruption checks on UsefulOutBuf

 1. Figure out if the new data will fit or not

 2. Is insertion position in the range of valid data?

 3. If insertion point is not at the end, slide data to the right of the insertion point to the right

 4. Put the new data in at the insertion position.

 */
void UsefulOutBuf_InsertUsefulBuf(UsefulOutBuf *me, UsefulBufC NewData, size_t uInsertionPos)
{
   if(me->err) {
      // Already in error state.
      return;
   }

   /* 0. Sanity check the UsefulOutBuf structure */
   // A "counter measure". If magic number is not the right number it
   // probably means me was not initialized or it was corrupted. Attackers
   // can defeat this, but it is a hurdle and does good with very
   // little code.
   if(me->magic != USEFUL_OUT_BUF_MAGIC) {
      me->err = 1;
      return;  // Magic number is wrong due to uninitalization or corrption
   }

   // Make sure valid data is less than buffer size. This would only occur
   // if there was corruption of me, but it is also part of the checks to
   // be sure there is no pointer arithmatic under/overflow.
   if(me->UB.len > me->size) {  // Check #1
      me->err = 1;
      return; // Offset of valid data is off the end of the UsefulOutBuf due to uninitialization or corruption
   }

   /* 1. Will it fit? */
   // WillItFit() is the same as: NewData.len <= (me->size - me->UB.len)
   // Check #1 makes sure subtraction in RoomLeft will not wrap around
   if(! UsefulOutBuf_WillItFit(me, NewData.len)) { // Check #2
      // The new data will not fit into the the buffer.
      me->err = 1;
      return;
   }

   /* 2. Check the Insertion Position */
   // This, with Check #1, also confirms that uInsertionPos <= me->size
   if(uInsertionPos > me->UB.len) { // Check #3
      // Off the end of the valid data in the buffer.
      me->err = 1;
      return;
   }

   /* 3. Slide existing data to the right */
   uint8_t *pSourceOfMove       = (uint8_t*)me->UB.ptr + uInsertionPos; // PtrMath #1
   size_t   uNumBytesToMove     = me->UB.len - uInsertionPos; // PtrMath #2
   uint8_t *pDestinationOfMove  = pSourceOfMove + NewData.len; // PtrMath #3
   size_t   uRoomInDestination  = me->size - (uInsertionPos + NewData.len); // PtrMath #4

   if(uNumBytesToMove && me->UB.ptr) {
      memsmove(pDestinationOfMove, uRoomInDestination, pSourceOfMove, uNumBytesToMove);
   }

   /* 4. Put the new data in */
   uint8_t *pInsertionPoint = (uint8_t*)me->UB.ptr + uInsertionPos; // PtrMath #5
   uRoomInDestination       = me->size - uInsertionPos; // PtrMath #6
   if(me->UB.ptr) {
      memsmove(pInsertionPoint, uRoomInDestination, NewData.ptr, NewData.len);
   }
   me->UB.len += NewData.len ;
}


/*
 Rationale that describes why the above pointer math is safe

 PtrMath #1 will never wrap around over because
   Check #0 in UsefulOutBuf_Init makes sure me-UB.ptr + me->size doesn't wrap
   Check #1 makes sure me->UB.len is less than me->size
   Check #3 makes sure uInsertionPos is less than me->UB.len

 PtrMath #2 will never wrap around under because
   Check #3 makes sure uInsertionPos is less than me->UB.len

 PtrMath #3 will never wrap around over because   todo
   PtrMath #1 is checked resulting in pStartOfDataToMove being between me->UB.ptr and a maximum valid ptr

 PtrMath #4 will never wrap under because
    Check #3 makes sure uInsertionPos is less than me->UB.len
    Check #3 allows Check #2 to be refactored as NewData.Len > (me->size - uInsertionPos)
    This algebraically rearranges to me->size > uInsertionPos + NewData.len

 PtrMath #5 is exactly the same as PtrMath #1

 PtrMath #6 will never wrap under because
   Check #1 makes sure me->UB.len is less than me->size
   Check #3 makes sure uInsertionPos is less than me->UB.len
 */


/*
 Public function -- see UsefulBuf.h

 Returns the resulting valid data in a UsefulBuf

 */
int UsefulOutBuf_OutUBuf(UsefulOutBuf *me, UsefulBuf *O)
{
   if(me->err) {
      return me->err;
   }

   if(me->magic != USEFUL_OUT_BUF_MAGIC) {
      me->err = 1;
      return 1;
   }

   *O = me->UB;
   return 0;
}


/*
 Public function -- see UsefulBuf.h

 Copy out the data accumulated in the output buffer.

 */
int UsefulOutBuf_CopyOut(UsefulOutBuf *me, void *pBuf, size_t uBufSize, size_t *puCopied)
{
   UsefulBuf B;
   if(UsefulOutBuf_OutUBuf(me, &B)) {
      return 1; // was in error state or was corrupted
   }

   if(B.len > uBufSize) {
      return 1; // buffer was too small
   }

   memsmove(pBuf, uBufSize, B.ptr, B.len);

   *puCopied = me->UB.len;

   return 0;
}




/*
 Public function -- see UsefulBuf.h

 The core of UsefulInputBuf -- consume some bytes without going off the end of the buffer.

 Code Reviewers: THIS FUNCTION DOES POINTER MATH
 */
const void * UsefulInputBuf_GetBytes(UsefulInputBuf *me, size_t uAmount)
{
   // Already in error state. Do nothing.
   if(me->err) {
      return NULL;
   }

   if(!UsefulInputBuf_BytesAvailable(me, uAmount)) {
      // The number of bytes asked for at current position are more than available
      me->err = 1;
      return NULL;
   }

   // This is going to succeed
   const void * const result = (const void*)((const uint8_t*)(me->UB.ptr) + me->cursor);
   me->cursor += uAmount; // this will not overflow because of check using UsefulInputBuf_BytesAvailable()
   return result;
}

