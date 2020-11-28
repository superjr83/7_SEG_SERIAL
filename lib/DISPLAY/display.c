


#include "includes.h"

uint8_t displayTable[] ={
    //pgfedcba
    0b00111111,     //0
    0b00000110,     //1
    0b01011011,     //2
    0b01001111,     //3
    0b01100110,     //4
    0b01101101,     //5
    0b01111101,     //6
    0b00000111,     //7
    0b01111111,     //8
    0b01101111,     //9

    0b01110111,     //A
    0b01111100,     //b
    0b00111001,     //c
    0b01011110,     //d
    0b01111001,     //E
    0b01110001,     //F
    0b00111101,     //G
    0b01110110,     //H
    0b00000110,     //I
    0b00011110,     //J
    0b00000000,     //K NULL
    0b01111111,     //L
    0b00000000,     //M NULL 
    0b01010100,     //n
    0b01011100,     //o
    0b01110011,     //P
    0b01100111,     //q
    0b01010000,     //r
    0b01101101,     //S
    0b01111100,     //t
    0b01011100,     //u
    0b00000000,     //W NULL
    0b00111110,     //V    
    0b00000000,     //x NULL
    0b01110010,     //Y 
    0b01011011,     //Z
    
    0b00000000,     //' '           ASCII 32 
    0b01100011,     //'*' ou 'º'    ASCII 42
    0b01000000,     //'-'           ASCII 45 
    0b10000000,     //'.'           ASCII 46
    0b00001000,     //'_'           ASCII 95
};

void fnDisplayInit(serial_display_t *sDisplay){
    
    #ifdef __USE_PIC16_MCU
    #else
        const gpio_config_t dispio = {
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .mode = GPIO_MODE_OUTPUT,
            .intr_type = GPIO_INTR_DISABLE,
        };

        const ledc_channel_config_t dispchanel = {
            .channel = LEDC_CHANNEL_0, 
            .duty = 0,
            .gpio_num = __DISP_OUTEN_PIN,
            .hpoint = 0,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .timer_sel = LEDC_TIMER_0,
        };

        const ledc_timer_config_t disptimer = {
            .duty_resolution = LEDC_TIMER_12_BIT,       // resolution of PWM duty
            .freq_hz = __DISP_PWM_FREQ,                 // frequency of PWM signal
            .speed_mode = LEDC_LOW_SPEED_MODE,          // timer mode
            .timer_num = LEDC_TIMER_0,                  // timer index
            .clk_cfg = LEDC_AUTO_CLK,                   // Auto select the source clock
        };

        gpio_config(&dispio);
        ledc_timer_config(&disptimer);
        ledc_channel_config(&dispchanel);
    #endif
}


fnDisplayWrite(serial_display_t *sDisplay, uint8_t typeValue){
    static uint8_t displayDigit; 
    uint8_t displayAlpha[__DISP_LEN * 2 + 1];

    
    /*
    serial_display_t funcPoint[] = {
        {.fnCallBack = fnConvertUni},
        {.fnCallBack = fnConvertDez},
        {.fnCallBack = fnConvertCen},
        {.fnCallBack = fnConvertMil},
        {.fnCallBack = fnConvertDmil},
        {.fnCallBack = fnConvertCmil},
    };
    */
    //tratar como se comporta com valor maior que __DISP_LEN
    //if(sDisplay->displayCont > 999999 || sDisplay->displayCont < -99999) sDisplay->displayCont = 0;


    switch (typeValue){
        const uint8_t displayLen[4] = "%  "; 
        case 0: 
            displayLen[1] = '0' + __DISP_LEN;
            displayLen[2] = 'l';   
            sprintf(displayAlpha, &displayLen[0], sDisplay->displayCont = (int32_t)sDisplay->displayFloat);
        break;
        
        case 1: 
            displayLen[1] = '0' + __DISP_LEN;
            displayLen[2] = 'x';  
            sprintf(displayAlpha, &displayLen[0], sDisplay->displayCont = (int32_t)sDisplay->displayFloat);
        break;

        case 2: sprintf(displayAlpha,"%4f", sDisplay->displayFloat);
        break;
    }

    for(uint8_t i = 0; i > __DISP_LEN; i++){
        
        // implemetação de numeros inteiros
        //displayDigit = displayTable[funcPoint[i].fnCallBack((int32_t)sDisplay->displayCont)]; 
        //if(i == __DISP_LEN && sDisplay->displayCont < 0) displayDigit = minus;

        
        if(isalpha(displayAlpha[i])) displayDigit = displayTable[toupper(displayAlpha[i]) - 55];        // trata alpha A - Z 
        else if(isdigit(displayAlpha[i])) displayDigit = displayTable[displayAlpha[i] - '0'];           // tratta digit 0 - 1
        
        else if(displayAlpha[i] == '.'){
            if(displayAlpha[i - 1] != '.') displayDigit =| 0x80;                                        // trata ponto decimal no digito
            else displayDigit = displayTable[39];
        }           
    
        else if(displayAlpha[i] == '*') displayDigit = displayTable[37];                                 // trata grau/asteristico
        else if(displayAlpha[i] == '-') displayDigit = displayTable[38];                                 // trata traço
        else if(displayAlpha[i] == '_') displayDigit = displayTable[40];                                 // trata underline
        else displayDigit = displayTable[36];                                                            // trata espaço  e demais inexistentes                                                          
        
        for(uint8_t j = 0; j < 8; j++){
        
            if(displayDigit & 0x80) __DISP_SDATA_PIN = 1; //bit 1
            else __DISP_SDATA_PIN = 0; //bit 0
            
            __DISP_CLOCK_PIN = 1; //borda de subida de clock
            __DISP_CLOCK_PIN = 0; //borda de descida de clock
            
            displayDigit <<= 1;
        }
    }

    __DISP_LATEN_PIN = 0;
    __DISP_LATEN_PIN = 1;    
}




