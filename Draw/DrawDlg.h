
// DrawDlg.h : файл заголовка
//

#pragma once
#include "Drawer.h"
#include <iostream>
#include <sstream>
// диалоговое окно CDrawDlg
class CDrawDlg : public CDialogEx
{
// Создание
public:
	CDrawDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	Drawer drv;
	afx_msg void OnStnClickedPicture();
	CString List_box_Cstr_angel;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeEdit1();
	CString Edit1_Cstr_angel;
	afx_msg void OnBnClickedButton1();
	CString Angel_out_str;
	CEdit out_angel;
	afx_msg void OnEnChangeEdit2();
	double angeeeel;
	int int_in_angel;
	afx_msg void OnEnChangeEdit3();
	CString str_out_angel;
	CEdit Angeel_cedit;
	int Angel_in;
	int V0_in;
	afx_msg void OnEnChangeEdit4();
	CEdit V0_out;
	afx_msg void OnEnChangeEdit5();
	double k_in;
	CEdit k_out;
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit6();
	double k_in_double;
	double dT_in;
	CEdit dT_out;
	afx_msg void OnEnChangeEdit9();
	CEdit y_max_out;
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnBnClickedCheck1();
	BOOL in_the_hole;
	CEdit control_game_out;
	CEdit distance_to_the_wall_out;
	CEdit distance_to_the_hole_out;
	CEdit hole_size_out;
	CEdit wall_fly_out;
};
