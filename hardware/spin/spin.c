#include "spin.h"
#include "fft.h"
#include "tftDisp.h"
// ��ת���������ŵĳ�ʼ��
void  Spin_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    SPIN_GPIO_CLK_ENABLE();
    // �Ҳ����ת���������ų�ʼ��
    GPIO_InitStruct.Pin  = SPIN_KEY_PIN | SPIN_A_PIN | SPIN_B_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIO_SPIN_PORT, &GPIO_InitStruct);
}

// ��ʼ��������ת��������״̬
void  Init_Spin_Status(struspin *spin)
{
    spin->rotatestatus  = SPIN_NO_ROTATE;
    spin->keystatus     = KEY_NO_PRESSED;
}

////////////////////////////////////////////////////////////
// ��ȡ 2 ��ת��������״̬
static  LEVEL  last_spinkey_level= H;           // �������һ�ΰ����ĵ�ƽ���
static  SpinABstatus last_spinABst=SPIN_AB_ST3; // �������һ��AB���ŵĵ�ƽ���
void  Read_Spin(struspin *spin)
{
    LEVEL           now_spinkey_level;
    LEVEL           now_spinA_level;
    LEVEL           now_spinB_level;
    SpinABstatus    now_spinABst;
    
    // �ȶ�ȡ��ת�������ĸ����ŵĵ�ƽֵ
    if( READ_SPIN_KEY() ) { now_spinkey_level = H; }  // ��ȡ��ת�������İ�����ƽֵ
    else                  { now_spinkey_level = L; }
    
    if( READ_SPIN_A()   ) { now_spinA_level   = H; }  // ��ȡ��ת�������� A �źŵ�ƽֵ
    else                  { now_spinA_level   = L; }
    
    if( READ_SPIN_B()   ) { now_spinB_level   = H; }  // ��ȡ��ת�������� B �źŵ�ƽֵ
    else                  { now_spinB_level   = L; }
    
    // ���� ��ת�������İ��� ǰ�� ���εĵ�ƽֵ, ȷ������״̬
    if(     (last_spinkey_level == H)  && (now_spinkey_level == L) )  { spin->keystatus  = KEY_JUST_PRESSED;    } 
    else if((last_spinkey_level == H)  && (now_spinkey_level == H) )  { spin->keystatus  = KEY_NO_PRESSED;      } 
    else if((last_spinkey_level == L)  && (now_spinkey_level == H) )  { spin->keystatus  = KEY_JUST_POPUP;      } 
    else                                                              { spin->keystatus  = KEY_ALREADY_PRESSED; } 

    //  ���� �����ת�������� A B �ĵ�ƽֵ, ȷ�� AB ״̬
    if(     (now_spinA_level == H)  && (now_spinB_level == H) )  { now_spinABst  = SPIN_AB_ST3; }  // A=1 B=1; 
    else if((now_spinA_level == H)  && (now_spinB_level == L) )  { now_spinABst  = SPIN_AB_ST2; }  // A=1 B=0;
    else if((now_spinA_level == L)  && (now_spinB_level == L) )  { now_spinABst  = SPIN_AB_ST0; }  // A=0 B=0;
    else                                                         { now_spinABst  = SPIN_AB_ST1; }  // A=0 B=1;
   
    // �ٸ��� �����ת������ ǰ������ AB�ź��ߵ�״̬, ȷ����������������
    if(      (last_spinABst == SPIN_AB_ST3) && (now_spinABst == SPIN_AB_ST2)){ spin->rotatestatus = SPIN_CLOCKWISE;     }
    else if ((last_spinABst == SPIN_AB_ST3) && (now_spinABst == SPIN_AB_ST1)){ spin->rotatestatus = SPIN_UNTICLOCKWISE; }
    else                                                                     { spin->rotatestatus = SPIN_NO_ROTATE;     }
  
    last_spinkey_level  = now_spinkey_level;  // ���浱ǰ״̬����Ϊ�´�״̬������
    last_spinABst       = now_spinABst;
}

void  Proc_Spin(struspin spin, uint16_t *x_freq, FunctionalState *Dispx_en)
{
    if(spin.rotatestatus == SPIN_CLOCKWISE)
    {
        if((*x_freq) >= (FFT_LENGTH / 2 - FFT_SUBWIN_SPECTRUM_MAX / 2 ))
        {
            *x_freq = 0;
        }
        else
        {
            (*x_freq)++;
        }
        *Dispx_en = ENABLE;
    }
    else  if(spin.rotatestatus == SPIN_UNTICLOCKWISE)
    {
        if((*x_freq) == 0)
        {
            *x_freq = FFT_LENGTH / 2 - FFT_SUBWIN_SPECTRUM_MAX / 2;
        }
        else
        {
            (*x_freq)--;
        }
        *Dispx_en = ENABLE;
    }
}

