
#include "coredump.h"
#include "aop_hwio.h"
#include "aop_ipc.h"
#include "aop_ulog.h"
#include "mpm_pshold_hwio.h"
#include "IPCC.h"

extern RPM_LOG_CONTEXT rpm_ulogContext;
extern void set_gpo_bit(void);
extern uint32 is_debug_path_2_ddr_on(void);
extern bool check_nocs_b4_acking_sdi;
extern uint32 g_bypass_notify_tz;

IPCC_Handle hIPCC2;

//__attribute__((section("aop_core_dump")))
riscv_core_dump_t aop_core_dump =
{
    .cookie = 0xbaff1ed,
    .chip_reset_en = 0,
    .ulog_state = &rpm_ulogContext,
};

void setup_notify_tz(void)
{
  IPCC_Attach(&hIPCC2, IPCC_P_MPROC);
}

void __attribute__((used)) notify_tz(void)
{
  if(g_bypass_notify_tz == 1) { //trigger crash dump directly from AOP side
    g_bypass_notify_tz = 0;
	   return; //bypass notify tz 
  }

  if (!hIPCC2)
  {
    IPCC_Attach(&hIPCC2, IPCC_P_MPROC);
  }
  IPCC_Trigger(hIPCC2, IPCC_C_TZ, 1, 1);
}


void __attribute__((used)) err_fatal_sw_event(unsigned ra, unsigned mcause)
{
  SWEVENT(AOP_RISCV_ERR_FATAL, ra, mcause);
}


void __attribute__((used)) reset_chip(void)
{
  if(aop_core_dump.chip_reset_en)
  {
      HWIO_OUT(MPM_PS_HOLD, 0);
  }
}

void force_gpo_bit(void)
{
  if(check_nocs_b4_acking_sdi && is_debug_path_2_ddr_on())
  {
    //set bit when ddr is on
    set_gpo_bit();
  }	
}

void __attribute__((used)) ddraux_log(void)
{
    copy_ddraux_log();
}

__attribute__((used))
static const uint32_t timer_addr_lo = HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_ADDR;

volatile int in_abort;

