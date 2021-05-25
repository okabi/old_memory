// -------------------------------------------------------------------------------
// 
// 		�c�w���C�u����		�w�b�_�t�@�C��
// 
// 				Ver 2.25
// 
// -------------------------------------------------------------------------------

#ifndef __DXLIB
#define __DXLIB

// �c�w���C�u�����̃o�[�W����
#define DXLIB_VERSION 0x2250
#define DXLIB_VERSION_STR "2.25"

// �ݒ� -----------------------------------------------------------------------

// �c�w���C�u�����ɕK�v�� lib �t�@�C�����A�v���W�F�N�g�̃J�����g�t�H���_��
// �R���p�C���̃f�t�H���g LIB �p�X�ɐݒ肹���Ɏg�p�����ꍇ�͈ȉ���
// �R�����g���O���Ă�������
//#define DX_LIB_NOT_DEFAULTPATH

#ifndef __DX_MAKE

// �`��֘A�̊֐�����؎g�p����Ȃ��ꍇ�͈ȉ��̃R�����g���O���ĉ�����
//#define DX_NOTUSE_DRAWFUNCTION

#endif

// �^��` ---------------------------------------------------------------------

// �c�����������h���������̃o�[�W�����ݒ�
#define DIRECTINPUT_VERSION 0x700

#include <windows.h>
#include <stdio.h>

#ifndef DWORD_PTR
#define DWORD_PTR	DWORD
#endif

#ifndef LONG_PTR
#define LONG_PTR	DWORD
#endif

// �c�����������w�֘A��`�� ---------------------------------------------------

#include "DxDirectX.h"
/*
#ifdef DX_USE_DIRECTX_SDK_FILE
	#include <dinput.h>
	#include <ddraw.h>
	#include <d3d.h>
	#ifndef DX_NON_MOVIE
		#include <dshow.h>
	#endif
	#include <qedit.h>
	#include <stdio.h>
	#include <dsound.h>
	#include <dmusici.h>
#else
	#include "DxDirectX.h"
#endif
*/

// ���C�u���������N��`--------------------------------------------------------

#ifndef __DX_MAKE
	#ifndef DX_LIB_NOT_DEFAULTPATH
		#ifdef _DEBUG
			#pragma comment( lib, "DxLib_d.lib"		)			//  �c�w���C�u�����g�p�w��
			#pragma comment( lib, "DxUseCLib_d.lib"		)		//  �W���b���C�u�������g�p���镔���� lib �t�@�C���̎g�p�w��
			#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
		#else
			#pragma comment( lib, "DxLib.lib"		)			//  �c�w���C�u�����g�p�w��
			#pragma comment( lib, "DxUseCLib.lib"		)		//  �W���b���C�u�������g�p���镔���� lib �t�@�C���̎g�p�w��
			#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
		#endif

		//#pragma comment( lib, "GetDirectXVer" )
		//#pragma comment( lib, "ddraw.lib"		)				//  DirectDraw���C�u����
		//#pragma comment( lib, "dinput.lib"		)			//  DirectInput���C�u����
		//#pragma comment( lib, "dxguid.lib"		)			//  DirectX GUID���C�u����
		//#pragma comment( lib, "dsound.lib"		)			//  DirectSound���C�u����
		//#pragma comment( lib, "libcmt.lib"		)				//  C�W���}���`�X���b�h�Ή����C�u����
		#pragma comment( lib, "kernel32.lib"		)			//  Win32�J�[�l�����C�u����
		#pragma comment( lib, "comctl32.lib"		)			//�@Win32API�p���C�u����
		#pragma comment( lib, "user32.lib"		)				//  Win32API�p���C�u����
		#pragma comment( lib, "gdi32.lib"		)				//  Win32API�p���C�u����
		#pragma comment( lib, "advapi32.lib"		)			//  Win32API�p���C�u����
		#pragma comment( lib, "ole32.lib"		)				//  Win32API�p���C�u����
		#pragma comment( lib, "shell32.lib"		)				//  �}���`���f�B�A���C�u����
		#pragma comment( lib, "winmm.lib"		)				//  �}���`���f�B�A���C�u����
		#ifndef DX_NON_MOVIE
			//#pragma comment( lib, "Strmiids.lib" )			//�@DirectShow�p���C�u����
		#endif
		#ifndef DX_NON_NETWORK
			#pragma comment( lib, "wsock32.lib" )				//  WinSockets�p���C�u����
		#endif
		#ifndef DX_NON_KEYEX
			#pragma comment( lib, "imm32.lib" )					// �h�l�d����p���C�u����
		#endif
		#ifndef DX_NON_ACM
			#pragma comment( lib, "msacm32.lib" )				// �`�b�l����p���C�u���� 
		#endif
		#ifndef DX_NON_PNGREAD
			#ifdef _DEBUG
				#pragma comment( lib, "libpng_d.lib" )			// �o�m�f�p���C�u����
				#pragma comment( lib, "zlib_d.lib" )
			#else
				#pragma comment( lib, "libpng.lib" )			// �o�m�f�p���C�u����
				#pragma comment( lib, "zlib.lib" )
			#endif
		#endif
		#ifndef DX_NON_JPEGREAD
			#ifdef _DEBUG
				#pragma comment( lib, "libjpeg_d.lib" )			// �i�o�d�f�p���C�u����
			#else
				#pragma comment( lib, "libjpeg.lib" )			// �i�o�d�f�p���C�u����
			#endif
		#endif
		#ifndef DX_NON_OGGVORBIS								// �n�����u�����������p���C�u����
			#ifdef _DEBUG
				#pragma comment( lib, "ogg_static_d.lib" )
				#pragma comment( lib, "vorbis_static_d.lib" )
				#pragma comment( lib, "vorbisfile_static_d.lib" )
			#else
				#pragma comment( lib, "ogg_static.lib" )
				#pragma comment( lib, "vorbis_static.lib" )
				#pragma comment( lib, "vorbisfile_static.lib" )
			#endif
		#endif
		#ifndef DX_NON_OGGTHEORA								// �n�����s�����������p���C�u����
			#ifndef _DEBUG
				#pragma comment( lib, "ogg_static_d.lib" )
				#pragma comment( lib, "vorbis_static_d.lib" )
				#pragma comment( lib, "vorbisfile_static_d.lib" )

				#pragma comment( lib, "libtheora_static.lib"		)		//  �c�w���C�u�����g�p�w��
			#else
				#pragma comment( lib, "ogg_static.lib" )
				#pragma comment( lib, "vorbis_static.lib" )
				#pragma comment( lib, "vorbisfile_static.lib" )

				#pragma comment( lib, "libtheora_static_d.lib"		)		//  �c�w���C�u�����g�p�w��
			#endif
		#endif
	#endif
#endif

/*
#ifndef __DX_MAKE
	#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
	#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
	#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
	#pragma comment( linker, "/NODEFAULTLIB:msvcrt.lib" )
	#pragma comment( linker, "/NODEFAULTLIB:msvcrtd.lib" )
#endif
*/

/*
#ifndef __DX_MAKE
	#ifdef _DEBUG
		#ifndef DX_USE_VISUALC_MEM_DEBUG
			#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
//			#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:msvcrt.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:msvcrtd.lib" )
		#else
			#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
		#endif
	#else
		#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
//		#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:msvcrt.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:msvcrtd.lib" )
	#endif
#endif
*/

/*
#ifndef __DX_MAKE
	#ifdef _DEBUG
		#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
//		#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:msvcrt.lib" )
		#ifdef DX_USE_MULTITASK_LIB
			#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
		#else
			#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:msvcrtd.lib" )
		#endif
	#else
		#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:libcd.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:libcmtd.lib" )
		#pragma comment( linker, "/NODEFAULTLIB:msvcrtd.lib" )
		#ifdef DX_USE_MULTITASK_LIB
			#pragma comment( linker, "/NODEFAULTLIB:libc.lib" )
		#else
//			#pragma comment( linker, "/NODEFAULTLIB:libcmt.lib" )
			#pragma comment( linker, "/NODEFAULTLIB:msvcrt.lib" )
		#endif
	#endif
#endif
*/


#ifdef DX_USE_DIRECTX_SDK_FILE
	#ifndef __DX_MAKE
		#ifdef __BCC
			#ifdef strcpy
			#undef strcpy
			#endif
			
			#ifdef strcat
			#undef strcat
			#endif
			
			#ifdef sprintf
			#undef sprintf
			#endif
			
			#ifdef vsprintf
			#undef vsprintf
			#endif
		#endif
	#endif

	// strsafe.h �ւ̑΍R��
	#undef lstrcpy
	#undef lstrcat
	#undef wsprintf
	#undef wvsprintf
	#undef StrCpy
	#undef StrCat
	#undef StrNCat
	#undef StrCatN

	#undef lstrcpyA
	#undef lstrcpyW
	#undef lstrcatA
	#undef lstrcatW
	#undef wsprintfA
	#undef wsprintfW

	#undef StrCpyW
	#undef StrCatW
	#undef StrNCatA
	#undef StrNCatW
	#undef StrCatNA
	#undef StrCatNW
	#undef wvsprintfA
	#undef wvsprintfW

	#undef _tcscpy
	#undef _ftcscpy
	#undef _tcscat
	#undef _ftcscat
	#undef _stprintf
	#undef _sntprintf
	#undef _vstprintf
	#undef _vsntprintf
	#undef _getts

	#undef strcpy
	#undef wcscpy
	#undef strcat
	#undef wcscat
	#undef sprintf
	#undef swprintf
	#undef vsprintf
	#undef vswprintf
	#undef _snprintf
	#undef _snwprintf
	#undef _vsnprintf
	#undef _vsnwprintf
	#undef gets
	#undef _getws

	#ifdef UNICODE
	#define lstrcpy    lstrcpyW
	#define lstrcat    lstrcatW
	#define wsprintf   wsprintfW
	#define wvsprintf  wvsprintfW
	#else
	#define lstrcpy    lstrcpyA
	#define lstrcat    lstrcatA
	#define wsprintf   wsprintfA
	#define wvsprintf  wvsprintfA
	#endif

	#ifdef UNICODE
	#define StrCpy  StrCpyW
	#define StrCat  StrCatW
	#define StrNCat StrNCatW
	#else
	#define StrCpy  lstrcpyA
	#define StrCat  lstrcatA
	#define StrNCat StrNCatA
	#endif

	#ifdef _UNICODE
	#define _tcscpy     wcscpy
	#define _ftcscpy    wcscpy
	#define _tcscat     wcscat
	#define _ftcscat    wcscat
	#define _stprintf   swprintf
	#define _sntprintf  _snwprintf
	#define _vstprintf  vswprintf
	#define _vsntprintf _vsnwprintf
	#define _getts      _getws
	#else
	#define _tcscpy     strcpy
	#define _ftcscpy    strcpy
	#define _tcscat     strcat
	#define _ftcscat    strcat
	#define _stprintf   sprintf
	#define _sntprintf  _snprintf
	#define _vstprintf  vsprintf
	#define _vsntprintf _vsnprintf
	#define _getts      gets
	#endif

	#define strcpy	_STRCPY
	#define strcat	_STRCAT
#endif

// ��`---------------------------------------------------------------------------

#define DX_CHAR										char

#define DX_DEFINE_START

#define MAX_IMAGE_NUM								(32768)				// �����Ɏ��Ă�O���t�B�b�N�n���h���̍ő吔( �n���h���G���[�`�F�b�N�̃}�X�N�Ɏg�p���Ă���̂� 65536 �ȉ��� 2 �ׂ̂���ɂ��ĉ����� )
#define MAX_2DSURFACE_NUM							(32768)				// �Q�c�T�[�t�F�X�f�[�^�̍ő吔( �n���h���G���[�`�F�b�N�̃}�X�N�Ɏg�p���Ă���̂� 65536 �ȉ��� 2 �ׂ̂���ɂ��ĉ����� )
#define MAX_3DSURFACE_NUM							(65536)				// �R�c�T�[�t�F�X�f�[�^�̍ő吔( �n���h���G���[�`�F�b�N�̃}�X�N�Ɏg�p���Ă���̂� 65536 �ȉ��� 2 �ׂ̂���ɂ��ĉ����� )
#define MAX_IMAGE_DIVNUM							(64)				// �摜�����̍ő吔
#define MAX_SURFACE_NUM								(65536)				// �T�[�t�F�X�f�[�^�̍ő吔

#define MAX_SOUND_NUM								(4096)				// �����Ɏ��Ă�T�E���h�n���h���̍ő吔
#define MAX_MUSIC_NUM								(256)				// �����Ɏ��Ă�~���[�W�b�N�n���h���̍ő吔
#define MAX_MOVIE_NUM								(100)				// �����Ɏ��Ă郀�[�r�[�n���h���̍ő吔
#define MAX_MASK_NUM								(512)				// �����Ɏ��Ă�}�X�N�n���h���̍ő吔
#define MAX_FONT_NUM								(40)				// �����Ɏ��Ă�t�H���g�n���h���̍ő吔
#define MAX_INPUT_NUM								(20)				// �����Ɏ��Ă镶������̓n���h���̍ő吔
#define MAX_SOCKET_NUM								(4096)				// �����Ɏ��Ă�ʐM�n���h���̍ő吔

#define MAX_JOYPAD_NUM								(8)					// �W���C�p�b�h�̍ő吔
#define MAX_EVENTPROCESS_NUM						(5)					// ��x�ɏ�������C�x���g�̍ő吔

#define DEFAULT_SCREEN_SIZE_X						(640)				// �f�t�H���g�̉�ʂ̕�
#define DEFAULT_SCREEN_SIZE_Y						(480)				// �f�t�H���g�̉�ʂ̍���
#define DEFAULT_COLOR_BITDEPTH						(16)				// �f�t�H���g�̐F�r�b�g�[�x

#define DEFAULT_FOV									(60.0F * 3.1415926535897932384626433832795F / 180.0F)	// �f�t�H���g�̎���p
#define DEFAULT_TAN_FOV_HALF						(0.57735026918962576450914878050196F) // tan( FOV * 0.5 )
#define DEFAULT_NEAR								(0.0F)				// NEAR�N���b�v��
#define DEFAULT_FAR									(1000.0F)			// FAR�N���b�v��

#define DEFAULT_FONT_SIZE							(16)				// �t�H���g�̃f�t�H���g�̃T�C�Y
#define DEFAULT_FONT_THINCK							(6)					// �t�H���g�̃f�t�H���g�̑���
#define DEFAULT_FONT_TYPE							( DX_FONTTYPE_NORMAL )	// �t�H���g�̃f�t�H���g�̌`��
#define DEFAULT_FONT_EDGESIZE						(1)					// �t�H���g�̃f�t�H���g�̑���

#define FONT_CACHE_MAXNUM							(2024)				// �t�H���g�L���b�V���Ɋi�[�ł���ő啶����
#define FONT_CACHE_MEMORYSIZE						(0x50000)			// �t�H���g�L���b�V���̍ő�e��
#define FONT_CACHE_MAX_YLENGTH						(0x4000)			// �t�H���g�L���b�V���T�[�t�F�X�̍ő�c��

#define MAX_USERIMAGEREAD_FUNCNUM					(10)				// ���[�U�[���o�^�ł���O���t�B�b�N���[�h�֐��̍ő吔


// �n���h���̓���
#define DX_HANDLEINDEX_MASK							(0x0000ffff)		// �n���h���z��C���f�b�N�X�}�X�N
#define DX_HANDLECHECKBIT_MASK						(0x07ff0000)		// �n���h���C���f�b�N�X�G���[�`�F�b�N�p�}�X�N
#define DX_HANDLECHECKBIT_ADDRESS					(16)				// �n���h���C���f�b�N�X�G���[�`�F�b�N�p�}�X�N�̊J�n�A�h���X
#define DX_HANDLETYPE_MASK							(0x78000000)		// �n���h���^�C�v�}�X�N
#define DX_HANDLEERROR_MASK							(0x80000000)		// �G���[�`�F�b�N�}�X�N( �O�ł͂Ȃ�������G���[ )
#define DX_HANDLEERROR_OR_TYPE_MASK					(0xf8000000)		// DX_HANDLETYPE_MASK �� DX_HANDLEERROR_MASK ���|�����킹������

// �n���h���^�C�v��`
#define DX_HANDLETYPE_GRAPH							(0x08000000)		// �O���t�B�b�N�n���h��
#define DX_HANDLETYPE_SOUND							(0x10000000)		// �T�E���h�n���h��
#define DX_HANDLETYPE_MOVIE							(0x18000000)		// ���[�r�[�n���h��
#define DX_HANDLETYPE_FONT							(0x20000000)		// �t�H���g�n���h��
#define DX_HANDLETYPE_2DSURFACE						(0x28000000)		// �Q�c�T�[�t�F�X�n���h��
#define DX_HANDLETYPE_3DSURFACE						(0x30000000)		// �R�c�T�[�t�F�X�n���h��
#define DX_HANDLETYPE_SURFACE						(0x38000000)		// �T�[�t�F�X�n���h��
#define DX_HANDLETYPE_GMASK							(0x40000000)		// �}�X�N�n���h��
#define DX_HANDLETYPE_NETWORK						(0x48000000)		// �l�b�g���[�N�n���h��
#define DX_HANDLETYPE_KEYINPUT						(0x50000000)		// ��������̓n���h��
#define DX_HANDLETYPE_MUSIC							(0x58000000)		// �~���[�W�b�N�n���h��
#define DX_HANDLETYPE_PALETTEGRAPH					(0x60000000)		// �p���b�g�O���t�B�b�N�n���h��
#define DX_HANDLETYPE_MODEL							(0x68000000)		// �R�c���f��

// �v�h�m�c�n�v�r�̃o�[�W�����}�N��
#define DX_WINDOWSVERSION_31						(0x000)
#define DX_WINDOWSVERSION_95						(0x001)
#define DX_WINDOWSVERSION_98						(0x002)
#define DX_WINDOWSVERSION_ME						(0x003)
#define DX_WINDOWSVERSION_NT31						(0x104)
#define DX_WINDOWSVERSION_NT40						(0x105)
#define DX_WINDOWSVERSION_2000						(0x106)
#define DX_WINDOWSVERSION_XP						(0x107)
#define DX_WINDOWSVERSION_VISTA						(0x108)
#define DX_WINDOWSVERSION_NT_TYPE					(0x100)

// �c�����������w�̃o�[�W�����}�N��
#define DX_DIRECTXVERSION_NON						(0)
#define DX_DIRECTXVERSION_1							(0x10000)
#define DX_DIRECTXVERSION_2							(0x20000)
#define DX_DIRECTXVERSION_3							(0x30000)
#define DX_DIRECTXVERSION_4							(0x40000)
#define DX_DIRECTXVERSION_5							(0x50000)
#define DX_DIRECTXVERSION_6							(0x60000)
#define DX_DIRECTXVERSION_6_1						(0x60100)
#define DX_DIRECTXVERSION_7							(0x70000)
#define DX_DIRECTXVERSION_8							(0x80000)
#define DX_DIRECTXVERSION_8_1						(0x80100)

// �����Z�b�g
#define DX_CHARSET_DEFAULT							(0)				// �f�t�H���g�����Z�b�g
#define DX_CHARSET_SHFTJIS							(1)				// ���{�ꕶ���Z�b�g
#define DX_CHARSET_HANGEUL							(2)				// �؍��ꕶ���Z�b�g

// �l�h�c�h�̍Đ����[�h��`
#define DX_MIDIMODE_MCI								(0)				// �l�b�h�ɂ��Đ�
#define DX_MIDIMODE_DM								(1)				// �c�����������l���������ɂ��Đ�

// �`�惂�[�h��`
#define DX_DRAWMODE_NEAREST							(0)				// �l�A���X�g�l�C�o�[�@�ŕ`��
#define DX_DRAWMODE_BILINEAR						(1)				// �o�C���j�A�@�ŕ`�悷��

// �t�H���g�̃^�C�v
#define DX_FONTTYPE_NORMAL							(0)				// �m�[�}���t�H���g
#define DX_FONTTYPE_EDGE							(1)				// �G�b�W���t�H���g
#define DX_FONTTYPE_ANTIALIASING					(2)				// �A���`�G�C���A�X�t�H���g
#define DX_FONTTYPE_ANTIALIASING_EDGE				(3)				// �A���`�G�C���A�X���G�b�W�t���t�H���g

// �`��u�����h���[�h��`
#define DX_BLENDMODE_NOBLEND						(0)				// �m�[�u�����h
#define DX_BLENDMODE_ALPHA							(1)				// ���u�����h
#define DX_BLENDMODE_ADD							(2)				// ���Z�u�����h
#define DX_BLENDMODE_SUB							(3)				// ���Z�u�����h
#define DX_BLENDMODE_MUL							(4)				// ��Z�u�����h
   // (���������p)
#define DX_BLENDMODE_SUB2							(5)				// ���������p���Z�u�����h�q�P
//#define DX_BLENDMODE_BLINEALPHA						(7)				// ���E���ڂ���
#define DX_BLENDMODE_XOR							(6)				// XOR�u�����h
#define DX_BLENDMODE_DESTCOLOR						(8)				// �J���[�͍X�V����Ȃ�
#define DX_BLENDMODE_INVDESTCOLOR					(9)				// �`���̐F�̔��]�l���|����
#define DX_BLENDMODE_INVSRC							(10)			// �`�挳�̐F�𔽓]����
#define DX_BLENDMODE_MULA							(11)			// �A���t�@�`�����l���l���t����Z�u�����h

// �`����ʎw��p��`
#define DX_SCREEN_FRONT								(0xfffffffc)
#define DX_SCREEN_BACK								(0xfffffffe) 
#define DX_SCREEN_WORK 								(0xfffffffd)
#define DX_SCREEN_TEMPFRONT							(0xfffffffb)

#define DX_NONE_GRAPH								(0xfffffffb)	// �O���t�B�b�N�Ȃ��n���h��

// �O���t�B�b�N���F���̉摜�򉻊ɘa�������[�h
#define DX_SHAVEDMODE_NONE							(0)				// �摜�򉻊ɘa�������s��Ȃ�
#define DX_SHAVEDMODE_DITHER						(1)				// �f�B�U�����O
#define DX_SHAVEDMODE_DIFFUS						(2)				// �덷�g�U

// �摜�̕ۑ��^�C�v
#define DX_IMAGESAVETYPE_BMP						(0)				// bitmap
#define DX_IMAGESAVETYPE_JPEG						(1)				// jpeg
#define DX_IMAGESAVETYPE_PNG						(2)				// Png

// �T�E���h�Đ��`�Ԏw��p��`
#define DX_PLAYTYPE_LOOPBIT							(0x0002)		// ���[�v�Đ��r�b�g
#define DX_PLAYTYPE_BACKBIT							(0x0001)		// �o�b�N�O���E���h�Đ��r�b�g
	
#define DX_PLAYTYPE_NORMAL							(0)												// �m�[�}���Đ�
#define DX_PLAYTYPE_BACK				  			( DX_PLAYTYPE_BACKBIT )							// �o�b�N�O���E���h�Đ�
#define DX_PLAYTYPE_LOOP							( DX_PLAYTYPE_LOOPBIT | DX_PLAYTYPE_BACKBIT )	// ���[�v�Đ�

// ����Đ��^�C�v��`
#define DX_MOVIEPLAYTYPE_BCANCEL					(0)				// �{�^���L�����Z������
#define DX_MOVIEPLAYTYPE_NORMAL						(1)				// �{�^���L�����Z���Ȃ�

// �T�E���h�̃^�C�v
#define DX_SOUNDTYPE_NORMAL							(0)				// �m�[�}���T�E���h�`��
#define DX_SOUNDTYPE_STREAMSTYLE					(1)				// �X�g���[�����T�E���h�`��

// �X�g���[���T�E���h�Đ��f�[�^�^�C�v�̃}�N��
#define DX_SOUNDDATATYPE_MEMNOPRESS					(0)				// ���k���ꂽ�S�f�[�^�͍Đ����n�܂�O�ɃT�E���h�������ɂ��ׂĉ𓀂���A�i�[�����
#define DX_SOUNDDATATYPE_MEMNOPRESS_PLUS			(1)				// ���k���ꂽ�S�f�[�^�̓V�X�e���������Ɋi�[����A�Đ����Ȃ��璀���𓀂���A�ŏI�I�ɂ��ׂăT�E���h�������Ɋi�[�����(���̌�V�X�e���������ɑ��݂��鈳�k�f�[�^�͔j�������)
#define DX_SOUNDDATATYPE_MEMPRESS					(2)				// ���k���ꂽ�S�f�[�^�̓V�X�e���������Ɋi�[����A�Đ����镔�����������𓀂��Ȃ���T�E���h�������Ɋi�[����(�炵�I���Ɖ𓀂����f�[�^�͔j�������̂ŉ��x���𓀏������s����)
#define DX_SOUNDDATATYPE_FILE						(3)				// ���k���ꂽ�f�[�^�̍Đ����镔�������t�@�C�����璀���ǂݍ��݉𓀂���A�T�E���h�������Ɋi�[�����(�炵�I���Ɖ𓀂����f�[�^�͔j�������̂ŉ��x���𓀏������s����)

// �}�X�N���ߐF���[�h
#define DX_MASKTRANS_WHITE							(0)				// �}�X�N�摜�̔��������𓧉ߐF�Ƃ���
#define DX_MASKTRANS_BLACK							(1)				// �}�X�N�摜�̍��������𓧉ߐF�Ƃ���
#define DX_MASKTRANS_NONE							(2) 			// ���ߐF�Ȃ�

// �y�o�b�t�@�������݃��[�h
#define DX_ZWRITE_MASK								(0)				// �������߂Ȃ��悤�Ƀ}�X�N����
#define DX_ZWRITE_CLEAR								(1)				// �������߂�悤�Ƀ}�X�N���N���A����

