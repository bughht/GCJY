#ifndef  __SPIN_H
#define  __SPIN_H

#include  "stm32f4xx_hal.h"
#include  "key.h"
//////////////////////////////////////////////////////

#define    SPIN_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE() //  ���������ת������ʹ�õ�GPIOEʱ��
#define    GPIO_SPIN_PORT              GPIOE                 //  �������ת�����������������ڵĶ˿�
#define    SPIN_KEY_PIN                GPIO_PIN_6            // �������ת������ ���� ���ź�
#define    SPIN_A_PIN                  GPIO_PIN_4            // �������ת������ A ���ź�
#define    SPIN_B_PIN                  GPIO_PIN_5            // �������ת������ B ���ź�

#define    READ_SPIN_KEY()             HAL_GPIO_ReadPin(GPIO_SPIN_PORT, SPIN_KEY_PIN) // PE0
#define    READ_SPIN_A()               HAL_GPIO_ReadPin(GPIO_SPIN_PORT, SPIN_A_PIN)   // PE2 ���� A ���ŵĵ�ƽ
#define    READ_SPIN_B()               HAL_GPIO_ReadPin(GPIO_SPIN_PORT, SPIN_B_PIN)   // PE1 ���� B ���ŵĵ�ƽ


///////////////////////////////////////////////////
typedef enum
{
    L = 0,    // �͵�ƽ
    H    ,    // �ߵ�ƽ
}LEVEL;

//typedef  enum
//{
//    KEY_NO_PRESSED      = 0,
//    KEY_JUST_PRESSED       ,
//    KEY_ALREADY_PRESSED    ,
//    KEY_JUST_POPUP         ,
//}KeyStatus;

typedef enum
{
    SPIN_NO_ROTATE   = 0,  // ����ת
    SPIN_CLOCKWISE      ,  // ˳ʱ����ת
    SPIN_UNTICLOCKWISE  ,  // ��ʱ����ת
}RotateStatus;

typedef struct tagspin
{
    RotateStatus   rotatestatus; // ��ת״̬
    KeyStatus      keystatus;    // ����״̬
}struspin;

typedef enum
{
    SPIN_AB_ST0  = 0,    // A=0 B=0;
    SPIN_AB_ST1     ,    // A=0 B=1;
    SPIN_AB_ST2     ,    // A=1 B=0;
    SPIN_AB_ST3     ,    // A=1 B=1; 
}SpinABstatus;          // ��ת�������ź��� A B �ĵ�ƽ



///////////////////////////////////////////////////
void  Spin_GpioInit(void);
void  Init_Spin_Status(struspin *);  // ��ʼ��������ת��������״̬
void  Read_Spin(struspin *);
void  Proc_Spin(struspin , uint16_t *, FunctionalState *);
    
#endif


