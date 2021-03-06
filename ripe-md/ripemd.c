

/********************************************************************/
/*  file: ripemd.c                                                  */
/*                                                                  */
/*  description: A sample C-implementation of the RIPEMD            */
/*           hash-function. This function is derived from the MD4   */
/*           Message Digest Algorithm from RSA Data Security, Inc.  */
/*           This implementation was developed by RIPE.             */
/*                                                                  */
/*  copyright (C)                                                   */
/*           Centre for Mathematics and Computer Science, Amsterdam */
/*           Siemens AG                                             */
/*           Philips Crypto BV                                      */
/*           PTT Research, the Netherlands                          */
/*           Katholieke Universiteit Leuven                         */
/*           Aarhus University                                      */
/*  1992, All Rights Reserved                                       */
/*                                                                  */
/*  date:    05/25/92                                               */
/*  version: 1.0                                                    */
/*                                                                  */
/********************************************************************/


/*  header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ripemd.h"      

/********************************************************************/

void MDinit(dword *MDbuf)
{
   MDbuf[0] = 0x67452301UL;
   MDbuf[1] = 0xefcdab89UL;
   MDbuf[2] = 0x98badcfeUL;
   MDbuf[3] = 0x10325476UL;

   return;
}

/********************************************************************/

void compress(dword *MDbuf, dword *X)
{
   dword aa = MDbuf[0],  bb = MDbuf[1],  cc = MDbuf[2],  dd = MDbuf[3];
   dword aaa = MDbuf[0], bbb = MDbuf[1], ccc = MDbuf[2], ddd = MDbuf[3];

   /* round 1 */
   FF(aa, bb, cc, dd, X[0], 11);
   FF(dd, aa, bb, cc, X[1], 14);
   FF(cc, dd, aa, bb, X[2], 15);
   FF(bb, cc, dd, aa, X[3], 12);
   FF(aa, bb, cc, dd, X[4],  5);
   FF(dd, aa, bb, cc, X[5],  8);
   FF(cc, dd, aa, bb, X[6],  7);
   FF(bb, cc, dd, aa, X[7],  9);
   FF(aa, bb, cc, dd, X[8], 11);
   FF(dd, aa, bb, cc, X[9], 13);
   FF(cc, dd, aa, bb, X[10],14);
   FF(bb, cc, dd, aa, X[11],15);
   FF(aa, bb, cc, dd, X[12], 6);
   FF(dd, aa, bb, cc, X[13], 7);
   FF(cc, dd, aa, bb, X[14], 9);
   FF(bb, cc, dd, aa, X[15], 8);

   /* round 2 */
   GG(aa, bb, cc, dd, X[7],  7);
   GG(dd, aa, bb, cc, X[4],  6);
   GG(cc, dd, aa, bb, X[13], 8);
   GG(bb, cc, dd, aa, X[1], 13);
   GG(aa, bb, cc, dd, X[10],11);
   GG(dd, aa, bb, cc, X[6],  9);
   GG(cc, dd, aa, bb, X[15], 7);
   GG(bb, cc, dd, aa, X[3], 15);
   GG(aa, bb, cc, dd, X[12], 7);
   GG(dd, aa, bb, cc, X[0], 12);
   GG(cc, dd, aa, bb, X[9], 15);
   GG(bb, cc, dd, aa, X[5],  9);
   GG(aa, bb, cc, dd, X[14], 7);
   GG(dd, aa, bb, cc, X[2], 11);
   GG(cc, dd, aa, bb, X[11],13);
   GG(bb, cc, dd, aa, X[8], 12);

   /* round 3 */
   HH(aa, bb, cc, dd, X[3], 11);
   HH(dd, aa, bb, cc, X[10],13);
   HH(cc, dd, aa, bb, X[2], 14);
   HH(bb, cc, dd, aa, X[4],  7);
   HH(aa, bb, cc, dd, X[9], 14);
   HH(dd, aa, bb, cc, X[15], 9);
   HH(cc, dd, aa, bb, X[8], 13);
   HH(bb, cc, dd, aa, X[1], 15);
   HH(aa, bb, cc, dd, X[14], 6);
   HH(dd, aa, bb, cc, X[7],  8);
   HH(cc, dd, aa, bb, X[0], 13);
   HH(bb, cc, dd, aa, X[6], 6);
   HH(aa, bb, cc, dd, X[11],12);
   HH(dd, aa, bb, cc, X[13], 5);
   HH(cc, dd, aa, bb, X[5],  7);
   HH(bb, cc, dd, aa, X[12], 5);

   /* parallel round 1 */
   FFF(aaa, bbb, ccc, ddd, X[0], 11);
   FFF(ddd, aaa, bbb, ccc, X[1], 14);
   FFF(ccc, ddd, aaa, bbb, X[2], 15);
   FFF(bbb, ccc, ddd, aaa, X[3], 12);
   FFF(aaa, bbb, ccc, ddd, X[4],  5);
   FFF(ddd, aaa, bbb, ccc, X[5],  8);
   FFF(ccc, ddd, aaa, bbb, X[6],  7);
   FFF(bbb, ccc, ddd, aaa, X[7],  9);
   FFF(aaa, bbb, ccc, ddd, X[8], 11);
   FFF(ddd, aaa, bbb, ccc, X[9], 13);
   FFF(ccc, ddd, aaa, bbb, X[10],14);
   FFF(bbb, ccc, ddd, aaa, X[11],15);
   FFF(aaa, bbb, ccc, ddd, X[12], 6);
   FFF(ddd, aaa, bbb, ccc, X[13], 7);
   FFF(ccc, ddd, aaa, bbb, X[14], 9);
   FFF(bbb, ccc, ddd, aaa, X[15], 8);

   /* parallel round 2 */
   GGG(aaa, bbb, ccc, ddd, X[7],  7);
   GGG(ddd, aaa, bbb, ccc, X[4],  6);
   GGG(ccc, ddd, aaa, bbb, X[13], 8);
   GGG(bbb, ccc, ddd, aaa, X[1], 13);
   GGG(aaa, bbb, ccc, ddd, X[10],11);
   GGG(ddd, aaa, bbb, ccc, X[6],  9);
   GGG(ccc, ddd, aaa, bbb, X[15], 7);
   GGG(bbb, ccc, ddd, aaa, X[3], 15);
   GGG(aaa, bbb, ccc, ddd, X[12], 7);
   GGG(ddd, aaa, bbb, ccc, X[0], 12);
   GGG(ccc, ddd, aaa, bbb, X[9], 15);
   GGG(bbb, ccc, ddd, aaa, X[5],  9);
   GGG(aaa, bbb, ccc, ddd, X[14], 7);
   GGG(ddd, aaa, bbb, ccc, X[2], 11);
   GGG(ccc, ddd, aaa, bbb, X[11],13);
   GGG(bbb, ccc, ddd, aaa, X[8], 12);

   /* parallel round 3 */
   HHH(aaa, bbb, ccc, ddd, X[3], 11);
   HHH(ddd, aaa, bbb, ccc, X[10],13);
   HHH(ccc, ddd, aaa, bbb, X[2], 14);
   HHH(bbb, ccc, ddd, aaa, X[4],  7);
   HHH(aaa, bbb, ccc, ddd, X[9], 14);
   HHH(ddd, aaa, bbb, ccc, X[15], 9);
   HHH(ccc, ddd, aaa, bbb, X[8], 13);
   HHH(bbb, ccc, ddd, aaa, X[1], 15);
   HHH(aaa, bbb, ccc, ddd, X[14], 6);
   HHH(ddd, aaa, bbb, ccc, X[7],  8);
   HHH(ccc, ddd, aaa, bbb, X[0], 13);
   HHH(bbb, ccc, ddd, aaa, X[6], 6);
   HHH(aaa, bbb, ccc, ddd, X[11],12);
   HHH(ddd, aaa, bbb, ccc, X[13], 5);
   HHH(ccc, ddd, aaa, bbb, X[5],  7);
   HHH(bbb, ccc, ddd, aaa, X[12], 5);

   /* combine results */
   ddd += cc + MDbuf[1];               /* final result for MDbuf[0] */
   MDbuf[1] = MDbuf[2] + dd + aaa;
   MDbuf[2] = MDbuf[3] + aa + bbb;
   MDbuf[3] = MDbuf[0] + bb + ccc;
   MDbuf[0] = ddd;

   return;
}

