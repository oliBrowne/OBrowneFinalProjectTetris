/*
 * LCD_Driver.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */

static LTDC_HandleTypeDef hltdc;
static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
static FONT_t *LCD_Currentfonts;
static uint16_t CurrentTextColor   = 0xFFFF;


/*
 * fb[y*W+x] OR fb[y][x]
 * Alternatively, we can modify the linker script to have an end address of 20013DFB instead of 2002FFFF, so it does not place variables in the same region as the frame buffer. In this case it is safe to just specify the raw address as frame buffer.
 */
//uint32_t frameBuffer[(LCD_PIXEL_WIDTH*LCD_PIXEL_WIDTH)/2] = {0};		//16bpp pixel format. We can size to uint32. this ensures 32 bit alignment


//Someone from STM said it was "often accessed" a 1-dim array, and not a 2d array. However you still access it like a 2dim array,  using fb[y*W+x] instead of fb[y][x].
uint16_t frameBuffer[LCD_PIXEL_WIDTH*LCD_PIXEL_HEIGHT] = {0};			//16bpp pixel format.


void LCD_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable the LTDC clock */
  __HAL_RCC_LTDC_CLK_ENABLE();

  /* Enable GPIO clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* GPIO Config
   *
    LCD pins
   LCD_TFT R2 <-> PC.10
   LCD_TFT G2 <-> PA.06
   LCD_TFT B2 <-> PD.06
   LCD_TFT R3 <-> PB.00
   LCD_TFT G3 <-> PG.10
   LCD_TFT B3 <-> PG.11
   LCD_TFT R4 <-> PA.11
   LCD_TFT G4 <-> PB.10
   LCD_TFT B4 <-> PG.12
   LCD_TFT R5 <-> PA.12
   LCD_TFT G5 <-> PB.11
   LCD_TFT B5 <-> PA.03
   LCD_TFT R6 <-> PB.01
   LCD_TFT G6 <-> PC.07
   LCD_TFT B6 <-> PB.08
   LCD_TFT R7 <-> PG.06
   LCD_TFT G7 <-> PD.03
   LCD_TFT B7 <-> PB.09
   LCD_TFT HSYNC <-> PC.06
   LCDTFT VSYNC <->  PA.04
   LCD_TFT CLK   <-> PG.07
   LCD_TFT DE   <->  PF.10
  */

  /* GPIOA configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 |
                           GPIO_PIN_11 | GPIO_PIN_12;
  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Alternate= GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

 /* GPIOB configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_8 | \
                           GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

 /* GPIOC configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

 /* GPIOD configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

 /* GPIOF configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

 /* GPIOG configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | \
                           GPIO_PIN_11;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

  /* GPIOB configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
  GPIO_InitStructure.Alternate= GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* GPIOG configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void LTCD_Layer_Init(uint8_t LayerIndex)
{
	LTDC_LayerCfgTypeDef  pLayerCfg;

	pLayerCfg.WindowX0 = 0;	//Configures the Window HORZ START Position.
	pLayerCfg.WindowX1 = LCD_PIXEL_WIDTH;	//Configures the Window HORZ Stop Position.
	pLayerCfg.WindowY0 = 0;	//Configures the Window vertical START Position.
	pLayerCfg.WindowY1 = LCD_PIXEL_HEIGHT;	//Configures the Window vertical Stop Position.
	pLayerCfg.PixelFormat = LCD_PIXEL_FORMAT_1;  //INCORRECT PIXEL FORMAT WILL GIVE WEIRD RESULTS!! IT MAY STILL WORK FOR 1/2 THE DISPLAY!!! //This is our buffers pixel format. 2 bytes for each pixel
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	if (LayerIndex == 0){
		pLayerCfg.FBStartAdress = (uintptr_t)frameBuffer;
	}
	pLayerCfg.ImageWidth = LCD_PIXEL_WIDTH;
	pLayerCfg.ImageHeight = LCD_PIXEL_HEIGHT;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, LayerIndex) != HAL_OK)
	{
		LCD_Error_Handler();
	}
}

void clearScreen(void)
{
  LCD_Clear(0,LCD_COLOR_WHITE);
}

void LTCD__Init(void)
{
	hltdc.Instance = LTDC;
	/* Configure horizontal synchronization width */
	hltdc.Init.HorizontalSync = ILI9341_HSYNC;
	/* Configure vertical synchronization height */
	hltdc.Init.VerticalSync = ILI9341_VSYNC;
	/* Configure accumulated horizontal back porch */
	hltdc.Init.AccumulatedHBP = ILI9341_HBP;
	/* Configure accumulated vertical back porch */
	hltdc.Init.AccumulatedVBP = ILI9341_VBP;
	/* Configure accumulated active width */
	hltdc.Init.AccumulatedActiveW = 269;
	/* Configure accumulated active height */
	hltdc.Init.AccumulatedActiveH = 323;
	/* Configure total width */
	hltdc.Init.TotalWidth = 279;
	/* Configure total height */
	hltdc.Init.TotalHeigh = 327;
	/* Configure R,G,B component values for LCD background color */
	hltdc.Init.Backcolor.Red = 0;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 0;

	/* LCD clock configuration */
	/* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
	/* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz */
	/* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/4 = 48 Mhz */
	/* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_8 = 48/4 = 6Mhz */

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 4;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
	/* Polarity */
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

	LCD_GPIO_Init();

	if (HAL_LTDC_Init(&hltdc) != HAL_OK)
	 {
	   LCD_Error_Handler();
	 }

	ili9341_Init();
}

