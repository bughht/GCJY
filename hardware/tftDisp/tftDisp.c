/*************************************************
// �ļ�˵��:      ���ļ�Ϊ����û�����ĺ�����
//                �������ڵײ������ļ��ͻ�����ʾ����֮�ϣ��û�����������Ӧ����ʾ����
//                ��Ϊ������ļ�������û�����ģ���������к�ǿ����ֲ��
// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/

/* --------------------------Includes ---------------------------------------------*/
#include "tftDisp.h"

/* ----------------------End of Includes ---------------------------------------------*/
uint16_t Last_Spectrum[FFT_MAINWIN_SPECT_TOTAL_DISP];

static uint8_t x_last = 0, y_last = 0;
void tftDisp_Test_Val(uint16_t val_x, uint16_t val_y)
{
    if (val_x != x_last) // ����ֵ�仯��, ��ʾ, ��������ʾά��ԭ״̬
    {
        GUI_A_usigned_Decimal(VALUE_X_X1, VALUE_X_Y0, VAL_X_FORCOLOR, VAL_X_BKCOLOR, val_x, 5, DOT24X24aWORD);
        x_last = val_x;
    }

    if (val_y != y_last) // ����ֵ�仯��, ��ʾ, ��������ʾά��ԭ״̬
    {
        GUI_A_usigned_Decimal(VALUE_Y_X1, VALUE_X_Y0, VAL_X_FORCOLOR, VAL_X_BKCOLOR, val_y, 5, DOT24X24aWORD);
        y_last = val_y;
    }
}
/************************************************************************
// �� �� ��:      tftDisp_Touch_XY(struCTPxy *cptxy, struCTPxy *lastxy)
// ������������:  ��ʾXY������ֵ
// ��������:      x,y ����;  forcolor:ǰ��; bkcolor:����; char *string:��ʾ���ַ���   
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     �����û���--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
************************************************************************/
static struTouch cptxylast = {
    0,
    0,
    NO_TOUCH,
    X_NO_MOVING,
    Y_NO_MOVING,
};
void tftDisp_Touch_XY(struTouch *cptxynow)
{
    if (cptxynow->ctpxy.ctp_x != cptxylast.ctpxy.ctp_x) // ����ֵ�仯��, ��ʾ, ��������ʾά��ԭ״̬
    {
        if (cptxynow->ctpxy.ctp_x == 0x0fff) // û�д�����
        {
            Gui_Draw_Asc24_Hzk24(X_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, (uint8_t *)"-----");
        }
        else
        {
            GUI_A_usigned_Decimal(X_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, cptxynow->ctpxy.ctp_x, 5, DOT24X24aWORD);
        }
    }

    if (cptxynow->ctpxy.ctp_y != cptxylast.ctpxy.ctp_y) // ����ֵ�仯��, ��ʾ, ��������ʾά��ԭ״̬
    {
        if (cptxynow->ctpxy.ctp_y == 0x0fff) // û�д�����
        {
            Gui_Draw_Asc24_Hzk24(Y_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, (uint8_t *)"-----");
        }
        else
        {
            GUI_A_usigned_Decimal(Y_TOUCHX, X_Y0, TOUCH_DIG_FORCOLOR, TOUCH_DIG_BKCOLOR, cptxynow->ctpxy.ctp_y, 5, DOT24X24aWORD);
        }
    }

    cptxylast.ctpxy.ctp_x = cptxynow->ctpxy.ctp_x;
    cptxylast.ctpxy.ctp_y = cptxynow->ctpxy.ctp_y;
}

