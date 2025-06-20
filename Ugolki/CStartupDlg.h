#pragma once
#include "pch.h"
#include "UgolkiDlg.h"

// Диалоговое окно CStartupDlg

class CStartupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartupDlg)

public:
	CStartupDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CStartupDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CString strPlayerName1;
public:
	afx_msg void OnEnChangeEditnameplayer2();
private:
	CString strPlayerName2;
	CComboBox mTypePlayer1;
	CComboBox mTypePlayer2;

	CUgolkiDlg* dlgParent;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedStartbutton();
	void SetDlgParent(CUgolkiDlg* p);
};
