#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

double totalspace;

struct item{
    string name;
    double weight;

    item(string Name, double Weight):name(Name),weight(Weight){}
    bool operator<(const item &comp)const{
        return weight<comp.weight;
    }
    bool operator>(const item &comp)const{
        return weight>comp.weight;
    }
};

struct bag{
    double space;
    vector<int> vItemIdx;

    bag():space(totalspace){}
    bool operator<(const bag &comp)const{
        return space<comp.space;
    }
};

struct solution{
    double sqsp;
    vector<bag> vBags;

    solution():sqsp(0.0){
    }

    bool operator<(const solution &comp)const{
        if(vBags.size()<comp.vBags.size())return true;
        if(vBags.size()>comp.vBags.size())return false;
        return sqsp>comp.sqsp;
    }
    bool operator>(const solution &comp)const{
        if(vBags.size()>comp.vBags.size())return true;
        if(vBags.size()<comp.vBags.size())return false;
        return sqsp<comp.sqsp;
    }
    //void calsqsp(){
    //    sqsp=0.0;
    //    for(int i=0;i<(int)vBags.size();++i)
    //        sqsp+=vBags[i].space*vBags[i].space;
    //}
};

int nAns;
int nmxBag;
solution obj;
vector<item> vItems;
list<solution> lAnswers;    //取nAns个solution，按升序排序

void encase(int iItem){
    if(iItem>=(int)vItems.size()){   //Finish this solution
        nmxBag=obj.vBags.size();
        if((int)lAnswers.size()<nAns)
            lAnswers.insert(find_if(lAnswers.begin(),lAnswers.end(),bind2nd(greater<solution>(),obj)),obj);
        else if(lAnswers.back()>obj){
            lAnswers.pop_back();
            lAnswers.insert(find_if(lAnswers.begin(),lAnswers.end(),bind2nd(greater<solution>(),obj)),obj);
        }
        return;
    }
    if(vItems[iItem].weight>totalspace){
        encase(iItem+1);   //.......体积过大
        return;
    }
    for(int iBag=0;iBag<(int)obj.vBags.size();++iBag){
        if(obj.vBags[iBag].space<vItems[iItem].weight)continue;

        double tmpsqsp=obj.sqsp;
        obj.sqsp-=obj.vBags[iBag].space*obj.vBags[iBag].space;
        obj.vBags[iBag].space-=vItems[iItem].weight;
        obj.sqsp+=obj.vBags[iBag].space*obj.vBags[iBag].space;
        obj.vBags[iBag].vItemIdx.push_back(iItem);
        encase(iItem+1);
        obj.sqsp=tmpsqsp;
        obj.vBags[iBag].vItemIdx.pop_back();
        obj.vBags[iBag].space+=vItems[iItem].weight;
    }
    if((int)obj.vBags.size()<nmxBag){
        double tmpsqsp=obj.sqsp;
        obj.vBags.push_back(bag());
        obj.vBags.back().space=totalspace-vItems[iItem].weight;
        obj.sqsp+=obj.vBags.back().space*obj.vBags.back().space;
        obj.vBags.back().vItemIdx.push_back(iItem);
        encase(iItem+1);
        obj.sqsp=tmpsqsp;
        obj.vBags.pop_back();
    }
}

int main(){
    ifstream fin("input.txt");
    fin>>totalspace>>nAns;
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
        vItems.push_back(item(name,w));
    }
    fin.close();
    nmxBag=vItems.size();
    stable_sort(vItems.begin(),vItems.end(),greater<item>());

    encase(0);

    ofstream fout("output.txt");
    for(list<solution>::iterator itr=lAnswers.begin();itr!=lAnswers.end();++itr){
        fout<<"Bags used:"<<itr->vBags.size()<<"\tBag size:"<<totalspace<<'\n';
        for(int i=0;i<(int)itr->vBags.size();++i){
            sort(itr->vBags.begin(),itr->vBags.end());
            fout<<"\tBag No."<<setw(2)<<i+1<<" : free space:"<<setw(9)<<fixed<<setprecision(2)<<itr->vBags[i].space<<", ";
            fout.unsetf(ios::floatfield);
            fout.precision(6);
            for(int j=0;j<(int)itr->vBags[i].vItemIdx.size();++j){
                int idx=itr->vBags[i].vItemIdx[j];
                fout<<vItems[idx].name<<'('<<vItems[idx].weight<<") ";
            }
            fout<<'\n';
        }
        fout<<'\n';
    }

    return 0;
}