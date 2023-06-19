#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

struct Node{
    Node *parent ;
    string dir ;
    map <string,Node*> Folders ;
    map <string,Node*> files ;
};

class Terminal11{
    
    public:
    vector <string> path ;
    string username ;
    Node* root ;
    Node* curr_dir ;
    
    Terminal11(Node* r,Node *curr){
        root = r ;
        curr_dir=curr ;
        username = curr->dir ;
        path.push_back(r->dir);
        path.push_back(curr_dir->dir);
    }
    
    void pwd(){
        Node * temp = root ;
        if(path.empty())
            {cout<<"/"; return ;}
        
        for(int i=0;i<path.size();i++){
            cout<<"/"<<path[i];
        }
      
    }
    
    void mkdir(string Folder_name){
        
        if((curr_dir->Folders).count(Folder_name)!=0) {
            cout<<"Folder Exists"<<endl;
        }
        else if((curr_dir->files).count(Folder_name)!=0){
            cout<<"File Exists"<<endl;
        }
        else{
            Node * n = new Node ;
            n->parent = curr_dir ;
            n->dir=Folder_name ;
            (curr_dir->Folders)[Folder_name]=n ;
        }
    }
    
    void touch(string file_name){
        if((curr_dir->Folders).count(file_name)!=0) {
            cout<<"Folder Exists"<<endl;
        }
        else if((curr_dir->files).count(file_name)!=0){
            cout<<"File Exists"<<endl;
        }
        else{
            Node * n = new Node ;
            n->parent = curr_dir ;
            n->dir=file_name ;
            (curr_dir->files)[file_name]=n ;
        }  
    }
    
    void rm(string name){
        
        if((curr_dir->Folders).count(name)!=0) {
          delete (curr_dir->Folders)[name];
          (curr_dir->Folders).erase(name);
        }
        
        else if((curr_dir->files).count(name)!=0) {
          delete (curr_dir->files)[name];
          (curr_dir->files).erase(name);
        }
        
        else {cout<<"Does not exist"<<endl;}
    }
    
    void cd(string name){
        
         if((curr_dir->Folders).count(name)!=0) {
          curr_dir=(curr_dir->Folders)[name];
          path.push_back(curr_dir->dir);
        }
        
        else {
            cout<<"Folder does not exist"<<endl;
        }
    }
    
    void ls (){
        
        for(auto i:(curr_dir->Folders)){
            cout<<i.first<<" ";
        }
        for(auto i:(curr_dir->files)){
            cout<<i.first<<" ";
        }
        cout<<endl;
    }
    
    void cd_prev(){
        
        if(curr_dir->parent==NULL) return ;
        curr_dir=curr_dir->parent ;
        path.pop_back();
    }
    
    void cd_home(){
        
        curr_dir=(root->Folders)[username];
        
        while(path.size()>2){
            path.pop_back();
        }
        
    }
};