/* START Draw functions */


/*
 * This is really the only function needed.
 * All drawing consists of is manipulating the array.
 * Adding input sanitation should probably be done.
 */
void LCD_Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
	frameBuffer[y*LCD_PIXEL_WIDTH+x] = color;  //You cannot do x*y to set the pixel.
}

/*
 * These functions are simple examples. Most computer graphics like OpenGl and stm's graphics library use a state machine. Where you first call some function like SetColor(color), SetPosition(x,y), then DrawSqure(size)
 * Instead all of these are explicit where color, size, and position are passed in.
 * There is tons of ways to handle drawing. I dont think it matters too much.
 */
void LCD_Draw_Circle_Fill(uint16_t Xpos, uint16_t Ypos, uint16_t radius, uint16_t color)
{
    for(int16_t y=-radius; y<=radius; y++)
    {
        for(int16_t x=-radius; x<=radius; x++)
        {
            if(x*x+y*y <= radius*radius)
            {
            	LCD_Draw_Pixel(x+Xpos, y+Ypos, color);
            }
        }
    }
}

void LCD_Draw_Vertical_Line(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
  for (uint16_t i = 0; i < len; i++)
  {
	  LCD_Draw_Pixel(x, i+y, color);
  }
}
void LCD_Draw_Horizontal_Line(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
  for (uint16_t i = 0; i < len; i++)
  {
	  LCD_Draw_Pixel(x+i, y, color);
  }
}
void LCD_Draw_Box(uint16_t x, uint16_t y,uint16_t len, uint16_t color){
	for (uint16_t i = 0; i < len; i++){
		LCD_Draw_Vertical_Line(x+i,y,len,color);
	}

}

void LCD_Clear(uint8_t LayerIndex, uint16_t Color)
{
	if (LayerIndex == 0){
		for (uint32_t i = 0; i < LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT; i++){
			frameBuffer[i] = Color;
		}
	}
  // TODO: Add more Layers if needed
}

//This was taken and adapted from stm32's mcu code
void LCD_SetTextColor(uint16_t Color)
{
  CurrentTextColor = Color;
}

//This was taken and adapted from stm32's mcu code
void LCD_SetFont(FONT_t *fonts)
{
  LCD_Currentfonts = fonts;
}

