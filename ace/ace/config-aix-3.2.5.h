/* -*- C++ -*- */
// config-aix-3.2.5.h,v 4.12 2000/03/23 21:27:02 nanbor Exp

// The following configuration file is designed to work for AIX 3.2.5
// with xlC.  Thanks to Bob Olson <olson@mcs.anl.gov> for this.

#ifndef ACE_CONFIG_H
#define ACE_CONFIG_H
#include "ace/pre.h"

/*#define ACE_HAS_PTHREADS*/

#define MAXNAMELEN 1024

#define ACE_DEFAULT_BASE_ADDR ((char *) 0x80000000)
#define ACE_HAS_2_PARAM_ASCTIME_R_AND_CTIME_R
#define ACE_HAS_RECURSIVE_THR_EXIT_SEMANTICS
#define ACE_HAS_CONSISTENT_SIGNAL_PROTOTYPES
#define ACE_HAS_TEMPLATE_TYPEDEFS
#define ACE_HAS_STRERROR
#define ACE_HAS_SIG_ATOMIC_T
#define ACE_HAS_SSIZE_T
#define ACE_HAS_CPLUSPLUS_HEADERS
#define ACE_HAS_POLL
#define ACE_HAS_POSIX_NONBLOCK
#define ACE_HAS_AIX_GETTIMEOFDAY
#define ACE_HAS_NO_SYSCALL_H
#define ACE_NEEDS_DEV_IO_CONVERSION
// Optimize ACE_Handle_Set for select().
#define ACE_HAS_HANDLE_SET_OPTIMIZED_FOR_SELECT

// Compiler/platform has the getrusage() system call.
#define ACE_HAS_GETRUSAGE

// Compiler/platform uses old malloc()/free() prototypes (ugh).
#define ACE_HAS_OLD_MALLOC

// Defines the page size of the system.
#define ACE_PAGE_SIZE 4096

// Compiler/platform supports struct strbuf
#define ACE_HAS_STRBUF_T

// Platform supports STREAMS.
/*#define ACE_HAS_STREAMS*/

#include "ace/post.h"
#endif /* ACE_CONFIG_H */
