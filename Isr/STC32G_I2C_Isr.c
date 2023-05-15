#include	"STC32G_I2C.h"

I2C_IsrTypeDef I2CIsr;
bit DisplayFlag;

//========================================================================
// ����: I2C_ISR_Handler
// ����: I2C�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2020-09-23
//========================================================================
void I2C_ISR_Handler() interrupt I2C_VECTOR
{
	// TODO: �ڴ˴�����û�����

	// ����ģʽ
	I2CMSST &= ~0x40;       //I2Cָ������״̬���

	if(DMA_I2C_CR & 0x04)   //ACKERR
	{
		DMA_I2C_CR &= ~0x04;  //�����ݺ��յ�NAK
	}

	// �ӻ�ģʽ
	if (I2CSLST & 0x40)
	{
		I2CSLST &= ~0x40;                       //����START�¼�
	}
	else if (I2CSLST & 0x20)
	{
		I2CSLST &= ~0x20;                       //����RECV�¼���SLACKO����Ϊ0
		if (I2CIsr.isda)
		{
			I2CIsr.isda = 0;                           //����RECV�¼���RECV DEVICE ADDR��
		}
		else if (I2CIsr.isma)
		{
			I2CIsr.isma = 0;                           //����RECV�¼���RECV MEMORY ADDR��
			I2CIsr.addr = I2CRXD;
			I2CTXD = I2C_Buffer[I2CIsr.addr];
		}
		else
		{
			I2C_Buffer[I2CIsr.addr++] = I2CRXD;            //����RECV�¼���RECV DATA��
		}
	}
	else if (I2CSLST & 0x10)
	{
		I2CSLST &= ~0x10;                       //����SEND�¼�
		if (I2CSLST & 0x02)
		{
			I2CTXD = 0xff;
		}
		else
		{
			I2CTXD = I2C_Buffer[++I2CIsr.addr];
		}
	}
	else if (I2CSLST & 0x08)
	{
		I2CSLST &= ~0x08;                       //����STOP�¼�
		I2CIsr.isda = 1;
		I2CIsr.isma = 1;
		DisplayFlag = 1;
	}
}

