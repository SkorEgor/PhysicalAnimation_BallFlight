using namespace std;


/*****************������� ���������*****************/
double Ax (double Vx, double Vy, double k, double m, double g) { return((-k * Vx * sqrt(Vx * Vx + Vy * Vy)) / m); }				//� ������� Ax, g �� ������������� �� ��� �������� ���������� ����, ������ ���� ��������, ����� ������� Ax � Ay ���� �����
double Ay (double Vx, double Vy, double k, double m, double g) { return(-g - (k * Vy * sqrt(Vx * Vx + Vy * Vy)) / m); }
/***************************************************/

/************������� ������ ����� �����*************/
//������� �������� k
double** Motion(double (*F_coord_x)(double, double, double, double, double), double (*F_coord_y)(double, double, double, double, double), double x, double y, double Vx, double Vy, double k, double m, double g, double dt)
{
	
	//cout << Vx << "\t" << Vy << "\t"<<x << "\t" << y << endl;
	/*********************************
	mass_k =  [ [kx1, kx2, kx3, kx4],
				[ky1, ky2, ky3, ky4] ]
	mass_k[����������][����� �-1],
	����������: 0 - x,1-y;
	*********************************/
	double** mass_k = new double* [4];
	for (int count = 0; count < 4; count++)
		mass_k[count] = new double[4];

	mass_k[0][0] = F_coord_x(Vx, Vy, k, m, g) * dt;												//kx1
	mass_k[1][0] = F_coord_y(Vx, Vy, k, m, g) * dt;												//ky1
	//cout << mass_k[0][0] << "\t" << mass_k[1][0] << endl;

	mass_k[0][1] = F_coord_x(Vx + mass_k[0][0] / 2.0, Vy + mass_k[1][0] / 2.0, k, m, g) * dt;		//ky2
	mass_k[1][1] = F_coord_y(Vx + mass_k[0][0] / 2.0, Vy + mass_k[1][0] / 2.0, k, m, g) * dt;		//ky2
	//cout << mass_k[0][1] << "\t" << mass_k[1][1] << endl;

	mass_k[0][2] = F_coord_x(Vx + mass_k[0][1] / 2.0, Vy + mass_k[1][1] / 2.0, k, m, g) * dt;		//kx3
	mass_k[1][2] = F_coord_y(Vx + mass_k[0][1] / 2.0, Vy + mass_k[1][1] / 2.0, k, m, g) * dt;		//ky3
	//cout << mass_k[0][2] << "\t" << mass_k[1][2] << endl;

	mass_k[0][3] = F_coord_x(Vx + mass_k[0][2], Vy + mass_k[1][2], k, m, g) * dt;				//kx4
	mass_k[1][3] = F_coord_y(Vx + mass_k[0][2], Vy + mass_k[1][2], k, m, g) * dt;				//ky4
	//cout << mass_k[0][3] << "\t" << mass_k[1][3] << endl;

	/****************************************************
	*speed_and__coord = [	[Vx, Vy],					*
	*						[x, y]		]				*
	*mass_k[��������(0)/����������(1)][�� x(0)/y(1)],	*
	****************************************************/
	double** speed_and__coord = new double* [2];
	for (int count = 0; count < 2; count++)	{ speed_and__coord[count] = new double[2];}

	speed_and__coord[0][0] = Vx + (mass_k[0][0] + 2 * mass_k[0][1] + 2 * mass_k[0][2] + mass_k[0][3]) / 6.0;//Vx
	speed_and__coord[0][1] = Vy + (mass_k[1][0] + 2 * mass_k[1][1] + 2 * mass_k[1][2] + mass_k[1][3]) / 6.0;//Vy
	//cout << speed_and__coord[0][0] << "\t" << speed_and__coord[0][1] <<"\t";

	speed_and__coord[1][0] = x + Vx * dt + (dt * (mass_k[0][0] + mass_k[0][1] + mass_k[0][2])) / 6.0;		//x
	speed_and__coord[1][1] = y + Vy * dt + (dt * (mass_k[1][0] + mass_k[1][1] + mass_k[1][2])) / 6.0;		//y
	//cout << speed_and__coord[1][0] << "\t" << speed_and__coord[1][1] << endl;
	return (speed_and__coord);
}
/***************************************************/

/**************************************************
������� �� ��������� ��������:
��� ������� �������� �� ����� ���������������� ������ ����� 300 ��/� (83,33�/�),
�� ������ ����� ������� ������� ��������� ������ � 414 ��/� (���������
��������). �� ������ ����� ���������� ��� ��� ������. ��� ������ 
���������� 326 ��/���, � ��� ������� ���� ������ ����������� �� 
270 ��/���. 
����� ������� ������������ �������� 80 �/�
������� �� ��������������� ����
����������� ��� ��� ����������������� ������ ������ 
������ �� ����� 45,93 � (0,04593 ��)
����� ������� �� ����� 42,67 �� (0,04267 �)
*/