#include"header.h"

int main()
{
	//���±�д��������������߼���֮���ٽ�ͷ�ļ���������

	//��������Ϊȫ�ֱ��������ÿ���
	string newFile = "NULL";  //��Ϊ�����������ļ�
	string filename = "NULL"; //��Ϊ�����Ѿ����ڵ��ļ�
	bool switcher = true;
	int ApplianceNum = 0; //��ȡ����

	cout << "Please enter the file name��\n";
	getline(cin, filename); //�����������ȡһ�е����ݣ��ո�Ҳ����Ч�ġ�

	cout << "Confirming the existence of file...��\n";

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
			goto EXIT; //����gotoʵ����ת��
			break;
		default:
			goto EXIT;
			break;
		}
		break;
	case false:
		cout << "File Founded, you wnat USE it ��Y/N\n";
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
			goto EXIT; //����gotoʵ����ת��
			break;
		default:
			goto EXIT;
			break;
		}
		break;
	}

	//���ж��崴������������ļ��еĲ����������ʾ�û���ָ��Ŀ¼��Ѱ��Դ�ļ�
	//TestBegin_FileCreate֮�в�û�иı������ȵĲ���
	//����ApplianceNum���Դ����¸��������������ļ���ȡʹ��

TestBegin_FileCreate:
	{
		cout << "How Many Items You Wanna Store To File? \n" << endl;
		cin >> ApplianceNum;
		cin.get();

		Appliance* APPS = new Appliance[ApplianceNum];

		//�������
		for (int i = 0; i < ApplianceNum; i++)
			InitDataNode(APPS[i]);
		//cout << endl;
		//��������������
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
			cout << "Enter the file name��\n";
			getline(cin, newFile);
			Writetofile(List, newFile, ApplianceNum);
			cout << endl;
			cout << "Data stored, check it in Realtive folder...\n";
			cout << ".............................................\n";
			cout << "Do you want TSET this file ��Y/N\n"; //���Ե����

			char Confirm_4;
			cin >> Confirm_4;
			cin.get();
			switch (Confirm_4)
			{
			case 'Y':
				goto TestBegin_FileTest;
				switcher = false; //��switcherתΪ����ʹTestBegin_FileTestʶ���ǴӺδ��������ļ���
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

	//�ļ��ҵ�֮��Ĳ���Ϊ���ָ�Ϊ�����������Ļ�ϡ����в��ҡ��������
	//���Ҳ���֮������������뵽�ļ�֮��

TestBegin_FileTest:
	{

		//switcher���ڱ���ļ�����Դ��
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