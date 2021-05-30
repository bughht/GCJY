#include  "key.h"
#include  "fft.h"
#include  "tftDisp.h"
#include  "led.h"


void  IO_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    KEY_GPIO_CLK_ENABLE();
    
    // LED1�����ų�ʼ��
    GPIO_InitStruct.Pin  = IO1_pin | IO2_pin | IO3_pin | IO4_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOx_IO_PORT, &GPIO_InitStruct);
    HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO2_pin);

}

/************************************************************************
// �� �� ��:      void  Key_Init(void)
// ������������:  ������������˿ڼ����ŵĳ�ʼ��                
// ��������:      ��
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ���򰴼���·��--Ӳ���ӿڲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2014-12-14
// �� �� �ˣ�                                                                         
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Key_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    KEY_GPIO_CLK_ENABLE();
    
    // LED1�����ų�ʼ��
    GPIO_InitStruct.Pin  = KEY1_PIN | KEY2_PIN | KEY3_PIN | KEY4_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOx_KEY_PORT, &GPIO_InitStruct);

}

/************************************************************************
// �� �� ��:      Init_KeyStatus(struKeyStatus *key)
// ������������:  ��ʼ��������״̬               
// ��������:      struKeysStatus  *key:  
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ��̬����:      key1_last,key2_last,key3_last,key4_last: 
// ����״̬��     ��ɲ���
// ������Σ�     ���򰴼���·��--����������

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Init_KeyStatus(struKeyStatus *key4)  
{ 
    key4->key1 = KEY_NO_PRESSED;
    key4->key2 = KEY_NO_PRESSED;
    key4->key3 = KEY_NO_PRESSED;
    key4->key4 = KEY_NO_PRESSED;
}

/************************************************************************
// �� �� ��:      void  Read_KeyStatus(struKeysStatus  *keynow)
// ������������:  ��ȡ������ǰ��״̬                
// ��������:      struKeysStatus  *keynow:  ����4��������ǰ��״̬ 
//                ������һ��4��������״̬��ͨ�������ڵİ���״̬�Ƚϣ���õ�ǰ����������״̬�ͼ���ֵ
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ���򰴼���·��--Ӳ���ӿڲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_KeyStatus(struKeyStatus  *keynow)
{
    KeyStatus  key_last;
    
    /////////////////////////////////////////////////////////////
    // ���KEY1��״̬
    key_last = keynow->key1;     // �����ϴε�KEY1��״̬
    if( !READ_KEY1() )            // KEY1�ĵ�ƽ����Ϊ0, ����Ϊ1;
    {                             // KEY1��ǰ�ĵ�ƽΪ����
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key1 = KEY_ALREADY_PRESSED; 
        }
        else
        {
            keynow->key1 = KEY_JUST_PRESSED; 
        }
    }
    else                     // KEY1��ǰ�ĵ�ƽΪ����
    {
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key1 = KEY_JUST_POPUP;    
        }
        else
        {
            keynow->key1 = KEY_NO_PRESSED;
        }
    }
    /////////////////////////////////////////////////////////////
    // ���KEY2��״̬
    key_last = keynow->key2;      // �����ϴε�KEY1��״̬
    if( !READ_KEY2() )            // KEY2�ĵ�ƽ����Ϊ0, ����Ϊ1;
    {                             // KEY2��ǰ�ĵ�ƽΪ����
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key2 = KEY_ALREADY_PRESSED; 
        }
        else
        {
            keynow->key2 = KEY_JUST_PRESSED; 
        }
    }
    else                          // KEY2��ǰ�ĵ�ƽΪ����
    {
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key2 = KEY_JUST_POPUP;    
        }
        else
        {
            keynow->key2 = KEY_NO_PRESSED;
        }
    }    
    /////////////////////////////////////////////////////////////
    // ���KEY3��״̬
    key_last = keynow->key3;      // �����ϴε�KEY3��״̬
    if( !READ_KEY3() )            // KEY3�ĵ�ƽ����Ϊ0, ����Ϊ1;
    {                             // KEY3��ǰ�ĵ�ƽΪ����
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key3 = KEY_ALREADY_PRESSED; 
        }
        else
        {
            keynow->key3 = KEY_JUST_PRESSED; 
        }
    }
    else                          // KEY3��ǰ�ĵ�ƽΪ����
    {
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key3 = KEY_JUST_POPUP;    
        }
        else
        {
            keynow->key3 = KEY_NO_PRESSED;
        }
    }
    /////////////////////////////////////////////////////////////
    // ���KEY4��״̬
    key_last = keynow->key4;      // �����ϴε�KEY4��״̬
    if( !READ_KEY4() )            // KEY4�ĵ�ƽ����Ϊ0, ����Ϊ1;
    {                             // KEY4��ǰ�ĵ�ƽΪ����
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key4 = KEY_ALREADY_PRESSED; 
        }
        else
        {
            keynow->key4 = KEY_JUST_PRESSED; 
        }
    }
    else                          // KEY4��ǰ�ĵ�ƽΪ����
    {
        if( (key_last == KEY_JUST_PRESSED) || (key_last == KEY_ALREADY_PRESSED) ) 
        {
            keynow->key4 = KEY_JUST_POPUP;    
        }
        else
        {
            keynow->key4 = KEY_NO_PRESSED;
        }
    }    
}

/************************************************************************
// �� �� ��:      void  Key_Process(struKeyStatus *key)
// ������������:  �����Ĵ���                
// ��������:      struKeysStatus  *key:  4��������ǰ��״̬
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ��̬����:      ��
// ����״̬��     ��ɲ���
// ������Σ�     Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
************************************************************************/
void  Key_Process(struKeyStatus key, uint16_t *x_freq, FunctionalState *Dispx_en)
{
    if(key.key1 == KEY_JUST_PRESSED)  // ����1 �հ���ʱ�Ķ��� 
    { 
        HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO1_pin);
        LED1_TOGGLE();
    } 
    
    if(key.key2 == KEY_JUST_PRESSED)  // ����2 �հ���ʱ�Ķ��� 
    { 
        HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO2_pin);
        LED2_TOGGLE();
    } 
    
    if(key.key3 == KEY_JUST_PRESSED)  // ����3 �հ���ʱ�Ķ��� 
    { 
        HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO3_pin);
        LED3_TOGGLE();
        /*
        if((*x_freq) < 50)
        {
            *x_freq = FFT_LENGTH / 2 - FFT_SUBWIN_SPECTRUM_MAX;
        }
        else
        {
            (*x_freq) = (*x_freq) - 50;
        }
        *Dispx_en = ENABLE
        */
    } 
    
    if(key.key4 == KEY_JUST_PRESSED)  // ����4 �հ���ʱ�Ķ��� 
    { 
        HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO4_pin);
        LED4_TOGGLE();
        /*
        HAL_GPIO_TogglePin(GPIOx_IO_PORT, IO1_pin);
        (*x_freq) = (*x_freq) + 50;
        if((*x_freq) > (FFT_LENGTH / 2 - FFT_SUBWIN_SPECTRUM_MAX ))
        {
            *x_freq = 0;
        }
        *Dispx_en = ENABLE;
        */
    } 
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

