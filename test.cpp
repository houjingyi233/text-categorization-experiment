#include<set>
#include<map> 
#include<io.h>
#include<queue>  
#include<vector>
#include<string>  
#include<iomanip>    
#include<fstream>
#include<sstream>
#include<iostream>  
using namespace std;
string str;
int maxlength;
//max length of words in dict
int feature_nums = 0, tot = 0;
//nums of feature words 
//nums of known articles
const int K = 15;
//set k in KNN
vector<string> files;
//store file names
map<int, string> dict;
//store dict
map<string, int> words;
//store words in to be classified
struct Distance
{
	int dis;
	int attribute;
	bool operator<(const Distance&a) const
	{
		return a.dis<dis;
	}
}distances[10000];
//store distances between known articles and unknown articles
string featureword[100000];
//store feature words
map<string, int> articles[100000];
//store feature words and occurrences in each known articles
priority_queue< Distance, vector<Distance>, less<Distance> > knn_queue;
vector< pair<string, int> > words_result;
struct Articles_result
{
	vector< pair<string, int> > article_words;
	int attribute;
}articles_result[100000];
ofstream fout("D:\\result.txt");
//dict files for each classification
char *dictnames[39] =
{
	"none","D:\\足球.txt","D:\\篮球.txt","D:\\排球.txt","D:\\网球.txt","D:\\手球.txt","D:\\垒球.txt","D:\\曲棍球.txt",
	"D:\\橄榄球.txt","D:\\水球.txt","D:\\棒球.txt","D:\\高尔夫.txt","D:\\乒乓.txt","D:\\羽毛球.txt","D:\\台球.txt",
	"D:\\壁球.txt","D:\\棋牌.txt","D:\\游泳.txt","D:\\跳水.txt","D:\\赛车.txt","D:\\自行车.txt","D:\\体操.txt",
	"D:\\田径.txt","D:\\武术.txt","D:\\拳击.txt","D:\\摔跤.txt","D:\\柔道跆拳道.txt","D:\\举重.txt","D:\\击剑.txt",
	"D:\\马术.txt","D:\\射击射箭.txt","D:\\赛艇与皮划艇.txt","D:\\帆船帆板.txt","D:\\铁人三项和现代五项.txt",
	"D:\\冰雪项目.txt","D:\\登山.txt","D:\\奥运.txt","D:\\亚运.txt","D:\\全运.txt",
};
//training files' catalog
char *training_filepaths[39] =
{
	"none",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\01足球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\02篮球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\03排球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\04网球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\05手球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\06垒球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\07曲棍球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\08橄榄球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\09水球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\10棒球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\11高尔夫",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\12乒乓",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\13羽毛球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\14台球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\15壁球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\16棋牌",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\17游泳",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\18跳水",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\19赛车",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\20自行车",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\21体操",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\22田径",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\23武术",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\24拳击",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\25摔跤",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\26柔道跆拳道",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\27举重",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\28击剑",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\29马术",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\30射击射箭",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\31赛艇与皮划艇",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\32帆船帆板",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\33铁人三项和现代五项",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\34冰雪项目",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\35登山",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\36奥运",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\37亚运",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类训练文档\\38全运",
};
//test files' catalog
char *test_filepaths[39] =
{
	"none",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\01足球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\02篮球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\03排球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\04网球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\05手球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\06垒球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\07曲棍球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\08橄榄球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\09水球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\10棒球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\11高尔夫",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\12乒乓",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\13羽毛球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\14台球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\15壁球",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\16棋牌",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\17游泳",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\18跳水",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\19赛车",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\20自行车",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\21体操",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\22田径",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\23武术",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\24拳击",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\25摔跤",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\26柔道跆拳道",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\27举重",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\28击剑",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\29马术",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\30射击射箭",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\31赛艇与皮划艇",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\32帆船帆板",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\33铁人三项和现代五项",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\34冰雪项目",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\35登山",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\36奥运",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\37亚运",
	"C:\\Users\\Administrator\\Desktop\\实验4\\体育领域\\体育分类测试文档\\38全运",
};

int cmp(const pair<string, int> &x, const pair<string, int> &y)
{
	return x.second > y.second;
}

void sort_by_value(map<string, int> &t_map, vector< pair<string, int> > &t_vec)
{
	for (map<string, int>::iterator iter = t_map.begin(); iter != t_map.end(); iter++)
	{
		t_vec.push_back(make_pair(iter->first, iter->second));
	}
	sort(t_vec.begin(), t_vec.end(), cmp);
}

