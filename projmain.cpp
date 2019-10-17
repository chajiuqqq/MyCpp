#include <iostream>
#include <string.h>
using namespace std;
//123
//456
class Pack{
	private:	
		char *dist;
		char* readFile(char* path);
		int write2File(char* content);
		void addSplit(char* content,char* split,int account);
		long getFileLength(FILE* fp);
	public:
		Pack(char* distPath){
			dist=new char[100];
			strcpy(dist,distPath);
		}	
		void copy2dist(char* srcPath);
		
};

void Pack::copy2dist(char *srcPath){
	char* fileContent=readFile(srcPath);
	char split[]={char(0xff),'\0'};
	addSplit(fileContent,split,8);
	write2File(fileContent); 
}

char* Pack::readFile(char* path){
	FILE* fp;
	if((fp=fopen(path,"rb"))==NULL){
		printf("read error");
		return nullptr;
	}
	long length=getFileLength(fp);	
	char* out=new char[length];
	fread(out,100,1,fp);
	return out;	
}

void Pack::addSplit(char* content,char* split,int amount){
	for(int i=0;i<amount;i++){
		strcat(content,split);
	}
}

int Pack::write2File(char* content){
	FILE* fw;
	if((fw=fopen(Pack::dist,"ab+"))==NULL){
		printf("复制失败！文件名%s\n",Pack::dist);
		return -1;
	}
	fwrite(content,strlen(content),1,fw);
	printf("复制成功！文件名%s\n",Pack::dist);
	return 0;
}

long Pack::getFileLength(FILE* fp){
	fseek(fp,0,2);
	long l=ftell(fp);
	fseek(fp,0,0);
	return l;
}
int main(int argc, char** argv) {
	char* s[]={"C:\\Users\\Alice\\Desktop\\zyy out\\1.txt","C:\\Users\\Alice\\Desktop\\zyy out\\2.txt","C:\\Users\\Alice\\Desktop\\zyy out\\3.txt"};
	char *dist="C:\\Users\\Alice\\Desktop\\zyy out\\xyz.dat";
	Pack p(dist);
	for(int i=0;i<3;i++){
		p.copy2dist(s[i]);
	}
	system("pause");
	return 0;
}
