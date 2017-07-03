/* This file contains multiple realizations of rdtsc */
#include <inttypes.h>

/* Return CPU time stamp as 64bit number. */
#if defined(__x86_64__) || defined(i386)
static inline uint64_t
rdtsc (void)
{
  uint32_t a, d;
  asm volatile ("rdtsc":"=a" (a), "=d" (d));
  return (uint64_t) a + ((uint64_t) d << (uint64_t) 32);
}

#elif defined (__powerpc64__)

static inline uint64_t
rdtsc (void)
{
  uint64_t t;
  asm volatile ("mftb %0":"=r" (t));
  return t;
}

#elif defined (__SPU__)

static inline uint64_t
rdtsc (void)
{
#ifdef _XLC
  return spu_rdch (0x8);
#else
  return 0 /* __builtin_si_rdch (0x8) FIXME */ ;
#endif
}

#elif defined (__powerpc__)

static inline uint64_t
rdtsc (void)
{
  uint32_t hi1, hi2, lo;
  asm volatile ("1:\n"
		"mftbu %[hi1]\n"
		"mftb  %[lo]\n"
		"mftbu %[hi2]\n"
		"cmpw %[hi1],%[hi2]\n"
		"bne 1b\n":[hi1] "=r" (hi1),[hi2] "=r" (hi2),[lo] "=r" (lo));
  return (uint64_t) lo + ((uint64_t) hi2 << (uint64_t) 32);
}

#elif defined (__arm__)
#if defined(__ARM_ARCH_8A__)
static inline uint64_t
rdtsc (void)	/* We may run arm64 in aarch32 mode, to leverage 64bit counter */
{
  uint64_t tsc;
  asm volatile ("mrrc p15, 0, %Q0, %R0, c9":"=r" (tsc));
  return tsc;
}
#elif defined(__ARM_ARCH_7A__)
static inline uint64_t
rdtsc (void)
{
  uint32_t tsc;
  asm volatile ("mrc p15, 0, %0, c9, c13, 0":"=r" (tsc));
  return (uint64_t) tsc;
}
#else
static inline uint64_t
rdtsc (void)
{
  uint32_t lo;
  asm volatile ("mrc p15, 0, %[lo], c15, c12, 1":[lo] "=r" (lo));
  return (uint64_t) lo;
}
#endif

#elif defined (__xtensa__)

/* Stub for now. */
static inline uint64_t
rdtsc (void)
{
  return 0;
}

#elif defined (__TMS320C6X__)

static inline uint64_t
rdtsc (void)
{
  uint32_t l, h;

  asm volatile (" dint\n"
		" mvc .s2 TSCL,%0\n"
		" mvc .s2 TSCH,%1\n" " rint\n":"=b" (l), "=b" (h));

  return ((uint64_t) h << 32) | l;
}

#elif defined (__aarch64__)
static inline uint64_t
rdtsc (void)
{
  uint64_t tsc;

  /* Works on Cavium ThunderX. Other platforms: YMMV */
  asm volatile ("mrs %0, cntvct_el0":"=r" (tsc));

  return tsc;
}

#else
#error "don't know how to read CPU time stamp"

#endif
