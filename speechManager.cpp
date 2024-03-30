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

//���캯��
SpeechManager::SpeechManager() {
	//��ʼ��
	this->initspeech_system();


}

//��ʼ��
void SpeechManager::initspeech_system() {
	//��֤����Ϊ��
	this->v_first.clear();
	this->v_second.clear();
	this->v_victory.clear();
	this->m_speaker.clear();
	//���ñ���Ϊ��һ��
	this->index = 1;
}

//���ӵ�һ���ݽ�ѡ��
void SpeechManager::First_add_speaker() {
	string add_name = "ABCDEFGHIJKL";
	for (int i = 0; i < add_name.size(); i++) {
		string temp_name = "ѡ��";
		temp_name += add_name[i];

		Speaker sp;
		sp.m_Name = temp_name;

		for (int j = 0; j < 2; j++) {
			sp.m_score[j] = 0;
		}

		//�������
		this->m_speaker.insert(make_pair(10001 + i, sp));
		//���µ�һ�ֱ������ݽ��߱��
		this->v_first.push_back(10001 + i);
	}
}

//С����
void SpeechManager::group_min_game(int game_num, int did, vector<int>temp_vec) {
	cout << endl << "��" << this->index << "��������" << game_num + 1 << "С�������ʼ��" << endl;
	Sleep(500);
	//��ձ����ɼ�
	this->temp_v_score.clear();
	int temp_score[10];
	for (int i = did; i < did + 6; i++) {
		cout << endl;
		vector<int>::iterator itv = temp_vec.begin();
		map<int, Speaker>::iterator it = m_speaker.find(*(itv + i));
		cout << (*it).first << "��" << (*it).second.m_Name << "�����ݽ���..." << endl;
		Sleep(1000);
		int all_score = 0;
		for (int k = 0; k < 10; k++) {
			temp_score[k] = rand() % 100 + 1;
			cout << "����" << k + 1 << "����" << temp_score[k] << "��" << " ";
			all_score += temp_score[k];
			Sleep(50);
			if (k == 4) {
				cout << endl;
			}
		}
		cout << endl;
		sort(temp_score, temp_score + 10);
		all_score = all_score - temp_score[0] - temp_score[9];
		cout << "���շ�Ϊ(ȥ����߷ֺ���ͷ�)��" << all_score * 1.0 / 8 << endl;
		//�������
		(*it).second.m_score[this->index - 1] = double(all_score * 1.0 / 8);
		this->temp_v_score.push_back(double((all_score * 1.0) / 8));
	}
}

//��һ������
void SpeechManager::first_game() {
	cout << "��" << this->index << "������ѡ�����ڷ�����..." << endl;
	//_sleep(2000
	Sleep(1000);
	//1����ǩ
	srand((unsigned int)time(NULL));
	random_shuffle(this->v_first.begin(), this->v_first.end());
	cout << "����ɹ�!" << endl;
	Sleep(500);
	cout << "��һ�����ѡ��:" << endl;
	for_each(this->v_first.begin(), this->v_first.begin() + 6, my_print());
	Sleep(1000);
	cout << endl << "�ڶ������ѡ��:" << endl;
	for_each(this->v_first.end() - 6, this->v_first.end(), my_print());
	Sleep(500);
	cout << endl;
	cout << "------------- ��" << this->index << "����ʽ������ʼ��------------- " << endl;
	//2������
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
	cout << "------------- ��" << this->index << "�ֱ�����ʽ������------------- " << endl;

	//3����ʾ�������
		//�Է�������
	sort(temp_v_score.begin(), temp_v_score.end(), my_sort_d());
	cout << endl;
	cout << "��ϲ����6λѡ�ֽ�����" << endl;
	for (int o = 0; o < 6; o++) {
		map<int, Speaker>::iterator itm_s = find_if(this->m_speaker.begin(), this->m_speaker.end(), my_map_find_if(temp_v_score[o]));
		cout << (*itm_s).first << "��ѡ��" << (*itm_s).second.m_Name << " ����Ϊ" << (*itm_s).second.m_score[this->index - 1] << endl;
		//���µڶ��������ı���ѡ��
		this->v_second.push_back((*itm_s).first);
	}
	Sleep(1000);
	cout << endl;
	this->index++;
}

//�ڶ�������
void SpeechManager::second_game() {
	//1����ǩ
	cout << "��" << this->index << "������ѡ�����ڷ�����..." << endl;
	Sleep(1000);
	srand((unsigned int)time(NULL));
	random_shuffle(this->v_second.begin(), this->v_second.end());
	cout << "����ɹ�!" << endl;
	Sleep(500);
	cout << "��һС���ԱΪ��" << endl;
	for_each(this->v_second.begin(), this->v_second.end(), my_print());
	cout << endl;
	cout << "------------- ��" << this->index << "����ʽ������ʼ��------------- " << endl;
	//2������
	this->group_min_game(0, 0, this->v_second);
	Sleep(1000);
	cout << endl;
	cout << "------------- ��" << this->index << "�ֱ�����ʽ������------------- " << endl;

	//3����ʾ���ս��
	sort(temp_v_score.begin(), temp_v_score.end(), my_sort_d());
	for_each(temp_v_score.begin(), temp_v_score.end(), my_print_d());
	cout << endl;
	cout << "��ϲ������λѡ�ֽ�����" << endl;
	for (int i = 0; i < 3; i++) {
		map<int, Speaker>::iterator it_m = find_if(this->m_speaker.begin(), this->m_speaker.end(), my_map_find_if_if(temp_v_score[i]));
		cout << "��" << i + 1 << "����" << (*it_m).first << "��ѡ��" << (*it_m).second.m_Name << " ����Ϊ��" << (*it_m).second.m_score[this->index - 1] << endl;
	}
	//4���������
	ofstream ofs;
	ofs.open("D:\\Users\\15022\\source\\repos\\�ݽ��������̹���ϵͳ\\�ݽ��������̹���ϵͳ\\ѡ�ֳɼ�.csv", ios::out | ios::app);
	if (!ofs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
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


//չʾ�˵�
void SpeechManager::show_menu() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//��ʼ�ݽ�����
void SpeechManager::Start_Speech() {
	this->First_add_speaker();
	this->first_game();
	this->second_game();
}

//�鿴�����¼
void SpeechManager::Show_Game_Record() {
	this->m_speaker.clear();
	ifstream ifs;
	ifs.open("D:\\Users\\15022\\source\\repos\\�ݽ��������̹���ϵͳ\\�ݽ��������̹���ϵͳ\\ѡ�ֳɼ�.csv", ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
	}
	char c;
	//while ((c = ifs.get()) != EOF) {
	//	this->m_speaker.insert(make_pair()
	//}

	ifs.close();
}

//��ձ�����¼
void SpeechManager::Delete_Game_Record() {

}

//�˳�ϵͳd
void SpeechManager::exit_system() {
	cout << "��ӭ�´�ʹ��" << endl;
}

//��������
SpeechManager::~SpeechManager() {

}