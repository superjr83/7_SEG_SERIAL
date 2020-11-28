#ifndef DISPLAY_H
#define DISPLAY_H

#define __DISP_CLOCK_PIN
#define __DISP_SDATA_PIN
#define __DISP_LATEN_PIN
#define __DISP_OUTEN_PIN

#define __DISP_PWM_FREQ 1000


#define __DISP_LEN  2



#ifdef __USE_PIC16_MCU
#else
    #include "driver/gpio.h"
    #include "driver/timer.h"
    #include "driver/ledc.h"
#endif





typedef struct{
    #ifdef __USE_PIC16_MCU
    #else 
        gpio_config_t displayIoConfig;
        ledc_channel_config_t displayLedConfig;
        ledc_timer_config_t displayTimerConfig;
    #endif
    int32_t displayCont;
    float   displayFloat;
    uint8_t displayLenght;
    uint8_t (*fnCallBack)(int32_t);
    uint8_t *displayString[];

}serial_display_t;

serial_display_t sDisplayGlobals = {
    .displayLenght = __DISP_LEN,
};

enum dispchars {
    number_0,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9,
    
    latter_A,
    latter_B,
    latter_C,
    latter_D,
    latter_E,
    latter_F,
    latter_G,
    latter_H,
    latter_I,
    latter_J,
    latter_K,
    latter_L,
    latter_M,
    latter_N,
    latter_O,
    latter_P,
    latter_Q,
    latter_R,
    latter_S,
    latter_T,
    latter_U,
    latter_V,
    latter_W,
    latter_X,
    latter_Y,
    latter_Z,
    
    underline,
    space,
    minus,
    degree,
    dot,
};


fnDisplayWrite(serial_display_t *sDisplay, uint8_t typeValue);   










#endif

