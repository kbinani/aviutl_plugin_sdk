//---------------------------------------------------------------------------------------------
//		�}���`�X���b�h�Ή��T���v���t�B���^(�t�B���^�v���O�C��)  for AviUtl ver0.99a�ȍ~
//---------------------------------------------------------------------------------------------
#include <windows.h>

#include "filter.h"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	3														//	�g���b�N�o�[�̐�
TCHAR	*track_name[] =		{	"track0",	"track1",	"track2"	};	//	�g���b�N�o�[�̖��O
int		track_default[] =	{	512		,	0		,	0			};	//	�g���b�N�o�[�̏����l
int		track_s[] =			{	-999	,	-999	,	-999		};	//	�g���b�N�o�[�̉����l
int		track_e[] =			{	+999	,	+999	,	+999		};	//	�g���b�N�o�[�̏���l

#define	CHECK_N	4														//	�`�F�b�N�{�b�N�X�̐�
TCHAR	*check_name[] = 	{	"thread1"	,"thread2"	,"thread3"	,"thread4",	};	//	�`�F�b�N�{�b�N�X�̖��O
int		check_default[] = 	{	1			,1			,1			,1			};	//	�`�F�b�N�{�b�N�X�̏����l (�l��0��1)

FILTER_DLL filter = {
	FILTER_FLAG_EX_INFORMATION,	//	�t�B���^�̃t���O
								//	FILTER_FLAG_ALWAYS_ACTIVE		: �t�B���^����ɃA�N�e�B�u�ɂ��܂�
								//	FILTER_FLAG_CONFIG_POPUP		: �ݒ���|�b�v�A�b�v���j���[�ɂ��܂�
								//	FILTER_FLAG_CONFIG_CHECK		: �ݒ���`�F�b�N�{�b�N�X���j���[�ɂ��܂�
								//	FILTER_FLAG_CONFIG_RADIO		: �ݒ�����W�I�{�^�����j���[�ɂ��܂�
								//	FILTER_FLAG_EX_DATA				: �g���f�[�^��ۑ��o����悤�ɂ��܂��B
								//	FILTER_FLAG_PRIORITY_HIGHEST	: �t�B���^�̃v���C�I���e�B����ɍŏ�ʂɂ��܂�
								//	FILTER_FLAG_PRIORITY_LOWEST		: �t�B���^�̃v���C�I���e�B����ɍŉ��ʂɂ��܂�
								//	FILTER_FLAG_WINDOW_THICKFRAME	: �T�C�Y�ύX�\�ȃE�B���h�E�����܂�
								//	FILTER_FLAG_WINDOW_SIZE			: �ݒ�E�B���h�E�̃T�C�Y���w��o����悤�ɂ��܂�
								//	FILTER_FLAG_DISP_FILTER			: �\���t�B���^�ɂ��܂�
								//	FILTER_FLAG_EX_INFORMATION		: �t�B���^�̊g������ݒ�ł���悤�ɂ��܂�
								//	FILTER_FLAG_NO_CONFIG			: �ݒ�E�B���h�E��\�����Ȃ��悤�ɂ��܂�
								//	FILTER_FLAG_AUDIO_FILTER		: �I�[�f�B�I�t�B���^�ɂ��܂�
								//	FILTER_FLAG_RADIO_BUTTON		: �`�F�b�N�{�b�N�X�����W�I�{�^���ɂ��܂�
								//	FILTER_FLAG_WINDOW_HSCROLL		: �����X�N���[���o�[�����E�B���h�E�����܂�
								//	FILTER_FLAG_WINDOW_VSCROLL		: �����X�N���[���o�[�����E�B���h�E�����܂�
								//	FILTER_FLAG_IMPORT				: �C���|�[�g���j���[�����܂�
								//	FILTER_FLAG_EXPORT				: �G�N�X�|�[�g���j���[�����܂�
	0,0,						//	�ݒ�E�C���h�E�̃T�C�Y (FILTER_FLAG_WINDOW_SIZE�������Ă��鎞�ɗL��)
	"�}���`�X���b�h�T���v���t�B���^",			//	�t�B���^�̖��O
	TRACK_N,					//	�g���b�N�o�[�̐� (0�Ȃ疼�O�����l����NULL�ł悢)
	track_name,					//	�g���b�N�o�[�̖��O�S�ւ̃|�C���^
	track_default,				//	�g���b�N�o�[�̏����l�S�ւ̃|�C���^
	track_s,track_e,			//	�g���b�N�o�[�̐��l�̉������ (NULL�Ȃ�S��0�`256)
	CHECK_N,					//	�`�F�b�N�{�b�N�X�̐� (0�Ȃ疼�O�����l����NULL�ł悢)
	check_name,					//	�`�F�b�N�{�b�N�X�̖��O�S�ւ̃|�C���^
	check_default,				//	�`�F�b�N�{�b�N�X�̏����l�S�ւ̃|�C���^
	func_proc,					//	�t�B���^�����֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�ݒ肪�ύX���ꂽ�Ƃ��ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�ݒ�E�B���h�E�ɃE�B���h�E���b�Z�[�W���������ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,NULL,					//	�V�X�e���Ŏg���܂��̂Ŏg�p���Ȃ��ł�������
	NULL,						//  �g���f�[�^�̈�ւ̃|�C���^ (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
	NULL,						//  �g���f�[�^�T�C�Y (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
	"�}���`�X���b�h�T���v���t�B���^ version 0.01 by �j�d�m����",
								//  �t�B���^���ւ̃|�C���^ (FILTER_FLAG_EX_INFORMATION�������Ă��鎞�ɗL��)
	NULL,						//	�Z�[�u���J�n����钼�O�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�Z�[�u���I���������O�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
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
void multi_thread_func( int thread_id,int thread_num,void *param1,void *param2 )
{
//	thread_id	: �X���b�h�ԍ� ( 0 �` thread_num-1 )
//	thread_num	: �X���b�h�� ( 1 �` )
//	param1		: �ėp�p�����[�^
//	param2		: �ėp�p�����[�^
//
//	���̊֐�������Win32API��O���֐�(rgb2yc,yc2rgb�͏���)���g�p���Ȃ��ł��������B
//
	FILTER *fp				= (FILTER *)param1;
	FILTER_PROC_INFO *fpip	= (FILTER_PROC_INFO *)param2;

	int			x,y,y_start,y_end;
	PIXEL_YC	*ycp;

	//	�`�F�b�N�{�b�N�X���O��Ă���X���b�h�͏������Ȃ�
	if( fp->check[thread_id] == 0 ) return;

	//	�X���b�h���̉摜����������ꏊ���v�Z����
	y_start = ( fpip->h * thread_id     ) / thread_num;
	y_end   = ( fpip->h * (thread_id+1) ) / thread_num;

	//	�e�v�f�Ƀg���b�N�o�[�̒l�𑫂�����
	for(y=y_start;y<y_end;y++) {
		ycp = fpip->ycp_edit + y*fpip->max_w;
		for(x=0;x<fpip->w;x++) {
			ycp->y  += (short)fp->track[0];
			ycp->cb += (short)fp->track[1];
			ycp->cr += (short)fp->track[2];
			ycp++;
		}
	}
}


//---------------------------------------------------------------------
//		�t�B���^�����֐�
//---------------------------------------------------------------------
BOOL func_proc( FILTER *fp,FILTER_PROC_INFO *fpip )
{
	//	�}���`�X���b�h�Ńt�B���^�����֐����Ă�
	fp->exfunc->exec_multi_thread_func(multi_thread_func,(void *)fp,(void *)fpip);

	//	�����摜�̈�|�C���^�̓���ւ���𑜓x�ύX����
	//	fpip �̓��e��ς���ꍇ�͂�����̊֐����ŏ���������

	return TRUE;
}


