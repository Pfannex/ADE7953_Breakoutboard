/******************************************************************************

  ProjectName: ADE7953-WattMeter                  ***** *****
  SubTitle   : Register definition               *     *     ************
                                                *   **   **   *           *
  Copyright by Pf@nne                          *   *   *   *   *   ****    *
                                               *   *       *   *   *   *   *
  Last modification by:                        *   *       *   *   ****    *
  - Pf@nne (pf@nne-mail.de)                     *   *     *****           *
                                                 *   *        *   *******
  Date    : 03.12.2016                            *****      *   *
  Version : alpha 0.200                                     *   *
  Revison :                                                *****

********************************************************************************/

//8-Bit Registers
//      Register Name	Address 			      R/W Def  Type 	Register Description
#define SAGCYC			  0x000  				    //R/W 0x00 Unsigned Sag line cycles
#define DISNOLOAD		  0x001  				    //R/W 0x00 Unsigned No-load detection disable (see Table 16)
#define LCYCMODE		  0x004  				    //R/W 0x40 Unsigned Line cycle accumulation mode configuration (see Table 17)
#define PGA_V			    0x007  				    //R/W 0x00 Unsigned Voltage channel gain configuration (Bits[2:0])
#define PGA_IA			  0x008  				    //R/W 0x00 Unsigned Current Channel A gain configuration (Bits[2:0])
#define PGA_IB			  0x009  				    //R/W 0x00 Unsigned Current Channel B gain configuration (Bits[2:0])
#define WRITE_PROTECT	0x040  				    //R/W 0x00 Unsigned Write protection bits (Bits[2:0])
#define LAST_OP			  0x0FD  				    //R	  0x00 Unsigned Contains the type (read or write) of the last successful communication (0x35 = read; 0xCA = write)
#define LAST_RWDATA		0x0FF  				    //R   0x00 Unsigned Contains the data from the last successful 8-bit register communication
#define Version			  0x702  				    //R   N/A  Unsigned Contains the silicon version number
#define EX_REF			  0x800  				    //R/W 0x00 Unsigned Reference input configuration: set to 0 for internal; set to 1 for external
#define unlock        0xFE				      //R/W 0x00 Unsigned Unlocking Register Reserved1 0x120 by writing 0xAD to meet the performance specified in Table 1.

//16-Bit Registers
//      Register Name	Address 			      R/W Def    Type 	  Register Description
#define ZXTOUT			  0x100  				    //R/W 0xFFFF Unsigned Zero-crossing timeout
#define LINECYC			  0x101  				    //R/W 0x0000 Unsigned Number of half line cycles for line cycle energy accumulation mode
#define CONFIG			  0x102  				    //R/W 0x8004 Unsigned Configuration register (see Table 18)
#define CF1DEN			  0x103  				    //R/W 0x003F Unsigned CF1 frequency divider denominator. When modifying this register, two sequential write operations must be performed to ensure that the write is successful.
#define CF2DEN			  0x104  				    //R/W 0x003F Unsigned CF2 frequency divider denominator. When modifying this register, two sequential write operations must be performed to ensure that the write is successful.
#define CFMODE			  0x107  				    //R/W 0x0300 Unsigned CF output selection (see Table 19)
#define PHCALA			  0x108  				    //R/W 0x0000 Signed   Phase calibration register (Current Channel A). This register is in sign magnitude format.
#define PHCALB			  0x109  				    //R/W 0x0000 Signed   Phase calibration register (Current Channel B). This register is in sign magnitude format.
#define PFA				    0x10A  				    //R   0x0000 Signed   Power factor (Current Channel A)
#define PFB				    0x10B  				    //R   0x0000 Signed   Power factor (Current Channel B)
#define ANGLE_A			  0x10C  				    //R   0x0000 Signed   Angle between the voltage input and the Current Channel A input
#define ANGLE_B			  0x10D  				    //R   0x0000 Signed   Angle between the voltage input and the Current Channel B input
#define Period			  0x10E  				    //R   0x0000 Unsigned Period register
#define ALT_OUTPUT		0x110  				    //R/W 0x0000 Unsigned Alternative output functions (see Table 20)
#define LAST_ADD		  0x1FE  				    //R   0x0000 Unsigned Contains the address of the last successful communication
#define LAST_RWDATA		0x1FF  				    //R   0x0000 Unsigned Contains the data from the last successful 16-bit register communication
#define Reserved1		  0x120  				    //R/W 0x0000 Unsigned This register should be set to 30h to meet the performance specified in Table 1. To modify this register, it must be unlocked by setting Register Address 0xFE to 0xAD immediately prior.