__asm void abort(void)
{

  /* Disable all interrupts except NMI */
  asm("csrw mie, x0");

  /* Using temporary registers as scratch registers. Push them onto stack */
  asm("addi sp, sp, -16");
  asm("sw a0, 0(sp)");
  asm("sw a1, 4(sp)");
  asm("sw a2, 8(sp)");
  asm("sw a3, 12(sp)");

  /* updating global variable (in_abort) */
  asm("li a0, 1");
  asm("la a1, in_abort");
  asm("sw a0, 0(a1)");

  /* Get the address of the core dump structure. */
  asm("la   a0, aop_core_dump");

  /* If we have already dumped registers on this run, stop here. */
  asm("lw    a1, 4(a0)"); /* aop_core_dump.dumped_at first chunk */
  asm("bnez  a1, hang "); /* if nonzero, previous dump performed */
  asm("lw    a1, 8(a0)"); /* aop_core_dump.dumped_at second chunk */
  asm("bnez  a1, hang"); /* if nonzero, previous dump performed */

  /* Read the timetick and store it */
  asm("la   a1, timer_addr_lo");
  asm("lw   a1, 0(a1)");   /* a1 now points to "lo" word of timetick */

asm("retry:");
  asm("lw   a3, 4(a1)"); /* read "hi" word */
  asm("lw   a2, 0(a1)"); /* read "lo" word */
  asm("sw   a2, 4(a0)"); /* save "lo" word */
  asm("lw   a2, 4(a1)"); /* read "hi" word again */
  asm("bne  a2, a3, retry"); /* if "hi" word rolled over while we dumped we must retry */
  asm("sw   a2, 8(a0)"); /* save "hi" word */

  /* Store x5-x31, but skip a0-a3 (x10-x13) */  
  asm("la   a0, aop_core_dump");  /* get a fresh pointer to the core dump  */
  asm("add  a0, a0, 12"); /* move past cookie and timestamp to where x5-x31 should be stored. */
  asm("sw x5, 0(a0)");
  asm("sw x6, 4(a0)");
  asm("sw x7, 8(a0)");
  asm("sw x8, 12(a0)");
  asm("sw x9, 16(a0)");
  asm("sw x14, 36(a0)");
  asm("sw x15, 40(a0)");
  asm("sw x16, 44(a0)");
  asm("sw x17, 48(a0)");
  asm("sw x18, 52(a0)");
  asm("sw x19, 56(a0)");
  asm("sw x20, 60(a0)");
  asm("sw x21, 64(a0)");
  asm("sw x22, 68(a0)");
  asm("sw x23, 72(a0)");
  asm("sw x24, 76(a0)");
  asm("sw x25, 80(a0)");
  asm("sw x26, 84(a0)");
  asm("sw x27, 88(a0)");
  asm("sw x28, 92(a0)");
  asm("sw x29, 96(a0)");
  asm("sw x30, 100(a0)");
  asm("sw x31, 104(a0)");

  /* Go back and get original values of a0-a3 (x10-x13) from stack */
  asm("lw   a2, 0(sp)");
  asm("lw   a3, 4(sp)"); 
  asm("lw   a4, 8(sp)"); 
  asm("lw   a5, 12(sp)");
  asm("addi sp, sp, 16");
  
  /* Store a0-a3 (x10-x13) into aop_core_ dump */
  asm("la   a0, aop_core_dump"); /* get a fresh pointer to the core dump  */
  asm("add  a0, a0, 32");            /* move past cookie, timestamp, and x5-x9 to where a0-a3 (x10-x13) should be stored */
  asm("sw a2, 0(a0)");
  asm("sw a3, 4(a0)");
  asm("sw a4, 8(a0)");
  asm("sw a5, 12(a0)"); 

  /* Grab the remaining registers (x1, x2, x3, x4, MCAUSE, MEPC, MSTATUS, MTVEC, MTVAL, MIP) */ 
  asm("la   a0, aop_core_dump"); /* get a fresh pointer to the core dump */
  asm("add  a0, a0, 120");           /* move past cookie and timestamp to where remaining registers should be stored */
  asm("sw x1, 0(a0)"); 
  asm("sw x2, 4(a0)"); 
  asm("sw x3, 8(a0)"); 
  asm("sw x4, 12(a0)"); 
  asm("csrr a2, mcause");
  asm("sw a2, 16(a0)"); 
  asm("csrr a2, mepc");
  asm("sw a2, 20(a0)"); 
  asm("csrr a2, mstatus");
  asm("sw a2, 24(a0)"); 
  asm("csrr a2, mtvec");
  asm("sw a2, 28(a0)"); 
  asm("csrr a2, mtval");
  asm("sw a2, 32(a0)"); 
  asm("csrr a2, mip");
  asm("sw a2, 36(a0)"); 
  asm("csrr a2, mscratch");
  asm("sw a2, 40(a0)"); 

  /* Add something useful to the log */ 
  asm("addi sp, sp, -8");
  asm("csrr a2, mcause");
  asm("sw a2, 0(sp)");
  asm("sw x1, 4(sp)");     /* push x1 so we can pop later and preserve the stack for the debugger. Need to push 8 bytes */

  asm("add x10, x1, x0");
  asm("csrr a1, mepc");

  asm("jal ra, err_fatal_sw_event");

  asm("jal ra, ddraux_log");

#if !defined(WILL_TRIGGER_DBG_PDC_ON_RAMDUMP)
  /*if both AOP and DBG PDC aren't used, assert GPO[31]*/
  asm("jal ra, force_gpo_bit");
#endif

#ifdef DDR_ABORT_REG_DUMP
  asm("jal ra, ddr_store_status_regs_error_fatal");
#endif

  asm("jal ra, notify_tz");

  asm("jal ra, reset_chip");

asm("hang:");
  asm("j hang");
}