////////////////////////////
const uint8_t Arrow[8] = {
    0x10,
    0x10,
    0x10,
    0x38,
    0x38,
    0x7c,
    0x7c,
    0xfe,
};
void Gui_Draw_A_Arrow(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor)
{ // xΪ��ͷ�����ĵ�
    uint16_t i, j, xst;
    uint8_t tmp;

    if (x > 3)
    {
        xst = x - 3;
        Lcd_Set_Region(xst, y, (xst + 7), (y + 7));
        for (i = 0; i < 8; i++) // 8��
        {
            tmp = Arrow[i];
            for (j = 0; j < 8; j++) // 7��
            {
                if (tmp & 0x80)
                {
                    *(__IO uint16_t *)(Bank1_LCD_D) = forcolor;
                }
                else
                {
                    *(__IO uint16_t *)(Bank1_LCD_D) = bkcolor;
                }
                tmp <<= 1;
            }
        }
        Lcd_Set_Region(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
    }
}
////////////////////////////
// �������� ����Ƶ�׾��ο� ������
void Draw_MainWin_Block_Words(void)
{
    uint16_t i, x, yaxis;
    char str[30], str1[10];

    Gui_Draw_Rect(FFT_MAINWIN_X0_1, FFT_MAINWIN_Y0_1, FFT_MAINWIN_X1_1, FFT_MAINWIN_Y1_1, FFT_MAINSUBWIN_COLOR); // ����Ƶ�������ο�
    Gui_Draw_Rect(FFT_MAINWIN_X0_2, FFT_MAINWIN_Y0_2, FFT_MAINWIN_X1_2, FFT_MAINWIN_Y1_2, FFT_MAINSUBWIN_COLOR); // ����Ƶ�������ο�

    x = FFT_MAINWIN_WORD_DB_X;
    for (i = 1; i < 8; i++)
    {
        yaxis = FFT_MAINWIN_Y0 - 40 * i - 8;
        GUI_A_usigned_Decimal(x, yaxis, WHITE_4_4, BLUE_4_4, (i * 20), 20, DOT16X16aWORD); // ����20dB����Ķ�����
    }
    yaxis = FFT_MAINWIN_Y0 - 40 * 8 + 8;
    Gui_Draw_Asc16_Hzk16(x + 4, yaxis, WHITE_4_4, BLUE_4_4, (uint8_t *)"dB"); // д����"dB"

    // д��λ(Hz)
    memset(str, 0, 30);
    strcpy(str, "��λ(");
    sprintf(str1, "%d", FFT_MAINWIN_X_SPECTRUM_INTERNAL);
    strcat(str, str1);
    strcat(str, "Hz)");
    Gui_Draw_Asc16_Hzk16((FFT_MAINWIN_X1_2 - 100), FFT_MAINWIN_Y0_WORD_UNIT, WHITE_4_4, BLUE_4_4, (uint8_t *)str);
}

// ���Ӵ��� ��ϸƵ�� ���ο� �� д"HZ"
void Draw_SubWin_Block(void)
{
    Gui_Draw_Rect(FFT_SUBWIN_X0_1, FFT_SUBWIN_Y0_1, FFT_SUBWIN_X1_1, FFT_SUBWIN_Y1_1, FFT_MAINSUBWIN_COLOR); // ��ϸƵ�������ο�
    Gui_Draw_Rect(FFT_SUBWIN_X0_2, FFT_SUBWIN_Y0_2, FFT_SUBWIN_X1_2, FFT_SUBWIN_Y1_2, FFT_MAINSUBWIN_COLOR); // ��ϸƵ�������ο�
    Gui_Draw_Asc16_Hzk16((FFT_SUBWIN_X1_2 - 16), FFT_MAINWIN_Y0_WORD_UNIT, FFT_MAINSUBWIN_COLOR, BLUE_4_4, (uint8_t *)"Hz");
}

// ������ʼ������
void Init_Last_Spectrum(uint16_t *lastvalue)
{
    uint16_t i;
    for (i = 0; i < FFT_MAINWIN_SPECT_TOTAL_DISP; i++)
    {
        lastvalue[i] = FFT_MAINWIN_Y0;
    }
}

// ��20 �� 40��dB������ ,�������ڶ���
void Draw_xdB_Line(void)
{
    uint16_t i, x0, y, x1;

    x0 = FFT_MAINWIN_X0;
    x1 = FFT_SUBWIN_X1_1;
    for (i = 1; i < NUMBERofDBLINES; i++)
    {
        y = FFT_MAINWIN_Y0 - DOTS_20dB * i;
        Gui_Draw_Line(x0, y, x1, y, WHITE_1_4);
    }
}

// ��Ƶ��ֵ�����ߣ����ڶ����Ƶ�� ����
void Draw_MainWin_Spectrum_Flag_Line(void)
{
    float freq, ftmp;
    uint16_t i, fx, y0, y1;

    y0 = FFT_MAINWIN_Y0 + 10;
    y1 = FFT_MAINWIN_Y0 - MAINWIN_HEIGH;

    fx = FFT_MAINWIN_X0;                      // 0Hz ����
    Gui_Draw_Line(fx, y0, fx, y1, WHITE_1_4); // �м���Գ�Ƶ�ʵ�

    // ��Ƶ�ʵ㶨�꣬��������
    for (i = 1; i < 10000; i++)
    {
        freq = (float)(i * FFT_MAINWIN_X_SPECTRUM_INTERNAL); // �����Ƶ��ֵ
        if (freq < ((float)SAMPLE_FREQ / 2))
        {
            ftmp = freq * ((float)FFT_LENGTH / SAMPLE_FREQ) / FFT_MAINWIN_SPECT_SUM_NUMB + 1; // ÿHZ��Ӧ2��
            fx = (uint16_t)ftmp;                                                              // �����ڵڼ���������
            Gui_Draw_Line((fx + FFT_MAINWIN_X0), y0, (fx + FFT_MAINWIN_X0), y1, WHITE_2_4);   // �м���Գ�Ƶ�ʵ�
        }
        else
        {
            break;
        }
    }
    fx = ((FFT_LENGTH - 1) / FFT_MAINWIN_SPECT_SUM_NUMB - 1) / 2 + 1 + FFT_MAINWIN_X0; // �м���Գ�Ƶ�ʵ��X����
    Gui_Draw_Line(fx, y0, fx, y1, GREEN_3_4);                                          // �м���Գ�Ƶ�ʵ�
}

// ��Ƶ��ֵ�����ߣ����ڶ����Ƶ����ֵ
void Draw_MainWin_Spectrum_Flag_Word(void)
{
    float freq, ftmp;
    uint16_t i, fx, y0;

    y0 = FFT_MAINWIN_Y_FREQ_WORDS;
    fx = FFT_MAINWIN_X0;                                                   // 0Hz ����
    Gui_Draw_Asc16_Hzk16(fx - 4, y0, WHITE_4_4, BLUE_4_4, (uint8_t *)"0"); // д0

    // ��Ƶ�ʵ㶨�꣬��������
    for (i = 1; i < 10000; i++)
    {
        freq = (float)(i * FFT_MAINWIN_X_SPECTRUM_INTERNAL); // �����Ƶ��ֵ
        if (freq < ((float)SAMPLE_FREQ / 2))
        {
            ftmp = freq * ((float)FFT_LENGTH / SAMPLE_FREQ) / FFT_MAINWIN_SPECT_SUM_NUMB + 1;
            fx = (uint16_t)ftmp;                                                                                                                              // �����ڵڼ���������
            GUI_A_usigned_Decimal((fx + FFT_MAINWIN_X0 - 4), y0, WHITE_4_4, BLUE_4_4, (uint32_t)(freq / FFT_MAINWIN_X_SPECTRUM_INTERNAL), 20, DOT16X16aWORD); // ����Ƶ�ʼ���Ķ���ֵ
        }
        else
        {
            break;
        }
    }
}

void Inin_Win(void)
{
    Gui_Draw_Line(0, LINE_Y0, X_MAX_PIXEL - 1, LINE_Y0, WHITE_4_4);             // ��ʾ2���ָ����
    Gui_Draw_Line(0, (LINE_Y0 + 1), X_MAX_PIXEL - 1, (LINE_Y0 + 1), WHITE_4_4); //
    Draw_MainWin_Block_Words();                                                 // �������ڲ�д�̶�����
    Draw_MainWin_Spectrum_Flag_Word();                                          // дƵ�׶��������
    Draw_SubWin_Block();                                                        // ����ϸƵ�׵��Ӵ���
}
// ������������ߣ�ÿ7��ϳ�һ������
void Draw_MainWin_Spectrum(float *fftfreq, uint32_t fftlength)
{
    uint32_t i, j;
    float ftmp;
    uint16_t spectrum[FFT_MAINWIN_SPECT_TOTAL_DISP + 1]; // �ܹ���ʾ�������ж��ٸ�

    // ����ֱ��������ֵ
    if (fftfreq[0] > 0)
    {
        ftmp = log10(fftfreq[0]);
        spectrum[0] = (uint16_t)(ftmp * FFT_MAINWIN_dBVALUE_nDISP);
    }

    // ����������ÿ FFT_SPECT_SUM_NUMB �����߼���һ����ʾ
    for (i = 0; i < FFT_MAINWIN_SPECT_TOTAL_DISP; i++)
    {
        ftmp = 0;
        for (j = 0; j < FFT_MAINWIN_SPECT_SUM_NUMB; j++)
        {
            ftmp += fftfreq[i * FFT_MAINWIN_SPECT_SUM_NUMB + j + 1]; // FFT_SPECT_SUM_NUMB �����ߵĺ�
        }
        ftmp = log10(ftmp);                                             // �������
        spectrum[i + 1] = (uint16_t)(ftmp * FFT_MAINWIN_dBVALUE_nDISP); // ��������ʾ��Է�ֵ
    }

    // ������ֵת��Ϊ��ʾ�ľ�������
    for (i = 0; i <= FFT_MAINWIN_SPECT_TOTAL_DISP; i++)
    {
        spectrum[i] = FFT_MAINWIN_Y0 - spectrum[i];
    }

    // ���߻���Ƶ����
    for (i = 0; i <= FFT_MAINWIN_SPECT_TOTAL_DISP; i++)
    {
        if (spectrum[i] <= Last_Spectrum[i])
        {
            Gui_Draw_Line((FFT_MAINWIN_X0 + i), FFT_MAINWIN_Y0, (FFT_MAINWIN_X0 + i), spectrum[i], FFT_MAINWIN_SPECTRUM_COLOR);
        }
        else if (spectrum[i] > Last_Spectrum[i])
        {
            Gui_Draw_Line((FFT_MAINWIN_X0 + i), spectrum[i], (FFT_MAINWIN_X0 + i), Last_Spectrum[i], FFT_MAINWIN_SPECTRUM_lastCOLOR);
        }
        Last_Spectrum[i] = spectrum[i];
    }
}

// ��ʾָ��ĳ��Ƶ��ֵ�ļ�ͷ���������л�ɫ���ϵ�С��ͷ
static uint16_t last_xcenter = 0;
void DRAW_MainWin_Arrow_Freq(uint16_t xfreqleft)
{
    uint16_t tmp16;

    if (xfreqleft == 0)
    {
        tmp16 = 0;
    }
    else
    {
        tmp16 = (xfreqleft - 1) / FFT_MAINWIN_SPECT_SUM_NUMB + 1;
    }
    Gui_Draw_A_Arrow((last_xcenter + FFT_MAINWIN_X0), FFT_MAINWIN_Y_ARROW, FFT_MAINWIN_ARROW_BKCOLOR, FFT_MAINWIN_ARROW_BKCOLOR);
    Gui_Draw_A_Arrow((tmp16 + FFT_MAINWIN_X0), FFT_MAINWIN_Y_ARROW, FFT_MAINWIN_ARROW_FORCOLOR, FFT_MAINWIN_ARROW_BKCOLOR);
    last_xcenter = tmp16;
}

// ��ʾС�����δ��������Ƶ��ֵ �� �м��Ƶ��ֵ ���Ҳ�Ƶ��ֵ
void Write_SubWin_Left_Center_Freq(uint16_t xleft)
{
    float ftmp, xHZ_perDot;
    uint16_t x, y;

    // �Ӵ��ڵ�һ�����ߵ�Ƶ��ֵ
    xHZ_perDot = (float)SAMPLE_FREQ / FFT_LENGTH; // 0.5HZ/��

    ftmp = xleft * xHZ_perDot;
    x = FFT_SUBWIN_X0_1;
    y = FFT_MAINWIN_Y0_WORD_UNIT;
    Lcd_Clear_Some_Area(x, y, (x + 6 * ASC16_8PIXELperROW), (y + ASC16_nLINE), BLUE_1_4);
    GUI_aFloat(x, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4, ftmp, 1, DOT16X16aWORD);

    // �Ӵ����м����ߵ�Ƶ��ֵ
    ftmp = (xleft + (FFT_SUBWIN_SPECTRUM_MAX - 1) / 2) * xHZ_perDot;
    x = FFT_SUBWIN_X0_1 + FFT_SUBWIN_SPEC_INTERNAL * FFT_SUBWIN_SPECTRUM_MAX / 2 - 3 * 8;
    y = FFT_MAINWIN_Y0_WORD_UNIT;
    Lcd_Clear_Some_Area(x, y, (x + 6 * ASC16_8PIXELperROW), (y + ASC16_nLINE), BLUE_1_4);
    GUI_aFloat(x, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4, ftmp, 1, DOT16X16aWORD);

    // �Ӵ������ұߵ����ߵ�Ƶ��ֵ
    ftmp = xleft + (FFT_SUBWIN_SPECTRUM_MAX - 1);
    ftmp = ftmp * xHZ_perDot;
    x = FFT_SUBWIN_X1_1 - 70;
    y = FFT_MAINWIN_Y0_WORD_UNIT;
    Lcd_Clear_Some_Area(x, y, (x + 6 * ASC16_8PIXELperROW), (y + ASC16_nLINE), BLUE_1_4);
    GUI_aFloat(x, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4, ftmp, 1, DOT16X16aWORD);
}

////////////////////
// �����Ƶ��������ʾ9������ ��0.5HZ���
void Draw_SubWin_FFT_Spectrum(uint16_t x_left, float *fft_out)
{
    uint16_t i, spectrum[FFT_SUBWIN_SPECTRUM_MAX]; // �ܹ���ʾ�������ж��ٸ�;
    uint16_t forcolor, x, y;

    float ftmp;

    // ����������ÿ FFT_SPECT_SUM_NUMB �����߼���һ����ʾ
    for (i = 0; i < FFT_SUBWIN_SPECTRUM_MAX; i++)
    {
        ftmp = fft_out[i + x_left];
        ftmp = log10(ftmp);                                         // �������
        spectrum[i] = (uint16_t)(ftmp * FFT_MAINWIN_dBVALUE_nDISP); // ��������ʾ��Է�ֵ
    }

    // ������ֵת��Ϊ��ʾ�ľ�������
    for (i = 0; i < FFT_SUBWIN_SPECTRUM_MAX; i++)
    {
        spectrum[i] = FFT_SUBWIN_Y0 - spectrum[i];
    }

    // ������ϸƵ����
    for (i = 0; i < FFT_SUBWIN_SPECTRUM_MAX; i++)
    {
        if ((i == 0) || (i == (FFT_SUBWIN_SPECTRUM_MAX / 2)) || (i == (FFT_SUBWIN_SPECTRUM_MAX - 1)))
        {
            forcolor = FFT_SUBWIN_SPECTRUM_COLOR_2;
        }
        else
        {
            forcolor = FFT_SUBWIN_SPECTRUM_COLOR_1;
        }
        Gui_Draw_Line((FFT_SUBWIN_X_ST + i * FFT_SUBWIN_SPEC_INTERNAL), FFT_SUBWIN_Y0,
                      (FFT_SUBWIN_X_ST + i * FFT_SUBWIN_SPEC_INTERNAL), spectrum[i], forcolor);

        Gui_Draw_Line((FFT_SUBWIN_X_ST + i * FFT_SUBWIN_SPEC_INTERNAL), spectrum[i],
                      (FFT_SUBWIN_X_ST + i * FFT_SUBWIN_SPEC_INTERNAL), FFT_SUBWIN_Y1_1, FFT_MAINWIN_SPECTRUM_lastCOLOR);
    }

    // ���2�߼��м��Ƶ��ֵ
    x = FFT_SUBWIN_X_ST - 5;
    y = FFT_SUBWIN_Y1_1 + 4;
    for (i = 0; i < FFT_SUBWIN_SPECTRUM_MAX; i++)
    {
        if (i == 0)
        {
            GUI_A_usigned_Decimal(x, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4,
                                fft_out[x_left], 8, DOT16X16aWORD);
        }
        else if (i == (FFT_SUBWIN_SPECTRUM_MAX / 2))
        {
            GUI_A_usigned_Decimal(x + 9 * ASC16_8PIXELperROW, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4,
                                fft_out[x_left + i], 8, DOT16X16aWORD);
        }
        else if (i == (FFT_SUBWIN_SPECTRUM_MAX - 1))
        {
            GUI_A_usigned_Decimal(x + 18 * ASC16_8PIXELperROW, y, FFT_SUBWIN_SPECTRUM_COLOR_2, BLUE_4_4,
                                fft_out[x_left + i], 8, DOT16X16aWORD);
        }
    }
}