// ��r���[�h
#define DX_CMP_NEVER								(1)				// FALSE
#define DX_CMP_LESS									(2)				// Src <  Dest
#define DX_CMP_EQUAL								(3)				// Src == Dest
#define DX_CMP_LESSEQUAL							(4)				// Src <= Dest
#define DX_CMP_GREATER								(5)				// Src >  Dest
#define DX_CMP_NOTEQUAL								(6)				// Src != Dest
#define DX_CMP_GREATEREQUAL							(7)				// Src >= Dest
#define DX_CMP_ALWAYS								(8)				// TRUE
#define DX_ZCMP_DEFAULT								( DX_CMP_LESSEQUAL )
#define DX_ZCMP_REVERSE								( DX_CMP_GREATEREQUAL )

// �V�F�[�f�B���O���[�h
#define DX_SHADEMODE_FLAT							D_D3DSHADE_FLAT
#define DX_SHADEMODE_GOURAUD						D_D3DSHADE_GOURAUD

// �e�N�X�`���A�h���X�^�C�v
#define DX_TEXADDRESS_WRAP							D_D3DTADDRESS_WRAP
#define DX_TEXADDRESS_MIRROR						D_D3DTADDRESS_MIRROR
#define DX_TEXADDRESS_CLAMP							D_D3DTADDRESS_CLAMP
#define DX_TEXADDRESS_BORDER						D_D3DTADDRESS_BORDER

// �|���S���`��^�C�v
#define DX_PRIMTYPE_POINTLIST						D_D3DPT_POINTLIST
#define DX_PRIMTYPE_LINELIST						D_D3DPT_LINELIST
#define DX_PRIMTYPE_LINESTRIP						D_D3DPT_LINESTRIP
#define DX_PRIMTYPE_TRIANGLELIST					D_D3DPT_TRIANGLELIST
#define DX_PRIMTYPE_TRIANGLESTRIP					D_D3DPT_TRIANGLESTRIP
#define DX_PRIMTYPE_TRIANGLEFAN						D_D3DPT_TRIANGLEFAN

// ���C�g�^�C�v
#define DX_LIGHTTYPE_D3DLIGHT_POINT					D_D3DLIGHT_POINT
#define DX_LIGHTTYPE_D3DLIGHT_SPOT					D_D3DLIGHT_SPOT
#define DX_LIGHTTYPE_D3DLIGHT_DIRECTIONAL			D_D3DLIGHT_DIRECTIONAL
#define DX_LIGHTTYPE_D3DLIGHT_FORCEDWORD			D_D3DLIGHT_FORCE_DWORD

// �O���t�B�b�N�C���[�W�t�H�[�}�b�g�̒�`
#define DX_GRAPHICSIMAGE_FORMAT_3D_RGB16					(0)		// �P�U�r�b�g�J���[�W��
#define DX_GRAPHICSIMAGE_FORMAT_3D_RGB32					(1)		// �R�Q�r�b�g�J���[�W��
#define DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_RGB16				(2)		// ���`�����l���t���P�U�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_ALPHA_RGB32				(3)		// ���`�����l���t���R�Q�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_RGB16			(4)		// ���e�X�g�t���P�U�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_ALPHATEST_RGB32			(5)		// ���e�X�g�t���R�Q�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_RGB16			(6)		// �`��\�P�U�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_RGB32			(7)		// �`��\�R�Q�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_DRAWVALID_ALPHA_RGB32	(8)		// �`��\���t���R�Q�r�b�g�J���[
#define DX_GRAPHICSIMAGE_FORMAT_3D_NUM						(9)
#define DX_GRAPHICSIMAGE_FORMAT_2D							(9)		// �W��( DirectDrawSurface �̏ꍇ�͂���̂� )
#define DX_GRAPHICSIMAGE_FORMAT_R5G6B5						(10)	// R5G6B5( MEMIMG �p )
#define DX_GRAPHICSIMAGE_FORMAT_X8A8R5G6B5					(11)	// X8A8R5G6B5( MEMIMG �p )
#define DX_GRAPHICSIMAGE_FORMAT_X8R8G8B8					(12)	// X8R8G8B8( MEMIMG �p )
#define DX_GRAPHICSIMAGE_FORMAT_A8R8G8B8					(13)	// A8R8G8B8( MEMIMG �p )

#define DX_GRAPHICSIMAGE_FORMAT_NUM							(14)	// �O���t�B�b�N�t�H�[�}�b�g�̎�ނ̐�

// �c�[���o�[�̃{�^���̏��
#define TOOLBUTTON_STATE_ENABLE				(0)			// ���͉\�ȏ��
#define TOOLBUTTON_STATE_PRESSED			(1)			// ������Ă�����
#define TOOLBUTTON_STATE_DISABLE			(2)			// ���͕s�\�ȏ��
#define TOOLBUTTON_STATE_PRESSED_DISABLE	(3)			// ������Ă����ԂŁA���͕s�\�ȏ��
#define TOOLBUTTON_STATE_NUM				(4)			// �c�[���o�[�̃{�^���̏�Ԃ̐�

// �c�[���o�[�̃{�^���̃^�C�v
#define TOOLBUTTON_TYPE_NORMAL			(0)			// ���ʂ̃{�^��
#define TOOLBUTTON_TYPE_CHECK			(1)			// �������Ƃɂn�m�^�n�e�e���؂�ւ��{�^��
#define TOOLBUTTON_TYPE_GROUP			(2)			// �ʂ� TOOLBUTTON_TYPE_GROUP �^�C�v�̃{�^�����������Ƃn�e�e�ɂȂ�^�C�v�̃{�^��(�O���[�v�̋�؂�͌��Ԃ�)
#define TOOLBUTTON_TYPE_SEP				(3)			// ����(�{�^���ł͂���܂���)
#define TOOLBUTTON_TYPE_NUM				(4)			// �c�[���o�[�̃{�^���̃^�C�v�̐�

// �e���j���[�̂h�c
#define MENUITEM_IDTOP								(0xabababab)

// ���j���[�ɒǉ�����ۂ̃^�C�v
#define MENUITEM_ADD_CHILD							(0)				// �w��̍��ڂ̎q�Ƃ��Ēǉ�����
#define MENUITEM_ADD_INSERT							(1)				// �w��̍��ڂƎw��̍��ڂ����̍��ڂ̊Ԃɒǉ�����

// ���j���[�̉��ɕt���}�[�N�^�C�v
#define MENUITEM_MARK_NONE							(0)				// �����t������
#define MENUITEM_MARK_CHECK							(1)				// �`�F�b�N�}�[�N
#define MENUITEM_MARK_RADIO							(2)				// ���W�I�{�^��

// �����ϊ��^�C�v��`
#define DX_NUMMODE_10								(0)				// �P�O�i��
#define DX_NUMMODE_16								(1)				// �P�U�i��
#define DX_STRMODE_NOT0								(2)				// �󂫂��O�Ŗ��߂Ȃ�
#define DX_STRMODE_USE0								(3)				// �󂫂��O�Ŗ��߂�

// CheckHitKeyAll �Œ��ׂ���̓^�C�v
#define DX_CHECKINPUT_KEY							(0x0001)		// �L�[���͂𒲂ׂ�
#define DX_CHECKINPUT_PAD							(0x0002)		// �p�b�h���͂𒲂ׂ�
#define DX_CHECKINPUT_MOUSE							(0x0004)		// �}�E�X�{�^�����͂𒲂ׂ�
#define DX_CHECKINPUT_ALL							(DX_CHECKINPUT_KEY | DX_CHECKINPUT_PAD | DX_CHECKINPUT_MOUSE)	// ���ׂĂ̓��͂𒲂ׂ�

// �p�b�h���͎擾�p�����[�^
#define DX_INPUT_KEY_PAD1							(0x1001)		// �L�[���͂ƃp�b�h�P����
#define DX_INPUT_PAD1								(0x0001)		// �p�b�h�P����
#define DX_INPUT_PAD2								(0x0002)		// �p�b�h�Q����
#define DX_INPUT_PAD3								(0x0003)		// �p�b�h�R����
#define DX_INPUT_PAD4								(0x0004)		// �p�b�h�S����
#define DX_INPUT_PAD5								(0x0005)		// �p�b�h�T����
#define DX_INPUT_PAD6								(0x0006)		// �p�b�h�U����
#define DX_INPUT_PAD7								(0x0007)		// �p�b�h�V����
#define DX_INPUT_PAD8								(0x0008)		// �p�b�h�W����
#define DX_INPUT_KEY								(0x1000)		// �L�[����

// ���[�r�[�̃T�[�t�F�X���[�h
#define DX_MOVIESURFACE_NORMAL						(0)
#define DX_MOVIESURFACE_OVERLAY						(1)
#define DX_MOVIESURFACE_FULLCOLOR					(2)

// �p�b�h���͒�`
#define PAD_INPUT_DOWN								(0x00000001)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_LEFT								(0x00000002)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_RIGHT								(0x00000004)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_UP								(0x00000008)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_A									(0x00000010)	// �`�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_B									(0x00000020)	// �a�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_C									(0x00000040)	// �b�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_X									(0x00000080)	// �w�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Y									(0x00000100)	// �x�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Z									(0x00000200)	// �y�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_L									(0x00000400)	// �k�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_R									(0x00000800)	// �q�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_START								(0x00001000)	// �r�s�`�q�s�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_M									(0x00002000)	// �l�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_D									(0x00004000)
#define PAD_INPUT_F									(0x00008000)
#define PAD_INPUT_G									(0x00010000)
#define PAD_INPUT_H									(0x00020000)
#define PAD_INPUT_I									(0x00040000)
#define PAD_INPUT_J									(0x00080000)
#define PAD_INPUT_K									(0x00100000)
#define PAD_INPUT_LL								(0x00200000)
#define PAD_INPUT_N									(0x00400000)
#define PAD_INPUT_O									(0x00800000)
#define PAD_INPUT_P									(0x01000000)
#define PAD_INPUT_RR								(0x02000000)
#define PAD_INPUT_S									(0x04000000)
#define PAD_INPUT_T									(0x08000000)
#define PAD_INPUT_U									(0x10000000)
#define PAD_INPUT_V									(0x20000000)
#define PAD_INPUT_W									(0x40000000)
#define PAD_INPUT_XX								(0x80000000)

// �}�E�X���͒�`
#define MOUSE_INPUT_LEFT							(0x0001)			// �}�E�X���{�^��
#define MOUSE_INPUT_RIGHT							(0x0002)			// �}�E�X�E�{�^��
#define MOUSE_INPUT_MIDDLE							(0x0004)			// �}�E�X�����{�^��
#define MOUSE_INPUT_1								(0x0001)			// �}�E�X�P�{�^��
#define MOUSE_INPUT_2								(0x0002)			// �}�E�X�Q�{�^��
#define MOUSE_INPUT_3								(0x0004)			// �}�E�X�R�{�^��
#define MOUSE_INPUT_4								(0x0008)			// �}�E�X�S�{�^��
#define MOUSE_INPUT_5								(0x0010)			// �}�E�X�T�{�^��
#define MOUSE_INPUT_6								(0x0020)			// �}�E�X�U�{�^��
#define MOUSE_INPUT_7								(0x0040)			// �}�E�X�V�{�^��
#define MOUSE_INPUT_8								(0x0080)			// �}�E�X�W�{�^��

// �L�[��`
#define KEY_INPUT_BACK								D_DIK_BACK			// �o�b�N�X�y�[�X�L�[
#define KEY_INPUT_TAB								D_DIK_TAB			// �^�u�L�[
#define KEY_INPUT_RETURN							D_DIK_RETURN		// �G���^�[�L�[

#define KEY_INPUT_LSHIFT							D_DIK_LSHIFT		// ���V�t�g�L�[
#define KEY_INPUT_RSHIFT							D_DIK_RSHIFT		// �E�V�t�g�L�[
#define KEY_INPUT_LCONTROL							D_DIK_LCONTROL		// ���R���g���[���L�[
#define KEY_INPUT_RCONTROL							D_DIK_RCONTROL		// �E�R���g���[���L�[
#define KEY_INPUT_ESCAPE							D_DIK_ESCAPE		// �G�X�P�[�v�L�[
#define KEY_INPUT_SPACE								D_DIK_SPACE			// �X�y�[�X�L�[
#define KEY_INPUT_PGUP								D_DIK_PGUP			// �o�������t�o�L�[
#define KEY_INPUT_PGDN								D_DIK_PGDN			// �o�������c�������L�[
#define KEY_INPUT_END								D_DIK_END			// �G���h�L�[
#define KEY_INPUT_HOME								D_DIK_HOME			// �z�[���L�[
#define KEY_INPUT_LEFT								D_DIK_LEFT			// ���L�[
#define KEY_INPUT_UP								D_DIK_UP			// ��L�[
#define KEY_INPUT_RIGHT								D_DIK_RIGHT			// �E�L�[
#define KEY_INPUT_DOWN								D_DIK_DOWN			// ���L�[
#define KEY_INPUT_INSERT							D_DIK_INSERT		// �C���T�[�g�L�[
#define KEY_INPUT_DELETE							D_DIK_DELETE		// �f���[�g�L�[

#define KEY_INPUT_MINUS								D_DIK_MINUS			// �|�L�[
#define KEY_INPUT_YEN								D_DIK_YEN			// ���L�[
#define KEY_INPUT_PREVTRACK							D_DIK_PREVTRACK		// �O�L�[
#define KEY_INPUT_PERIOD							D_DIK_PERIOD		// �D�L�[
#define KEY_INPUT_SLASH								D_DIK_SLASH			// �^�L�[
#define KEY_INPUT_LALT								D_DIK_LALT			// ���`�k�s�L�[
#define KEY_INPUT_RALT								D_DIK_RALT			// �E�`�k�s�L�[
#define KEY_INPUT_SCROLL							D_DIK_SCROLL		// ScrollLock�L�[
#define KEY_INPUT_SEMICOLON							D_DIK_SEMICOLON		// �G�L�[
#define KEY_INPUT_COLON								D_DIK_COLON			// �F�L�[
#define KEY_INPUT_LBRACKET							D_DIK_LBRACKET		// �m�L�[
#define KEY_INPUT_RBRACKET							D_DIK_RBRACKET		// �n�L�[
#define KEY_INPUT_AT								D_DIK_AT			// ���L�[
#define KEY_INPUT_BACKSLASH							D_DIK_BACKSLASH		// �_�L�[
#define KEY_INPUT_COMMA								D_DIK_COMMA			// �C�L�[
#define KEY_INPUT_CAPSLOCK							D_DIK_CAPSLOCK		// CaspLock�L�[
#define KEY_INPUT_SYSRQ								D_DIK_SYSRQ			// PrintScreen�L�[
#define KEY_INPUT_PAUSE								D_DIK_PAUSE			// PauseBreak�L�[

#define KEY_INPUT_NUMPAD0							D_DIK_NUMPAD0		// �e���L�[�O
#define KEY_INPUT_NUMPAD1							D_DIK_NUMPAD1		// �e���L�[�P
#define KEY_INPUT_NUMPAD2							D_DIK_NUMPAD2		// �e���L�[�Q
#define KEY_INPUT_NUMPAD3							D_DIK_NUMPAD3		// �e���L�[�R
#define KEY_INPUT_NUMPAD4							D_DIK_NUMPAD4		// �e���L�[�S
#define KEY_INPUT_NUMPAD5							D_DIK_NUMPAD5		// �e���L�[�T
#define KEY_INPUT_NUMPAD6							D_DIK_NUMPAD6		// �e���L�[�U
#define KEY_INPUT_NUMPAD7							D_DIK_NUMPAD7		// �e���L�[�V
#define KEY_INPUT_NUMPAD8							D_DIK_NUMPAD8		// �e���L�[�W
#define KEY_INPUT_NUMPAD9							D_DIK_NUMPAD9		// �e���L�[�X
#define KEY_INPUT_MULTIPLY							D_DIK_MULTIPLY		// �e���L�[���L�[
#define KEY_INPUT_ADD								D_DIK_ADD			// �e���L�[�{�L�[
#define KEY_INPUT_SUBTRACT							D_DIK_SUBTRACT		// �e���L�[�|�L�[
#define KEY_INPUT_DECIMAL							D_DIK_DECIMAL		// �e���L�[�D�L�[
#define KEY_INPUT_DIVIDE							D_DIK_DIVIDE		// �e���L�[�^�L�[
#define KEY_INPUT_NUMPADENTER						D_DIK_NUMPADENTER	// �e���L�[�̃G���^�[�L�[

#define KEY_INPUT_F1								D_DIK_F1			// �e�P�L�[
#define KEY_INPUT_F2								D_DIK_F2			// �e�Q�L�[
#define KEY_INPUT_F3								D_DIK_F3			// �e�R�L�[
#define KEY_INPUT_F4								D_DIK_F4			// �e�S�L�[
#define KEY_INPUT_F5								D_DIK_F5			// �e�T�L�[
#define KEY_INPUT_F6								D_DIK_F6			// �e�U�L�[
#define KEY_INPUT_F7								D_DIK_F7			// �e�V�L�[
#define KEY_INPUT_F8								D_DIK_F8			// �e�W�L�[
#define KEY_INPUT_F9								D_DIK_F9			// �e�X�L�[
#define KEY_INPUT_F10								D_DIK_F10			// �e�P�O�L�[
#define KEY_INPUT_F11								D_DIK_F11			// �e�P�P�L�[
#define KEY_INPUT_F12								D_DIK_F12			// �e�P�Q�L�[

#define KEY_INPUT_A									D_DIK_A			// �`�L�[
#define KEY_INPUT_B									D_DIK_B			// �a�L�[
#define KEY_INPUT_C									D_DIK_C			// �b�L�[
#define KEY_INPUT_D									D_DIK_D			// �c�L�[
#define KEY_INPUT_E									D_DIK_E			// �d�L�[
#define KEY_INPUT_F									D_DIK_F			// �e�L�[
#define KEY_INPUT_G									D_DIK_G			// �f�L�[
#define KEY_INPUT_H									D_DIK_H			// �g�L�[
#define KEY_INPUT_I									D_DIK_I			// �h�L�[
#define KEY_INPUT_J									D_DIK_J			// �i�L�[
#define KEY_INPUT_K									D_DIK_K			// �j�L�[
#define KEY_INPUT_L									D_DIK_L			// �k�L�[
#define KEY_INPUT_M									D_DIK_M			// �l�L�[
#define KEY_INPUT_N									D_DIK_N			// �m�L�[
#define KEY_INPUT_O									D_DIK_O			// �n�L�[
#define KEY_INPUT_P									D_DIK_P			// �o�L�[
#define KEY_INPUT_Q									D_DIK_Q			// �p�L�[
#define KEY_INPUT_R									D_DIK_R			// �q�L�[
#define KEY_INPUT_S									D_DIK_S			// �r�L�[
#define KEY_INPUT_T									D_DIK_T			// �s�L�[
#define KEY_INPUT_U									D_DIK_U			// �t�L�[
#define KEY_INPUT_V									D_DIK_V			// �u�L�[
#define KEY_INPUT_W									D_DIK_W			// �v�L�[
#define KEY_INPUT_X									D_DIK_X			// �w�L�[
#define KEY_INPUT_Y									D_DIK_Y			// �x�L�[
#define KEY_INPUT_Z									D_DIK_Z			// �y�L�[

#define KEY_INPUT_0 								D_DIK_0			// �O�L�[
#define KEY_INPUT_1									D_DIK_1			// �P�L�[
#define KEY_INPUT_2									D_DIK_2			// �Q�L�[
#define KEY_INPUT_3									D_DIK_3			// �R�L�[
#define KEY_INPUT_4									D_DIK_4			// �S�L�[
#define KEY_INPUT_5									D_DIK_5			// �T�L�[
#define KEY_INPUT_6									D_DIK_6			// �U�L�[
#define KEY_INPUT_7									D_DIK_7			// �V�L�[
#define KEY_INPUT_8									D_DIK_8			// �W�L�[
#define KEY_INPUT_9									D_DIK_9			// �X�L�[

// �A�X�L�[�R���g���[���L�[�R�[�h
#define CTRL_CODE_BS								(0x08)				// �o�b�N�X�y�[�X
#define CTRL_CODE_TAB								(0x09)				// �^�u
#define CTRL_CODE_CR								(0x0d)				// ���s
#define CTRL_CODE_DEL								(0x10)				// �c�d�k�L�[

#define CTRL_CODE_LEFT								(0x1d)				// ���L�[
#define CTRL_CODE_RIGHT								(0x1c)				// ���L�[
#define CTRL_CODE_UP								(0x1e)				// ���L�[
#define CTRL_CODE_DOWN								(0x1f)				// ���L�[

#define CTRL_CODE_ESC								(0x1b)				// �d�r�b�L�[
#define CTRL_CODE_CMP								(0x20)				// ����R�[�h�~���l

// SetGraphMode �߂�l��`
#define DX_CHANGESCREEN_OK							(0)					// ��ʕύX�͐�������
#define DX_CHANGESCREEN_RETURN						(-1)				// ��ʂ̕ύX�͎��s���A���̉�ʃ��[�h�ɖ߂��ꂽ
#define DX_CHANGESCREEN_DEFAULT						(-2)				// ��ʂ̕ύX�͎��s���f�t�H���g�̉�ʃ��[�h�ɕύX���ꂽ
#define DX_CHANGESCREEN_REFRESHNORMAL				(-3)				// ��ʂ̕ύX�͐����������A���t���b�V�����[�g�̕ύX�͎��s����

// �X�g���[���f�[�^�ǂݍ��ݏ����R�[�h�ȗ����֘A
#define STTELL( st )								((st)->ReadShred.Tell( (st)->DataPoint ))
#define STSEEK( st, pos, type )						((st)->ReadShred.Seek( (st)->DataPoint, (pos), (type) ))
#define STREAD( buf, length, num, st )				((st)->ReadShred.Read( (buf), (length), (num), (st)->DataPoint ))
#define STWRITE( buf, length, num, st )				((st)->ReadShred.Write( (buf), (length), (num), (st)->DataPoint ))
#define STEOF( st )									((st)->ReadShred.Eof( (st)->DataPoint ))
#define STCLOSE( st )								((st)->ReadShred.Close( (st)->DataPoint ))

// �X�g���[���f�[�^����̃V�[�N�^�C�v��`
#define STREAM_SEEKTYPE_SET							(SEEK_SET)
#define STREAM_SEEKTYPE_END							(SEEK_END)
#define STREAM_SEEKTYPE_CUR							(SEEK_CUR)

// �O���t�B�b�N���[�h���̃C���[�W�^�C�v
#define LOADIMAGE_TYPE_FILE							(0)				// �C���[�W�̓t�@�C���ł���
#define LOADIMAGE_TYPE_MEM							(1)				// �C���[�W�̓������ł���
#define LOADIMAGE_TYPE_NONE							(-1)			// �C���[�W�͖���

// DrawPreparation �֐��ɓn���t���O
#define DRAWPREP_TRANS			(0x0001)
#define DRAWPREP_VECTORINT		(0x0002)
#define DRAWPREP_ENABLEZBUFFER	(0x0004)
#define DRAWPREP_GOURAUDSHADE	(0x0008)
#define DRAWPREP_PERSPECTIVE	(0x0010)
#define DRAWPREP_DIFFUSERGB		(0x0020)
#define DRAWPREP_DIFFUSEALPHA	(0x0040)

#ifndef DX_NON_NETWORK

// HTTP �G���[
#define HTTP_ERR_SERVER								(0)				// �T�[�o�[�G���[
#define HTTP_ERR_NOTFOUND							(1)				// �t�@�C����������Ȃ�����
#define HTTP_ERR_MEMORY								(2)				// �������m�ۂ̎��s
#define HTTP_ERR_LOST								(3)				// �r���Őؒf���ꂽ
#define HTTP_ERR_NONE								(-1)			// �G���[�͕񍐂���Ă��Ȃ�

// HTTP �����̌���
#define HTTP_RES_COMPLETE							(0)				// ��������
#define HTTP_RES_STOP								(1)				// �������~
#define HTTP_RES_ERROR								(2)				// �G���[�I��
#define HTTP_RES_NOW								(-1)			// ���ݐi�s��

#endif

#define DX_DEFINE_END

// �f�[�^�^��`-------------------------------------------------------------------

#define DX_STRUCT_START

// �h�l�d���͕�����̕`��ɕK�v�ȏ��̓��̕��ߏ��
typedef struct tagIMEINPUTCLAUSEDATA
{
	int						Position ;				// ���o�C�g�ڂ���
	int						Length ;				// ���o�C�g��
} IMEINPUTCLAUSEDATA, *LPIMEINPUTCLAUSEDATA ;

// �h�l�d���͕�����̕`��ɕK�v�ȏ��
typedef struct tagIMEINPUTDATA
{
	const char *				InputString ;			// ���͒��̕�����

	int							CursorPosition ;		// �J�[�\���̓��͕����񒆂̈ʒu(�o�C�g�P��)

	const IMEINPUTCLAUSEDATA *	ClauseData ;			// ���ߏ��
	int							ClauseNum ;				// ���ߏ��̐�
	int							SelectClause ;			// �I�𒆂̕���( -1 �̏ꍇ�͂ǂ̕��߂ɂ������Ă��Ȃ�( �����ɃJ�[�\�������� ) )

	int							CandidateNum ;			// �ϊ����̐�( 0�̏ꍇ�͕ϊ����ł͂Ȃ� )
	const char **				CandidateList ;			// �ϊ���╶���񃊃X�g( ��F���Ԗڂ̌���`�悷��ꍇ  DrawString( 0, 0, data.CandidateList[ n ], GetColor(255,255,255) ); )
	int							SelectCandidate ;		// �I�𒆂̕ϊ����
} IMEINPUTDATA, *LPIMEINPUTDATA ;

// �^�C���f�[�^�^
typedef struct tagDATEDATA
{
	int						Year ;							// �N
	int						Mon ;							// ��
	int						Day ;							// ��
	int						Hour ;							// ����
	int						Min ;							// ��
	int						Sec ;							// �b
} DATEDATA, *LPDATEDATA ;

