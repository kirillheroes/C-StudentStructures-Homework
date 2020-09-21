#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

const unsigned int N = 3;
struct Student
{
	string name;
	string nick;
	unsigned short int math;
	unsigned short int inf;
	unsigned short int phy;
};

void Output(Student info[])
{
	fstream f; f.open("student.data", ios::in);
	for (int i = 0; i < N; i++)
	{
		f >> info[i].name;
		f >> info[i].nick;
		f >> info[i].math;
		f >> info[i].inf;
		f >> info[i].phy;
	}
	f.close();
}

void BinaryInput(Student info[])
{
	fstream B; B.open("binary.data", ios::binary | ios::out);
	for (int i = 0; i < N; i++)
	{
		B.write((char *)&info, sizeof(info));
	}
	B.close();
}
void BinaryOutput(Student info[])
{
	cout << "\n===========================================" << endl;
	cout << "А) Данные из бинарного файла: ";
	fstream B; B.open("binary.data", ios::binary | ios::in);
	for (int i = 0; i < N; i++)
	{
		B.read((char *)&info, sizeof(info));
		cout << '\n' << info[i].name << '\n' << info[i].nick << endl;
		cout << info[i].math << '\n' << info[i].inf << '\n' << info[i].phy << endl;
	}
	B.close();
}

void Sort(Student **Ptr)
{
	for (int i = N - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if ((Ptr[j]->math + Ptr[j]->inf + Ptr[j]->phy) 
		> (Ptr[j + 1]->math + Ptr[j+1]->inf + Ptr[j+1]->phy))
				swap(Ptr[j], Ptr[j + 1]);
}


void Result(Student **Ptr)
{
	cout << "\n===========================================" << endl;
	cout << "Б) Результат из массива указателей на структуру: ";
	for (int i = 0; i < N; i++)
	{
		cout << '\n' << Ptr[i]->name << '\n' << Ptr[i]->nick << endl;
		cout << Ptr[i]->math << '\n' << Ptr[i]->inf << '\n' << Ptr[i]->phy << endl;
	}
}


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	fstream f; f.open("student.data", ios::out);
	Student info[N]; //массив структур
	for (int i = 0; i < N; i++)
	{
		cout << "Студент №" << (i + 1);
		cout << "\nИмя студента: "; 
		cin >> info[i].name;
		f << info[i].name << ' ';
		cout << "Фамилия студента: ";
		cin >> info[i].nick;
		f << info[i].nick << ' ';
		cout << "Его оценка по: ";
		info[i].math = rand() % 3 + 2;
		cout << "\n- Математике: " << info[i].math;
		f << info[i].math << ' ';
		info[i].inf = rand() % 3 + 2;
		cout << "\n- Информатике: " << info[i].inf;
		f << info[i].inf << ' ';
		info[i].phy = rand() % 3 + 2;
		cout << "\n- Физика: " << info[i].phy << endl;
		f << info[i].phy << ' ';
	}
	f.close();
	//===============================================================
	Student *ptrinfo = info; 
	Output(ptrinfo); 
	BinaryInput(ptrinfo);
	BinaryOutput(ptrinfo);

	Student **Ptr = new Student*[N]; //массив указателей на структуру
	for (int i = 0; i < N; i++) Ptr[i] = &info[i];
	Sort(Ptr);
	Result(Ptr);
	system("pause > nul");
}