#include<iostream>
#include<fstream>
using namespace std; 
/*
打开pak文件 
--->表的大小  个数
表的内容 文件内容 

*/
struct fileList{
    int fileoff; //streamoff == long
    int fileSize;
    int fileNameSize;
    char fileName[20];
    friend ostream&operator<<(ostream&os,fileList&other){
    	os<<"文件偏移量"<<other.fileoff<<"文件大小"<<other.fileSize<<"文件名大小"<<other.fileNameSize<<"文件名"<<other.fileName<<endl; 
        return os;
	}
}fInfo[2]; //file struct array


int main(int argc,char* argv[]){
fstream srcfile;
srcfile.open("new.pak",ios::in|ios::binary);
//if(srcfile.is_open()){
//	cout<<"dakai";
//}
int listNum,listSize;
srcfile.read((char*)&listSize,4);
srcfile.read((char*)&listNum,4); 
cout<<listSize<<endl<<listNum<<endl;

for(int i=0;i<listNum;++i){
	
	srcfile.read((char*)&fInfo[i].fileoff,4);
	srcfile.read((char*)&fInfo[i].fileSize,4);
	srcfile.read((char*)&fInfo[i].fileNameSize,4);
	srcfile.read(fInfo[i].fileName,fInfo[i].fileNameSize);
    fInfo[i].fileName[fInfo[i].fileNameSize]='\0';
    
    cout<<fInfo[i];
}

//写入文件 
	fstream file[2];
	for(int i=0;i<2;++i){
		file[i].open(fInfo[i].fileName,ios::out|ios::binary);
		for(streamoff j=0;j<fInfo[i].fileSize;++j){
			file[i].put(srcfile.get());
		}
		file[i].close();
	}
	
srcfile.close();
cin.get();
return 0;	
} 