//This was taken and adapted from stm32's mcu code
void LCD_Draw_Char(uint16_t Xpos, uint16_t Ypos, const uint16_t *c)
{
  uint32_t index = 0, counter = 0;
  for(index = 0; index < LCD_Currentfonts->Height; index++)
  {
    for(counter = 0; counter < LCD_Currentfonts->Width; counter++)
    {
      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> counter)) == 0x00) && (LCD_Currentfonts->Width <= 12)) || (((c[index] & (0x1 << counter)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
      {
         //Background If want to overrite text under then add a set color here
      }
      else
      {
    	  LCD_Draw_Pixel(counter + Xpos,index + Ypos,CurrentTextColor);
      }
    }
  }
}

//This was taken and adapted from stm32's mcu code
void LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  Ascii -= 32;
  LCD_Draw_Char(Xpos, Ypos, &LCD_Currentfonts->table[Ascii * LCD_Currentfonts->Height]);
}
void PrintTimeLCD(uint32_t time_elapsed){

	if(time_elapsed > 100){
	int Sec100s = time_elapsed / 100; // x
	LCD_Draw_Box(155+5,270,30,LCD_COLOR_BLACK);
	LCD_DisplayChar(155, 270, Sec100s + 48);
	}
	time_elapsed = time_elapsed % 100; // now holds xx
	int Sec_10s = time_elapsed / 10; // x
	int Sec_1s = time_elapsed % 10; // x

	LCD_Draw_Box(155+15,270,30,LCD_COLOR_BLACK);
	LCD_Draw_Box(155+30,270,30,LCD_COLOR_BLACK);

	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(110,270,'T');
	LCD_DisplayChar(120,270,'i');
	LCD_DisplayChar(130,270,'m');
	LCD_DisplayChar(146,270,'e');

	LCD_DisplayChar(155+15, 270, Sec_10s + 48);
	LCD_DisplayChar(155+30, 270, Sec_1s + 48);
}
void PrintDownLCD(void){
	LCD_DisplayChar(110 - 70,270,'D');
	LCD_DisplayChar(120 - 70,270,'o');
	LCD_DisplayChar(130 - 70,270,'w');
	LCD_DisplayChar(146 - 70,270,'n');
}
void title_screen(void){

	LCD_SetFont(&Font16x24);

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');

	//line
	LCD_Draw_Box(20,80,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,60,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,20,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,40,20,LCD_COLOR_CYAN);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_BLACK);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');
	//square
	LCD_Draw_Box(160,200,20,LCD_COLOR_RED);
	LCD_Draw_Box(180,200,20,LCD_COLOR_RED);
	LCD_Draw_Box(180,220,20,LCD_COLOR_RED);
	LCD_Draw_Box(160,220,20,LCD_COLOR_RED);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');
	//L
	LCD_Draw_Box(20,220,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(20,240,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(20,260,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(40,260,20,LCD_COLOR_BLUE);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');

	//other L
	LCD_Draw_Box(80,80,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(80,100,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(80,120,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(60,120,20,LCD_COLOR_GREEN);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');
	// smol pp
	LCD_Draw_Box(150,20,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(150,40,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(170,20,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(130,20,20,LCD_COLOR_BLUE2);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');
	//squiggle
	LCD_Draw_Box(70,170,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(90,170,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(90,190,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(110,190,20,LCD_COLOR_MAGENTA);

	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');
	//other squiggle
	LCD_Draw_Box(160,270,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(180,270,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(160,290,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(140,290,20,LCD_COLOR_YELLOW);


	HAL_Delay(500);
	LCD_Clear(0, LCD_COLOR_BLACK);


	//line
	LCD_Draw_Box(20,80,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,60,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,20,20,LCD_COLOR_CYAN);
	LCD_Draw_Box(20,40,20,LCD_COLOR_CYAN);



	//square
	LCD_Draw_Box(160,200,20,LCD_COLOR_RED);
	LCD_Draw_Box(180,200,20,LCD_COLOR_RED);
	LCD_Draw_Box(180,220,20,LCD_COLOR_RED);
	LCD_Draw_Box(160,220,20,LCD_COLOR_RED);


	//L
	LCD_Draw_Box(20,220,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(20,240,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(20,260,20,LCD_COLOR_BLUE);
	LCD_Draw_Box(40,260,20,LCD_COLOR_BLUE);


	//other L
	LCD_Draw_Box(80,80,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(80,100,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(80,120,20,LCD_COLOR_GREEN);
	LCD_Draw_Box(60,120,20,LCD_COLOR_GREEN);


	// smol pp
	LCD_Draw_Box(150,20,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(150,40,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(170,20,20,LCD_COLOR_BLUE2);
	LCD_Draw_Box(130,20,20,LCD_COLOR_BLUE2);


	//squiggle
	LCD_Draw_Box(70,170,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(90,170,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(90,190,20,LCD_COLOR_MAGENTA);
	LCD_Draw_Box(110,190,20,LCD_COLOR_MAGENTA);


	//other squiggle
	LCD_Draw_Box(160,270,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(180,270,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(160,290,20,LCD_COLOR_YELLOW);
	LCD_Draw_Box(140,290,20,LCD_COLOR_YELLOW);

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(100,140,'T');
	LCD_DisplayChar(115,140,'E');
	LCD_DisplayChar(130,140,'T');
	LCD_DisplayChar(145,140,'R');
	LCD_DisplayChar(155,140,'I');
	LCD_DisplayChar(165,140,'S');

}
void grid(void){
	for(uint16_t i = 30;i < 230; i=i+20 ){
		LCD_Draw_Vertical_Line(i, 40, 220,LCD_COLOR_WHITE);

	}
	for(uint16_t i = 40;i < 280; i=i + 20){
		LCD_Draw_Horizontal_Line(30, i, 180,LCD_COLOR_WHITE);

	}
}
void game_screen(void){
	LCD_Clear(0, LCD_COLOR_BLACK);
	grid();

	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayChar(100,25,'T');
	LCD_DisplayChar(107,25,'E');
	LCD_DisplayChar(114,25,'T');
	LCD_DisplayChar(120,25,'R');
	LCD_DisplayChar(127,25,'I');
	LCD_DisplayChar(130,25,'S');
}
void end_screen(void){
	LCD_Clear(0, LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(120,140,'G');
	LCD_DisplayChar(135,140,'A');
	LCD_DisplayChar(150,140,'M');
	LCD_DisplayChar(165,140,'E');

	LCD_DisplayChar(120,170,'O');
	LCD_DisplayChar(135,170,'V');
	LCD_DisplayChar(150,170,'E');
	LCD_DisplayChar(165,170,'R');




	//line
		LCD_Draw_Box(20,80,20,LCD_COLOR_CYAN);
		LCD_Draw_Box(20,60,20,LCD_COLOR_CYAN);
		LCD_Draw_Box(20,20,20,LCD_COLOR_CYAN);
		LCD_Draw_Box(20,40,20,LCD_COLOR_CYAN);



		//square
		LCD_Draw_Box(160,200,20,LCD_COLOR_RED);
		LCD_Draw_Box(180,200,20,LCD_COLOR_RED);
		LCD_Draw_Box(180,220,20,LCD_COLOR_RED);
		LCD_Draw_Box(160,220,20,LCD_COLOR_RED);


		//L
		LCD_Draw_Box(20,220,20,LCD_COLOR_BLUE);
		LCD_Draw_Box(20,240,20,LCD_COLOR_BLUE);
		LCD_Draw_Box(20,260,20,LCD_COLOR_BLUE);
		LCD_Draw_Box(40,260,20,LCD_COLOR_BLUE);


		//other L
		LCD_Draw_Box(80,80,20,LCD_COLOR_GREEN);
		LCD_Draw_Box(80,100,20,LCD_COLOR_GREEN);
		LCD_Draw_Box(80,120,20,LCD_COLOR_GREEN);
		LCD_Draw_Box(60,120,20,LCD_COLOR_GREEN);


		// smol pp
		LCD_Draw_Box(150,20,20,LCD_COLOR_BLUE2);
		LCD_Draw_Box(150,40,20,LCD_COLOR_BLUE2);
		LCD_Draw_Box(170,20,20,LCD_COLOR_BLUE2);
		LCD_Draw_Box(130,20,20,LCD_COLOR_BLUE2);


		//squiggle
		LCD_Draw_Box(70,170,20,LCD_COLOR_MAGENTA);
		LCD_Draw_Box(90,170,20,LCD_COLOR_MAGENTA);
		LCD_Draw_Box(90,190,20,LCD_COLOR_MAGENTA);
		LCD_Draw_Box(110,190,20,LCD_COLOR_MAGENTA);


		//other squiggle
		LCD_Draw_Box(160,270,20,LCD_COLOR_YELLOW);
		LCD_Draw_Box(180,270,20,LCD_COLOR_YELLOW);
		LCD_Draw_Box(160,290,20,LCD_COLOR_YELLOW);
		LCD_Draw_Box(140,290,20,LCD_COLOR_YELLOW);
}
void visualDemo(void)
{
	//uint16_t x;
	//uint16_t y;
	// This for loop just illustrates how with using logic and for loops, you can create interesting things
	// this may or not be useful ;)
//	for(y=0; y<LCD_PIXEL_HEIGHT; y++){
//		for(x=0; x < LCD_PIXEL_WIDTH; x++){
//			if (x & 32)
//				frameBuffer[x*y] = LCD_COLOR_WHITE;
//			else
//				frameBuffer[x*y] = LCD_COLOR_BLACK;
//		}
//	}

	title_screen();
	HAL_Delay(3000);
	game_screen();
	HAL_Delay(3000);
	end_screen();

//
//	HAL_Delay(1500);
//	LCD_Clear(0, LCD_COLOR_GREEN);
//	HAL_Delay(1500);
//	LCD_Clear(0, LCD_COLOR_RED);
//	HAL_Delay(1500);
//	LCD_Clear(0, LCD_COLOR_WHITE);
//	LCD_Draw_Vertical_Line(10,10,250,LCD_COLOR_MAGENTA);
//	HAL_Delay(1500);
//	LCD_Draw_Vertical_Line(230,10,250,LCD_COLOR_MAGENTA);
//	HAL_Delay(1500);
//
//	LCD_Draw_Circle_Fill(125,150,20,LCD_COLOR_BLACK);
//	HAL_Delay(2000);
//
//	LCD_Clear(0,LCD_COLOR_BLUE);
//	LCD_SetTextColor(LCD_COLOR_BLACK);
//	LCD_SetFont(&Font16x24);
//
//	LCD_DisplayChar(100,140,'H');
//	LCD_DisplayChar(115,140,'e');
//	LCD_DisplayChar(125,140,'l');
//	LCD_DisplayChar(130,140,'l');
//	LCD_DisplayChar(140,140,'o');
//
//	LCD_DisplayChar(100,160,'W');
//	LCD_DisplayChar(115,160,'o');
//	LCD_DisplayChar(125,160,'r');
//	LCD_DisplayChar(130,160,'l');
//	LCD_DisplayChar(140,160,'d');
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void LCD_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

// Touch Functionality   //

#if COMPILE_TOUCH_FUNCTIONS == 1

void InitializeLCDTouch(void)
{
  if(STMPE811_Init() != STMPE811_State_Ok)
  {
	 for(;;); // Hang code due to error in initialzation
  }
}

STMPE811_State_t returnTouchStateAndLocation(STMPE811_TouchData * touchStruct)
{
	return STMPE811_ReadTouch(touchStruct);
}

void DetermineTouchPosition(STMPE811_TouchData * touchStruct)
{
	STMPE811_DetermineTouchPosition(touchStruct);
}

uint8_t ReadRegisterFromTouchModule(uint8_t RegToRead)
{
	return STMPE811_Read(RegToRead);
}

void WriteDataToTouchModule(uint8_t RegToWrite, uint8_t writeData)
{
	STMPE811_Write(RegToWrite, writeData);
}

#endif // COMPILE_TOUCH_FUNCTIONS
