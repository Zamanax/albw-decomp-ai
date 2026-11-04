/* System registers as armcc named register variables (ARM Compiler 4.1 documented construct).
 *
 * A declaration, not an asm statement: it allocates no storage, a read emits MRC (VMRS for fpscr),
 * a write emits MCR (VMSR), and every use re-reads the register. armcc 4.1 has no coprocessor
 * intrinsic, so these instructions cannot be written in plain C.
 *
 * Accepted as honest by project-owner decision (2026-11-04) on condition that every user is logged:
 * shared/construct_exceptions.json -> "named_register" lists them, and tools/audit.py refuses an
 * honest source that includes this header without being listed. This is the only file in the
 * repository allowed to declare named registers; add one here only with the same evidence.
 */
#ifndef CP15_H
#define CP15_H

register unsigned int tls_tp __asm("cp15:0:c13:c0:3");  /* TPIDRURO: thread pointer (TLS base) */
register unsigned int dsb_tp __asm("cp15:0:c7:c10:4");  /* write: data synchronisation barrier */
register unsigned int dmb_tp __asm("cp15:0:c7:c10:5");  /* write: data memory barrier */
register unsigned int fpscr_reg __asm("fpscr");         /* VFP status and control */

#endif
