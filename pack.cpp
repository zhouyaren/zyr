#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
char fileName[][10]={"1.txt","2.txt"};//define fiile name
struct fileList{
    streamoff fileoff; //streamoff == long
    streamoff fileSize;
    streamoff fileNameSize;
    char *fileName;
}file[2]; //file struct array


int main(int argc, char *argv[])
{
    int listnum=2,listsize=0;//excel head
    fstream srcFile[3];  //use to open file
    for(int i=0;i<2;++i){
        file[i].fileName = fileName[i];//fie name
        string s=fileName[0];
        file[i].fileNameSize=strlen(fileName[i]);//fie name size

        srcFile[i].open(fileName[i],ios::in|ios::binary);//open file

        srcFile[i].seekg(0,ios::end);//move file ptr to the end of file
        file[i].fileSize = srcFile[i].tellp();//p-->read  g-->write
        int a=srcFile[i].tellg();
        //int b=srcFile[1].tellp();
        listsize+=4+4+4+file[i].fileNameSize; //excel size sum
     //=listsize+=sizeof(file[i].fileoff)+sizeof(file[i].fileSize)+sizeof(file[i].fileNameSize)+file[i].fileNameSize;


    }
   //start to count fileoff
    for(int i=0;i<2;++i){
        if(i==0){ //the first file
            file[i].fileoff=8+listsize;
        }else{
           file[i].fileoff=file[i-1].fileoff+file[i-1].fileSize;//follow size
        }
    }


  //all struct is be write
  //start to write pak file
  srcFile[2].open("new.pak",ios::out|ios::binary); //create ,use binary
  srcFile[2].write((char*)&listsize,sizeof(int));//write listsize
  srcFile[2].write((char*)&listnum,sizeof(int));
  for(int i=0;i<2;++i){
      srcFile[2].write((char*)&file[i].fileoff,sizeof(int));
      srcFile[2].write((char*)&file[i].fileSize,sizeof(int));
      srcFile[2].write((char*)&file[i].fileNameSize,sizeof(int));
      srcFile[2].write(file[i].fileName,file[i].fileNameSize);
  }

//circle to write file content
  for(int i=0;i<2;i++){
      srcFile[i].seekp(0,ios::beg);
      //read write //fileSize
      for(streamoff j=0;j<file[j].fileSize;++j){
          //fgetc() fputc()
          srcFile[2].put(srcFile[j].get());//write
      }
      //txt dont have EOF character,binary have EOF

      srcFile[i].close();

  }

  srcFile[2].close();
  cin.get();
  return 0;

}

