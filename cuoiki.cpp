#include <bits/stdc++.h>
#include "graph.hpp"
using namespace std;
#define MAX 100

map<string,int> rankIn;
map<string,int> rankOut;
map<string,double> pageRank;
map<string,vector<string>> pageTo;

typedef struct{
    string id;
    string url;
}Links;

// doc file roi luu cac dong doc duoc vao mang
string * readFile(string filePath){
    int count;
    ifstream infile(filePath);
    infile>>count;
    // cout << count << endl;
    string* lines = new string[count];
    int index = -1;
    if(infile.is_open()){
        string line;
        while(getline(infile, line)){
            if(index == -1){
                index++;
            }
            else{
                lines[index] = line.c_str();
                index++;
            }
            // cout << line.c_str() << endl;
        }
        infile.close();
    }
    // for(int i = 0; i <count; i++){
    //     cout << lines[i] << endl;
    // }
    return lines;
}

int numberLines(string filePath){
    int count;
    ifstream infile(filePath);
    infile>>count;
    infile.close();
    return count;
}

// tach chuoi theo ki tu truyen vao, roi luu vao mang
int numSub(string s,string sub){
    int count = 0;
    int start = 0;
    int end = s.find(sub);
    while (end != -1) {
        start = end + sub.size();
        end = s.find(sub, start);
        count++;
    }
    return count;
}
string* split(string s, string del) 
{
    int count = numSub(s,del)+1;
    string *output = new string[count];
    int i = 0;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        output[i] = s.substr(start, end - start);
        start = end + del.size();
        end = s.find(del, start);
        i++;
    }
    output[i] = s.substr(start, end - start);
    return output;
}

void pageRank_Algo(Graph g,int n,int numVertex){
    double pageRankCopy[numVertex];
    int k = 0;
    for(auto x:g){
        pageRankCopy[k] = pageRank[x.first]; 
        k++;
    }
    k = 0;
    for(int i = 0; i < n; i++){
        int m =0;
        for(auto x : g){
            int num = pageTo[x.first].size();
            if(num != 0){
                pageRankCopy[m] = 0;
            }
            for(int j = 0; j < num;j++){
                string page = pageTo[x.first][j];
                // cout << page<< endl;
                pageRankCopy[m] += pageRank[page]/rankOut[page];
            }
            m++;
        }
        for(auto x:g){
            pageRank[x.first] = pageRankCopy[k];
            k++;
        }
        k = 0;
    }  
}

void displayPageRank(Graph g){
    for(auto x:g){
        cout << "pageRank of "<<x.first << " is: " <<pageRank[x.first] << endl;
    }
}

void resetPageRank(Graph g){
    for(auto vertex:g){
        pageRank[vertex.first] = 1;
    }
}

int main () 
{ 
    Graph g;

    int max = 0;
    int max2 =0;
    int min = MAX;
    string verMax;
    string verMin;

    int spamtop = 0;
    int spambot = 0;

    string id1,id2;

    string pageRankMax;
    string pageRankMax2;
    string pageRankMin;
    int m;

    // doc webpages lưu vào struct
    string* pages;
    pages = readFile("webpages.txt");
    int count = numberLines("webpages.txt");
    Links link[count];
    for(int i = 0; i < count; i++){
        int n = pages[i].length();
        int posSpace = pages[i].find(" ");
        link[i].url = pages[i].substr(0,posSpace);
        // cout << link[i].url << endl;
        link[i].id = pages[i].substr(posSpace+1,n-1);
        // cout << link[i].id << endl;
    }
    // cout << &link[1].url << endl;

    // doc pagesconections luu vao do thi g
    string * lines;
    lines = readFile("pageConections.txt");
    int num = numberLines("pageConections.txt") ;
    for(int i = 0; i < num; i++){
        string* vertexs = split(lines[i]," ");
        // cout << vertexs[0] << endl;
        insert_vertex(g,vertexs[0]);
        int cc = numSub(lines[i]," ")+1;
        for(int j = 1; j < cc; j++){
            // cout << vertexs[j]<< endl;
            insert_vertex(g,vertexs[j]);
            insert_edge(g,vertexs[0],vertexs[j],1);
            pageTo[vertexs[j]].push_back(vertexs[0]);
            rankOut[vertexs[0]]++;
            rankIn[vertexs[j]]++;
        }
    }
    resetPageRank(g);
    int menu;
    while(1){
        cout << "------------------------------MENU-------------------------------" << endl;
        cout << "1.doc va hien file webpages,hien thi web co nhieu,it lk toi nhat"<< endl;
        cout << "2.thuc hien pageRank lan 1 in ra man hinh url cua web co pageRank be nhat,lon nhat"<< endl;
        cout << "3.thuc hien pageRank lan m(nhap vao) in ra top 3 trang web quan trong nhat" << endl;
        cout << "4.in ra so luong web chi co lien ket den,chi co lien ket di"<< endl;
        cout << "5.nhap vao id1 va id2 in ra khoang cach nho nhat"<< endl;
        cout << "6.thoat"<< endl;
        cout << "chon menu:";
        cin >> menu;
        switch(menu){
            case 1:
            cout << "so luong webpages: "<<count << endl;
            for(int i = 0; i < count; i++){
                cout << link[i].url  << " ";
                cout << link[i].id << endl;
            }
            for(auto x:g){
                if(rankIn[x.first] > max){
                    max = rankIn[x.first];
                    verMax = x.first;
                }
                if(rankIn[x.first] < min){
                    min = rankIn[x.first];
                    verMin = x.first;
                }
                // cout <<"rankIn "<<x.first <<" : "<<rankIn[x.first] << endl;
            }
            for (auto item : link){
                if(item.id == verMax) verMax=item.url;
                if(item.id == verMin) verMin=item.url; 
            }
            cout <<endl<<"webpages nhieu lien ket toi nhat: " << verMax << endl;
            cout <<"webpages it lien ket toi nhat: "<< verMin << endl;
            max = 0;
            min = MAX;
            break;
            case 2:
            pageRank_Algo(g,1,count);
            for(auto x: g){
                if(pageRank[x.first] > max) {
                    max = pageRank[x.first];
                    pageRankMax = x.first;
                }
                if(pageRank[x.first] < min){
                    min = pageRank[x.first];
                    pageRankMin = x.first;
                } 
            }
            for(auto y: link){
                if(y.id == pageRankMax) pageRankMax = y.url;
                if(y.id == pageRankMin) pageRankMin = y.url;
            }
            displayPageRank(g);
            cout << "web co pageRank be nhat: " << pageRankMin << endl;
            cout << "web co pageRank lon nhat: " << pageRankMax << endl;
            resetPageRank(g);
            max =0;
            min = MAX;
            break;
            case 3:
            cout << "nhap m: "; cin>>m;
            pageRank_Algo(g,m,count);

            break;
            case 4:
            for(auto x:g){
                if(rankIn[x.first] != 0 && rankOut[x.first] == 0){
                    spamtop++;
                }
                if(rankIn[x.first] == 0 && rankOut[x.first] != 0){
                    spambot++;
                }
            }
            cout <<"so luong web chi co lk den: "<< spamtop << endl;
            cout <<"so luong web chi co lk di: "<< spambot << endl;
            break;
            case 5:
            cout << "nhap id1: "; cin>>id1;
            cout << "nhap id2: "; cin>>id2;
            Dijkstra(g,id1,id2);
            // for(auto x: g){
            //     for(auto y: x.second){
            //         cout << x.first << "---" << y.first << endl;
            //     }
            // }

            break;
            case 6:
            exit(0);
            break;
        }
    }
    return 0; 
}