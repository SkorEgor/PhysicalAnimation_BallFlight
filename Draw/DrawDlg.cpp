
// DrawDlg.cpp : файл реализации
#include "stdafx.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "afxdialogex.h"
#include <vector>
#include "Motion_functions.h"
#include <string>
#include <sstream>

/*******************Константы***********************/
#define G 9.81										//Ускорение свободного падения м/с^2
#define M 0.04593									//Масса мяча в кг
#define D 0.04267									//Диаметр мяча в м
#define R 0.021335									//Радиус мяча в м
#define Pi 3.1415926535897932						//Задаем мат. const число Пи
/***************************************************/

/*****************Начальные условия*****************/
double V0 = 70.0; double angle0 = (45 * Pi) / 180.0; double k = 0.00000001;
double X0 = 0.0; double Y0 = 0.0;
double deltaT = 0.3;
const int height_to_the_opening = 30;
const int opening_width = 20;
const int distance_to_the_wall = 100;
const int distance_to_the_hole = 210;
const int hole_size = 25;
/***************************************************/
//30, 10, 100, 230, 30);	//		int wall_height_in, int wall_holl_in, int distance_to_wall, int distance_to_hole, int hole_size)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAW_DIALOG, pParent)
	, List_box_Cstr_angel(_T(""))
	, Edit1_Cstr_angel(_T(""))
	, angeeeel(0)
	, int_in_angel(45)
	, Angel_in(45)
	, V0_in(70)
	, k_in(0)
	, k_in_double(0)
	, dT_in(0.3)
	, in_the_hole(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, out_angel);
	DDX_Text(pDX, IDC_EDIT1, int_in_angel);
	DDX_Text(pDX, IDC_EDIT2, str_out_angel);
	DDX_Control(pDX, IDC_EDIT3, Angeel_cedit);
	DDX_Text(pDX, IDC_EDIT3, Angel_in);
	DDX_Text(pDX, IDC_EDIT4, V0_in);
	DDX_Control(pDX, IDC_EDIT5, V0_out);
	DDX_Control(pDX, IDC_EDIT7, k_out);
	DDX_Text(pDX, IDC_EDIT6, k_in_double);
	DDX_Text(pDX, IDC_EDIT8, dT_in);
	DDX_Control(pDX, IDC_EDIT9, dT_out);
	DDX_Control(pDX, IDC_EDIT10, y_max_out);
	DDX_Check(pDX, IDC_CHECK1, in_the_hole);
	DDX_Control(pDX, IDC_EDIT11, control_game_out);
	DDX_Control(pDX, IDC_EDIT13, distance_to_the_wall_out);
	DDX_Control(pDX, IDC_EDIT14, distance_to_the_hole_out);
	DDX_Control(pDX, IDC_EDIT12, hole_size_out);
	DDX_Control(pDX, IDC_EDIT15, wall_fly_out);
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDrawDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_PICTURE, &CDrawDlg::OnStnClickedPicture)
	ON_EN_CHANGE(IDC_EDIT2, &CDrawDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CDrawDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CDrawDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CDrawDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT7, &CDrawDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT6, &CDrawDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT9, &CDrawDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CDrawDlg::OnEnChangeEdit10)
END_MESSAGE_MAP()

