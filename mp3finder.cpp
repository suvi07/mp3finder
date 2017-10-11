//Mp3 finder
//Author: Suvrat Sanson

#include<iostream>
#include<dirent.h>     
#include<string>
#include<string.h>
#include<vector>    
using namespace std;
class mp3file{
    private:
    string fp;
    string fn;
    public:
    string show(){
    return fp;
    }
    string showf(){
    return fn;
    } 
    mp3file(string filename,string path){
    fn=filename;       
    fp=path;
        
    }   
};
vector<mp3file> list;
class dirfile{
    public:
    DIR *direc;           
    struct dirent *ent;
    dirfile(string strin){
    direc=opendir(strin.c_str());
    }
    bool isDir(){
    if(ent->d_type==4)
    return true;
    else 
    return false;
    }
    bool isMp3(){
    if(ent->d_type==8){
    string temp;
    for(int i=strlen(ent->d_name)-4;i<strlen(ent->d_name);i++)
    temp.push_back(ent->d_name[i]);
    if(temp==".mp3")
    return true;
    else
    return false;
    }
    else
    return false;                   
    }   
};
void mp3find(string strin){
    dirfile d(strin);
    if(d.direc!=NULL){
    while((d.ent=readdir(d.direc))!=NULL){
    if(strcmp(d.ent->d_name,".")==0 || strcmp(d.ent->d_name,"..")==0 || d.ent->d_name[0]=='.')            
    continue;
    if(d.isDir()){                                                                                        
    string temp(d.ent->d_name);
    temp=strin+"/"+temp; 
    mp3find(temp);
            }
    if(d.isMp3()){                                                                                        
    mp3file m((string)d.ent->d_name,strin);
                
    list.push_back(m);                                      
            }    
        }
    closedir(d.direc);
    }
    else
    cout<<"Couldn't open the directory "<<strin<<endl;
}
int main(){
    string path;
    cout<<"Enter the path: "<<endl;
    cin>>path;
    mp3find(path);
    for(int i=0;i<list.size();i++)
    cout<<list[i].showf()<<"\t"<<list[i].show()<<endl;   
    return 0;
}
