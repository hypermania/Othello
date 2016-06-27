#include "index_computation.h"

unsigned long int index_for_config_00(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_00_squares[i]){
index += pow3[i];
} else if(config.b & pat_00_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_01(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_01_squares[i]){
index += pow3[i];
} else if(config.b & pat_01_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_02(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<7;i++){
if(config.w & pat_02_squares[i]){
index += pow3[i];
} else if(config.b & pat_02_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_03(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<7;i++){
if(config.w & pat_03_squares[i]){
index += pow3[i];
} else if(config.b & pat_03_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_04(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<7;i++){
if(config.w & pat_04_squares[i]){
index += pow3[i];
} else if(config.b & pat_04_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_05(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<7;i++){
if(config.w & pat_05_squares[i]){
index += pow3[i];
} else if(config.b & pat_05_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_06(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<6;i++){
if(config.w & pat_06_squares[i]){
index += pow3[i];
} else if(config.b & pat_06_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_07(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<6;i++){
if(config.w & pat_07_squares[i]){
index += pow3[i];
} else if(config.b & pat_07_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_08(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<6;i++){
if(config.w & pat_08_squares[i]){
index += pow3[i];
} else if(config.b & pat_08_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_09(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<6;i++){
if(config.w & pat_09_squares[i]){
index += pow3[i];
} else if(config.b & pat_09_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_10(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<5;i++){
if(config.w & pat_10_squares[i]){
index += pow3[i];
} else if(config.b & pat_10_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_11(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<5;i++){
if(config.w & pat_11_squares[i]){
index += pow3[i];
} else if(config.b & pat_11_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_12(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<5;i++){
if(config.w & pat_12_squares[i]){
index += pow3[i];
} else if(config.b & pat_12_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_13(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<5;i++){
if(config.w & pat_13_squares[i]){
index += pow3[i];
} else if(config.b & pat_13_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_14(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<4;i++){
if(config.w & pat_14_squares[i]){
index += pow3[i];
} else if(config.b & pat_14_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_15(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<4;i++){
if(config.w & pat_15_squares[i]){
index += pow3[i];
} else if(config.b & pat_15_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_16(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<4;i++){
if(config.w & pat_16_squares[i]){
index += pow3[i];
} else if(config.b & pat_16_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_17(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<4;i++){
if(config.w & pat_17_squares[i]){
index += pow3[i];
} else if(config.b & pat_17_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_18(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_18_squares[i]){
index += pow3[i];
} else if(config.b & pat_18_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_19(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_19_squares[i]){
index += pow3[i];
} else if(config.b & pat_19_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_20(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_20_squares[i]){
index += pow3[i];
} else if(config.b & pat_20_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_21(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_21_squares[i]){
index += pow3[i];
} else if(config.b & pat_21_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_22(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_22_squares[i]){
index += pow3[i];
} else if(config.b & pat_22_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_23(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_23_squares[i]){
index += pow3[i];
} else if(config.b & pat_23_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_24(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_24_squares[i]){
index += pow3[i];
} else if(config.b & pat_24_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_25(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_25_squares[i]){
index += pow3[i];
} else if(config.b & pat_25_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_26(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_26_squares[i]){
index += pow3[i];
} else if(config.b & pat_26_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_27(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_27_squares[i]){
index += pow3[i];
} else if(config.b & pat_27_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_28(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_28_squares[i]){
index += pow3[i];
} else if(config.b & pat_28_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_29(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_29_squares[i]){
index += pow3[i];
} else if(config.b & pat_29_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_30(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_30_squares[i]){
index += pow3[i];
} else if(config.b & pat_30_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_31(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_31_squares[i]){
index += pow3[i];
} else if(config.b & pat_31_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_32(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_32_squares[i]){
index += pow3[i];
} else if(config.b & pat_32_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_33(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<8;i++){
if(config.w & pat_33_squares[i]){
index += pow3[i];
} else if(config.b & pat_33_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_34(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_34_squares[i]){
index += pow3[i];
} else if(config.b & pat_34_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_35(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_35_squares[i]){
index += pow3[i];
} else if(config.b & pat_35_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_36(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_36_squares[i]){
index += pow3[i];
} else if(config.b & pat_36_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_37(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_37_squares[i]){
index += pow3[i];
} else if(config.b & pat_37_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_38(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<9;i++){
if(config.w & pat_38_squares[i]){
index += pow3[i];
} else if(config.b & pat_38_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_39(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<9;i++){
if(config.w & pat_39_squares[i]){
index += pow3[i];
} else if(config.b & pat_39_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_40(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<9;i++){
if(config.w & pat_40_squares[i]){
index += pow3[i];
} else if(config.b & pat_40_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_41(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<9;i++){
if(config.w & pat_41_squares[i]){
index += pow3[i];
} else if(config.b & pat_41_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_42(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_42_squares[i]){
index += pow3[i];
} else if(config.b & pat_42_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_43(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_43_squares[i]){
index += pow3[i];
} else if(config.b & pat_43_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_44(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_44_squares[i]){
index += pow3[i];
} else if(config.b & pat_44_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_45(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_45_squares[i]){
index += pow3[i];
} else if(config.b & pat_45_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_46(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_46_squares[i]){
index += pow3[i];
} else if(config.b & pat_46_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_47(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_47_squares[i]){
index += pow3[i];
} else if(config.b & pat_47_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_48(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_48_squares[i]){
index += pow3[i];
} else if(config.b & pat_48_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}

unsigned long int index_for_config_49(Config_store config){
unsigned long int index = 0;
int i;
for(i=0;i<10;i++){
if(config.w & pat_49_squares[i]){
index += pow3[i];
} else if(config.b & pat_49_squares[i]){
index += 2 * pow3[i];
}
}
return index;
}


unsigned long int index_for_config_fast(Pattern pattern, Config_store config){
  /*
  if(pattern & 0x8100000008000081){
    if(pattern & 0x0040000000010200){
      if(pattern == 0x8040201008040201) return index_for_config_00(config);
      if(pattern == 0x0101010101010101) return index_for_config_21(config);
      if(pattern == 0xff42000000000000) return index_for_config_34(config);
      if(pattern == 0x80c080808080c080) return index_for_config_35(config);
      if(pattern == 0x00000000000042ff) return index_for_config_36(config);
      if(pattern == 0x0103010101010301) return index_for_config_37(config);
      if(pattern == 0xe0e0e00000000000) return index_for_config_38(config);
      if(pattern == 0x0000000000070707) return index_for_config_40(config);
      if(pattern == 0xf8f8000000000000) return index_for_config_42(config);
      if(pattern == 0x0000000000001f1f) return index_for_config_44(config);
      if(pattern == 0xc0c0c0c0c0000000) return index_for_config_46(config);
      if(pattern == 0x0000000303030303) return index_for_config_48(config);
    } else {
      if(pattern == 0x0102040810204080) return index_for_config_01(config);
      if(pattern == 0x0001020408102040) return index_for_config_05(config);
      if(pattern == 0xff00000000000000) return index_for_config_18(config);
      if(pattern == 0x8080808080808080) return index_for_config_19(config);
      if(pattern == 0x00000000000000ff) return index_for_config_20(config);
      if(pattern == 0x00000000ff000000) return index_for_config_32(config);
      if(pattern == 0x0808080808080808) return index_for_config_33(config);
      if(pattern == 0x0000000000e0e0e0) return index_for_config_39(config);
      if(pattern == 0x0707070000000000) return index_for_config_41(config);
      if(pattern == 0x000000c0c0c0c0c0) return index_for_config_43(config);
      if(pattern == 0x0303030303000000) return index_for_config_45(config);
      if(pattern == 0x1f1f000000000000) return index_for_config_47(config);
      if(pattern == 0x000000000000f8f8) return index_for_config_49(config);
    }
  } else {
    if(pattern & 0x00400000001d0200){
      if(pattern == 0x0080402010080402) return index_for_config_04(config);
      if(pattern == 0x2010080402010000) return index_for_config_06(config);
      if(pattern == 0x0000804020100804) return index_for_config_08(config);
      if(pattern == 0x0000010204081020) return index_for_config_09(config);
      if(pattern == 0x0000000102040810) return index_for_config_13(config);
      if(pattern == 0x00ff000000000000) return index_for_config_22(config);
      if(pattern == 0x4040404040404040) return index_for_config_23(config);
      if(pattern == 0x000000000000ff00) return index_for_config_24(config);
      if(pattern == 0x0202020202020202) return index_for_config_25(config);
      if(pattern == 0x0000000000ff0000) return index_for_config_28(config);
      if(pattern == 0x0404040404040404) return index_for_config_29(config);
      if(pattern == 0x1010101010101010) return index_for_config_31(config);
    } else {
      if(pattern == 0x4020100804020100) return index_for_config_02(config);
      if(pattern == 0x0204081020408000) return index_for_config_03(config);
      if(pattern == 0x0408102040800000) return index_for_config_07(config);
      if(pattern == 0x1008040201000000) return index_for_config_10(config);
      if(pattern == 0x0810204080000000) return index_for_config_11(config);
      if(pattern == 0x0000008040201008) return index_for_config_12(config);
      if(pattern == 0x0804020100000000) return index_for_config_14(config);
      if(pattern == 0x1020408000000000) return index_for_config_15(config);
      if(pattern == 0x0000000080402010) return index_for_config_16(config);
      if(pattern == 0x0000000001020408) return index_for_config_17(config);
      if(pattern == 0x0000ff0000000000) return index_for_config_26(config);
      if(pattern == 0x2020202020202020) return index_for_config_27(config);
      if(pattern == 0x000000ff00000000) return index_for_config_30(config);
    }
  }
  */

if(pattern & 0x0400042000085000){
  if(pattern & 0x8842000200020000){
    if(pattern & 0x00442040c2008000){
      if(pattern & 0x0000022007000080){
	if(pattern & 0x4400000002052001){
	  if(pattern == 0x0707070000000000) return index_for_config_41(config);
	} else {
	  if(pattern == 0x000000ff00000000) return index_for_config_30(config);
	  if(pattern == 0x80c080808080c080) return index_for_config_35(config);
	}
      } else {
	if(pattern & 0x8000201000200000){
	  if(pattern == 0xff42000000000000) return index_for_config_34(config);
	} else {
	  if(pattern == 0x4040404040404040) return index_for_config_23(config);
	  if(pattern == 0x1f1f000000000000) return index_for_config_47(config);
	}
      }
    } else {
      if(pattern & 0x0208020180000000){
	if(pattern & 0x2400200002010000){
	  if(pattern == 0xff00000000000000) return index_for_config_18(config);
	} else {
	  if(pattern == 0x1008040201000000) return index_for_config_10(config);
	  if(pattern == 0x0808080808080808) return index_for_config_33(config);
	}
      } else {
	if(pattern & 0x0808006800000000){
	  if(pattern == 0x0102040810204080) return index_for_config_01(config);
	} else {
	  if(pattern == 0x0000010204081020) return index_for_config_09(config);
	  if(pattern == 0x0000000000ff0000) return index_for_config_28(config);
	}
      }
    }
  } else {
    if(pattern & 0x20000010020c0100){
      if(pattern & 0x4000100000180010){
	if(pattern & 0x0000001008050000){
	  if(pattern == 0x1010101010101010) return index_for_config_31(config);
	} else {
	  if(pattern == 0x0080402010080402) return index_for_config_04(config);
	  if(pattern == 0x0000000000001f1f) return index_for_config_44(config);
	}
      } else {
	if(pattern & 0x0000010044120002){
	  if(pattern == 0x0404040404040404) return index_for_config_29(config);
	} else {
	  if(pattern == 0x000000000000ff00) return index_for_config_24(config);
	  if(pattern == 0x2020202020202020) return index_for_config_27(config);
	}
      }
    } else {
      if(pattern & 0x2100040000041000){
	if(pattern & 0x000a2000000a0004){
	  if(pattern == 0x0000ff0000000000) return index_for_config_26(config);
	} else {
	  if(pattern == 0x0000008040201008) return index_for_config_12(config);
	  if(pattern == 0x000000000000f8f8) return index_for_config_49(config);
	}
      } else {
	if(pattern & 0x0020b00800000600){
	  if(pattern == 0x0408102040800000) return index_for_config_07(config);
	  if(pattern == 0x00000000000042ff) return index_for_config_36(config);
	} else {
	  if(pattern == 0x0000000000e0e0e0) return index_for_config_39(config);
	  if(pattern == 0x000000c0c0c0c0c0) return index_for_config_43(config);
	}
      }
    }
  }
 } else {
  if(pattern & 0x0200421004000040){
    if(pattern & 0xa000004008180500){
      if(pattern & 0x0000000008440861){
	if(pattern & 0x40004100040800a8){
	  if(pattern == 0x00000000ff000000) return index_for_config_32(config);
	} else {
	  if(pattern == 0x8040201008040201) return index_for_config_00(config);
	  if(pattern == 0x0001020408102040) return index_for_config_05(config);
	}
      } else {
	if(pattern & 0x0002094042001000){
	  if(pattern == 0xc0c0c0c0c0000000) return index_for_config_46(config);
	} else {
	  if(pattern == 0x4020100804020100) return index_for_config_02(config);
	  if(pattern == 0xe0e0e00000000000) return index_for_config_38(config);
	}
      }
    } else {
      if(pattern & 0x200000020800d000){
	if(pattern & 0x000458000820c000){
	  if(pattern == 0x0204081020408000) return index_for_config_03(config);
	} else {
	  if(pattern == 0x0202020202020202) return index_for_config_25(config);
	  if(pattern == 0x0303030303000000) return index_for_config_45(config);
	}
      } else {
	if(pattern & 0x0000010240080004){
	  if(pattern == 0x00000000000000ff) return index_for_config_20(config);
	} else {
	  if(pattern == 0x0804020100000000) return index_for_config_14(config);
	  if(pattern == 0x1020408000000000) return index_for_config_15(config);
	}
      }
    }
  } else {
    if(pattern & 0x0010100000040000){
      if(pattern & 0x4000a00001900001){
	if(pattern & 0x0000140000444000){
	  if(pattern == 0x0000000000070707) return index_for_config_40(config);
	} else {
	  if(pattern == 0x0810204080000000) return index_for_config_11(config);
	  if(pattern == 0xf8f8000000000000) return index_for_config_42(config);
	}
      } else {
	if(pattern & 0x000c400004000444){
	  if(pattern == 0x00ff000000000000) return index_for_config_22(config);
	} else {
	  if(pattern == 0x2010080402010000) return index_for_config_06(config);
	  if(pattern == 0x0000000102040810) return index_for_config_13(config);
	}
      }
    } else {
      if(pattern & 0x0000080100010000){
	if(pattern & 0x0002400020200004){
	  if(pattern == 0x0103010101010301) return index_for_config_37(config);
	} else {
	  if(pattern == 0x0101010101010101) return index_for_config_21(config);
	  if(pattern == 0x0000000303030303) return index_for_config_48(config);
	}
      } else {
	if(pattern & 0x0480800108000000){
	  if(pattern == 0x0000804020100804) return index_for_config_08(config);
	  if(pattern == 0x8080808080808080) return index_for_config_19(config);
	} else {
	  if(pattern == 0x0000000080402010) return index_for_config_16(config);
	  if(pattern == 0x0000000001020408) return index_for_config_17(config);
	}
      }
    }
  }
}


  
if(pattern == 0x8040201008040201){
return index_for_config_00(config);
}
  
if(pattern == 0x0102040810204080){
return index_for_config_01(config);
}

if(pattern == 0x4020100804020100){
return index_for_config_02(config);
}

if(pattern == 0x0204081020408000){
return index_for_config_03(config);
}

if(pattern == 0x0080402010080402){
return index_for_config_04(config);
}

if(pattern == 0x0001020408102040){
return index_for_config_05(config);
}

if(pattern == 0x2010080402010000){
return index_for_config_06(config);
}

if(pattern == 0x0408102040800000){
return index_for_config_07(config);
}

if(pattern == 0x0000804020100804){
return index_for_config_08(config);
}

if(pattern == 0x0000010204081020){
return index_for_config_09(config);
}

if(pattern == 0x1008040201000000){
return index_for_config_10(config);
}

if(pattern == 0x0810204080000000){
return index_for_config_11(config);
}

if(pattern == 0x0000008040201008){
return index_for_config_12(config);
}

if(pattern == 0x0000000102040810){
return index_for_config_13(config);
}

if(pattern == 0x0804020100000000){
return index_for_config_14(config);
}

if(pattern == 0x1020408000000000){
return index_for_config_15(config);
}

if(pattern == 0x0000000080402010){
return index_for_config_16(config);
}

if(pattern == 0x0000000001020408){
return index_for_config_17(config);
}

if(pattern == 0xff00000000000000){
return index_for_config_18(config);
}

if(pattern == 0x8080808080808080){
return index_for_config_19(config);
}

if(pattern == 0x00000000000000ff){
return index_for_config_20(config);
}

if(pattern == 0x0101010101010101){
return index_for_config_21(config);
}

if(pattern == 0x00ff000000000000){
return index_for_config_22(config);
}

if(pattern == 0x4040404040404040){
return index_for_config_23(config);
}

if(pattern == 0x000000000000ff00){
return index_for_config_24(config);
}

if(pattern == 0x0202020202020202){
return index_for_config_25(config);
}

if(pattern == 0x0000ff0000000000){
return index_for_config_26(config);
}

if(pattern == 0x2020202020202020){
return index_for_config_27(config);
}

if(pattern == 0x0000000000ff0000){
return index_for_config_28(config);
}

if(pattern == 0x0404040404040404){
return index_for_config_29(config);
}

if(pattern == 0x000000ff00000000){
return index_for_config_30(config);
}

if(pattern == 0x1010101010101010){
return index_for_config_31(config);
}

if(pattern == 0x00000000ff000000){
return index_for_config_32(config);
}

if(pattern == 0x0808080808080808){
return index_for_config_33(config);
}

if(pattern == 0xff42000000000000){
return index_for_config_34(config);
}

if(pattern == 0x80c080808080c080){
return index_for_config_35(config);
}

if(pattern == 0x00000000000042ff){
return index_for_config_36(config);
}

if(pattern == 0x0103010101010301){
return index_for_config_37(config);
}

if(pattern == 0xe0e0e00000000000){
return index_for_config_38(config);
}

if(pattern == 0x0000000000e0e0e0){
return index_for_config_39(config);
}

if(pattern == 0x0000000000070707){
return index_for_config_40(config);
}

if(pattern == 0x0707070000000000){
return index_for_config_41(config);
}

if(pattern == 0xf8f8000000000000){
return index_for_config_42(config);
}

if(pattern == 0x000000c0c0c0c0c0){
return index_for_config_43(config);
}

if(pattern == 0x0000000000001f1f){
return index_for_config_44(config);
}

if(pattern == 0x0303030303000000){
return index_for_config_45(config);
}

if(pattern == 0xc0c0c0c0c0000000){
return index_for_config_46(config);
}

if(pattern == 0x1f1f000000000000){
return index_for_config_47(config);
}

if(pattern == 0x0000000303030303){
return index_for_config_48(config);
}

if(pattern == 0x000000000000f8f8){
return index_for_config_49(config);
}

 return ULLONG_MAX;
}

unsigned long int index_for_config(Pattern pattern, Config_store config){

  return index_for_config_fast(pattern, config);
  
  unsigned long int fast_result = index_for_config_fast(pattern, config);
  if(fast_result != ULLONG_MAX)
    return fast_result;

  unsigned long int mask;
  unsigned long int result = 0;
  for(mask = 1; mask != 0; mask <<= 1){
    if(mask & pattern){
      result *= 3;
      if(config.x & mask){
	result += 0;
      } else if(config.w & mask){
	result += 1;
      } else {
	result += 2;
      }
    }
  }
  return result;
}
