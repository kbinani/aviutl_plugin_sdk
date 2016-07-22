//---------------------------------------------------------------------
//		�T���v���C���^�[���[�X�����v���O�C��  for AviUtl ver0.98�ȍ~
//---------------------------------------------------------------------
#include	<windows.h>

#include	"filter.h"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	0
#define	CHECK_N	0

FILTER_DLL filter = {
	FILTER_FLAG_INTERLACE_FILTER|FILTER_FLAG_EX_INFORMATION|FILTER_FLAG_NO_CONFIG,
	0,0,
	"�T���v������",
	TRACK_N,NULL,NULL,
	NULL,NULL,
	CHECK_N,NULL,NULL,
	func_proc,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,NULL,
	NULL,
	NULL,
	"�T���v���C���^�[���[�X���� version 0.01 by �j�d�m����",
	NULL,NULL,
	NULL,NULL,NULL,
	NULL,
	func_is_saveframe
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
//
//	fp->track[n]			: �g���b�N�o�[�̐��l
//	fp->check[n]			: �`�F�b�N�{�b�N�X�̐��l
//	fpip->w 				: ���ۂ̉摜�̉���
//	fpip->h 				: ���ۂ̉摜�̏c��
//	fpip->max_w				: �摜�̈�̉���
//	fpip->max_h				: �摜�̈�̏c��
//	fpip->ycp_edit			: �摜�̈�ւ̃|�C���^
//	fpip->ycp_temp			: �e���|�����̈�ւ̃|�C���^
//	fpip->ycp_edit[n].y		: ��f(�P�x    )�f�[�^ (     0 �` 4095 )
//	fpip->ycp_edit[n].cb	: ��f(�F��(��))�f�[�^ ( -2048 �` 2047 )
//	fpip->ycp_edit[n].cr	: ��f(�F��(��))�f�[�^ ( -2048 �` 2047 )
//
//	�C���^�[���[�X�����t�B���^�͉摜�T�C�Y��ς�����
//	�摜�̈�ƃe���|�����̈�����ւ�����͏o���܂���B
//
//	�摜�̈�ɏ����摜�f�[�^�͓����Ă��܂���B
//	get_ycp_source_cache()���g���Ď����œǂݍ��ޕK�v������܂��B
//
	int			y;
	PIXEL_YC	*ycp,*ycp2,*p0;

	//	�C���^�[���[�X�����t�B���^��fpip->ycp_edit�ɂ̓f�[�^�������Ă��Ȃ��̂�
	//	get_ycp_source_cache()���g���Ď����œǂݍ��ށB
	p0 = (PIXEL_YC *)fp->exfunc->get_ycp_source_cache(fpip->editp,fpip->frame,0);

	//	�����
	for(y=0;y<fpip->h;y++) {
		ycp  = p0 + (y-(y&1))*fpip->max_w;
		ycp2 = fpip->ycp_edit + y*fpip->max_w;
		memcpy(ycp2,ycp,sizeof(PIXEL_YC)*fpip->w);
	}

	return TRUE;
}

BOOL func_is_saveframe( FILTER *fp,void *editp,int saveno,int frame,int fps,int edit_flag,int inter )
{
//	saveno		: �Z�[�u����͈͂̐擪����̃t���[���ԍ�
//	frame		: �ҏW�t���[���ԍ�
//	fps			: �t���[�����[�g�̕ύX�̐ݒ�l (30,24,20,15,10)
//	edit_flag	: �ҏW�t���O
//	inter		: �t���[���̃C���^�[���[�X
//
//	TRUE��Ԃ��ƕۑ��t���[���AFALSE��Ԃ��ƊԈ����t���[���ɂȂ�܂��B
//
	if( saveno*fps/30 - (saveno+1)*fps/30 ) return TRUE;
	return FALSE;
}


