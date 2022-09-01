
![C++](https://img.shields.io/badge/-C++-090909?style=for-the-badge&logo=C%2b%2b&logoColor=6296CC) ![MFC](https://img.shields.io/badge/-MFC-090909?style=for-the-badge) ![MFC](https://img.shields.io/badge/-Window_App-090909?style=for-the-badge)

<h3 align="center">PhysicalAnimatio_BallFlight</h3>
<p align="center">
Отрисовка графиков в Picture Control MFC
</p>


<details>
  <summary>Содержание</summary>
  <ol>
    <li><a href="#О-проекте">О проекте</a></li>
    <li><a href="#Демонстрация">Демонстрация</a></li>
    <li><a href="#Установка">Установка</a></li>
    <li><a href="#Описание-класса-Drawer">Описание класса Drawer</a></li>
    <li><a href="#Особенности-проекта">Особенности проекта</a></li>
  </ol>
</details>


## О проекте
Проект моделирует полет маленького мяча через отверстие в стене так, чтобы он попал в лунку, учитывая сопротивление воздуха с силой, зависящее от скорости в квадрате. Расчет траектории возможен только численными методами.
![me](https://github.com/Daisyliu6/Daisyliu6/blob/master/me.gif)
<div align="center">

![me](https://i.gifer.com/embedded/download/W3Za.gif)
<div align="center">

![Demo](https://github.com/SkorEgor/PhysicalAnimation_BallFlight/blob/writingREADME/Pictures/bandicam%202022-07-18%2015-54-09-616%20(1).gif)
</div>

## Демонстрация
Для использования программы достаточно скачать [“Draw.exe”](https://github.com/SkorEgor/PhysicalAnimation_BallFlight/tree/writingREADME/x64/Debug) - файл програмы и запустить.
Пример работы можно посмотреть на [“YouTube”](https://youtu.be/GeE4p0rey5c)

## Интерфейс
<div align="center">

![interface](https://github.com/SkorEgor/PhysicalAnimation_BallFlight/blob/writingREADME/Pictures/4.1.Общая%20структура%20для%20git.jpg)
</div>


<div align="center">

![Application window](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/9.ExampleWin.png)
</div>



## Установка
1.	Разместите на окне элемент «Picture Control»

<div align="center">

![1.PictureControl.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/1.PictureControl.png)
</div>

2.	Измените “ID” элемента со статичного (Я дал “IDC_GRAPH”)

<div align="center">

![2.ID.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/2.ID.png)
</div>

3.	Кликаем правой кнопкой по «Picture Control», добавляем переменную, дав имя (Я дал “graphPicture”-элемент управления «Picture Control»)

<div align="center">

![3.AddVar.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/3.AddVar.png)
</div>

4.	В папку с проектом добавляем файл «Drawer.h», а также в сам проект

<div align="center">

![4.AddDrawer.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/4.AddDrawer.png)
</div>

5.	Подготовка к отрисовке<br />
a.	Открываем заголовочный файл проекта “…Dlg.h”. В моем случае “GraphDrawingDlg.h” 
<br /><p align="center">![5.OpenHeader.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/5.OpenHeader.png)</p>
b.	Подключаем класс в коде, прописывая `#include “Drawer.h`<br />
c.	В поле protected добавляем объект класса “Drawer”. Пример `Drawer drv;`
<br /><p align="center">![6.EditHeader.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/6.EditHeader.png)</p>
6.	«Проинициализируем» объект класса Drawer в функции создания окна. Открываем аналогичный Header файлу cpp файл. В моем случае «GraphDrawingDlg.cpp». Находим функцию «OnInitDialog» и вызываем в ней метод “Creat” для объекта класса «Drawer» и передаем HWND «Picture Control»
```C
drv.Create(GetDlgItem(IDC_GRAPH)->GetSafeHwnd());
```
<br /><p align="center">![7.OnInit.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/7.OnInit.png)</p>

---

Дальше можно пользоваться, вызывать метод Draw для отрисовки с заданными параметрами.

---

Для примера работы, добавим в этот проект кнопку и обработчик нажатия на неё. Напишем небольшой код.
1.	Создадим 2 вектора (предварительно подключив класс vector)
```C
vector <double> x, y;
```
2.	Заполним их значениями
```C
int numberFunctionPoints = 20;
for (int i = 0; i < numberFunctionPoints; i++) {
	x.push_back(i);
	y.push_back(i * 2);
}
```
3.	Передадим их в drv (объект класса Drawer)
```C
drv.Draw(
	y, y[0], y[y.size() - 1],
	x, x[0], x[x.size() - 1],
	'R'
);
```
В итоге должно получится также:
<div align="center">

![8.Example.png](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/8.Example.png)
</div>

## Описание класса [Drawer](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/GraphDrawing/Drawer.h)
1.	Для использования объекта класса, необходимо связать объект класса с Picture Control, для отображения, по средством метода ` void Create(HWND hWnd)`
2.	Для рисования вызывается метод Draw
<br />Параметры:
```C
vector<double>& data	- вектор значений по оси Y
double min_data		- min значение по Y
double max_data		- max значение по Y
vector<double>& keys	- вектор значений по оси Y 
double min_keys		- min значение по X
double max_keys		- max значение по X
char color		- символ цвета графика ('R' – красный; 'G'-зеленый)
```
Переменные для рисования (ручки, их цвета и жирность)
```C
CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
CPen data_pen2(PS_SOLID, 2, RGB(38, 0, 255));
CPen pen_red(PS_SOLID, 2, RGB(178, 34, 34));
CPen pen_green(PS_SOLID, 2, RGB(0, 128, 0));
CFont font;
font.CreateFontW(18, 0, 0, 0,
	FW_DONTCARE,
	FALSE,				// Курсив
	FALSE,				// Подчеркнутый
	FALSE,				// Перечеркнутый		DEFAULT_CHARSET,	// Набор символов
	OUT_OUTLINE_PRECIS,	// Точность соответствия.	
	CLIP_DEFAULT_PRECIS,//  
	CLEARTYPE_QUALITY,	// Качество
	VARIABLE_PITCH,		//
	TEXT("Times New Roman")		//
);
```
Получаем размеры окна, задаем отступы и получаем реальную область рисования, её ширину и высоту.
```C
int padding = 20;
int left_keys_padding = 20;
int bottom_keys_padding = 10;

int actual_width = frame.Width() - 2 * padding - left_keys_padding;
int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

int actual_top = padding;
int actual_bottom = actual_top + actual_height;
int actual_left = padding + left_keys_padding;
int actual_right = actual_left + actual_width;
```
Рисование сетки
```C
unsigned int grid_size = 10;

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
```
Выбираем цвета, запоминаем крайние значения конвертируем значения по осям из реальных значений в координаты окна
```C
if (color == 'R')memDC.SelectObject(&pen_red);
else if (color == 'G')memDC.SelectObject(&pen_green);
else memDC.SelectObject(&data_pen);

double data_y_max(max_data), data_y_min(min_data);
double data_x_max(max_keys), data_x_min(min_keys);

vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);

memDC.MoveTo(x[0], y[0]);
for (unsigned int i = 0; i < y.size(); i++)
{
	memDC.LineTo(x[i], y[i]);
}
```
Подписываем оси и выводим буфер на картинку
```C
memDC.SelectObject(&font);
memDC.SetTextColor(RGB(0, 0, 0));
for (int i = 0; i < grid_size / 2 + 1; i++)
{
	CString str;
	str.Format(L"%.1f", data_x_min + i * (data_x_max - data_x_min) / (grid_size / 2));
	memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);

	str.Format(L"%.1f", data_y_min + i * (data_y_max - data_y_min) / (grid_size / 2));
	memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
}

dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
```

## Особенности проекта
Специфичные оси координат окна
<br /><p align="center">![Axes](https://github.com/SkorEgor/GraphDrawing/blob/writingREADME/Картинки/axes.jpg)</p>
Предварительная отрисовка в буфер 
