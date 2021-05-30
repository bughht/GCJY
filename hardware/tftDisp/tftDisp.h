#ifndef __TFTDISP_H__
#define __TFTDISP_H__

#include "GUI.h"
#include "fft.h"
#include "DataOperation.h"

// ��ʾ��������Ĳ���
#define LINE_Y0 (Y_MAX_PIXEL - 41) // ���߷ָ���������ʾ
#define X_X0 66
#define X_Y0 (Y_MAX_PIXEL - 32)
#define X_TOUCHX (X_X0 + 24)

#define Y_X0 (X_X0 + 100)
#define Y_Y0 X_Y0
#define Y_TOUCHX (Y_X0 + 24)

#define TOUCH_DIG_FORCOLOR YELLOW_4_4
#define TOUCH_DIG_BKCOLOR BLUE_4_4

// ��ʾ������ֵ�Ĳ���
#define VALUE_X_Y0 (Y_MAX_PIXEL - 32)
#define VALUE_X_X0 400
#define VALUE_X_X1 (VALUE_X_X0 + 12 * 5)
#define VAL_X_FORCOLOR WHITE_3_4
#define VAL_X_BKCOLOR GREEN_2_4

#define VALUE_Y_X0 (VALUE_X_X1 + 12 * 6)
#define VALUE_Y_X1 (VALUE_Y_X0 + 12 * 5)

// ��ʾʱ��Ĳ���
#define DATA_TIME_Y (Y_MAX_PIXEL - 32)
#define YEAR_X0 10
#define YEAR_X1 (YEAR_X0 + 12 * 2)
#define MONTH_X (YEAR_X1 + 12 * 3)
#define DATA_X (MONTH_X + 12 * 3)
#define HOUR_X (DATA_X + 12 * 3)
#define MINUTE_X (HOUR_X + 12 * 3)
#define SECOND_X (MINUTE_X + 12 * 3)

#define DATA_TIME_FORCOLOR CYAN_4_4
#define DATA_TIME__BKCOLOR RED_2_4

////////////////////////////////////////////////////////
// ��������������ʾ����
#define FFT_MAINWIN_X0 30  // X������ԭ��
#define FFT_MAINWIN_Y0 320 // Y������ԭ��
#define MAINWIN_WIDTH 590  // �����ڿ��
#define MAINWIN_HEIGH 300  // �����ڸ߶�

// ��߿�
#define FFT_MAINWIN_X0_1 (FFT_MAINWIN_X0 - 2)
#define FFT_MAINWIN_X0_2 (FFT_MAINWIN_X0 - 3)
#define FFT_MAINWIN_Y0_1 (FFT_MAINWIN_Y0 + 1)
#define FFT_MAINWIN_Y0_2 (FFT_MAINWIN_Y0 + 2)

#define FFT_MAINWIN_X1_1 (FFT_MAINWIN_X0 + MAINWIN_WIDTH + 1)
#define FFT_MAINWIN_X1_2 (FFT_MAINWIN_X0 + MAINWIN_WIDTH + 2)
#define FFT_MAINWIN_Y1_1 (FFT_MAINWIN_Y0 - MAINWIN_HEIGH - 1)
#define FFT_MAINWIN_Y1_2 (FFT_MAINWIN_Y0 - MAINWIN_HEIGH - 2)

#define FFT_MAINWIN_Y0_WORD_UNIT (FFT_MAINWIN_Y0 + 10) // ����ʱдƵ�ʵ�λ��Y����

#define NUMBERofDBLINES 8
#define DOTS_20dB 40
#define FFT_MAINWIN_WORD_DB_X (FFT_MAINWIN_X0 - 28)              // ����DBʱ���ֵ�X����
#define FFT_MAINWIN_WORD_DB_Y20 (FFT_MAINWIN_Y0 - DOTS_20dB - 8) //

#define FFT_MAINWIN_SPECT_SUM_NUMB 7 // ÿ����7�����ߺϳ���һ����ʾ
#define FFT_MAINWIN_SPECT_TOTAL_DISP ((FFT_LENGTH - 1) / FFT_MAINWIN_SPECT_SUM_NUMB + 1)

