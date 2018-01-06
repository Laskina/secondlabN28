#include <iostream>
#include <string>
/*28. Создать абстрактный класс Root с виртуальными методами вычисления корней и
вывода результата на экран. Определить производные классы Linear (линейное
уравнение) и Square (квадратное уравнение) и собственными методами вычисления
корней и вывода на экран. Выполнила Ласкина Н.В*/

using namespace std;
//перевод double строку, где d - число, format - максимальное количество знаков после запятой
string DoubleToString(double d, int format) {
	string s = to_string(d);
	string s2="";
	int i = 0, n=s.length();
	while (i < n && s[i] != ',') {//сохраняем целую часть
		s2+= s[i];
		++i;
	}
	int pos = i;
	i = pos + format;
	while (i > pos && s[i] == '0') --i; //все нули справа пропускаем
	int len = i;
	if (i > pos) {//если после запятой не только нули
		i = pos + 1;
		while (i <= len) {
			s2[i]+= s[i];
			--i;
		}
	}
	
	return s2;
}
//создает одночлен многочлена, d - коэффициент, degree - степень х данного одночлена, maxdegree - максимальная степень уравнения
string Odnochlen(double d, int degree, int maxdegree) {
	string s = "";
	if (d != 0)
	{
		s = DoubleToString(abs(d), 3);
		switch (degree) {
		case 0:break;
		case 1: s += "x"; break;
		default: s += "x^" + to_string(degree); break;
		}
		if (d < 0) s = "-" + s;
		else
			if (degree < maxdegree) s = "+" + s;//если степень не высшая, добавляем + к положительному коэффициенту
	}
	return s;
}

//класс - корень
class Root {
public:
	virtual void FindRoot()=0;//найти корень
	virtual void Display()=0;//вывести на экран
	virtual void Read()=0;//считать
	virtual string ToString()=0;//преобразовать в строку
};
//линейное уравнение, имеет вид ах+в=0
class Linear : public Root 
{
protected:
	double a, b;//коэффициенту
	double root;//корень уравнения
public:
	Linear(double a_=0, double b_=0) : a(a_), b(b_) {};//конструктор
	//поиск корня
	virtual void FindRoot() {
		if (a == 0)
		{
			if (b == 0) //уравнение вида 0=0 
				cout << "Бесконечное число корней" << endl;
			else//уравнение вида в=0, корней нет
				cout << "Корней нет" << endl;
			return ;
		}
		if (b == 0) root = 0;//уравнение вида ах=0
		else//ах+в=0 
			root= ((-1)*b) / a;
		cout <<"Корень: " << root << endl;
		return ;
	};
	//вывести уравнение на экран
	virtual void Display() {
		cout << ToString()<<endl;
	};
	//считать коэффициенты уравнения
	virtual void Read() {
		cout << "Введите коэффициенты a и b линеного уравнения ax+b=0"<< endl;
		cout << "a: ";
		cin >> a;
		cout << endl;
		cout << "b: ";
		cin >> b;
		cout << endl;
	};
	//привести уравнение к виду строки
	virtual string ToString() {
		string sa = Odnochlen(a,1,1), sb = Odnochlen(b, 0, 1);//получаем одночлены
		string s = sa + sb;
		if (s.length() > 0) s += " = 0";//если не пустое уравнение
		else
			s = "0 = 0";
		return s;
	};
	
	
};
//квадратное уравнение вида ах^2+bx+c=0
class Square : public Root
{
protected:
	double a, b, c; //коэффициенты уравнения 
	double root1, root2; //корни
public:
	Square(double a_=0, double b_=0, double c_=0) : a(a_), b(b_),c(c_) {};//конструктор
	//поиск корней
	virtual void FindRoot() {
		if (a == 0) {//если линейное уравнение
			Linear lin(b, c);
			lin.FindRoot();
			return;
		}
		else
		{		//вычисляем -b (так как 0*(-1) получается -0)
				double b1 = b==0?0:(-1)*b;
				double d = b*b - 4 * a*c;//дискриминант
				if (d < 0) { cout << "Корней нет" << endl; return; }
				if (d == 0) {
					root1 = (b1) / (2 * a);
					root2 = root1;
					cout << "Корень: " << root1 << endl;
					return;
				}//если два корня
				root1 = (b1 - sqrt(d)) / (2 * a);
				root2 = (b1 + sqrt(d)) / (2 * a);
				cout << "Корни: " << root1 << " " << root2 << endl;
				return;
			
		}
	};
	//вывод квадратного уравнения
	virtual void Display() {
		cout << ToString() << endl;
	};
	//считывает коэффициенты квадратного уравнения
	virtual void Read() {
		cout << "Введите коэффициенты a и b линеного уравнения ax^2+bx+c=0" << endl;
		cout << "a: ";
		cin >> a;
		cout << endl;
		cout << "b: ";
		cin >> b;
		cout << endl;
		cout << "c: ";
		cin >> c;
		cout << endl;
	};
	//преобразовать квадратное уравнение к виду строки
	virtual string ToString() {
		string sa = Odnochlen(a, 2, 2), sb = Odnochlen(b, 1, 2), sc= Odnochlen(c, 0, 2);
		string s = sa + sb + sc;
		if (s.length() > 0) s += " = 0";
		else
			s = "0 = 0";
		return s;
	};

};

int main() {
	setlocale(LC_ALL, "Russian");

	Linear lin;
	Square sq;
	//считываем линейное уравнение, и вычисляем его корни
	lin.Read();
	lin.Display();
	lin.FindRoot();
	//считываем квадратное уравнение и вычисляем его корни
	sq.Read();
	sq.Display();
	sq.FindRoot();
	system("pause");


	return 0;
}