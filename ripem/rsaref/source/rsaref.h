#ifndef _H_RSAREF
#define _H_RSAREF

/* 92.12.30 RL - added #ifdef to avoid mult. inclusion and added constants
 *                      to support INIT,PROCESS,END mode
 */

/* RSAREF.H - header file for RSAREF cryptographic toolkit
 */

/* Copyright (C) 1991-2 RSA Laboratories, a division of RSA Data
   Security, Inc. All rights reserved.
 */

/* Message-digest algorithms.
 */
#define DA_MD2 3
#define DA_MD5 5

/* Data encryption algorithms.   (Added by Mark Henderson/Mark Riordan)
 */
#define EA_DES_CBC      0
#define EA_DES_EDE2_CBC 1

/* RSA key lengths.
 */
#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 1024
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)

/* Maximum lengths of encoded and encrypted content, as a function of
   content length len. Also, inverse functions.
 */
#define ENCODED_CONTENT_LEN(len) (4*(len)/3 + 3)
#define ENCRYPTED_CONTENT_LEN(len) ENCODED_CONTENT_LEN ((len)+8)
#define DECODED_CONTENT_LEN(len) (3*(len)/4 + 1)
#define DECRYPTED_CONTENT_LEN(len) DECODED_CONTENT_LEN ((len)-1)

/* Maximum lengths of signatures, encrypted keys, encrypted
   signatures, and message digests.
 */
#define MAX_SIGNATURE_LEN MAX_RSA_MODULUS_LEN
#define MAX_PEM_SIGNATURE_LEN ENCODED_CONTENT_LEN (MAX_SIGNATURE_LEN)
#define MAX_PEM_ENCRYPTED_KEY_LEN ENCODED_CONTENT_LEN (MAX_RSA_MODULUS_LEN)
#define MAX_PEM_ENCRYPTED_SIGNATURE_LEN \
  ENCRYPTED_CONTENT_LEN (MAX_SIGNATURE_LEN)
#define MAX_DIGEST_LEN 16

/* Error codes.
 */
#define RE_CONTENT_ENCODING 0x0400
#define RE_DATA 0x0401
#define RE_DIGEST_ALGORITHM 0x0402
#define RE_ENCODING 0x0403
#define RE_KEY 0x0404
#define RE_KEY_ENCODING 0x0405
#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_NEED_RANDOM 0x0408
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_SIGNATURE 0x040b
#define RE_SIGNATURE_ENCODING 0x040c

/* Random structure.
 */
typedef struct {
  unsigned int bytesNeeded;
  unsigned char state[16];
  unsigned int outputAvailable;
  unsigned char output[16];
} R_RANDOM_STRUCT;

/* RSA public and private key.
 */
typedef struct {
  unsigned int bits;                           /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];                    /* modulus */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];           /* public exponent */
} R_RSA_PUBLIC_KEY;

typedef struct {
  unsigned int bits;                           /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];                    /* modulus */
  unsigned char publicExponent[MAX_RSA_MODULUS_LEN];     /* public exponent */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];          /* private exponent */
  unsigned char prime[2][MAX_RSA_PRIME_LEN];               /* prime factors */
  unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];   /* exponents for CRT */
  unsigned char coefficient[MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} R_RSA_PRIVATE_KEY;

/* RSA prototype key.
 */
typedef struct {
  unsigned int bits;                           /* length in bits of modulus */
  int useFermat4;                        /* public exponent (1 = F4, 0 = 3) */
} R_RSA_PROTO_KEY;

/* Random structures.
 */
int R_RandomInit PROTO_LIST ((R_RANDOM_STRUCT *));
int R_RandomUpdate PROTO_LIST
  ((R_RANDOM_STRUCT *, unsigned char *, unsigned int));
int R_GetRandomBytesNeeded PROTO_LIST ((unsigned int *, R_RANDOM_STRUCT *));
void R_RandomFinal PROTO_LIST ((R_RANDOM_STRUCT *));

/* Cryptographic enhancements.
 */
int R_SignPEMBlock PROTO_LIST
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int *,
    unsigned char *, unsigned int, int, int, R_RSA_PRIVATE_KEY *, int));
int R_VerifyPEMSignature PROTO_LIST
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    unsigned char *, unsigned int, int, int, R_RSA_PUBLIC_KEY *, int));
int R_VerifyBlockSignature PROTO_LIST
  ((unsigned char *, unsigned int, unsigned char *, unsigned int, int,
    R_RSA_PUBLIC_KEY *, int));
int R_SealPEMBlock PROTO_LIST
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int *,
    unsigned char *, unsigned int *, unsigned char [8], unsigned char *,
    unsigned int, int, R_RSA_PUBLIC_KEY *, R_RSA_PRIVATE_KEY *,
    R_RANDOM_STRUCT *, int));
int R_OpenPEMBlock PROTO_LIST 
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    unsigned char *, unsigned int, unsigned char *, unsigned int,
    unsigned char [8], int, R_RSA_PRIVATE_KEY *, R_RSA_PUBLIC_KEY *, int));
int R_DigestBlock PROTO_LIST 
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int, int, int));
  
/* Key-pair generation.
 */
int R_GeneratePEMKeys PROTO_LIST
  ((R_RSA_PUBLIC_KEY *, R_RSA_PRIVATE_KEY *, R_RSA_PROTO_KEY *,
    R_RANDOM_STRUCT *));

/* Routines supplied by the implementor.
 */
void R_memset PROTO_LIST ((POINTER, int, unsigned int));
void R_memcpy PROTO_LIST ((POINTER, POINTER, unsigned int));
int R_memcmp PROTO_LIST ((POINTER, POINTER, unsigned int));

/* extensions */
#define MODE_STANDARD 0
#define MODE_INIT 1
#define MODE_PROCESS 2
#define MODE_END 3

#endif