int main() {
  
    string term;
    string username ;
  
    cin>>term ;
    cin>>username ;
   
    
    vector <string> history ;
    Node * root_par = new Node ;
    root_par->dir="/";
    root_par->parent = NULL ;
   
    Node * root = new Node ;
    root->dir = "home";
    root->parent = root_par;
    (root_par->Folders)["home"]=root ;
    
    Node * k = new Node ;
    k->dir = username;
    k->parent = root ;
    (root->Folders)[username]=k ;
    
    Terminal11 *m = new Terminal11(root,k);
    
    string command ;
    
    // for sh 
    if(term=="sh"){
        
        do{
            cout<<"$ ";
            string s="";
            cin>> command ;
            cout<<command;
            s+=command ;
            
            if(command=="pwd"){
                cout<<endl;
                m->pwd() ;
                cout<<endl;
            }
            
            else if(command=="mkdir"){
                string Folder_name ;
                cin>> Folder_name ;
                cout<<" "<<Folder_name<<endl;
                s+=" ";
                s+=Folder_name ;
                m->mkdir(Folder_name);
            }
            
            else if(command=="touch"){
                string file_name ;
                cin>> file_name ;
                cout<<" "<<file_name<<endl;
                s+=" ";
                s+=file_name ;
                m->touch(file_name);
            }
            
            else if(command=="rm"){
                string name ;
                cin>>name ;
                cout<<" "<<name<<endl;
                s+=" ";
                s+=name ;
                m->rm(name);
            }
            
           else if(command=="cd"){
                string Folder_name ;
                cin>> Folder_name ;
               
                if(Folder_name==".."){
                    cout<<" .."<<endl;
                    m->cd_prev();
                }
                else{ 
                    cout<<" "<<Folder_name<<endl;
                    s+=" ";
                    s+=Folder_name ;
                    m->cd(Folder_name);
                }
            }
            
            else if(command=="ls"){
                cout<<endl;
                m->ls();
            }
            
            else if(command=="quit") {}
            
            else {
                cout<<endl;
                cout<<"Command does not exist"<<endl;
            }
            
            history.push_back(s);
            
        }while(command!="quit");
    }
    
    // for csh
    else if(term=="csh"){
        do{
            cout<<"$ ";
            string s="";
            cin>> command ;
            cout<<command;
            s+=command ;
            
            if(command=="pwd"){
                cout<<endl;
                m->pwd() ;
                cout<<endl;
            }
            
            else if(command=="mkdir"){
                string Folder_name ;
                cin>> Folder_name ;
                cout<<" "<<Folder_name<<endl;
                s+=" ";
                s+=Folder_name ;
                m->mkdir(Folder_name);
            }
            
            else if(command=="touch"){
                string file_name ;
                cin>> file_name ;
                cout<<" "<<file_name<<endl;
                s+=" ";
                s+=file_name ;
                m->touch(file_name);
            }
            
            else if(command=="rm"){
                string name ;
                cin>>name ;
                cout<<" "<<name<<endl;
                s+=" ";
                s+=name ;
                m->rm(name);
            }
            
           else if(command=="cd"){
                string Folder_name ;
                cin>> Folder_name ;
                if(Folder_name==".."){
                    cout<<" .."<<endl;
                    m->cd_prev();
                }
               else if(Folder_name=="~"){
                   cout<<" ~"<<endl;
                   m->cd_home();
               }
               else{ 
                   cout<<" "<<Folder_name<<endl;
                    s+=" ";
                    s+=Folder_name ;
                    m->cd(Folder_name);
               }
            }
            
            else if(command=="ls"){
                cout<<endl;
                m->ls();
            }
            else if(command=="quit") {}
            
            else {
                cout<<endl;
                cout<<"Command does not exist"<<endl;
            }
            
            history.push_back(s);
            
        }while(command!="quit");
        
    }
    
    //for bash
    else if(term=="bash"){  do{
            
            m->pwd();
            cout<<" $ ";
            string s="";
            cin>> command ;
            cout<<command;
            s+=command ;
            
            if(command=="pwd"){
                cout<<endl;
                m->pwd() ;
                cout<<endl;
            }
            
            else if(command=="mkdir"){
                string Folder_name ;
                cin>> Folder_name ;
                cout<<" "<<Folder_name<<endl;
                s+=" ";
                s+=Folder_name ;
                m->mkdir(Folder_name);
            }
            
            else if(command=="touch"){
                string file_name ;
                cin>> file_name ;
                cout<<" "<<file_name<<endl;
                s+=" ";
                s+=file_name ;
                m->touch(file_name);
            }
            
            else if(command=="rm"){
                string name ;
                cin>>name ;
                cout<<" "<<name<<endl;
                s+=" ";
                s+=name ;
                m->rm(name);
            }
            
           else if(command=="cd"){
                string Folder_name ;
                cin>> Folder_name ;
                if(Folder_name==".."){
                    cout<<" .."<<endl;
                    m->cd_prev();
                }
               else if(Folder_name=="~"){
                   cout<<" ~"<<endl;
                   m->cd_home();
               }
               else{ 
                   cout<<" "<<Folder_name<<endl;
                    s+=" ";
                    s+=Folder_name ;
                    m->cd(Folder_name);
               }
            }
            
            else if(command=="ls"){
                cout<<endl;
                m->ls();
            }
            else if(command=="quit") {}
            
            else {
                cout<<endl;
                cout<<"Command does not exist"<<endl;
            }
            
            history.push_back(s);
            
        }while(command!="quit");
        
        
    }
    
    // for zsh
    else if(term=="zsh"){ 
        do{
            cout<<username<<" ";
            m->pwd();
            cout<<" $ ";
            string s="";
            cin>> command ;
            cout<<command;
            s+=command ;
            
            if(command=="pwd"){
                cout<<endl;
                m->pwd() ;
                cout<<endl;
            }
            
            else if(command=="mkdir"){
                string Folder_name ;
                cin>> Folder_name ;
                cout<<" "<<Folder_name<<endl;
                s+=" ";
                s+=Folder_name ;
                m->mkdir(Folder_name);
            }
            
            else if(command=="touch"){
                string file_name ;
                cin>> file_name ;
                cout<<" "<<file_name<<endl;
                s+=" ";
                s+=file_name ;
                m->touch(file_name);
            }
            
            else if(command=="rm"){
                string name ;
                cin>>name ;
                cout<<" "<<name<<endl;
                s+=" ";
                s+=name ;
                m->rm(name);
            }
            
           else if(command=="cd"){
                string Folder_name ;
                cin>> Folder_name ;
                s+=" ";
                s+=Folder_name ;
                if(Folder_name==".."){
                    cout<<" .."<<endl;
                    m->cd_prev();
                }
               else if(Folder_name=="~"){
                   cout<<" ~"<<endl;
                   m->cd_home();
               }
               else{ 
                   cout<<" "<<Folder_name<<endl;
                   m->cd(Folder_name);
                   }
            }
            
            else if(command=="ls"){
                cout<<endl;
                m->ls();
            }
        
            else if (command=="history"){
                cout<<endl;
                for(int i=0;i<history.size();i++){
                
                    cout<<i<<" "<<history[i]<<endl;
                }
            }
            else if(command=="quit") {}
            
            else {
                cout<<endl;
                cout<<"Command does not exist"<<endl;
            }
            
            history.push_back(s);
            
        }while(command!="quit");
  }     
    return 0;
}
