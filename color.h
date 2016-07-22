//----------------------------------------------------------------------------------
//	�F�ϊ��v���O�C�� �w�b�_�[�t�@�C�� for AviUtl version 0.99h �ȍ~
//	By �j�d�m����
//----------------------------------------------------------------------------------

//	YC�\����
#ifndef PIXEL_YC
typedef	struct {
	short	y;					//	��f(�P�x    )�f�[�^ (     0 �` 4096 )
	short	cb;					//	��f(�F��(��))�f�[�^ ( -2048 �` 2048 )
	short	cr;					//	��f(�F��(��))�f�[�^ ( -2048 �` 2048 )
								//	��f�f�[�^�͔͈͊O�ɏo�Ă��邱�Ƃ�����܂�
								//	�܂��͈͓��Ɏ��߂Ȃ��Ă����܂��܂���
} PIXEL_YC;
#endif

//	�}���`�X���b�h�֐��p�̒�`
typedef void (*MULTI_THREAD_FUNC)( int thread_id,int thread_num,void *param1,void *param2 );
								//	thread_id	: �X���b�h�ԍ� ( 0 �` thread_num-1 )
								//	thread_num	: �X���b�h�� ( 1 �` )
								//	param1		: �ėp�p�����[�^
								//	param2		: �ėp�p�����[�^

//	�F�ϊ��̏������\����
typedef struct {
	int			flag;			//	�t���O
								//	COLOR_PROC_INFO_FLAG_INVERT_HEIGHT	: pixelp�̏c�������㉺�t�ɏ�������
								//	COLOR_PROC_INFO_FLAG_USE_SSE		: SSE�g�p
								//	COLOR_PROC_INFO_FLAG_USE_SSE2		: SSE2�g�p
	PIXEL_YC	*ycp;			//	PIXEL_YC�\���̂ւ̃|�C���^
	void 		*pixelp;		//	DIB�`���f�[�^�ւ̃|�C���^
	DWORD 		format; 		//	DIB�`���f�[�^�̃t�H�[�}�b�g( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 / 'Y''C''4''8' = PIXEL_YC )
	int			w,h;			//	�摜�f�[�^�̏c���T�C�Y
	int			line_size;		//	PIXEL_YC�\���̂̉����̃o�C�g�T�C�Y
	int			yc_size;		//	PIXEL_YC�\���̂̉�f�̃o�C�g�T�C�Y
	BOOL		(*exec_multi_thread_func)( MULTI_THREAD_FUNC func,void *param1,void *param2 );
								//	�w�肵���֐����V�X�e���̐ݒ�l�ɉ������X���b�h���ŌĂяo���܂�
								//	�Ăяo���ꂽ�֐�������Win32API��O���֐����g�p���Ȃ��ł�������
								//	func	: �}���`�X���b�h�ŌĂяo���֐�
								//	param1 	: �Ăяo���֐��ɓn���ėp�p�����[�^
								//	param2 	: �Ăяo���֐��ɓn���ėp�p�����[�^
								//  �߂�l	: TRUE�Ȃ琬��
	int			reserve[16];
} COLOR_PROC_INFO;

#define COLOR_PROC_INFO_FLAG_INVERT_HEIGHT	1
#define COLOR_PROC_INFO_FLAG_USE_SSE		256
#define COLOR_PROC_INFO_FLAG_USE_SSE2		512

//	�F�ϊ��v���O�C���\����
typedef struct {
	int		flag;				//	�t���O
	LPSTR	name;				//	�v���O�C���̖��O
	LPSTR	information;		//	�v���O�C���̏��
	BOOL 	(*func_init)( void );
								//	DLL�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	BOOL 	(*func_exit)( void );
								//	DLL�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
	BOOL 	(*func_pixel2yc)( COLOR_PROC_INFO *cpip );
								//	DIB�`���̉摜���炩��PIXEL_YC�`���̉摜�ɕϊ����܂� (NULL�Ȃ�Ă΂�܂���)
								//  �߂�l		: TRUE�Ȃ琬��
								//				: FALSE�Ȃ�AviUtl���Ńf�t�H���g�ϊ�����܂�
	BOOL 	(*func_yc2pixel)( COLOR_PROC_INFO *cpip );
								//	PIXEL_YC�`���̉摜���炩��DIB�`���̉摜�ɕϊ����܂� (NULL�Ȃ�Ă΂�܂���)
								//  �߂�l		: TRUE�Ȃ琬��
								//				: FALSE�Ȃ�AviUtl���Ńf�t�H���g�ϊ�����܂�
	int		reserve[16];
} COLOR_PLUGIN_TABLE;

BOOL func_init( void );
BOOL func_exit( void );
BOOL func_pixel2yc( COLOR_PROC_INFO *cpip );
BOOL func_yc2pixel( COLOR_PROC_INFO *cpip );


