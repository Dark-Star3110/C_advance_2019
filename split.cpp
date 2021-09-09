#include<bits/stdc++.h>
using namespace std;

// thu vien tach chuoi theo dau nhap vao test code (tu code nen co the co bug :V)
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

int main(){
    string input = "hello world";
    int count = numSub(input," ")+1;
    string *output = split(input," ");
    for(int i=0; i<count; i++){
        cout<<output[i]<<endl;
    }
    return 0;
}
