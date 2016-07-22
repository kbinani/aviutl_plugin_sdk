//----------------------------------------------------------------------------------
//		�T���v���I�[�f�B�I�t�B���^(�t�B���^�v���O�C��)  for AviUtl ver0.96c�ȍ~
//----------------------------------------------------------------------------------
#include <windows.h>

#include "filter.h"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	1		//	�g���b�N�o�[�̐�
static TCHAR	*track_name[] =		{	"���x��"	};
static int		track_default[] =	{	256			};

#define	CHECK_N	0		//	�`�F�b�N�{�b�N�X�̐�

FILTER_DLL filter = {
	FILTER_FLAG_PRIORITY_HIGHEST|FILTER_FLAG_AUDIO_FILTER|FILTER_FLAG_EX_INFORMATION,
	0,0,
	"���ʂ̒���",
	TRACK_N,track_name,track_default,
	NULL,NULL,
	NULL,NULL,NULL,
	func_proc,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,NULL,
	NULL,
	NULL,
	"���ʂ̒��� version 0.03 by �j�d�m����",
	NULL,
	NULL,
};


//---------------------------------------------------------------------
//		�t�B���^�\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable( void )
{
	return &filter;
}


//---------------------------------------------------------------------
//		�t�B���^�����֐�
//---------------------------------------------------------------------
static BOOL func_proc( FILTER *fp,FILTER_PROC_INFO *fpip )
{
	int		i;

	//	���ʂ�ύX����
	for(i=0;i<fpip->audio_n*fpip->audio_ch;i++) {
		fpip->audiop[i] = (short)(fpip->audiop[i]*fp->track[0]/256);
	}

	return TRUE;
}


