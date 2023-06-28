#pragma execution_character_set("utf-8")
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "tqdm.hpp"

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

string ImagePath = ".\\ScreenShot";

vector<string> skilllist{ "攻击", "挑战者", "无伤", "怨恨", "死里逃生", "看破", "超会心",
"弱点特效", "力量解放", "精神抖擞", "会心击【属性】", "达人艺", "火属性攻击强化",
"水属性攻击强化", "冰属性攻击强化", "雷属性攻击强化", "龙属性攻击强化", "毒属性强化",
"麻痹属性强化", "睡眠属性强化", "爆破属性强化", "匠", "利刃", "弹丸节约", "刚刃打磨",
"心眼", "弹道强化", "钝器能手", "解放弓的蓄力阶段", "集中", "强化持续", "跑者", "体术",
"耐力急速回复", "防御性能", "防御强化", "攻击守势", "拔刀术【技】", "拔刀术【力】", "纳刀术",
"击晕术", "夺取耐力", "滑走强化", "吹笛名人", "炮术", "炮弹装填", "特殊射击强化", "通常弹・连射箭强化",
"贯穿弹・贯穿箭强化", "散弹・扩散箭强化", "装填扩充", "装填速度", "减轻后坐力", "抑制偏移", "速射强化",
"防御", "精灵加护", "体力回复量提升", "回复速度", "快吃", "耳塞", "风压耐性", "耐震", "泡沫之舞", "回避性能",
"回避距离提升", "火耐性", "水耐性", "冰耐性", "雷耐性", "龙耐性", "属性异常状态的耐性", "毒耐性", "麻痹耐性",
"睡眠耐性", "昏厥耐性", "泥雪耐性", "爆破异常状态的耐性", "植生学", "地质学", "破坏王", "捕获名人", "剥取名人",
"幸运", "砥石使用高速化", "炸弹客", "最爱蘑菇", "道具使用强化", "广域化", "满足感", "火场怪力", "不屈", "减轻胆怯",
"跳跃铁人", "剥取铁人", "饥饿耐性", "飞身跃入", "佯动", "骑乘名人", "霞皮的恩惠", "钢壳的恩惠", "炎鳞的恩惠",
"龙气活性", "翔虫使", "墙面移动", "逆袭", "高速变形", "鬼火缠", "风纹一致", "雷纹一致", "风雷合一", "气血",
"伏魔耗命", "激昂", "业铠【修罗】", "因祸得福", "狂龙症【蚀】", "坚如磐石", "偷袭", "巧击", "嘲讽防御",
"合气", "提供", "蓄力大师", "攻势", "零件改造", "打磨术【锐】", "刃鳞打磨", "走壁移动【翔】", "弱点特效【属性】",
"连击", "毅力", "迅之气息", "状态异常必定累积", "刚心", "累积时攻击强化", "狂化", "风绕", "粉尘绕", "寒气炼成", "龙气转换", "奋斗" ,"狂龙症【翔】","天衣无缝","气血觉醒"};

vector<Scalar> collower{ Scalar(156, 43, 46),Scalar(0,0,221),Scalar(40,100,46) };
vector<Scalar> colupper{ Scalar(180,255,255),Scalar(180,30,255),Scalar(70,255,255) };
vector<vector<string>> df1{ vector<string>{"序号","孔位","技能1","技能2","技能3"} };
vector<vector<string>> df2{ vector<string>{"序号","红光","识别错误"} };

// 创建一个tesseract引擎对象
static tesseract::TessBaseAPI api;
// 使用静态变量来保持引擎对象的生命周期，避免每次调用函数时都重新创建一个新的引擎对象

// 初始化tesseract引擎，指定数据文件目录和语言模型
static bool initialized = api.Init(".\\tessdata_fast", "mhr", tesseract::OEM_LSTM_ONLY);
// 使用静态变量来记录是否已经初始化过引擎，避免每次调用函数时都重新初始化引擎


