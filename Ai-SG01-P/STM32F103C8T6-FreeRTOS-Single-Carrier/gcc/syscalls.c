/*
 * gcc/syscalls.c - minimal newlib syscall layer for the GNU (arm-none-eabi)
 * build of STM32F103C8T6-FREERTOS-AISG01.
 *
 * Why this file exists
 * --------------------
 * Under armcc/AC5, printf() was retargeted via fputc() in BSP/src/bsp_uart.c.
 * Under GCC + newlib, printf() ends in _write_r() -> _write(), NOT fputc().
 * Without _write() here, linking -lnosys pulls in a stub that always fails
 * ("_write is not implemented and will always fail") and EVERY printf in the
 * AT command firmware is silently discarded -- no serial output at all.
 *
 * This file provides the real syscalls, so:
 *   - printf() output goes out on USART1 via the existing fputc(),
 *   - the six "not implemented and will always fail" linker warnings go away,
 *   - -lnosys can be dropped from the link line (its _write is a strong symbol
 *     and would otherwise clash with ours).
 *
 * This is a bare-metal target: no filesystem, no processes, no dynamic loader.
 * Only _write needs to do real work; the rest are small, well-defined stubs.
 */
#include <stddef.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

/* Symbols supplied by gcc/stm32f103c8.ld. Declared as arrays so pointer
 * arithmetic on them does not trip -Warray-bounds (they are linker symbols,
 * not real C objects). */
extern char end[];
extern char _estack[];

/* crti/crtn equivalents.
 *
 * The GNU startup calls __libc_init_array(), which calls _init()/_fini() and
 * walks .init_array/.fini_array. A bare-metal build with -nostdlib has no
 * crti.o/crtn.o, so provide real (Thumb) no-op functions here. Defining them
 * as linker-script address constants instead would leave the symbols untyped
 * and produce "Unknown destination type (ARM/Thumb)" / "dangerous relocation"
 * from ld. This matches the working official Ai-SG01_ATCommandFirmware. */
void _init(void)
{
}

void _fini(void)
{
}

/* printf() is NOT wired here. newlib-nano resolves printf -> _write_r ->
 * _write(), and _write() is implemented in BSP/src/bsp_uart.c right next to
 * the USART1 driver (same layout as the official firmware). Keeping _write
 * out of this file also avoids clashing with libnosys.a's strong _write. */

/* ------------------------------------------------------------------ */
/* The other reentrant syscalls newlib-nano references                   */
/* ------------------------------------------------------------------ */
int _read(int fd, void *buf, size_t len)
{
    (void)fd; (void)buf; (void)len;
    return 0;           /* no stdin: report EOF */
}

int _close(int fd)
{
    (void)fd;
    return -1;
}

int _fstat(int fd, struct stat *st)
{
    (void)fd;
    if (st != NULL) {
        st->st_mode = S_IFCHR;   /* stdout/stdin are character devices */
    }
    return 0;
}

int _isatty(int fd)
{
    (void)fd;
    return 1;           /* line-buffered stdout, conventional for a console */
}

int _lseek(int fd, off_t offset, int whence)
{
    (void)fd; (void)offset; (void)whence;
    return 0;
}

int _getpid(void)
{
    return 1;
}

int _kill(int pid, int sig)
{
    (void)pid; (void)sig;
    errno = EINVAL;
    return -1;
}

void _exit(int status)
{
    (void)status;
    for (;;) { }        /* no OS to return to; halt for the debugger */
}

/* ------------------------------------------------------------------ */
/* Heap support for malloc()/free() (newlib may pull these in).         */
/* Heap grows up from `end`; leave _Min_Stack_Size (2 KB) for the stack. */
/* ------------------------------------------------------------------ */
void *_sbrk(ptrdiff_t incr)
{
    static char *heap_end;
    char *prev;
    uintptr_t stack_limit = (uintptr_t)_estack - 0x800u;

    if (heap_end == NULL) {
        heap_end = end;
    }
    prev = heap_end;

    if ((uintptr_t)heap_end + (uintptr_t)incr > stack_limit) {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_end += incr;
    return (void *)prev;
}