/********************************************************************/

void MDfinish(dword *MDbuf, byte *strptr, dword lswlen, dword mswlen)
{
   dword        i;                                 /* counter       */
   dword        X[16];                             /* message words */

   for (i=0; i<16; i++) {
      X[i] = 0;
   }

   /* put bytes from strptr into X */
   for (i=0; i<(lswlen&63); i++) {
      /* byte i goes into word X[i div 4] at pos.  8*(i mod 4)  */
      X[i>>2] ^= (dword) *(strptr++) << (8 * (i&3));
   }

   /* append the bit m_n == 1 */
   X[(lswlen>>2)&15] ^= (dword)1 << (8*(lswlen&3) + 7);

   if ((lswlen & 63) > 55) {
      /* length goes to next block */
      compress(MDbuf, X);
      for (i=0; i<16; i++) {
         X[i] = 0;
      }
   }

   /* append length in bits*/
   X[14] = lswlen << 3;
   X[15] = (lswlen >> 29) | (mswlen << 3);

   compress(MDbuf, X);

   return;
}

/************************ end of file ripemd.c **********************/


/********************************************************************/
/*  file: hashtest.c                                                */
/*                                                                  */
/*  description: test file for ripemd.c, a sample C-implementation  */
/*           of the RIPEMD hash-function.                           */
/*                                                                  */
/*  command line arguments:                                         */
/*           filename  -- compute hash code of file read binary     */
/*           -sstring  -- print string & hascode                    */
/*           -t        -- perform time trial                        */
/*           -a        -- execute standard test suite, ASCII input  */
/*                         and binary input from file test.bin      */
/*           -x        -- execute standard test suite, hexadecimal  */
/*                         input read from file test.hex            */
/*                                                                  */
/*  copyright (C)                                                   */
/*           Centre for Mathematics and Computer Science, Amsterdam */
/*           Siemens AG                                             */
/*           Philips Crypto BV                                      */
/*           PTT Research, the Netherlands                          */
/*           Katholieke Universiteit Leuven                         */
/*           Aarhus University                                      */
/*  1992, All Rights Reserved                                       */
/*                                                                  */
/*  date:    06/25/92                                               */
/*  version: 1.0                                                    */
/*                                                                  */
/********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ripemd.h"

#ifndef CLK_TCK
#define CLK_TCK CLOCKS_PER_SEC   /* this is a hack for c89 compiler */
#endif                           /* (DEC C for ULTRIX on RISC v1.0) */

