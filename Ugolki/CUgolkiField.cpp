// CUgolkiField.cpp: файл реализации
//

#include "pch.h"

#define UgolkiFIELD_CLASSNAME L"UgolkiField"
#define FIELDNUMBRERSSPACE 20
#define TIMER_ID 101

// CUgolkiField

IMPLEMENT_DYNAMIC(CUgolkiField, CWnd)

CUgolkiField::CUgolkiField()
{

	FieldSizeX = 8;
	FieldSizeY = 8;
	gameParent = nullptr;
	this->RegisterClass();
	nSelectedX = -1;
	nSelectedY = -1;
}

CUgolkiField::~CUgolkiField()
{
}


BEGIN_MESSAGE_MAP(CUgolkiField, CWnd)
	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
//ON_WM_RBUTTONDOWN()
ON_WM_LBUTTONUP()
//ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// Обработчики сообщений CUgolkiField




bool CUgolkiField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, UgolkiFIELD_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = UgolkiFIELD_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


void CUgolkiField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CWnd::OnPaint() для сообщений рисования

	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	CRect rect;
	GetClientRect(&rect);



	CPen ourPen;
	HGDIOBJ oldPen;
	ourPen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(ourPen);

	oldPen = dc.SelectObject(ourPen);

	int hPartSize = (rect.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rect.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;

	this->HighlightSelection(dc);

	for (int i = 0; i < FieldSizeX + 1; i++)
	{
		dc.MoveTo(FIELDNUMBRERSSPACE + i * hPartSize, FIELDNUMBRERSSPACE);
		dc.LineTo(FIELDNUMBRERSSPACE + i * hPartSize, rect.bottom);
	}

	for (int i = 0; i < FieldSizeY + 1; i++)
	{
		dc.MoveTo(FIELDNUMBRERSSPACE,  i * vPartSize + FIELDNUMBRERSSPACE);
		dc.LineTo(rect.right, i * vPartSize + FIELDNUMBRERSSPACE);
	}

	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkMode(TRANSPARENT);

	char letter = 'A';
	for (int i = 0; i < FieldSizeX; i++)
	{
		CString str;
		str.Format(L"%c", letter);
		dc.TextOutW(FIELDNUMBRERSSPACE / 2 + hPartSize / 2 + i * hPartSize, 0, str);
		letter++;
	}

	for (int i = 0; i < FieldSizeY + 1; i++)
	{
		CString str;
		str.Format(L"%d", i);
		dc.TextOutW(0, FIELDNUMBRERSSPACE / 2 + FieldSizeY * vPartSize + vPartSize / 2 - i * vPartSize, str);
	}


	for (int x = 0; x < FieldSizeX; x++)
		for (int y = 0; y < FieldSizeY; y++)
		{
			if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_X)
				this->DrawX(dc, this->GetRectFromField(x, y));
			if (this->gameParent->GetBoard()->GetCell(x, y) == CellType_O)
				this->DrawO(dc, this->GetRectFromField(x, y));
		}


	dc.SelectObject(oldPen);
	ourPen.DeleteObject();

}


bool CUgolkiField::CheckEndCondition()
{
	if (this->gameParent->GetBoard()->CheckEndCondition())
	{
		if (this->gameParent->GetBoard()->IsVictory())
		{
			CString str;
			str.Format(L"Игрок %s победил!", this->gameParent->GetCurrentPlayer()->GetName());
			AfxMessageBox(str);
		}
		else
		{
			AfxMessageBox(L"Ничья!");
		}
		
		return true;
	}

	return false;
}


void CUgolkiField::GetFieldPosition(CPoint point, int& xpos, int& ypos)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return;

	CRect rect;
	GetClientRect(&rect);
	int hPartSize = (rect.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rect.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;
	for (int i = 0; i < FieldSizeX; i++)
	{
		if ((point.x > FIELDNUMBRERSSPACE + i * hPartSize) && (point.x < FIELDNUMBRERSSPACE + (i + 1) * hPartSize))
			xpos = i;
	}
	for (int i = 0; i < FieldSizeY; i++)
	{
		if ((point.y > FIELDNUMBRERSSPACE + i * vPartSize) && (point.y < FIELDNUMBRERSSPACE + (i + 1) * vPartSize))
			ypos = i;
	}
}


