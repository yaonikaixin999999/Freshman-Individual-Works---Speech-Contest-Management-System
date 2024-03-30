#include<iostream>
#include"speechManager.h"
using namespace std;

class my_print_d {
public:
	void operator()(double val) {
		cout << val << " ";
	}
};

class my_sort_d {
public:
	bool operator()(double v1, double v2) {
		return v1 > v2;
	}
};

class my_print {
public:
	void operator()(int val) {
		cout << val << " ";
	}
};

class my_map_find_if_if /*:public SpeechManager*/ {
public:
	my_map_find_if_if(double my_temp_score) :temp_score(my_temp_score) {}
	bool operator()(map<int, Speaker>::value_type pair) {
		return pair.second.m_score[1] == temp_score;
	}

private:
	double temp_score;
};

class my_map_find_if /*:public SpeechManager*/ {
public:
	my_map_find_if(double my_temp_score) :temp_score(my_temp_score) {}
	bool operator()(map<int, Speaker>::value_type pair) {
		return pair.second.m_score[0] == temp_score;
	}

private:
	double temp_score;
};

//构造函数
SpeechManager::SpeechManager() {
	//初始化
	this->initspeech_system();


}

//初始化
void SpeechManager::initspeech_system() {
	//保证容器为空
	this->v_first.clear();
	this->v_second.clear();
	this->v_victory.clear();
	this->m_speaker.clear();
	//设置比赛为第一场
	this->index = 1;
}

//增加第一局演讲选手
void SpeechManager::First_add_speaker() {
	string add_name = "ABCDEFGHIJKL";
	for (int i = 0; i < add_name.size(); i++) {
		string temp_name = "选手";
		temp_name += add_name[i];

		Speaker sp;
		sp.m_Name = temp_name;

		for (int j = 0; j < 2; j++) {
			sp.m_score[j] = 0;
		}

		//存放数据
		this->m_speaker.insert(make_pair(10001 + i, sp));
		//更新第一轮比赛的演讲者编号
		this->v_first.push_back(10001 + i);
	}
}

//小组赛
void SpeechManager::group_min_game(int game_num, int did, vector<int>temp_vec) {
	cout << endl << "第" << this->index << "场比赛第" << game_num + 1 << "小组比赛开始！" << endl;
	Sleep(500);
	//清空比赛成绩
	this->temp_v_score.clear();
	int temp_score[10];
	for (int i = did; i < did + 6; i++) {
		cout << endl;
		vector<int>::iterator itv = temp_vec.begin();
		map<int, Speaker>::iterator it = m_speaker.find(*(itv + i));
		cout << (*it).first << "号" << (*it).second.m_Name << "正在演讲中..." << endl;
		Sleep(1000);
		int all_score = 0;
		for (int k = 0; k < 10; k++) {
			temp_score[k] = rand() % 100 + 1;
			cout << "裁判" << k + 1 << "给出" << temp_score[k] << "分" << " ";
			all_score += temp_score[k];
			Sleep(50);
			if (k == 4) {
				cout << endl;
			}
		}
		cout << endl;
		sort(temp_score, temp_score + 10);
		all_score = all_score - temp_score[0] - temp_score[9];
		cout << "最终分为(去除最高分和最低分)：" << all_score * 1.0 / 8 << endl;
		//保存分数
		(*it).second.m_score[this->index - 1] = double(all_score * 1.0 / 8);
		this->temp_v_score.push_back(double((all_score * 1.0) / 8));
	}
}