#define TEST_BLOCK_SIZE 8000
#define TEST_BLOCKS 1250

/* number of test bytes = TEST_BLOCK_SIZE * TEST_BLOCKS */
static long TEST_BYTES = (long)TEST_BLOCK_SIZE * (long)TEST_BLOCKS;

/********************************************************************/

byte *RIPEMD(byte *message)
/*
 * returns RIPEMD(message)
 * message should be a string terminated by '\0'
 */
{
   dword         MDbuf[4];     /* contains (A, B, C, D)             */
   static byte   hashcode[16];   /* for final hash-value            */
   dword         X[16];        /* current 16-word chunk             */
   word          i;            /* counter                           */
   dword         length;       /* length in bytes of message        */
   dword         nbytes;       /* # of bytes not yet processed      */
   byte         *strptr;       /* points to the current mess. chunk */

   /* initialize */
   MDinit(MDbuf);
   strptr = message;                /* strptr points to first chunk */
   length = (dword)strlen((char *)message);
   nbytes = length;

   /* process message in 16-word chunks */
   while (nbytes > 63) {
      for (i=0; i<16; i++) {
         X[i] = BYTES_TO_WORD(strptr);
         strptr += 4;
      }
      compress(MDbuf, X);
      nbytes -= 64;                     /* 64 bytes less to process */
   }                                    /* length mod 64 bytes left */

   /* finish: */
   MDfinish(MDbuf, strptr, length, 0);

   for (i=0; i<16; i+=4) {
      hashcode[i]   =  MDbuf[i>>2];         /* implicit cast to byte  */
      hashcode[i+1] = (MDbuf[i>>2] >>  8);  /*  extracts the 8 least  */
      hashcode[i+2] = (MDbuf[i>>2] >> 16);  /*  significant bits.     */
      hashcode[i+3] = (MDbuf[i>>2] >> 24); 
   }

   return (byte *)hashcode;
}

/********************************************************************/

