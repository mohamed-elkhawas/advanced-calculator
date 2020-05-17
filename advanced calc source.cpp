#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;

float solve(int n, float mat[50][50])
{
	float sum = 0, mat1[50][50];
	if (n == 2)
	{
		return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			for (int k = 0, kk = 0; k < n; kk++, k++)
			{
				if (k == i)
				{
					kk--;
					continue;
				}
				mat1[j][kk] = mat[j + 1][k];
			}
		}
		if (i % 2 == 0)
		{
			if (mat[0][i] != 0)
			{
				sum += mat[0][i] * solve(n - 1, mat1);
			}
		}
		else
		{
			if (mat[0][i] != 0)
			{
				sum -= mat[0][i] * solve(n - 1, mat1);
			}
		}
	}
	return sum;
}

float value(int num, int n, float var1[101][101])
{
	float mat[50][50];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == num)
			{
				mat[i][j] = -1 * var1[i][0];
			}
			else
			{
				mat[i][j] = var1[i][j + 1];
			}

		}
	}

	return  solve(n, mat);
}

int main()
{
	float  var1[100][101];
	int num = 0, n, e, ee = 0, p = 0, pp = 0, uu[100], a[100], aa = 0;
	char var_num = 0;
	string equ, equ1, x = "+-=,.1234567890", var[100], piece[200], piecex[200], nn;

	//intialization var1 =0
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			var1[i][j] = 0;
		}
	}

	//ÇÏÎÇá
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> equ;
		if (equ.substr(0, 1) == "-")
		{
			equ1 = equ;
		}
		else
		{
			equ1 = "+" + equ;
		}
		for (int j = 0; j < equ1.length(); j++)
		{
			if (equ1.substr(j, 1) == "=" && equ1.substr(j + 1, 1) != "-")
			{
				equ1 = equ1.substr(0, j + 1) + "+" + equ1.substr(j + 1, equ1.length() - j);
			}
		}
		for (int j = 0; j < equ1.length(); j++)
		{
			if (equ1.substr(j, 1) == "=")
			{
				e = j;
				equ = equ1.substr(0, j) + equ1.substr(j + 1, equ1.length() - j) + "=";
			}

		}
		for (int j = e; j < equ1.length(); j++)
		{
			if (equ.substr(j, 1) == "+")
			{
				equ1 = equ1.substr(0, j) + "-" + equ.substr(j + 1, equ.length() - j);
			}
			else if (equ.substr(j, 1) == "-")
			{
				equ1 = equ1.substr(0, j) + "+" + equ.substr(j + 1, equ.length() - j);

			}
		}
		for (int j = 0; j < 200; j++)
		{
			piecex[j] = "";
		}
		int u = 0;
		uu[i] = 0;
		for (int j = 1; j < equ1.length(); j++)
		{
			if (equ1.substr(j, 1) == "=" || equ1.substr(j, 1) == "-" || equ1.substr(j, 1) == "+")
			{
				piece[uu[i]] = equ1.substr(u, j - u);
				u = j;
				uu[i]++;
			}
		}
		for (int j = 0; j < uu[i]; j++)
		{
			for (int k = 0; k < piece[j].length(); k++)
			{
				int f = 0;
				for (int l = 0; l < 16; l++)
				{
					if (piece[j][k] == x[l])
					{
						f = 1;
						if (l == 0)
						{
							piecex[j] += "0";
						}
						else if (l == 1)
						{
							piecex[j] += "1";
						}
						else if (l == 2)
						{
							piecex[j] += "2";
						}
						else
						{
							piecex[j] += "3";
						}
					}
				}
				if (f == 0)
				{
					piecex[j] += "4";
				}
			}
		}
		for (int jj = 0; jj < uu[i]; jj++)
		{
			for (int k = 0; k < piece[jj].length(); k++)
			{
				if (piecex[jj].substr(k, 1) == "4")
				{

					if (num > 0)
					{
						int flag = 0;
						for (int iii = 0; iii < num; iii++)
						{
							if (piece[jj].substr(k) == var[iii])
							{
								flag = 1;
							}
						}
						if (flag == 0)
						{
							var[num] = piece[jj].substr(k);
							num++;
						}
					}

					else
					{
						var[num] = piece[jj].substr(k);
						num++;
					}

					break;
				}

			}
		}
		for (int jj = 0; jj < uu[i]; jj++)
		{
			int flag = 0;
			for (int k = 0; k < piece[jj].length(); k++)
			{
				if (flag == 0)
				{
					if (piecex[jj].substr(k, 1) == "4")
					{
						flag = 1;
						for (int iii = 0; iii < num; iii++)
						{
							if (piece[jj].substr(k) == var[iii])
							{
								var1[i][iii + 1] += atof(piece[jj].c_str());
								if (atof(piece[jj].substr(0, k).c_str()) == 0 && piece[jj].substr(0, 1) == "+")
								{
									var1[i][iii + 1] += 1;
								}
								if (atof(piece[jj].substr(0, k).c_str()) == 0 && piece[jj].substr(0, 1) == "-")
								{
									var1[i][iii + 1] -= 1;
								}
							}
						}
					}
				}
			}
			if (flag == 0)
			{
				var1[i][0] += atof(piece[jj].c_str());
			}
		}
	}

	//äÑÊíÈ ÇáãÊÛíÑÇÊ

	for (int j = 0; j < num; j++)
	{
		for (int i = 1; i < num; i++)
		{
			if (var[i] < var[i - 1])
			{
				string vari;
				vari = var[i];
				var[i] = var[i - 1];
				var[i - 1] = vari;
				for (int k = 0; k < n; k++)
				{
					float varr;
					varr = var1[k][i + 1];
					var1[k][i + 1] = var1[k][i];
					var1[k][i] = varr;
				}
			}
		}
	}


	while (true)
	{
		getline(cin, nn);
		if (nn == "quit")
		{
			break;
		}
		else if (nn.substr(0, 9) == "num_vars")
		{
			cout << num << endl;
		}
		else if (nn.substr(0, 8) == "equation")
		{
			int i = atoi(nn.substr(9).c_str()) - 1;
			int m;
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[i][j] > 0 != 0)
				{
					m = j;
					break;
				}
			}
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[i][j] > 0 && j <= m)
				{
					cout << var1[i][j] << var[j - 1];
				}
				if (var1[i][j] > 0 && j >m)
				{
					cout << "+" << var1[i][j] << var[j - 1];
				}
				if (var1[i][j] < 0)
				{
					cout << var1[i][j] << var[j - 1];
				}
			}
			if (var1[i][0] == 0)
			{
				cout << "=" << var1[i][0] << endl;
			}
			else
			{
				cout << "=" << -var1[i][0] << endl;
			}
		}
		else if (nn.substr(0, 6) == "column")
		{
			int i = 0;
			for (int j = 0; j < num; j++)
			{

				if (nn.substr(7) == var[j])
				{
					i = j;
				}
			}
			for (int j = 0; j < n; j++)
			{
				cout << var1[j][i + 1] << endl;
			}
		}
		else if (nn.substr(0, 3) == "add")
		{
			int k = atoi(nn.substr(4).c_str()) - 1, l;
			if (k<9)
			{
				l = atoi(nn.substr(6).c_str()) - 1;
			}
			if (k<99 && k>8)
			{
				l = atoi(nn.substr(7).c_str()) - 1;
			}
			if (k == 99)
			{
				l = atoi(nn.substr(8).c_str()) - 1;
			}
			int m;
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[k][j] + var1[l][j]> 0 != 0)
				{
					m = j;
					break;
				}
			}
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[k][j] + var1[l][j] > 0 && j <= m)
				{
					cout << (var1[k][j] + var1[l][j]) << var[j - 1];
				}
				if (var1[k][j] + var1[l][j] > 0 && j >m)
				{
					cout << "+" << var1[k][j] + var1[l][j] << var[j - 1];
				}
				if (var1[k][j] + var1[l][j] < 0)
				{
					cout << (var1[k][j] + var1[l][j]) << var[j - 1];
				}
			}
			if (var1[k][0] + var1[l][0] == 0)
			{
				cout << "=" << (var1[k][0] + var1[l][0]) << endl;
			}
			else
			{
				cout << "=" << -(var1[k][0] + var1[l][0]) << endl;
			}
		}
		else if (nn.substr(0, 8) == "subtract")
		{
			int k = atoi(nn.substr(9).c_str()) - 1, l;
			if (k<9)
			{
				l = atoi(nn.substr(11).c_str()) - 1;
			}
			if (k<99 && k>8)
			{
				l = atoi(nn.substr(12).c_str()) - 1;
			}
			if (k == 99)
			{
				l = atoi(nn.substr(13).c_str()) - 1;
			}
			int m;
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[k][j] - var1[l][j] != 0)
				{
					m = j;
					break;
				}
			}
			for (int j = 1; j < num + 1; j++)
			{
				if (var1[k][j] - var1[l][j] > 0 && j <= m)
				{
					cout << var1[k][j] - var1[l][j] << var[j - 1];
				}
				if (var1[k][j] - var1[l][j] > 0 && j >m)
				{
					cout << "+" << var1[k][j] - var1[l][j] << var[j - 1];
				}
				if (var1[k][j] - var1[l][j] < 0)
				{
					cout << var1[k][j] - var1[l][j] << var[j - 1];
				}
			}
			cout << "=" << (-var1[k][0] + var1[l][0]) << endl;
		}
		else if (nn.substr(0, 10) == "substitute")
		{
			string m;
			for (int i = 11; i < nn.length(); i++)
			{
				if (nn.substr(i, 1) == " ")
				{
					m = nn.substr(11, i - 13);
				}
			}
			if (m.substr(m.length() - 1, 1) == " ")
			{
				m = m.substr(0, m.length() - 1);
			}
			int kk = 0, k = atoi(nn.substr(m.length() + 11).c_str()) - 1, l;

			if (k<9)
			{
				l = atof(nn.substr(m.length() + 13).c_str());
			}
			if (k<99 && k>8)
			{
				l = atof(nn.substr(m.length() + 14).c_str());
			}
			if (k == 99)
			{
				l = atof(nn.substr(m.length() + 15).c_str());
			}

			for (int i = 0; i < num; i++)
			{
				if (var[i] == m)
				{
					kk = i;
				}
			}
			int mm = 1;
			for (int j = 1; j < num + 1; j++)
			{
				if (j == kk + 1)
				{
					continue;
				}
				if (var1[k][j] != 0)
				{
					mm = j;
					break;
				}
			}
			for (int j = 1; j < num + 1; j++)
			{
				if (j - 1 == kk)
				{
					continue;
				}
				if (var1[k][j] > 0 && j <= mm)
				{
					cout << var1[k][j] << var[j - 1];
				}
				if (var1[k][j] > 0 && j >mm)
				{
					cout << "+" << var1[k][j] << var[j - 1];
				}
				if (var1[k][j] < 0)
				{
					cout << var1[k][j] << var[j - 1];
				}
			}
			if (var1[k][0] + (l*var1[k][kk + 1]) == 0)
			{
				cout << "=" << (var1[k][0] + (l*var1[k][kk + 1])) << endl;
			}
			else
			{
				cout << "=" << -(var1[k][0] + (l*var1[k][kk + 1])) << endl;
			}
		}
		else if (nn.substr(0, 1) == "D"&&nn.length() == 1)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 1; j < num + 1; j++)
				{
					if (j>1 && j<num + 1)
					{
						cout << "	";
					}
					cout << var1[i][j];
				}
				cout << endl;
			}

		}
		else if (nn.substr(0, 2) == "D ")
		{
			int k;
			for (int i = 0; i<num; i++)
			{
				if (nn.substr(2) == var[i])
				{
					k = i;
				}
			}
			for (int i = 0; i<num; i++)
			{
				for (int j = 1; j < num + 1; j++)
				{
					if (j != k + 1)
					{
						if (j > 1)
						{
							cout << "	";
						}
						cout << var1[i][j];
					}
					else
					{
						if (j > 1)
						{
							cout << "	";
						}
						if (var1[i][0] == 0)
						{
							cout << var1[i][0];
						}
						else
						{
							cout << -var1[i][0];
						}
					}
				}
				cout << endl;
			}
		}
		else if (nn.substr(0, 8) == "D_value")
		{
			if (n == num)
			{
				cout << value(num, n, var1) << endl;
			}

		}
		else if (nn.substr(0, 6) == "solve")
		{
			if (n != num || value(num, n, var1) == 0)
			{
				cout << "No Solution" << endl;
			}

			else
			{
				if (n == 1)
				{
					cout << var[0] << "=" << (-1)*var1[0][0] / var1[0][1] << endl;
					continue;
				}
				else
				{
					float D_value = value(num, n, var1);
					for (int i = 0; i < num; i++)
					{
						cout << var[i] << "=" << value(i, n, var1) / D_value << endl;
					}

				}
			}
		}

	}

	return 0;
}
