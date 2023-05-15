#include	"STC32G_LIN.h"

bit LinRxFlag;

//========================================================================
// ����: LIN_ISR_Handler
// ����: LIN�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-28
//========================================================================
void LIN_ISR_Handler (void) interrupt LIN_VECTOR
{
	u8 isr;
	u8 arTemp;
	arTemp = LINAR;     //LINAR �ֳ����棬������ѭ����д�� LINAR ������жϣ����ж����޸��� LINAR ����
	
	isr = LinReadReg(LSR);		//��ȡ�Ĵ������״̬��־λ
	if((isr & 0x03) == 0x03)
	{
		isr = LinReadReg(LER);
		if(isr == 0x00)		//No Error
		{
			LinRxFlag = 1;
		}
	}
	else
	{
		isr = LinReadReg(LER);	//��ȡ�������Ĵ���
	}

	LINAR = arTemp;    //LINAR �ֳ��ָ�
}


