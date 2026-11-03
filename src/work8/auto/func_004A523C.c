/* func_004A523C - 0x004A523C (USA code.bin), 84 bytes
 *
 * Applies an on/off flag to the session object hanging off a node and, when
 * the value actually changes, raises the node's dirty marker.
 *
 *   p->field_1C            node object            (int*)
 *   node->field_00->0x10   session object         (int*, byte at +0x44)
 *   node->field_00->0x70   node dirty bits        (bit 1)
 *
 * The per-flag work lives in the inlined helper; the session value is handed
 * to it by value.
 */
typedef unsigned char byte;
typedef unsigned int uint;

static __inline void applyFlag(int *node, int session, uint on)
{
  byte bVar1;
  uint uVar4;

  bVar1 = *(byte *)(session + 0x44);
  if ((bVar1 & 1) != 0) {
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  if ((uVar4 != on) &&
      (*(byte *)(session + 0x44) = bVar1 & 0xfe | (byte)on, on != 0)) {
    *(byte *)(node + 0x1c) = *(byte *)(node + 0x1c) | 2;
  }
}

void func_004A523C(int param_1, uint param_2)
{
  int *piVar2;
  int iVar3;

  piVar2 = *(int **)(param_1 + 0x1c);
  if (piVar2 == 0) {
    return;
  }
  iVar3 = *(int *)(*piVar2 + 0x10);
  if (iVar3 == 0) {
    return;
  }
  applyFlag(piVar2, iVar3, param_2);
}
