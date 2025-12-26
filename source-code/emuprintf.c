
#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdarg.h>
#include <stdio.h>

#include "emuprintf.h"


/* ==========  SERIAL OUTPUT BASICO  ========== */

void serial_putchar(char c) {
    SB_REG = (uint8_t)c;   // envia byte
    SC_REG = 0x81;         // reloj interno + start

    while (SC_REG & 0x80) {
        ;                  // espera a que termine
    }
}

/* opcional: CRLF bonito para BGB */
void serial_putchar_crlf(char c) {
    if(c == '\n')
        serial_putchar('\r');
    serial_putchar(c);
}


/* ==========  HELPERS TEXTO Y NÚMEROS  ========== */

void serial_puts(const char *s) {
    while(*s) serial_putchar_crlf(*s++);
}

void serial_put_uint(unsigned int v) {
    char buf[6];
    uint8_t i = 0;

    if(v == 0) { serial_putchar('0'); return; }

    while(v > 0) {
        buf[i++] = '0' + (v % 10);
        v /= 10;
    }
    while(i--) serial_putchar(buf[i]);
}

void serial_put_int(int v) {
    if(v < 0) {
        serial_putchar('-');
        v = -v;
    }
    serial_put_uint((unsigned int)v);
}

void serial_put_hex(uint8_t v) {
    static const char h[] = "0123456789ABCDEF";
    serial_putchar(h[v >> 4]);
    serial_putchar(h[v & 0x0F]);
}


/* ==========  MINI PRINTF PARA DEBUG  ========== */
/*  soporta: %s %u %d %x %X %c %%              */

void EMU_printf(const char *fmt, ...) {

    va_list ap;
    va_start(ap, fmt);

    while(*fmt) {

        if(*fmt == '%') {
            fmt++;

            switch(*fmt) {

                case 'c':
                    serial_putchar((char)va_arg(ap, int));
                    break;

                case 's':
                    serial_puts(va_arg(ap, char *));
                    break;

                case 'u':
                    serial_put_uint(va_arg(ap, unsigned int));
                    break;

                case 'd':
                    serial_put_int(va_arg(ap, int));
                    break;

                case 'x':
                case 'X':
                    serial_put_hex((uint8_t)va_arg(ap, int));
                    break;

                case '%':
                    serial_putchar('%');
                    break;

                default:
                    serial_putchar('?');
                    break;
            }
        }
        else {
            serial_putchar_crlf(*fmt);
        }

        fmt++;
    }

    va_end(ap);
}