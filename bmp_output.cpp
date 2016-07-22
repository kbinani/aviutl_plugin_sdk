//----------------------------------------------------------------------------------
//		�T���v��BMP�o�̓v���O�C��(�o�̓v���O�C��)  for AviUtl ver0.98�ȍ~
//----------------------------------------------------------------------------------
#include <windows.h>

#include "output.h"
#include "bmp_output.h"


//---------------------------------------------------------------------
//		�o�̓v���O�C���\���̒�`
//---------------------------------------------------------------------
OUTPUT_PLUGIN_TABLE output_plugin_table = {
	NULL,												//	�t���O
	"�A��BMP�o��",										//	�v���O�C���̖��O
	"BmpFile (*.bmp)\0*.bmp\0AllFile (*.*)\0*.*\0",		//	�o�̓t�@�C���̃t�B���^
	"�A��BMP�o�� version 0.06 By �j�d�m����",			//	�v���O�C���̏��
	NULL,												//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	NULL,												//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_output,										//	�o�͎��ɌĂ΂��֐��ւ̃|�C���^
	func_config,										//	�o�͐ݒ�̃_�C�A���O��v�����ꂽ���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_config_get,									//	�o�͐ݒ�f�[�^���擾���鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_config_set,									//	�o�͐ݒ�f�[�^��ݒ肷�鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
};


//---------------------------------------------------------------------
//		�o�̓v���O�C���\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C OUTPUT_PLUGIN_TABLE __declspec(dllexport) * __stdcall GetOutputPluginTable( void )
{
	return &output_plugin_table;
}


//---------------------------------------------------------------------
//		�o�̓v���O�C�������ϐ�
//---------------------------------------------------------------------
typedef struct {
	TCHAR	name[256];
} CONFIG;
static CONFIG	config = {"_%04d"};


