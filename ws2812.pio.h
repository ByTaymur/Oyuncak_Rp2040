.program ws2812
.side_set 1

define public WS2812_T1  4
define public WS2812_T0  1
define public WS2812_RESET 48

.wrap_target
bitloop:
    out x, 1 side 1 [WS2812_T1 - 1]
    jmp !x do_zero side 0 [WS2812_T0 - 1]
do_zero:
    nop side 0 [WS2812_T1 - 1]
.wrap

% c-sdk {
    #include "hardware/pio.h"
    void ws2812_program_init(PIO pio, uint sm, uint offset, uint pin, uint freq, bool rgbw);
%}

% c
void ws2812_program_init(PIO pio, uint sm, uint offset, uint pin, uint freq, bool rgbw) {
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    pio_sm_config c = ws2812_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, false, true, 24);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, (float)clock_get_hz(clk_sys) / (freq * (rgbw ? 32 : 24)));
    pio_sm_set_enabled(pio, sm, true);
}