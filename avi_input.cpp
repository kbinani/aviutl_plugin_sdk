//----------------------------------------------------------------------------------
//		�T���v��AVI(vfw�o�R)���̓v���O�C��  for AviUtl ver0.98�ȍ~
//----------------------------------------------------------------------------------
#include	<windows.h>
#include	<vfw.h>

#include	"input.h"


//---------------------------------------------------------------------
//		���̓v���O�C���\���̒�`
//---------------------------------------------------------------------
INPUT_PLUGIN_TABLE input_plugin_table = {
	INPUT_PLUGIN_FLAG_VIDEO|INPUT_PLUGIN_FLAG_AUDIO,	//	�t���O
														//	INPUT_PLUGIN_FLAG_VIDEO	: �摜���T�|�[�g����
														//	INPUT_PLUGIN_FLAG_AUDIO	: �������T�|�[�g����
	"AVI File Reader (sample)",							//	�v���O�C���̖��O
	"AviFile (*.avi)\0*.avi\0",							//	���̓t�@�C���t�B���^
	"AVI File Reader version 0.03 By �j�d�m����",		//	�v���O�C���̏��
	func_init,											//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_exit,											//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	func_open,											//	���̓t�@�C�����I�[�v������֐��ւ̃|�C���^
	func_close,											//	���̓t�@�C�����N���[�Y����֐��ւ̃|�C���^
	func_info_get,										//	���̓t�@�C���̏����擾����֐��ւ̃|�C���^
	func_read_video,									//	�摜�f�[�^��ǂݍ��ފ֐��ւ̃|�C���^
	func_read_audio,									//	�����f�[�^��ǂݍ��ފ֐��ւ̃|�C���^
	func_is_keyframe,									//	�L�[�t���[�������ׂ�֐��ւ̃|�C���^ (NULL�Ȃ�S�ăL�[�t���[��)
	func_config,										//	���͐ݒ�̃_�C�A���O��v�����ꂽ���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
};


//---------------------------------------------------------------------
//		���̓v���O�C���\���̂̃|�C���^��n���֐�
//---------------------------------------------------------------------
EXTERN_C INPUT_PLUGIN_TABLE __declspec(dllexport) * __stdcall GetInputPluginTable( void )
{
	return &input_plugin_table;
}


//---------------------------------------------------------------------
//		�t�@�C���n���h���\����
//---------------------------------------------------------------------
typedef struct {
	int				flag;
	PAVIFILE		pfile;
	PAVISTREAM		pvideo,paudio;
	AVIFILEINFO		fileinfo;
	AVISTREAMINFO	videoinfo,audioinfo;
	void			*videoformat;
	LONG			videoformatsize;
	void			*audioformat;
	LONG			audioformatsize;
} FILE_HANDLE;
#define FILE_HANDLE_FLAG_VIDEO		1
#define FILE_HANDLE_FLAG_AUDIO		2


//---------------------------------------------------------------------
//		������
//---------------------------------------------------------------------
BOOL func_init( void )
{
	AVIFileInit();
	return TRUE;
}


//---------------------------------------------------------------------
//		�I��
//---------------------------------------------------------------------
BOOL func_exit( void )
{
	AVIFileExit();
	return TRUE;
}


//---------------------------------------------------------------------
//		�t�@�C���I�[�v��
//---------------------------------------------------------------------
INPUT_HANDLE func_open( LPSTR file )
{
	FILE_HANDLE		*fp;
	int				i;
	PAVISTREAM		pas;
	AVISTREAMINFO	asi;

	fp = (FILE_HANDLE *)GlobalAlloc(GMEM_FIXED,sizeof(FILE_HANDLE));
	if( fp == NULL ) return NULL;
	ZeroMemory(fp,sizeof(FILE_HANDLE));

	if( AVIFileOpen(&fp->pfile,file,OF_READ,NULL) != 0 ) {
		GlobalFree(fp);
		return NULL;
	}

	if( AVIFileInfo(fp->pfile,&fp->fileinfo,sizeof(fp->fileinfo)) == 0 ) {
		for(i=0;i<fp->fileinfo.dwStreams;i++) {
			if( AVIFileGetStream(fp->pfile,&pas,0,i) == 0 ) {
				AVIStreamInfo(pas,&asi,sizeof(asi));
				if( asi.fccType == streamtypeVIDEO ) {
					//	�r�f�I�X�g���[���̐ݒ�
					fp->pvideo = pas;
					fp->videoinfo = asi;
					AVIStreamFormatSize(fp->pvideo,0,&fp->videoformatsize);
					fp->videoformat = (FILE_HANDLE *)GlobalAlloc(GMEM_FIXED,fp->videoformatsize);
					if( fp->videoformat ) {
						AVIStreamReadFormat(fp->pvideo,0,fp->videoformat,&fp->videoformatsize);
						fp->flag |= FILE_HANDLE_FLAG_VIDEO;
					} else {
						AVIStreamRelease(pas);
					}
				} else if( asi.fccType == streamtypeAUDIO ) {
					//	�I�[�f�B�I�X�g���[���̐ݒ�
					fp->paudio = pas;
					fp->audioinfo = asi;
					AVIStreamFormatSize(fp->paudio,0,&fp->audioformatsize);
					fp->audioformat = (FILE_HANDLE *)GlobalAlloc(GMEM_FIXED,fp->audioformatsize);
					if( fp->videoformat ) {
						AVIStreamReadFormat(fp->paudio,0,fp->audioformat,&fp->audioformatsize);
						fp->flag |= FILE_HANDLE_FLAG_AUDIO;
					} else {
						AVIStreamRelease(pas);
					}
				} else {
					AVIStreamRelease(pas);
				}
			}
		}
	}

	return fp;
}