bool checkcol(InputArray& src, int col) {
	Mat tmp, mask;
	cvtColor(src, tmp, COLOR_BGR2HSV);
	inRange(tmp, collower[col], colupper[col], mask);
	return countNonZero(mask);
}

// 定义一个函数，将二维vector输出为csv文件
void write_vector_to_csv(const vector<vector<string>>& vec, const string& filename)
{
	// 打开一个csv文件
	ofstream file(filename);
	file << "\xEF\xBB\xBF"; // UTF-8 BOM
	// 遍历二维vector
	for (auto& row : vec)
	{
		// 遍历每一行的元素
		for (auto& elem : row)
		{
			// 写入元素和逗号
			file << elem << ",";
		}
		// 写入换行符
		file << "\n";
	}

	// 关闭文件
	file.close();
}

string image_ocr(Mat img)
{

	// 调用图像处理函数，传入图像参数
	//Mat processed = image_preprocessing(img);
	Mat processed = img;

	// 设置图像数据
	api.SetImage((uchar*)img.data, img.size().width, img.size().height, img.channels(), img.step);

	// 设置白名单，只识别数字和字母
	//tess.SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	// 识别图像中的文字
	char* outText = api.GetUTF8Text();

	// 将识别结果转换为字符串
	string result = outText;

	// 释放内存
	delete[] outText;

	return result;
}

std::string rstrip(std::string s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
	return s;
}

