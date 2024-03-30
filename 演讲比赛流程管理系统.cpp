#include<iostream>
#include"speechManager.h"
using namespace std;

int main() {
	SpeechManager sm;
	while (1) {
	FLAG1:
		//展示菜单
		sm.show_menu();
		int temp_select;
		cout << "请输入您想要的操作：" << endl;
		cin >> temp_select;
		switch (temp_select) {
		case 1: {
			//开始演讲比赛
			sm.Start_Speech();
			system("pause");
			system("cls");
			break;

		}
		case 2: {
			//查看往届比赛
			sm.Show_Game_Record();
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			//清空比赛记录
			sm.Delete_Game_Record();
			system("pause");
			system("cls");
			break;
		}
		case 0: {
			//退出比赛系统
			sm.exit_system();
			break;
		}
		default:
			cout << "您输入有误，请重新输入" << endl;
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