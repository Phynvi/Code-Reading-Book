// server.cpp,v 1.3 2001/03/26 21:17:07 coryan Exp
// ============================================================================
//
// = LIBRARY
//    TAO/performance-tests/Demux
//
// = FILENAME
//    server.cpp
//
//    Server-side driver program
//
// = AUTHOR
//
//    Aniruddha Gokhale
//
// ============================================================================


#include "demux_test_server.h"
#include "tao/debug.h"

ACE_RCSID(CodeGen, server, "server.cpp,v 1.3 2001/03/26 21:17:07 coryan Exp")


int main (int argc, char *argv [])
{
  // Set TAO_debug_level to 0 to ensure silent running unless
  // debugging is explicitly invoked

  TAO_debug_level = 0;

  Demux_Test_Server demux_test_server;

  ACE_TRY_NEW_ENV
    {
      int r =
        demux_test_server.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (r == -1)
        return -1;

      demux_test_server.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception");
      return -1;
    }
  ACE_CATCH (CORBA::UserException, userex)
    {
      ACE_PRINT_EXCEPTION (userex, "User Exception");
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}
