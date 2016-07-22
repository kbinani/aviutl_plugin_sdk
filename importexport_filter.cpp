//---------------------------------------------------------------------------------------------
//		�T���v��IMPORT&EXPORT�v���O�C��(�t�B���^�v���O�C��)  for AviUtl ver0.96c�ȍ~
//---------------------------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>

#include "filter.h"

#define	FILE_TXT		"TextFile (*.txt)\0*.txt\0AllFile (*.*)\0*.*\0"


//---------------------------------------------------------------------
//		�t�B���^�\���̒�`
//---------------------------------------------------------------------
FILTER_DLL filter = {
	FILTER_FLAG_IMPORT|FILTER_FLAG_EXPORT|FILTER_FLAG_NO_CONFIG|FILTER_FLAG_ALWAYS_ACTIVE|FILTER_FLAG_PRIORITY_LOWEST|FILTER_FLAG_EX_INFORMATION,
	0,0,
	"24fps����",
	NULL,NULL,NULL,
	NULL,NULL,
	NULL,NULL,NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	func_WndProc,
	NULL,NULL,
	NULL,
	NULL,
	"24fps����Import&Export version 0.01 by �j�d�m����",
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
//		WndProc
//---------------------------------------------------------------------
BOOL func_WndProc( HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam,void *editp,FILTER *fp )
{
	//	TRUE��Ԃ��ƑS�̂��ĕ`�悳���

	int				i,j,k,l,n;
	TCHAR			buf[MAX_PATH],*bp;
	FRAME_STATUS	fs;
	FILE			*fh;

	//	�ҏW���łȂ���Ή������Ȃ�
	if( fp->exfunc->is_editing(editp) != TRUE ) return FALSE;

	switch(message) {
		case WM_FILTER_IMPORT:
			if( fp->exfunc->dlg_get_load_name(buf,FILE_TXT,NULL) != TRUE ) break;
			if( (fh=fopen(buf,"r")) == NULL ) return FALSE;
			n = fp->exfunc->get_frame_n(editp);
			k = 0,l = 0;
			for(i=0;i<n;i++) {
				if( i == k ) {
					j = l;
					if( fgets(buf,sizeof(buf),fh) != NULL ) {
						for(bp=buf;*bp&&*bp!=',';bp++);
						if( bp ) bp++;
						k = atoi(buf);
						l = atoi(bp);
					}
				}
				fp->exfunc->get_frame_status(editp,i,&fs);
				if( fs.index24fps != j ) {
					fs.index24fps = j;
					fp->exfunc->set_frame_status(editp,i,&fs);
				}
				j = (j+1)%5;
			}
			fclose(fh);
			return TRUE;
		case WM_FILTER_EXPORT:
			if( fp->exfunc->dlg_get_save_name(buf,FILE_TXT,NULL) != TRUE ) break;
			if( (fh=fopen(buf,"w")) == NULL ) return FALSE;
			n = fp->exfunc->get_frame_n(editp);
			j = 0;
			for(i=0;i<n;i++) {
				fp->exfunc->get_frame_status(editp,i,&fs);
				if( j != fs.index24fps ) {
					j = fs.index24fps;
					wsprintf(buf,"%d,%d\n",i,j);
					fputs(buf,fh);
				}
				j = (j+1)%5;
			}
			fclose(fh);
			break;
	}

	return FALSE;
}