// обработчики сообщений CDrawDlg
BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	drv.Create(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//drv.Draw();
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawDlg::OnStnClickedPicture()
{
	// TODO: добавьте свой код обработчика уведомлений
}



/*Здесь код!!!)))))*/
void CDrawDlg::OnBnClickedOk()
{
	//UpdateData(TRUE);
	//angle0 = _wtof(Edit1_Cstr_angel);
	//height_to_the_opening, opening_width, distance_to_the_wall, distance_to_the_hole, hole_size);
	bool input_error = false;
	CString Pole;
	Pole.Format(_T("%d"), opening_width);
	control_game_out.SetWindowText(Pole);
	Pole.Format(_T("%d"), distance_to_the_wall);
	distance_to_the_wall_out.SetWindowText(Pole);
	Pole.Format(_T("%d"), distance_to_the_hole);
	distance_to_the_hole_out.SetWindowText(Pole);
	Pole.Format(_T("%d"), hole_size);
	hole_size_out.SetWindowText(Pole);

	/******Сохраняем входные данные угла*****/
	UpdateData(true);
	CString Angel_str;
	if (Angel_in >= 0 && Angel_in <= 90) {
		angle0 = ((double)Angel_in * Pi) / 180.0;
		Angel_str.Format(_T("%d"), Angel_in);
		out_angel.SetWindowText(Angel_str);
	}
	else
	{
		Angel_str="Error";
		out_angel.SetWindowText(Angel_str);
		input_error = true;
	}
	/****************************************/
	CString Vo_str;
	if (V0_in >= 0 && V0_in <= 70)
	{
		V0 = V0_in;
		Vo_str.Format(_T("%d"), V0_in);
		V0_out.SetWindowText(Vo_str);
	}
	else
	{
		Vo_str = "Error";
		V0_out.SetWindowText(Vo_str);
		input_error = true;
	}
	/****************************************/
	CString k_str;
	if (k_in_double >= 0.0 && k_in_double <= 1.0)
	{
		k = k_in_double;
		k_str.Format(_T("%f"), k_in_double);
		k_out.SetWindowText(k_str);
	}
	else
	{
		k_str = "Error";
		k_out.SetWindowText(k_str);
		input_error = true;
	}
	/****************************************/
	CString dT_str;
	if (k_in_double >= 0.0 && k_in_double <= 0.005)
	{
		deltaT = dT_in;
		dT_str.Format(_T("%f"), dT_in);
		dT_out.SetWindowText(dT_str);
	}
	else
	{
		dT_str = "Error";
		dT_out.SetWindowText(dT_str);
		input_error = true;
	}
	/****************************************/
	vector <double> speed_x = { V0 * cos(angle0) };
	vector <double> speed_y = { V0 * sin(angle0) };
	vector <double> coordinate_x = { X0 };
	vector <double> coordinate_y = { Y0 };
	vector <double> kin_energy = { (M * V0 * V0) / 2 };
	vector <double> pot_energy = { M * G * coordinate_y[0] };
	vector <double> time = { 0.0 };
	int i = 0;
	bool flying_wall = false;
	CString wall, holl;
	do{
		double** parametr_motion = Motion(Ax, Ay, coordinate_x[i], coordinate_y[i], speed_x[i], speed_y[i], k, M, G, deltaT);

		speed_x.push_back(**(parametr_motion));
		speed_y.push_back(*(*(parametr_motion)+1));
		
		coordinate_x.push_back(**(parametr_motion + 1));
		coordinate_y.push_back(*(*(parametr_motion + 1) + 1));
		if (coordinate_x[i + 1] >= distance_to_the_wall && !flying_wall && in_the_hole)
		{
			if (!(coordinate_y[i + 1] >= height_to_the_opening && coordinate_y[i + 1] <= height_to_the_opening + opening_width)) {
				wall = "Не пролет";
				speed_x[i + 1] = 0; speed_y[i + 1] = 0;
				wall_fly_out.SetWindowText(wall);
			}
			flying_wall = true;
		}
		double speed_general = sqrt(speed_x[i + 1] * speed_x[i + 1] + speed_y[i + 1] * speed_y[i + 1]);
		kin_energy.push_back((M * speed_general * speed_general) / 2);

		pot_energy.push_back(M * G * coordinate_y[i+1]);

		time.push_back(time[i] + deltaT);
		i++;
	} while (coordinate_y[i] > 0.0);
	if (coordinate_x[coordinate_x.size() - 1] >= distance_to_the_hole && coordinate_x[coordinate_x.size() - 1] <= distance_to_the_hole + hole_size && in_the_hole)
	{
		wall = "Долетел";
		wall_fly_out.SetWindowText(wall);
	}
	else {
		wall = "Не попал";
		wall_fly_out.SetWindowText(wall);
	}

	CDC* pDC = GetDC();
	pDC->MoveTo(10, 10);
	pDC->LineTo(20, 20);
	ReleaseDC(pDC);
	if (in_the_hole) {
		drv.Draw(coordinate_x, coordinate_y, 0, 520, 0, 270,
			time, speed_x, time, speed_y, 0, 15, -80, 80,
			time, kin_energy, pot_energy, M, G, 0, 15, 0, 150,
			height_to_the_opening, opening_width, distance_to_the_wall, distance_to_the_hole, hole_size);
	}
	else {
		drv.Draw(coordinate_x, coordinate_y, 0, 520, 0, 270,
			time, speed_x, time, speed_y, 0, 15, -90, 90,
			time, kin_energy, pot_energy, M, G, 0, 15, 0, 150,
			0, 270, distance_to_the_wall, distance_to_the_hole, 0);
	}

	//		int wall_height_in, int wall_holl_in, int distance_to_wall, int distance_to_hole, int hole_size)
	CString y_max;
	y_max.Format(_T("%f"), coordinate_x[coordinate_x.size()-1]);
	y_max_out.SetWindowText(y_max);

	UpdateData(FALSE);
}

void CDrawDlg::OnEnChangeEdit1()
{
	/*UpdateData(true);
	CString str = Edit1_Cstr_angel;
	angle0 = _tstof(str);

	str.Format(_T("%d"), angle0);
	out_angel.SetWindowText(str);*/
	CString text;
	Angeel_cedit.GetWindowText(text);
	out_angel.SetWindowText(text);
}


void CDrawDlg::OnBnClickedButton1() {
}


void CDrawDlg::OnEnChangeEdit2() {
	UpdateData(true);
}


void CDrawDlg::OnEnChangeEdit3() {
}


void CDrawDlg::OnEnChangeEdit4() {
}


void CDrawDlg::OnEnChangeEdit5() {
	UpdateData(true);
}


void CDrawDlg::OnEnChangeEdit7() {
	UpdateData(true);
}


void CDrawDlg::OnEnChangeEdit6() {
}


void CDrawDlg::OnEnChangeEdit9() {
	UpdateData(true);
}


void CDrawDlg::OnEnChangeEdit10() {
	UpdateData(true);
}


