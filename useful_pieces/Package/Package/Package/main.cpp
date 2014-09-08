#define __DP__

#ifndef __DP__
#include<fstream>
//#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

struct item{    //每个物体，包括名称、重量以及价值
    string name;
    double weight;
    double value;

    item(){}
    item(string Name, double Weight, double Value):name(Name),weight(Weight),value(Value){}

    bool operator<(const item &comp)const{  //比较大小时按重量计(为排序)
        return weight<comp.weight;
    }
};

int nans;   //
vector<item> Items;
vector<bool> IsInbag;

double totalspace;

inline double calval(){
    double valsum=0;
    for(int i=0;i<(int)Items.size();++i)if(IsInbag[i])valsum+=Items[i].value;
    return valsum;
}

struct comb{
    double valuesum;
    double freespace;
    vector<int> itemidx;

    comb(){
        valuesum=calval();
        freespace=totalspace;
        for(int i=0;i<(int)Items.size();++i)if(IsInbag[i]){
            freespace-=Items[i].weight;
            itemidx.push_back(i);
        }
    }
    comb(double ValueSum, double FreeSpace):valuesum(ValueSum),freespace(FreeSpace){
        for(int i=0;i<(int)IsInbag.size();++i)if(IsInbag[i])itemidx.push_back(i);
    }

    bool operator<(const comb &cp)const{
        return valuesum<cp.valuesum;
    }
    bool operator>(const comb &cp)const{
        return valuesum>cp.valuesum;
    }
    bool operator==(const comb &cp)const{
        return valuesum==cp.valuesum;
    }
};

list<comb> answers;

void encase(double capacity,int ist){
    bool endstate=true;
    for(int i=ist;i<(int)Items.size()&&Items[i].weight<=capacity;++i){
        endstate=false;
        IsInbag[i]=true;
        encase(capacity-Items[i].weight,i+1);
        IsInbag[i]=false;
    }
    if(endstate){
        //double vl=calval();   //按价值算时用此式
        double vl=totalspace-capacity;  //按体积算时为了提高效率用此式

        if((int)answers.size()<nans || vl>answers.back().valuesum){
            comb ans(vl,capacity);
            answers.insert(find_if(answers.begin(),answers.end(),bind2nd(less<comb>(),ans)),ans);
            if((int)answers.size()>nans)answers.pop_back();
        }
    }
}

int main(){
    ifstream fin("input.txt");
    fin>>totalspace>>nans;

    char ch;
    double w;
    string name;
    while(fin>>ch){
        if(ch==';'){
            while((ch=fin.get())!='\n');
            continue;
        }
        fin.seekg(-1,ios_base::cur);
        if(!(fin>>name))break;
        fin>>w;
        Items.push_back(item(name,w,w));
    }
    fin.close();
    stable_sort(Items.begin(),Items.end(),less<item>());
    IsInbag.resize(Items.size(),false);

    encase(totalspace,0);
    ofstream fout("output.txt");
    for(list<comb>::iterator itr=answers.begin();itr!=answers.end();++itr){
        fout<<"Total weight:"<<(itr->valuesum)<<"\tFree space:"<<(itr->freespace)<<"\n";
        for(int i=0;i<(int)itr->itemidx.size();++i){
            int idx=itr->itemidx[i];
            fout<<"    "<<Items[idx].name<<"\t("<<Items[idx].value<<")\n";
        }
        fout<<'\n';
    }

    return 0;
}

#else   // Dynamic Programming :

#include<fstream>
#include<string>
#include<vector>
#include<bitset>
using namespace std;

struct item{    //每个物体，包括名称、重量以及价值
    string name;
    int weight;     //relative weight: original weight * rate -> weight
    double value;

    item(){}
    item(string Name, int Weight, double Value):name(Name),weight(Weight),value(Value){}

    bool operator<(const item &comp)const{  //比较大小时按重量计(为排序)
        return weight<comp.weight;
    }
};

int nans;   //
double totalspace;
vector<item> vItems;
const int bitmax = 512; //max items
const int tsint = 50000; //totalspace : double * rate -> tsint

struct DPNode{
    double value;   //max total value of this weight
    bitset<bitmax> IsInBag; //which itmes are in the bag
    DPNode():value(0.0){}
};

vector<DPNode> DP;

void filldp(){
    for(int n=0;n<=tsint;++n){
        for(int iItem=0;iItem<int(vItems.size());++iItem){
            int neweight = n + vItems[iItem].weight;
            if(neweight <= tsint){
                double newvalue=DP[n].value;
                bool flag=false;
                if(!DP[n].IsInBag.test(iItem)){
                    flag=true;
                    newvalue+=vItems[iItem].value;
                }
                if(newvalue > DP[neweight].value){
                    DP[neweight].IsInBag = DP[n].IsInBag;
                    if(flag)DP[neweight].IsInBag.set(iItem);
                    DP[neweight].value = newvalue;
                }
            }
        }
    }
}

int main(){
    ifstream fin("input.txt");
    fin>>totalspace>>nans;

    char ch;
    double w;
    string name;
    double rate = double(tsint)/totalspace;
    while(fin>>ch){
        if(ch==';'){
            while((ch=fin.get())!='\n');
            continue;
        }
        fin.seekg(-1,ios_base::cur);
        if(!(fin>>name))break;
        fin>>w;
        vItems.push_back(item(name,int(w*rate+0.9),w));  //进位 -> 将造成积累误差；以后可实验四舍五入的效果
    }
    fin.close();
    DP.resize(tsint+1);

    filldp();

    ofstream fout("output.txt");
    for(int i=0,nextsp=tsint;i<nans && nextsp>0;++i){
        double totalv=DP[nextsp].value;
        fout<<"Total weight:"<<totalv<<"\tFree space:"<<totalspace-totalv<<"\n";
        for(int j=0;j<int(vItems.size());++j)if(DP[nextsp].IsInBag.test(j)){
            fout<<"    "<<vItems[j].name<<"\t("<<vItems[j].value<<")\n";
        }
        fout<<"\n";
        while(DP[--nextsp].value == totalv)if(nextsp<1)break;
    }

    return 0;
}

#endif