// UgolkiDlg.h: файл заголовка
//
#pragma once
#include "pch.h"
#include "UgolkiBoard.h"
#include "UgolkiPlayer.h"
#include "UgolkiComputerPlayer.h"
#include "UgolkiHumanPlayer.h"
#include "CUgolkiField.h"
class CUgolkiField;

// Диалоговое окно CUgolkiDlg
class CUgolkiDlg : public CDialogEx
{
// Создание
public:
	CUgolkiDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTFOUR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;
	CUgolkiField Field;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void CreateBoard();
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);

	UgolkiBoard* GetBoard();
	UgolkiPlayer* GetCurrentPlayer();

private:
	UgolkiBoard* board;
	UgolkiPlayer* player1;
	UgolkiPlayer* player2;
	UgolkiPlayer* currentPlayer;
	bool bGameInProgress = false;

	void Cleanup();
	void UpdateName();
public:
	afx_msg void OnDestroy();
	void SetGameInProgress(bool InProgress);
	CButton mStartStopButton;
	CString strPlayerTurn;

	void TogglePlayer();
//	afx_msg void OnStnClickedStatic1();
};
