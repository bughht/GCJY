/*************************************************
// �ļ�˵��:      ���ļ�Ϊ������ͼ����ʾ����������
//                �������ڵײ������ļ�֮�ϣ��û�����������Ӧ��ͼ�ι���
//                ��������ĺ����ǻ��㺯���������Ľ����ڴ˺���֮�ϣ����������ֲ
// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/
#include "gui.h"

/*************************************************
// �� �� ��:      Gui_Draw_aPixel(uint16_t x,uint16_t y,uint16_t color)
// ������������:  ��һ����. �˺���Ϊ���º����Ļ���, Ҳ���Թ�ΪӲ���ӿڲ�ĺ���
// ��������:      u16 x,u16 y: ����; u16 color: ��ɫ����
// �� �� ֵ:      ��       
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ������ܲ�

// �� �� �ˣ�     ZHAOWL
// ���ڣ�         2017-5-10
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
*************************************************/
void Gui_Draw_aPixel(uint16_t x, uint16_t y, uint16_t color)
{
    Lcd_Set_XY(x, y);
    *(__IO uint16_t *)(Bank1_LCD_D) = color;
}

/****************************************************************************
// �� �� ��:      Gui_Circle(u16 X0,u16 Y0,u16 R,u16 fc)
// ������������:  Bresenham�㷨 ��Բ
// ��������:      u16 X0,u16 Y0:��ɫ����; u16 R:�뾶; u16 fc:��ɫֵ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Circle(uint16_t X0, uint16_t Y0, uint16_t R, uint16_t fc)
{
    int x, y, d;

    x = 0;
    y = R;
    d = 3 - 2 * R; // ���߳�ʼֵ
    while (x < y)
    {
        Gui_Draw_aPixel(X0 + x, Y0 + y, fc); //        7 �Գƻ���8����
        Gui_Draw_aPixel(X0 - x, Y0 + y, fc); //        6
        Gui_Draw_aPixel(X0 + x, Y0 - y, fc); //        2
        Gui_Draw_aPixel(X0 - x, Y0 - y, fc); //        3
        Gui_Draw_aPixel(X0 + y, Y0 + x, fc); //        8
        Gui_Draw_aPixel(X0 - y, Y0 + x, fc); //        5
        Gui_Draw_aPixel(X0 + y, Y0 - x, fc); //        1
        Gui_Draw_aPixel(X0 - y, Y0 - x, fc); //        4

        if (d < 0)
        {
            d = d + 4 * x + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    if (x == y)
    {
        Gui_Draw_aPixel(X0 + x, Y0 + y, fc); //  �Գƻ���8����
        Gui_Draw_aPixel(X0 - x, Y0 + y, fc);
        Gui_Draw_aPixel(X0 + x, Y0 - y, fc);
        Gui_Draw_aPixel(X0 - x, Y0 - y, fc);
        Gui_Draw_aPixel(X0 + y, Y0 + x, fc);
        Gui_Draw_aPixel(X0 - y, Y0 + x, fc);
        Gui_Draw_aPixel(X0 + y, Y0 - x, fc);
        Gui_Draw_aPixel(X0 - y, Y0 - x, fc);
    }
}

/****************************************************************************
// �� �� ��:      Gui_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color) 
// ������������:  ���ߺ�����ʹ��Bresenham ��ֱ���㷨
//0=<k<1, p0=2*dy - dx; �� pk<0 ʱ ��һ��������Ϊ (xk + 1,yk), pk+1 = pk+2*dy; �� pk>=0 ʱ��һ��������Ϊ (xk + 1,yk + 1), pk+1= pk + 2*dy - 2��dx; 
//-1<k<0, p0=2*dy + dx; �� pk>0 ʱ ��һ��������Ϊ (xk + 1,yk), pk+1 = pk+2*dy; �� pk<=0 ʱ��һ��������Ϊ (xk + 1,yk - 1), pk+1= pk + 2*dy + 2��dx; 
// ��������:      u16 x0, u16 y0, u16 x1, u16 y1:����յ�����; u16 Color:��ɫֵ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t Color)
{
    int dx, dy, dx2, dy2, x_inc, y_inc, error, index, xx0, yy0;

    xx0 = x0;
    yy0 = y0;

    Lcd_Set_XY(x0, y0);
    dx = x1 - x0; //����x����
    dy = y1 - y0; //����y����

    if (dx >= 0)
    {
        x_inc = 1;
    }
    else
    {
        x_inc = -1;
        dx = -dx;
    }

    if (dy >= 0)
    {
        y_inc = 1;
    }
    else
    {
        y_inc = -1;
        dy = -dy;
    }

    dx2 = dx << 1;
    dy2 = dy << 1;

    if (dx > dy) //x�������y���룬��ôÿ��x����ֻ��һ���㣬ÿ��y���������ɸ��� //���ߵĵ�������x���룬��x���������
    {
        error = dy2 - dx;
        for (index = 0; index <= dx; index++) //Ҫ���ĵ������ᳬ��x����
        {
            Gui_Draw_aPixel(xx0, yy0, Color); //����
            if (error >= 0)                   //�Ƿ���Ҫ����y����ֵ
            {
                error -= dx2;
                yy0 += y_inc; //����y����ֵ
            }
            error += dy2; // adjust the error term
            xx0 += x_inc; //x����ֵÿ�λ���󶼵���1 // move to the next pixel
        }
    }
    else //y�����x�ᣬ��ÿ��y����ֻ��һ���㣬x�����ɸ���  //��y��Ϊ��������
    {
        error = dx2 - dy;                     // initialize error term
        for (index = 0; index <= dy; index++) // draw the line
        {
            Gui_Draw_aPixel(xx0, yy0, Color); // set the pixel
            if (error >= 0)                   // test if error overflowed
            {
                error -= dy2;
                xx0 += x_inc; // move to next line
            }
            error += dx2;
            yy0 += y_inc;
        }
    }
}

/****************************************************************************
// �� �� ��:      Gui_Draw_Rect(u16 x0, u16 y0, u16 x1, u16 y1, u16 linecolor) 
// ������������:  ������
// ��������:      (x0,y0) ���Ͻǵ������,  (x1,y1) ���½ǵ������; u16 linecolor: �߽���ɫ
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t linecolor)
{
    Gui_Draw_Line(x0, y0, x1, y0, linecolor);
    Gui_Draw_Line(x0, y0, x0, y1, linecolor);
    Gui_Draw_Line(x0, y1, x1, y1, linecolor);
    Gui_Draw_Line(x1, y0, x1, y1, linecolor);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_Asc16_Hzk16(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д16��16����ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc16_Hzk16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
    uint32_t i, j, ch1;
    uint8_t str[HZK16_nByte + 1], tmp;
    uint16_t x0, y0;

    x0 = x;
    y0 = y;

    while (*string)
    {
        if ((*string) < 0x80)
        {
            ch1 = (uint32_t)(*string++);
            Read_aAsc16_Dot(ch1, str);
            Lcd_Set_Region(x0, y0, (x0 + 7), (y0 + ASC16_nLINE - 1));
            for (i = 0; i < ASC16_nLINE; i++)
            {
                tmp = str[i];
                for (j = 0; j < 8; j++)
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
            x0 += 8;
        }
        else
        {
            ch1 = (uint32_t)(*string++);
            ch1 <<= 8;
            ch1 |= *string++;
            Read_aWord_Hzk16_Dot(ch1, str);
            Lcd_Set_Region(x0, y0, (x0 + 15), (y0 + ASC16_nLINE - 1));
            for (i = 0; i < HZK16_nLINE; i++)
            {
                tmp = str[2 * i];
                for (j = 0; j < 8; j++)
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
                tmp = str[2 * i + 1];
                for (j = 0; j < 8; j++)
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
            x0 += 16;
        }
    }
    Lcd_Set_Region(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_A_Asc16(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 chr) 
// ������������:  д8��16���һ��ASCII�ַ�
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 chr:�ַ� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_A_Asc16(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t chr)
{
    uint32_t i, j;
    uint8_t str[HZK16_nByte + 1], tmp;

    Read_aAsc16_Dot(chr, str);
    Lcd_Set_Region(x, y, (x + 7), (y + ASC16_nLINE - 1));
    for (i = 0; i < ASC16_nLINE; i++)
    {
        tmp = str[i];
        for (j = 0; j < 8; j++)
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

/****************************************************************************
// �� �� ��:      Gui_Draw_Asc24_Hzk24(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д24��24�����Ӣ���ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc24_Hzk24(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
    uint32_t i, j, ch1;
    uint8_t str[HZK24_nByte + 1], tmp;
    uint16_t x0, y0;

    x0 = x;
    y0 = y;

    while (*string)
    {
        if ((*string) < 0x80)
        {
            ch1 = (uint32_t)(*string);
            string++;
            Read_aAsc24_Dot(ch1, str);
            Lcd_Set_Region(x0, y0, (x0 + 11), (y0 + ASC24_nLINE - 1));
            for (i = 0; i < ASC24_nLINE; i++)
            {
                tmp = str[2 * i];
                for (j = 0; j < 8; j++)
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
                tmp = str[2 * i + 1];
                for (j = 0; j < 4; j++)
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
            x0 += 12;
        }
        else
        {
            ch1 = (uint32_t)(*string);
            string++;
            ch1 <<= 8;
            ch1 |= *string;
            string++;
            Read_aWord_Hzk24_Dot(ch1, str);
            Lcd_Set_Region(x0, y0, (x0 + 23), (y0 + HZK24_nLINE - 1));
            for (i = 0; i < HZK24_nLINE; i++)
            {
                tmp = str[3 * i];
                for (j = 0; j < 8; j++)
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

                tmp = str[3 * i + 1];
                for (j = 0; j < 8; j++)
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
                tmp = str[3 * i + 2];
                for (j = 0; j < 8; j++)
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
            x0 += 24;
        }
    }
    Lcd_Set_Region(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
}

/****************************************************************************
// �� �� ��:      Gui_Draw_Asc32_String(u16 x, u16 y, u16 forcolor, u16 bkcolor, u8 *string) 
// ������������:  д32��32���Ӣ���ַ���
// ��������:      u16 x, u16 y:���Ͻǵ����ʼ����; u16 forcolor:ǰ��ɫ; u16 bkcolor: ����ɫ; u8 *string:�ַ��� 
// �� �� ֵ:      ��    
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void Gui_Draw_Asc32_String(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t *string)
{
    uint32_t i, j, ch1;
    uint8_t str[ASC32_nByte + 1], tmp;
    uint16_t x0, y0;

    x0 = x;
    y0 = y;

    while (*string)
    {
        if ((*string) < 0x80)
        {
            ch1 = (uint32_t)(*string);
            string++;
            Read_aAsc32_Dot(ch1, str);
            Lcd_Set_Region(x0, y0, (x0 + 15), (y0 + ASC32_nLINE - 1));
            for (i = 0; i < ASC32_nLINE; i++)
            {
                tmp = str[2 * i];
                for (j = 0; j < 8; j++)
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
                tmp = str[2 * i + 1];
                for (j = 0; j < 8; j++)
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
            x0 += 16;
        }
    }
    Lcd_Set_Region(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʾһ���޷���ָ�����ȵ�ʮ������
void GUI_A_usigned_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint32_t digital, uint8_t numericprecision, uniWORDDOTSTYPE dotstype)
{ //     X����        Y����        ǰ����ɫ           ������ɫ         ��ʾ����          ��ʾ��λ��               ��ʾ���ֵĵ���
    char dig[30];
    memset(dig, '\0', 30);

    switch (numericprecision)
    {
    case 1:
    {
        sprintf(dig, "%1d", digital);
        break;
    }
    case 2:
    {
        sprintf(dig, "%2d", digital);
        break;
    }
    case 3:
    {
        sprintf(dig, "%3d", digital);
        break;
    }
    case 4:
    {
        sprintf(dig, "%4d", digital);
        break;
    }
    case 5:
    {
        sprintf(dig, "%5d", digital);
        break;
    }
    case 6:
    {
        sprintf(dig, "%6d", digital);
        break;
    }
    case 7:
    {
        sprintf(dig, "%7d", digital);
        break;
    }
    case 8:
    {
        sprintf(dig, "%8d", digital);
        break;
    }
    case 9:
    {
        sprintf(dig, "%9d", digital);
        break;
    }
    default:
    {
        sprintf(dig, "%d", digital);
        break;
    } // ȱʡ
    }

    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    }
    }
}

void GUI_A_signed_Decimal(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, int digital, uint8_t numericprecision, uniWORDDOTSTYPE dotstype)
{ //     X����        Y����        ǰ����ɫ           ������ɫ        ��ʾ����          ��ʾ��λ��           ��ʾ���ֵĵ���
    char dig[30];
    memset(dig, '\0', 30);

    switch (numericprecision)
    {
    case 1:
    {
        sprintf(dig, "%1d", digital);
        break;
    }
    case 2:
    {
        sprintf(dig, "%2d", digital);
        break;
    }
    case 3:
    {
        sprintf(dig, "%3d", digital);
        break;
    }
    case 4:
    {
        sprintf(dig, "%4d", digital);
        break;
    }
    case 5:
    {
        sprintf(dig, "%5d", digital);
        break;
    }
    case 6:
    {
        sprintf(dig, "%6d", digital);
        break;
    }
    case 7:
    {
        sprintf(dig, "%7d", digital);
        break;
    }
    case 8:
    {
        sprintf(dig, "%8d", digital);
        break;
    }
    case 9:
    {
        sprintf(dig, "%9d", digital);
        break;
    }
    default:
    {
        sprintf(dig, "%d", digital);
        break;
    }
    }

    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    }
    }
}

// ��ʾһ���޷���ָ�����ȵ�ʮ��������
void GUI_A_Uint8_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint8_t digital, uniWORDDOTSTYPE dotstype)
{ //   X����        Y����        ǰ����ɫ           ������ɫ         ��ʾ����          ��ʾ���ֵĵ���
    char dig[20], buf[20];
    memset(dig, '\0', 20);
    memset(buf, '\0', 20);
    strcpy(buf, "0x");
    sprintf(dig, "%x", digital);
    strcat(buf, dig);
    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    }
    }
}

// ��ʾһ���޷���ָ�����ȵ�ʮ��������
void GUI_A_Uint16_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint16_t digital, uniWORDDOTSTYPE dotstype)
{ //   X����        Y����        ǰ����ɫ           ������ɫ         ��ʾ����          ��ʾ���ֵĵ���
    char dig[20], buf[20];
    memset(dig, '\0', 20);
    memset(buf, '\0', 20);
    strcpy(buf, "0x");
    sprintf(dig, "%x", digital);
    strcat(buf, dig);
    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    }
    }
}

// ��ʾһ���޷���ָ�����ȵ�ʮ��������
void GUI_A_Uint32_Hex(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, uint32_t digital, uniWORDDOTSTYPE dotstype)
{ //   X����        Y����        ǰ����ɫ           ������ɫ         ��ʾ����          ��ʾ���ֵĵ���
    char dig[20], buf[20];
    memset(dig, '\0', 20);
    memset(buf, '\0', 20);
    strcpy(buf, "0x");
    sprintf(dig, "%x", digital);
    strcat(buf, dig);
    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)buf);
        break;
    }
    }
}
/////////////////////////////////////////////////////////////////////////////
// ��ʾfloat �͵�һ����
void GUI_aFloat(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor, float digital, uint8_t numericprecision, uniWORDDOTSTYPE dotstype)
{ //   X����        Y����        ǰ����ɫ           ������ɫ         ��ʾ����        С�����ֵ�λ��             ��ʾ���ֵĵ���
    char dig[30];
    memset(dig, '\0', 30);

    switch (numericprecision)
    {
    case 0:
    {
        sprintf(dig, "%.0f", digital);
        break;
    } // ����ʾС�����֣���������
    case 1:
    {
        sprintf(dig, "%.1f", digital);
        break;
    } // ��ʾ1λС������������
    case 2:
    {
        sprintf(dig, "%.2f", digital);
        break;
    } // ��ʾ2λС������������
    case 3:
    {
        sprintf(dig, "%.3f", digital);
        break;
    } // ��ʾ3λС������������
    case 4:
    {
        sprintf(dig, "%.4f", digital);
        break;
    } // ��ʾ4λС������������
    case 5:
    {
        sprintf(dig, "%.5f", digital);
        break;
    } // ��ʾ5λС������������
    default:
    {
        sprintf(dig, "%f", digital);
        break;
    } // ��ʾ6λС�����������룬float��С�����־���6λ
    }

    switch (dotstype)
    {
    case DOT16X16aWORD:
    {
        Gui_Draw_Asc16_Hzk16(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 16*8 ����ģʽ��ʾ��ֵ
    case DOT24X24aWORD:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 24*12����ģʽ��ʾ��ֵ
    case DOT32X16aCHAR:
    {
        Gui_Draw_Asc32_String(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    } // 32*16����ģʽ��ʾ��ֵ
    default:
    {
        Gui_Draw_Asc24_Hzk24(x, y, forcolor, bkcolor, (uint8_t *)dig);
        break;
    }
    }
}
