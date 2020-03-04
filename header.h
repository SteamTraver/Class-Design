#pragma once
#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ios_base;
using std::ofstream;
using std::ifstream;


//����ҵ�����ݽṹ��
struct Appliance
{
	string name;
	string logo;
	double price;
	int numbers;
	Appliance* next;
	//�Զ����Ĭ�Ϲ��캯��
	Appliance();
	Appliance(string n, string l, double p, int N);
};

#pragma region Declaration
//���ò�����ʼ���б�Խṹ����и�ֵ
Appliance::Appliance() : name("NULL"), logo("NULL"), price(0.00), numbers(0), next(nullptr) {};
Appliance::Appliance(string n, string l, double p, int N) : name(n), logo(l), price(p), numbers(N), next(nullptr) {};

//�������ڲ��ĺ������壺
void InitDataNode(Appliance& Ap); //��ʼ��һ���ڵ�
void OutputNode(Appliance* Ap);   //��������ṹ��
void OutputList(Appliance* Head); //�����������

Appliance* CreateList(Appliance* Ap, int Num);        //��������
Appliance* SortList(Appliance* Head);                 //�鲢���������ݹ���á�
Appliance* merge(Appliance* head1, Appliance* head2); //����������ϲ�
Appliance* getMid(Appliance* head);                   //��ȡ�����е�

Appliance* InsertNode(Appliance* Head, Appliance* Ap);  //�̶����յ��۵�����������в���
Appliance* Deleteforname(Appliance* Head, string name); //ɾ��List������Ϊname����Ʒ,����Ҫ�޸ķ���ֵΪvoid
Appliance* Deleteforlogo(Appliance* Head, string logo); //ɾ��List��Ʒ��Ϊlogo����Ʒ,����������Ҫ�����Ʒ���ٷ�����ɾ��

void Searchforname(Appliance* Head, string name); // ͨ����Ʒ���ƽ���ɾ��
void Searchforlogo(Appliance* Head, string logo); // ͨ����ƷƷ�ƽ���ɾ��

//���������ⲿ�ļ������ĺ������壺
void Write(Appliance& Ap, string filename);
void Writetofile(Appliance* Head, string filename, int n); //д��
void ClearFile(string filename);
Appliance* Read(string filename);   //��ȡ�ļ�������һ������õ�����
void ReadfromFile(string fromfile); //��ȡ�ļ������Ҳ�ȡ��Ӧ����
void Savechanges(Appliance* list);  //�����������������ɾ��֮�󣬰ѸĶ�д�뵽�ļ���ȥ��

#pragma endregion

#pragma region Definition

// ��ʼ��һ���ڵ�
void InitDataNode(Appliance& Ap) //��ʼ��������Ӧ��ע����������ո�
{
	cout << "Enter the name and logo of this product:\n";
	cout << "name:\n";
	getline(cin, Ap.name); //getline ����string����
	cout << "logo:\n";
	getline(cin, Ap.logo);
	cout << "Enter price and numbers in repos: \n";
	cout << "price:\n";
	cin >> Ap.price;
	cin.get();
	cout << "numbers:\n";
	cin >> Ap.numbers;
	cin.get();
	Ap.next = nullptr;
	cin.get(); //�������һ���س�
}
// ��һ���ڵ�������
void OutputNode(Appliance* Ap)
{
	if (Ap != nullptr)
	{
		cout << "Name and Brand of this product:\n";
		cout << ".................................";
		cout << "\nProduct Name��\t" << Ap->name << '\n'
			<< "Product Brand��\t" << Ap->logo << endl;

		cout << "Price and Numbers in repos:\n";
		cout << ".................................";
		cout << "\nPrice��\t" << Ap->price << '\n'
			<< "Numbers��\t" << Ap->numbers << endl;
		cout << "/////////////////////////////////\n";
	}

}
// ����������������
void OutputList(Appliance* Head)
{

	if (!Head)
		return;
	for (Appliance* p = Head; p != nullptr; p = p->next)
	{
		OutputNode(p);
	}

}

// ����һ��appliance���飬����һ������
Appliance* CreateList(Appliance* Ap, int Num)
{
	if (!Ap)
		return nullptr;
	Appliance* p = nullptr;
	Appliance* Lp = nullptr;
	for (int i = 0; i < Num; i++)
	{
		if (p == nullptr)
		{
			p = &Ap[i];
			Lp = p;
		}
		else
		{
			while (true)
			{
				if (p->next == nullptr)
				{
					p->next = &Ap[i];
					break;
				}
				p = p->next;
			}
		}
	}
	return Lp;
}
//�ھ���CreateList�Ĳ���֮����Ҫ������ڵ������������
//����������ʹһ�������Ĺ���ȥ���ӻ���������������������У���������

Appliance* SortList(Appliance* Head) //ʹ�ù鲢����
{
	if (Head == nullptr || Head->next == nullptr)
		return Head;

	Appliance* head1 = Head;
	Appliance* head2 = getMid(Head);

	head1 = SortList(head1);
	head2 = SortList(head2);

	return merge(head1, head2);
}
Appliance* merge(Appliance* head1, Appliance* head2)
{
	Appliance* newHead = new Appliance();
	Appliance* newTail = newHead;
	while (head1 && head2)
	{
		if (head1->price <= head2->price)
		{
			newTail->next = head1;
			head1 = head1->next;
		}
		else
		{
			newTail->next = head2;
			head2 = head2->next;
		}
		newTail = newTail->next;
		newTail->next = nullptr;
	}
	if (head1)
		newTail->next = head1;
	if (head2)
		newTail->next = head2;
	return newHead->next;
}
Appliance* getMid(Appliance* head)
{
	Appliance* fast = head->next;
	Appliance* slow = head->next;
	Appliance* prev = head;
	while (true)
	{
		if (fast == nullptr)
			break;
		fast = fast->next;
		if (fast == nullptr)
			break;
		fast = fast->next;

		prev = slow;
		slow = slow->next;
	}
	prev->next = nullptr;
	return slow;
}
// ����ڵ�
Appliance* InsertNode(Appliance* Head, Appliance* Ap)
{
	if (!Head || !Ap)
		return nullptr;
	Appliance* p = Head;
	while (true)
	{
		if (p->next == nullptr) //�ҵ����һ���ڵ㣬ֱ�����������
		{
			p->next = Ap;
			Ap->next = nullptr; //�����һ���ڵ��next��ֵΪ�ա�
			break;
		}
		p = p->next;
	}
	Head = SortList(Head); //����SortList�����������������
	return Head;
}
// ������Ʒ���ƽ���ɾ��
Appliance* Deleteforname(Appliance* Head, string name)
{
	if (Head != nullptr)
	{
		Appliance* p = Head;
		while (true)
		{
			if (p->next->name == name && p->next->next != nullptr)
			{
				p->next = p->next->next;
				break;
			}
			if (p->next->name == name && p->next->next == nullptr)
			{
				p->next = nullptr;
				break;
			}
			if (p->name == name)
			{
				Head = p->next;
				break;
			}
			p = p->next;
		}
		Head = SortList(Head);
		return Head;
	}

}
// ����logo����ɾ��
Appliance* Deleteforlogo(Appliance* Head, string logo)
{
	if (Head != nullptr)
	{
		Appliance* p = Head;
		while (true)
		{
			if (p->next->logo == logo && p->next->next != nullptr)
			{
				p->next = p->next->next;
				break;
			}
			if (p->next->logo == logo && p->next->next == nullptr)
			{
				p->next = nullptr;
				break;
			}
			p = p->next;
		}
		Head = SortList(Head);
		return Head;
	}

}
// ��ͬ����Ʒ���в���
void Searchforname(Appliance* Head, string name)
{
	if (Head != nullptr)
	{
		Appliance* p = Head;
		while (true)
		{
			if (p->name == name)
			{
				cout << endl;
				cout << "Appliance Founded��" << endl;
				OutputNode(p);
				//break;
			}
			if (p->next == nullptr)
			{
				cout << "No More Information At Last" << endl;
				break;
			}
			p = p->next;
		}
	}

}
// ��ͬ��logo������Ʒ����
void Searchforlogo(Appliance* Head, string logo)
{
	if (Head != nullptr)
	{
		Appliance* p = Head;
		while (true)
		{
			if (p->logo == logo)
			{
				cout << endl;
				cout << "Appliance Founded: " << endl;
				OutputNode(p);
				//break;
			}
			if (p->next == nullptr)
			{
				cout << "No result, quit. " << endl;
				break;
			}
			p = p->next;
		}
	}

}
// �Ե�����Ʒ�������д��
void Write(Appliance& Ap, string filename)
{
	fstream fout;
	fout.open(filename, ios_base::app);
	{
		fout << Ap.name << endl;
		fout << Ap.logo << endl;
		fout << Ap.price << endl;
		fout << Ap.numbers << endl;
	}
	//2
	fout.clear();
	fout.close();
}
// ��������Ʒ�������д��
void Writetofile(Appliance* Head, string filename, int n)
{
	Appliance* p = Head;

	fstream fouttime(filename, ios_base::app);
	fouttime << n << endl;
	//���洢����������ļ����С�
	fouttime.clear();
	fouttime.close();

	while (true) //Ȼ����б���������ļ��С�
	{
		Write(*p, filename);
		if (p->next == nullptr)
			break;
		p = p->next;
	}
}
void ClearFile(string filename)
{
	ofstream fc(filename, ios_base::trunc);
	fc.close();
}
//Read�������ǽ����ݶ�ȡ��һ���ṹ�������У�����һ�������ָ��
//��Ϊֱ�Ӷ�ȡ�����ļ������ݣ���ȡ���������Կ���
Appliance* Read(string filename) //�����޸�
{
	fstream fin;
	fin.open(filename, ios_base::in);

	int Readtimes = 0;
	fin >> Readtimes;
	//3
	//fin.close();
	//�½��������ڴ洢����

	Appliance* APPS2 = new Appliance[Readtimes];

	for (int i = 0; i < Readtimes; i++)
	{
		fin >> APPS2[i].name
			>> APPS2[i].logo
			>> APPS2[i].price
			>> APPS2[i].numbers;
		fin.flush();
	}


	Appliance* TempHead = CreateList(APPS2, Readtimes);
	return TempHead;
}
void ReadfromFile(string fromfile)
{

	//���ļ��лָ�һ���Ѿ�����õ�����
	Appliance* newList1 = SortList(Read(fromfile));

	cout << "Output after data restored: \n" << endl;
	OutputList(newList1);
	cout << "..................................." << endl;;

	string search = "NULL";
	Appliance newNode;
	string deleteway;
	Appliance* tmp = nullptr;

	char OP = 'Z';
	while (OP != 'Q')
	{
		cout << "..................................................................\n";
		cout << "Chose Your Operations: \n (S)earch \t (I)nsert \t (D)elete \t (W)rite \t (Q)uit \t (L)ist\n";
		cout << "..................................................................\n";

		/* code */
		cin >> OP;
		cin.get();

		switch (OP)
		{
		case 'S':
		{
			cout << "Chose the way you search product: \n\"name or logo\": \n ";
			cin >> search;
			if (search == "name")
			{
				string name;
				cout << "Enter Product Name��\n";
				cin >> name;
				Searchforname(newList1, name);
			}
			if (search == "logo")
			{
				string logo;
				cout << "Enter the Brand Name��\n";
				cin >> logo;
				Searchforlogo(newList1, logo);
			}
		}
		break;
		case 'I':
		{
			cout << "Init A Node.....\n";
			InitDataNode(newNode);
			tmp = &newNode;

			newList1 = InsertNode(newList1, tmp);
			cout << endl;
			cout << "List after Node been Inserted....\n";
			cout << ".................................\n";
			OutputList(newList1);
			cout << ".................................\n";
		}
		break;
		case 'D':
		{
			cout << "Delete Operaation.....\n";
			cout << "Chose the way you Delete product: \n\"name or logo\": \n ";

			cin >> deleteway;
			cin.get();

			if (deleteway == "name")
			{
				string name;
				cout << "Enter the name��" << endl;
				cin >> name;
				newList1 = Deleteforname(newList1, name);
				cout << "List after One Node been delete��\n";
				cout << ".................................\n";
				OutputList(newList1);
				cout << ".................................\n";
			}
			if (deleteway == "logo")
			{
				string logo;
				cout << "Enetr the Brand��\n";
				cin >> logo;
				cin.get();

				newList1 = Deleteforlogo(newList1, logo);
				cout << "List after One Node been delete��\n";
				cout << ".................................\n";
				OutputList(newList1);
				cout << ".................................\n";
			}
		}
		break;
		case 'W':
		{
			int NodeNum = 0;
			Appliance* p = newList1;

			while (true)
			{
				NodeNum++; //���¼�¼�������
				if (p->next == nullptr)
					break;
				p = p->next;
			}
			ClearFile(fromfile); //���ȫ������

			Writetofile(newList1, fromfile, NodeNum);

			cout << "All Operations Saved to file." << endl;
			cout << endl;
		}
		break;
		case 'L':
		{
			cout << "...................................\nCurrent List:\n";
			OutputList(newList1);
			cout << "\n...................................";
		}
		break;
		default:
			cout << "Quit Operations \n";
			break;
		}
	}
}
#pragma endregion

#endif // !HEADER_H_

