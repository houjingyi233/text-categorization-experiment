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
const int K=100;
set<string> words;
vector<string> files;
map<int,string> dict;
int maxlength;
int nums=0,tot=0;
string str;
struct Document
{
	int dis;
	int number;
	bool operator<(const Document&a) const  
    {  
        return a.dis<dis;  
    }  
}document[10000];
struct Mydict
{
	int weight;
	string strs; 	
	bool operator<(const Mydict&src) const
	{
    	return src.strs<strs;
	}
}mydict[100000];
set<Mydict> user[100000];
ofstream fout("result.txt");
set<string>::iterator its;
set<Mydict>::iterator set_it;
map<string,int>::iterator it1,it2;
priority_queue< Document,vector<Document>,less<Document> > knn_queue;
vector<int> results[38];
int countresults[38];
//小顶堆 
int fnumbers[38]=
{
56,6,7,6,2,3,
5,1,1,3,5,6,5,
3,1,3,2,4,2,3,
6,4,4,5,2,3,3,
3,3,6,3,4,2,9,
2,13,10,7,
/*
2227,240,263,235,83,105,
199,44,58,129,214,229,187,
122,42,114,65,166,94,118,
221,143,141,190,93,112,104,
104,111,250,111,150,95,375,
98,515,404,275,
*/
};
char *dictnames[38]=
{
	"D:\\足球.txt","D:\\篮球.txt","D:\\排球.txt","D:\\网球.txt","D:\\手球.txt","D:\\垒球.txt","D:\\曲棍球.txt",
	"D:\\橄榄球.txt","D:\\水球.txt","D:\\棒球.txt","D:\\高尔夫.txt","D:\\乒乓.txt","D:\\羽毛球.txt","D:\\台球.txt",
	"D:\\壁球.txt","D:\\棋牌.txt","D:\\游泳.txt","D:\\跳水.txt","D:\\赛车.txt","D:\\自行车.txt","D:\\体操.txt",
	"D:\\田径.txt","D:\\武术.txt","D:\\拳击.txt","D:\\摔跤.txt","D:\\柔道跆拳道.txt","D:\\举重.txt","D:\\击剑.txt",
	"D:\\马术.txt","D:\\射击射箭.txt","D:\\赛艇与皮划艇.txt","D:\\帆船帆板.txt","D:\\铁人三项和现代五项.txt",
	"D:\\冰雪项目.txt","D:\\登山.txt","D:\\奥运.txt","D:\\亚运.txt","D:\\全运.txt",
};
char *filepaths1[38]=
{
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
char *filepaths2[38]=
{
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
	
void getfiles(string path,string exd,vector<string>& files)
{
	long hFile=0;
	struct _finddata_t fileinfo;
	string pathName, exdName;
	if(0!=strcmp(exd.c_str(),""))
	{
		exdName="\\*."+exd;
	}
	else
	{
		exdName="\\*";
	}
	if((hFile=_findfirst(pathName.assign(path).append(exdName).c_str(),&fileinfo))!=-1)
	{
		do
		{
			if((fileinfo.attrib& _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					getfiles( pathName.assign(path).append("\\").append(fileinfo.name),exd,files);
			}
			else
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile, &fileinfo)==0);
		_findclose(hFile);
	}
}

void read_text(char *filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	buf.clear();
	str.clear();
	char ch;
	while(buf&&ifile.get(ch)) buf.put(ch);
    str=buf.str();
	unsigned char c1,c2;
	int i=0;
	while(i<str.length())
	{
		if(i+1<str.length())
		{
			c1=(unsigned char)str[i];
			c2=(unsigned char)str[i+1];
			if(c1>=0xb0&&c1<=0xf7&&c2>=0xa1&&c2<=0xfe) i+=2;
			else str.erase(i,1);
		}
		else str.erase(i,1);
	}
	ifile.close();
}

void read_feature(char *pname)
{
	int j;
	ifstream infile(pname,ios::in);
	string sstr,ssstr;
	nums=0;
	int temp;
	int weight;
	while(getline(infile,sstr))
	{
		temp=0;
		weight=0;
		int i=0;
		while(sstr[i]!=' ') i++;
		ssstr=sstr.substr(0,i);
		while(sstr[i]==' ') i++;
		while(i<sstr.length())
		{	
			weight=weight*10+sstr[i]-'0';
			i++;
		}
		mydict[nums].strs=ssstr;
		mydict[nums].weight=1;
		nums++;
		int sleng=ssstr.length();
		if(sleng>maxlength) maxlength=ssstr.length();
		for(j=ssstr.length()-1;j>=0;j--)
		{
			temp+=ssstr[j];
			temp=temp*100;

		}
		dict[temp]=ssstr;
		ssstr.clear();
	}
	infile.close();
}

void pre_knn(char *dictname,char *filepath)
{
	nums=0;
	int i,j,temp;
	dict.clear();
	files.clear();
	read_feature(dictname);
	getfiles(filepath,"txt",files);
 	int size=files.size();
	for(int k=0;k<size;k++)
	{
		string strtemp=files[k];
		int len=strtemp.size();
		string c="\\";
		for(int m=0;m<len;m++)
		{
			if(strtemp[m]=='\\') 
			{
				strtemp.insert(m,c);
				m+=2;
				len=strtemp.size();
			}
		}
		char *f1name=(char *)strtemp.c_str();
		cout<<f1name<<endl;
		read_text(f1name);
		int pos=-1;
		i=j=str.length()-1;
		map<int,string>::iterator map_it; 
		while(i>=0)
		{
			int temp=0;
			int j=i;
			for(;j>=0;j--)
			{
				temp+=str[j];
				temp=temp*100;
				map_it=dict.find(temp);
				if(map_it!=dict.end()&&j!=0)
				{
					if(j%2==0) pos=j;
				}
				if(map_it!=dict.end()&&j==0)
				{
					for(int ii=0;ii<nums;ii++)
					{
						if(str.substr(0,i-j+1)==mydict[ii].strs)
						{
							user[tot].insert(mydict[ii]);
							break;
						}
					}
					i=-1;
					break;
				}
				if(map_it==dict.end()&&(i-j>=maxlength-1||j==0))
				{
					if(pos==-1)
					{
						i-=2;
						break;

					}
					else
					{
						for(int ii=0;ii<nums;ii++)
						{
							if(str.substr(pos,i-pos+1)==mydict[ii].strs)
							{
								user[tot].insert(mydict[ii]);
								break;
							}
						}
						i=pos-1;
						pos=-1;
						break;
					}
				}
			}
		}
		tot++;
	} 	
}

void read_dict(char *pname)
{
	int j;
	dict.clear(); 
	ifstream infile(pname, ios::in);
	string sstr;
	int temp;
	while(getline(infile,sstr))
	{
		temp=0;
		int sleng=sstr.length();
		if(sleng>maxlength) maxlength=sstr.length();
		for(j=sstr.length()-1;j>=0;j--)
		{
			temp+=sstr[j];
			temp=temp*100;

		}
		dict[temp]=sstr;
		sstr.clear();
	}
	infile.close();
}

void count_dis(int i)
{
	int temp=0;
	for(its=words.begin();its!=words.end();its++)
	{
		for(set_it=user[i].begin();set_it!=user[i].end();set_it++)
		{
			if((*its)==(*set_it).strs)
			{
				temp+=(*set_it).weight;
			}
		}
	}
	document[i].dis=temp;
	document[i].number=i;
	if(knn_queue.size()<K) knn_queue.push(document[i]);
	else if(document[i].dis>knn_queue.top().dis) 
	{
		knn_queue.pop();
		knn_queue.push(document[i]);
	}
}

void solve(int tempnum)
{
	int adjust=1;
	int interval=1;
	int categorys[38];
	for(int i=0;i<38;i++) categorys[i]=0;
	while(!knn_queue.empty())
	{
		int t=knn_queue.top().number;
		knn_queue.pop();
		if(t<2227) categorys[0]+=adjust;
		//足球 
		if(t>=2227&&t<2467) categorys[1]+=adjust;
		//篮球 
		if(t>=2467&&t<2730) categorys[2]+=adjust;
		//排球 
		if(t>=2730&&t<2965) categorys[3]+=adjust;
		//网球 
	//	if(t>=2965&&t<3048) categorys[4]+=adjust;
	//	if(t>=3048&&t<3153) categorys[5]+=adjust;
	//	if(t>=3153&&t<3352) categorys[6]+=adjust;
	//	if(t>=3352&&t<3396) categorys[7]+=adjust;
	//	if(t>=3396&&t<3454) categorys[8]+=adjust;
		if(t>=2965&&t<3094) categorys[9]+=adjust;
		//棒球 
		if(t>=3094&&t<3308) categorys[10]+=adjust;
		//高尔夫 
		if(t>=3308&&t<3537) categorys[11]+=adjust;
		//乒乓 
		if(t>=3537&&t<3724) categorys[12]+=adjust;
		//羽毛球 
		if(t>=3724&&t<3846) categorys[13]+=adjust;
		//台球 
	//	if(t>=3846&&t<4377) categorys[14]+=adjust;
		if(t>=3846&&t<3960) categorys[15]+=adjust;
		if(t>=3960&&t<4025) categorys[16]+=adjust;
		if(t>=4025&&t<4191) categorys[17]+=adjust;
		if(t>=4191&&t<4285) categorys[18]+=adjust;
		if(t>=4285&&t<4403) categorys[19]+=adjust;
		if(t>=4403&&t<4624) categorys[20]+=adjust;
		if(t>=4624&&t<4767) categorys[21]+=adjust;
		if(t>=4767&&t<4908) categorys[22]+=adjust;
		if(t>=4908&&t<5098) categorys[23]+=adjust;
	//	if(t>=5629&&t<5722) categorys[24]+=adjust;
	//	if(t>=5722&&t<5834) categorys[25]+=adjust;
	//	if(t>=5834&&t<5938) categorys[26]+=adjust;
		if(t>=5098&&t<5202) categorys[27]+=adjust;
	//	if(t>=6042&&t<6153) categorys[28]+=adjust;
		if(t>=5202&&t<5452) categorys[29]+=adjust;
	//	if(t>=6403&&t<6514) categorys[30]+=adjust;
	//	if(t>=6514&&t<6664) categorys[31]+=adjust;
		if(t>=5452&&t<5547) categorys[32]+=adjust;
		if(t>=5547&&t<5922) categorys[33]+=adjust;
	//	if(t>=7134&&t<7232) categorys[34]+=adjust;
	//	if(t>=7232&&t<7747) categorys[35]+=adjust;
	//	if(t>=7747&&t<8151) categorys[36]+=adjust;
	//	if(t>=8151) categorys[37]+=adjust;
		adjust+=interval;
		interval++;	
	} 
	/*
	categorys[37]=0;
	categorys[36]=0;
	categorys[35]=0;
	categorys[34]=0;
	categorys[31]=0;
	categorys[30]=0;
	categorys[28]=0;
	categorys[26]=0;
	categorys[25]=0;
	categorys[24]=0;
	categorys[14]=0;
	categorys[8]=0;
	categorys[7]=0;
	categorys[6]=0;
	categorys[5]=0;
	categorys[4]=0;
	*/
	for(int i=0;i<38;i++)
	{
		categorys[i]=categorys[i]*10000/fnumbers[i];
	}
	int maxelement=0,maxpos;
	for(int i=0;i<38;i++)
	{
		if(categorys[i]>maxelement) 
		{
			maxelement=categorys[i];
			maxpos=i;
		}
	}
	results[tempnum].push_back(maxpos);
	countresults[maxpos]++;
}

void train(char *filepath,int tempnum)
{
	int i,j;
	files.clear();
	getfiles(filepath,"txt",files);
 	int size=files.size();
	for(int k=0;k<size;k++)
	{
		string strtemp=files[k];
		int len=strtemp.size();
		string c="\\";
		for(int m=0;m<len;m++)
		{
			if(strtemp[m]=='\\') 
			{
				strtemp.insert(m,c);
				m+=2;
				len=strtemp.size();
			}
		}
		char *f1name=(char *)strtemp.c_str();
		fout<<f1name<<endl;
		cout<<"正在处理："<<f1name<<endl; 
		read_text(f1name);
		int pos=-1;
		i=j=str.length()-1;
		map<int,string>::iterator map_it;
		words.clear(); 
		while(!knn_queue.empty()) knn_queue.pop();
		while(i>=0)
		{
			int temp=0;
			int j=i;
			for(;j>=0;j--)
			{
				temp+=str[j];
				temp=temp*100;
				map_it=dict.find(temp);
				if(map_it!=dict.end()&&j!=0)
				{
					if(j%2==0) pos=j;
				}
				if(map_it!=dict.end()&&j==0)
				{
					words.insert(str.substr(0,i-j+1));
					i=-1;
					break;
				}
				if(map_it==dict.end()&&(i-j>=maxlength-1||j==0))
				{
					if(pos==-1)
					{
						i-=2;
						break;
					}
					else
					{
						words.insert(str.substr(pos,i-pos+1));
						i=pos-1;
						pos=-1;
						break;
					}
				}
			}
		}
		for(int ii=0;ii<tot;ii++) count_dis(ii);
		solve(tempnum);
	} 	
}

int main()
{
	char *filepath,*dictname;
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			dictname=dictnames[i];
			filepath=filepaths1[i];
			pre_knn(dictname,filepath);
		}
	}
	read_dict("词典.txt");
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			filepath=filepaths2[i];
			train(filepath,i);
		}
	}
	for(int i=0;i<38;i++)
	{
		if(i!=37&&i!=36&&i!=35&&i!=34&&i!=31&&i!=30&&i!=28&&i!=26&&i!=25&&i!=24&&i!=14&&i!=8&&i!=7&&i!=6&&i!=5&&i!=4)
		{
			cout<<i<<endl;
			fout<<i<<endl;
			int temps=0;
			for(int j=0;j<results[i].size();j++)
			{
				if(results[i][j]==i) temps++;
			}
			double tt=temps/countresults[i];
			cout<<temps<<" "<<countresults[i]<<" "<<tt<<endl;
			fout<<temps<<" "<<countresults[i]<<" "<<tt<<endl;
		}
	}
	fout.close();
	return 0;
}
