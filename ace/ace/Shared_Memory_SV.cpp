// Shared_Memory_SV.cpp
// Shared_Memory_SV.cpp,v 4.2 2000/04/19 02:49:40 brunsch Exp

#include "ace/Shared_Memory_SV.h"

#if !defined (__ACE_INLINE__)
#include "ace/Shared_Memory_SV.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(ace, Shared_Memory_SV, "Shared_Memory_SV.cpp,v 4.2 2000/04/19 02:49:40 brunsch Exp")

ACE_ALLOC_HOOK_DEFINE(ACE_Shared_Memory_SV)

void
ACE_Shared_Memory_SV::dump (void) const
{
  ACE_TRACE ("ACE_Shared_Memory_SV::dump");
}

ACE_Shared_Memory_SV::ACE_Shared_Memory_SV (key_t id,
					    int length, 
					    int create, 
					    int perms, 
					    void *addr, 
					    int flags)
  : shared_memory_ (id, length, create, perms, addr, flags)
{
  ACE_TRACE ("ACE_Shared_Memory_SV::ACE_Shared_Memory_SV");
}