//---------------------------------------------------------------------
//		�t�@�C���N���[�Y
//---------------------------------------------------------------------
BOOL func_close( INPUT_HANDLE ih )
{
	FILE_HANDLE	*fp = (FILE_HANDLE *)ih;

	if( fp ) {
		if( fp->flag&FILE_HANDLE_FLAG_AUDIO ) {
			AVIStreamRelease(fp->paudio);
			GlobalFree(fp->audioformat);
		}
		if( fp->flag&FILE_HANDLE_FLAG_VIDEO ) {
			AVIStreamRelease(fp->pvideo);
			GlobalFree(fp->videoformat);
		}
		AVIFileRelease(fp->pfile);
		GlobalFree(fp);
	}

	return TRUE;
}


//---------------------------------------------------------------------
//		�t�@�C���̏��
//---------------------------------------------------------------------
BOOL func_info_get( INPUT_HANDLE ih,INPUT_INFO *iip )
{
	FILE_HANDLE	*fp = (FILE_HANDLE *)ih;

	iip->flag = 0;

	if( fp->flag&FILE_HANDLE_FLAG_VIDEO ) {
		iip->flag |= INPUT_INFO_FLAG_VIDEO;
		iip->rate = fp->videoinfo.dwRate;
		iip->scale = fp->videoinfo.dwScale;
		iip->n = fp->videoinfo.dwLength;
		iip->format = (BITMAPINFOHEADER *)fp->videoformat;
		iip->format_size = fp->videoformatsize;
		iip->handler = fp->videoinfo.fccHandler;
	}

	if( fp->flag&FILE_HANDLE_FLAG_AUDIO ) {
		iip->flag |= INPUT_INFO_FLAG_AUDIO;
		iip->audio_n = fp->audioinfo.dwLength;
		iip->audio_format = (WAVEFORMATEX *)fp->audioformat;
		iip->audio_format_size = fp->audioformatsize;
	}

	return TRUE;
}


//---------------------------------------------------------------------
//		�摜�ǂݍ���
//---------------------------------------------------------------------
int func_read_video( INPUT_HANDLE ih,int frame,void *buf )
{
	FILE_HANDLE	*fp = (FILE_HANDLE *)ih;
	LONG		videosize;
	LONG		size;

	AVIStreamRead(fp->pvideo,frame,1,NULL,NULL,&videosize,NULL);
	if( AVIStreamRead(fp->pvideo,frame,1,buf,videosize,&size,NULL) ) return 0;
	return size;
}


//---------------------------------------------------------------------
//		�����ǂݍ���
//---------------------------------------------------------------------
int func_read_audio( INPUT_HANDLE ih,int start,int length,void *buf )
{
	FILE_HANDLE	*fp = (FILE_HANDLE *)ih;
	LONG		size;
	int			samplesize;

	samplesize = ((WAVEFORMATEX *)fp->audioformat)->nBlockAlign;
	if( AVIStreamRead(fp->paudio,start,length,buf,samplesize*length,NULL,&size) ) return 0;
	return size;
}


//---------------------------------------------------------------------
//		�L�[�t���[�����
//---------------------------------------------------------------------
BOOL func_is_keyframe( INPUT_HANDLE ih,int frame )
{
	FILE_HANDLE	*fp = (FILE_HANDLE *)ih;

	return AVIStreamIsKeyFrame(fp->pvideo,frame);
}


//---------------------------------------------------------------------
//		�ݒ�_�C�A���O
//---------------------------------------------------------------------
BOOL func_config( HWND hwnd,HINSTANCE dll_hinst )
{
	MessageBox(hwnd,"�T���v���_�C�A���O","���͐ݒ�",MB_OK);

	//	DLL���J������Ă��ݒ肪�c��悤�ɕۑ����Ă����Ă��������B

	return TRUE;
}


