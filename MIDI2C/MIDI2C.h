
// MIDI2C.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMIDI2CApp: 
// �йش����ʵ�֣������ MIDI2C.cpp
//

class CMIDI2CApp : public CWinApp
{
public:
	CMIDI2CApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMIDI2CApp theApp;