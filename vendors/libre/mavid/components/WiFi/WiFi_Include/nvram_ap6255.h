#if 0 //Help for power calculation
maxp2ga0=80 
dot11agofdmhrbw202gpo=0x4444
above paras means : 11b tx power : 80/4-1.5=18.5
54m/48m/36m/24m tx power=80/4-4/2-1.5=16.5
#endif

const char wifi_nvram_image[] = {
"NVRAMRev=$Rev: 498373 $"   "\x00"
"sromrev=11"                "\x00"
"vendid=0x14e4"	            "\x00"
"devid=0x43ab"              "\x00"
"manfid=0x2d0"			    "\x00"
"prodid=0x06e4"				"\x00"
"macaddr=00:90:4c:11:22:55" "\x00"
"nocrc=1"                   "\x00"
"boardtype=0x6e4"           "\x00"
"boardrev=0x1304"	        "\x00"
"xtalfreq=37400"            "\x00"
"btc_mode=1"                "\x00"
"boardflags=0x00480201"     "\x00"
"boardflags2=0x40800000"    "\x00"
"boardflags3=0x48200100"	"\x00"
"phycal_tempdelta=15"       "\x00"
"rxchain=1"                 "\x00"
"txchain=1"	                "\x00"
"aa2g=1"                    "\x00"
"aa5g=1"	                "\x00"
"tssipos5g=1"				"\x00"
"tssipos2g=1"	            "\x00"
"femctrl=0"					"\x00"
"AvVmid_c0=1,165,2,100,2,100,2,100,2,100"	"\x00"
"pa2ga0=-170,6411,-751"  "\x00"
"pa2ga1=-118,4850,-635"	 "\x00"
"pa5ga0=-157,6889,-812,-157,6883,-809,-156,6618,-789,-152,6873,-808"  "\x00"
"pa5ga1=-142,4930,-655,-150,4859,-646,-156,4887,-644,-158,4864,-641"  "\x00"
"itrsw=1"	                 "\x00"
"pdoffset2g40ma0=10"         "\x00"
"pdoffset40ma0=0xaaaa"       "\x00"
"pdoffset80ma0=0xaaaa"       "\x00"
"extpagain5g=2"              "\x00"
"extpagain2g=2"				 "\x00"
"tworangetssi2g=0"  "\x00"
"tworangetssi5g=0"  "\x00"
"ltecxmux=0"                 "\x00"
"ltecxpadnum=0x0504"         "\x00"
"ltecxfnsel=0x22"	         "\x00"
"ltecxgcigpio=0x32"	         "\x00"
#ifdef  SONY_REQ
"maxp2ga0=36"  "\x00"
#else
"maxp2ga0=80"  "\x00"
#endif
"cckbw202gpo=0x5533"   "\x00"
"ofdmlrbw202gpo=0x0055"  "\x00"
"dot11agofdmhrbw202gpo=0x7775"  "\x00"
"mcsbw202gpo=0x98777755"																					 "\x00"
"mcsbw402gpo=0x98999977"  "\x00"
"maxp5ga0=68,68,66,70"  "\x00"
"mcsbw205glpo=0xb9111100"  "\x00"
"mcsbw205gmpo=0xb9222200"  "\x00"
"mcsbw205ghpo=0xb9111100"  "\x00"
"mcsbw405glpo=0xb9222200"  "\x00"
"mcsbw405gmpo=0xb9222200"  "\x00"
"mcsbw405ghpo=0xb9222200"  "\x00"
"mcsbw805glpo=0xdddddbbb"  "\x00"
"mcsbw805gmpo=0xdddddbbb"  "\x00"
"mcsbw805ghpo=0xdddddbbb"  "\x00"
"swctrlmap_2g=0x00000000,0x00000000,0x00000000,0x010000,0x3ff"  "\x00"
"swctrlmap_5g=0x00100010,0x00200020,0x00200020,0x010000,0x3fe"  "\x00"
"swctrlmapext_5g=0x00000000,0x00000000,0x00000000,0x000000,0x3"  "\x00"
"swctrlmapext_2g=0x00000000,0x00000000,0x00000000,0x000000,0x3"  "\x00"
"vcodivmode=1"																					 "\x00"
"deadman_to=481500000"																					 "\x00"
"ed_thresh2g=-69"  "\x00"
"ed_thresh5g=-69"  "\x00"
"eu_edthresh2g=-69"  "\x00"
"eu_edthresh5g=-69"  "\x00"
"ldo1=4"																					 "\x00"
"rawtempsense=0x1ff"																					 "\x00"
"cckPwrIdxCorr=3"																					 "\x00"
"cckTssiDelay=150"																					 "\x00"
"ofdmTssiDelay=150"																					 "\x00"
"txpwr2gAdcScale=1"																					 "\x00"
"txpwr5gAdcScale=1"																					 "\x00"
"dot11b_opts=0x3aa85"																					 "\x00"
"cbfilttype=2"  "\x00"
"muxenab=0x10"                                                                                  "\x00"
  "\x00\x00"}; 
