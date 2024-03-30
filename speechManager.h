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
	//��ʼ��
	void initspeech_system();

	//���캯��
	SpeechManager();

	//��һ�ֱ�����Ա���
	vector<int>v_first;

	//�ڶ��ֱ���
	vector<int>v_second;

	//����
	vector<int>v_victory;

	//�������
	map<int, Speaker>m_speaker;

	//�����ɼ�
	vector<double>temp_v_score;

	//��������
	int index;

	//С����
	void group_min_game(int game_num, int did,vector<int>temp_vec);

	//��ӵ�һ���ݽ�ѡ��
	void First_add_speaker();

	//�ļ�Ϊ�յı�־
	bool file_NULL;

	
	
	//չʾ�˵�
	void show_menu();

	//��ʼ��һ������
	void first_game();

	//��ʼ�ڶ�������
	void second_game();

	//��ʼ�ݽ�����
	void Start_Speech();

	//�鿴������¼
	void Show_Game_Record();

	//��ձ�����¼
	void Delete_Game_Record();

	//�˳�ϵͳ
	void exit_system();

	//��������
	~SpeechManager();
};