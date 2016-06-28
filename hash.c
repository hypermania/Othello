#include "hash.h"

unsigned int hash_board(Board board){
  unsigned int result = 0;
  unsigned char ch;

  int i; int length = BOARD_SIZE_SQR * sizeof(char);
  for(i=0;i<length;i++){
    ch = *board++;
    result = ((result & 0x00ffffff) << 8) ^ hash_consts[result >> 24 ^ ch];
  }
  
  return result;
}

unsigned int hash_state(State state){
  unsigned int result = 0;
  unsigned char ch;

  char *ptr = (char *)state;
  
  int i; int length = (sizeof state->board) + (sizeof state->turn);
  for(i=0;i<length;i++){
    ch = *ptr++;
    result = ((result & 0x00ffffff) << 8) ^ hash_consts[result >> 24 ^ ch];
  }
  
  return result;
}


unsigned int hash_mem(char *board, size_t size){
  unsigned int result = 0;
  unsigned char ch;

  int i;
  for(i=0;i<size;i++){
    ch = *board++;
    result = ((result & 0x00ffffff) << 8) ^ hash_consts[result >> 24 ^ ch];
  }
  
  return result;
}



unsigned int hash_consts[256] = { 
	0x6c1603e5,
	0x6104a65d,
	0x35d54a20,
	0x21242f1f,
	0x41717337,
	0x33d4e1be,
	0x6453831c,
	0x26d2f38f,
	0x3d012105,
	0x4aac433d,
	0x743d0b02,
	0x40999431,
	0x24134331,
	0x60be3130,
	0x4f26b71c,
	0x2010977f,
	0x747290b7,
	0x7dcbea1a,
	0x67b532c8,
	0x737a2c81,
	0x27b2ea61,
	0x5d6b2070,
	0x730d220c,
	0x578cc914,
	0x3c6f2c28,
	0x0ce3c6f5,
	0x3792f154,
	0x4e318b59,
	0x74dd8bd2,
	0x7bb9c1e7,
	0x3d0ea806,
	0x6ec279c7,
	0x2157cfe0,
	0x670b26dd,
	0x463bc75e,
	0x01cc1e51,
	0x5c1f487c,
	0x330ca65a,
	0x6994852b,
	0x55860b49,
	0x002572a9,
	0x3f2d8f3c,
	0x6f0d9b94,
	0x1f3878bb,
	0x29a04bea,
	0x6f6b99f0,
	0x1874e2ee,
	0x48a43122,
	0x1e8af77c,
	0x7bd85be1,
	0x66ce95b7,
	0x39571121,
	0x0a4c0c6f,
	0x28f78c9d,
	0x410432ef,
	0x77671946,
	0x0df59b84,
	0x468fecd4,
	0x5a709ab1,
	0x46128b34,
	0x6840733d,
	0x45280362,
	0x7b5f0fbb,
	0x4d352fc8,
	0x4b370934,
	0x38f56681,
	0x4c5320bc,
	0x314470d4,
	0x49aeeeb3,
	0x25298462,
	0x183df99c,
	0x17e6c0d0,
	0x4e6f59ff,
	0x540d6a33,
	0x3cfef7b0,
	0x0b7f5d5a,
	0x60f92a51,
	0x703a02f1,
	0x7631595f,
	0x6bd5bc90,
	0x72f7563a,
	0x762790bc,
	0x453260da,
	0x3215fd2d,
	0x5a46b9f7,
	0x2347fa98,
	0x67e37312,
	0x6cbbf4c2,
	0x7290a309,
	0x4b7e9aec,
	0x7991e535,
	0x4a337233,
	0x39ac0d47,
	0x5482eba9,
	0x7f85607a,
	0x755e546e,
	0x658bad24,
	0x0a8b32b5,
	0x4e6fad41,
	0x3e43cdb8,
	0x50a8ab04,
	0x6c2b8082,
	0x1f1bca90,
	0x5da17053,
	0x0efe41ab,
	0x1c380d05,
	0x65b4e511,
	0x2a908b66,
	0x686fd720,
	0x0ce0b50c,
	0x12bbdffd,
	0x594d4582,
	0x05ca3add,
	0x49747139,
	0x747b679e,
	0x44609959,
	0x571d8b70,
	0x036accf1,
	0x5147ad52,
	0x4d9c7f4c,
	0x49b8d381,
	0x32132661,
	0x2f60bedc,
	0x7d8191d0,
	0x04a87e89,
	0x02c4fc33,
	0x7b0312ae,
	0x17ad291b,
	0x0fdbcbf7,
	0x1af42bcb,
	0x667edd40,
	0x77ee9af9,
	0x02ea8a18,
	0x367aad89,
	0x0cfdf58d,
	0x21450e10,
	0x1c442230,
	0x52ce7644,
	0x2cd66ec6,
	0x1714a830,
	0x40772936,
	0x050a5c89,
	0x0ceafcbb,
	0x7e7e7d45,
	0x19847d93,
	0x2de523de,
	0x5da50366,
	0x6b4e48ed,
	0x7590d1f8,
	0x15afb49a,
	0x56191602,
	0x7bb7dfdb,
	0x076e369c,
	0x568dc7b1,
	0x6c36df81,
	0x2bd0e5b8,
	0x201685d1,
	0x4c63a90e,
	0x389dbf0a,
	0x16607c20,
	0x3c5e38ba,
	0x3477c7ad,
	0x48d8afad,
	0x4119cf1e,
	0x27dd766a,
	0x2db72575,
	0x6b387b39,
	0x201e8fc2,
	0x47c1bf7a,
	0x01978367,
	0x5eebe8c0,
	0x2aff504b,
	0x05d961f8,
	0x23f3fac1,
	0x1ebc97db,
	0x7a002466,
	0x2d15ba29,
	0x24d92efa,
	0x2dfa4e09,
	0x793435dd,
	0x511ea64d,
	0x4f7f7231,
	0x5b996a34,
	0x31aa8c7b,
	0x350ba60c,
	0x534e7dc0,
	0x0031f219,
	0x189d995a,
	0x2acdacb2,
	0x1ea52ea3,
	0x51964db6,
	0x30778a3a,
	0x700ddfa9,
	0x48b92f8d,
	0x350b44d0,
	0x337d7ccd,
	0x59d58d98,
	0x3588729b,
	0x54c2d5ba,
	0x05fce072,
	0x39014cf0,
	0x212e590a,
	0x142f12d6,
	0x4387842d,
	0x3e5eb81e,
	0x47dc1dd9,
	0x60b3b98f,
	0x7122d22f,
	0x3f4e7c24,
	0x27f1864d,
	0x3bc31ff0,
	0x678ed08c,
	0x700088fe,
	0x67fd3665,
	0x18106d28,
	0x7fed019e,
	0x51090d6f,
	0x0aaf0c5d,
	0x5cdef711,
	0x7e502a8f,
	0x336ebbce,
	0x56d99466,
	0x28787e0f,
	0x1b54c6b0,
	0x5bd1470b,
	0x004d40af,
	0x694f4349,
	0x43a0d749,
	0x0c843282,
	0x0f383e29,
	0x531b2122,
	0x6fd3e373,
	0x23d6797a,
	0x7d3ffc51,
	0x0cd2b887,
	0x6d4dd80d,
	0x32c6f0b9,
	0x0a6986d0,
	0x2329d2be,
	0x39fb306c,
	0x656b7281,
	0x6e410a93,
	0x1113ecba,
	0x42abb8bc,
	0x534cdd79,
	0x2c6c3bb1,
	0x6f993bf1,
	0x23a2eecd,
	0x0260a4c0,
	0x05347443,
	0x572ae6f3,
	0x47783364,
	0x7926fee4,
	0x781ec338,
	0x747600dc
};





