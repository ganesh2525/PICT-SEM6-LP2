#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void setData(map<string,string>&data){
    ifstream in("data.txt");
    string key,value;
    while(in>>key>>value){
        replace(value.begin(),value.end(),'_',' ');
        data[key]=value;
    }
    in.close();
}

int main(){
    map<string,string>data;
    setData(data);
    cout<<"\nPICT ChatBot: How can I help you today ?"<<endl;

    string input;

    ofstream file;
    while(true){
        cout<<"\nYou: ";
        getline(cin,input);
        transform(input.begin(),input.end(),input.begin(),::tolower);
        input.erase(remove_if(input.begin(),input.end(),[](unsigned char c){return isspace(c);}),input.end());

        bool found=false;
        for(auto x:data){
            if(input.find(x.first)!=string::npos){
                cout<<"\nChatBot: "<<data[x.first]<<endl;
                found=true;
                break;
            }
        }

        if(!found){
            cout<<"\nChatBot: Data is not present in the dataset. Please provide the answer. Enter the data in key-value pairs"<<endl;
            string str1,str2;
            cout<<"Key: ";
            getline(cin,str1);
            cout<<"Value: ";
            getline(cin,str2);

            transform(str1.begin(),str1.end(),str1.begin(),::tolower);
            str1.erase(remove_if(str1.begin(),str1.end(),[](unsigned char c){return isspace(c);}),str1.end());

            data[str1]=str2;

            replace(str2.begin(),str2.end(),' ','_');
            file.open("data.txt",ios::app);

            if(file.is_open()){
                file<<endl<<str1<<" "<<str2;
                file.close();
            }
            else{
                cout<<"\nFailed to open the file"<<endl;
            }

            cout<<"\n\tData remembered!"<<endl;
            found = false;
        }
    }
    return 0;
}