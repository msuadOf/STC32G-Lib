#include "STC32G_LCM.h"

//========================================================================
// ����: LCM_ISR_Handler
// ����: LCM �жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2022-03-23
//========================================================================
void LCM_ISR_Handler (void) interrupt LCM_VECTOR
{
	// TODO: �ڴ˴�����û�����
	if(LCMIFSTA & 0x01)
	{
		LCMIFSTA = 0x00;
//		LcmFlag = 0;
	}
}