byte *RIPEMDbinary(char *fname)
/*
 * returns RIPEMD(message in file fname)
 * fname is read as binary data.
 */
{
   FILE         *mf;                /* pointer to file <fname>      */
   byte          data[1024];        /* contains current mess. block */
   dword         nbytes;            /* length of this block         */
   dword         MDbuf[4];          /* contains (A, B, C, D)        */
   static byte   hashcode[16];      /* for final hash-value         */
   dword         X[16];             /* current 16-word chunk        */
   word          i, j;              /* counters                     */
   dword         length[2];         /* length in bytes of message   */
   dword         offset;            /* # of unprocessed bytes at    */
                                 /* call of MDfinish */

   /* initialize */
   MDinit(MDbuf);
   if ((mf = fopen(fname, "rb")) == NULL) {
      fprintf(stderr, "\nRIPEMDbinary: cannot open file \"%s\".\n", 
              fname);
      exit(1);
   }

   while ((nbytes = fread(data, 1, 1024, mf)) != 0) {
      /* process all complete blocks */
      for (i=0; i<(nbytes>>6); i++) {
         for (j=0; j<16; j++) {
            X[j] = BYTES_TO_WORD(data+64*i+4*j);
         }
         compress(MDbuf, X);
      }
      /* update length[] */
      if (length[0] + nbytes < length[0])
         length[1]++;                  /* overflow to msb of length */
      length[0] += nbytes;
   }

   /* finish: */
   offset = length[0] & 0x3C0;   /* extract bytes 6 to 10 inclusive */
   MDfinish(MDbuf, data+offset, length[0], length[1]);

   for (i=0; i<16; i+=4) {
      hashcode[i]   =  MDbuf[i>>2];        
      hashcode[i+1] = (MDbuf[i>>2] >>  8);
      hashcode[i+2] = (MDbuf[i>>2] >> 16);
      hashcode[i+3] = (MDbuf[i>>2] >> 24);
   }

   fclose(mf);

   return (byte *)hashcode;
}

/********************************************************************/


byte *RIPEMDhex(char *fname)
/*
 * returns RIPEMD(message in file fname)
 * fname should contain the message in hex format; 
 * first number of bytes, then the bytes in hexadecimal. 
 */
{
   FILE         *mf;                /* pointer to file <fname>      */
   byte          data[64];          /* contains current mess. block */
   dword         nbytes;            /* length of the message        */
   dword         MDbuf[4];          /* contains (A, B, C, D)        */
   static byte   hashcode[16];        /* for final hash-value       */
   dword         X[16];             /* current 16-word chunk        */
   word          i, j;              /* counters                     */
   int           val;               /* temp for reading from file   */

   /* initialize */
   if ((mf = fopen(fname, "r")) == NULL) {
      fprintf(stderr, "\nRIPEMDhex: cannot open file \"%s\".\n", 
              fname);
      exit(1);
   }
   MDinit(MDbuf);

   fscanf(mf, "%x", &val);
   nbytes = val;
   i = 0;
   while (nbytes - i > 63) {
      /* read and process complete block */
      for (j=0; j<64; j++) {
         fscanf(mf, "%x", &val);
         data[j] = (byte)val;
      }
      for (j=0; j<16; j++) {
         X[j] = BYTES_TO_WORD(data+4*j);
      }
      compress(MDbuf, X);
      i += 64;
   }

   /* read last nbytes-i bytes: */
   j = 0;
   while (i<nbytes) {
      fscanf(mf, "%x", &val);
      data[j++] = (byte)val;
      i++;
   }

   /* finish */
   MDfinish(MDbuf, data, nbytes, 0);

   for (i=0; i<16; i+=4) {
      hashcode[i]   =  MDbuf[i>>2];        
      hashcode[i+1] = (MDbuf[i>>2] >>  8);
      hashcode[i+2] = (MDbuf[i>>2] >> 16);
      hashcode[i+3] = (MDbuf[i>>2] >> 24);
   }

   fclose(mf);

   return (byte *)hashcode;
}

/********************************************************************/