void CUgolkiField::OnDestroy()
{
	CWnd::OnDestroy();
	// TODO: добавьте свой код обработчика сообщений
}

CRect CUgolkiField::GetRectFromField(int x, int y)
{
	// TODO: Добавьте сюда код реализации.
	if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
		return CRect(0, 0, 0, 0);

	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - FIELDNUMBRERSSPACE) / FieldSizeX;
	int vPartSize = (rectWnd.bottom - FIELDNUMBRERSSPACE) / FieldSizeY;

	rect.left = FIELDNUMBRERSSPACE + x * hPartSize + 1;
	rect.top = FIELDNUMBRERSSPACE + y * vPartSize + 1;
	rect.right = FIELDNUMBRERSSPACE + ((x + 1) * hPartSize) - 1;
	rect.bottom = FIELDNUMBRERSSPACE + ((y + 1) * vPartSize) - 1;

	return rect;
}


void CUgolkiField::DrawX(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(245, 200, 220));
	HGDIOBJ oldbrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 3, rect.top + 3, rect.right - 3, rect.bottom - 3);

	dc.SelectObject(oldPen);
	pen.DeleteObject();
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}


void CUgolkiField::DrawO(CPaintDC& dc, CRect rect)
{
	// TODO: Добавьте сюда код реализации.
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(70, 100, 100));
	HGDIOBJ oldbrush = dc.SelectObject(brush);

	dc.Ellipse(rect.left + 3, rect.top + 3, rect.right - 3, rect.bottom - 3);

	dc.SelectObject(oldPen);
	pen.DeleteObject();
	dc.SelectObject(oldbrush);
	brush.DeleteObject();

}


void CUgolkiField::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	int x, y;

	GetFieldPosition(point, x, y);
	if ((nSelectedX != x) || (nSelectedY != y))
	{
		nSelectedX = x;
		nSelectedY = y;
		this->Invalidate();
	}

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;

	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
}


void CUgolkiField::HighlightSelection(CPaintDC& dc)
{
	// TODO: Добавьте сюда код реализации.
	if ((nSelectedX < 0) || (nSelectedY < 0))
		return;
	CRect rect = GetRectFromField(nSelectedX, nSelectedY);
	CBrush brush;
	brush.CreateSolidBrush(RGB(50, 252, 50));
	HGDIOBJ oldbrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
}


void CUgolkiField::OnMouseLeave()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	nSelectedX = -1;
	nSelectedY = -1;
	this->Invalidate();

	CWnd::OnMouseLeave();
}

void CUgolkiField::SetGameParent(CUgolkiDlg* p)
{
	this->gameParent = p;
}

void CUgolkiField::SetGameInProgress(bool InProgress)
{
	if (bGameInProgress != InProgress)
	{
		this->bGameInProgress = InProgress;
		this->gameParent->SetGameInProgress(InProgress);
		if (InProgress)
			SetTimer(TIMER_ID, 1000, NULL);
		else
			KillTimer(TIMER_ID);
	}
}

void CUgolkiField::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((bGameInProgress) && (!this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;

		if (this->gameParent->GetCurrentPlayer()->MakeMove(0, 0, 0, 0) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
		}
		this->Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}


void CUgolkiField::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((bGameInProgress) && (this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;
		this->GetFieldPosition(point, x, y);
		this->Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}



void CUgolkiField::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if ((bGameInProgress) && (this->gameParent->GetCurrentPlayer()->IsHuman()))
	{
		if ((this->gameParent == nullptr) || (this->gameParent->GetBoard() == nullptr))
			return;
		this->GetFieldPosition(point, x2, y2);

		if (this->gameParent->GetCurrentPlayer()->MakeMove(x, y, x2, y2) == true)
		{
			if (this->CheckEndCondition())
			{
				this->SetGameInProgress(false);
				this->gameParent->Invalidate();
			}
			else
			{
				this->gameParent->TogglePlayer();
			}
			x = 0;
			y = 0;
			x2 = 0;
			y2 = 0;
		}
		this->Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}
