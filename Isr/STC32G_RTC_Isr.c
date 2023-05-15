#include	"STC32G_RTC.h"

bit B_1S;
bit B_Alarm;

//========================================================================
// ����: RTC_ISR_Handler
// ����: RTC�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-21
//========================================================================
void RTC_ISR_Handler (void) interrupt RTC_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(RTCIF & 0x80)    //�����ж�
	{
		P01 = !P01;
		RTCIF &= ~0x80;
		B_Alarm = 1;
	}

	if(RTCIF & 0x08)    //���ж�
	{
		P00 = !P00;
		RTCIF &= ~0x08;
		B_1S = 1;
	}
}