//store all files in path with exd extension in vector
void getfiles(string path, string exd, vector<string>& files)
{
	long hFile = 0;
	struct _finddata_t fileinfo;
	string pathName, exdName;
	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}
	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib& _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getfiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//read text in file and store chinese character in str
void read_text(char *textname)
{
	ifstream infile(textname);
	ostringstream buf;
	buf.clear();
	str.clear();
	char ch;
	while (buf&&infile.get(ch)) buf.put(ch);
	str = buf.str();
	unsigned char c1, c2;
	int i = 0;
	while (i<str.length())
	{
		if (i + 1<str.length())
		{
			c1 = (unsigned char)str[i];
			c2 = (unsigned char)str[i + 1];
			if (c1 >= 0xb0 && c1 <= 0xf7 && c2 >= 0xa1 && c2 <= 0xfe) i += 2;
			//in GB2312 a chinese character is represented as two bytes
			//high bytes from 0xB0 to 0xF7,low bytes from 0xA1 to 0xFE
			else str.erase(i, 1);
		}
		else str.erase(i, 1);
	}
	infile.close();
}

//read feature word in file,store in map and string
void read_feature(char *featurename)
{
	ifstream infile(featurename, ios::in);
	feature_nums = 0;
	while (getline(infile, str))
	{
		int temp = 0;
		featureword[feature_nums]= str;
		int len = str.length();
		if (len>maxlength) maxlength = str.length();
		for (int i = str.length() - 1; i >= 0; i--)
		{
			temp += str[i];
			temp = temp * 100;
		}
		dict[temp] = str;
		str.clear();
		feature_nums++;
	}
	infile.close();
}

//record keywords in each training distances 
void pre_knn(char *dictname, char *filepath,int attribute)
{
	dict.clear();
	files.clear();
	feature_nums = 0;
	read_feature(dictname);
	getfiles(filepath, "txt", files);
	int size = files.size();
	for (int k = 0; k<size; k++)
	{
		//deal with escape character '\'
		string tempstr = files[k];
		int len = tempstr.size();
		string backslash = "\\";
		for (int m = 0; m<len; m++)
		{
			if (tempstr[m] == '\\')
			{
				tempstr.insert(m, backslash);
				m += 2;
				len = tempstr.size();
			}
		}
		char *fname = (char *)tempstr.c_str();
		cout << fname << endl;
		read_text(fname);
		int pos = -1;
		//pos is for record matching position
		int i = str.length() - 1;
		map<int, string>::iterator map_it;
		while (i >= 0)
		{
			int j = i;
			int temp = 0;
			for (; j >= 0; j--)
			{
				temp += str[j];
				temp = temp * 100;
				map_it = dict.find(temp);
				if (map_it != dict.end() && j != 0)
				{
					if (j % 2 == 0) pos = j;
					//record matching position
				}
				if (map_it != dict.end() && j == 0)
				{
					for (int k = 0; k<feature_nums; k++)
					{
						if (str.substr(0, i - j + 1) == featureword[k])
						{
							if (articles[tot].find(str.substr(0, i + 1)) == articles[tot].end())
							{
								articles[tot][str.substr(0, i + 1)] = 1;
							}
							else
							{
								articles[tot][str.substr(0, i + 1)]++;
							}
							break;
						}
					}
					i = -1;
					break;
				}
				if (map_it == dict.end() && (i - j >= maxlength - 1 || j == 0))
				{
					if (pos == -1)
					{
						i -= 2;
						break;
					}
					//match failed,skip this character
					else
					{
						for (int k = 0; k<feature_nums; k++)
						{
							if (str.substr(pos, i - pos + 1) == featureword[k])
							{
								if (articles[tot].find(str.substr(pos, i - pos + 1)) == articles[tot].end())
								{
									articles[tot][str.substr(pos, i - pos + 1)] = 1;
								}
								else
								{
									articles[tot][str.substr(pos, i - pos + 1)]++;
								}
							}
						}
						i = pos - 1;
						pos = -1;
						break;
					}
					//use pos recorded last time
				}
			}
		}
		sort_by_value(articles[tot], articles_result[tot].article_words);
		articles_result[tot].attribute = attribute;
		tot++;
	}
}

//read terms in file ,compute hash value and store them in map
void read_dict(char *dictname)
{
	ifstream infile(dictname, ios::in);
	dict.clear();
	string dict_str;
	int temp;
	while (getline(infile, dict_str))
	{
		temp = 0;
		int len = dict_str.length();
		if (len>maxlength) maxlength = dict_str.length();
		for (int i = dict_str.length() - 1; i >= 0; i--)
		{
			temp += dict_str[i];
			temp = temp * 100;

		}
		dict[temp] = dict_str;
		dict_str.clear();
	}
	infile.close();
}

