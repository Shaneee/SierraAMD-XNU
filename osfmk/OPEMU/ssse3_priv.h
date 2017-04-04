#pragma once

#include "opemu.h"
#include "libudis86/extern.h"

// log function debug
#define LF	D("%s\n", __PRETTY_FUNCTION__);
#define D	printf

/**
 * 128-bit Register proper for ssse3
 * For 64-bit operations, use the same register type, and ignore the high values
 */
union __attribute__((__packed__)) sse_reg {
	int8_t		int8[16];
	int16_t		int16[8];
	int32_t		int32[4];
	int64_t		int64[2];
	__int128_t	int128;
	uint8_t		uint8[16];
	uint16_t	uint16[8];
	uint32_t	uint32[4];
	uint64_t	uint64[2];
	__uint128_t	uint128;
};
typedef union sse_reg sse_reg_t;

/**
 * Print said register to screen. Useful for debugging
 * @param  uint128
 */
#define print128(x)	printf("0x%016llx%016llx", ((uint64_t*)(&(x)))[1], ((uint64_t*)(&(x)))[0] );

/**
 * ssse3 object
 */
struct ssse3 {
	uint8_t	extended;	// bool type

	sse_reg_t		dst, src;
	sse_reg_t		res;

	// operands
	const ud_operand_t	*udo_src, *udo_dst, *udo_imm;

	// objects
	const op_t		*op_obj;

	// legacy mmx flag
	uint8_t 		islegacy;
};
typedef struct ssse3 ssse3_t;



/**
 * Instruction emulation function type.
 */
typedef void (*ssse3_func)(ssse3_t*);


#define storedqu_template(n, where)					\
	do {								\
	asm __volatile__ ("movdqu %%xmm" #n ", %0" : "=m" (*(where)));	\
	} while (0);

#define loaddqu_template(n, where)					\
	do {								\
	asm __volatile__ ("movdqu %0, %%xmm" #n :: "m" (*(where)));	\
	} while (0);

#define storeq_template(n, where)					\
	do {								\
	asm __volatile__ ("movq %%mm" #n ", %0" : "=m" (*(where)));	\
	} while (0);

#define loadq_template(n, where)					\
	do {								\
	asm __volatile__ ("movq %0, %%mm" #n :: "m" (*(where)));	\
	} while (0);

/**
 * Store xmm register somewhere in memory
 */
inline void _store_xmm (const uint8_t n, __uint128_t *where)
{
	switch (n) {
case 0:  storedqu_template(0, where); break;
case 1:  storedqu_template(1, where); break;
case 2:  storedqu_template(2, where); break;
case 3:  storedqu_template(3, where); break;
case 4:  storedqu_template(4, where); break;
case 5:  storedqu_template(5, where); break;
case 6:  storedqu_template(6, where); break;
case 7:  storedqu_template(7, where); break;
case 8:  storedqu_template(8, where); break;
case 9:  storedqu_template(9, where); break;
case 10: storedqu_template(10, where); break;
case 11: storedqu_template(11, where); break;
case 12: storedqu_template(12, where); break;
case 13: storedqu_template(13, where); break;
case 14: storedqu_template(14, where); break;
case 15: storedqu_template(15, where); break;
}}

/**
 * Load xmm register from memory
 */
inline void _load_xmm (const uint8_t n, const __uint128_t *where)
{
	switch (n) {
case 0:  loaddqu_template(0, where); break;
case 1:  loaddqu_template(1, where); break;
case 2:  loaddqu_template(2, where); break;
case 3:  loaddqu_template(3, where); break;
case 4:  loaddqu_template(4, where); break;
case 5:  loaddqu_template(5, where); break;
case 6:  loaddqu_template(6, where); break;
case 7:  loaddqu_template(7, where); break;
case 8:  loaddqu_template(8, where); break;
case 9:  loaddqu_template(9, where); break;
case 10: loaddqu_template(10, where); break;
case 11: loaddqu_template(11, where); break;
case 12: loaddqu_template(12, where); break;
case 13: loaddqu_template(13, where); break;
case 14: loaddqu_template(14, where); break;
case 15: loaddqu_template(15, where); break;
}}

/**
 * Store mmx register somewhere in memory
 */
inline void _store_mmx (const uint8_t n, uint64_t *where)
{
	switch (n) {
case 0:  storeq_template(0, where); break;
case 1:  storeq_template(1, where); break;
case 2:  storeq_template(2, where); break;
case 3:  storeq_template(3, where); break;
case 4:  storeq_template(4, where); break;
case 5:  storeq_template(5, where); break;
case 6:  storeq_template(6, where); break;
case 7:  storeq_template(7, where); break;
}}

/**
 * Load mmx register from memory
 */
inline void _load_mmx (const uint8_t n, const uint64_t *where)
{
	switch (n) {
case 0:  loadq_template(0, where); break;
case 1:  loadq_template(1, where); break;
case 2:  loadq_template(2, where); break;
case 3:  loadq_template(3, where); break;
case 4:  loadq_template(4, where); break;
case 5:  loadq_template(5, where); break;
case 6:  loadq_template(6, where); break;
case 7:  loadq_template(7, where); break;
}}

inline int ssse3_grab_operands(ssse3_t*);
inline int ssse3_commit_results(const ssse3_t*);
inline int op_sse3x_run(const op_t*);

inline void psignb	(ssse3_t*);
inline void psignw	(ssse3_t*);
inline void psignd	(ssse3_t*);
inline void pabsb	(ssse3_t*);
inline void pabsw	(ssse3_t*);
inline void pabsd	(ssse3_t*);
inline void palignr	(ssse3_t*);
inline void pshufb	(ssse3_t*);
inline void pmulhrsw	(ssse3_t*);
inline void pmaddubsw	(ssse3_t*);
inline void phsubw	(ssse3_t*);
inline void phsubd	(ssse3_t*);
inline void phsubsw	(ssse3_t*);
inline void phaddw	(ssse3_t*);
inline void phaddd	(ssse3_t*);
inline void phaddsw	(ssse3_t*);

/*** SSE4.2 TODO move this somewhere else ***/
inline void pcmpistri	(ssse3_t*);
inline void pcmpestri	(ssse3_t*);
inline void pcmpestrm	(ssse3_t*);
inline void pcmpistrm	(ssse3_t*);
inline void pcmpgtq     (ssse3_t*);
