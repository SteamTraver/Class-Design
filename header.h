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


//定义家电的数据结构体
struct Appliance
{
	string name;
	string logo;
	double price;
	int numbers;
	Appliance* next;
	//自定义的默认构造函数
	Appliance();
	Appliance(string n, string l, double p, int N);
};

#pragma region Declaration
//利用参数初始化列表对结构体进行赋值
Appliance::Appliance() : name("NULL"), logo("NULL"), price(0.00), numbers(0), next(nullptr) {};
Appliance::Appliance(string n, string l, double p, int N) : name(n), logo(l), price(p), numbers(N), next(nullptr) {};

//对链表内部的函数定义：
void InitDataNode(Appliance& Ap); //初始化一个节点
void OutputNode(Appliance* Ap);   //输出单个结构体
void OutputList(Appliance* Head); //输出整个链表

Appliance* CreateList(Appliance* Ap, int Num);        //创建链表
Appliance* SortList(Appliance* Head);                 //归并主函数，递归调用。
Appliance* merge(Appliance* head1, Appliance* head2); //将两个链表合并
Appliance* getMid(Appliance* head);                   //获取链表中点

Appliance* InsertNode(Appliance* Head, Appliance* Ap);  //固定按照单价的升序进行排列插入
Appliance* Deleteforname(Appliance* Head, string name); //删除List中名称为name的商品,可能要修改返回值为void
Appliance* Deleteforlogo(Appliance* Head, string logo); //删除List中品牌为logo的商品,先搜索符合要求的商品，再分条件删除

void Searchforname(Appliance* Head, string name); // 通过商品名称进行删除
void Searchforlogo(Appliance* Head, string logo); // 通过商品品牌进行删除

//对链表与外部文件交互的函数定义：
void Write(Appliance& Ap, string filename);
void Writetofile(Appliance* Head, string filename, int n); //写入
void ClearFile(string filename);
Appliance* Read(string filename);   //读取文件，返回一个整理好的链表
void ReadfromFile(string fromfile); //读取文件，并且采取相应操作
void Savechanges(Appliance* list);  //接受链表，对链表进行删改之后，把改动写入到文件中去。

#pragma endregion

#pragma region Definition

// 初始化一个节点
void InitDataNode(Appliance& Ap) //初始化函数中应该注意如何抛弃空格
{
	cout << "Enter the name and logo of this product:\n";
	cout << "name:\n";
	getline(cin, Ap.name); //getline 属于string流。
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
	cin.get(); //抛弃最后一个回车
}
// 对一个节点进行输出
void OutputNode(Appliance* Ap)
{
	if (Ap != nullptr)
	{
		cout << "Name and Brand of this product:\n";
		cout << ".................................";
		cout << "\nProduct Name：\t" << Ap->name << '\n'
			<< "Product Brand：\t" << Ap->logo << endl;

		cout << "Price and Numbers in repos:\n";
		cout << ".................................";
		cout << "\nPrice：\t" << Ap->price << '\n'
			<< "Numbers：\t" << Ap->numbers << endl;
		cout << "/////////////////////////////////\n";
	}

}
// 对整个链表进行输出
void OutputList(Appliance* Head)
{

	if (!Head)
		return;
	for (Appliance* p = Head; p != nullptr; p = p->next)
	{
		OutputNode(p);
	}

}

// 接受一个appliance数组，创建一个链表
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
//在经过CreateList的操作之后，需要对链表节点进行重新排序
//这样做可以使一个函数的功能去复杂化，并且做到互相独立运行，互不干扰

Appliance* SortList(Appliance* Head) //使用归并排序
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
// 插入节点
Appliance* InsertNode(Appliance* Head, Appliance* Ap)
{
	if (!Head || !Ap)
		return nullptr;
	Appliance* p = Head;
	while (true)
	{
		if (p->next == nullptr) //找到最后一个节点，直接链接在最后
		{
			p->next = Ap;
			Ap->next = nullptr; //将最后一个节点的next赋值为空。
			break;
		}
		p = p->next;
	}
	Head = SortList(Head); //调用SortList对整个链表进行整理。
	return Head;
}
// 根据商品名称进行删除
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
// 根据logo名称删除
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
// 对同名商品进行查找
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
				cout << "Appliance Founded：" << endl;
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
// 对同名logo进行商品查找
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
// 对单个商品对象进行写入
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
// 对整个商品链表进行写入
void Writetofile(Appliance* Head, string filename, int n)
{
	Appliance* p = Head;

	fstream fouttime(filename, ios_base::app);
	fouttime << n << endl;
	//将存储次数输出到文件首行。
	fouttime.clear();
	fouttime.close();

	while (true) //然后进行遍历输出到文件中。
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
//Read的作用是将数据读取到一个结构体数组中，返回一个数组的指针
//因为直接读取整个文件的数据，读取操作会难以控制
Appliance* Read(string filename) //留待修改
{
	fstream fin;
	fin.open(filename, ios_base::in);

	int Readtimes = 0;
	fin >> Readtimes;
	//3
	//fin.close();
	//新建数组用于存储数据

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

	//从文件中恢复一个已经整理好的链表：
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
				cout << "Enter Product Name：\n";
				cin >> name;
				Searchforname(newList1, name);
			}
			if (search == "logo")
			{
				string logo;
				cout << "Enter the Brand Name：\n";
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
				cout << "Enter the name：" << endl;
				cin >> name;
				newList1 = Deleteforname(newList1, name);
				cout << "List after One Node been delete：\n";
				cout << ".................................\n";
				OutputList(newList1);
				cout << ".................................\n";
			}
			if (deleteway == "logo")
			{
				string logo;
				cout << "Enetr the Brand：\n";
				cin >> logo;
				cin.get();

				newList1 = Deleteforlogo(newList1, logo);
				cout << "List after One Node been delete：\n";
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
				NodeNum++; //重新记录输出个数
				if (p->next == nullptr)
					break;
				p = p->next;
			}
			ClearFile(fromfile); //清楚全部数据

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

