/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     ReactOS AMD64 user mode callback helper
 * COPYRIGHT:   Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include <ksamd64.inc>

/*
 * NTSTATUS
 * KiUserModeCallout (
 *     _Inout_ PKCALLOUT_FRAME CalloutFrame);
 */
EXTERN KiUserModeCallout:PROC

.code64

/*
 * NTSTATUS
 * KiCallUserMode (
 *     _In_ PVOID *OutputBuffer@<rcx>,
 *     _In_ PULONG OutputLength@<rdx>);
 */
PUBLIC KiCallUserMode
.PROC KiCallUserMode

    /* Generate a KEXCEPTION_FRAME on the stack */
    /* This is identical to a KCALLOUT_FRAME */
    GENERATE_EXCEPTION_FRAME

    /* Save OutputBuffer and OutputLength */
    mov [rsp + ExOutputBuffer], rcx
    mov [rsp + ExOutputLength], rdx

    /* Call the C function */
    mov rcx, rsp
    call KiUserModeCallout

    /* Restore the registers from the KEXCEPTION_FRAME */
    RESTORE_EXCEPTION_STATE

    /* Return */
    ret

.ENDP

/*
 * DECLSPEC_NORETURN
 * VOID
 * KiCallbackReturn (
 *     _In_ PVOID Stack,
 *     _In_ NTSTATUS Status);
 */
PUBLIC KiCallbackReturn
.PROC KiCallbackReturn

    .ENDPROLOG

    /* Restore the stack */
    mov rsp, rcx

    /* Set return status */
    mov eax, edx

    /* Restore the registers from the KEXCEPTION_FRAME */
    RESTORE_EXCEPTION_STATE

    /* Return */
    ret

.ENDP

/*
 * VOID
 * NTAPI
 * KiSwitchStackAndCallout(
 *    _In_opt_ PVOID Parameter@<rcx>,
 *    _In_ PEXPAND_STACK_CALLOUT Callout@<rdx>,
 *    _In_ PVOID Stack@<r8>)
*/
PUBLIC KiSwitchStackAndCallout
.PROC KiSwitchStackAndCallout
    /* Save rbp */
    mov [rsp + 8], rbp
    .SAVEREG rbp, 8

    /* Save stack pointer in rbp for unwinding */
    mov rbp, rsp
    .SETFRAME rbp, 0

    .ENDPROLOG

    /* Save the current stack pointer on the new stack */
    mov [r8 - 8], rsp

    /* Switch to the new stack and reserve home space */
    lea rsp, [r8 - 48]

    /* Enable interrupts again */
    sti

    /* Call the callout */
    call rdx

    /* Disable interrupts */
    cli

    /* Restore the stack pointer */
    mov rsp, [rsp + 48 - 8]

    /* Return */
    mov rbp, [rsp + 8]
    ret

.ENDP

/*
 * ULONG_PTR KiGetStackPointer(VOID);
 */
PUBLIC KiGetStackPointer
KiGetStackPointer:

    /* Return the stack pointer */
    lea rax, [rsp + 8]
    ret


END
