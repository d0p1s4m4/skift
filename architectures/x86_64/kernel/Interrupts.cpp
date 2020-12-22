#include <libsystem/Logger.h>

#include "kernel/interrupts/Dispatcher.h"
#include "kernel/interrupts/Interupts.h"
#include "kernel/scheduling/Scheduler.h"
#include "kernel/system/System.h"

#include "architectures/x86/kernel/PIC.h"
#include "architectures/x86_64/kernel/Interrupts.h"

static const char *_exception_messages[32] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

extern "C" uint64_t interrupts_handler(uintptr_t rsp)
{
    InterruptStackFrame *stackframe = reinterpret_cast<InterruptStackFrame *>(rsp);

    if (stackframe->intno < 32)
    {
        system_panic_with_context(
            stackframe,
            "CPU EXCEPTION: '%s' (INT:%d ERR:%x) !",
            _exception_messages[stackframe->intno],
            stackframe->intno,
            stackframe->err);
    }
    else if (stackframe->intno < 48)
    {
        interrupts_disable_holding();

        int irq = stackframe->intno - 32;

        if (irq == 0)
        {
            system_tick();
            rsp = schedule(rsp);
        }
        else
        {
            dispatcher_dispatch(irq);
        }

        interrupts_enable_holding();
    }
    else if (stackframe->intno == 127)
    {
        interrupts_disable_holding();

        rsp = schedule(rsp);

        interrupts_enable_holding();
    }

    pic_ack(stackframe->intno);

    return rsp;
}
