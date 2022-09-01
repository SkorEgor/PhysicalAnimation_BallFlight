#pragma once

#include <afxwin.h>
#include <vector>

using namespace std;

class Drawer
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, области рисования.
	CWnd * wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC * dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		init = true;
	}

	// Нарисовать график по переданным данным.
	void Draw(vector<double>& keys, vector<double>& data, double data_x_min, double data_x_max, double data_y_min, double data_y_max,
		vector<double>& keysx, vector<double>& datax, vector<double>& keysy, vector<double>& datay, double data_x_min1, double data_x_max1, double data_y_min1, double data_y_max1,
		vector<double>& keysT, vector<double>& kinetic_energy, vector<double>& pot_ener, double mass, double g, double data_T_min, double data_T_max, double data_V_min, double data_V_max,
		int wall_height_in, int wall_holl_in, int distance_to_wall, int distance_to_hole, int hole_size)
	{
		//time, speed_V, M, G, 0, 15, -50, 50);
		if (!init) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen subgrid_pen_red (PS_DOT, 1, RGB(200, 0, 0));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data_pen_n(PS_SOLID, 2, RGB(0, 0, 255));
		CPen data_pen_gren(PS_SOLID, 2, RGB(0, 255, 0));
		CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = (frame.Width() - 3 * padding - 2*left_keys_padding)/2;
		int actual_height = (frame.Height() - 2 * padding - bottom_keys_padding);

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;
		
		// Белый фон.
		memDC.FillSolidRect(frame, RGB(255,255,255));

		// Рисуем сетку и подсетку.
		unsigned int grid_size = 10;

		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i+=1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left,   actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size+1; i+=1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}
	
		//рисуем припятсвия
		//Нижняя стена
		CBrush pen_wall(RGB(177, 81, 36));

		int wall_width = 5;
		int wall_height = actual_height;
		int wall_height_down =  wall_height_in* ((actual_bottom - actual_top)/( data_y_max - data_y_min));
		int wall_height_holes = wall_holl_in * ((actual_bottom - actual_top) / (data_y_max - data_y_min));

		int right1 = padding + left_keys_padding + distance_to_wall * ((actual_right - actual_left) / (data_x_max - data_x_min));
		int bottom1 = actual_bottom;
		int left1 = right1 - wall_width;
		int top1 = actual_bottom - wall_height_down;// wall_height;
		memDC.SelectObject(pen_wall);
		memDC.Rectangle(left1, top1, right1, bottom1);

		//Верхняя стена
		int bottom2 = actual_bottom - wall_height_down - wall_height_holes;
		int top2 = actual_top;
		 
		memDC.SelectObject(pen_wall);
		memDC.Rectangle(left1, top2, right1, bottom2);

		//Левая земля
		CBrush pen_ground(RGB(52, 201, 36));

		int wall_height_left = 5;
		int wall_width_left = distance_to_hole * ((actual_right - actual_left) / (data_x_max - data_x_min));
		int wall_width_holes = hole_size * ((actual_right - actual_left) / (data_x_max - data_x_min));

		int left_left_ground = padding + left_keys_padding;
		int right_left_ground = left_left_ground + wall_width_left;
		int bottom_left_ground = actual_bottom;
		int top_left_ground = actual_bottom + wall_height_left;// wall_height;

		memDC.SelectObject(pen_ground);
		memDC.Rectangle(left_left_ground, top_left_ground, right_left_ground, bottom_left_ground);

		//Правая земля
		int left_right_ground = right_left_ground + wall_width_holes;
		int right_right_ground = actual_width;

		memDC.SelectObject(pen_ground);
		memDC.Rectangle(left_right_ground, top_left_ground, actual_right, bottom_left_ground);
		//отрисовали объекты


		// Рисуем график.
		if (data.empty()) return;

		if (keys.size() != data.size())
		{
			keys.resize(data.size());
			for (int i = 0; i < keys.size(); i++)
			{
				keys[i] = i;
			}
		}

		memDC.SelectObject(&data_pen);



		vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
		vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);

		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.SelectObject(&subgrid_pen_red);
			memDC.LineTo(x[i], y[i]);
		}

		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size + 1; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i*(data_x_max - data_x_min) /grid_size);
			if (i == grid_size) { str = "\n X, M"; }
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size) - bottom_keys_padding, actual_bottom + bottom_keys_padding, str);

			str.Format(L"%.1f", data_y_min + i*(data_y_max - data_y_min) / (grid_size));
			if (i == grid_size) { str = "\n Y, M"; }
			memDC.TextOutW(actual_left - 1.5*left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size) - bottom_keys_padding, str);
		}
		/***********************************************************************/
		padding = 20;

		actual_width = (frame.Width() - 3 * padding - 2 * left_keys_padding) / 2;
		actual_height = (frame.Height() - 3 * padding - 2 * bottom_keys_padding) / 2;

		actual_top = padding;
		actual_bottom = actual_top + actual_height;
		actual_left = actual_left + actual_width + padding + left_keys_padding;
		actual_right = actual_left + actual_width;

		unsigned int grid_size1 = 10;
		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}
		//
		// Рисуем график.
		if (datax.empty()) return;
		if (keysx.size() != datax.size()) {
			keysx.resize(datax.size());
			for (int i = 0; i < keysx.size(); i++) {
				keysx[i] = i;
			}
		}
		if (datay.empty()) return;
		if (keysy.size() != datay.size()) {
			keysy.resize(datay.size());
			for (int i = 0; i < keysy.size(); i++) {
				keysy[i] = i;
			}
		}
		vector<double> overall_speed_in;
		for (int i = 0; i < datax.size(); i++) {
			overall_speed_in.push_back(sqrt(datax[i] * datax[i] + datay[i] * datay[i]));;
		}
		vector<double> overall_speed_out = convert_range(overall_speed_in, actual_top, actual_bottom, data_y_max1, data_y_min1);
		vector<double> yx = convert_range(datax, actual_top, actual_bottom, data_y_max1, data_y_min1);
		vector<double> xx = convert_range(keysx, actual_right, actual_left, data_x_max1, data_x_min1);
		vector<double> yy = convert_range(datay, actual_top, actual_bottom, data_y_max1, data_y_min1);
		vector<double> xy = convert_range(keysy, actual_right, actual_left, data_x_max1, data_x_min1);

		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size + 1; i++)
		{
			CString str1;
			str1.Format(L"%.1f", data_x_min1 + i * (data_x_max1 - data_x_min1) / (grid_size ));
			if (i == grid_size) { str1 = "\n t,c"; }
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size) - bottom_keys_padding, actual_bottom + bottom_keys_padding, str1);

			str1.Format(L"%.1f", data_y_min1 + i * (data_y_max1 - data_y_min1) / (grid_size));
			if (i == grid_size) { str1 = "\n V,m/c"; }
			memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size) - bottom_keys_padding, str1);
		}
		/***********************************************************************/
		padding = 20;

		actual_width = (frame.Width() - 3 * padding - 2 * left_keys_padding) / 2;
		actual_height = (frame.Height() - 3 * padding - 2 * bottom_keys_padding) / 2;

		actual_bottom = frame.Height() - bottom_keys_padding - padding;
		actual_top = actual_bottom - actual_height;
		actual_right = frame.Width() - padding ;
		actual_left = actual_right - actual_width;

		unsigned int grid_size2 = 10;
		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		vector<double> potentional_energy = convert_range(pot_ener, actual_top, actual_bottom, data_V_max, data_V_min);

		vector<double> kinet_energy = convert_range(kinetic_energy, actual_top, actual_bottom, data_V_max, data_V_min);
		vector<double> T = convert_range(keysT, actual_right, actual_left, data_T_max, data_T_min);

		vector<double> mex_enr;
		for (int i = 0; i < pot_ener.size(); i++) { mex_enr.push_back(pot_ener[i] + kinetic_energy[i]); }
		vector<double> mex_enrgy = convert_range(mex_enr, actual_top, actual_bottom, data_V_max, data_V_min);;
		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size + 1; i++)
		{
			CString str2;
			str2.Format(L"%.1f", data_T_min + i * (data_T_max - data_T_min) / (grid_size));
			if (i == grid_size) { str2 = "t,c"; }
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size) - bottom_keys_padding, actual_bottom + bottom_keys_padding, str2);

			str2.Format(L"%.1f", data_V_min + i * (data_V_max - data_V_min) / (grid_size));
			if (i == grid_size) { str2 = "E,Дж"; }
			memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size) - bottom_keys_padding, str2);
		}
		/***********************************************************************/

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);

		CBrush bred(RGB(255, 0, 0));
		CBrush bred_w(RGB(0, 0, 0));
		double Radius = 20;
		
		for (unsigned int i = 1; i < y.size(); i++)
		{
			memDC.SelectObject(&data_pen);
			memDC.MoveTo(xx[i-1], yx[i-1]);
			memDC.LineTo(xx[i], yx[i]);

			memDC.SelectObject(&data_pen_n);
			memDC.MoveTo(xy[i - 1], yy[i - 1]);
			memDC.LineTo(xy[i], yy[i]);

			memDC.SelectObject(&data_pen_gren);
			memDC.MoveTo(xy[i - 1], overall_speed_out[i - 1]);
			memDC.LineTo(xy[i], overall_speed_out[i]);

			memDC.SelectObject(&data_pen);
			memDC.MoveTo(T[i], kinet_energy[i]);
			memDC.LineTo(T[i - 1], kinet_energy[i - 1]);

			memDC.SelectObject(&data_pen_n);
			memDC.MoveTo(T[i], potentional_energy[i]);
			memDC.LineTo(T[i - 1], potentional_energy[i-1]);

			memDC.SelectObject(&data_pen_gren);
			memDC.MoveTo(T[i], mex_enrgy[i]);
			memDC.LineTo(T[i - 1], mex_enrgy[i - 1]);

			dc->SelectObject(bred);
			dc->Ellipse(x[i] - Radius, y[i] + Radius, x[i] + Radius, y[i] - Radius);
			Sleep(40);
			dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
		}

	}

	vector<double> convert_range(vector <double> & data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto & item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
};