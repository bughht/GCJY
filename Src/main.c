
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include "key.h"
#include "spin.h"
#include "led.h"
#include "common.h"
#include "exti_test.h"
#include "lcd_drive.h"
#include "gui.h"
#include "tftDisp.h"
#include "w25q64.h"
#include "touch.h"
#include "fft.h"
#include "windowsframe.h"
#include "DataOperation.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// ���̣�FFT
// Tim2.����Ƚ�ͨ��2�������� ����һ· ADC1_IN10 ����ADCת������ɺ��Զ�ͨ��DMAͨ���������� ADC1_Value[]�С�
//      �������󣬴��� "DMA2_Stream0_IRQHandler" �жϣ� ����"ADC_DMAConvCplt",�ٵ���"HAL_ADC_ConvCpltCallback" �������ݴ���

// ��ʾ���밴ת�� dB ��λ, ��������ʾ����Ƶ�ף��Ӵ�����ʾ������ϸ���ߣ��������·���С��ͷָʾ���Ӵ���Ƶ�����������е�λ��
// 1�����԰���K3K4������ʾ�Ӵ��ڵ�Ƶ��
// 2����������ת������ϸ���Ӵ��ڵ�Ƶ��
// 3�����Ե㴥�����������������Ӵ��ڵ�Ƶ��
// 4�����Ի����Ӵ���������  ���Ӵ��ڵ�Ƶ��

/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

