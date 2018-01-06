#include <iostream>
#include <string>
/*28. ������� ����������� ����� Root � ������������ �������� ���������� ������ �
������ ���������� �� �����. ���������� ����������� ������ Linear (��������
���������) � Square (���������� ���������) � ������������ �������� ����������
������ � ������ �� �����. ��������� ������� �.�*/

using namespace std;
//������� double ������, ��� d - �����, format - ������������ ���������� ������ ����� �������
string DoubleToString(double d, int format) {
	string s = to_string(d);
	string s2="";
	int i = 0, n=s.length();
	while (i < n && s[i] != ',') {//��������� ����� �����
		s2+= s[i];
		++i;
	}
	int pos = i;
	i = pos + format;
	while (i > pos && s[i] == '0') --i; //��� ���� ������ ����������
	int len = i;
	if (i > pos) {//���� ����� ������� �� ������ ����
		i = pos + 1;
		while (i <= len) {
			s2[i]+= s[i];
			--i;
		}
	}
	
	return s2;
}
//������� �������� ����������, d - �����������, degree - ������� � ������� ���������, maxdegree - ������������ ������� ���������
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
			if (degree < maxdegree) s = "+" + s;//���� ������� �� ������, ��������� + � �������������� ������������
	}
	return s;
}

//����� - ������
class Root {
public:
	virtual void FindRoot()=0;//����� ������
	virtual void Display()=0;//������� �� �����
	virtual void Read()=0;//�������
	virtual string ToString()=0;//������������� � ������
};
//�������� ���������, ����� ��� ��+�=0
class Linear : public Root 
{
protected:
	double a, b;//������������
	double root;//������ ���������
public:
	Linear(double a_=0, double b_=0) : a(a_), b(b_) {};//�����������
	//����� �����
	virtual void FindRoot() {
		if (a == 0)
		{
			if (b == 0) //��������� ���� 0=0 
				cout << "����������� ����� ������" << endl;
			else//��������� ���� �=0, ������ ���
				cout << "������ ���" << endl;
			return ;
		}
		if (b == 0) root = 0;//��������� ���� ��=0
		else//��+�=0 
			root= ((-1)*b) / a;
		cout <<"������: " << root << endl;
		return ;
	};
	//������� ��������� �� �����
	virtual void Display() {
		cout << ToString()<<endl;
	};
	//������� ������������ ���������
	virtual void Read() {
		cout << "������� ������������ a � b �������� ��������� ax+b=0"<< endl;
		cout << "a: ";
		cin >> a;
		cout << endl;
		cout << "b: ";
		cin >> b;
		cout << endl;
	};
	//�������� ��������� � ���� ������
	virtual string ToString() {
		string sa = Odnochlen(a,1,1), sb = Odnochlen(b, 0, 1);//�������� ���������
		string s = sa + sb;
		if (s.length() > 0) s += " = 0";//���� �� ������ ���������
		else
			s = "0 = 0";
		return s;
	};
	
	
};
//���������� ��������� ���� ��^2+bx+c=0
class Square : public Root
{
protected:
	double a, b, c; //������������ ��������� 
	double root1, root2; //�����
public:
	Square(double a_=0, double b_=0, double c_=0) : a(a_), b(b_),c(c_) {};//�����������
	//����� ������
	virtual void FindRoot() {
		if (a == 0) {//���� �������� ���������
			Linear lin(b, c);
			lin.FindRoot();
			return;
		}
		else
		{		//��������� -b (��� ��� 0*(-1) ���������� -0)
				double b1 = b==0?0:(-1)*b;
				double d = b*b - 4 * a*c;//������������
				if (d < 0) { cout << "������ ���" << endl; return; }
				if (d == 0) {
					root1 = (b1) / (2 * a);
					root2 = root1;
					cout << "������: " << root1 << endl;
					return;
				}//���� ��� �����
				root1 = (b1 - sqrt(d)) / (2 * a);
				root2 = (b1 + sqrt(d)) / (2 * a);
				cout << "�����: " << root1 << " " << root2 << endl;
				return;
			
		}
	};
	//����� ����������� ���������
	virtual void Display() {
		cout << ToString() << endl;
	};
	//��������� ������������ ����������� ���������
	virtual void Read() {
		cout << "������� ������������ a � b �������� ��������� ax^2+bx+c=0" << endl;
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
	//������������� ���������� ��������� � ���� ������
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
	//��������� �������� ���������, � ��������� ��� �����
	lin.Read();
	lin.Display();
	lin.FindRoot();
	//��������� ���������� ��������� � ��������� ��� �����
	sq.Read();
	sq.Display();
	sq.FindRoot();
	system("pause");


	return 0;
}