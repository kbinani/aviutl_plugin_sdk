//---------------------------------------------------------------------------------------------
//		YUY2�t�B���^���[�h�Ή��T���v���t�B���^(�t�B���^�v���O�C��)  for AviUtl ver0.99a�ȍ~
//---------------------------------------------------------------------------------------------
//		YUY2�t�B���^���[�h�ɂ��Ă�AviUtl�̐����ȋ@�\�ł͂Ȃ�
//		�e�X�g�I�Ȃ��܂��@�\�Ƃ��čl���Ă��܂��̂�
//		�����Ă݂����l�̂ݑΉ������Ă��������B
//---------------------------------------------------------------------------------------------
#include <windows.h>

#include "filter.h"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
#define	TRACK_N	0														//	�g���b�N�o�[�̐�
#define	CHECK_N	0														//	�`�F�b�N�{�b�N�X�̐�

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
	"YUY2�t�B���^���[�h�Ή��T���v���t�B���^",	//	�t�B���^�̖��O
	TRACK_N,					//	�g���b�N�o�[�̐� (0�Ȃ疼�O�����l����NULL�ł悢)
	NULL,						//	�g���b�N�o�[�̖��O�S�ւ̃|�C���^
	NULL,						//	�g���b�N�o�[�̏����l�S�ւ̃|�C���^
	NULL,NULL,					//	�g���b�N�o�[�̐��l�̉������ (NULL�Ȃ�S��0�`256)
	CHECK_N,					//	�`�F�b�N�{�b�N�X�̐� (0�Ȃ疼�O�����l����NULL�ł悢)
	NULL,						//	�`�F�b�N�{�b�N�X�̖��O�S�ւ̃|�C���^
	NULL,						//	�`�F�b�N�{�b�N�X�̏����l�S�ւ̃|�C���^
	func_proc,					//	�t�B���^�����֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�ݒ肪�ύX���ꂽ�Ƃ��ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,						//	�ݒ�E�B���h�E�ɃE�B���h�E���b�Z�[�W���������ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,NULL,					//	�V�X�e���Ŏg���܂��̂Ŏg�p���Ȃ��ł�������
	NULL,						//  �g���f�[�^�̈�ւ̃|�C���^ (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
	NULL,						//  �g���f�[�^�T�C�Y (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
	"YUY2�t�B���^���[�h�Ή��T���v���t�B���^ version 0.01 by �j�d�m����",
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
//		YUY2�t�B���^�\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTableYUY2( void )
{
	return &filter;
}


//---------------------------------------------------------------------
//		�t�B���^�����֐�
//---------------------------------------------------------------------
BOOL func_proc( FILTER *fp,FILTER_PROC_INFO *fpip )
{
//
//	fpip->w 				: ���ۂ̉摜�̉���
//	fpip->h 				: ���ۂ̉摜�̏c��
//	fpip->max_w				: �摜�̈�̉���
//	fpip->max_h				: �摜�̈�̏c��
//	fpip->ycp_edit			: �摜�̈�ւ̃|�C���^
//	fpip->ycp_temp			: �e���|�����̈�ւ̃|�C���^
//	fpip->yc_size;			: �摜�̈�̉�f�̃o�C�g�T�C�Y ( �ʏ�t�B���^���[�h�� = 6 , YUY2�t�B���^���[�h�� = 2 )
//	fpip->line_size;		: �摜�̈�̕��̃o�C�g�T�C�Y

//	�t�B���^���[�h�ɂ���ĉ摜�̈�̉�f�̃t�H�[�}�b�g�͈Ⴂ�܂��B
//	�ʏ�t�B���^���[�h���͌^�ʂ��PIXEL_YC�`���ł���
//	YUY2�t�B���^���[�h���͓��e��YUY2�`���̃f�[�^�ɂȂ�܂��B
//	YUY2�`���ł͉������̉𑜓x��2�̔{���݂̂̑Ή��ɂȂ�܂��B
//
	int			x,y;
	PIXEL_YC	*ycp,*ycp2,*ycp3;
	BYTE		*p,*p2,*p3;

	//	�c������1/2�ɏk��
	if( fpip->yc_size == 2 ) {
		//	YUY2���[�h��
		for(y=0;y<fpip->h/2;y++) {
			p = (BYTE *)fpip->ycp_edit + y*fpip->line_size;
			p2 = (BYTE *)fpip->ycp_edit + y*2*fpip->line_size;
			p3 = p2 + fpip->line_size;
			for(x=0;x<fpip->w;x+=2) {
				p[0] = (unsigned char)(( p2[0] + p3[0] )/2);	//	Y0
				p[1] = (unsigned char)(( p2[1] + p3[1] )/2);	//	U0
				p[2] = (unsigned char)(( p2[2] + p3[2] )/2);	//	Y1
				p[3] = (unsigned char)(( p2[3] + p3[3] )/2);	//	V0
				p  += 4;
				p2 += 4;
				p3 += 4;
			}
		}
	} else {
		//	�ʏ탂�[�h��
		for(y=0;y<fpip->h/2;y++) {
			ycp = fpip->ycp_edit + y*fpip->max_w;
			ycp2 = fpip->ycp_edit + y*2*fpip->max_w;
			ycp3 = ycp2 + fpip->max_w;
			for(x=0;x<fpip->w;x++) {
				ycp->y  = (short)(( ycp2->y  + ycp3->y  )/2);
				ycp->cb = (short)(( ycp2->cb + ycp3->cb )/2);
				ycp->cr = (short)(( ycp2->cr + ycp3->cr )/2);
				ycp++;
				ycp2++;
				ycp3++;
			}
		}
	}

	//	���𔼕��ɂ����̂� fpip->w �𔼕��ɂ���
	fpip->h /= 2;

	return TRUE;
}


