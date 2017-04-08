/*  BYTE Registers  */
sfr P0   = 0x80;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr SPSTAT= 0x84;
sfr SPCTL = 0x85;
sfr SPDAT = 0x86;
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr AUXR  = 0x8E;


sfr P1    = 0x90;
sfr P1M0  = 0x91;
sfr P1M1  = 0x92;
sfr P0M0  = 0x93;
sfr P0M1  = 0x94;
sfr P2M0  = 0x95;
sfr P2M1  = 0x96;

sfr SCON  = 0x98;
sfr SBUF  = 0x99;

sfr P2    = 0xA0;
sfr TEST_WDT = 0xA7;
sfr IE    = 0xA8;
sfr SADDR = 0xA9;

sfr P3    = 0xB0;
sfr P3M0  = 0xB1;
sfr P3M1  = 0xB2;
sfr IPH   = 0xB7;
sfr IP    = 0xB8;
sfr SADEN = 0xB9;
sfr ADC_DATA2  = 0xBE;
sfr ADC_LOW2   = 0xBE;
/*  8052 Extensions  */

sfr ADC_CONTR  = 0xC5;
sfr ADC_DATA8  = 0xC6;
sfr ADC_DATA   = 0xC6;
sfr CLK_DIV    = 0xC7;

sfr T2CON      = 0xC8;
sfr RCAP2L     = 0xCA;
sfr RCAP2H     = 0xCB;
sfr TL2        = 0xCC;
sfr TH2        = 0xCD;

sfr PSW        = 0xD0;
sfr CCON       = 0xD8;
sfr CMOD       = 0xD9;
sfr CCAPM0     = 0xDA;
sfr CCAPM1     = 0xDB;
sfr CCAPM2     = 0xDC;
sfr CCAPM3     = 0xDD;

sfr ACC        = 0xE0;
sfr WDT_CONTR  = 0xe1;
sfr isp_data   = 0xe2;
sfr isp_addrh  = 0xe3;
sfr isp_addrl  = 0xe4;
sfr isp_cmd    = 0xe5;
sfr isp_trig   = 0xe6;
sfr isp_contr  = 0xe7;

sfr CL      = 0xe9;
sfr CCAP0L  = 0xeA;
sfr CCAP1L  = 0xeB;
sfr CCAP2L  = 0xeC;
sfr CCAP3L  = 0xeD;

sfr B     = 0xF0;

sfr PCA_PWM0= 0xF2;
sfr PCA_PWM1= 0xF3;
sfr PCA_PWM2= 0xF4;
sfr PCA_PWM3= 0xF5;


sfr CH    = 0xF9;
sfr CCAP0H= 0xFA;
sfr CCAP1H= 0xFB;
sfr CCAP2H= 0xFC;
sfr CCAP3H= 0xFD;

//----------------------------------
/*  BIT Registers  */
/*  PSW  */
sbit CY    = 0xD7;
sbit AC    = 0xD6;
sbit F0    = 0xD5;
sbit RS1   = 0xD4;
sbit RS0   = 0xD3;
sbit OV    = 0xD2;
sbit P     = 0xD0;

/*  TCON  */
sbit TF1   = 0x8F;
sbit TR1   = 0x8E;
sbit TF0   = 0x8D;
sbit TR0   = 0x8C;
sbit IE1   = 0x8B;
sbit IT1   = 0x8A;
sbit IE0   = 0x89;
sbit IT0   = 0x88;

/*  IE  */
sbit EA    = 0xAF;
sbit ES    = 0xAC;
sbit ET1   = 0xAB;
sbit EX1   = 0xAA;
sbit ET0   = 0xA9;
sbit EX0   = 0xA8;

/*  IP  */
sbit PS    = 0xBC;
sbit PT1   = 0xBB;
sbit PX1   = 0xBA;
sbit PT0   = 0xB9;
sbit PX0   = 0xB8;

/*  P3  */
sbit RD   = 0xB7;
sbit WR   = 0xB6;
sbit T1   = 0xB5;
sbit T0   = 0xB4;
sbit INT1 = 0xB3;
sbit INT0 = 0xB2;
sbit TXD  = 0xB1;
sbit RXD  = 0xB0;

/*  SCON  */
sbit SM0   = 0x9F;
sbit SM1   = 0x9E;
sbit SM2   = 0x9D;
sbit REN   = 0x9C;
sbit TB8   = 0x9B;
sbit RB8   = 0x9A;
sbit TI    = 0x99;
sbit RI    = 0x98;

/*  8052 Extensions  */
/*  IE  */
sbit ET2   = 0xAD;

/*  IP  */
sbit PT2   = 0xBD;

/*  P1  */
sbit T2EX  = 0x91;
sbit T2    = 0x90;
             
/*  T2CON  */
sbit TF2   = 0xCF;
sbit T2IP  = 0xCE;
sbit T2IE  = 0xCD;
sbit T2RSE = 0xCC;
sbit BGEN  = 0xCB;
sbit TR2   = 0xCA;
sbit C_T2  = 0xC9;
sbit CP_RL2= 0xC8;

