
//�����ӿ�����
//�汾��V0.1
//����޸�ʱ�䣺2018��5��9��
//-------------------------------------------------------------------------------------------------------------------------------------------- 
//��������  
//��1������λ���Լ�IC-3173�Ӿ�����������������ݶ�����Send��Receive��ͷ
// (2) �ʹ������Լ���λ��ֱ�����豸�����Ķ�����Set/set����Get��ͷ 

// -------------------------------485----------
void GetBatteryInfo(void);//��ȡ������ݣ����� float��ѹ��float�������Լ����� 

//---------------------------------GPIO/EXTI----------------------- 
//�豸����-�������߹رռ����״�ȵ� 
void SetFan(1,enable);//�򿪷���,�β�Ϊ��ţ�����˵1�ŷ��� /disable 
void SetRadar(1,enable);//���״� or disableĬ��ֻ��һ���״� 

//����LED��״̬������ֻ������LED�� 
void SetTopLed(choice);//����on-2����˸ blinking-1���ر�off-0 ��ǰdefine 
void SetMidLed(choice);//����2����˸1���ر�0 
void SetRgbLed(color,choice);//����2��ѡ��R/G/B?������˸1���ر�0  ò��Ҫ����IOȥ���� 

//��ȡ��������״̬

int32_t GetEncoderRelativePosition(void) ;//����������λ�� 
int32_t GetEncoderAbsolutePosition(void) ;//����������λ�� 
void ResetEncoderRelativePosition(void) ;//�������������λ�� ���� 
void ResetEncoderAbsolutePosition(void) ;//����������λ�� ���� 

//��ȡ��������������״̬------------------------------------------------------------------------------------------------------------------------------------ 
u8 GetSickSensorState(void);//��翪�ص�ֵ--ע�⣺��翪�ص��жϷ���Ӧ�������벶���жϣ������Чʱ����������������λ�����㣬���������Ӽ�1 
u16 GetSickNum(void); //��ȡ���ļ���ֵ
void ResetSickNum(void);
u8 GetBackFrontSensorState(void);//��ȡǰ����ϴ�������ֵ��
float GetBoardTemperature(void);//��һ��PT100���¶� ,���PT100��װ�ڵ�·���� 
float GetICTemperature(void);//�ڶ���PT100���¶ȣ����PT100��װ��IC-3173�� 



//���ͻ�������źŸ�IC3173
void SendHomingCompletingSignal_to_IC3173(void);//1������ԭ�㣬��Ӧ��GPIO����ߵ�ƽ��0����δ�ﵽԭ�㣬��Ӧ��GPIO����͵�ƽ,��Ҫ���ڻ�������С�

//��ȡԭ�㿪���ź�---ģʽ����Ϊhoming�Լ���翪��Ϊ�ߵ�ƽ�ұ�����������������ֵ��EncThreshod�����壩 #define EncThreshod 300 �������������������ʱ���ڿ�����������ߵ�ƽ
//Ӧ�����жϷ���������洦�� 
//���ն�����ʵ�����º���
void SetLimitSwitch(enbale);//disable���ӵ������������LimitSwitch�ܽ�����ߵ͵�ƽ 


 


///-------------------------------CAN--RS232--Motor-------------------------------------------------------------- 
void SetCAN(enable) ;//NMT enable/disable
void SetMotor(enable);//ʹ�ܵ��or disable 
void SetMotorTargetPosVel(position,velocity);
void SetMotorADcceleration(acceleration,deceleration);


//��ȡ����˶����� 
 typedef struct motordata{
 	int32_t position;
 	float velocity;
 }MotorPosVel;
 //���positon��velocity��ȫ�ֱ��� 
MotorPosVel GetMotorPosVel(void);// ����һ���ṹ�壬 
void ResetMotorPos(void);
 xx GetMotorCurrent(void);//��ȡ��������� 





 

 


//--------------------------------TCP/IP-----JSON��ʽ---------------------- 
//������λ������
ReceiveCommand_from_Server();//����һ���ṹ�壬 json���ݸ�ʽ����
{
"RobotStatus": {
	"RunStatus": "Auto",		// Stop, Auto, Charging, Jog
"CurrentTime": "2017-10-13 17:27:30",
"CurrentPosition":2010,		// I32
"CurrentSpeed": 390,			// I16
"RunningCount": 10,			// U16
"CurrentTemp": 47,            // I8
"CurrentVoltage": 22.38     // Float(����ϵͳ��صĹ�����ѹ)
"CurrentAmp": 400.2         // Float������ϵͳ��صĹ���������
"CurrentDir": true         // true-����false-��
"ControlSystemEnergy": 50%   //float,��ʾ�ٷ���
"DynamicSystemEnergy": 60%   //float,��ʾ�ٷ���
}
}


//���Ʒ���ֻ��"�������"��"���Զ�"����ʱ����
{
"Response":{
"Command": "Jog",		// "Auto", "Set", "Stop"
 "Result": "OK"��		// "Error:"
} 
}




//�������ݸ���λ��
SendStatus_to_Server();//����һ���ṹ�壬 


//json��ʽ���� 
{
"RobotCommand": {
"Command": "Jog",		// "Auto", "Set", "Stop", "Forward", "Backward","Jog","Dot"
"Speed": 400,  			// I16
"RunCount":2,				// U16
"StartPosition": 0,		// I32
"EndPosition": 10000 , 	// I32
"TargetPosition":12000,  //I32
"WorkMode": "RealTime" ,      // "Regular", "Daily"
"Step": 20					// I16
}
}











 