void speedtest(void)
/*
 * A time trial routine, to measure the speed of ripemd.
 * Measures processor time required to process TEST_BLOCKS times 
 *  a message of TEST_BLOCK_SIZE characters.
 */
{
  clock_t    t0, t1;
  byte       data[TEST_BLOCK_SIZE];
  byte       hashcode[64];
  dword      X[16];
  dword      MDbuf[4];
  word       i, j, k;

  /* initialize test data */
  for (i=0; i<TEST_BLOCK_SIZE; i++)
     data[i] = (byte)(i%1000);

  /* start timer */
  printf ("RIPEMD time trial. Processing %ld characters...\n", TEST_BYTES);
  t0 = clock();

  /* process data */
  MDinit(MDbuf);
  for (i=0; i<TEST_BLOCKS; i++) {
     for (j=0; j<TEST_BLOCK_SIZE; j+=64) {
        for (k=0; k<16; k++) {
           X[k] = BYTES_TO_WORD(data+j+4*k);
        }
        compress(MDbuf, X);
     }
  }
  MDfinish(MDbuf, data, TEST_BYTES, 0);

  /* stop timer, get time difference */
  t1 = clock();
  printf("\nTest input processed in %g seconds.\n", 
         ((double)(t1-t0)/(double)CLK_TCK));
  printf("Characters processed per second: %g\n",
         (double)CLK_TCK*TEST_BYTES/((double)t1-t0));

  for (i=0; i<16; i+=4) {
     hashcode[i]   =  MDbuf[i>>2];        
     hashcode[i+1] = (MDbuf[i>>2] >>  8);
     hashcode[i+2] = (MDbuf[i>>2] >> 16);
     hashcode[i+3] = (MDbuf[i>>2] >> 24);
  }
  printf("\nhashcode: ");
  for (i=0; i<16; i++)
     printf("%02x", hashcode[i]);

  return;
}

/********************************************************************/

void testascii (void)
/* 
 *   standard test suite, ASCII input
 */
{
   int i;
   byte *hashcode;

   printf("\nRIPEMD test suite results (ASCII):\n");

   hashcode = RIPEMD((byte *)"");
   printf("\n\nmessage: \"\"  (empty string)\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)"a");
   printf("\n\nmessage: \"a\"\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)"abc");
   printf("\n\nmessage: \"abc\"\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)"message digest");
   printf("\n\nmessage: \"message digest\"\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)"abcdefghijklmnopqrstuvwxyz");
   printf("\n\nmessage: \"abcdefghijklmnopqrstuvwxyz\"\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   printf("\n\nmessage: A...Za...z0...9\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMD((byte *)"1234567890123456789012345678901234567890\
1234567890123456789012345678901234567890");
   printf("\n\nmessage: 8 times \"1234567890\"\nhashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   /* Contents of binary created file test.bin are "abc" */
   printf("\n\nmessagefile (binary): test.bin\nhashcode: ");
   hashcode = RIPEMDbinary ("test.bin");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   return;
}

/********************************************************************/

void testhex (void)
/* 
 *   standard test suite, hex input, read from files
 */
{
   int i;
   byte *hashcode;

   printf("\nRIPEMD test suite results (hex):\n");

   hashcode = RIPEMDhex("test1.hex");
   printf("\n\nfile test1.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test2.hex");
   printf("\n\nfile test2.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test3.hex");
   printf("\n\nfile test3.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test4.hex");
   printf("\n\nfile test4.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test5.hex");
   printf("\n\nfile test5.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test6.hex");
   printf("\n\nfile test6.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   hashcode = RIPEMDhex("test7.hex");
   printf("\n\nfile test7.hex; hashcode: ");
   for (i=0; i<16; i++)
      printf("%02x", hashcode[i]);

   return;
}

/********************************************************************/

main (int argc, char *argv[])
/*
 *  main program. calls one or more of the test routines depending
 *  on command line arguments. see the header of this file.
 *
 *  (For VAX/VMS, do: HASHTEST :== $<pathname>HASHTEST.EXE
 *   at the command prompt (or in login.com) first. 
 *   (The run command does not allow command line args.)
 *   The <pathname> must include device, e.g., "DSKD:".)
 */
{
  int   i, j;
  byte *hashcode;

   if (argc == 1) {
      fprintf(stderr, "hashtest: no command line arguments supplied.\n");
      exit(1);
   }
   else {
      for (i = 1; i < argc; i++) {
         if (argv[i][0] == '-' && argv[i][1] == 's') {
            printf("\n\nmessage: %s", argv[i]+2);
            hashcode = RIPEMD((byte *)argv[i] + 2);
            printf("\nhashcode: ");
            for (j=0; j<16; j++)
               printf("%02x", hashcode[j]);
         }
         else if (strcmp (argv[i], "-t") == 0)
            speedtest ();
         else if (strcmp (argv[i], "-a") == 0)
            testascii ();
         else if (strcmp (argv[i], "-x") == 0)
            testhex ();
         else { 
            hashcode = RIPEMDbinary (argv[i]);
            printf("\n\nmessagefile (binary): %s", argv[i]);
            printf("\nhashcode: ");
            for (j=0; j<16; j++)
               printf("%02x", hashcode[j]);
         }
      }
   }
   printf("\n");

   return 0;
}

/********************** end of file hashtest.c **********************/
