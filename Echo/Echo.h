
// Echo.h: основной файл заголовка для приложения Echo
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CEchoApp:
// Сведения о реализации этого класса: Echo.cpp
//

class CEchoApp : public CWinApp
{
public:
	CEchoApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEchoApp theApp;
