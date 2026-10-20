/**
  * ############################################################################
  * @file     Timer_lib.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This library contains all portable basic functions.
  * ############################################################################
  */
//
//  Includes
//
#include  "Timer_Lib.h"

//
//  ###########################################################################
//
//  CANONICAL COPY -- LINT round 2, addendum
//
//  There were four physical Timer_Lib.c files in the tree: this one plus a
//  local one each in AD57_FE_GIT, F4_GenBL_GIT and F4_Audio_GIT. But all
//  four projects already compile the linked folder Common_Misc as well --
//  so the three local copies were duplicates.
//
//  Nobody noticed, because MDP_TIMER_LIB is set only in AD57_BL.
//  In the other three projects both copies compile to an empty
//  translation unit, so nothing collides. As soon as MDP_TIMER_LIB is
//  switched on there (in GenBL the line is ready, commented out), the
//  linker reports "multiple definition of Timer_Set".
//
//  Time base changed from g_SystemTime_sec to g_SystemTime_ms. The only
//  user is CAN_MDP_Lib.c in AD57_BL, which uses it to time a CAN packet
//  exchange -- that takes milliseconds, so with seconds the result was
//  nearly always 0. The local copies in GenBL and Audio already used ms.
//  The arrays are not read anywhere outside this file (pure debugger
//  stopwatch), so the change does not alter any run-time behavior.
//
//  ###########################################################################

#ifdef  MDP_TIMER_LIB

  COMMON uint32_t Timer_Array_Current_Value[c_length_timer_array] = {0};
  COMMON uint32_t Timer_Array_Last_Value[c_length_timer_array] = {0};

  // *****************************************************************************
  //
  void  Timer_Set ( uint8_t index )
  {
    //
    //  LINT-Fix 2 : the check was wrong in two ways --
    //    - "index >= 0" is always true for uint8_t and checks nothing
    //    - "<= c_length_timer_array" let index == 10 pass, but only
    //      0..9 are valid. The write then landed in the COMMON block
    //      behind the array.
    //  Since ASSERT no longer stops hard (Fix A3), this needs a real
    //  barrier here, not just a diagnostic aid.
    //
    ASSERT ( index < c_length_timer_array );
    if ( index >= c_length_timer_array )
    {
      return;
    }

    Timer_Array_Current_Value[index] = g_SystemTime_ms;
  }

  // *****************************************************************************
  //
  void Timer_Get_Current_Value ( uint8_t index )
  {
    //
    //  LINT-Fix 2 : the check was wrong in two ways --
    //    - "index >= 0" is always true for uint8_t and checks nothing
    //    - "<= c_length_timer_array" let index == 10 pass, but only
    //      0..9 are valid. The write then landed in the COMMON block
    //      behind the array.
    //  Since ASSERT no longer stops hard (Fix A3), this needs a real
    //  barrier here, not just a diagnostic aid.
    //
    ASSERT ( index < c_length_timer_array );
    if ( index >= c_length_timer_array )
    {
      return;
    }

    Timer_Array_Last_Value[index] = g_SystemTime_ms - Timer_Array_Current_Value[index];
  }

#endif

// ****************************************************************************
// End of File
// ****************************************************************************