//第一场比赛
void SpeechManager::first_game() {
	cout << "第" << this->index << "场比赛选手正在分组中..." << endl;
	//_sleep(2000
	Sleep(1000);
	//1、抽签
	srand((unsigned int)time(NULL));
	random_shuffle(this->v_first.begin(), this->v_first.end());
	cout << "分组成功!" << endl;
	Sleep(500);
	cout << "第一组比赛选手:" << endl;
	for_each(this->v_first.begin(), this->v_first.begin() + 6, my_print());
	Sleep(1000);
	cout << endl << "第二组比赛选手:" << endl;
	for_each(this->v_first.end() - 6, this->v_first.end(), my_print());
	Sleep(500);
	cout << endl;
	cout << "------------- 第" << this->index << "轮正式比赛开始：------------- " << endl;
	//2、比赛
	for (int j = 0; j < 2; j++) {
		if (j == 0) {
			SpeechManager::group_min_game(j, 0, this->v_first);
			Sleep(1000);
		}
		if (j == 1) {
			SpeechManager::group_min_game(j, 6, this->v_first);
			Sleep(1000);
		}
	}
	cout << endl;
	cout << "------------- 第" << this->index << "轮比赛正式结束！------------- " << endl;

	//3、显示晋级结果
		//对分数排序
	sort(temp_v_score.begin(), temp_v_score.end(), my_sort_d());
	cout << endl;
	cout << "恭喜以下6位选手晋级：" << endl;
	for (int o = 0; o < 6; o++) {
		map<int, Speaker>::iterator itm_s = find_if(this->m_speaker.begin(), this->m_speaker.end(), my_map_find_if(temp_v_score[o]));
		cout << (*itm_s).first << "号选手" << (*itm_s).second.m_Name << " 分数为" << (*itm_s).second.m_score[this->index - 1] << endl;
		//更新第二场比赛的比赛选手
		this->v_second.push_back((*itm_s).first);
	}
	Sleep(1000);
	cout << endl;
	this->index++;
}

//第二场比赛
void SpeechManager::second_game() {
	//1、抽签
	cout << "第" << this->index << "场比赛选手正在分组中..." << endl;
	Sleep(1000);
	srand((unsigned int)time(NULL));
	random_shuffle(this->v_second.begin(), this->v_second.end());
	cout << "分组成功!" << endl;
	Sleep(500);
	cout << "第一小组成员为：" << endl;
	for_each(this->v_second.begin(), this->v_second.end(), my_print());
	cout << endl;
	cout << "------------- 第" << this->index << "轮正式比赛开始：------------- " << endl;
	//2、比赛
	this->group_min_game(0, 0, this->v_second);
	Sleep(1000);
	cout << endl;
	cout << "------------- 第" << this->index << "轮比赛正式结束！------------- " << endl;

	//3、显示最终结果
	sort(temp_v_score.begin(), temp_v_score.end(), my_sort_d());
	for_each(temp_v_score.begin(), temp_v_score.end(), my_print_d());
	cout << endl;
	cout << "恭喜以下三位选手晋级：" << endl;
	for (int i = 0; i < 3; i++) {
		map<int, Speaker>::iterator it_m = find_if(this->m_speaker.begin(), this->m_speaker.end(), my_map_find_if_if(temp_v_score[i]));
		cout << "第" << i + 1 << "名：" << (*it_m).first << "号选手" << (*it_m).second.m_Name << " 分数为：" << (*it_m).second.m_score[this->index - 1] << endl;
	}
	//4、保存分数
	ofstream ofs;
	ofs.open("D:\\Users\\15022\\source\\repos\\演讲比赛流程管理系统\\演讲比赛流程管理系统\\选手成绩.csv", ios::out | ios::app);
	if (!ofs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 12; i++) {
			map<int, Speaker>::iterator it_m_map = find_if(this->m_speaker.begin(), this->m_speaker.end(), my_map_find_if(10000 + i));
			ofs << (*it_m_map).first << " " << (*it_m_map).second.m_Name << " " << (*it_m_map).second.m_score[j] << endl;
		}
	}
	ofs << endl;
	ofs.close();
}


//展示菜单
void SpeechManager::show_menu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//开始演讲比赛
void SpeechManager::Start_Speech() {
	this->First_add_speaker();
	this->first_game();
	this->second_game();
}

//查看往届记录
void SpeechManager::Show_Game_Record() {
	this->m_speaker.clear();
	ifstream ifs;
	ifs.open("D:\\Users\\15022\\source\\repos\\演讲比赛流程管理系统\\演讲比赛流程管理系统\\选手成绩.csv", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
	}
	char c;
	//while ((c = ifs.get()) != EOF) {
	//	this->m_speaker.insert(make_pair()
	//}

	ifs.close();
}

//清空比赛记录
void SpeechManager::Delete_Game_Record() {

}

//退出系统d
void SpeechManager::exit_system() {
	cout << "欢迎下次使用" << endl;
}

//析构函数
SpeechManager::~SpeechManager() {

}