//---------------------------------------------------------------------
//		�o�̓v���O�C���o�͊֐�
//---------------------------------------------------------------------
//
//	oip->flag;				// �t���O
//							// OUTPUT_INFO_FLAG_VIDEO	: �摜�f�[�^����
//							// OUTPUT_INFO_FLAG_AUDIO	: �����f�[�^����
//	oip->w,oip->h;			// �c���T�C�Y
//	oip->rate,oip->scale;	// �t���[�����[�g
//	oip->n;					// �t���[����
//	oip->size;				// �P�t���[���̃o�C�g��
//	oip->audio_rate;		// �����T���v�����O���[�g
//	oip->audio_ch;			// �����`�����l����
//	oip->audio_n;			// �����T���v�����O��
//	oip->audio_size;		// �����P�T���v���̃o�C�g��
//	oip->savefile;			// �Z�[�u�t�@�C�����ւ̃|�C���^
//
//	void *oip->func_get_video( int frame );
//							// DIB�`��(RGB24bit)�̉摜�f�[�^�ւ̃|�C���^���擾���܂��B
//							// frame	: �t���[���ԍ�
//							// �߂�l	: �f�[�^�ւ̃|�C���^
//	void *oip->func_get_audio( int start,int length,int *readed );
//							// 16bitPCM�`���̉����f�[�^�ւ̃|�C���^���擾���܂��B
//							// start	: �J�n�T���v���ԍ�
//							// length	: �ǂݍ��ރT���v����
//							// readed	: �ǂݍ��܂ꂽ�T���v����
//							// �߂�l	: �f�[�^�ւ̃|�C���^
//	BOOL oip->func_is_abort( void );
//							// ���f���邩���ׂ܂��B
//							// �߂�l	: TRUE�Ȃ璆�f
//	BOOL oip->func_rest_time_disp( int now,int total );
//							// �c�莞�Ԃ�\�������܂��B
//							// now		: �������Ă���t���[���ԍ�
//							// total	: �������鑍�t���[����
//							// �߂�l	: TRUE�Ȃ琬��
//	int oip->func_get_flag( int frame );
//							//	�t���O���擾���܂��B
//							//	frame	: �t���[���ԍ�
//							//	�߂�l	: �t���O
//							//  OUTPUT_INFO_FRAME_FLAG_KEYFRAME		: �L�[�t���[������
//							//  OUTPUT_INFO_FRAME_FLAG_COPYFRAME	: �R�s�[�t���[������
//	BOOL oip->func_update_preview( void );
//							//	�v���r���[��ʂ��X�V���܂��B
//							//	�Ō��func_get_video�œǂݍ��܂ꂽ�t���[�����\������܂��B
//							//	�߂�l	: TRUE�Ȃ琬��
//
BOOL func_output( OUTPUT_INFO *oip )
{
	int					i;
	TCHAR				path[MAX_PATH],name[MAX_PATH],ext[MAX_PATH],buf[MAX_PATH],*p,*p2,*p3;
	HANDLE				fp;
	DWORD				dw;
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	void				*pixelp;

	//	BMP�w�b�_�[�쐬
	ZeroMemory(&bmfh,sizeof(bmfh));
	bmfh.bfType    = 'B'+'M'*256;
	bmfh.bfSize    = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+oip->size;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	ZeroMemory(&bmih,sizeof(bmih));
	bmih.biSize        = sizeof(bmih);
	bmih.biWidth       = oip->w;
	bmih.biHeight      = oip->h;
	bmih.biPlanes      = 1;
	bmih.biBitCount    = 24;
	bmih.biCompression = BI_RGB;

	//	�A�ԃt�@�C�����̏���
	lstrcpy(path,oip->savefile);
	p2 = p3 = NULL;
	for(p=path;*p;p++) {
		if(*p=='\\') p2=p+1;
		if(*p=='.' ) p3=p;
	}
	if( p2 == NULL ) p2 = path;
	if( p3 == NULL ) p3 = p;
	lstrcpy(ext,p3);
	*p3 = NULL;
	lstrcpy(name,p2);

	//	BMP�o��
	for(i=0;i<oip->n;i++) {
		if( oip->func_is_abort() ) break;
		oip->func_rest_time_disp(i,oip->n);
		pixelp = oip->func_get_video_ex(i,NULL);
		wsprintf(buf,config.name,i);
		wsprintf(p2,"%s%s%s",name,buf,ext);
		if( (fp=CreateFile(path,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE ) return FALSE;
		WriteFile(fp,&bmfh,sizeof(bmfh),&dw,NULL);
		WriteFile(fp,&bmih,sizeof(bmih),&dw,NULL);
		WriteFile(fp,pixelp,oip->size,&dw,NULL);
		CloseHandle(fp);
		if( dw == 0 ) return FALSE;
		oip->func_update_preview();
	}

	return TRUE;
}


//---------------------------------------------------------------------
//		�o�̓v���O�C���ݒ�֐�
//---------------------------------------------------------------------
LRESULT CALLBACK func_config_proc( HWND hdlg,UINT umsg,WPARAM wparam, LPARAM lparam )
{
	switch( umsg ) {
		case WM_INITDIALOG:
			SetDlgItemText(hdlg,IDC_EDIT0,config.name);
			return TRUE;
		case WM_COMMAND:
			switch( LOWORD(wparam) ) {
				case IDCANCEL:
					EndDialog(hdlg,LOWORD(wparam));
					break;
				case IDOK:
					GetDlgItemText(hdlg,IDC_EDIT0,config.name,sizeof(config.name));
					EndDialog(hdlg,LOWORD(wparam));
					break;
			}
			break;
	}
	return FALSE;
}

BOOL func_config( HWND hwnd,HINSTANCE dll_hinst )
{
	DialogBox(dll_hinst,"CONFIG",hwnd,(DLGPROC)func_config_proc);
	return TRUE;
}

int func_config_get( void *data,int size )
{
	if( data ) memcpy(data,&config,sizeof(config));
	return sizeof(config);
}

int func_config_set( void *data,int size )
{
	if( size != sizeof(config) ) return NULL;
	memcpy(&config,data,size);
	return size;
}


