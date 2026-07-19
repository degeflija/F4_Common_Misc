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

#ifdef  MDP_TIMER_LIB

  COMMON uint32_t Timer_Array_Current_Value[c_length_timer_array] = {0};
  COMMON uint32_t Timer_Array_Last_Value[c_length_timer_array] = {0};

  // *****************************************************************************
  //
  void  Timer_Set ( uint8_t index )
  {
    ASSERT ( index >= 0 );
    ASSERT ( index <= c_length_timer_array);

    Timer_Array_Current_Value[index] = g_SystemTime_sec;
  }

  // *****************************************************************************
  //
  void Timer_Get_Current_Value ( uint8_t index )
  {
    ASSERT ( index >= 0 );
    ASSERT ( index <= c_length_timer_array);

    Timer_Array_Last_Value[index] = g_SystemTime_sec - Timer_Array_Current_Value[index];
  }

#endif

// ****************************************************************************
// End of File
// ****************************************************************************
