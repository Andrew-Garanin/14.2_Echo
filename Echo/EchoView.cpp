
// EchoView.cpp: реализация класса CEchoView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Echo.h"
#endif

#include "EchoDoc.h"
#include "EchoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEchoView

IMPLEMENT_DYNCREATE(CEchoView, CView)

BEGIN_MESSAGE_MAP(CEchoView, CView)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_CLEAR, &CEchoView::OnEditClear)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// Создание или уничтожение CEchoView

CEchoView::CEchoView() noexcept
{
	// TODO: добавьте код создания
	m_CaretPos.x = m_CaretPos.y = 0;
}

CEchoView::~CEchoView()
{
}

BOOL CEchoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CEchoView

void CEchoView::OnDraw(CDC* pDC)
{
	CEchoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(0, 0, pDoc->m_TextLine);

}


// Диагностика CEchoView

#ifdef _DEBUG
void CEchoView::AssertValid() const
{
	CView::AssertValid();
}

void CEchoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEchoDoc* CEchoView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEchoDoc)));
	return (CEchoDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CEchoView


void CEchoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar < 32)
	{
		::MessageBeep(MB_OK); // генерация стандартного звука
		return;
	}

	CEchoDoc* PDoc = GetDocument();
	PDoc->m_TextLine += (wchar_t)nChar;

	CClientDC ClientDC(this);

	ClientDC.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	ClientDC.SetBkMode(TRANSPARENT);
	HideCaret();
	ClientDC.TextOut(0, 0, PDoc->m_TextLine);
	CSize Size = ClientDC.GetTextExtent(PDoc->m_TextLine,
		PDoc->m_TextLine.GetLength());
	m_CaretPos.x = Size.cx;
	SetCaretPos(m_CaretPos);
	ShowCaret();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CEchoView::OnEditClear()
{
	// TODO: добавьте свой код обработчика команд
	CEchoDoc* PDoc = GetDocument();
	PDoc->m_TextLine.Empty();
	PDoc->UpdateAllViews(NULL);
	m_CaretPos.x = 0;
	SetCaretPos(m_CaretPos);

}


int CEchoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	CClientDC ClientDC(this);
	TEXTMETRIC TM;
	ClientDC.GetTextMetrics(&TM);
	m_XCaret = TM.tmAveCharWidth / 3;
	m_YCaret = TM.tmHeight + TM.tmExternalLeading;

	return 0;
}


void CEchoView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: добавьте свой код обработчика сообщений
	::DestroyCaret();
}


void CEchoView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: добавьте свой код обработчика сообщений
	CreateSolidCaret(m_XCaret, m_YCaret);
	SetCaretPos(m_CaretPos);
	ShowCaret();

}
