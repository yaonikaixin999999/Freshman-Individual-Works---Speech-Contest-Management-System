#pragma once
#include<iostream>
#include<fstream>
#include<ostream>
#include<algorithm>
#include<string>
#include<ctime>
#include<vector>
#include<map>
#include"speaker.h"
#include<windows.h>
using namespace std;

class SpeechManager {
public:
	//初始化
	void initspeech_system();

	//构造函数
	SpeechManager();

	//第一轮比赛成员编号
	vector<int>v_first;

	//第二轮比赛
	vector<int>v_second;

	//获奖者
	vector<int>v_victory;

	//存放数据
	map<int, Speaker>m_speaker;

	//比赛成绩
	vector<double>temp_v_score;

	//比赛场数
	int index;

	//小组赛
	void group_min_game(int game_num, int did,vector<int>temp_vec);

	//添加第一局演讲选手
	void First_add_speaker();

	//文件为空的标志
	bool file_NULL;

	
	
	//展示菜单
	void show_menu();

	//开始第一场比赛
	void first_game();

	//开始第二场比赛
	void second_game();

	//开始演讲比赛
	void Start_Speech();

	//查看比赛记录
	void Show_Game_Record();

	//清空比赛记录
	void Delete_Game_Record();

	//退出系统
	void exit_system();

	//析构函数
	~SpeechManager();
};