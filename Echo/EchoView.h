
// EchoView.h: интерфейс класса CEchoView
//

#pragma once


class CEchoView : public CView
{
private:
	POINT m_CaretPos;
	int m_XCaret, m_YCaret;

protected: // создать только из сериализации
	CEchoView() noexcept;
	DECLARE_DYNCREATE(CEchoView)

// Атрибуты
public:
	CEchoDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CEchoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditClear();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

#ifndef _DEBUG  // версия отладки в EchoView.cpp
inline CEchoDoc* CEchoView::GetDocument() const
   { return reinterpret_cast<CEchoDoc*>(m_pDocument); }
#endif

