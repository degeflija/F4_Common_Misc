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
//  KANONISCHE KOPIE -- LINT-Runde 2, Nachtrag
//
//  Es gab vier physische Timer_Lib.c im Baum: diese hier plus je eine
//  lokale in AD57_FE_GIT, F4_GenBL_GIT und F4_Audio_GIT. Alle vier
//  Projekte kompilieren aber ohnehin schon den Linked Folder Common_Misc
//  mit -- die drei lokalen Kopien waren also Duplikate.
//
//  Aufgefallen ist es nie, weil MDP_TIMER_LIB nur im AD57_BL gesetzt ist.
//  In den anderen drei Projekten uebersetzen beide Kopien zu einer leeren
//  Uebersetzungseinheit, es kollidiert also nichts. Sobald MDP_TIMER_LIB
//  dort eingeschaltet wird (im GenBL steht die Zeile auskommentiert bereit),
//  gibt es "multiple definition of Timer_Set" beim Linken.
//
//  Zeitbasis von g_SystemTime_sec auf g_SystemTime_ms umgestellt. Einziger
//  Verbraucher ist CAN_MDP_Lib.c im AD57_BL, das damit einen CAN-
//  Paketaustausch misst -- der dauert Millisekunden, mit Sekunden kam
//  praktisch immer 0 heraus. Die lokalen Kopien in GenBL und Audio
//  benutzten bereits ms. Die Arrays werden ausserhalb dieser Datei nirgends
//  gelesen (reine Debugger-Stoppuhr), die Umstellung aendert also kein
//  Laufzeitverhalten.
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
    //  LINT-Fix 2 : die Pruefung war doppelt falsch --
    //    - "index >= 0" ist bei uint8_t immer wahr und prueft nichts
    //    - "<= c_length_timer_array" liess index == 10 durch, gueltig
    //      sind aber nur 0..9. Der Schreibzugriff landete dann im
    //      COMMON-Block hinter dem Array.
    //  Seit ASSERT nicht mehr hart stoppt (Fix A3) braucht es hier eine
    //  echte Schranke, nicht nur eine Diagnosehilfe.
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
    //  LINT-Fix 2 : die Pruefung war doppelt falsch --
    //    - "index >= 0" ist bei uint8_t immer wahr und prueft nichts
    //    - "<= c_length_timer_array" liess index == 10 durch, gueltig
    //      sind aber nur 0..9. Der Schreibzugriff landete dann im
    //      COMMON-Block hinter dem Array.
    //  Seit ASSERT nicht mehr hart stoppt (Fix A3) braucht es hier eine
    //  echte Schranke, nicht nur eine Diagnosehilfe.
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