#define FFT_MAINSUBWIN_COLOR WHITE_4_4
#define FFT_MAINWIN_SPECTRUM_COLOR RED_4_4      // ��Ƶ���ߵ���ɫ
#define FFT_MAINWIN_SPECTRUM_lastCOLOR BLUE_1_4 // ��Ƶ���ߵĵ�ɫ

#define FFT_MAINWIN_dBVALUE_nDISP 40 // һ��20LOG10X, 40��Ϊ����ʾ�ĳ�������һ��

#define FFT_MAINWIN_X_SPECTRUM_INTERNAL 100            // ����Ƶ��ֵ�ļ��
#define FFT_MAINWIN_Y_FREQ_WORDS (FFT_MAINWIN_Y0 + 20) // ����Ƶ�����ֵ�Y����

#define FFT_MAINWIN_Y_ARROW (FFT_MAINWIN_Y0 + 10) // ��ͷ
#define FFT_MAINWIN_ARROW_FORCOLOR YELLOW_4_4
#define FFT_MAINWIN_ARROW_BKCOLOR BLUE_1_4

////////////////////////////////////////////////////////
// ����Ϊ�Ӵ��ڲ���
#define FFT_SUBWIN_SPECTRUM_MAX 41 // ��ϸ���߻���9��
#define FFT_SUBWIN_SPEC_INTERNAL 5 // ÿ����� 5 ��

// �Ӵ�����ϸ���ߵ���߿�����
#define FFT_SUBWIN_X0_1 (FFT_MAINWIN_X1_1 + 7) // ����Ŀ�� ���½�X����
#define FFT_SUBWIN_X0_2 (FFT_MAINWIN_X1_1 + 6) // ����Ŀ�� ���½�X����
#define FFT_SUBWIN_Y0_1 FFT_MAINWIN_Y0_1       // ����Ŀ�� ���½�Y����
#define FFT_SUBWIN_Y0_2 FFT_MAINWIN_Y0_2       // ����Ŀ�� ���½�Y����

#define FFT_SUBWIN_X1_1 (FFT_SUBWIN_X0_1 + FFT_SUBWIN_SPECTRUM_MAX * FFT_SUBWIN_SPEC_INTERNAL + 15)
#define FFT_SUBWIN_X1_2 (FFT_SUBWIN_X1_1 + 1) // ����
#define FFT_SUBWIN_Y1_1 FFT_MAINWIN_Y1_1
#define FFT_SUBWIN_Y1_2 FFT_MAINWIN_Y1_2

#define FFT_SUBWIN_X_ST (FFT_SUBWIN_X0_1 + 10) // �Ӵ�����ϸƵ�� ��������ߵ�X�Ὺʼ��
#define FFT_SUBWIN_Y0 FFT_MAINWIN_Y0           // �Ӵ�����ϸƵ�� Y�Ὺʼ��
//
#define FFT_SUBWIN_SPECTRUM_COLOR_1 CYAN_4_4              // �Ӵ�����ϸƵ�׵���ɫ
#define FFT_SUBWIN_SPECTRUM_COLOR_2 (RED_4_4 | GREEN_2_4) // �Ӵ�����ϸƵ�׵� 2�߼��м� Ƶ���ߵ���ɫ
////////////////////////////////////////////////////////

extern uint16_t Last_Spectrum[FFT_MAINWIN_SPECT_TOTAL_DISP];

////////////////////////////////////////////////////////

void tftDisp_Test_Val(uint16_t, uint16_t); // ��ʾ valuetest ��ֵ

void tftDisp_Touch_XY(struTouch *);
void Gui_Draw_A_Arrow(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor);
void Draw_MainWin_Block_Words(void);
void Draw_MainWin_Spectrum(float *fftfreq, uint32_t fftlength);
void Init_Last_Spectrum(uint16_t *lastvalue);
void Draw_xdB_Line(void);
void Draw_MainWin_Spectrum_Flag_Line(void);
void Draw_MainWin_Spectrum_Flag_Word(void);

void Inin_Win(void);

void DRAW_MainWin_Arrow_Freq(uint16_t);
void Write_SubWin_Left_Center_Freq(uint16_t);

void Draw_SubWin_FFT_Spectrum(uint16_t, float *);
void Draw_SubWin_Block(void);
////////////////////////////////////////////////////////
#endif
