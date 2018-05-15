/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.c
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        ����w5500��tcpӦ�ó�
**************************************************************************************************
*/
#include "include.h"
uint8_t buff[1000];
uint16_t remote_port =  502;
uint8_t remote_ip[4] = {192,168,1,103};
/**
*@brief   TCP Server�ػ���ʾ������
*@param   ��
*@return  ��
*/
void do_tcp_server(void)
{
  uint16_t len=0;
  switch(getSn_SR(SOCK_TCPS))                                   /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                           /*socket���ڹر�״̬*/
      socket(SOCK_TCPS, Sn_MR_TCP, sDefaultNetConfig_.localPort, Sn_MR_ND);         /*��socket*/
      break;

    case SOCK_INIT:                                             /*socket�ѳ�ʼ��״̬*/
      listen(SOCK_TCPS);                                        /*socket��������*/
      break;

    case SOCK_ESTABLISHED:                                      /*socket�������ӽ���״̬*/
      if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPS, Sn_IR_CON);                         /*��������жϱ�־λ*/
      }
      len=getSn_RX_RSR(SOCK_TCPS);                              /*����lenΪ�ѽ������ݵĳ���*/
      if(len>0)
      {
        recv(SOCK_TCPS,buff,len);                               /*��������Client������*/
        send(SOCK_TCPS,buff,len -2);
      }
      break;
    case SOCK_CLOSE_WAIT:                                       /*socket���ڵȴ��ر�״̬*/

      close(SOCK_TCPS);
      break;
  }
}
/**
*@brief		TCP Client�ػ���ʾ������
*@param		��
*@return	��
*/
void do_tcp_client(void)
{	
   uint16_t len=0;	

	switch(getSn_SR(SOCK_TCPC))								  				         /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:											        		         /*socket���ڹر�״̬*/
			socket(SOCK_TCPC,Sn_MR_TCP,sDefaultNetConfig_.localPort++,Sn_MR_ND);
		  break;
		
		case SOCK_INIT:													        	         /*socket���ڳ�ʼ��״̬*/
			connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/ 
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket�������ӽ���״̬*/
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON); 							         /*��������жϱ�־λ*/
			}
		
			len=getSn_RX_RSR(SOCK_TCPC); 								  	         /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
				recv(SOCK_TCPC,buff,len); 							   		         /*��������Server������*/
				buff[len]=0x00;  											                 /*����ַ���������*/
				//printf("%s\r\n",buff);
				//send(SOCK_TCPC,buff,len -2);								     	         /*��Server��������*/
        rx_data_processing(buff,len,COM_TYPE_ETHERNET);
			}	
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPC);
		  break;

	}
}
