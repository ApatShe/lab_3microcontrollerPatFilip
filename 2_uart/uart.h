#define UART ((NRF_UART_REG*)0x40002000)

void uart_init();
void uart_send(char letter);
char uart_read();

typedef struct {
    volatile uint32_t TASKS_STARTRX;    // 0x000
    volatile uint32_t TASKS_STOPRX;     // 0x004
    volatile uint32_t TASKS_STARTTX;    // 0x008
    volatile uint32_t TASKS_STOPTX;     // 0x00C
    volatile uint32_t RESERVED0[3];     // 0x010-0x01C (gap: 16 bytes)
    volatile uint32_t TASKS_SUSPEND;    // 0x01C
    volatile uint32_t RESERVED1[56];    // 0x020-0x100 (gap: 228 bytes)
    volatile uint32_t EVENTS_CTS;       // 0x100
    volatile uint32_t EVENTS_NCTS;      // 0x104
    volatile uint32_t EVENTS_RXDRDY;    // 0x108
    volatile uint32_t RESERVED2[4];     // 0x10C-0x11C (gap: 20 bytes)
    volatile uint32_t EVENTS_TXDRDY;    // 0x11C
    volatile uint32_t RESERVED3[1];     // 0x120-0x124 (gap: 8 bytes)
    volatile uint32_t EVENTS_ERROR;     // 0x124
    volatile uint32_t RESERVED4[7];     // 0x128-0x144 (gap: 32 bytes)
    volatile uint32_t EVENTS_RXTO;      // 0x144
    volatile uint32_t RESERVED5[46];    // 0x148-0x200 (gap: 188 bytes)
    volatile uint32_t SHORTS;           // 0x200
    volatile uint32_t RESERVED6[64];    // 0x204-0x304 (gap: 260 bytes)
    volatile uint32_t INTENSET;         // 0x304
    volatile uint32_t INTENCER;         // 0x308
    volatile uint32_t RESERVED7[93];    // 0x30C-0x480 (gap: 376 bytes)
    volatile uint32_t ERRORSRC;         // 0x480
    volatile uint32_t RESERVED8[31];    // 0x484-0x500 (gap: 128 bytes)
    volatile uint32_t ENABLE;           // 0x500
    volatile uint32_t RESERVED9[1];     // 0x504-0x508 (gap: 8 bytes)
    volatile uint32_t PSELRTS;          // 0x508
    volatile uint32_t PSELTXD;          // 0x50C
    volatile uint32_t PSELCTS;          // 0x510
    volatile uint32_t PSELRXD;          // 0x514
    volatile uint32_t RXD;              // 0x518
    volatile uint32_t TXD;              // 0x51C
    volatile uint32_t RESERVED10[1];    // 0x520-0x524 (gap: 8 bytes)
    volatile uint32_t BAUDRATE;         // 0x524
    volatile uint32_t RESERVED11[17];   // 0x528-0x56C (gap: 72 bytes)
    volatile uint32_t CONFIG;           // 0x56C

} NRF_UART_REG;