//24(32)-Bit Registers
//      Register Name	Add24 		  Add32	  R/W Def      Type 	Register Description
#define SAGLVL			  0x200 		//0x300   R/W 0x000000 Unsigned Sag voltage level
#define ACCMODE			  0x201 		//0x301   R/W 0x000000 Unsigned Accumulation mode (see Table 21)
#define AP_NOLOAD		  0x203 		//0x303   R/W 0x00E419 Unsigned Active power no-load level
#define VAR_NOLOAD		0x204 		//0x304   R/W 0x00E419 Unsigned Reactive power no-load level
#define VA_NOLOAD		  0x205 		//0x305   R/W 0x000000 Unsigned Apparent power no-load level
#define AVA 			    0x210 		//0x310   R   0x000000 Signed   Instantaneous apparent power (Current Channel A)
#define BVA				    0x211 		//0x311   R   0x000000 Signed   Instantaneous apparent power (Current Channel B)
#define AWATT			    0x212 		//0x312   R   0x000000 Signed   Instantaneous active power (Current Channel A)
#define BWATT			    0x213 		//0x313   R   0x000000 Signed   Instantaneous active power (Current Channel B)
#define AVAR			    0x214 		//0x314   R   0x000000 Signed   Instantaneous reactive power (Current Channel A)
#define BVAR			    0x215 		//0x315   R   0x000000 Signed   Instantaneous reactive power (Current Channel B)
#define IA				    0x216 		//0x316   R   0x000000 Signed   Instantaneous current (Current Channel A)
#define IB				    0x217 		//0x317   R   0x000000 Signed   Instantaneous current (Current Channel B)
#define V				      0x218 		//0x318   R   0x000000 Signed   Instantaneous voltage (voltage channel)
#define IRMSA			    0x21A 		//0x31A   R   0x000000 Unsigned IRMS register (Current Channel A)
#define IRMSB			    0x21B 		//0x31B   R   0x000000 Unsigned IRMS register (Current Channel B)
#define VRMS			    0x21C 		//0x31C   R   0x000000 Unsigned VRMS register
#define AENERGYA		  0x21E 		//0x31E   R   0x000000 Signed   Active energy (Current Channel A)
#define AENERGYB		  0x21F 		//0x31F   R   0x000000 Signed   Active energy (Current Channel B)
#define RENERGYA		  0x220 		//0x320   R   0x000000 Signed   Reactive energy (Current Channel A)
#define RENERGYB		  0x221 		//0x321   R   0x000000 Signed   Reactive energy (Current Channel B)
#define APENERGYA		  0x222 		//0x322   R   0x000000 Signed   Apparent energy (Current Channel A)
#define APENERGYB		  0x223 		//0x323   R   0x000000 Signed   Apparent energy (Current Channel B)
#define OVLVL			    0x224 		//0x324   R/W 0xFFFFFF Unsigned Overvoltage level
#define OILVL			    0x225 		//0x325   R/W 0xFFFFFF Unsigned Overcurrent level
#define VPEAK			    0x226 		//0x326   R   0x000000 Unsigned Voltage channel peak
#define RSTVPEAK		  0x227 		//0x327   R   0x000000 Unsigned Read voltage peak with reset
#define IAPEAK			  0x228 		//0x328   R   0x000000 Unsigned Current Channel A peak
#define RSTIAPEAK		  0x229 		//0x329   R   0x000000 Unsigned Read Current Channel A peak with reset
#define IBPEAK			  0x22A 		//0x32A   R   0x000000 Unsigned Current Channel B peak
#define RSTIBPEAK		  0x22B 		//0x32B   R   0x000000 Unsigned Read Current Channel B peak with reset
#define IRQENA			  0x22C 		//0x32C   R/W 0x100000 Unsigned Interrupt enable (Current Channel A, see Table 22)
#define IRQSTATA		  0x22D 		//0x32D   R   0x000000 Unsigned Interrupt status (Current Channel A, see Table 23)
#define RSTIRQSTATA		0x22E 		//0x32E   R   0x000000 Unsigned Reset interrupt status (Current Channel A)
#define IRQENB			  0x22F 		//0x32F   R/W 0x000000 Unsigned Interrupt enable (Current Channel B, see Table 24)
#define IRQSTATB		  0x230 		//0x330   R   0x000000 Unsigned Interrupt status (Current Channel B, see Table 25)
#define RSTIRQSTATB		0x231 		//0x331   R   0x000000 Unsigned Reset interrupt status (Current Channel B)
#define CRC				   		          0x37F //R   0xFFFFFFFF Unsigned Checksum
#define AIGAIN			  0x280 		//0x380   R/W 0x400000 Unsigned Current channel gain (Current Channel A)
#define AVGAIN			  0x281 		//0x381   R/W 0x400000 Unsigned Voltage channel gain
#define AWGAIN			  0x282 		//0x382   R/W 0x400000 Unsigned Active power gain (Current Channel A)
#define AVARGAIN		  0x283 		//0x383   R/W 0x400000 Unsigned Reactive power gain (Current Channel A)
#define AVAGAIN			  0x284 		//0x384   R/W 0x400000 Unsigned Apparent power gain (Current Channel A)
#define Reserved2		  0x285 		//0x385   R/W 0x000000 Signed   This register should not be modified.
#define AIRMSOS			  0x286 		//0x386   R/W 0x000000 Signed   IRMS offset (Current Channel A)
#define Reserved3		  0x287 		//0x387   R/W 0x000000 Signed   This register should not be modified.
#define VRMSOS			  0x288 		//0x388   R/W 0x000000 Signed   VRMS offset
#define AWATTOS			  0x289 		//0x389   R/W 0x000000 Signed   Active power offset correction (Current Channel A)
#define AVAROS			  0x28A 		//0x38A   R/W 0x000000 Signed   Reactive power offset correction (Current Channel A)
#define AVAOS			    0x28B 		//0x38B   R/W 0x000000 Signed   Apparent power offset correction (Current Channel A)
#define BIGAIN			  0x28C 		//0x38C   R/W 0x400000 Unsigned Current channel gain (Current Channel B)
#define BVGAIN			  0x28D 		//0x38D   R/W 0x400000 Unsigned This register should not be modified.
#define BWGAIN			  0x28E 		//0x38E   R/W 0x400000 Unsigned Active power gain (Current Channel B)
#define BVARGAIN		  0x28F 		//0x38F   R/W 0x400000 Unsigned Reactive power gain (Current Channel B)
#define BVAGAIN			  0x290 		//0x390   R/W 0x400000 Unsigned Apparent power gain (Current Channel B)
#define Reserved4		  0x291 		//0x391   R/W 0x000000 Signed   This register should not be modified.
#define BIRMSOS			  0x292 		//0x392   R/W 0x000000 Signed   IRMS offset (Current Channel B)
#define Reserved5		  0x293 		//0x393   R/W 0x000000 Unsigned This register should not be modified.
#define Reserved6		  0x294 		//0x394   R/W 0x000000 Unsigned This register should not be modified.
#define BWATTOS			  0x295 		//0x395   R/W 0x000000 Signed   Active power offset correction (Current Channel B)
#define BVAROS			  0x296 		//0x396   R/W 0x000000 Signed   Reactive power offset correction (Current Channel B)
#define BVAOS			    0x297 		//0x397   R/W 0x000000 Signed   Apparent power offset correction (Current Channel B)
#define LAST_RWDATA		0x2FF 		//0x3FF   R   0x000000 Unsigned Contains the data from the last successful 24-bit/32-bit register communication