// ��ʱ����������жϣ��ж�Ƶ�����ۿ��Ժܸߣ���ʵ�����ڽ����ж�ҪһЩʱ�䣬һ�����500KHz;
// ��ʱ������ʱ�ж�Ƶ�ʵļ��㷽��: Fclk/(Prescaler+1)/(Period)
// Fclk:��ʱ����������Ƶ��*2;  Prescaler:Ԥ��Ƶֵ;  Period:���ϼ��������ֵ
// TIMER4�ж�Ƶ��: 84M/(8399+1)/(999+1)=10Hz
// TIMER5�ж�Ƶ��: 84M/(83+1)/(999999+1)=1Hz
// TIMER7�ж�Ƶ��: 84M/(83+1)/(999+1)=1000Hz
// TIMER6�ж�Ƶ��: 84M/(3+1)/(4+1)=4.2MHz, ���ڴ���DAC1; ��DAC1��ʱ����ʱ,ֻ����ָ����TIM6�����,TIM6���Բ���Ϊ�ж�ģʽ

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
    /* USER CODE BEGIN 1 */
    struKeyStatus key; // �ĸ�������״̬����
    struTouch ctpxy;   // ���ݴ������Ĳ���
    struspin spin;

    //float fft_inputbuf[FFT_LENGTH * 2]; //FFT��������
    //float fft_outputbuf[FFT_LENGTH];    //FFT�������

    uint16_t disp_x_freq_left;      // ��ϸ��9����������ߵĵ���
    FunctionalState disp_x_freq_en; // ��ʾ��ϸƵ��ʹ��
    /* USER CODE END 1 */

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM4_Init();
    MX_USART1_UART_Init();
    MX_SPI2_Init();
    MX_TIM5_Init();
    MX_TIM7_Init();
    MX_FSMC_Init();
    MX_ADC1_Init();
    MX_TIM2_Init();

    /* Initialize interrupts */
    MX_NVIC_Init();
    /* USER CODE BEGIN 2 */
    //_TIM2_SetFreq();

    HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1); // ʹ��TIM4������PA1���PWM�ź�

    HAL_TIM_Base_Start_IT(&htim7);

    W25Q64_CS_GPIO_Init();  // W25Q64.CS���ų�ʼ��
    FT6336_I2C_GPIO_Init(); // LCD���Ĵ�������2�����ų�ʼ��
    LCD_Initialize();       // LCD���ĸ�λ���ţ��������� ��ʼ��

    IO_GPIO_Init();
    LED_GPIO_Init();       // �ĸ�LEDָʾ�� ���ų�ʼ�� �����������
    Key_GPIO_Init();       // �ĸ�����      ���ų�ʼ�� ���������룩
    Exti_Test_GPIO_Init(); // �ж��������ŵĳ�ʼ��, �������ж˵�IO�����ĳ�ʼ��

    Spin_GpioInit(); // ��ת��������IO���ų�ʼ��
    spin.keystatus = KEY_NO_PRESSED;
    spin.rotatestatus = SPIN_NO_ROTATE;
    //////////////////////
    Init_KeyStatus(&key); // �ĸ����� ״̬��ʼ��Ϊ "û�а��¼�"

    ProcADC_Enable = DISABLE; // ������ADC1_IN0�任
    // ADC TIM2��CC2ƥ���¼�����
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC1_Value, SIZEofADC1); // ����ADC1_IN0��DMA ���ݻ�����
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);                      // ʹ��TIM2������PA1���PWM�ź�

    ADCBuf_Init();
    ADCBuf_Normalize();

    t_ratio = 50;
    f_ratio = 2;

    Lcd_Clear_All(BLACK);

    Voltage_time_fig = Figure_init(Point(64, 30), Point(355, 350));
    sprintf(Voltage_time_fig.xlabel, "t/ms");
    sprintf(Voltage_time_fig.ylabel, "U/Voltage");
    sprintf(Voltage_time_fig.title, "ʱ��");
    Figure_bound_data(&Voltage_time_fig, ADC_Voltage_buf + 10, (float)SIZEofADC1 / t_ratio);
    Figure_window_plot(&Voltage_time_fig);
    Voltage_time_fig.xrange[0] = 0;
    Voltage_time_fig.xrange[1] = (float)125 / t_ratio;
    Voltage_time_fig.xlegendnum = 9;
    Voltage_time_fig.ylegendnum = 21;

    FFT_fig = Figure_init(Point(420, 30), Point(X_MAX_PIXEL - 15, 350));
    sprintf(FFT_fig.xlabel, "f/kHz");
    sprintf(FFT_fig.ylabel, "U/Voltage");
    sprintf(FFT_fig.title, "Ƶ��");
    Figure_bound_data(&FFT_fig, fft_Result, FFT_LENGTH / f_ratio);
    Figure_window_plot(&FFT_fig);
    FFT_fig.xrange[0] = 0;
    FFT_fig.xrange[1] = (SAMPLE_FREQ / 1000) / f_ratio;
    FFT_fig.xlegendnum = 13;
    FFT_fig.ylegendnum = 21;

    StopButton = Button_init(Point(700, 400), Point(800, 450), " Pause", " Resume", WHITE_4_4, WHITE_1_4, RED_4_4);
    Button_plot(&StopButton);

    /////////////////////////
    //Init_Last_Spectrum(Last_Spectrum); // ��ʼ�������ߵ�ǰֵ
    //Inin_Win();                        // ��ʼ��LCD��ʾ�Ĳ��������
    //disp_x_freq_left = 0;              // �Ӵ��������Ƶ��=0
    //disp_x_freq_en = ENABLE; // ����ʹ����ʾ

    /////////////////////////
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        /*
        if (disp_x_freq_en == ENABLE)
        { // ����ת������ �� K3 K4 �� ���� �ı� ��ϸƵ�׵�������Ƶ��ֵ������������+0.5HZ
            disp_x_freq_en = DISABLE;
            DRAW_MainWin_Arrow_Freq(disp_x_freq_left);                 // �����������·���С��ͷ��ָ���Ӵ�����ϸ�������������п�ʼ��λ��
            Write_SubWin_Left_Center_Freq(disp_x_freq_left);           // ���Ӵ�������ϸ����ͼ�б����һ�����м�����1�����ߵ�Ƶ��ֵ
            Draw_SubWin_FFT_Spectrum(disp_x_freq_left, fft_outputbuf); // ���Ӵ��ڻ�����ϸ����ͼ
        }
        */
        // �������Ĵ���
        if (ReadTouch_Enable == ENABLE) // ÿ10mS�����ȡ�����ʹ�����, ���Ҵ���
        {
            ReadTouch_Enable = DISABLE;
            ReadCTP(&ctpxy); // ��ȡ�������Ĵ������꼰״̬
            if (ctpxy.ctpmainstatus == JUST_TOUCH)
            {
                if (Button_Checkpos(&StopButton, ctpxy.ctpxy.ctp_x, ctpxy.ctpxy.ctp_y) == TRUE)
                {
                    StopButton.ButtonDOWN = !StopButton.ButtonDOWN;
                    Button_plot(&StopButton);
                }
            }
            if (ctpxy.ctpmainstatus == TOUCHED)
            {
                if (Figure_Checkpos(&Voltage_time_fig, ctpxy.ctpxy.ctp_x, ctpxy.ctpxy.ctp_y) == TRUE && StopButton.ButtonDOWN == TRUE)
                {
                    if (ctpxy.xmove == LEFT_MOVING)
                    {
                        t_ratio -= 2;
                        t_ratio = t_ratio < 2 ? 2 : t_ratio;
                        Voltage_time_fig.datalen = SIZEofADC1 / t_ratio;
                        Voltage_time_fig.xrange[1] = 125 / t_ratio;
                        Figure_line_plot(&Voltage_time_fig, 1.8, GREEN_4_4);
                    }
                    if (ctpxy.xmove == RIGHT_MOVING)
                    {
                        t_ratio += 2;
                        t_ratio = t_ratio > 100 ? 100 : t_ratio;
                        Voltage_time_fig.datalen = SIZEofADC1 / t_ratio;
                        Voltage_time_fig.xrange[1] = 125 / t_ratio;
                        Figure_line_plot(&Voltage_time_fig, 1.8, GREEN_4_4);
                    }
                }
                if (Figure_Checkpos(&FFT_fig, ctpxy.ctpxy.ctp_x, ctpxy.ctpxy.ctp_y) == TRUE && StopButton.ButtonDOWN == TRUE)
                {
                    if (ctpxy.xmove == LEFT_MOVING)
                    {
                        f_ratio -= 0.4;
                        //f_ratio += ctpxy.xmove / 100;
                        f_ratio = f_ratio < 2 ? 2 : f_ratio;
                        FFT_fig.datalen = FFT_LENGTH / f_ratio;
                        FFT_fig.xrange[1] = SAMPLE_FREQ / 1000.0 / f_ratio;
                        Figure_line_plot(&FFT_fig, 1, PINGKISH_4_4);
                    }
                    if (ctpxy.xmove == RIGHT_MOVING)
                    {
                        f_ratio += 0.4;
                        f_ratio = f_ratio > 30 ? 30 : f_ratio;
                        FFT_fig.datalen = FFT_LENGTH / f_ratio;
                        FFT_fig.xrange[1] = SAMPLE_FREQ / 1000.0 / f_ratio;
                        Figure_line_plot(&FFT_fig, 1, PINGKISH_4_4);
                    }
                }
            }
            //Proc_Touch_inMainWin(ctpxy, &disp_x_freq_left, &disp_x_freq_en); // ���������ڵĴ���������ı����Ӵ�����ϸ����ͼ�е�һ�����ߵ�Ƶ��ֵ��ϸ��
            //Proc_Touch_inSubWin(ctpxy, &disp_x_freq_left, &disp_x_freq_en);  // �����Ӵ��ڵĴ���������ı����Ӵ�����ϸ����ͼ�е�һ�����ߵ�Ƶ��ֵ��ϸ��
        }
        // ��������ת�������Ĵ���
        if (ReadKey_Enable == ENABLE)
        {
            ReadKey_Enable = DISABLE;
            ////////////////////////

            Read_KeyStatus(&key); // ��ȡ�ĸ�������״̬��������ȥ����
            Key_Process(key, &disp_x_freq_left, &disp_x_freq_en); // ����K3 K4������״̬���ı�����ϸ����ͼ�е�һ�����ߵ�Ƶ��ֵ���ֵ�
            ////////////////////////
            /*
            Read_Spin(&spin);                                    // ��ȡ��ת��������ֵ
            Proc_Spin(spin, &disp_x_freq_left, &disp_x_freq_en); // ����ת��������ı�����ϸ����ͼ�е�һ�����ߵ�Ƶ��ֵ��ϸ��
            */
        }

        // ���һ�β������ں����ݵĴ���
        if (ProcADC_Enable == ENABLE) // ���һ��ADCת���󣬸ñ�־λ ��ʹ��
        {
            //TIM2->DIER &= 0;
            //TIM2->CR1 &= ~(1);
            HAL_TIM_Base_Stop_IT(&htim2);
            HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
            HAL_TIM_Base_Stop(&htim2);
            //LED1_TOGGLE();
            Figure_line_plot(&Voltage_time_fig, 1.8, GREEN_4_4);
            ADC2FFTbuffer();
            FFT_Cal();
            Figure_line_plot(&FFT_fig, 1, PINGKISH_4_4);

            //            Generate_Wave_Pulse(fft_inputbuf, FFT_LENGTH, SAMPLE_FREQ); // ����һ�����岨��Ƶ��/ռ�ձ�/���� �ɵ�
            /*
            //Generate_Wave_Sin(fft_inputbuf, FFT_LENGTH, SAMPLE_FREQ);   // �������������Ҳ���Ƶ��/���� �ɵ�
            Write_ADCBuf_toFFTbuf(ADC1_Value, fft_inputbuf, SIZEofADC1); // ��ADC��ֵд��FFT�������飬����ʼ����FFT��������
            Windows_Input_Param(fft_inputbuf, FFT_LENGTH);               // ��ԭʼ�źżӴ�������Ƶ��
            Calculate_FFT(fft_inputbuf, fft_outputbuf, FFT_LENGTH);      // ����FFTֵ
            // ����Ϊ��ʾ�����ߺ���ϸ����
            //Draw_xdB_Line();                                           // ��ʾ����  dB������
            //Draw_MainWin_Spectrum_Flag_Line();                         // ��������ʾ����Ƶ�ʶ�����
            //Draw_MainWin_Spectrum(fft_outputbuf, FFT_LENGTH);          // ��������ʾ������Ƶ��
            //Draw_SubWin_FFT_Spectrum(disp_x_freq_left, fft_outputbuf); // ���Ӵ������Ƶ��������ʾ9����ϸ���� ��0.5HZ���
            */
            //HAL_TIM_Base_Start_IT(&htim2);
            //HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
            ProcADC_Enable = DISABLE;
        }
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Configure the Systick interrupt time 
    */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick 
    */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
    /* USART1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* TIM5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
    /* TIM7_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM7_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
    /* EXTI9_5_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    /* DMA2_Stream0_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
    /* TIM4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM4_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
