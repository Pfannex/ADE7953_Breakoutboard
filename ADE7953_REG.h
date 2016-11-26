/******************************************************************************

  ProjectName: ADE7953-WattMeter                  ***** *****
  SubTitle   : ADE7953-WattMeter                 *     *     ************
                                                *   **   **   *           *
  Copyright by Pf@nne                          *   *   *   *   *   ****    *
                                               *   *       *   *   *   *   *
  Last modification by:                        *   *       *   *   ****    *
  - Pf@nne (pf@nne-mail.de)                     *   *     *****           *
                                                 *   *        *   *******
  Date    : 24.11.2016                            *****      *   *
  Version : alpha 0.100                                     *   *
  Revison :                                                *****

********************************************************************************/

#define unlock              0xFE
#define Reserved            0x120
//IA
  #define IRMSA               0x21A
  #define AIGAIN              0x210
  #define PGA_IA              0x008
//IB
  #define IRMSB               0x21B
  #define BIGAIN              0x28C
  #define PGA_IB              0x009
//V
  #define VRMS                0x21C
  #define AVGAIN              0x281
  #define PGA_V               0x007