bool inVector(const std::vector<string>& vec, string value) {
	return std::find(vec.begin(), vec.end(), value) != vec.end();
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	// 如果初始化失败，打印错误信息并返回空字符串
	if (initialized)
	{
		cerr << "Tesseract初始化失败" << endl;
		std::system("pause");
		exit(1);
	}
	// 设置psm模式为7，表示单行文本
	api.SetPageSegMode(tesseract::PSM_SINGLE_LINE);

	// 设置dpi为96，表示图像分辨率
	api.SetVariable("user_defined_dpi", "96");
	vector<fs::path> ImageList; // 定义图片列表
	for (auto& p : fs::directory_iterator(ImagePath)) // 遍历路径下的所有文件
	{
		if (p.is_regular_file() && p.path().has_extension()) // 如果是普通文件且有扩展名
		{
			ImageList.push_back(p.path()); // 将文件路径加入列表
		}
	}
	sort(ImageList.begin(), ImageList.end(), [](const fs::path& a, const fs::path& b) // 对列表进行排序
		{
			string sa = a.stem().string(); // 获取不带扩展名的文件名
			string sb = b.stem().string();
			return stoi(sa) < stoi(sb); // 将文件名转换为整数并比较大小
		});
	auto t = tq::tqdm(ImageList);
	int l = size(ImageList);
	int c = 0;
	for (const auto& p : t) {
		c++;
		t <<"[" +p.stem().string() + "/" <<l <<"]";
		//cout << p << endl;
		int yoffset = 0;
		string slot0 = "0";
		string slot1 = "0";
		string slot2 = "0";
		string skill1 = "";
		string skill2 = "";
		string skill3 = "";
		Mat tmp;
		Mat image = cv::imread(p.string(), cv::IMREAD_COLOR);
		cv::resize(image, image, cv::Size(1920, 1080), cv::INTER_LANCZOS4);
		//1.检测是否红色特效，红色则标记跳过
		if (checkcol(image(Rect(760, 230, 10, 90)), 0)) {
			df2.push_back(vector<string>{p.stem().string(), "1", "0"});
			continue;
		}
		//2.检测页数,检测顶部白色数字1/2
		if (checkcol(image(Rect(920, 235, 80, 30)), 1))
			yoffset = 37;
		//3.检测孔位部分的绿色，确认孔位是否增加
		//if (checkcol(image(Rect(1000, 280 + yoffset, 150, 20)), 2))
			//slot = "+";
		//3.分别检测3个孔位部分的绿色，确认当前孔位是否增加
		if (checkcol(image(Rect(1020, 280 + yoffset, 21, 20)), 2))
			slot0 = "1";
		if (checkcol(image(Rect(1063, 280 + yoffset, 21, 20)), 2))
			slot1 = "1";
		if (checkcol(image(Rect(1104, 280 + yoffset, 21, 20)), 2))
			slot2 = "1";
		//4.检测第一个技能是否存在，技能名，加减情况
		if (checkcol(image(Rect(805, 550 + yoffset, 235, 30 )), 1)) {
			cv::cvtColor(image(Rect(805, 550 + yoffset, 235, 30 )), tmp, cv::COLOR_BGR2GRAY);
			cv::threshold(tmp, tmp, 182, 255, cv::THRESH_BINARY_INV);
			//cv::imshow("测试",tmp);
			//waitKey(0);
			skill1 = rstrip(image_ocr(tmp));
			//cout << skill1 << endl;
			if (!inVector(skilllist, skill1)) {
				df2.push_back(vector<string>{p.stem().string(), "0", "1"});
				cv::imwrite(".\\wrong\\" + p.stem().string() + "_1.jpg", tmp);
				cv::imwrite(".\\WrongImageOutput\\" + p.stem().string() + ".jpg", image);
				continue;
			}if (checkcol(image(Rect(825, 590 + yoffset, 175, 25 )), 2))
				skill1 += "+";
			else
				skill1 += "-";
			//5.检测第二个技能是否存在，技能名，加减情况
			if (checkcol(image(Rect(805, 625 + yoffset, 235, 30 )), 1)) {
				cv::cvtColor(image(Rect(805, 625 + yoffset, 235, 30 )), tmp, cv::COLOR_BGR2GRAY);
				cv::threshold(tmp, tmp, 182, 255, cv::THRESH_BINARY_INV);
				skill2 = rstrip(image_ocr(tmp));
				if (!inVector(skilllist, skill2)) {
					df2.push_back(vector<string>{p.stem().string(), "0", "1"});
					cv::imwrite(".\\wrong\\" + p.stem().string() + "_2.jpg", tmp);
					cv::imwrite(".\\WrongImageOutput\\" + p.stem().string() + ".jpg", image);
					continue;
				}
				if (checkcol(image(Rect(825, 664 + yoffset, 175, 25 )), 2))
					skill2 += "+";
				else
					skill2 += "-";
				//5.检测第三个技能是否存在，技能名，加减情况
				if (checkcol(image(Rect(805, 702 + yoffset, 235, 30 )), 1)) {
					cv::cvtColor(image(Rect(805, 702 + yoffset, 235, 30 )), tmp, cv::COLOR_BGR2GRAY);
					cv::threshold(tmp, tmp, 182, 255, cv::THRESH_BINARY_INV);
					skill3 = rstrip(image_ocr(tmp));
					if (!inVector(skilllist, skill3)) {
						df2.push_back(vector<string>{p.stem().string(), "0", "1"});
						cv::imwrite(".\\wrong\\" + p.stem().string() + "_3.jpg", tmp);
						cv::imwrite(".\\WrongImageOutput\\" + p.stem().string() + ".jpg", image);
						continue;
					}if (checkcol(image(Rect(825, 742 + yoffset, 175, 25 )), 2))
						skill3 += "+";
					else
						skill3 += "-";
				}
			}
			df1.push_back(vector<string>{p.stem().string(), slot0 + "#" + slot1 + "#" + slot2,skill1,skill2,skill3});
		}
		else
		{
			skill1 = "";
			skill2 = "";
			skill3 = "";
			df1.push_back(vector<string>{p.stem().string(), slot0+"#"+slot1+"#"+slot2, skill1, skill2, skill3});
		}
	}
	write_vector_to_csv(df1,".\\result.csv");
	write_vector_to_csv(df2,".\\wrong.csv");
	std::cout << "\nFinish!" << endl;
	std::system("pause");
	return 0;
}