#include<iostream>
#include"speechManager.h"
using namespace std;

int main() {
	SpeechManager sm;
	while (1) {
	FLAG1:
		//չʾ�˵�
		sm.show_menu();
		int temp_select;
		cout << "����������Ҫ�Ĳ�����" << endl;
		cin >> temp_select;
		switch (temp_select) {
		case 1: {
			//��ʼ�ݽ�����
			sm.Start_Speech();
			system("pause");
			system("cls");
			break;

		}
		case 2: {
			//�鿴�������
			sm.Show_Game_Record();
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			//��ձ�����¼
			sm.Delete_Game_Record();
			system("pause");
			system("cls");
			break;
		}
		case 0: {
			//�˳�����ϵͳ
			sm.exit_system();
			break;
		}
		default:
			cout << "��������������������" << endl;
			system("pause");
			system("cls");
			goto FLAG1;
			break;
		}
		if (temp_select == 0) {
			exit(0);
			break;
		}
	}
	system("pause");
	return 0;
}