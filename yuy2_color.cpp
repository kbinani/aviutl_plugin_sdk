//----------------------------------------------------------------------------------
//		�T���v��YUY2�F�ϊ��v���O�C��(�F�ϊ��v���O�C��)  for AviUtl ver0.99h�ȍ~
//----------------------------------------------------------------------------------
#include <windows.h>

#include "color.h"


//---------------------------------------------------------------------
//		�F�ϊ��v���O�C���\���̒�`
//---------------------------------------------------------------------
COLOR_PLUGIN_TABLE color_plugin_table = {
	NULL,												//	�t���O
	"�T���v��YUY2�ϊ�",									//	�v���O�C���̖��O
	"�T���v��YUY2�ϊ� version 0.01 By �j�d�m����",		//	�v���O�C���̏��
	NULL,												//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,												//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_pixel2yc,										//	DIB�`���̉摜���炩��PIXEL_YC�`���̉摜�ɕϊ����܂� (NULL�Ȃ�Ă΂�܂���)
	func_yc2pixel,										//	PIXEL_YC�`���̉摜���炩��DIB�`���̉摜�ɕϊ����܂� (NULL�Ȃ�Ă΂�܂���)
};


//---------------------------------------------------------------------
//		�F�ϊ��v���O�C���\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C COLOR_PLUGIN_TABLE __declspec(dllexport) * __stdcall GetColorPluginTable( void )
{
	return &color_plugin_table;
}
//	��GetColorPluginTableYUY2��YUY2�t�B���^���[�h�ɂ��Ή��ł��܂�


//---------------------------------------------------------------------
//		���͕ϊ�
//---------------------------------------------------------------------
BOOL func_pixel2yc( COLOR_PROC_INFO *cpip )
{
	int			x,y;
	PIXEL_YC	*ycp;
	BYTE		*pixelp;

	//	YUY2�ȊO��AviUtl�{�̂̕ϊ��ɔC����
	if( cpip->format != MAKEFOURCC('Y','U','Y','2') ) return FALSE;

	//	ITU-R BT.601�Ƃ��ĕϊ�
	for(y=0;y<cpip->h;y++) {
		ycp    = (PIXEL_YC *)( (BYTE *)cpip->ycp + y*cpip->line_size );
		pixelp = (BYTE *)cpip->pixelp + y*((cpip->w+1)/2*4);
		for(x=0;x<cpip->w;x+=2) {
			ycp->y  = (pixelp[0]-16 )*4096/219;
			ycp->cb = (pixelp[1]-128)*4096/224;
			ycp->cr = (pixelp[3]-128)*4096/224;
			ycp++;
			ycp->y  = (pixelp[2]-16 )*4096/219;
			ycp->cb = (pixelp[1]-128)*4096/224;
			ycp->cr = (pixelp[3]-128)*4096/224;
			ycp++;
			pixelp+=4;
		}
	}

	return TRUE;
}


//---------------------------------------------------------------------
//		�o�͕ϊ�
//---------------------------------------------------------------------
BYTE pack_byte( int val )
{
	if(      val < 0   ) val = 0;
	else if( val > 255 ) val = 255;
	return (BYTE)val;
}
BOOL func_yc2pixel( COLOR_PROC_INFO *cpip )
{
	int			x,y;
	PIXEL_YC	*ycp;
	BYTE		*pixelp;

	//	YUY2�ȊO��AviUtl�{�̂̕ϊ��ɔC����
	if( cpip->format != MAKEFOURCC('Y','U','Y','2') ) return FALSE;

	//	ITU-R BT.601�Ƃ��ĕϊ�
	for(y=0;y<cpip->h;y++) {
		ycp    = (PIXEL_YC *)( (BYTE *)cpip->ycp + y*cpip->line_size );
		pixelp = (BYTE *)cpip->pixelp + y*((cpip->w+1)/2*4);
		for(x=0;x<cpip->w;x+=2) {
			pixelp[0] = pack_byte( ycp->y *219/4096 + 16  );
			pixelp[1] = pack_byte( ycp->cb*224/4096 + 128 );
			pixelp[3] = pack_byte( ycp->cr*224/4096 + 128 );
			ycp++;
			pixelp[2] = pack_byte( ycp->y *219/4096 + 16  );
			ycp++;
			pixelp+=4;
		}
	}

	return TRUE;
}