//count distances between two articles based on cosine similarity
void count_dis(int i)
{
	int temp1, temp2, temp3;
	temp1 = temp2 = temp3 = 0;
	for (int j = 0; j < articles_result[i].article_words.size(); j++)
	{
		temp1 += articles_result[i].article_words[j].second*articles_result[i].article_words[j].second;
	}
	for(int k = 0; k < words_result.size(); k++)
	{
		temp2 += words_result[k].second*words_result[k].second;
	}
	for (int j = 0; j <articles_result[i].article_words.size(); j++)
	{
		for (int k = 0; k < words_result.size(); k++)
		{
			if (articles_result[i].article_words[j].first == words_result[k].first)
			{
				temp3 += articles_result[i].article_words[j].second*words_result[k].second;
				break;
			}
		}
	}
	if (temp1 != 0 && temp2 != 0)
	{
		distances[i].dis = 100000*temp3*temp3 / temp1 / temp2;
	}
	else
	{
		distances[i].dis = 0;
	}
	distances[i].attribute = articles_result[i].attribute;
	if (knn_queue.size()<K) knn_queue.push(distances[i]);
	else if (distances[i].dis>knn_queue.top().dis)
	{
		knn_queue.pop();
		knn_queue.push(distances[i]);
	}
}

//count the number of each class label in k nearest neighbor  
//the class label with the largest frequency 
//is selected as the class label of the unknown sample
void select_category()
{
	int categorys[39];
	for (int i = 1; i<39; i++) categorys[i] = 0;
	while (!knn_queue.empty())
	{
		int t = knn_queue.top().attribute;
		cout << t << endl;
		knn_queue.pop();
		categorys[t] += 1;
	}
	int maxelement = 0, pos;
	for (int i = 1; i<39; i++)
	{
		if (categorys[i]>maxelement)
		{
			maxelement = categorys[i];
			pos = i;
		}
	}
	cout << "this acticle is classified in:" << pos << endl;
}

//segmentation acticles in directory
void txt_segmentation(char *filepath)
{
	files.clear();
	getfiles(filepath, "txt", files);
	int size = files.size();
	for (int k = 0; k<size; k++)
	{
		//deal with escape character '\'
		string tempstr = files[k];
		int len = tempstr.size();
		string backslash = "\\";
		for (int m = 0; m<len; m++)
		{
			if (tempstr[m] == '\\')
			{
				tempstr.insert(m, backslash);
				m += 2;
				len = tempstr.size();
			}
		}
		char *fname = (char *)tempstr.c_str();
		fout << fname << endl;
		cout << "judging the category of this article：" << fname << endl;
		read_text(fname);
		int pos = -1;
		int i = str.length() - 1;
		map<int, string>::iterator map_it;
		words.clear();
		//store all terms 
		while (!knn_queue.empty()) knn_queue.pop();
		while (i >= 0)
		{
			int j = i;
			int temp = 0;
			for (; j >= 0; j--)
			{
				temp += str[j];
				temp = temp * 100;
				map_it = dict.find(temp);
				if (map_it != dict.end() && j != 0)
				{
					if (j % 2 == 0) pos = j;
				}
				if (map_it != dict.end() && j == 0)
				{
					if (words.find(str.substr(0, i + 1)) == words.end())
					{
						words[str.substr(0, i + 1)] = 1;
					}
					else
					{
						words[str.substr(0, i + 1)]++;
					}
					i = -1;
					break;
				}
				if (map_it == dict.end() && (i - j >= maxlength - 1 || j == 0))
				{
					if (pos == -1)
					{
						i -= 2;
						break;
					}
					else
					{
						if (words.find(str.substr(pos, i - pos + 1)) == words.end())
						{
							words[str.substr(pos, i - pos + 1)] = 1;
						}
						else
						{
							words[str.substr(pos, i - pos + 1)]++;
						}
						i = pos - 1;
						pos = -1;
						break;
					}
				}
			}
		}
		sort_by_value(words,words_result);
		for (int k = 0; k<tot; k++) count_dis(k);
		//count dis between all known article
		select_category();
	}
}

int main()
{
	char *filepath, *dictname;
	for (int i = 1; i<39; i++)
	{
		dictname = dictnames[i];
		filepath = training_filepaths[i];
		pre_knn(dictname, filepath,i);
	}
	read_dict("D:\\词典.txt");
	for (int i = 1; i<39; i++)
	{
		filepath = test_filepaths[i];
		txt_segmentation(filepath);
	}
	fout.close();
	system("pause");
	return 0;
}
