#include "fft.h"

// �����鲿ȫ��Ϊ0
void Set_inFFT_IM_0(float *inSignal, uint32_t fftlength)
{
    uint32_t i;
    for (i = 0; i < fftlength; i++)
    {
        inSignal[2 * i + 1] = 0; //�鲿ȫ��Ϊ0
    }
}
// ����ʵ��ȫ��Ϊ0
void Set_inFFT_RE_0(float *inSignal, uint32_t fftlength)
{
    uint32_t i;

    for (i = 0; i < fftlength; i++)
    {
        inSignal[2 * i] = 0;
    }
}

// ����ʵ���鲿ȫ��Ϊ0
void Set_inFFT_RE_IM_0(float *inSignal, uint32_t fftlength)
{
    uint32_t i;
    for (i = 0; i < (fftlength * 2); i++)
    {
        inSignal[i] = 0;
    }
}

void Set_inFFT_RE_DC(float *inSignal, uint32_t fftlength, uint16_t dclevel)
{
    uint32_t i;

    for (i = 0; i < fftlength; i++)
    {
        inSignal[2 * i] += dclevel;
    }
}

// ���������ź�
void Set_inFFT_RE_TO_Sin(float *inSignal, uint16_t am, uint32_t freq, uint32_t fftlength, uint32_t samplefreq)
{ //  ��ŵ�����        ���         Ƶ��           �������              ����Ƶ��
    uint32_t i;
    for (i = 0; i < fftlength; i++)
    {
        inSignal[2 * i] += am * arm_sin_f32(2 * PI * i * freq / samplefreq);
    }
}

// ���������ź�
void Set_inFFT_RE_TO_Cos(float *inSignal, uint16_t am, uint32_t freq, uint32_t fftlength, uint32_t samplefreq)
{ //  ��ŵ�����        ���         Ƶ��           �������              ����Ƶ��
    uint32_t i;
    for (i = 0; i < fftlength; i++)
    {
        inSignal[2 * i] += am * arm_cos_f32(2 * PI * i * freq / samplefreq); // samplefreq/freq: ��ʾ��Ƶ�ʵ��ź�ռ��������/����
    }
}
// �����ϳɵ����Ҳ�
void Generate_Wave_Sin(float *inSignal, uint32_t fftlength, uint32_t samplefreq)
{
    uint32_t freq1, freq2, freq3, freq4, freq5; // Ƶ��HZ
    uint16_t am1, am2, am3, am4, am5;           // ��� �޵�λ [1-2047]

    am1 = 150; //
    freq1 = 6;
    am2 = 300;
    freq2 = 77;
    am3 = 500;
    freq3 = 690;
    am4 = 1000;
    freq4 = 1000;
    am5 = 800;
    freq5 = 1700;

    Set_inFFT_RE_IM_0(inSignal, fftlength);     // ��ʵ���鲿��0
    Set_inFFT_RE_DC(inSignal, fftlength, 2000); // ����ֱ����ƽ
    Set_inFFT_RE_TO_Sin(inSignal, am1, freq1, fftlength, samplefreq);
    Set_inFFT_RE_TO_Sin(inSignal, am2, freq2, fftlength, samplefreq);
    Set_inFFT_RE_TO_Sin(inSignal, am3, freq3, fftlength, samplefreq);
    Set_inFFT_RE_TO_Sin(inSignal, am4, freq4, fftlength, samplefreq);
    //    Set_inFFT_RE_TO_Sin(inSignal, am5,  freq5, fftlength, samplefreq); // 2048Hz����ʱ���
}

// �������岨
void Generate_Wave_Pulse(float *inSignal, uint32_t fftlength, uint32_t samplefreq)
{
    uint32_t i, freq, signalH, signalL;
    uint32_t numberofdots_aPeroid, numberofdots_H, tmp1;
    float dutyratio, ftmp;

    signalH = 3000;   // �ߵ�ƽ��ѹ
    signalL = 800;    // �͵�ƽ��ѹ
    freq = 16;        // Ƶ��HZ
    dutyratio = 12.5; // ռ�ձ� 12.5%

    Set_inFFT_RE_IM_0(inSignal, fftlength); // ��ʵ���鲿��0

    ftmp = samplefreq;
    ftmp = ftmp / freq;                                  // samplefreq/freq: ��ʾ��Ƶ�ʵ��ź�1������ռ��������
    numberofdots_aPeroid = (uint32_t)ftmp;               // ��Ƶ�ʵ��ź�1������ռ��������
    numberofdots_H = (uint32_t)(ftmp * dutyratio / 100); // ��Ƶ�ʵ��ź������иߵ�ƽռ��������
    for (i = 0; i < FFT_LENGTH; i++)                     //�����ź�����
    {
        tmp1 = i % numberofdots_aPeroid; // ���ڸõ���x���������еĵڼ�����
        if (tmp1 < numberofdots_H)       // С�� dutyratio% ��Ϊ�ߵ�ƽ
        {
            inSignal[2 * i] = signalH;
        }
        else
        {
            inSignal[2 * i] = signalL;
        }
    }
}

void Windows_Input_Param(float *fftinbuf, uint32_t fftlength)
{
    uint32_t i;
    float ftmp;

    for (i = 0; i < fftlength; i++)
    {
        ftmp = fftinbuf[2 * i]; // ʵ��
        //ftmp = ftmp * FWin_Param[i];
        fftinbuf[2 * i] = ftmp;
    }
}

void Calculate_FFT(float *insignal, float *outsignal, uint32_t fftlength)
{
    arm_cfft_radix4_instance_f32 scfft;

    arm_cfft_radix4_init_f32(&scfft, fftlength, 0, 1); //��ʼ��scfft�ṹ�壬�趨FFT��ز���
    arm_cfft_radix4_f32(&scfft, insignal);             //FFT���㣨��4��
    arm_cmplx_mag_f32(insignal, outsignal, fftlength); //��������������ģ�÷�ֵ
}

void Write_ADCBuf_toFFTbuf(uint16_t *adcbuf, float *fftinbuf, uint32_t adclength)
{
    uint32_t i;
    for (i = 0; i < adclength; i++)
    {
        fftinbuf[2 * i] = (float)adcbuf[i]; // ʵ��
        fftinbuf[2 * i + 1] = 0;            // �鲿ȫ��Ϊ0
    }
}
