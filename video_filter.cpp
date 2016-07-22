//----------------------------------------------------------------------------------
//		�T���v���r�f�I�t�B���^(�t�B���^�v���O�C��)  for AviUtl ver0.99e�ȍ~
//----------------------------------------------------------------------------------
#include <windows.h>

#include "filter.h"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	3														//	�g���b�N�o�[�̐�
TCHAR	*track_name[] =		{	"track0",	"track1",	"track2"	};	//	�g���b�N�o�[�̖��O
int		track_default[] =	{	0,			0,			0			};	//	�g���b�N�o�[�̏����l
int		track_s[] =			{	-999,		-999,		-999		};	//	�g���b�N�o�[�̉����l
int		track_e[] =			{	+999,		+999,		+999		};	//	�g���b�N�o�[�̏���l

#define	CHECK_N	2														//	�`�F�b�N�{�b�N�X�̐�
TCHAR	*check_name[] = 	{	"check0",	"check1"	};				//	�`�F�b�N�{�b�N�X�̖��O
int		check_default[] = 	{	0,			0			};				//	�`�F�b�N�{�b�N�X�̏����l (�l��0��1)

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
	"�T���v���t�B���^",			//	�t�B���^�̖��O
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
	"�T���v���t�B���^ version 0.06 by �j�d�m����",
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
//	���L�̂悤�ɂ����1��auf�t�@�C���ŕ����̃t�B���^�\���̂�n�����Ƃ��o���܂�
/*
FILTER_DLL *filter_list[] = {&filter,&filter2,NULL};
EXTERN_C FILTER_DLL __declspec(dllexport) ** __stdcall GetFilterTableList( void )
{
	return (FILTER_DLL **)&filter_list;
}
*/


//---------------------------------------------------------------------
//		�t�B���^�����֐�
//---------------------------------------------------------------------
BOOL func_proc( FILTER *fp,FILTER_PROC_INFO *fpip )
{
//
//	fp->track[n]			: �g���b�N�o�[�̐��l
//	fp->check[n]			: �`�F�b�N�{�b�N�X�̐��l
//	fpip->w 				: ���ۂ̉摜�̉���
//	fpip->h 				: ���ۂ̉摜�̏c��
//	fpip->max_w				: �摜�̈�̉���
//	fpip->max_h				: �摜�̈�̏c��
//	fpip->ycp_edit			: �摜�̈�ւ̃|�C���^
//	fpip->ycp_temp			: �e���|�����̈�ւ̃|�C���^
//	fpip->ycp_edit[n].y		: ��f(�P�x    )�f�[�^ (     0 �` 4096 )
//	fpip->ycp_edit[n].cb	: ��f(�F��(��))�f�[�^ ( -2048 �` 2048 )
//	fpip->ycp_edit[n].cr	: ��f(�F��(��))�f�[�^ ( -2048 �` 2048 )
//
//  ��f�f�[�^�͔͈͊O�ɏo�Ă��邱�Ƃ�����܂��B
//  �܂��͈͓��Ɏ��߂Ȃ��Ă����܂��܂���B
//
//	�摜�T�C�Y��ς������Ƃ��� fpip->w �� fpip->h ��ς��܂��B
//
//	�e���|�����̈�ɏ��������摜���i�[�������Ƃ���
//	fpip->ycp_edit �� fpip->ycp_temp �����ւ��܂��B
//
	int			x,y;
	PIXEL_YC	*ycp,*ycp2;

	//	�e�v�f�Ƀg���b�N�o�[�̒l�𑫂�����
	for(y=0;y<fpip->h;y++) {
		ycp = fpip->ycp_edit + y*fpip->max_w;
		for(x=0;x<fpip->w;x++) {
			ycp->y  += (short)fp->track[0];
			ycp->cb += (short)fp->track[1];
			ycp->cr += (short)fp->track[2];
			ycp++;
		}
	}

	//	check0���`�F�b�N����Ă����牡������1/2�ɏk��
	if( fp->check[0] ) {
		for(y=0;y<fpip->h;y++) {
			ycp  = fpip->ycp_edit + y*fpip->max_w;
			ycp2 = fpip->ycp_temp + y*fpip->max_w;
			for(x=0;x<fpip->w/2;x++) {
				ycp2->y  = (short)(( ycp[0].y  + ycp[1].y  )/2);
				ycp2->cb = (short)(( ycp[0].cb + ycp[1].cb )/2);
				ycp2->cr = (short)(( ycp[0].cr + ycp[1].cr )/2);
				ycp+=2;
				ycp2++;
			}
		}
		//	���𔼕��ɂ����̂� fpip->w �𔼕��ɂ���
		fpip->w /= 2;
		//	fpip->ycp_temp �ɏ��������f�[�^���������񂾂̂�
		//	fpip->ycp_edit �� fpip->ycp_temp �����ւ���
		ycp = fpip->ycp_edit;
		fpip->ycp_edit = fpip->ycp_temp;
		fpip->ycp_temp = ycp;
	}

	//	check1���`�F�b�N����Ă�����摜��1/2�ɏk���������̂𒆉��ɔ������ŕ\��
	if( fp->check[1] ) {
		//	fpip->ycp_temp �� fpip->ycp_edit ��1/2�ɏk���������̂��쐬
		fp->exfunc->resize_yc(fpip->ycp_temp,fpip->w/2,fpip->h/2,fpip->ycp_edit,0,0,fpip->w,fpip->h);
		//	fpip->ycp_temp �� fpip->ycp_edit �̒����ɔ������ŕ`��
		fp->exfunc->copy_yc(fpip->ycp_edit,fpip->w/4,fpip->w/4,fpip->ycp_temp,0,0,fpip->w/2,fpip->h/2,2048);
	}

	return TRUE;
}


