// test_non_existent.cpp,v 1.13 2000/10/13 18:42:32 doccvs Exp

#include "ace/Naming_Context.h"
#include "ace/Log_Msg.h"

ACE_RCSID(Naming, test_non_existent, "test_non_existent.cpp,v 1.13 2000/10/13 18:42:32 doccvs Exp")

int main (int, char *[])
{
  int i;

  ACE_STATIC_SVC_REGISTER(ACE_Naming_Context);

  ACE_Naming_Context *ns_ptr;
  ACE_NEW_RETURN (ns_ptr,
                  ACE_Naming_Context,
                  1);

  ACE_Name_Options *name_options = ns_ptr->name_options ();

  const char *m_argv[] = 
  {
    "MyName",
    "-cNODE_LOCAL" ,
#if defined (ACE_WIN32)
    "-lC:\\temp\\non_existent",
#else
    "-l/tmp/foobar.mine",
#endif /* ACE_WIN32 */
    NULL
  };

  int m_argc =
    sizeof (m_argv) / sizeof (char *) -1;

  name_options->parse_args (m_argc,
                            (char **) m_argv);

  i = ns_ptr->open (ACE_Naming_Context::NODE_LOCAL);
  ACE_DEBUG ((LM_DEBUG,
              "(%P) opened with %d\n",
              i));
  if (i != 0) 
    return -1;

  i = ns_ptr->bind ("Key_Value",
                    "Val_Value",
                    "-");

  ACE_DEBUG ((LM_DEBUG,
              "(%P) bound with %d\n",
              i));
  return 0;
}
