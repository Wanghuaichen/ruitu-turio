/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         ocp_spi.c
* @author       zhou
* @version      V1.0
* @date         2018/5/4
* @brief        板上SPI配置文件
**************************************************************************************************
*/
#include "include.h"

static void spi1_NVIC_config(void);
static void spi1_gpio_config(void);
static void spi1_parameter_config(void);
/**
*@function void spi1_init(void)
*@brief    spi1初始化,包括时钟\中断\gpio\参数
*@param    void
*@return   无
*@date     2018/5/4
*/
void spi1_init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  spi1_NVIC_config();
  spi1_gpio_config();
  spi1_parameter_config();
}
/**
*@function void spi1_NVIC_config(void)
*@brief    spi中断配置
*@param    void
*@return   无
*@date     2018/5/4
*/
static void spi1_NVIC_config(void)
{
#if (0)
  NVIC_InitTypeDef  NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);      //
  NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
#endif
}
/**
*@function void spi1_gpio_config(void)
*@brief    spi管脚配置
*@return   无
*@date     2018/5/4
*/
static void spi1_gpio_config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*! Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO,
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /*!< Configure SPI_FLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*!< Configure SPI_FLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);



  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**
*@function void spi1_parameter_config(void)
*@brief    spi参数配置
*@return   无
*@date     2018/5/4
*/
static void spi1_parameter_config(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  /*! SPI1 configuration */
  // W25X16: data input on the DIO pin is sampled on the rising edge of the CLK.
  // Data on the DO and DIO pins are clocked out on the falling edge of CLK.
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_Cmd(SPI1, ENABLE);
}
/**
*@function uint8_t spi_set_get_data(uint8_t byte)
*@brief    spi写入和读取函数，全双工读写
*@param    byte：写入值
*@return   读取值
*@date     2018/5/7
*/
uint8_t spi_send_get_data(uint8_t sendByte,uint8_t *getByte)
{
  #define SPI_DELAY_TIME 10000
  uint16_t i,spiGetData;
  i = 0;
  //* Loop while DR register in not emplty */
  while ((SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) && (++i < SPI_DELAY_TIME));

  // 判断发while是否正常退出
  if (i  >= SPI_DELAY_TIME) 
    return 0;

  //* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, sendByte);

  //* Wait to receive a byte */
  i = 0;
  while ((SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) && (++i < SPI_DELAY_TIME));
  // 判断while是否正常退出
  if (i >= SPI_DELAY_TIME) 
    return 0;
  //* Return the byte read from the SPI bus */
  //return SPI_I2S_ReceiveData(SPI1);
  spiGetData = SPI_I2S_ReceiveData(SPI1);
  *getByte = (uint8_t) spiGetData;
  return 1;
}

/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/