// �t�@�C�����\����
typedef struct tagFILEINFO
{
	char					Name[260] ;			// �I�u�W�F�N�g��
	int						DirFlag ;			// �f�B���N�g�����ǂ���( TRUE:�f�B���N�g��  FALSE:�t�@�C�� )
	LONGLONG				Size ;				// �T�C�Y
	DATEDATA				CreationTime ;		// �쐬����
	DATEDATA				LastWriteTime ;		// �ŏI�X�V����
} FILEINFO, *LPFILEINFO ;

#ifndef DX_NOTUSE_DRAWFUNCTION

// �s��\����
typedef struct tagMATRIX
{
	float					m[4][4] ;
} MATRIX, *LPMATRIX ;

// �x�N�g���f�[�^�^
typedef struct tagVECTOR
{
	float					x, y, z ;
} VECTOR, *LPVECTOR ;

// �N�H�[�^�j�I���f�[�^�\����
typedef struct tagQT
{
	float w ;
	VECTOR v ;
} QT, *LPQT ;

// �Q�c�`��p���_�\����(�e�N�X�`������)
typedef struct tagVERTEX_NOTEX_2D
{
	VECTOR					pos ;
	float					rhw ;
	int						color ;
} VERTEX_NOTEX_2D, *LPVERTEX_NOTEX_2D ; 

// ��ɂQ�c�`��Ɏg�p���钸�_�f�[�^�^
typedef struct tagVERTEX_2D
{
	VECTOR					pos ;
	float					rhw ;
	int						color ;
	float					u, v ;
} VERTEX_2D, *LPVERTEX_2D ; 

// ��ɂQ�c�`��Ɏg�p���钸�_�f�[�^�^(���J�p)
typedef struct tagVERTEX
{
	float					x, y ;
	float					u, v ;
	unsigned char			b, g, r, a ;
} VERTEX ;

// ��ɂR�c�`��Ɏg�p���钸�_�f�[�^�^
typedef struct tagVERTEX_3D
{
	VECTOR					pos ;
	unsigned char			b, g, r, a ;
	float					u, v ;
} VERTEX_3D, *LPVERTEX_3D ;

// ��ɂR�c�`��Ɏg�p���钸�_�f�[�^�^�̃��C�g�Ή���
typedef struct tagVERTEX_3D_LIGHT
{
	VECTOR					pos ;
	VECTOR					normal ;
	unsigned char			b, g, r, a ;
	float					u, v ;
} VERTEX_3D_LIGHT, *LPVERTEX_3D_LIGHT ;

// float �^�̃J���[�l
typedef struct tagCOLOR_F
{
	float					r, g, b, a ;
} COLOR_F, *LPCOLOR_F ;

// unsigned char �^�̃J���[�l
typedef struct tagCOLOR_U8
{
	BYTE					b, g, r, a ;
} COLOR_U8 ;

#endif // DX_NOTUSE_DRAWFUNCTION






// �X�g���[���f�[�^����p�֐��|�C���^�\���̃^�C�v�Q
typedef struct tagSTREAMDATASHREDTYPE2
{
	int						(*Open)( const char *Path, int UseCacheFlag, int BlockReadFlag, int UseASyncReadFlag ) ;
	int						(*Close)( int Handle ) ;
	long					(*Tell)( int Handle ) ;
	int						(*Seek)( int Handle, long SeekPoint, int SeekType ) ;
	size_t					(*Read)( void *Buffer, size_t BlockSize, size_t DataNum, int Handle ) ;
	int						(*Eof)( int Handle ) ;
	int						(*IdleCheck)( int Handle ) ;
	int						(*ChDir)( const char *Path ) ;
	int						(*GetDir)( char *Buffer ) ;
	int						(*FindFirst)( const char *FilePath, FILEINFO *Buffer ) ;	// �߂�l: -1=�G���[  -1�ȊO=FindHandle
	int						(*FindNext)( int FindHandle, FILEINFO *Buffer ) ;			// �߂�l: -1=�G���[  0=����
	int						(*FindClose)( int FindHandle ) ;							// �߂�l: -1=�G���[  0=����
} STREAMDATASHREDTYPE2 ;

// �X�g���[���f�[�^����p�֐��|�C���^�\����
typedef struct tagSTREAMDATASHRED
{
	long					(*Tell)( void *StreamDataPoint ) ;
	int						(*Seek)( void *StreamDataPoint, long SeekPoint, int SeekType ) ;
	size_t					(*Read)( void *Buffer, size_t BlockSize, size_t DataNum, void *StreamDataPoint ) ;
//	size_t					(*Write)( void *Buffer, size_t BlockSize, size_t DataNum, void *StreamDataPoint ) ;
	int						(*Eof)( void *StreamDataPoint ) ;
	int						(*IdleCheck)( void *StreamDataPoint ) ;
	int						(*Close)( void *StreamDataPoint ) ;
} STREAMDATASHRED, *LPSTREAMDATASHRED ;

// �X�g���[���f�[�^����p�f�[�^�\����
typedef struct tagSTREAMDATA
{
	STREAMDATASHRED			ReadShred ;
	void					*DataPoint ;
} STREAMDATA ;




#ifndef DX_NOTUSE_DRAWFUNCTION

// �������ɒu���ꂽ�f�[�^���t�@�C���Ƃ��Ĉ������߂̃f�[�^�\����
typedef struct tagMEMSTREAMDATA
{
	unsigned char			*DataBuffer ;
	unsigned int			DataSize ;
	int						DataPoint ;
	int						EOFFlag ;
} MEMSTREAMDATA, *LPMEMSTREAMDATA ;

// �p���b�g���\����
typedef struct tagCOLORPALETTEDATA
{
	unsigned char			Blue ;
	unsigned char			Green ;
	unsigned char			Red ;
	unsigned char			Alpha ;
} COLORPALETTEDATA ;

// �J���[�\�����\����
typedef struct tagCOLORDATA
{
	unsigned short			ColorBitDepth ;									// �r�b�g�[�x
	unsigned short			PixelByte ;										// �P�s�N�Z��������̃o�C�g��
	unsigned char			RedWidth, GreenWidth, BlueWidth, AlphaWidth ;	// �e�F�̃r�b�g��
	unsigned char			RedLoc	, GreenLoc  , BlueLoc  , AlphaLoc   ;	// �e�F�̔z�u����Ă���r�b�g�A�h���X
	unsigned int			RedMask , GreenMask , BlueMask , AlphaMask  ;	// �e�F�̃r�b�g�}�X�N
	unsigned int			NoneMask ;										// �g���Ă��Ȃ��r�b�g�̃}�X�N
	COLORPALETTEDATA		Palette[256] ;									// �p���b�g(�r�b�g�[�x���W�ȉ��̏ꍇ�̂ݗL��)
	unsigned char			NoneLoc, NoneWidth;								// �g���Ă��Ȃ��r�b�g�̃A�h���X�ƕ�
} COLORDATA, *LPCOLORDATA ;

// ��{�C���[�W�f�[�^�\����
typedef struct tagBASEIMAGE
{
	COLORDATA				ColorData ;							// �F���
	int						Width, Height, Pitch ;				// ���A�����A�s�b�`
	void					*GraphData ;						// �O���t�B�b�N�C���[�W
} BASEIMAGE, GRAPHIMAGE, *LPGRAPHIMAGE ;

// ���C���f�[�^�^
typedef struct tagLINEDATA
{
	int						x1, y1, x2, y2 ;					// ���W
	int						color ;								// �F
	int						pal ;								// �p�����[�^
} LINEDATA, *LPLINEDATA ;

// ���W�f�[�^�^
typedef struct tagPOINTDATA
{
	int						x, y ;								// ���W
	int						color ;								// �F
	int						pal ;								// �p�����[�^
} POINTDATA, *LPPOINTDATA ;

// �C���[�W�t�H�[�}�b�g�f�[�^
typedef struct tagIMAGEFORMATDESC
{
	unsigned char			TextureFlag ;					// �e�N�X�`�����A�t���O( TRUE:�e�N�X�`��  FALSE:�W���T�[�t�F�X )
	unsigned char			AlphaChFlag ;					// ���`�����l���͂��邩�A�t���O	( TRUE:����  FALSE:�Ȃ� )
	unsigned char			DrawValidFlag ;					// �`��\���A�t���O( TRUE:�\  FALSE:�s�\ )
	unsigned char			SystemMemFlag ;					// �V�X�e����������ɑ��݂��Ă��邩�A�t���O( TRUE:�V�X�e����������  FALSE:�u�q�`�l�� )( �W���T�[�t�F�X�̎��̂ݗL�� )
	unsigned char			NotManagedTextureFlag ;			// �}�l�[�W�h�e�N�X�`�����g�p���Ȃ����A�t���O

	unsigned char			AlphaTestFlag ;					// ���e�X�g�`�����l���͂��邩�A�t���O( TRUE:����  FALSE:�Ȃ� )( �e�N�X�`���̏ꍇ�̂ݗL�� )
	unsigned char			ColorBitDepth ;					// �F�[�x( �e�N�X�`���̏ꍇ�̂ݗL�� )
	unsigned char			BlendGraphFlag ;				// �u�����h�p�摜���A�t���O
	unsigned char			UsePaletteFlag ;				// �p���b�g���g�p���Ă��邩�A�t���O( SystemMemFlag �� TRUE �̏ꍇ�̂ݗL�� )
} IMAGEFORMATDESC ;

#endif // DX_NOTUSE_DRAWFUNCTION







// WinSockets�g�p���̃A�h���X�w��p�\����
typedef struct tagIPDATA
{
	union
	{
		struct
		{
			unsigned char	d1, d2, d3, d4 ;				// �A�h���X�l
		} ;
		unsigned int		dall ;
	} ;
} IPDATA, *LPIPDATA ;



#define DX_STRUCT_END


// �֐��v���g�^�C�v�錾------------------------------------------------------------------

#define DX_FUNCTION_START

// DxWin.cpp�֐��v���g�^�C�v�錾

// �������I���n�֐�
extern	int			DxLib_Init( void ) ;													// ���C�u�����������֐�
extern	int			DxLib_End( void ) ;														// ���C�u�����g�p�̏I���֐�

extern	int			DxLib_GlobalStructInitialize( void ) ;									// ���C�u�����̓����Ŏg�p���Ă���\���̂��[�����������āADxLib_Init �̑O�ɍs�����ݒ�𖳌�������( DxLib_Init �̑O�ł̂ݗL�� )
extern	int			DxLib_IsInit( void ) ;													// ���C�u����������������Ă��邩�ǂ������擾����( �߂�l: TRUE=����������Ă���  FALSE=����Ă��Ȃ� )

// �G���[�����֐�
extern	BOOL		ErrorLogAdd( const char *ErrorStr ) ;									// �G���[�����������o��
extern 	BOOL		ErrorLogFmtAdd( const char *FormatString , ... ) ;						// �����t���G���[�����������o��
extern	BOOL		ErrorLogTabAdd( void ) ;												// �^�u���𑝂₷
extern	BOOL		ErrorLogTabSub( void ) ;												// �^�u�������炷
extern	BOOL		SetUseTimeStampFlag( int UseFlag ) ;									// �^�C���X�^���v�̗L����ݒ肷��
extern 	BOOL		AppLogAdd( const char *String , ... ) ;									// �����t�����O������������o��

// �������m�یn�֐�
extern	void*		DxAlloc( size_t AllocSize , const char *File = NULL , int Line = -1 ) ;	// ���������m�ۂ���
extern	void*		DxCalloc( size_t AllocSize , const char *File = NULL , int Line = -1 ) ;	// ���������m�ۂ��ĂO�ŏ���������
extern	void*		DxRealloc( void *Memory , size_t AllocSize , const char *File = NULL , int Line = -1 ) ;	// �������̍Ċm�ۂ��s��
extern	void		DxFree( void *Memory ) ;												// ���������������
extern	size_t		DxSetAllocSizeTrap( size_t Size ) ;										// �񋓑Ώۂɂ��郁�����̊m�ۗe�ʂ��Z�b�g����
extern	int			DxSetAllocPrintFlag( int Flag ) ;										// �c�w���C�u�������Ń������m�ۂ��s���鎞�ɏ����o�͂��邩�ǂ������Z�b�g����
extern	size_t		DxGetAllocSize( void ) ;												// �m�ۂ��Ă��郁�����T�C�Y���擾����
extern	int			DxGetAllocNum( void ) ;													// �m�ۂ��Ă��郁�����̐����擾����
extern	void		DxDumpAlloc( void ) ;													// �m�ۂ��Ă��郁������񋓂���
extern	int			DxErrorCheckAlloc( void ) ;												// �m�ۂ�����������񂪔j�󂳂�Ă��Ȃ������ׂ�( -1:�j�󂠂�  0:�Ȃ� )
extern	int			DxSetAllocSizeOutFlag( int Flag ) ;										// ���������m�ہA������s����x�Ɋm�ۂ��Ă��郁�����̗e�ʂ��o�͂��邩�ǂ����̃t���O���Z�b�g����
extern	int			DxSetAllocMemoryErrorCheckFlag( int Flag ) ;							// �������̊m�ہA������s����x�Ɋm�ۂ��Ă��郁�����m�ۏ�񂪔j�����Ă��Ȃ������ׂ邩�ǂ����̃t���O���Z�b�g����

// ���O�o�͋@�\�֐�
extern	int			SetLogDrawOutFlag( int DrawFlag ) ;										// ���O�o�̓t���O���Z�b�g����
extern 	int			GetLogDrawFlag( void ) ;												// ���O�o�͂����邩�t���O�̎擾

// �ȈՉ�ʏo�͊֐�
extern 	int			printfDx( const char *FormatString , ... ) ;							// �ȈՉ�ʏo��
extern	int			clsDx( void ) ;															// �ȈՉ�ʏo�͂��N���A����

// �t�@�C���A�N�Z�X�֐�
extern	int			FileRead_open( const char *FilePath , int ASync = FALSE ) ;			// �t�@�C�����J��
extern	int			FileRead_size( const char *FilePath ) ;								// �t�@�C���̃T�C�Y�𓾂�
extern	int			FileRead_close( int FileHandle ) ;									// �t�@�C�������
extern	int			FileRead_tell( int FileHandle ) ;									// �t�@�C���|�C���^�̌��݈ʒu�𓾂�
extern	int			FileRead_seek( int FileHandle , int Offset , int Origin ) ;			// �t�@�C���|�C���^�̈ʒu��ύX����
extern	int			FileRead_read( void *Buffer , int ReadSize , int FileHandle ) ;		// �t�@�C������f�[�^��ǂݍ���
extern	int			FileRead_idle_chk( int FileHandle ) ;								// �t�@�C���ǂݍ��݂��������Ă��邩�ǂ������擾����
extern	int			FileRead_eof( int FileHandle ) ;									// �t�@�C���̏I�[���ǂ����𓾂�
extern	int			FileRead_gets( char *Buffer , int BufferSize , int FileHandle ) ;	// �t�@�C�����當�����ǂݏo��
extern	int			FileRead_getc( int FileHandle ) ;									// �t�@�C������ꕶ���ǂݏo��
extern	int			FileRead_scanf( int FileHandle , const char *Format , ... ) ;		// �t�@�C�����珑�������ꂽ�f�[�^��ǂݏo��

extern	int			FileRead_createInfo( const char *ObjectPath ) ;						// �t�@�C�����n���h�����쐬����( �߂�l  -1:�G���[  -1�ȊO:�t�@�C�����n���h�� )
extern	int			FileRead_getInfoNum( int FileInfoHandle ) ;							// �t�@�C�����n���h�����̃t�@�C���̐����擾����
extern	int			FileRead_getInfo( int Index , FILEINFO *Buffer , int FileInfoHandle ) ;	// �t�@�C�����n���h�����̃t�@�C���̏����擾����
extern	int			FileRead_deleteInfo( int FileInfoHandle ) ;							// �t�@�C�����n���h�����폜����

extern	int			FileRead_findFirst( const char *FilePath, FILEINFO *Buffer ) ;		// �w��̃t�@�C�����̓t�H���_�̏����擾���A�t�@�C�������n���h�����쐬����( �߂�l: -1=�G���[  -1�ȊO=�t�@�C�������n���h�� )
extern	int			FileRead_findNext( int FindHandle, FILEINFO *Buffer ) ;				// �����̍��v���鎟�̃t�@�C���̏����擾����( �߂�l: -1=�G���[  0=���� )
extern	int			FileRead_findClose( int FindHandle ) ;								// �t�@�C�������n���h�������( �߂�l: -1=�G���[  0=���� )

// �֗��֐�
extern	int			GetResourceInfo( const char *ResourceName , const char *ResourceType , void **DataPointerP , int *DataSizeP ) ;		// �w��̃��\�[�X���擾����( -1:���s  0:���� )

// ���b�Z�[�W�����֐�
extern	int			ProcessMessage( void ) ;												// �E�C���h�E�Y�̃��b�Z�[�W���[�v�ɑ��鏈�����s��

// �E�C���h�E�֌W���擾�֐�
extern	int			GetWindowCRect( RECT *RectBuf ) ;										// �E�C���h�E�̃N���C�A���g�̈���擾����
extern	int			GetWindowActiveFlag( void ) ;											// �E�C���h�E�̃A�N�e�B�u�t���O���擾
extern	HWND		GetMainWindowHandle( void ) ;											// ���C���E�C���h�E�̃n���h�����擾����
extern	int			GetWindowModeFlag( void ) ;												// �E�C���h�E���[�h�ŋN�����Ă��邩�A�̃t���O���擾����
extern	int			GetDefaultState( int *SizeX , int *SizeY , int *ColorBitDepth ) ;		// �N�����̃f�X�N�g�b�v�̉�ʃ��[�h���擾����
extern	int			GetActiveFlag( void ) ;													// �\�t�g���A�N�e�B�u���ǂ������擾����
extern	int			GetNoActiveState( int ResetFlag = TRUE ) ;								// ��A�N�e�B�u�ɂȂ�A�������ꎞ��~���Ă������ǂ������擾����(���� ResetFlag=TRUE:��Ԃ����Z�b�g FALSE:��Ԃ����Z�b�g���Ȃ�    �߂�l: 0=�ꎞ��~�͂��Ă��Ȃ�  1=�ꎞ��~���Ă��� )
extern	int			GetMouseDispFlag( void ) ;												// �}�E�X��\�����邩�ǂ����̃t���O���擾����
extern	int			GetAlwaysRunFlag( void ) ;												// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���擾����
extern	int			_GetSystemInfo( int *DxLibVer , int *DirectXVer , int *WindowsVer ) ;	// �c�w���C�u������ DirectX �̃o�[�W������ Windows �̃o�[�W�����𓾂�
extern	int			GetPcInfo( char *OSString , char *DirectXString ,
								char *CPUString , int *CPUSpeed /* �P��MHz */ ,
								double *FreeMemorySize /* �P��MByte */ , double *TotalMemorySize ,
								char *VideoDriverFileName , char *VideoDriverString ,
								double *FreeVideoMemorySize /* �P��MByte */ , double *TotalVideoMemorySize ) ;	// �o�b�̏��𓾂�
extern	int			GetUseMMXFlag( void ) ;													// �l�l�w���g���邩�ǂ����̏��𓾂�
extern	int			GetUseSSEFlag( void ) ;													// �r�r�d���g���邩�ǂ����̏��𓾂�
extern	int			GetUseSSE2Flag( void ) ;												// �r�r�d�Q���g���邩�ǂ����̏��𓾂�
extern	int			GetWindowCloseFlag( void ) ;											// �E�C���h�E����悤�Ƃ��Ă��邩�̏��𓾂�
extern	HINSTANCE	GetTaskInstance( void ) ;												// �\�t�g�̃C���X�^���X���擾����
extern	int			GetUseWindowRgnFlag( void ) ;											// ���[�W�������g���Ă��邩�ǂ������擾����
extern	int			GetWindowSizeChangeEnableFlag( int *FitScreen = NULL ) ;				// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���擾����
extern	double		GetWindowSizeExtendRate( void ) ;										// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦���擾����
extern	int			GetWindowUserCloseFlag( int StateResetFlag = FALSE ) ;					// �E�C���h�E�̕���{�^���������ꂽ���ǂ������擾����
extern	int			GetNotDrawFlag( void ) ;												// �`��@�\���g�����ǂ����̃t���O���擾����
extern	int			GetPaintMessageFlag( void ) ;											// WM_PAINT ���b�Z�[�W���������ǂ������擾����(�߂�l  TRUE:WM_PAINT���b�Z�[�W������(��x�擾����ƈȌ�A�Ă� WM_PAINT���b�Z�[�W������܂� FALSE ���Ԃ��Ă���悤�ɂȂ�)  FALSE:WM_PAINT ���b�Z�[�W�͗��Ă��Ȃ�)
extern	int			GetValidHiPerformanceCounter( void ) ;									// �p�t�H�[�}���X�J�E���^���L�����ǂ������擾����(�߂�l  TRUE:�L��  FALSE:����)

// �ݒ�n�֐�
extern	int			ChangeWindowMode( int Flag ) ;											// �E�C���h�E���[�h��ύX����
extern	int			LoadPauseGraph( const char *FileName ) ;								// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			LoadPauseGraphFromMem( void *MemImage , int MemImageSize ) ;			// �A�N�e�B�u�E�C���h�E�����̃\�t�g�Ɉڂ��Ă���ۂɕ\������摜�̃��[�h(NULL �ŉ���)
extern	int			SetActiveStateChangeCallBackFunction( int (* CallBackFunction )( int ActiveState , void * UserData ) , void *UserData ) ;	// �E�C���h�E�̃A�N�e�B�u��Ԃɕω����������Ƃ��ɌĂ΂��R�[���o�b�N�֐����Z�b�g����( NULL ���Z�b�g����ƌĂ΂�Ȃ��Ȃ� )
extern	int			SetWindowText( const char *WindowText ) ;								// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			SetMainWindowText( const char *WindowText ) ;							// ���C���E�C���h�E�̃E�C���h�E�e�L�X�g��ύX����
extern	int			SetMainWindowClassName( const char *ClassName ) ;						// ���C���E�C���h�E�̃N���X����ݒ肷��
extern	int			SetOutApplicationLogValidFlag( int Flag ) ;								// ���O�o�͂��s�����ۂ��̃Z�b�g
extern	int			SetAlwaysRunFlag( int Flag ) ;											// �E�C���h�E���A�N�e�B�u�ł͂Ȃ���Ԃł������𑱍s���邩�A�t���O���Z�b�g����
extern	int			SetWindowIconID( int ID ) ;												// �g�p����A�C�R���̂h�c���Z�b�g����
extern	int			SetUseASyncChangeWindowModeFunction( int Flag ,
										 void (* CallBackFunction )( void * ) , void *Data ) ;	// �ő剻�{�^����ALT+ENTER�L�[�ɂ��񓯊��ȃE�C���h�E���[�h�̕ύX�̋@�\�̐ݒ���s��
extern	int			SetWindowStyleMode( int Mode ) ;										// �E�C���h�E�̃X�^�C����ύX����
extern	int			SetWindowSizeChangeEnableFlag( int Flag, int FitScreen = TRUE ) ;		// �E�C���h�E�̃T�C�Y��ύX�ł��邩�ǂ����̃t���O���Z�b�g����( NotFitScreen:�E�C���h�E�̃N���C�A���g�̈�ɉ�ʂ��t�B�b�g������(�g�傳����)���ǂ���  TRUE:�t�B�b�g������  FALSE:�t�B�b�g�����Ȃ� )
extern	int			SetWindowSizeExtendRate( double ExRate ) ;								// �`���ʂ̃T�C�Y�ɑ΂���E�C���h�E�T�C�Y�̔䗦��ݒ肷��
extern	int			SetSysCommandOffFlag( int Flag , const char *HookDllPath = NULL ) ;	// �^�X�N�X�C�b�`��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			SetHookWinProc( WNDPROC WinProc ) ;										// ���b�Z�[�W���t�b�N����E�C���h�E�v���[�W����o�^����
extern	int			SetDoubleStartValidFlag( int Flag ) ;									// �Q�d�N�����������ǂ����̃t���O���Z�b�g����
extern	int			AddMessageTakeOverWindow( HWND Window ) ;								// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E��ǉ�����
extern	int			SubMessageTakeOverWindow( HWND Window ) ;								// ���b�Z�[�W�������c�w���C�u�����Ɍ����肵�Ă��炤�E�C���h�E�����炷

