#pragma once
// CUgolkiField
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"
#include "UgolkiComputerPlayer.h"
#include "UgolkiHumanPlayer.h"
#include "CUgolkiField.h"
#include "UgolkiDlg.h"
#include "pch.h"

class CUgolkiDlg;

class CUgolkiField : public CWnd
{
	DECLARE_DYNAMIC(CUgolkiField)

public:
	CUgolkiField();
	virtual ~CUgolkiField();

protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterClass();
public:
	afx_msg void OnPaint();
private:
	int FieldSizeX;
	int FieldSizeY;
	int x, y, x2, y2;
public:
private:
	void GetFieldPosition(CPoint point, int& xpos, int& ypos);
public:
	afx_msg void OnDestroy();
private:
	CRect GetRectFromField(int x, int y);
public:
	void DrawX(CPaintDC& dc, CRect rect);
private:
	void DrawO(CPaintDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	int nSelectedX;
	int nSelectedY;
	CUgolkiDlg* gameParent;
	bool bGameInProgress = false;
	void HighlightSelection(CPaintDC& dc);
	bool CheckEndCondition();
public:
	afx_msg void OnMouseLeave();
	void SetGameParent(CUgolkiDlg* p);
	void SetGameInProgress(bool InProgress);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};