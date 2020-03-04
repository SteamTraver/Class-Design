#include"header.h"

int main()
{
	//重新编写整个程序的运行逻辑，之后再将头文件进行清理。

	//三者设置为全局变量，更好控制
	string newFile = "NULL";  //此为后来创建的文件
	string filename = "NULL"; //此为可能已经存在的文件
	bool switcher = true;
	int ApplianceNum = 0; //读取个数

	cout << "Please enter the file name：\n";
	getline(cin, filename); //这种输入可以取一行的数据，空格也是有效的。

	cout << "Confirming the existence of file...：\n";

	ifstream fileManager(filename);
	switch (!fileManager)
	{
	case true:
		cout << "No such file, create it? Y/N \n";
		char Confirm;
		cin >> Confirm;
		cin.get();
		switch (Confirm)
		{
		case 'Y':
			goto TestBegin_FileCreate;
			break;
		case 'N':
			cout << "Pragram Exit.\n";
			goto EXIT; //利用goto实现跳转。
			break;
		default:
			goto EXIT;
			break;
		}
		break;
	case false:
		cout << "File Founded, you wnat USE it ？Y/N\n";
		char Confirm_2;
		cin >> Confirm_2;
		//cin.get();
		switch (Confirm_2)
		{
		case 'Y':
			goto TestBegin_FileTest;
			break;
		case 'N':
			cout << "Program Quit\n";
			goto EXIT; //利用goto实现跳转。
			break;
		default:
			goto EXIT;
			break;
		}
		break;
	}

	//其中定义创建链表及输出到文件中的操作，最后提示用户到指定目录中寻找源文件
	//TestBegin_FileCreate之中并没有改变链表长度的操作
	//所以ApplianceNum可以传到下个函数块中用于文件读取使用

TestBegin_FileCreate:
	{
		cout << "How Many Items You Wanna Store To File? \n" << endl;
		cin >> ApplianceNum;
		cin.get();

		Appliance* APPS = new Appliance[ApplianceNum];

		//数据填充
		for (int i = 0; i < ApplianceNum; i++)
			InitDataNode(APPS[i]);
		//cout << endl;
		//创建并整理链表
		Appliance* List = SortList(CreateList(APPS, ApplianceNum));

		cout << "Inputed data: \n";
		cout << ".................................\n";
		OutputList(List);
		cout << ".................................\n";

		cout << "Store the data to file? Y/N\n";

		char Confirm_3;
		cin >> Confirm_3;
		cin.get();
		switch (Confirm_3)
		{
		case 'Y':
			cout << "Enter the file name：\n";
			getline(cin, newFile);
			Writetofile(List, newFile, ApplianceNum);
			cout << endl;
			cout << "Data stored, check it in Realtive folder...\n";
			cout << ".............................................\n";
			cout << "Do you want TSET this file ？Y/N\n"; //测试到这里。

			char Confirm_4;
			cin >> Confirm_4;
			cin.get();
			switch (Confirm_4)
			{
			case 'Y':
				goto TestBegin_FileTest;
				switcher = false; //将switcher转为负，使TestBegin_FileTest识别是从何处传来的文件。
				break;
			case 'N':
				cout << "Program Quit\n";
				goto EXIT;
				break;
			default:
				cout << "Program Quit\n";
				goto EXIT;
				break;
			}
			break;
		case 'N':
			cout << "Program Quit\n";
			goto EXIT;
			break;
		default:
			cout << "Program Quit\n";
			goto EXIT;
			break;
		}
	}

	//文件找到之后的操作为：恢复为链表、输出到屏幕上、进行查找、插入操作
	//查找插入之后可以重新输入到文件之中

TestBegin_FileTest:
	{

		//switcher用于辨别文件的来源：
		if (switcher)
		{
			ReadfromFile(filename);
			goto EXIT;
		}

		else
		{
			ReadfromFile(newFile);
			goto EXIT;
		}
	}
EXIT:
	return 0;
}