// client.cpp,v 1.2 2000/11/22 23:35:18 corsaro Exp

# include "Collocation_Tester.h"

ACE_RCSID (tests, client, "client.cpp,v 1.2 2000/11/22 23:35:18 corsaro Exp")

int main (int argc, char *argv[])
{
  ACE_DECLARE_NEW_CORBA_ENV;

  ACE_TRY
    {
      // ORB Initialization
      CORBA::ORB_var orb = CORBA::ORB_init (argc, argv, "TAO", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::Object_var object;

      // Get The IOR from a file
      object = orb->string_to_object ("file://s.ior", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (object.in ()))
        {
          ACE_DEBUG ((LM_DEBUG, "Invalid IOR file\n"));
          return 1;
        }

      Collocation_Tester tester (object.in ());
      tester.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "CORBA Exception Raised");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
