#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> 
#include <Windows.h> 
#include <iomanip>

using namespace std;

ifstream base("D:\\base.txt");

struct baza
{
	string login;
	string pass;
}user[100];
struct grupa
{
	string number;
	string name;
}gruup[100];
int i = 0, m;

void qs(int left, int right);

void obnov()
{
	ifstream base("D:\\base.txt");
	while (!base.eof())
	{
		base >> user[i].login;
		base >> user[i].pass;
		i++;
		m = i;
	}
}
void vivodqs()
{
	obnov();
	qs(0, i - 1);
	for (int i = 0; i < m; i++)
		cout << i << ". " << user[i].login << " " << user[i].pass << endl;
}
void qs(int left, int right)
{
	string pivot;
	int k;
	int l_hold = left;
	int r_hold = right;
	pivot = user[left].login;
	user[i + 1] = user[left];
	while (left < right)
	{
		while ((user[right].login >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			user[left] = user[right];
			left++;
		}
		while ((user[left].login <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			user[right] = user[left];
			right--;
		}
	}
	user[left] = user[i + 1];
	k = left;
	left = l_hold;
	right = r_hold;
	if (left < k)
		qs(left, k - 1);
	if (right > k)
		qs(k + 1, right);
}
void vivod()
{
	obnov();
	for (int i = 0; i < m; i++)
		cout << i << ". " << user[i].login << " " << user[i].pass << endl;
}
void vivodNaEkran1()
{
	ifstream fin("D:\\gruup.txt");
	int schetchik = 0;
	do {
		fin >> gruup[schetchik].number >> gruup[schetchik].name;
		schetchik++;
	} while (fin.good());
	cout << setw(15) << "Номер" << setw(17) << "Название_команды" << endl;  
	for (int i = 0; i < m; i++)
		cout << setw(15) << gruup[i].number << setw(17) << gruup[i].name << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	string ulogin, uparol;
	int pet = 0, u, o;
	char c = '-';
	obnov();
	while (pet == 0)
	{
		cout << "Введите логин: " << endl;
		cin >> ulogin;
		for (int i = 0; i < m; i++)
		{
			if (ulogin == user[i].login)
			{
				u = i;
				pet++;
				break;
			}
		}
		if (pet > 0)
			break;
		else
		{
			system("cls");
			cout << "Логин не найден" << endl;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		cout << "Введите пароль: " << endl;
		cin >> uparol;
		if (uparol == user[u].pass)
		{
			cout << "Аутенфикация прошла успешно!" << endl;
			system("cls");
			break;
		}
		else
		{
			system("cls");
			cout << "Пароль не верный, у вас осталось " << 3 - i - 1 << " попыток " << endl;
		}
	}
	if (i == 2)
	{
		cout << "Попытка взлома!!! -_- ";
		system("pause");
		exit(0);
	}
	while (c != '+')
	{
		if (u == 0)
		{
			cout << "Вы авторизовались как администратор" << endl;
			cout << "Список доступных команд:" << endl << endl << " (1) Вывод списка пользователей" << endl << " (2) Вывод списка пользователей с сортировкой" << endl;
			cout << " (3) Изменить пароль пользователя" << endl << " (4) Добавить пользователя" << endl << " (5) Вывод списка групп" << endl;
			cout << " (6) Добавление новой группы" << endl << " (+) Выход из программы" << endl;
			cin >> o;
			switch (o)
			{
			case 1:
			{
				system("cls");
				vivod();
				system("pause");
				break;
			}
			case 2:
			{
				system("cls");
				vivodqs();
				system("pause");
				break;
			}
			case 3:
			{
				int nom;
				string s;
				system("cls");
				cout << "Введите номер пользователя" << endl;
				cin >> nom;
				cout << "Введите новый пароль" << endl;
				cin >> s;
				user[nom].pass = s;
				cout << "Пароль изменен успешно!" << endl;
				ofstream baze("d:\\base.txt", ios::trunc);
				for (int i = 0; i < m; i++)
				{
					baze << user[i].login << " " << user[i].pass << endl;
				}
				baze.close();
				system("pause");
				break;
			}
			case 4:
			{
				string s, s1;
				system("cls");
				ofstream baze("d:\\base.txt", ios::app);
				cout << "Введите логин" << endl;
				cin >> s;
				baze << s;
				m++;
				user[m].login = s;
				cout << "Введите пароль" << endl;
				cin >> s1;
				baze << " " << s1 << endl;
				user[m].pass = s1;
				baze.close();
				system("pause");
			}
			case 5:
			{
				system("cls");
				vivodNaEkran1();
				system("pause");
				break;
			}
			case 6:
			{
				string s, s1;
				system("cls");
				ofstream baze("d:\\gruup.txt", ios::app);
				cout << "Введите номер группы" << endl;
				cin >> s;
				baze << s;
				m++;
				gruup[m].number = s;
				cout << "Введите название группы" << endl;
				cin >> s1;
				baze << " " << s1 << endl;
				gruup[m].name = s1;
				baze.close();
				system("pause");
			}
			default:
				cout << "Неверная команда! Попробуйте еще раз!" << endl;

			}
		}
		else
		{
			string s;
			cout << "Желаете изменить пароль  (y (да) / n (нет)) ";
			cin >> s;
			if (s == "y")
			{
				cout << endl << "Введите новый пароль" << endl;
				cin >> s;
				user[u].pass = s;
				ofstream baze("d:\\base.txt", ios::trunc);
				for (int i = 0; i < m; i++)
				{
					baze << user[i].login << " " << user[i].pass << endl;
				}
				baze.close();
			}
			else if (s == "n")
			{
				exit(0);
			}
		}
	}
	system("pause");
	exit(0);
	return 0;
}
