#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define MAKE_VR(left, right) (right << 8 | left)
#else
#define MAKE_VR(left, right) ((left << 8 | right) << 16)
#endif
 
enum VALUE_REPRESENTATIONS {
  VR_NONE = 0,
  VR_AE = MAKE_VR('A', 'E'),
  VR_AS = MAKE_VR('A', 'S'),
  VR_AT = MAKE_VR('A', 'T'),
  VR_CS = MAKE_VR('C', 'S'),
  VR_DA = MAKE_VR('D', 'A'),
  VR_DS = MAKE_VR('D', 'S'),
  VR_DT = MAKE_VR('D', 'T'),
  VR_FL = MAKE_VR('F', 'L'),
  VR_FD = MAKE_VR('F', 'D'),
  VR_IS = MAKE_VR('I', 'S'),
  VR_LO = MAKE_VR('L', 'O'),
  VR_LT = MAKE_VR('L', 'T'),
  VR_OB = MAKE_VR('O', 'B'),
  VR_OD = MAKE_VR('O', 'D'),
  VR_OF = MAKE_VR('O', 'F'),
  VR_OL = MAKE_VR('O', 'L'),
  VR_OV = MAKE_VR('O', 'V'),
  VR_OW = MAKE_VR('O', 'W'),
  VR_PN = MAKE_VR('P', 'N'),
  VR_SH = MAKE_VR('S', 'H'),
  VR_SL = MAKE_VR('S', 'L'),
  VR_SQ = MAKE_VR('S', 'Q'),
  VR_SS = MAKE_VR('S', 'S'),
  VR_ST = MAKE_VR('S', 'T'),
  VR_SV = MAKE_VR('S', 'V'),
  VR_TM = MAKE_VR('T', 'M'),
  VR_UC = MAKE_VR('U', 'C'),
  VR_UI = MAKE_VR('U', 'I'),
  VR_UL = MAKE_VR('U', 'L'),
  VR_UN = MAKE_VR('U', 'N'),
  VR_UR = MAKE_VR('U', 'R'),
  VR_US = MAKE_VR('U', 'S'),
  VR_UT = MAKE_VR('U', 'T'),
  VR_UV = MAKE_VR('U', 'V'),
};

static bool is_vr16(const uint32_t vr) {
  // memmem to get SSE ?
  switch (vr) {
  case VR_AE:
  case VR_AS:
  case VR_AT:
  case VR_CS:
  case VR_DA:
  case VR_DS:
  case VR_DT:
  case VR_FD:
  case VR_FL:
  case VR_IS:
  case VR_LO:
  case VR_LT:
  case VR_PN:
  case VR_SH:
  case VR_SL:
  case VR_SS:
  case VR_ST:
  case VR_TM:
  case VR_UI:
  case VR_UL:
  case VR_US:
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
    uint32_t vr = argc;
    printf("found=%d", is_vr16(vr));
}