extern	int			SetWindowInitPosition( int x , int y ) ;									// �E�C���h�E�̏����ʒu��ݒ肷��
extern	int			SetNotWinFlag( int Flag ) ;												// �c�w���C�u�����̃E�C���h�E�֘A�̋@�\���g�p���Ȃ��t���O
extern	int			SetNotDrawFlag( int Flag ) ;											// �`��@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			SetNotSoundFlag( int Flag ) ;											// �T�E���h�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			SetNotInputFlag( int Flag ) ;											// ���͏�Ԃ̎擾�@�\���g�����ǂ����̃t���O���Z�b�g����
extern	int			SetDialogBoxHandle( HWND WindowHandle ) ;								// �c�w���C�u�����Ń��b�Z�[�W�������s���_�C�A���O�{�b�N�X��o�^����
extern	int			ChangeStreamFunction( STREAMDATASHREDTYPE2 *StreamThread ) ;			// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐���ύX����
extern	int			GetStreamFunctionDefault( void ) ;										// �c�w���C�u�����ŃX�g���[���f�[�^�A�N�Z�X�Ɏg�p����֐����f�t�H���g�̂��̂����ׂ�( TRUE:�f�t�H���g  FALSE:�f�t�H���g�ł͂Ȃ� )
extern	int			SetWindowVisibleFlag( int Flag ) ;										// ���C���E�C���h�E��\�����邩�ǂ����̃t���O���Z�b�g����
extern	int			SetWindowUserCloseEnableFlag( int Flag ) ;								// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����
extern	int			SetDxLibEndPostQuitMessageFlag( int Flag ) ;							// �c�w���C�u�����I������ PostQuitMessage ���ĂԂ��ǂ����̃t���O���Z�b�g����
extern	int			SetUserWindow( HWND WindowHandle ) ;									// �c�w���C�u�����ŗ��p����E�C���h�E�̃n���h�����Z�b�g����(DxLib_Init �����s����ȑO�ł̂ݗL��)
extern	int			SetUserWindowMessageProcessDXLibFlag( int Flag ) ;						// SetUseWindow �Őݒ肵���E�C���h�E�̃��b�Z�[�W���[�v�������c�w���C�u�����ōs�����ǂ����A�t���O���Z�b�g����
extern	int			SetUseDXArchiveFlag( int Flag ) ;										// �c�w�A�[�J�C�u�t�@�C���̓ǂݍ��݋@�\���g�����ǂ�����ݒ肷��( FALSE:�g�p���Ȃ�  TRUE:�g�p���� )
extern	int			SetDXArchiveExtension( const char *Extension = NULL ) ;					// ��������c�w�A�[�J�C�u�t�@�C���̊g���q��ύX����
extern	int			SetDXArchiveKeyString( const char *KeyString = NULL ) ;					// �c�w�A�[�J�C�u�t�@�C���̌��������ݒ肷��
extern	int			SetUseDateNameLogFile( int Flag ) ;										// ���O�t�@�C�����ɓ��t�����邩�ǂ������Z�b�g����
extern	int			SetBackgroundColor( int Red, int Green, int Blue ) ;					// ���C���E�C���h�E�̃o�b�N�O���E���h�J���[��ݒ肷��
extern	int			SetLogFontSize( int Size ) ;											// printfDx �ŉ�ʂɏo�͂��郍�O�t�H���g�̃T�C�Y��ύX����


// �h���b�O���h���b�v���ꂽ�t�@�C���֌W
extern	int			SetDragFileValidFlag( int Flag ) ;										// �t�@�C���̃h���b�O���h���b�v�@�\��L���ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int			DragFileInfoClear( void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̏�������������
extern	int			GetDragFilePath( char *FilePathBuffer ) ;								// �h���b�O���h���b�v���ꂽ�t�@�C�������擾����( -1:�擾�ł��Ȃ�����  0:�擾�ł��� )
extern	int			GetDragFileNum( void ) ;												// �h���b�O���h���b�v���ꂽ�t�@�C���̐����擾����

// �E�C���h�E�`��̈�ݒ�n�֐�
extern	HRGN		CreateRgnFromGraph( int Width , int Height , void *MaskData , int Pitch , int Byte ) ; // �C�ӂ̃O���t�B�b�N����RGN�n���h�����쐬����
extern	int			SetWindowRgnGraph( const char *FileName ) ;								// �C�ӂ̃O���t�B�b�N����q�f�m���Z�b�g����

// �c�[���o�[�֌W
extern	int			SetupToolBar( const char *BitmapName , int DivNum , int ResourceID = -1 ) ;				// �c�[���o�[�̏���( NULL ���w�肷��ƃc�[���o�[�������AResourceID �� BitmapName �� NULL �̍ۂɎg�p����� )
extern	int			AddToolBarButton( int Type /* TOOLBUTTON_TYPE_NORMAL �� */ , int State /* TOOLBUTTON_STATE_ENABLE �� */ , int ImageIndex, int ID ) ;		// �c�[���o�[�Ƀ{�^����ǉ�
extern	int			AddToolBarSep( void ) ;												// �c�[���o�[�Ɍ��Ԃ�ǉ�
extern	int			GetToolBarButtonState( int ID ) ;									// �c�[���o�[�̃{�^���̏�Ԃ��擾( TRUE:������Ă��� or �����ꂽ  FALSE:������Ă��Ȃ� )
extern	int			SetToolBarButtonState( int ID , int State ) ;						// �c�[���o�[�̃{�^���̏�Ԃ�ݒ�
extern	int			DeleteAllToolBarButton( void ) ;									// �c�[���o�[�̃{�^����S�č폜

// ���j���[�֌W
extern	int			SetUseMenuFlag( int Flag ) ;												// ���j���[��L���ɂ��邩�ǂ�����ݒ肷��
extern	int			SetUseKeyAccelFlag( int Flag ) ;											// �L�[�{�[�h�A�N�Z�����[�^�[���g�p���邩�ǂ�����ݒ肷��

extern	int			AddKeyAccel( const char *ItemName , int ItemID , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			AddKeyAccel_Name( const char *ItemName , int KeyCode , int CtrlFlag , int AltFlag , int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			AddKeyAccel_ID( int ItemID, int KeyCode, int CtrlFlag, int AltFlag, int ShiftFlag ) ;	// �V���[�g�J�b�g�L�[��ǉ�����
extern	int			ClearKeyAccel( void ) ;														// �V���[�g�J�b�g�L�[�̏�������������

extern	int			AddMenuItem( int AddType /* MENUITEM_ADD_CHILD�� */ , const char *ItemName, int ItemID,
									int SeparatorFlag, const char *NewItemName = NULL , int NewItemID = -1 ) ;	// ���j���[�ɍ��ڂ�ǉ�����
extern	int			DeleteMenuItem( const char *ItemName, int ItemID ) ;						// ���j���[����I�����ڂ��폜����
extern	int			CheckMenuItemSelect( const char *ItemName, int ItemID ) ;					// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			SetMenuItemEnable( const char *ItemName, int ItemID, int EnableFlag ) ;		// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��
extern	int			SetMenuItemMark( const char *ItemName, int ItemID, int Mark ) ;				// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��

extern	int			AddMenuItem_Name( const char *ParentItemName, const char *NewItemName ) ;	// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			AddMenuLine_Name( const char *ParentItemName ) ;							// ���j���[�̃��X�g�ɋ�؂����ǉ�����
extern	int			InsertMenuItem_Name( const char *ItemName, const char *NewItemName ) ;		// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			InsertMenuLine_Name( const char *ItemName ) ;								// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			DeleteMenuItem_Name( const char *ItemName ) ;								// ���j���[����I�����ڂ��폜����
extern	int			CheckMenuItemSelect_Name( const char *ItemName ) ;							// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			SetMenuItemEnable_Name( const char *ItemName, int EnableFlag ) ;			// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��( 1:�I���ł���  0:�I���ł��Ȃ� )
extern	int			SetMenuItemMark_Name( const char *ItemName, int Mark ) ;					// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��

extern	int			AddMenuItem_ID( int ParentItemID, const char *NewItemName, int NewItemID = -1 ) ;	// ���j���[�ɑI�����ڂ�ǉ�����
extern	int			AddMenuLine_ID( int ParentItemID ) ;										// ���j���[�̃��X�g�ɋ�؂����ǉ�����
extern	int			InsertMenuItem_ID( int ItemID, int NewItemID ) ;							// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊ԂɐV�������ڂ�ǉ�����
extern	int			InsertMenuLine_ID( int ItemID, int NewItemID ) ;							// �w��̍��ڂƁA�w��̍��ڂ̈��̍��ڂƂ̊Ԃɋ�؂����ǉ�����
extern	int			DeleteMenuItem_ID( int ItemID ) ;											// ���j���[����I�����ڂ��폜����
extern	int			CheckMenuItemSelect_ID( int ItemID ) ;										// ���j���[���I�����ꂽ���ǂ������擾����( 0:�I������Ă��Ȃ�  1:�I�����ꂽ )
extern	int			SetMenuItemEnable_ID( int ItemID, int EnableFlag ) ;						// ���j���[�̍��ڂ�I���o���邩�ǂ�����ݒ肷��
extern	int			SetMenuItemMark_ID( int ItemID, int Mark ) ;								// ���j���[�̍��ڂɃ`�F�b�N�}�[�N�⃉�W�I�{�^����\�����邩�ǂ�����ݒ肷��

extern	int			DeleteMenuItemAll( void ) ;													// ���j���[�̑S�Ă̑I�����ڂ��폜����
extern	int			ClearMenuItemSelect( void ) ;												// ���j���[���I�����ꂽ���ǂ����̏���������
extern	int			GetMenuItemID( const char *ItemName ) ;										// ���j���[�̍��ږ�����h�c���擾����
extern	int			GetMenuItemName( int ItemID, char *NameBuffer ) ;							// ���j���[�̍��ږ�����h�c���擾����
extern	int 		LoadMenuResource( int MenuResourceID ) ;									// ���j���[�����\�[�X����ǂݍ���
extern	int			SetMenuItemSelectCallBackFunction( void (* CallBackFunction )( const char *ItemName, int ItemID ) ) ; // ���j���[�̑I�����ڂ��I�����ꂽ�Ƃ��ɌĂ΂��R�[���o�b�N�֐���ݒ肷��

extern	int			SetWindowMenu( int MenuID, int (* MenuProc )( WORD ID ) ) ;				// (�Â��֐�)�E�C���h�E�Ƀ��j���[��ݒ肷��
extern	int			SetDisplayMenuFlag( int Flag ) ;										// ���j���[��\�����邩�ǂ������Z�b�g����
extern	int			GetDisplayMenuFlag( void ) ;											// ���j���[��\�����Ă��邩�ǂ������擾����
extern	int			GetUseMenuFlag( void ) ;												// ���j���[���g�p���Ă��邩�ǂ����𓾂�
extern	int			SetAutoMenuDisplayFlag( int Flag ) ;									// �t���X�N���[�����Ƀ��j���[�������ŕ\���������\���ɂ����肷�邩�ǂ����̃t���O���Z�b�g����

// �}�E�X�֌W�֐�
extern	int			SetMouseDispFlag( int DispFlag ) ;										// �}�E�X�̕\���t���O�̃Z�b�g
extern	int			GetMousePoint( int *XBuf, int *YBuf ) ;									// �}�E�X�̈ʒu���擾����
extern	int			SetMousePoint( int PointX, int PointY ) ;								// �}�E�X�̈ʒu���Z�b�g����
extern	int			GetMouseInput( void ) ;													// �}�E�X�̃{�^���̏�Ԃ𓾂� 
extern	int			GetMouseWheelRotVol( void ) ;											// �}�E�X�z�C�[���̉�]�ʂ𓾂�

// �E�G�C�g�n�֐�
extern	int			WaitTimer( int WaitTime ) ;												// �w��̎��Ԃ����������Ƃ߂�
extern	int			WaitKey( void ) ;														// �L�[�̓��͑҂�

// �J�E���^�y�ю����擾�n�֐�
extern	int			GetNowCount( int UseRDTSCFlag = FALSE ) ;								// �~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
extern	LONGLONG	GetNowHiPerformanceCount( int UseRDTSCFlag = FALSE ) ;					// GetNowCount�̍����x�o�[�W����
extern	int			GetDateTime( DATEDATA *DateBuf ) ;										// ���ݎ������擾���� 

// �����擾
extern	int			GetRand( int RandMax ) ;												// �������擾����( RandMax : �Ԃ��ė���l�̍ő�l )
extern	int			SRand( int Seed ) ;														// �����̏����l��ݒ肷��

#ifndef DX_NON_NETWORK

// �ʐM�֌W
extern	int			ProcessNetMessage( int RunReleaseProcess = FALSE ) ;					// �ʐM���b�Z�[�W�̏���������֐�

extern	int			GetHostIPbyName( const char *HostName, IPDATA *IPDataBuf ) ;			// �c�m�r�T�[�o�[���g���ăz�X�g������h�o�A�h���X���擾����
extern 	int			ConnectNetWork( IPDATA IPData, int Port = -1 ) ;							// ���}�V���ɐڑ�����
extern 	int			PreparationListenNetWork( int Port = -1 ) ;								// �ڑ����󂯂����Ԃɂ���
extern 	int			StopListenNetWork( void ) ;												// �ڑ����󂯂���Ԃ̉���
extern 	int			CloseNetWork( int NetHandle ) ;											// �ڑ����I������

extern 	int			GetNetWorkAcceptState( int NetHandle ) ;								// �ڑ���Ԃ��擾����
extern 	int			GetNetWorkDataLength( int NetHandle ) ;									// ��M�f�[�^�̗ʂ𓾂�
extern	int			GetNetWorkSendDataLength( int NetHandle ) ;								// �����M�̃f�[�^�̗ʂ𓾂� 
extern 	int			GetNewAcceptNetWork( void ) ;											// �V���ɐڑ������ʐM����𓾂�
extern 	int			GetLostNetWork( void ) ;												// �ڑ���ؒf���ꂽ�ʐM����𓾂�
extern 	int			GetNetWorkIP( int NetHandle, IPDATA *IpBuf ) ;							// �ڑ���̂h�o�𓾂�
extern	int			GetMyIPAddress( IPDATA *IpBuf ) ;										// �����̂h�o�𓾂�
extern	int			SetConnectTimeOutWait( int Time ) ;										// �ڑ��̃^�C���A�E�g�܂ł̎��Ԃ�ݒ肷��
extern	int			SetUseDXNetWorkProtocol( int Flag ) ;									// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������Z�b�g����
extern	int			GetUseDXNetWorkProtocol( void ) ; 										// �c�w���C�u�����̒ʐM�`�Ԃ��g�����ǂ������擾����
extern	int			SetUseDXProtocol( int Flag ) ;											// SetUseDXNetWorkProtocol �̕ʖ�
extern	int			GetUseDXProtocol( void ) ; 												// GetUseDXNetWorkProtocol �̕ʖ�
extern	int			SetNetWorkCloseAfterLostFlag( int Flag ) ;								// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���Z�b�g����
extern	int			GetNetWorkCloseAfterLostFlag( void ) ;									// �ڑ����ؒf���ꂽ����ɐڑ��n���h����������邩�ǂ����̃t���O���擾����
extern	int			SetProxySetting( int UseFlag, char *Address, int Port ) ;						// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���s��
extern	int			GetProxySetting( int *UseFlagBuffer, char *AddressBuffer, int *PortBuffer ) ;	// �g�s�s�o�ʐM�Ŏg�p����v���L�V�ݒ���擾����
extern	int			SetIEProxySetting( void ) ;												// �h�d�̃v���L�V�ݒ��K������


extern 	int			NetWorkRecv( int NetHandle, void *Buffer, int Length ) ;				// ��M�����f�[�^��ǂݍ���
extern	int			NetWorkRecvToPeek( int NetHandle, void *Buffer, int Length ) ;			// ��M�����f�[�^��ǂݍ��ށA�ǂݍ��񂾃f�[�^�̓o�b�t�@����폜����Ȃ�
extern	int			NetWorkRecvBufferClear( int NetHandle ) ;								// ��M�����f�[�^���N���A����
extern 	int			NetWorkSend( int NetHandle, void *Buffer, int Length ) ;				// �f�[�^�𑗐M����

/*	�g�p�s��
extern	int			HTTP_FileDownload( const char *FileURL, const char *SavePath = NULL ,
										 void **SaveBufferP = NULL , int *FileSize = NULL ,
										 char **ParamList = NULL ) ;						// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C�����_�E�����[�h����
extern	int			HTTP_GetFileSize( const char *FileURL ) ;								// HTTP ���g�p���ăl�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂�

extern	int			HTTP_StartFileDownload( const char *FileURL, const char *SavePath, void **SaveBufferP = NULL , char **ParamList = NULL ) ;	// HTTP ���g�p�����l�b�g���[�N��̃t�@�C�����_�E�����[�h���鏈�����J�n����
extern	int			HTTP_StartGetFileSize( const char *FileURL ) ;							// HTTP ���g�p�����l�b�g���[�N��̃t�@�C���̃T�C�Y�𓾂鏈�����J�n����
extern	int			HTTP_Close( int HttpHandle ) ;											// HTTP �̏������I�����A�n���h�����������
extern	int			HTTP_CloseAll( void ) ;													// �S�Ẵn���h���ɑ΂��� HTTP_Close ���s��
extern	int			HTTP_GetState( int HttpHandle ) ;										// HTTP �����̌��݂̏�Ԃ𓾂�( NET_RES_COMPLETE �� )
extern	int			HTTP_GetError( int HttpHandle ) ;										// HTTP �����ŃG���[�����������ꍇ�A�G���[�̓��e�𓾂�( HTTP_ERR_NONE �� )
extern	int			HTTP_GetDownloadFileSize( int HttpHandle ) ;							// HTTP �����őΏۂƂȂ��Ă���t�@�C���̃T�C�Y�𓾂�( �߂�l: -1 = �G���[�E�Ⴕ���͂܂��t�@�C���̃T�C�Y���擾���Ă��Ȃ�  0�ȏ� = �t�@�C���̃T�C�Y )
extern	int			HTTP_GetDownloadedFileSize( int HttpHandle ) ;							// HTTP �����Ŋ��Ƀ_�E�����[�h�����t�@�C���̃T�C�Y���擾����

extern	int			fgetsForNetHandle( int NetHandle, char *strbuffer ) ;					// fgets �̃l�b�g���[�N�n���h����( -1:�擾�ł��� 0:�擾�ł��� )
extern	int			URLAnalys( const char *URL, char *HostBuf = NULL , char *PathBuf = NULL ,
												 char *FileNameBuf = NULL , int *PortBuf = NULL ) ;	// �t�q�k����͂���
extern	int			URLConvert( char *URL, int ParamConvert = TRUE , int NonConvert = FALSE ) ;	// HTTP �ɓn���Ȃ��L�����g��ꂽ�������n����悤�ȕ�����ɕϊ�����( �߂�l: -1 = �G���[  0�ȏ� = �ϊ���̕�����̃T�C�Y )
extern	int			URLParamAnalysis( char **ParamList, char **ParamStringP ) ;				// HTTP �p�p�����[�^���X�g�����̃p�����[�^��������쐬����( �߂�l:  -1 = �G���[  0�ȏ� = �p�����[�^�̕�����̒��� )
*/

#endif


// �����R�[�h�o�b�t�@����֌W
extern	int			StokInputChar( char CharCode ) ;																												// �o�b�t�@�ɃR�[�h���X�g�b�N����
extern	int			ClearInputCharBuf( void ) ;																														// �����R�[�h�o�b�t�@���N���A����
extern	char		GetInputChar( int DeleteFlag ) ;																												// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^���當���R�[�h���擾����
extern	char		GetInputCharWait( int DeleteFlag ) ;																											// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�o�C�g���擾����A�o�b�t�@�ɂȂɂ������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�

extern	int			GetOneChar( char *CharBuffer, int DeleteFlag ) ;																								// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����
extern	int			GetOneCharWait( char *CharBuffer, int DeleteFlag ) ;																							// �����R�[�h�o�b�t�@�ɗ��܂����f�[�^����P�������擾����A�o�b�t�@�ɉ��������R�[�h���Ȃ��ꍇ�̓L�[���������܂ő҂�
extern	int			GetCtrlCodeCmp( char Char ) ;																													// �A�X�L�[�R���g���[���R�[�h�����ׂ�

#ifndef DX_NON_KEYEX

extern	int			DrawIMEInputString( int x, int y, int SelectStringNum ) ;																						// ��ʏ�ɓ��͒��̕������`�悷��
extern	int			SetUseIMEFlag( int UseFlag ) ;																													// �h�l�d���g�p���邩�ǂ������Z�b�g����
extern	int			SetInputStringMaxLengthIMESync( int Flag ) ;																									// �h�l�d�œ��͂ł���ő啶������ MakeKeyInput �̐ݒ�ɍ��킹�邩�ǂ������Z�b�g����( TRUE:���킹��  FALSE:���킹�Ȃ�(�f�t�H���g) )
extern	int			SetIMEInputStringMaxLength( int Length ) ;																										// �h�l�d�ň�x�ɓ��͂ł���ő啶������ݒ肷��( 0:�����Ȃ�  1�ȏ�:�w��̕������Ő��� )

#endif

extern	int			GetStringPoint( const char *String, int Point ) ;																								// �S�p�����A���p�������藐��钆����w��̕������ł̔��p�������𓾂�
extern	int			GetStringPoint2( const char *String, int Point ) ;																								// �S�p�����A���p�������藐��钆����w��̕������ł̑S�p�������𓾂�

extern	int			DrawObtainsString( int x, int y, int AddY, const char *String, int StrColor , int StrEdgeColor = 0 , int FontHandle = -1 ) ;					// �K��̈�Ɏ��߂��������ŕ������`��
extern	int			DrawObtainsBox( int x1, int y1, int x2, int y2, int AddY, int Color, int FillFlag ) ;															// �K��̈�Ɏ��߂��������ŋ�`��`�� 

#ifndef DX_NON_KEYEX

extern	int			InputStringToCustom( int x, int y, int BufLength, char *StrBuffer, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag ) ;			// ������̓��͎擾

extern	int			KeyInputString( int x, int y, int CharMaxLength, char *StrBuffer, int CancelValidFlag ) ;														// ������̓��͎擾
extern	int			KeyInputSingleCharString( int x, int y, int CharMaxLength, char *StrBuffer, int CancelValidFlag ) ;												// ���p������݂̂̓��͎擾
extern	int			KeyInputNumber( int x, int y, int MaxNum, int MinNum, int CancelValidFlag ) ;																	// ���l�̓���

extern	int			GetIMEInputModeStr( char *GetBuffer ) ;																											// IME�̓��̓��[�h������̎擾
extern	IMEINPUTDATA* GetIMEInputData( void ) ;																														// IME�œ��͒��̕�����̏����擾����
extern	int			SetKeyInputStringColor( ULONGLONG NmlStr, ULONGLONG NmlCur, ULONGLONG IMEStr, ULONGLONG IMECur, ULONGLONG IMELine, ULONGLONG IMESelectStr, ULONGLONG IMEModeStr , ULONGLONG NmlStrE = 0 , ULONGLONG IMESelectStrE = 0 , ULONGLONG IMEModeStrE = 0 , ULONGLONG IMESelectWinE = 0xffffffffffffffff ,	ULONGLONG IMESelectWinF = 0xffffffffffffffff ) ;	// InputString�֐��g�p���̕����̊e�F��ύX����
extern	int			SetKeyInputStringFont( int FontHandle ) ;																										// �L�[���͕�����`��֘A�Ŏg�p����t�H���g�̃n���h����ύX����(-1�Ńf�t�H���g�̃t�H���g�n���h��)
extern	int			DrawKeyInputModeString( int x, int y ) ;																										// ���̓��[�h�������`�悷��

extern	int			InitKeyInput( void ) ;																															// �L�[���̓f�[�^������
extern	int			MakeKeyInput( int MaxStrLength, int CancelValidFlag, int SingleCharOnlyFlag, int NumCharOnlyFlag ) ;											// �V�����L�[���̓f�[�^�̍쐬
extern	int			DeleteKeyInput( int InputHandle ) ;																												// �L�[���̓f�[�^�̍폜
extern	int			SetActiveKeyInput( int InputHandle ) ;																											// �w��̃L�[���͂��A�N�e�B�u�ɂ���
extern	int			CheckKeyInput( int InputHandle ) ;																												// ���͂��I�����Ă��邩�擾����
extern	int			ProcessActKeyInput( void ) ;																													// �L�[���͏����֐�
extern	int			DrawKeyInputString( int x, int y, int InputHandle ) ;																							// �L�[���͒��f�[�^�̕`��

extern	int			SetKeyInputCursorBrinkTime( int Time ) ;																										// �L�[���͎��̃J�[�\���̓_�ł��鑁�����Z�b�g����
extern	int			SetKeyInputCursorBrinkFlag( int Flag ) ;																										// �L�[���͎��̃J�[�\����_�ł����邩�ǂ������Z�b�g����
extern	int			SetKeyInputString( const char *String, int InputHandle ) ;																						// �L�[���̓f�[�^�Ɏw��̕�������Z�b�g����
extern	int			SetKeyInputNumber( int Number, int InputHandle ) ;																								// �L�[���̓f�[�^�Ɏw��̐��l�𕶎��ɒu�������ăZ�b�g����
extern	int			GetKeyInputString( char *StrBuffer, int InputHandle ) ;																							// ���̓f�[�^�̕�������擾����
extern	int			GetKeyInputNumber( int InputHandle ) ;
extern	int			GetKeyInputCursorPosition( int InputHandle ) ;																									// �L�[���͂̌��݂̃J�[�\���ʒu���擾����

#endif


// �������ɒu���ꂽ�f�[�^���t�@�C���̃f�[�^�ɗႦ�Ă������߂̊֐�
extern	void*		MemStreamOpen( void *DataBuffer, unsigned int DataSize ) ;
extern	int			MemStreamClose( void *StreamDataPoint ) ;












// DxInput.cpp�֐��v���g�^�C�v�錾

// ���͏�Ԏ擾�֐�
extern	int CheckHitKey( int KeyCode ) ;											// �L�[�{�[�h�̓��͏�Ԏ擾
extern	int CheckHitKeyAll( int CheckType = DX_CHECKINPUT_ALL ) ;					// �S�L�[�̉�����Ԃ��擾
extern	int GetHitKeyStateAll( DX_CHAR *KeyStateBuf ) ;								// ���ׂẴL�[�̉�����Ԃ��擾����
extern	int SetKeyExclusiveCooperativeLevelFlag( int Flag ) ;						// �L�[�{�[�h�̋������x����r�����x���ɂ��邩�ǂ����̃t���O���Z�b�g����
extern	int GetJoypadNum( void ) ;													// �W���C�p�b�h���ڑ�����Ă��鐔���擾����
extern	int GetJoypadInputState( int InputType ) ;									// �W���C�o�b�h�̓��͏�Ԏ擾
extern	int GetJoypadAnalogInput( int *XBuf, int *YBuf, int InputType ) ;			// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�
extern	int GetJoypadAnalogInputRight( int *XBuf, int *YBuf, int InputType ) ;		// �W���C�p�b�h�̃A�i���O�I�ȃX�e�B�b�N���͏��𓾂�(�E�X�e�B�b�N�p)
extern	int KeyboradBufferProcess( void ) ;											// �L�[�{�[�h�̃o�b�t�@����f�[�^���擾���鏈��
extern	int GetJoypadGUID( int PadIndex, GUID *GuidBuffer ) ;						// �W���C�p�b�h�̂f�tI�c�𓾂�
extern	int ConvertKeyCodeToVirtualKey( int KeyCode ) ;								// �c�w���C�u�����̃L�[�R�[�h���� Windows �̉��z�L�[�R�[�h���擾����
extern	int SetJoypadInputToKeyInput( int InputType, int PadInput, int KeyInput1, int KeyInput2 = -1 , int KeyInput3 = -1 , int KeyInput4 = -1  ) ; // �W���C�p�b�h�̓��͂ɑΉ������L�[�{�[�h�̓��͂�ݒ肷��
extern	int SetJoypadDeadZone( int InputType, double Zone ) ;						// �W���C�p�b�h�̖����]�[���̐ݒ���s��
extern	int StartJoypadVibration( int InputType, int Power, int Time ) ;			// �W���C�p�b�h�̐U�����J�n����
extern	int StopJoypadVibration( int InputType ) ;									// �W���C�p�b�h�̐U�����~����
extern	int GetJoypadPOVState( int InputType, int POVNumber ) ;						// �W���C�p�b�h�̂o�n�u���͂̏�Ԃ𓾂�( �P�ʂ͊p�x�̂P�O�O�{  ���S�ʒu�ɂ���ꍇ�� -1 ���Ԃ� )
extern	int GetJoypadName( int InputType, char *InstanceNameBuffer, char *ProductNameBuffer ) ;	// �W���C�p�b�h�̃f�o�C�X�o�^���Ɛ��i�o�^�����擾����
extern	int ReSetupJoypad( void ) ;													// �W���C�p�b�h�̍ăZ�b�g�A�b�v���s��( �V���ɐڑ����ꂽ�W���C�p�b�h������ꍇ�Ɍ��o����� )

extern	int SetKeyboardNotDirectInputFlag( int Flag ) ;								// �L�[�{�[�h�̓��͏����� DirectInput ���g��Ȃ����A�t���O���Z�b�g����
extern	int	SetUseDirectInputFlag( int Flag ) ;										// ���͏����� DirectInput ���g�p���邩�ǂ����̃t���O���Z�b�g����








#ifndef DX_NOTUSE_DRAWFUNCTION

// DxDraw.cpp�֐��v���g�^�C�v�錾

// �ݒ�֌W�֐�
extern	int		Set2D3DKyouzonFlag( int Flag ) ;							// �R�c�ƂQ�c�̋��������グ��t���O�̃Z�b�g
extern	int		SetWaitVSyncFlag( int Flag ) ;								// �u�r�x�m�b�҂������邩�̃t���O�Z�b�g
extern	int		SetNotUse3DFlag( int Flag ) ;								// �R�c�@�\���g��Ȃ��t���O�̃Z�b�g
extern	int		SetBasicBlendFlag( int Flag ) ;								// �ȗ����u�����h�������s�����ۂ��̃t���O���Z�b�g����
extern	int		SetScreenMemToVramFlag( int Flag ) ;						// ��ʃf�[�^���u�q�`�l�ɒu�����A�t���O
extern	int		SetUseSoftwareRenderModeFlag( int Flag ) ;					// �\�t�g�E�G�A�����_�����O���[�h���g�p���邩�ǂ������Z�b�g����
extern	int		SetUseDirectDrawFlag( int Flag ) ;							// �c�����������c���������g�p���邩�ǂ������Z�b�g����
extern	int		SetUseGDIFlag( int Flag ) ;									// �f�c�h�`���K�v�Ƃ��邩�A��ύX����
extern	int		SetDDrawUseGuid( GUID *Guid ) ;								// �c�����������c���������g�p����f�t�c�h��ݒ肷��
extern	int		SetDisplayRefreshRate( int RefreshRate ) ;					// �t���X�N���[�����̉�ʂ̃��t���b�V�����[�g��ύX����(Windows2000�ȍ~�̂ݗL��)
extern	int		SetMultiThreadFlag( int Flag ) ;							// DirectDraw �̋������x�����}���`�X���b�h�Ή��ɂ��邩�ǂ������Z�b�g����
extern	int		SetUseDirectDrawDeviceIndex( int Index ) ;					// �g�p���� DirectDraw �f�o�C�X�̃C���f�b�N�X��ݒ肷��
extern	int		SetUseTempFrontScreen( int Flag ) ;							// �ꎞ�ޔ�p�\��ʂ��g�p���邩�ǂ�����ݒ肷��( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int		SetEmuration320x240( int Flag ) ;							// �U�S�O���S�W�O�̉�ʂłR�Q�O���Q�S�O�̉�ʉ𑜓x�ɂ��邩�ǂ����̃t���O���Z�b�g����A�U�S�O���S�W�O�ȊO�̉𑜓x�ł͖���( TRUE:�L��  FALSE:���� )

// �c�����������c�������֌W���񋟊֐�
extern	int						GetDrawScreenSize( int *XBuf, int *YBuf ) ;							// �`��T�C�Y���擾����
extern	int						GetScreenBitDepth( void ) ;											// �g�p�F�r�b�g����Ԃ�
extern	int						GetWaitVSyncFlag( void ) ;											// �u�r�x�m�b�҂�������ݒ�ɂȂ��Ă��邩�ǂ������擾����
extern	int						GetBmpSurf3DRenderingValidState( int BmpIndex ) ;					// �w��̃C���f�b�N�X�̃r�b�g�}�b�v�f�[�^���R�c�f�o�C�X�ɂ��`�悪�\���ǂ������擾����( TRUE:�o����  FALSE:�o���Ȃ� )
extern	void*					GetDrawTargetSurface( void ) ;	/* �߂�l�� IDirectDrawSurface7 * �ɃL���X�g���ĉ����� */		// �`��ΏۂƂȂ��Ă���T�[�t�F�X���擾
extern	void*					GetPrimarySurface( void ) ;		/* �߂�l�� IDirectDrawSurface7 * �ɃL���X�g���ĉ����� */		// �v���C�}���T�[�t�F�X���擾
extern	void*					GetBackSurface( void ) ;		/* �߂�l�� IDirectDrawSurface7 * �ɃL���X�g���ĉ����� */		// �o�b�N�T�[�t�F�X���擾
extern	void*					GetWorkSurface( void ) ;		/* �߂�l�� IDirectDrawSurface7 * �ɃL���X�g���ĉ����� */		// ��Ɨp�T�[�t�F�X���擾
extern	int						GetDesktopDrawCmp( void ) ;											// �f�X�N�g�b�v��ʂւ̕`�悩�̔�����
extern	void*					GetUseDDrawObj( void ) ;		/* �߂�l�� IDirectDraw7 * �ɃL���X�g���ĉ����� */			// ���ݎg�p���Ă���c�����������c�������I�u�W�F�N�g�̃A�h���X���擾����
extern  int						GetUseDirectDrawFlag( void ) ;										// �c�����������c���������g�p���邩�ǂ������擾����
extern	int						GetColorBitDepth( void ) ;											// ��ʂ̐F�r�b�g�[�x�𓾂�
extern	int						GetChangeDisplayFlag( void ) ;										// ��ʃ��[�h���ύX����Ă��邩�ǂ����̃t���O���擾����
extern	COLORDATA*				GetDispColorData( void ) ;											// �f�B�X�v���[�̃J���[�f�[�^�|�C���^�𓾂�
extern	const D_DDPIXELFORMAT*	GetPixelFormat( void ) ;											// �s�N�Z���t�H�[�}�b�g�̎擾
extern	int						GetScreenMemToSystemMemFlag( void ) ;								// ��ʃO���t�B�b�N�f�[�^���V�X�e���������ɑ��݂��邩�t���O�̎擾
extern	const D_DDPIXELFORMAT*	GetOverlayPixelFormat( void ) ;										// �g�p�ł���I�[�o�[���C�̃s�N�Z���t�H�[�}�b�g�𓾂�
extern	D_DDCAPS				GetDirectDrawCaps( void ) ;											// DirectDraw �̏��𓾂�
extern	int						GetVideoMemorySize( int *AllSize, int *FreeSize ) ;					// �r�f�I�������̗e�ʂ𓾂�
extern	int						GetUseGDIFlag( void ) ;												// �f�c�h�`���K�v�Ƃ��邩�ǂ������擾����
extern	int						GetNotDraw3DFlag( void ) ;											// NotDraw3DFlag ���擾����
extern	HDC						GetDrawScreenDC( void ) ;											// �`���ɂȂ��Ă����ʂ̂c�b���擾����
extern	int						ReleaseDrawScreenDC( HDC Dc ) ;										// GetScreenDC �Ŏ擾�����c�b���������
extern	GUID*					GetDirectDrawDeviceGUID( int Number ) ;								// �L���� DirectDraw �f�o�C�X�� GUID ���擾����
extern	int						GetDirectDrawDeviceDescription( int Number, char *StringBuffer ) ;	// �L���� DirectDraw �f�o�C�X�̖��O�𓾂�
extern	int						GetDirectDrawDeviceNum( void ) ;									// �L���� DirectDraw �f�o�C�X�̐����擾����
extern	int						GetUseMEMIMGFlag( void ) ;											// MEMIMG �\���̂��g�p���邩�ǂ������擾����
extern	int						GetVSyncTime( void ) ;												// ���������M�����ɕt�������鎞�Ԃ��~���b�P�ʂŎ擾����
extern	int						GetRefreshRate( void ) ;											// ���݂̉�ʂ̃��t���b�V�����[�g���擾����

// �p���b�g����֌W�֐�
extern 	int		SetPalette( int PalIndex, int Red, int Green, int Blue ) ;							// �p���b�g�̃Z�b�g
extern 	int		ReflectionPalette( void ) ;															// �Z�b�g�����p���b�g���n�[�h�E�G�A�ɔ��f������
extern 	int		GetPalette( int PalIndex, int *Red, int *Green, int *Blue ) ;						// �p���b�g�̎擾
extern	int		SetBmpPal( const char *FileName ) ;													// �a�l�o�t�@�C���̃p���b�g�𔽉f������
extern	int		SetBmpPalPart( const char *FileName, int StartNum, int GetNum, int SetNum ) ;		// �a�l�o�t�@�C������̃p���b�g�̕����擾
extern	int		GetGraphPalette( int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ;	// ��������ɓǂݍ��񂾉摜�̃p���b�g���擾����(�t���J���[�摜�̏ꍇ�͖���)
extern  int		GetGraphOriginalPalette( int GrHandle, int ColorIndex, int *Red, int *Green, int *Blue ) ; // ��������ɓǂݍ��񂾉摜�� SetGraphPalette �ŕύX����O�̃p���b�g���擾����
extern	int		SetGraphPalette( int GrHandle, int ColorIndex, int Color ) ;							// ��������ɓǂݍ��񂾉摜�̃p���b�g��ύX����(�t���J���[�摜�̏ꍇ�͖���)
extern	int		ResetGraphPalette( int GrHandle ) ;													// SetGraphPalette �ŕύX�����p���b�g��S�Č��ɖ߂�

// �F���擾�֌W
extern	int		ColorKaiseki( void *PixelData, COLORDATA* ColorData ) ;									// �F�r�b�g�����
extern	DWORD	GetColor( int Red, int Green, int Blue ) ;													// �R���F�l���猻�݂̉�ʃ��[�h�ɑΉ������F�f�[�^�l�𓾂�
extern	int		GetColor2( int Color, int *Red, int *Green, int *Blue ) ;									// ��ʃ��[�h�ɑΉ������F�f�[�^�l����X�̂R���F�f�[�^�𔲂��o��
extern	int		GetColor3( COLORDATA *ColorData, int Red, int Green, int Blue, int Alpha = 255 ) ;			// �R���F�l����w��̃s�N�Z���t�H�[�}�b�g�ɑΉ������F�f�[�^�l�𓾂�
extern	int		GetColor4( COLORDATA *DestColorData, COLORDATA* SrcColorData, int SrcColor ) ;			// �Q�̃J���[�t�H�[�}�b�g�Ԃ̃f�[�^�ϊ����s�������𓾂� 
extern	int		GetColor5( COLORDATA *ColorData, int Color, int *Red, int *Green, int *Blue, int *Alpha = NULL ) ;	// �w��J���[�t�H�[�}�b�g�ɑΉ������F�f�[�^�l����X�̂R���F�f�[�^�𔲂��o��
extern	int		CreatePaletteColorData( COLORDATA *ColorDataBuf ) ;										// �p���b�g�J���[�̃J���[�����\�z����
extern	int		CreateXRGB8ColorData( COLORDATA *ColorDataBuf ) ;											// �w�q�f�a�W�J���[�̃J���[�����\�z����
extern	int		CreateARGB8ColorData( COLORDATA *ColorDataBuf ) ;											// �`�q�f�a�W�J���[�̃J���[�����\�z����
extern	int		CreateFullColorData( COLORDATA *ColorDataBuf ) ;											// �t���J���[�c�h�a�̃J���[�����\�z����
extern	int		CreateGrayColorData( COLORDATA *ColorDataBuf ) ;											// �O���[�X�P�[���̃J���[�����\�z����
extern	int		CreatePal8ColorData( COLORDATA *ColorDataBuf ) ;											// �p���b�g�Q�T�U�F�̃J���[�����\�z����
extern	int		CreateColorData( COLORDATA *ColorDataBuf, int ColorBitDepth,
								 DWORD RedMask, DWORD GreenMask, DWORD BlueMask, DWORD AlphaMask ) ;		// �J���[�f�[�^���쐬����
extern	int		CreatePixelFormat( D_DDPIXELFORMAT *PixelFormatBuf, int ColorBitDepth,
								 DWORD RedMask, DWORD GreenMask, DWORD BlueMask, DWORD AlphaMask ) ;		// DDPIXELFORMAT�f�[�^���쐬����
extern	void	SetColorDataNoneMask( COLORDATA *ColorData ) ;												// NoneMask �ȊO�̗v�f�𖄂߂� COLORDATA �\���̂̏������� NoneMask ���Z�b�g����
extern	int		CmpColorData( COLORDATA *ColorData1, COLORDATA *ColorData2 ) ;							// ��̃J���[�f�[�^�����������ǂ������ׂ�( TRUE:������  FALSE:�������Ȃ� )

// �ȈՃO���t�B�b�N�֌W�֐�
extern	int		GetPixel( int x, int y ) ;																											// �w����W�̐F���擾����
extern	int		Paint( int x, int y, int FillColor, int BoundaryColor = -1 ) ;																		// �w��_���狫�E�F������Ƃ���܂œh��Ԃ�(���E�F�� -1 �ɂ���Ǝw��_�̐F�̗̈��h��Ԃ�)
extern	int		BltFastOrBitBlt( D_IDirectDrawSurface7 *Dest, D_IDirectDrawSurface7 *Src, int DestX, int DestY, RECT *SrcRect, int BltType = -1 ) ;	// �w��̃T�[�t�F�X����w��̃T�[�t�F�X�փO���t�B�b�N�f�[�^��]������

// �E�G�C�g�֌W�֐�
extern	int		WaitVSync( int SyncNum ) ;																												// ���������M����҂�

// ��ʑ���֌W�֐�
extern	int		ScreenFlip( void ) ;																													// ����ʂƕ\��ʂ���������
extern 	int		ScreenCopy( void ) ;																													// ����ʂ̓��e��\��ʂɕ`�悷��
extern	int		GraphCopy( RECT *SrcRect, RECT *DestRect, int SrcHandle, int DestHandle = DX_SCREEN_BACK ) ;											// �摜�̓��e���R�s�[����
extern	int		SetGraphMode( int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate = 60 ) ;												// ��ʃ��[�h�̃Z�b�g

// �a�l�o�ۑ��֐�
extern	int		SaveDrawScreen( int x1, int y1, int x2, int y2, const char *FileName, int SaveType = DX_IMAGESAVETYPE_BMP, int Jpeg_Quality = 80 , int Jpeg_Sample2x1 = TRUE , int Png_CompressionLevel = -1 ) ;		// ���ݕ`��ΏۂɂȂ��Ă����ʂ�ۑ�����
extern	int		SaveDrawScreenToBMP( int x1, int y1, int x2, int y2, const char *FileName ) ;														// ���ݕ`��ΏۂɂȂ��Ă����ʂ��a�l�o�`���ŕۑ�����
extern	int		SaveDrawScreenToJPEG( int x1, int y1, int x2, int y2, const char *FileName, int Quality = 80 , int Sample2x1 = TRUE ) ;				// ���ݕ`��ΏۂɂȂ��Ă����ʂ��i�o�d�f�`���ŕۑ�����
extern	int		SaveDrawScreenToPNG( int x1, int y1, int x2, int y2, const char *FileName, int CompressionLevel = -1 ) ;							// ���ݕ`��ΏۂɂȂ��Ă����ʂ��o�m�f�`���ŕۑ�����









// Dx3D.cpp�֐��v���g�^�C�v�錾

// �ݒ�֌W
extern	D_IDirect3DDevice7* GetUseD3DDevObj( void ) ;															// �g�p���̂c�����������R�c�c�����������I�u�W�F�N�g�𓾂�
extern	int		SetUseDivGraphFlag( int Flag ) ;																// �K�v�Ȃ�O���t�B�b�N�̕������s�����A�t���O�̃Z�b�g
extern	int		SetUseMaxTextureSize( int Size ) ;																// �g�p����e�N�X�`���[�̍ő�T�C�Y���Z�b�g(0�Ńf�t�H���g)
extern	int		SetUseVertexBufferFlag( int Flag ) ;															// ���_�o�b�t�@���g�p���邩�ǂ�����ݒ肷��
extern	int		RenderVertexBuffer( void ) ;																	// ���_�o�b�t�@�ɗ��܂������_�f�[�^��f���o��
extern	VERTEX_2D* GetVertexBuffer( int VertexNum = 6 , int PrimType = DX_PRIMTYPE_TRIANGLELIST ) ;				// �ǉ����_�o�b�t�@�̒��_�ǉ��A�h���X�𓾂�( �߂�l�̓e�N�X�`���Ȃ��̏ꍇ�� VERTEX_NOTEX_2D �ƂȂ� )
extern	void	_DrawPreparation( int GrHandle = DX_NONE_GRAPH , int ParamFlag = 0 ) ;							// �`�揀�����s��( ParamFlag �� DRAWPREP_TRANS �� )
extern	void	Add4VertexBuffer( void ) ;																		// GetVertexTo3DDevice �ɂ���ĂS���_�ǉ����ꂽ���Ƃ�O��ɒ��_�ǉ��������s��
extern	void	AddVertexBuffer( int VertexNum = 6 ) ;															// GetVertexTo3DDevice �ɂ���Ďw�萔���_���ǉ����ꂽ���Ƃ�O��ɒ��_�ǉ��������s��
extern	void	SetGraphTexture( int GrHandle ) ;																// �c�����������R�c�f�o�C�X�Ƀe�N�X�`�����Z�b�g����
extern	int		SetUseOldDrawModiGraphCodeFlag( int Flag ) ;													// �ȑO�� DrawModiGraph �֐��̃R�[�h���g�p���邩�ǂ����̃t���O���Z�b�g����

// ���̑��⏕�֐�
extern D_DDPIXELFORMAT*	GetTexPixelFormat( int AlphaCh, int AlphaTest, int ColorBitDepth, int DrawValid = FALSE ) ;	// �s�N�Z���t�H�[�}�b�g�𓾂�
extern COLORDATA*		GetTexColorData( int AlphaCh, int AlphaTest, int ColorBitDepth, int DrawValid = FALSE ) ;	// �J���[�f�[�^�𓾂�
extern D_DDPIXELFORMAT*	GetTexPixelFormat( IMAGEFORMATDESC *Format ) ;												// �t�H�[�}�b�g�Ɋ�Â����J���[�t�H�[�}�b�g�𓾂�
extern COLORDATA*		GetTexColorData( IMAGEFORMATDESC *Format ) ;												// �t�H�[�}�b�g�Ɋ�Â����J���[�f�[�^�𓾂�
extern D_DDPIXELFORMAT*	GetTexPixelFormat( int FormatIndex ) ;														// �w��̃t�H�[�}�b�g�C���f�b�N�X�̃J���[�t�H�[�}�b�g�𓾂�
extern COLORDATA*		GetTexColorData( int FormatIndex ) ;														// �w��̃t�H�[�}�b�g�C���f�b�N�X�̃J���[�f�[�^�𓾂�
extern int				GetTexFormatIndex( IMAGEFORMATDESC *Format ) ;												// �e�N�X�`���t�H�[�}�b�g�̃C���f�b�N�X�𓾂�
extern D_DDPIXELFORMAT*	GetZBufferPixelFormat( int BitDepth ) ;														// �w��̃r�b�g�[�x�̂y�o�b�t�@�[�̃s�N�Z���t�H�[�}�b�g�𓾂�( ���݂̂Ƃ��� 16 �r�b�g�̂� )

extern int			GraphColorMatchBltVer2( void *DestGraphData, int DestPitch, COLORDATA *DestColorData,
											void *SrcGraphData, int SrcPitch, COLORDATA *SrcColorData,
											void *AlphaMask, int AlphaPitch, COLORDATA *AlphaColorData,
											POINT DestPoint, RECT *SrcRect, int ReverseFlag,
											int TransColorAlphaTestFlag, unsigned int TransColor,
											int ImageShavedMode, int AlphaOnlyFlag = FALSE ,
											int RedIsAlphaFlag = FALSE , int TransColorNoMoveFlag = FALSE,
											int Pal8ColorMatch = FALSE ) ;											// �J���[�}�b�`���O���Ȃ���O���t�B�b�N�f�[�^�ԓ]�����s�� Ver2








// DxGraphics�֐��v���g�^�C�v�錾

// �O���t�B�b�N����֌W�֐�
extern	int			MakeGraph( int SizeX, int SizeY, int NotUse3DFlag = FALSE ) ;																								// ��̃O���t�B�b�N���쐬
extern	int			MakeScreen( int SizeX, int SizeY ) ;																														// �`��\�ȉ�ʂ��쐬
extern	int			DeleteGraph( int GrHandle, int LogOutFlag = FALSE ) ;																										// �w��̃O���t�B�b�N�f�[�^���폜����
extern	int			GetGraphNum( void ) ;																																		// �L���ȃO���t�B�b�N�̐����擾����
extern	int			SetGraphLostFlag( int GrHandle, int *LostFlag ) ;																											// ������ɗ��Ă�t���O�̃|�C���^���Z�b�g����
extern	int			InitGraph( int LogOutFlag = FALSE ) ;																														// �摜�f�[�^�̏�����

extern	int			BltBmpToGraph( COLORDATA *SrcColor, HBITMAP Bmp, HBITMAP AlphaMask, const char *GraphName, int CopyPointX, int CopyPointY, int GrHandle, int ReverseFlag ) ; // �摜�f�[�^�̓]��
extern	int			BltBmpToDivGraph( COLORDATA *SrcColor, HBITMAP Bmp, HBITMAP AlphaMask, const char *GraphName,
										int AllNum, int XNum, int YNum, int Width, int Height, int *GrHandle, int ReverseFlag ) ;												// �����摜�ւ̂a�l�o�̓]��
extern	int			BltBmpOrGraphImageToGraph( COLORDATA *SrcColorData, HBITMAP Bmp, HBITMAP AlphaMask, const char *GraphName,
										int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage,
										int CopyPointX, int CopyPointY, int GrHandle, int ReverseFlag ) ;																		// �a�l�o �� GraphImage ���摜�ɓ]��
extern	int			BltBmpOrGraphImageToGraph2( COLORDATA *SrcColorData, HBITMAP Bmp, HBITMAP AlphaMask, const char *GraphName,
										int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage,
										RECT *SrcRect, int DestX, int DestY, int GrHandle, int ReverseFlag ) ;																	// �a�l�o �� GraphImage ���摜�ɓ]��
extern	int			BltBmpOrGraphImageToDivGraph( COLORDATA *SrcColor, HBITMAP Bmp, HBITMAP AlphaMask, const char *GraphName,
										int BmpFlag, BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage,
										int AllNum, int XNum, int YNum, int Width, int Height, int *GrHandle, int ReverseFlag ) ;												// �����摜�ւ� �a�l�o �� GraphImage �̓]��
extern	int			LoadBmpToGraph( const char *GraphName, int TextureFlag, int ReverseFlag, int SurfaceMode = DX_MOVIESURFACE_NORMAL ) ;										// �摜��ǂ݂��� 
extern	int			LoadDivBmpToGraph( const char *FileName, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag, int ReverseFlag ) ;			// �摜�t�@�C���̕����ǂ݂���
extern	int			LoadGraph( const char *FileName, int NotUse3DFlag = FALSE ) ;																								// �摜�t�@�C���̃������ւ̓ǂ݂���
extern	int			LoadGraphToResource( int ResourceID ) ;																														// ���\�[�X����摜�f�[�^��ǂݍ���
extern	int			LoadGraphToResource( const char *ResourceName, const char *ResourceType ) ;																					// ���\�[�X����摜�f�[�^��ǂݍ���
extern	int			LoadDivGraphToResource( const char *ResourceName, const char *ResourceType, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;		// ���\�[�X����摜�f�[�^�𕪊��ǂݍ��݂���
extern	int			LoadBlendGraph( const char *FileName ) ;																													// �摜�t�@�C������u�����h�p�摜��ǂݍ���

extern	int			LoadReverseGraph( const char *FileName, int NotUse3DFlag = FALSE ) ;																						// �摜�t�@�C���̃������ւ̔��]�ǂݍ���
extern	int			LoadDivGraph( const char *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int NotUse3DFlag = FALSE ) ;						// �摜�̕����ǂ݂���
extern	int			LoadReverseDivGraph( const char *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int NotUse3DFlag = FALSE ) ;				// �摜�̔��]�����ǂ݂���
#ifndef DX_NON_MOVIE
extern	int			OpenMovieToOverlay( const char *FileName ) ;																												// �I�[�o�[���C�T�[�t�F�X���g�p�������[�r�[�t�@�C���̃I�[�v��
extern	int			UpdateMovieToOverlay( int x, int y, int ExRate, int ShowFlag, int MovieHandle ) ;																			// �I�[�o�[���C�T�[�t�F�X���g�p�������[�r�[�̕\���X�e�[�^�X�Z�b�g
extern	int			CloseMovieToOverlay( int MovieHandle ) ;																													// �I�[�o�[���C�T�[�t�F�X���g�p�������[�r�[�t�@�C�������
#endif
extern	int			ReloadGraph( const char *FileName, int GrHandle, int ReverseFlag = FALSE ) ;																				// �摜�ւ̉摜�f�[�^�̓ǂݍ���
extern	int			ReloadDivGraph( const char *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf, int ReverseFlag = FALSE ) ;						// �摜�ւ̉摜�f�[�^�̕����ǂݍ���
extern	int			ReloadReverseGraph( const char *FileName, int GrHandle ) ;																									// �摜�ւ̉摜�f�[�^�̓ǂݍ���
extern	int			ReloadReverseDivGraph( const char *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;										// �摜�ւ̉摜�f�[�^�̕����ǂݍ���
extern	int			ReloadFileGraphAll( void ) ;																																// �t�@�C������ǂݍ��񂾉摜�����ēx�ǂݍ���
extern	int			SetGraphTransColor( int GrHandle, int Red, int Green, int Blue ) ;																							// �摜�̓��ߐF��ύX����(�A���t�@�`�����l���g�p���͖���)

extern	int			RestoreGraph( int GrHandle ) ;																																// �摜�f�[�^�̃��X�g�A
extern	int			AllRestoreGraph( void ) ;																																	// ���ׂẲ摜�f�[�^�̃��X�g�A


// �O���t�B�b�N�`��֌W�֐�
extern	int			ClearDrawScreen( void ) ;																												// ��ʂ̏�Ԃ�����������
extern	int			ClsDrawScreen( void ) ;																													// ��ʂ̏�Ԃ�����������(ClearDrawScreen�̋�����)

extern	int			LoadGraphScreen( int x, int y, const char *GraphName, int TransFlag ) ;																	// �a�l�o�t�@�C����ǂ݂���ŉ�ʂɕ`�悷��
extern	int			DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;																				// �O���t�B�b�N�̕`��
extern	int			DrawGraphF( float xf, float yf, int GrHandle, int TransFlag ) ;																			// �O���t�B�b�N�̕`��
extern	int			DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle, int TransFlag ) ;														// �O���t�B�b�N�̊g��k���`��
extern	int			DrawExtendGraphF( float x1f, float y1f, float x2f, float y2, int GrHandle, int TransFlag ) ;												// �O���t�B�b�N�̊g��k���`��
extern	int			DrawRotaGraph( int x, int y, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;						// �O���t�B�b�N�̉�]�`��
extern	int			DrawRotaGraphF( float xf, float yf, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;					// �O���t�B�b�N�̉�]�`��
extern	int			DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;		// �O���t�B�b�N�̉�]�`��Q
extern	int			DrawRotaGraph2F( float xf, float yf, float cxf, float cyf, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE  ) ;	// �O���t�B�b�N�̉�]�`��Q
extern	int			DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int TransFlag ) ;							// �摜�̎��R�ό`�`��
extern	int			DrawModiGraphF( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int GrHandle, int TransFlag ) ;			// �摜�̎��R�ό`�`��( float �� )
extern	int			DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;																			// �摜�̍��E���]�`��
extern	int			DrawTurnGraphF( float xf, float yf, int GrHandle, int TransFlag ) ;																		// �摜�̍��E���]�`��
extern	int			DrawChipMap( int Sx, int Sy, int XNum, int YNum, int *MapData, int ChipTypeNum, int MapDataPitch, int *GrHandle, int TransFlag ) ;		// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
extern	int			DrawChipMap( int MapWidth, int MapHeight, int *MapData, int ChipTypeNum, int *ChipGrHandle, int TransFlag,
										int MapDrawPointX, int MapDrawPointY, int MapDrawWidth, int MapDrawHeight, int ScreenX, int ScreenY ) ;			// �`�b�v�O���t�B�b�N���g�����}�b�v�`��
extern	int			DrawTile( int x1, int y1, int x2, int y2, int Tx, int Ty,
								double ExtRate, double Angle, int GrHandle, int TransFlag ) ;															// �O���t�B�b�N���w��̈�Ƀ^�C����ɕ`�悷��
extern	int			DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;	// �O���t�B�b�N�̎w���`�����݂̂�`��
extern	int			DrawRectExtendGraph( int DestX1, int DestY1, int DestX2, int DestY2, int SrcX, int SrcY, int SrcWidth, int SrcHeight, int GraphHandle, int TransFlag ) ;	// �O���t�B�b�N�̎w���`�����݂̂��g��`��
extern	int			DrawBlendGraph( int x, int y, int GrHandle, int TransFlag, int BlendGraph, int BorderParam, int BorderRange ) ;						// �u�����h�摜�ƍ������ĉ摜��`�悷��
extern	int			DrawBlendGraphPos( int x, int y, int GrHandle, int TransFlag, int bx, int by, int BlendGraph, int BorderParam, int BorderRange ) ;	// �u�����h�摜�ƍ������ĉ摜��`�悷��( �u�����h�摜�̋N�_���W���w�肷��� )
extern	int			DrawRectRotaGraph( int X, int Y, int SrcX, int SrcY, int Width, int Height, double ExtRate, double Angle, int GraphHandle, int TransFlag, int TurnFlag ) ; 
extern	int			DrawCircleGauge( int CenterX, int CenterY, double Percent, int GrHandle ) ;															// �~�O���t�I�ȕ`����s��
extern	int			DrawGraphToZBuffer( int X, int Y, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;											// �y�o�b�t�@�ɑ΂��ĉ摜�̕`����s��
extern	int			DrawTurnGraphToZBuffer( int x, int y, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;										// �y�o�b�t�@�ɑ΂��ĉ摜�̍��E���]�`��
extern	int			DrawExtendGraphToZBuffer( int x1, int y1, int x2, int y2, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;					// �y�o�b�t�@�ɑ΂��ĉ摜�̊g��k���`��
extern	int			DrawRotaGraphToZBuffer( int x, int y, double ExRate, double Angle, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ , int TurnFlag = FALSE  ) ;	// �y�o�b�t�@�ɑ΂��ĉ摜�̉�]�`��
extern	int			DrawModiGraphToZBuffer( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;	// �y�o�b�t�@�ɑ΂��ĉ摜�̎��R�ό`�`��
extern	int			DrawBoxToZBuffer( int x1, int y1, int x2, int y2, int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;							// �y�o�b�t�@�ɑ΂��ċ�`�̕`����s��
extern	int			DrawCircleToZBuffer( int x, int y, int r, int FillFlag, int WriteZMode /* DX_ZWRITE_MASK �� */ ) ;									// �y�o�b�t�@�ɑ΂��ĉ~�̕`����s��
extern	int			DrawPolygonBase( VERTEX *Vertex, int VertexNum, int PrimitiveType, int GrHandle, int TransFlag ) ;									// �Q�c�|���S����`�悷��
extern	int			DrawPolygon( VERTEX *Vertex, int PolygonNum, int GrHandle, int TransFlag ) ;														// �Q�c�|���S����`�悷��
extern	int			DrawPolygon3DBase( VERTEX_3D *Vertex, int VertexNum, int PrimitiveType, int GrHandle, int TransFlag ) ;								// �R�c�|���S����`�悷��
extern	int			DrawPolygon3D( VERTEX_3D *Vertex, int PolygonNum, int GrHandle, int TransFlag ) ;													// �R�c�|���S����`�悷��
extern	int			DrawGraph3D( float x, float y, float z, int GrHandle, int TransFlag ) ;																// �O���t�B�b�N�̂R�c�`��
extern	int			DrawExtendGraph3D( float x, float y, float z, double ExRateX, double ExRateY, int GrHandle, int TransFlag ) ;						// �O���t�B�b�N�̊g��R�c�`��
extern	int			DrawRotaGraph3D( float x, float y, float z, double ExRate, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE ) ;		// �O���t�B�b�N�̉�]�R�c�`��
extern	int			DrawRota2Graph3D( float x, float y, float z, float cx, float cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag = FALSE ) ;	// �O���t�B�b�N�̉�]�R�c�`��(��]���S�w��^)
extern	int			FillGraph( int GrHandle, int Red, int Green, int Blue, int Alpha = 255 ) ;															// �O���t�B�b�N�����̐F�œh��Ԃ�
extern	int			DrawLine( int x1, int y1, int x2, int y2, int Color, int Thickness = 1 ) ;																// ����`��
extern	int			DrawBox( int x1, int y1, int x2, int y2, int Color, int FillFlag ) ;																// �l�p�`�̕`��
extern	int			DrawFillBox( int x1, int y1, int x2, int y2, int Color ) ;																			// ���g�̂���l�p��`��
extern	int			DrawLineBox( int x1, int y1, int x2, int y2, int Color ) ;																			// �l�p�`�̕`�� 
extern	int			DrawCircle( int x, int y, int r, int Color, int FillFlag = TRUE ) ;																	// �~��`��
extern	int			DrawOval( int x, int y, int rx, int ry, int Color, int FillFlag ) ;																	// �ȉ~��`��
extern	int			DrawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, int Color, int FillFlag ) ;											// �O�p�`�̕`��
extern 	int			DrawPixel( int x, int y, int Color ) ;																								// �_��`�悷��
extern 	int			DrawPixelSet( POINTDATA *PointData, int Num ) ;																						// �_�̏W����`��
extern	int			DrawLineSet( LINEDATA *LineData, int Num ) ;																						// ���̏W����`��
extern	int			DrawString( int x, int y, const char *String, int Color, int EdgeColor = 0 ) ;														// ������̕`��
extern	int			DrawVString( int x, int y, const char *String, int Color, int EdgeColor = 0 ) ;														// ������̕`��
extern	int			DrawStringToHandle( int x, int y, const char *String, int Color, int FontHandle, int EdgeColor = 0 , int VerticalFlag = FALSE ) ;	// �������`�悷��
extern	int			DrawVStringToHandle( int x, int y, const char *String, int Color, int FontHandle, int EdgeColor = 0 ) ;								// �������`�悷��
extern	int			DrawFormatString( int x, int y, int Color, const char *FormatString, ... ) ;														// �����w�蕶�����`�悷��
extern	int			DrawFormatVString( int x, int y, int Color, const char *FormatString, ... ) ;														// �����w�蕶�����`�悷��
extern	int			DrawFormatStringToHandle( int x, int y, int Color, int FontHandle, const char *FormatString, ... ) ;								// �����w�蕶�����`�悷��
extern	int			DrawFormatVStringToHandle( int x, int y, int Color, int FontHandle, const char *FormatString, ... ) ;								// �����w�蕶�����`�悷��
extern	int			DrawExtendString( int x, int y, double ExRateX, double ExRateY, const char *String, int Color, int EdgeColor = 0 ) ;													// ������̊g��`��
extern	int			DrawExtendVString( int x, int y, double ExRateX, double ExRateY, const char *String, int Color, int EdgeColor = 0 ) ;													// ������̊g��`��
extern	int			DrawExtendStringToHandle( int x, int y, double ExRateX, double ExRateY, const char *String, int Color, int FontHandle, int EdgeColor = 0 , int VerticalFlag = FALSE ) ;	// ��������g��`�悷��
extern	int			DrawExtendVStringToHandle( int x, int y, double ExRateX, double ExRateY, const char *String, int Color, int FontHandle, int EdgeColor = 0 ) ;							// ��������g��`�悷��
extern	int			DrawExtendFormatString( int x, int y, double ExRateX, double ExRateY, int Color, const char *FormatString, ... ) ;														// �����w�蕶������g��`�悷��
extern	int			DrawExtendFormatVString( int x, int y, double ExRateX, double ExRateY, int Color, const char *FormatString, ... ) ;														// �����w�蕶������g��`�悷��
extern	int			DrawExtendFormatStringToHandle( int x, int y, double ExRateX, double ExRateY, int Color, int FontHandle, const char *FormatString, ... ) ;								// �����w�蕶������g��`�悷��
extern	int			DrawExtendFormatVStringToHandle( int x, int y, double ExRateX, double ExRateY, int Color, int FontHandle, const char *FormatString, ... ) ;								// �����w�蕶������g��`�悷��

extern	int			DrawNumberToI( int x, int y, int Num, int RisesNum, int Color, int EdgeColor = 0 ) ;												// �����^�̐��l��`�悷��
extern	int			DrawNumberToF( int x, int y, double Num, int Length, int Color, int EdgeColor = 0 ) ;												// ���������_�^�̐��l��`�悷��
extern	int			DrawNumberPlusToI( int x, int y, const char *NoteString, int Num, int RisesNum, int Color, int EdgeColor = 0 ) ;						// �����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern 	int			DrawNumberPlusToF( int x, int y, const char *NoteString, double Num, int Length, int Color, int EdgeColor = 0 ) ;					// ���������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

extern	int			DrawNumberToIToHandle( int x, int y, int Num, int RisesNum, int Color, int FontHandle, int EdgeColor = 0 ) ;							// �����^�̐��l��`�悷��
extern	int			DrawNumberToFToHandle( int x, int y, double Num, int Length, int Color, int FontHandle, int EdgeColor = 0 ) ;						// ���������_�^�̐��l��`�悷��
extern	int			DrawNumberPlusToIToHandle( int x, int y, const char *NoteString, int Num, int RisesNum, int Color, int FontHandle, int EdgeColor = 0 ) ;	// �����^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��
extern	int			DrawNumberPlusToFToHandle( int x, int y, const char *NoteString, double Num, int Length, int Color, int FontHandle, int EdgeColor = 0 ) ;	// ���������_�^�̐��l�Ƃ��̐����̕��������x�ɕ`�悷��

// �g�����W�V�����@�\�֐�
//extern	int			SetupTransition( int BlendGraph, int BorderRange ) ;				// �g�����W�V���������̏������s��
//extern	int			

// �R�c�`��֌W�֐�
//extern void			SetColorVertexState( LPVERTEXDATA Vertex, float x, float y, float z, float rhw, int red, int green, int blue, int alpha, float tu, float tv ) ;	// �R�c���_�f�[�^���Z�b�g����  

// �`��ݒ�֌W�֐�
extern	int			SetDrawMode( int DrawMode ) ;										// �`�惂�[�h���Z�b�g����
extern	int			SetDrawBlendMode( int BlendMode, int BlendParam ) ;					// �`��u�����h���[�h���Z�b�g����
extern	int			SetBlendGraph( int BlendGraph, int BorderParam, int BorderRange ) ;	// �`�揈�����ɕ`�悷��摜�ƃu�����h���郿�`�����l���t���摜���Z�b�g����( BlendGraph �� -1 �Ńu�����h�@�\�𖳌� )
extern	int			SetBlendGraphPosition( int x, int y ) ;								// �u�����h�摜�̋N�_���W���Z�b�g����
extern	int			SetDrawBright( int RedBright, int GreenBright, int BlueBright ) ;	// �`��P�x���Z�b�g
extern	int			SetDrawScreen( int DrawScreen ) ;									// �`����ʂ̃Z�b�g
extern	int			SetDrawArea( int x1, int y1, int x2, int y2 ) ;						// �`��\�̈�̃Z�b�g
extern	int			SetUse3DFlag( int Flag ) ;											// �R�c�@�\���g�����A�̃t���O���Z�b�g
extern	int			SetUseNotManageTextureFlag( int Flag ) ;							// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���Z�b�g( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			SetTransColor( int Red, int Green, int Blue ) ;						// �O���t�B�b�N�ɐݒ肷�铧�ߐF���Z�b�g����
extern	int			SetRestoreShredPoint( void (* ShredPoint )( void ) ) ;				// SetRestoreGraphCallback �̋���
extern	int			SetRestoreGraphCallback( void (* Callback )( void ) ) ;				// �O���t�B�b�N�n���h�������֐��̓o�^
extern	int			RunRestoreShred( void ) ;											// �O���t�B�b�N�����֐��̎��s
extern	int			SetTransformToWorld( MATRIX *Matrix, int SetIndex = 0 ) ;			// ���[���h�ϊ��p�s����Z�b�g����
extern	int			SetTransformToView( MATRIX *Matrix ) ;								// �r���[�ϊ��p�s����Z�b�g����
extern	int			SetTransformToProjection( MATRIX *Matrix ) ;						// ���e�ϊ��p�s����Z�b�g����
extern	int			SetTransformToViewport( MATRIX *Matrix ) ;							// �r���[�|�[�g�s����Z�b�g����
extern	int			SetUseZBufferFlag( int Flag ) ;										// �y�o�b�t�@��L���ɂ��邩�A�t���O���Z�b�g����
extern	int			SetWriteZBufferFlag( int Flag ) ;									// �y�o�b�t�@�ɏ������݂��s�����A�t���O���Z�b�g����
extern	int			SetZBufferCmpType( int CmpType /* DX_CMP_NEVER �� */ ) ;			// �y�l�̔�r���[�h���Z�b�g����
extern	int			SetUseCullingFlag( int Flag ) ;										// �|���S���J�����O�̗L���A�������Z�b�g����
extern	int			SetTextureAddressMode( int Mode /* DX_TEXADDRESS_WRAP �� */ ) ;		// �e�N�X�`���A�h���X���[�h��ݒ肷��
extern	int			SetDefTransformMatrix( void ) ;										// �f�t�H���g�̕ϊ��s����Z�b�g����
extern	int			SetLeftUpColorIsTransColorFlag( int Flag ) ;						// �摜����̐F�𓧉ߐF�ɂ��邩�ǂ����̃t���O���Z�b�g����
extern 	int			SetUseAlphaChannelGraphCreateFlag( int Flag ) ;						// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern 	int			SetUseGraphAlphaChannel( int Flag ) ;								// SetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			SetUseAlphaTestGraphCreateFlag( int Flag ) ;						// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			SetUseAlphaTestFlag( int Flag ) ;									// SetUseAlphaTestGraphCreateFlag �̋�����
extern	int			SetDrawValidGraphCreateFlag( int Flag ) ;							// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�`��\  FALSE:�`��s�\ )
extern	int			SetDrawValidFlagOf3DGraph( int Flag ) ;								// SetDrawValidGraphCreateFlag �̋�����
extern	int			SetDrawValidAlphaChannelGraphCreateFlag( int Flag ) ;				// �`��\�ȃ��`�����l���t���摜���쐬���邩�ǂ����̃t���O���Z�b�g����,SetDrawValidGraphCreateFlag �֐��ŕ`��\�摜���쐬����悤�ɐݒ肳��Ă��Ȃ��ƌ��ʂ��Ȃ�( TRUE:���`�����l���t�� FALSE:���`�����l���Ȃ� )
extern	int			SetUseNoBlendModeParam( int Flag ) ;								// SetDrawBlendMode �֐��̑������� DX_BLENDMODE_NOBLEND ���������ۂɁA�f�t�H���g�ł͑������͓����łQ�T�T���w�肵�����ƂɂȂ邪�A���̎����Q�T�T�������Ȃ����ǂ�����ݒ肷��( TRUE:���Ȃ�(�������̒l���g�p�����)   FALSE:����(�������̒l�͖�������� 255 ����Ɏg�p�����)(�f�t�H���g) )���`�����l���t���摜�ɑ΂��ĕ`����s���ꍇ�݈̂Ӗ�������֐�
extern	int			SetUseSystemMemGraphCreateFlag( int Flag ) ;						// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���Z�b�g����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			SetUseBlendGraphCreateFlag( int Flag ) ;							// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���Z�b�g����
extern	int			SetUseVramFlag( int Flag ) ;										// �u�q�`�l���g�p���邩�̃t���O���Z�b�g����
extern	int			SetMovieRightImageAlphaFlag( int Flag ) ;							// ����t�@�C���̉E�������A���t�@���Ƃ��Ĉ������ǂ������Z�b�g����( TRUE:�A���t�@���Ƃ��Ĉ��� )
extern	int			SetCreateGraphColorBitDepth( int BitDepth ) ;						// �쐬����O���t�B�b�N�̐F�[�x��ݒ肷��
extern	int			SetGraphColorBitDepth( int ColorBitDepth ) ;						// SetCreateGraphColorBitDepth �̋�����
extern	int			SetGraphDataShavedMode( int ShavedMode ) ;							// �O���t�B�b�N���F���̉摜�򉻊ɘa�������[�h�̕ύX
extern	int			RestoreGraphSystem( void ) ;										// �c�w���C�u�����̃O���t�B�b�N�֘A�̕��A�������s��
extern	int			SetUseBasicGraphDraw3DDeviceMethodFlag( int Flag ) ;				// �P���}�`�̕`��ɂR�c�f�o�C�X�̋@�\���g�p���邩�ǂ����̃t���O���Z�b�g����
extern	int			SetWindowDrawRect( RECT *DrawRect ) ;								// �ʏ�g�p���Ȃ�
extern	int			SetDrawZ( float Z ) ;												// �Q�c�`�掞�ɂy�o�b�t�@�ɏ������ނy�l��ύX����
extern	int			SetUseTransColor( int Flag ) ;										// ���ߐF�@�\���g�p���邩�ǂ�����ݒ肷��
extern	int			SetUseTransColorGraphCreateFlag( int Flag ) ;						// ���ߐF�@�\���g�p���邱�Ƃ�O��Ƃ����摜�̓ǂݍ��ݏ������s�����ǂ�����ݒ肷��( TRUE �ɂ���� SetDrawMode( DX_DRAWMODE_BILINEAR ); ��������Ԃ� DrawGraphF ���̕��������_�^���W���󂯎��֐��ŏ����_�ȉ��̒l���w�肵���ꍇ�ɔ�������`�挋�ʂ̕s���R���ɘa������ʂ����� ( �f�t�H���g�� FALSE ) )


// �O���t�B�b�N���擾�֌W�֐�
extern	int			GetTransColor( int *Red, int *Green, int *Blue ) ;												// ���ߐF�𓾂�
//extern	int			GetGraphHandle( IMAGEDATA *GraphData ) ;													// �����̃O���t�B�b�N�C���f�b�N�X�ԍ����擾����
//extern	IMAGEDATA 	*GetGraphData( int GrHandle ) ;																// �O���t�B�b�N�̃f�[�^���C���f�b�N�X�l������o��
extern	int			GetDrawScreenGraph( int x1, int y1, int x2, int y2, int GrHandle, int UseClientFlag = TRUE ) ;	// �A�N�e�B�u�ɂȂ��Ă����ʂ���w��̈�̃O���t�B�b�N���擾����
extern	DWORD*		GetFullColorImage( int GrHandle ) ;																// �w��̉摜�̂`�q�f�a�W�̃t���J���[�C���[�W���擾����

extern	int			GraphLock( int GrHandle, int *PitchBuf, void **DataPointBuf, COLORDATA **ColorDataPP = NULL ) ;	// �O���t�B�b�N�������̈�̃��b�N
extern	int			GraphUnLock( int GrHandle ) ;																// �O���t�B�b�N�������̈�̃��b�N����

extern	int			SetUseGraphZBuffer( int GrHandle, int UseFlag ) ;											// �O���t�B�b�N�ɂy�o�b�t�@���g�p���邩�ǂ�����ݒ肷��

extern	int			GetGraphSize( int GrHandle, int *SizeXBuf, int *SizeYBuf ) ;								// �O���t�B�b�N�̃T�C�Y�𓾂�
extern	int			GetScreenState( int *SizeX, int *SizeY, int *ColorBitDepth ) ;								// ���݂̉�ʂ̑傫���ƃJ���[�r�b�g���𓾂� 
extern	int			GetActiveGraph( void ) ;																	// �A�N�e�B�u�ɂȂ��Ă���O���t�B�b�N�̃n���h���𓾂�
extern	int			GetDrawArea( RECT *Rect ) ;																	// �`��\�̈�𓾂�
extern	int			GetUse3DFlag( void ) ;																		// �`��ɂR�c�@�\���g�����t���O���擾
extern	int			GetUseNotManageTextureFlag( void ) ;														// ��Ǘ��e�N�X�`�����g�p���邩�A�̃t���O���擾����( TRUE:�g�p����  FALSE:�g�p���Ȃ� )
extern	int			GetValidRestoreShredPoint( void ) ;															// �O���t�B�b�N�����֐��̗L�����擾																
extern	int			GetFontSize( void ) ;																		// �t�H���g�̃T�C�Y�𓾂�
extern	int			GetFontSizeToHandle( int FontHandle ) ;														// �t�H���g�̃T�C�Y�𓾂�
extern	char*		GetResourceIDString( int ResourceID ) ;														// ���\�[�X�h�c���烊�\�[�X�h�c������𓾂� 
extern	int			GetTransformToViewMatrix( MATRIX *MatBuf ) ;												// �r���[�s����擾����
extern	int			GetTransformToWorldMatrix( MATRIX *MatBuf ) ;												// ���[���h�s����擾����
extern	int			GetTransformToProjectionMatrix( MATRIX *MatBuf ) ;											// �ˉe�s����擾����
extern	int			GetTransformPosition( VECTOR *LocalPos, float *x, float *y ) ;								// ���[�J�����W�����ʍ��W���擾����
extern	int			SetUseFastLoadFlag( int Flag ) ;															// �����ǂݍ��݃��[�`�����g�����ۂ��̃t���O���Z�b�g����
extern	int			GetDrawBlendMode( int *BlendMode, int *BlendParam ) ;										// �`��u�����h���[�h���擾����
extern	int			GetDrawMode( void ) ;																		// �`�惂�[�h���擾����
extern	int			GetDrawBright( int *Red, int *Green, int *Blue ) ;											// �`��P�x���擾����
extern	int			GetCreateGraphColorBitDepth( void ) ;														// �쐬����O���t�B�b�N�̐F�[�x��ݒ肷��
extern 	int			GetGraphColorBitDepth( void ) ;																// GetCreateGraphColorBitDepth �̋�����
extern	int			GetGraphDataShavedMode( void ) ;															// �O���t�B�b�N���F���̉摜�򉻊ɘa�������[�h�̎擾
extern	int			GetUseSystemMemGraphCreateFlag( void ) ;													// �V�X�e����������ɃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:�V�X�e����������ɍ쐬  FALSE:�u�q�`�l��ɍ쐬 )
extern	int			GetUseBlendGraphCreateFlag( void ) ;														// �u�����h�����p�摜���쐬���邩�ǂ����̃t���O���擾����
extern	int			GetUseVramFlag( void ) ;																	// �Q�c�O���t�B�b�N�T�[�t�F�X�쐬���ɃV�X�e���������[���g�p���邩�̃t���O�擾
extern	int			GetUseAlphaTestGraphCreateFlag( void ) ;													// �A���t�@�e�X�g���g�p����O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����
extern	int			GetUseAlphaTestFlag( void ) ;																// GetUseAlphaTestGraphCreateFlag �̋�����
extern 	int			GetUseAlphaChannelGraphCreateFlag( void ) ;													// ���`�����l���t���O���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����( TRUE:���`�����l���t��   FALSE:���`�����l������ )
extern 	int			GetUseGraphAlphaChannel( void ) ;															// GetUseAlphaChannelGraphCreateFlag �̋�����
extern	int			GetDrawValidGraphCreateFlag( void ) ;														// �`��\�ȃO���t�B�b�N���쐬���邩�ǂ����̃t���O���擾����


// ���Z���C�u����
extern	int			CreateIdentityMatrix( MATRIX *Out ) ;														// �P�ʍs����쐬����
extern	int			CreateLookAtMatrix( MATRIX *Out, VECTOR *Eye, VECTOR *At, VECTOR *Up ) ;					// �r���[�s����쐬����
extern	int			CreateLookAtMatrix2( MATRIX *Out, VECTOR *Eye, double XZAngle, double Oira ) ;				// �r���[�s����쐬����
extern	int			CreateLookAtMatrixRH( MATRIX *Out, VECTOR *Eye, VECTOR *At, VECTOR *Up ) ;					// �r���[�s����쐬����(�E����W�n�p)
extern	int			CreateMultiplyMatrix( MATRIX *Out, MATRIX *In1, MATRIX *In2 ) ;								// �s��̐ς����߂�
extern	int			CreatePerspectiveFovMatrix( MATRIX *Out, float fov, float zn, float zf ) ;					// �ˉe�s����쐬����
extern	int			CreatePerspectiveFovMatrixRH( MATRIX *Out, float fov, float zn, float zf ) ;				// �ˉe�s����쐬����(�E����W�n�p)
extern	int			CreateScalingMatrix( MATRIX *Out, float sx, float sy, float sz ) ;							// �X�P�[�����O�s����쐬����
extern	int			CreateRotationXMatrix( MATRIX *Out, float Angle ) ;											// �w���𒆐S�Ƃ�����]�s����쐬����
extern	int			CreateRotationYMatrix( MATRIX *Out, float Angle ) ;											// �x���𒆐S�Ƃ�����]�s����쐬����
extern	int			CreateRotationZMatrix( MATRIX *Out, float Angle ) ;											// �y���𒆐S�Ƃ�����]�s����쐬����
extern	int			CreateTranslationMatrix( MATRIX *Out, float x, float y, float z ) ;							// ���s�ړ��s����쐬����
extern	int			CreateViewportMatrix( MATRIX *Out, float CenterX, float CenterY, float Width, float Height ) ; // �r���[�|�[�g�s����쐬����
extern	int			VectorNormalize( VECTOR *Out, VECTOR *In ) ;												// �x�N�g���𐳋K������
extern	int			VectorScale( VECTOR *Out, VECTOR *In, float Scale ) ;										// �x�N�g�����X�J���[�{����
extern	int			VectorMultiply( VECTOR *Out, VECTOR *In1, VECTOR *In2 ) ;									// �x�N�g���̊|���Z������
extern	int			VectorSub( VECTOR *Out, VECTOR *In1, VECTOR *In2 ) ;										// Out = In1 - In2 �̃x�N�g���v�Z������ 
extern	int			VectorAdd( VECTOR *Out, VECTOR *In1, VECTOR *In2 ) ;										// Out = In1 + In2 �̃x�N�g���v�Z������ 
extern	int			VectorOuterProduct( VECTOR *Out, VECTOR *In1, VECTOR *In2 ) ;								// In1��In2�̊O�ς��v�Z����
extern	float		VectorInnerProduct( VECTOR *In1, VECTOR *In2 ) ;											// In1��In2�̓��ς��v�Z����
extern	int			VectorRotationX( VECTOR *Out, VECTOR *In, double Angle ) ;									// �x�N�g���̂w�������ɂ�����]���s��
extern	int			VectorRotationY( VECTOR *Out, VECTOR *In, double Angle ) ;									// �x�N�g���̂x�������ɂ�����]���s��
extern	int			VectorRotationZ( VECTOR *Out, VECTOR *In, double Angle ) ;									// �x�N�g���̂y�������ɂ�����]���s��
extern	int			VectorTransform( VECTOR *Out, VECTOR *InVec, MATRIX *InMatrix ) ;							// �x�N�g���s���4x4�����s�����Z����( w �� 1 �Ɖ��� )
extern	int			VectorTransform4( VECTOR *Out, float *V4Out, VECTOR *InVec, float *V4In, MATRIX *InMatrix ) ; // �x�N�g���s���4x4�����s�����Z����( w �̗v�f��n�� )

// �⏕�֌W
//extern	int			AddUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;										// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^����
//extern	int			AddUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^����
//extern	int			AddUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ) ; // ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver3��o�^����
extern	int			AddUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *Image ) ) ; 													// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver4��o�^����
//extern	int			SubUserGraphLoadFunction( int ( *UserLoadFunc )( FILE *fp, BITMAPINFO **BmpInfo, void **GraphData ) ) ;										// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^���疕������
//extern	int			SubUserGraphLoadFunction2( int ( *UserLoadFunc )( void *Image, int ImageSize, int ImageType, BITMAPINFO **BmpInfo, void **GraphData ) ) ;	// ���[�U�[��`�̃O���t�B�b�N���[�h�֐���o�^���疕������
//extern	int			SubUserGraphLoadFunction3( int ( *UserLoadFunc )( void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ) ; // ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver3��o�^���疕������
extern	int			SubUserGraphLoadFunction4( int (* UserLoadFunc )( STREAMDATA *Src, BASEIMAGE *Image ) ) ; 													// ���[�U�[��`�̃O���t�B�b�N���[�h�֐�Ver4��o�^���疕������
extern	int			RectClipping( RECT *MotoRect, RECT *ClippuRect ) ;															// ��`�̃N���b�s���O
extern	int			GetCreateGraphColorData( COLORDATA *ColorData, IMAGEFORMATDESC *Format ) ;									// ���ꂩ��V���ɃO���t�B�b�N���쐬����ꍇ�Ɏg�p����J���[�����擾����

// �t�H���g�A������`��֌W�֐�
extern	int			EnumFontName( char *NameBuffer, int NameBufferNum, int JapanOnlyFlag = TRUE ) ;								// �g�p�\�ȃt�H���g�̖��O�����ׂė񋓂���
extern	int			InitFontToHandle( void ) ;																					// �t�H���g�̃X�e�[�^�X���f�t�H���g�ɖ߂�
extern	int			CreateFontToHandle( const char *FontName, int Size, int Thick, int FontType = -1 , int CharSet = -1 , int EdgeSize = -1 , int Italic = FALSE , int DataIndex = -1 , int ID = -1 ) ;			// �V�����t�H���g�f�[�^���쐬
extern	int			SetFontSpaceToHandle( int Point, int FontHandle ) ;															// ���Ԃ�ύX����
extern	int			SetDefaultFontState( const char *FontName, int Size, int Thick ) ;											// �f�t�H���g�t�H���g�̃X�e�[�^�X���ꊇ�ݒ肷��
extern	int			DeleteFontToHandle( int FontHandle ) ;																		// �t�H���g�L���b�V���̐�����I������
extern	int			SetFontLostFlag( int FontHandle, int *LostFlag ) ;															// ������� TRUE �ɂ���t���O�ւ̃|�C���^��ݒ肷��
extern	int			SetFontSize( int FontSize ) ;																				// �`�悷��t�H���g�̃T�C�Y���Z�b�g����
extern	int			SetFontThickness( int ThickPal ) ;																			// �t�H���g�̑������Z�b�g
extern	int			SetFontSpace( int Point ) ;																					// ���Ԃ�ύX����
extern	int			SetFontCacheToTextureFlag( int Flag ) ;																		// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����
extern	int			SetFontChacheToTextureFlag( int Flag ) ;																	// �t�H���g�̃L���b�V���Ƀe�N�X�`�����g�p���邩�A�t���O���Z�b�g����(�뎚��)
extern	int			SetFontCacheCharNum( int CharNum ) ;																		// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������w�肷��
extern	int			ChangeFont( const char *FontName, int CharSet = -1 /* DX_CHARSET_SHFTJIS */ ) ;								// �t�H���g��ύX
extern	int			ChangeFontType( int FontType ) ;																			// �t�H���g�^�C�v�̕ύX
// FontCacheStringDraw �� DrawString ���g���Ă�������
extern	int			FontCacheStringDrawToHandle( int x, int y, const char *StrData, int Color, int EdgeColor,
													BASEIMAGE *DestImage, RECT *ClipRect /* NULL �� */ , int FontHandle,
													int VerticalFlag = FALSE , SIZE *DrawSizeP = NULL ) ;

extern	int			GetFontMaxWidth( void ) ;																					// �����̍ő啝�𓾂�
extern	int			GetFontMaxWidthToHandle( int FontHandle ) ;																	// �����̍ő啝�𓾂�
extern	int			GetDrawStringWidth( const char *String, int StrLen, int VerticalFlag = FALSE ) ;							// ������̕��𓾂�
extern	int			GetDrawFormatStringWidth( const char *FormatString, ... ) ;													// �����t��������̕`�敝�𓾂�
extern	int			GetDrawStringWidthToHandle( const char *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;	// ������̕��𓾂�
extern	int			GetDrawFormatStringWidthToHandle( int FontHandle, const char *FormatString, ... ) ;							// �����t��������̕`�敝�𓾂�
extern	int			GetDrawExtendStringWidth( double ExRateX, const char *String, int StrLen, int VerticalFlag = FALSE ) ;							// ������̕��𓾂�
extern	int			GetDrawExtendFormatStringWidth( double ExRateX, const char *FormatString, ... ) ;												// �����t��������̕`�敝�𓾂�
extern	int			GetDrawExtendStringWidthToHandle( double ExRateX, const char *String, int StrLen, int FontHandle, int VerticalFlag = FALSE ) ;	// ������̕��𓾂�
extern	int			GetDrawExtendFormatStringWidthToHandle( double ExRateX, int FontHandle, const char *FormatString, ... ) ;						// �����t��������̕`�敝�𓾂�
extern	int			GetFontStateToHandle( char *FontName, int *Size, int *Thick, int FontHandle) ;								// �t�H���g�̏��𓾂�
extern	int			GetDefaultFontHandle( void ) ;																				// �f�t�H���g�̃t�H���g�̃n���h���𓾂�
extern	int			GetFontChacheToTextureFlag( void ) ;																		// �t�H���g�Ƀe�N�X�`���L���b�V�����g�p���邩�ǂ������擾����
extern	int			CheckFontChacheToTextureFlag( int FontHandle ) ;															// �w��̃t�H���g���e�N�X�`���L���b�V�����g�p���Ă��邩�ǂ����𓾂�
//extern	LPFONTMANAGE GetFontManageDataToHandle( int FontHandle ) ;																// �t�H���g�Ǘ��f�[�^�̎擾
extern	int			CheckFontHandleValid( int FontHandle ) ;																	// �w��̃t�H���g�n���h�����L�����ۂ����ׂ�
extern	int			MultiByteCharCheck( const char *Buf, int CharSet /* DX_CHARSET_SHFTJIS */ ) ;									// �Q�o�C�g���������ׂ�( TRUE:�Q�o�C�g����  FALSE:�P�o�C�g���� )
extern	int			GetFontCacheCharNum( void ) ;																				// �t�H���g�L���b�V���ŃL���b�V���ł��镶�������擾����( �߂�l  0:�f�t�H���g  1�ȏ�:�w�蕶���� )

#ifndef DX_NON_MASK

// �}�X�N�֌W
extern	int			CreateMaskScreen( void ) ;																				// �}�X�N�X�N���[�����쐬����
extern	int			DeleteMaskScreen( void ) ;																				// �}�X�N�X�N���[�����폜����
extern	void*		GetMaskSurface( void ) ; /* �߂�l�� IDirectDrawSurface7 * �ɃL���X�g���ĉ����� */						// �}�X�N�T�[�t�F�X���擾����
//extern	MEMIMG 		*GetMaskMemImg( void ) ;																				// �}�X�N�T�[�t�F�X�̑���� MEMIMG ���擾����
extern	int			DrawMaskToDirectData( int x, int y, int Width, int Height, void *MaskData , int TransMode ) ;			// �}�X�N�̃f�[�^�𒼐ڃZ�b�g
extern	int			DrawFillMaskToDirectData( int x1, int y1, int x2, int y2,  int Width, int Height, void *MaskData ) ;	// �}�X�N�̃f�[�^�𒼐ڃ}�X�N��ʑS�̂ɕ`�悷��

extern	int			SetUseMaskScreenFlag( int ValidFlag ) ;																	// �}�X�N�g�p���[�h��ύX
extern	int			GetUseMaskScreenFlag( void ) ;																			// �}�X�N�g�p���[�h�̎擾
extern	int			FillMaskScreen( int Flag ) ;																			// �}�X�N�X�N���[�����w��̐F�œh��Ԃ�

extern	int			InitMask( void ) ;																						// �}�X�N�f�[�^������������
extern	int			MakeMask( int Width, int Height ) ;																		// �}�X�N�f�[�^�̒ǉ�
extern	int			GetMaskSize( int *WidthBuf, int *HeightBuf, int MaskHandle ) ;											// �}�X�N�̑傫���𓾂� 
extern	int			SetDataToMask( int Width, int Height, void *MaskData, int MaskHandle ) ;								// �}�X�N�̃f�[�^���}�X�N�ɓ]������
extern	int			DeleteMask( int MaskHandle ) ;																			// �}�X�N�f�[�^���폜
extern	int			BmpBltToMask( HBITMAP Bmp, int BmpPointX, int BmpPointY, int MaskHandle ) ;								// �}�X�N�f�[�^�ɂa�l�o�f�[�^���}�X�N�f�[�^�ƌ����Ăē]��
extern	int			LoadMask( const char *FileName ) ;																		// �}�X�N�f�[�^�����[�h����
extern	int			LoadDivMask( const char *FileName, int AllNum, int XNum, int YNum, int XSize, int YSize, int *HandleBuf ) ;	// �}�X�N���摜���番���ǂ݂���
extern	int			DrawMask( int x, int y, int MaskHandle, int TransMode ) ;												// �}�X�N���Z�b�g����
extern	int			DrawFormatStringMask( int x, int y, int Flag, const char *FormatString, ... ) ;							// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��
extern	int			DrawFormatStringMaskToHandle( int x, int y, int Flag, int FontHandle, const char *FormatString, ... ) ;	// �����w�肠��̕�������}�X�N�X�N���[���ɕ`�悷��(�t�H���g�n���h���w���)
extern	int			DrawStringMask( int x, int y, int Flag, const char *String ) ;											// ��������}�X�N�X�N���[���ɕ`�悷��
extern	int			DrawStringMaskToHandle( int x, int y, int Flag, int FontHandle, const char *String ) ;					// ��������}�X�N�X�N���[���ɕ`�悷��(�t�H���g�n���h���w���)
extern	int			DrawFillMask( int x1, int y1, int x2, int y2, int MaskHandle ) ;										// �w��̃}�X�N����ʂ����ς��ɓW�J����	
extern	int			SetMaskTransColor( int ColorCode ) ;																	// �}�X�N�Ɏg�����ߐF�̃Z�b�g
extern	int			SetMaskReverseEffectFlag( int ReverseFlag ) ;															// �}�X�N�̐��l�ɑ΂�����ʂ��t�]������

extern 	int			GetMaskScreenData( int x1, int y1, int x2, int y2, int MaskHandle ) ;									// �}�X�N��ʏ�̕`���Ԃ��擾����
extern	int			GetMaskUseFlag( void ) ;																				// �}�X�N�X�N���[�����g�p�����t���O�̎擾

#endif

// ��{�C���[�W�f�[�^�@�\���J�p�֐�
extern	int		LoadSoftImage( const char *FileName ) ;																		// �\�t�g�E�G�A�ň����C���[�W�̓ǂݍ���( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int		LoadSoftImageToMem( void *FileImage, int FileImageSize ) ;													// �\�t�g�E�G�A�ň����C���[�W�̃���������̓ǂݍ���( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int		MakeSoftImage( int SizeX, int SizeY ) ;																		// �\�t�g�E�G�A�ň����C���[�W�̍쐬( -1:�G���[  -1�ȊO:�C���[�W�n���h�� )
extern	int		MakeARGB8ColorSoftImage( int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGBA8 �J���[ )
extern	int		MakeXRGB8ColorSoftImage( int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( XRGB8 �J���[ )
extern	int		MakeRGB8ColorSoftImage( int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( RGB8 �J���[ )
extern	int		MakePAL8ColorSoftImage( int SizeX, int SizeY ) ;															// �\�t�g�E�G�A�ň����C���[�W�̍쐬( �p���b�g�Q�T�U�F �J���[ )

extern	int		DeleteSoftImage( int SIHandle ) ;																			// �\�t�g�E�G�A�ň����C���[�W�̉��

extern	int		GetSoftImageSize( int SIHandle, int *Width, int *Height ) ;													// �\�t�g�E�G�A�ň����C���[�W�̃T�C�Y���擾����

extern	int		FillSoftImage( int SIHandle, int r, int g, int b, int a ) ;													// �\�t�g�E�G�A�ň����C���[�W���w��F�œh��Ԃ�(�e�F�v�f�͂O�`�Q�T�T)
extern	int		GetPaletteSoftImage( int SIHandle, int PaletteNo, int *r, int *g, int *b, int *a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int		SetPaletteSoftImage( int SIHandle, int PaletteNo, int  r, int  g, int  b, int  a ) ;						// �\�t�g�E�G�A�ň����C���[�W�̃p���b�g���Z�b�g����(�e�F�v�f�͂O�`�Q�T�T)
extern	int		DrawPixelPalCodeSoftImage( int SIHandle, int x, int y, int palNo ) ;										// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�p���b�g�摜�p�A�L���l�͂O�`�Q�T�T)
extern	int		GetPixelPalCodeSoftImage( int SIHandle, int x, int y ) ;													// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F�R�[�h���擾����(�p���b�g�摜�p�A�߂�l�͂O�`�Q�T�T)
extern	int		DrawPixelSoftImage( int SIHandle, int x, int y, int  r, int  g, int  b, int  a ) ;							// �\�t�g�E�G�A�ň����C���[�W�̎w����W�Ƀh�b�g��`�悷��(�e�F�v�f�͂O�`�Q�T�T)
extern	int		GetPixelSoftImage(  int SIHandle, int x, int y, int *r, int *g, int *b, int *a ) ;							// �\�t�g�E�G�A�ň����C���[�W�̎w����W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int		BltSoftImage( int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int SrcSIHandle, int DestX, int DestY, int DestSIHandle ) ;	// �\�t�g�E�G�A�ň����C���[�W��ʂ̃C���[�W��ɓ]������
extern	int		DrawSoftImage( int x, int y, int SIHandle ) ;																// �\�t�g�E�G�A�ň����C���[�W����ʂɕ`�悷��

extern	int		CreateGraphFromSoftImage( int SIHandle ) ;																	// �\�t�g�E�G�A�ň����C���[�W����O���t�B�b�N�n���h�����쐬����( -1:�G���[  -1�ȊO:�O���t�B�b�N�n���h�� )
extern	int		ReCreateGraphFromSoftImage( int SIHandle, int GrHandle ) ;													// �\�t�g�E�G�A�ň����C���[�W��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int		CreateDivGraphFromSoftImage( int SIHandle, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf ) ;		// �\�t�g�E�G�A�ň����C���[�W���番���O���t�B�b�N�n���h�����쐬����


// ��{�C���[�W�f�[�^�\���̊֌W
extern	int		CreateBaseImage(  const char *FileName, void *FileImage, int FileImageSize, int DataType/*=LOADIMAGE_TYPE_FILE*/, BASEIMAGE *BaseImage, int ReverseFlag ) ;																						// �e��O���t�B�b�N�f�[�^�����{�C���[�W�f�[�^���\�z����
extern	int		CreateGraphImage( const char *FileName, void *DataImage, int DataImageSize, int DataImageType, BASEIMAGE *GraphImage, int ReverseFlag ) ;																										// CreateBaseImage �̋�����
extern	int		CreateBaseImageToFile( const char *FileName,               BASEIMAGE *BaseImage, int ReverseFlag = FALSE ) ;																																	// �摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int		CreateBaseImageToMem(  void *FileImage, int FileImageSize, BASEIMAGE *BaseImage, int ReverseFlag = FALSE ) ;																																	// ��������ɓW�J���ꂽ�摜�t�@�C�������{�C���[�W�f�[�^���\�z����
extern	int		CreateARGB8ColorBaseImage( int SizeX, int SizeY, BASEIMAGE *BaseImage ) ;																																										// �`�q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int		CreateXRGB8ColorBaseImage( int SizeX, int SizeY, BASEIMAGE *BaseImage ) ;																																										// �w�q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int		CreateRGB8ColorBaseImage( int SizeX, int SizeY, BASEIMAGE *BaseImage ) ;																																										// �q�f�a�W�J���[�̋�̊�{�C���[�W�f�[�^���쐬����
extern	int		CreatePAL8ColorBaseImage( int SizeX, int SizeY, BASEIMAGE *BaseImage ) ;																																										// �p���b�g�W�r�b�g�J���[�̋�̊�{�C���[�W�f�[�^���쐬����

extern	int		ReleaseBaseImage(  BASEIMAGE *BaseImage ) ;																																																		// ��{�C���[�W�f�[�^�̌�n�����s��
extern	int		ReleaseGraphImage( BASEIMAGE *GraphImage ) ;																																																	// ReleaseBaseImage �̋�����

extern	int		FillBaseImage( BASEIMAGE *BaseImage, int r, int g, int b, int a ) ;																																												// ��{�C���[�W�f�[�^���w��̐F�œh��Ԃ�
extern	int		GetPaletteBaseImage( BASEIMAGE *BaseImage, int PaletteNo, int *r, int *g, int *b, int *a ) ;																																					// ��{�C���[�W�f�[�^�̃p���b�g���擾����
extern	int		SetPaletteBaseImage( BASEIMAGE *BaseImage, int PaletteNo, int  r, int  g, int  b, int  a ) ;																																					// ��{�C���[�W�f�[�^�̃p���b�g���Z�b�g����
extern	int		SetPixelPalCodeBaseImage( BASEIMAGE *BaseImage, int x, int y, int palNo ) ;																																										// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h��ύX����(�p���b�g�摜�p)
extern	int		GetPixelPalCodeBaseImage( BASEIMAGE *BaseImage, int x, int y ) ;																																												// ��{�C���[�W�f�[�^�̎w��̍��W�̐F�R�[�h���擾����(�p���b�g�摜�p)
extern	int		SetPixelBaseImage( BASEIMAGE *BaseImage, int x, int y, int  r, int  g, int  b, int  a ) ;																																						// ��{�C���[�W�f�[�^�̎w��̍��W�̐F��ύX����(�e�F�v�f�͂O�`�Q�T�T)
extern	int		GetPixelBaseImage( BASEIMAGE *BaseImage, int x, int y, int *r, int *g, int *b, int *a ) ;																																						// ��{�C���[�W�f�[�^�̎w��̍��W�̐F���擾����(�e�F�v�f�͂O�`�Q�T�T)
extern	int		BltBaseImage( int SrcX, int SrcY, int SrcSizeX, int SrcSizeY, int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;																										// ��{�C���[�W�f�[�^��]������
extern	int		BltBaseImage( int DestX, int DestY, BASEIMAGE *SrcBaseImage, BASEIMAGE *DestBaseImage ) ;																																							// ��{�C���[�W�f�[�^��]������
extern	int		DrawBaseImage( int x, int y, BASEIMAGE *BaseImage ) ;																																															// ��{�C���[�W�f�[�^��`�悷��

extern	int		CreateGraphFromBaseImage( BASEIMAGE *BaseImage ) ;																																																// ��{�C���[�W�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateGraphFromBaseImage( BASEIMAGE *BaseImage, int GrHandle ) ;																																												// ��{�C���[�W�f�[�^��������̃O���t�B�b�N�n���h���ɉ摜�f�[�^��]������
extern	int		CreateDivGraphFromBaseImage( BASEIMAGE *BaseImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf ) ;																														// ��{�C���[�W�f�[�^���番���O���t�B�b�N�n���h�����쐬����


// �摜�쐬�p�֌W
extern	int		CreateGraphFromMem( void *MemImage, int MemImageSize, void *AlphaImage = NULL , int AlphaImageSize = 0 , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																						// ��������̃O���t�B�b�N�C���[�W����O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateGraphFromMem( void *MemImage, int MemImageSize, int GrHandle, void *AlphaImage = NULL , int AlphaImageSize = 0 , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																		// ��������̃O���t�B�b�N�C���[�W��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		CreateDivGraphFromMem( void *MemImage, int MemImageSize, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , void *AlphaImage = NULL , int AlphaImageSize = 0 ) ;				// ��������̃O���t�B�b�N�C���[�W���番���O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateDivGraphFromMem( void *MemImage, int MemImageSize, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , void *AlphaImage = NULL , int AlphaImageSize = 0 ) ;			// ��������̃O���t�B�b�N�C���[�W��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		CreateGraphFromBmp( BITMAPINFO *BmpInfo, void *GraphData, BITMAPINFO *AlphaInfo = NULL , void *AlphaData = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																				// �r�b�g�}�b�v�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateGraphFromBmp( BITMAPINFO *BmpInfo, void *GraphData, int GrHandle, BITMAPINFO *AlphaInfo = NULL , void *AlphaData = NULL , int TextureFlag = TRUE , int ReverseFlag = FALSE ) ;																// �r�b�g�}�b�v�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		CreateDivGraphFromBmp( BITMAPINFO *BmpInfo, void *GraphData, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , BITMAPINFO *AlphaInfo = NULL , void *AlphaData = NULL ) ;		// �r�b�g�}�b�v�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateDivGraphFromBmp( BITMAPINFO *BmpInfo, void *GraphData, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , BITMAPINFO *AlphaInfo = NULL , void *AlphaData = NULL ) ;	// �r�b�g�}�b�v�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		CreateGraphFromGraphImage( BASEIMAGE *Image, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;																													// GraphImage�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int		CreateGraphFromGraphImage( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;																								// GraphImage�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateGraphFromGraphImage( BASEIMAGE *Image, int GrHandle, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;																									// GraphImage�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		ReCreateGraphFromGraphImage( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int GrHandle, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;																				// GraphImage�f�[�^��������̃O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		CreateDivGraphFromGraphImage( BASEIMAGE *Image, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;											// GraphImage�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int		CreateDivGraphFromGraphImage( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;						// GraphImage�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateDivGraphFromGraphImage( BASEIMAGE *Image, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;											// GraphImage�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		ReCreateDivGraphFromGraphImage( BASEIMAGE *Image, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag = TRUE , int ReverseFlag = FALSE , int DataReverseFlag = TRUE ) ;					// GraphImage�f�[�^��������̕����O���t�B�b�N�n���h���Ƀf�[�^��]������
extern	int		SetGraphName( int Handle, const char *GraphName ) ;																																																// ����̃t�@�C������摜��ǂݍ��񂾏ꍇ�̃t�@�C���p�X���Z�b�g����
extern	int		CreateGraph( int Width, int Height, int Pitch, void *GraphData, void *AlphaData = NULL , int GrHandle = -1 ) ;																																	// ��������̃O���t�B�b�N�f�[�^����O���t�B�b�N�n���h�����쐬����
extern	int		CreateDivGraph( int Width, int Height, int Pitch, void *GraphData, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, void *AlphaData = NULL ) ;																				// ��������̃O���t�B�b�N�f�[�^���番���O���t�B�b�N�n���h�����쐬����
extern	int		ReCreateGraph( int Width, int Height, int Pitch, void *GraphData, int GrHandle, void *AlphaData = NULL ) ;																																		// ��������̃O���t�B�b�N�f�[�^����O���t�B�b�N�n���h�����č쐬����
extern	int		CreateBmpInfo( BITMAPINFO *BmpInfo, int Width, int Height, int Pitch, void *SrcGrData, void **DestGrData ) ;																																	// �t���J���[�`����BITMAPINFO�\���̂��쐬����
extern	HBITMAP	CreateDIBGraphVer2( const char *FileName, void *MemImage, int MemImageSize, int ImageType, int ReverseFlag, COLORDATA *SrcColor ) ;																												// �c�h�a�O���t�B�b�N���쐬����(�o�[�W�����Q)
extern	int		CreateDIBGraphVer2_plus_Alpha( const char *FileName, void *MemImage, int MemImageSize, void *AlphaImage, int AlphaImageSize, int ImageType, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag, COLORDATA *SrcColor ) ;						// �c�h�a�O���t�B�b�N���쐬����
extern	DWORD	GetGraphImageFullColorCode( BASEIMAGE *GraphImage, int x, int y ) ;																																												// BASEIMAGE �\���̂̉摜��񂩂�w��̍��W�̃t���J���[�R�[�h���擾����
extern	int		CreateGraphImageType2( STREAMDATA *Src, BASEIMAGE *Dest ) ;																																														// �ėp�ǂݍ��ݏ����ɂ��O���t�B�b�N�C���[�W�\�z�֐�( 0:����  -1:���s )
extern	int		CreateGraphImage_plus_Alpha( const char *FileName, void *RgbImage, int RgbImageSize, int RgbImageType,
													void *AlphaImage, int AlphaImageSize, int AlphaImageType,
													BASEIMAGE *RgbGraphImage, BASEIMAGE *AlphaGraphImage, int ReverseFlag ) ;																																	// �e��O���t�B�b�N�f�[�^����O���t�B�b�N�C���[�W�f�[�^�ƃA���t�@�}�b�v�p�C���[�W�f�[�^���\�z����
extern	int		CreateGraphImageOrDIBGraph( const char *FileName, void *DataImage, int DataImageSize, int DataImageType, int BmpFlag, int ReverseFlag, BASEIMAGE *Image, BITMAPINFO **BmpInfo, void **GraphData ) ;												// �o�^����Ă���e��O���t�B�b�N���[�_�֐�����A�a�l�o�f�[�^�������� GraphImage�f�[�^���\�z����
extern	int		ReverseGraphImage( BASEIMAGE *GraphImage ) ;																																																	// �w��� GraphImage �����E���]����
extern	int		ConvBitmapToGraphImage( BITMAPINFO *BmpInfo, void *GraphData, BASEIMAGE *GraphImage, int CopyFlag ) ;																																			// �a�l�o �� GraphImage �ɕϊ�����( Ret 0:����I��  1:�R�s�[���s����  -1:�G���[ )
extern	int		ConvGraphImageToBitmap( BASEIMAGE *GraphImage, BITMAPINFO *BmpInfo, void **GraphData, int CopyFlag, int FullColorConv = TRUE ) ;																												// GraphImage �� �a�l�o �ɕϊ�����(�A���t�@�f�[�^�͂����Ă����������)( Ret 0:����I��  1:�R�s�[���s����  -1:�G���[ )
extern	HBITMAP	CreateDIBGraph( const char *FileName, int ReverseFlag, COLORDATA *SrcColor) ;																																									// �c�h�a�O���t�B�b�N���쐬����
extern	HBITMAP	CreateDIBGraphToMem( BITMAPINFO *BmpInfo, void *GraphData, int ReverseFlag, COLORDATA *SrcColor ) ;																																				// �c�h�a�O���t�B�b�N���������C���[�W����쐬����
extern	int		CreateDIBGraph_plus_Alpha( const char *FileName, HBITMAP *RGBBmp, HBITMAP *AlphaBmp, int ReverseFlag = FALSE , COLORDATA *SrcColor = NULL ) ;																									// �t�@�C������c�h�a�O���t�B�b�N�ƃ}�X�N�O���t�B�b�N���쐬����
extern	int		CreateDXGraph( BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int TextureFlag ) ;																																									// GraphImage �f�[�^����T�C�Y������o���A����ɍ������O���t�B�b�N�n���h�����쐬����
extern	int		CreateDXDivGraph( BASEIMAGE *RgbImage, BASEIMAGE *AlphaImage, int AllNum, int XNum, int YNum, int SizeX, int SizeY, int *HandleBuf, int TextureFlag ) ;																							// GraphImage �f�[�^�ɍ������T�C�Y�̕����O���t�B�b�N�n���h�����쐬����
extern	int		DerivationGraph( int SrcX, int SrcY, int Width, int Height, int SrcGraphHandle ) ;																																								// �w��̃O���t�B�b�N�̎w�蕔�������𔲂��o���ĐV���ȃO���t�B�b�N�n���h�����쐬����



#ifndef DX_NON_MOVIE
// ���[�r�[�O���t�B�b�N�֌W�֐�
extern	int		PlayMovie( const char *FileName, int ExRate, int PlayType ) ;									// ����t�@�C���̍Đ�
extern	int		OpenMovieToGraph( const char *FileName, int FullColor = TRUE ) ;								// ���[�r�[���J��
extern 	int		PlayMovieToGraph( int GraphHandle, int PlayType = DX_PLAYTYPE_BACK ) ;							// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����J�n����
extern 	int		PauseMovieToGraph( int GraphHandle ) ;															// ���[�r�[�O���t�B�b�N�Ɋ܂܂�郀�[�r�[�̍Đ����X�g�b�v����
extern	int		AddMovieFrameToGraph( int GraphHandle, unsigned int FrameNum ) ;								// ���[�r�[�̃t���[����i�߂�A�߂����Ƃ͏o���Ȃ�( ���[�r�[����~��ԂŁA���� Ogg Theora �̂ݗL�� )
extern	int		SeekMovieToGraph( int GraphHandle, int Time ) ;													// ���[�r�[�̍Đ��ʒu��ݒ肷��(�~���b�P��)
extern 	int		GetMovieStateToGraph( int GraphHandle ) ;														// ���[�r�[�̍Đ���Ԃ𓾂�
extern	int		SetMovieVolumeToGraph( int Volume, int GraphHandle ) ;											// ���[�r�[�̃{�����[�����Z�b�g����(0�`10000)
extern	BASEIMAGE* GetMovieBaseImageToGraph( int GraphHandle ) ;												// ���[�r�[�̊�{�C���[�W�f�[�^���擾����
extern	int		GetMovieTotalFrameToGraph( int GraphHandle ) ;													// ���[�r�[�̑��t���[�����𓾂�( Ogg Theora �ł̂ݗL�� )
extern	int		TellMovieToGraph( int GraphHandle ) ;															// ���[�r�[�̍Đ��ʒu���擾����(�~���b�P��)
extern	int		TellMovieToGraphToFrame( int GraphHandle ) ;													// ���[�r�[�̍Đ��ʒu���擾����(�t���[���P��)
extern	int		SeekMovieToGraphToFrame( int GraphHandle, int Frame ) ;											// ���[�r�[�̍Đ��ʒu��ݒ肷��(�t���[���P��)
extern	LONGLONG GetOneFrameTimeMovieToGraph( int GraphHandle ) ;												// ���[�r�[�̂P�t���[��������̎��Ԃ𓾂�

#endif

#endif // DX_NOTUSE_DRAWFUNCTION












// DxSound.cpp�֐��v���g�^�C�v�錾

// �T�E���h�f�[�^�Ǘ��n�֐�
extern	int InitSoundMem( int LogOutFlag = FALSE ) ;																// �������ɓǂ݂���WAVE�f�[�^���폜���A����������

extern	int AddSoundData( int Handle = -1 ) ;																		// �V�����T�E���h�f�[�^�̈���m�ۂ���
extern	int AddStreamSoundMem( STREAMDATA *Stream, int LoopNum,  int SoundHandle, int StreamDataType, int *CanStreamCloseFlag, int UnionHandle = -1 ) ;	// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int AddStreamSoundMemToMem( void *FileImageBuffer, int ImageSize, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;	// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int AddStreamSoundMemToFile( const char *WaveFile, int LoopNum,  int SoundHandle, int StreamDataType, int UnionHandle = -1 ) ;	// �X�g���[�����T�E���h�f�[�^�ɃT�E���h�f�[�^��ǉ�����
extern	int SetupStreamSoundMem( int SoundHandle ) ;																// �X�g���[�����T�E���h�f�[�^�̍Đ��������s��
extern	int PlayStreamSoundMem( int SoundHandle, int PlayType = DX_PLAYTYPE_LOOP , int TopPositionFlag = TRUE ) ;	// �X�g���[�����T�E���h�f�[�^�̍Đ��J�n
extern	int CheckStreamSoundMem( int SoundHandle ) ;																// �X�g���[�����T�E���h�f�[�^�̍Đ���Ԃ𓾂�
extern	int StopStreamSoundMem( int SoundHandle ) ;																	// �X�g���[�����T�E���h�f�[�^�̍Đ��I��
extern	int SetStreamSoundCurrentPosition( int Byte, int SoundHandle ) ;											// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	int GetStreamSoundCurrentPosition( int SoundHandle ) ;														// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int SetStreamSoundCurrentTime( int Time, int SoundHandle ) ;												// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	int GetStreamSoundCurrentTime( int SoundHandle ) ;															// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	int ProcessStreamSoundMem( int SoundHandle ) ;																// �X�g���[���T�E���h�̍Đ������֐�
extern	int ProcessStreamSoundMemAll( void ) ;																		// �L���ȃX�g���[���T�E���h�̂��ׂčĐ������֐��ɂ�����


extern	int LoadSoundMem2( const char *WaveName1, const char *WaveName2 ) ;											// �O�t���ƃ��[�v���ɕ����ꂽ�T�E���h�f�[�^�̍쐬
extern	int LoadBGM( const char *WaveName ) ;																		// ��ɂa�f�l��ǂݍ��ނ̂ɓK�����֐�

extern	int LoadSoundMemBase( const char *WaveName, int BufferNum, int UnionHandle ) ;								// �T�E���h�f�[�^��ǉ�����
extern	int LoadSoundMem( const char *WaveName, int BufferNum = 3 , int UnionHandle = -1 ) ;						// �T�E���h�f�[�^��ǉ�����
extern	int LoadSoundMemToBufNumSitei( const char *WaveName, int BufferNum ) ;										// �����Đ����w��^�T�E���h�ǉ��֐�
extern	int LoadSoundMemByResource( const char *ResourceName, const char *ResourceType, int BufferNum = 1 ) ;		// �T�E���h�����\�[�X����ǂݍ���

extern	int LoadSoundMemByMemImageBase( void *FileImageBuffer, int ImageSize, int BufferNum, int UnionHandle = -1 ) ; // ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����(�x�[�X�֐�)
extern	int LoadSoundMemByMemImage( void *FileImageBuffer, int ImageSize, int UnionHandle = -1 ) ;					// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����(�o�b�t�@���w�肠��) 
extern	int LoadSoundMemByMemImage2( void *UData, int UDataSize, WAVEFORMATEX *UFormat, int UHeaderSize ) ;			// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����2
extern	int LoadSoundMemByMemImageToBufNumSitei( void *FileImageBuffer, int ImageSize, int BufferNum ) ;			// ��������ɓW�J���ꂽ�t�@�C���C���[�W����n���h�����쐬����
extern	int LoadSoundMem2ByMemImage( void *FileImageBuffer1, int ImageSize1, void *FileImageBuffer2, int ImageSize2 ) ;	// ��������ɓW�J���ꂽ�t�@�C���C���[�W����O�t���ƃ��[�v���ɕ����ꂽ�n���h�����쐬����

extern	int DeleteSoundMem( int SoundHandle, int LogOutFlag = FALSE ) ;												// �������ɓǂݍ���WAVE�f�[�^���폜����

extern	int PlaySoundMem( int SoundHandle, int PlayType, int TopPositionFlag = TRUE ) ;								// �������ɓǂ݂���WAVE�f�[�^���Đ�����
extern	int StopSoundMem( int SoundHandle ) ;																		// �������ɓǂݍ���WAVE�f�[�^�̍Đ����~�߂�
extern	int CheckSoundMem( int SoundHandle ) ;																		// �������ɓǂ݂���WAVE�f�[�^���Đ��������ׂ�
extern	int SetPanSoundMem( int PanPal, int SoundHandle ) ;															// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀp����ݒ肷��
extern	int SetVolumeSoundMem( int VolumePal, int SoundHandle ) ;													// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀ{�����[����ݒ肷��( 100����1�f�V�x���P�� )
extern	int ChangeVolumeSoundMem( int VolumePal, int SoundHandle ) ;												// �������ɓǂ݂���WAVE�f�[�^�̍Đ��Ƀ{�����[����ݒ肷��( �p�[�Z���g�w�� )
extern	int GetVolumeSoundMem( int SoundHandle ) ;																	// �������ɓǂ݂���WAVE�f�[�^�̍Đ��̃{�����[�����擾����
extern	int SetFrequencySoundMem( int FrequencyPal, int SoundHandle ) ;												// �������ɓǂݍ���WAVE�f�[�^�̍Đ����g����ݒ肷��
extern	int GetFrequencySoundMem( int SoundHandle ) ;																// �������ɓǂݍ���WAVE�f�[�^�̍Đ����g�����擾����

extern	int SetSoundCurrentPosition( int Byte, int SoundHandle ) ;													// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŕύX����(�Đ����~�܂��Ă��鎞�̂ݗL��)
extern	int GetSoundCurrentPosition( int SoundHandle ) ;															// �T�E���h�n���h���̍Đ��ʒu���o�C�g�P�ʂŎ擾����
extern	int SetSoundCurrentTime( int Time, int SoundHandle ) ;														// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŐݒ肷��(���k�`���̏ꍇ�͐������ݒ肳��Ȃ��ꍇ������)
extern	int GetSoundCurrentTime( int SoundHandle ) ;																// �T�E���h�n���h���̍Đ��ʒu���~���b�P�ʂŎ擾����(���k�`���̏ꍇ�͐������l���Ԃ��Ă��Ȃ��ꍇ������)
extern	int GetSoundTotalSample( int SoundHandle ) ;																// �T�E���h�n���h���̉��̑����Ԃ��擾����(�P�ʂ̓T���v��)
extern	int GetSoundTotalTime( int SoundHandle ) ;																	// �T�E���h�n���h���̉��̑����Ԃ��擾����(�P�ʂ̓~���b)

extern	int SetLoopPosSoundMem( int LoopTime, int SoundHandle ) ;													// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��
extern	int SetLoopTimePosSoundMem( int LoopTime, int SoundHandle ) ;												// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��
extern	int SetLoopSamplePosSoundMem( int LoopSamplePosition, int SoundHandle ) ;									// �T�E���h�n���h���Ƀ��[�v�ʒu��ݒ肷��

// �ݒ�֌W�֐�
extern	int SetCreateSoundDataType( int SoundDataType ) ;															// �쐬����T�E���h�̃f�[�^�`����ݒ肷��( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int GetCreateSoundDataType( void ) ;																		// �쐬����T�E���h�̃f�[�^�`�����擾����( DX_SOUNDDATATYPE_MEMNOPRESS �� )
extern	int SetEnableSoundCaptureFlag( int Flag ) ;																	// �T�E���h�L���v�`����O��Ƃ�����������邩�ǂ�����ݒ肷��

// ���擾�n�֐�
extern	void* GetDSoundObj( void ) ;	/* �߂�l�� IDirectSound * �ɃL���X�g���ĉ����� */							// �c�w���C�u�������g�p���Ă��� DirectSound �I�u�W�F�N�g���擾����

#ifndef DX_NON_BEEP
// BEEP���Đ��p����
extern	int SetBeepFrequency( int Freq ) ;																			// �r�[�v�����g���ݒ�֐�
extern	int PlayBeep( void ) ;																						// �r�[�v�����Đ�����
extern	int StopBeep( void ) ;																						// �r�[�v�����~�߂�
#endif

// ���b�p�[�֐�
extern	int	PlaySoundFile( const char *FileName, int PlayType ) ;													// WAVE�t�@�C�����Đ�����
extern	int	PlaySound( const char *FileName, int PlayType ) ;														// PlaySoundFile �̋�����
extern	int	CheckSoundFile( void ) ;																				// WAVE�t�@�C���̍Đ��������ׂ�
extern	int	CheckSound( void ) ;																					// CheckSoundFile �̋�����
extern	int	StopSoundFile( void ) ;																					// WAVE�t�@�C���̍Đ����~�߂�
extern	int	StopSound( void ) ;																						// StopSoundFile �̋�����
extern	int SetVolumeSoundFile( int VolumePal ) ;																	// WAVE�t�@�C���̉��ʂ��Z�b�g����
extern	int SetVolumeSound( int VolumePal ) ;																		// SetVolumeSound �̋�����


// �l�h�c�h����֐�
extern	int AddMusicData( void ) ;																					// �V�����l�h�c�h�n���h�����擾����
extern	int DeleteMusicMem( int MusicHandle ) ;																		// �l�h�c�h�n���h�����폜����
extern	int LoadMusicMem( const char *FileName ) ;																	// �l�h�c�h�t�@�C����ǂݍ���
extern	int LoadMusicMemByMemImage( void *FileImageBuffer, int FileImageSize ) ;									// ��������ɓW�J���ꂽ�l�h�c�h�t�@�C����ǂݍ���
extern	int LoadMusicMemByResource( const char *ResourceName, const char *ResourceType ) ;							// ���\�[�X��̂l�h�c�h�t�@�C����ǂݍ���
extern	int PlayMusicMem( int MusicHandle, int PlayType ) ;															// �ǂݍ��񂾂l�h�c�h�f�[�^�̉��t���J�n����
extern	int StopMusicMem( int MusicHandle ) ;																		// �l�h�c�h�f�[�^�̉��t���~����
extern	int CheckMusicMem( int MusicHandle ) ;																		// �l�h�c�h�f�[�^�����t�����ǂ������擾����( TRUE:���t��  FALSE:��~�� )
extern	int GetMusicMemPosition( int MusicHandle ) ;																// �l�h�c�h�f�[�^�̌��݂̍Đ��ʒu���擾����
extern	int InitMusicMem( void ) ;																					// �l�h�c�h�f�[�^�n���h�������ׂč폜����
extern	int ProcessMusicMem( void ) ;																				// �l�h�c�h�f�[�^�̎����I����

extern	int PlayMusic( const char *FileName, int PlayType ) ;														// �l�h�c�h�t�@�C�������t����
extern	int PlayMusicByMemImage( void *FileImageBuffer, int FileImageSize, int PlayType ) ;							// ��������ɓW�J����Ă���l�h�c�h�t�@�C�������t����
extern	int PlayMusicByResource( const char *ResourceName, const char *ResourceType, int PlayType ) ;				// ���\�[�X����l�h�c�h�t�@�C����ǂݍ���ŉ��t����
extern	int SetVolumeMusic( int Volume ) ;																			// �l�h�c�h�̍Đ����ʂ��Z�b�g����
extern	int StopMusic( void ) ;																						// �l�h�c�h�t�@�C���̉��t��~
extern	int	CheckMusic( void ) ;																					// �l�h�c�h�t�@�C�������t�����ۂ������擾����
extern	int GetMusicPosition( void ) ;																				// �l�h�c�h�̌��݂̍Đ��ʒu���擾����

extern	int SelectMidiMode( int Mode ) ;																			// �l�h�c�h�̍Đ��`�����Z�b�g����











// DxArchive_.cpp �֐� �v���g�^�C�v�錾
extern	int DXArchivePreLoad( const char *FilePath , int ASync = FALSE ) ;	// �w��̂c�w�`�t�@�C�����ۂ��ƃ������ɓǂݍ���( �߂�l: -1=�G���[  0=���� )
extern	int DXArchiveCheckIdle( const char *FilePath ) ;					// �w��̂c�w�`�t�@�C���̎��O�ǂݍ��݂������������ǂ������擾����( �߂�l�F TRUE=�������� FALSE=�܂� )
extern	int DXArchiveRelease( const char *FilePath ) ;						// �w��̂c�w�`�t�@�C��������������������


















#define DX_FUNCTION_END


// DxModel.cpp �֐� �v���g�^�C�v�錾

#ifndef DX_NON_MODEL

extern	int			MV1LoadModel( const char *FileName ) ;													// ���f���̓ǂݍ���( -1:�G���[  0�ȏ�:���f���n���h�� )

extern	int			MV1AttachMotion( int MHandle, int MV1ModelHandle, const char *MotionName, int MotionIndex = -1, int AttachIndex = 0 ) ;	// ���[�V�������A�^�b�`����
extern	int			MV1DetachMotion( int MHandle, int AttachIndex = 0 ) ;									// ���[�V�������f�^�b�`����

extern	int			MV1PlayMotion( int MHandle, int Loop, int AttachIndex = 0 ) ;							// ���[�V�������Đ�����
extern	int			MV1MotionAddTime( int MHandle, float AddTime, int AttachIndex = 0 ) ;					// ���[�V������i�߂�
extern	int			MV1StopMotion( int MHandle, int AttachIndex = 0 ) ;										// ���[�V�������~�߂�
extern	int			MV1GetMotionState( int MHandle, int AttachIndex = 0 ) ;									// ���[�V�������Đ������ǂ������擾����( TRUE:�Đ���  FALSE:��~�� )

extern	int			MV1SetPosition( int MHandle, float x, float y, float z ) ;								// ���f���̈ʒu���Z�b�g
extern	int			MV1SetScale( int MHandle, float x, float y, float z ) ;									// ���f���̃X�P�[�����Z�b�g
extern	int			MV1SetRotation( int MHandle, float x, float y, float z ) ;								// ���f���̃��[�e�[�V�������Z�b�g
extern	int			MV1DrawModel( int MHandle ) ;															// ���f���̕`��

#if 0

// ���f���f�[�^�`��y�уA�j���[�V�����n
extern int StartModelAnimation( int ModelHandle, char *AnimationName, int AnimeType ) ;				// �A�j���[�V���������s����
extern int StopModelAnimation( int ModelHandle ) ;													// �A�j���[�V�������~�߂�
extern int AddModelAnimationTime( int ModelHandle, float AddTime ) ;								// �A�j���[�V�����̍Đ��|�C���g���ړ�����

extern int DrawModel( float x, float y, float z, int Modelhandle ) ;								// ���f����`�悷��

// �O�����J�֐�
extern int LoadModel( char *FileName ) ;															// ���f���f�[�^��ǂݍ���  
extern int DeleteModel( int ModelHandle ) ;															// ���f�����폜����
extern int InitModel( void ) ;																		// ���f���f�[�^����|����

#endif

#endif



// �c�w���C�u���������ł̂ݎg�p����w�b�_�t�@�C���̃C���N���[�h -------------------------

#ifdef __DX_MAKE
	#include "DxStatic.h"
#endif


#endif


