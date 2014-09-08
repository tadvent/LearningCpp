#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<algorithm>
#include<functional>
#include<limits>

#include<cassert>

using namespace std;

const int MaxItem = 64;    //bitset<MaxItem> max num of items in one disk -> affects memory use
double DiskCapacity;
double fillrate = 0.98;
double mostlowcut = DiskCapacity * 0.9;
int nAns;
bitset<MaxItem> allitembits;

struct Item {
    string name;
    double size;

    Item():size(0.0){}
    Item(const string &Name, double Size):name(Name),size(Size){}
};

vector<Item> vItems;

struct SizeNode {
    double size;
    vector< vector<Item>::iterator > vitemitrs;
    bitset<MaxItem> InDisk;

    SizeNode():size(0.0){}
    SizeNode(const SizeNode &node):size(node.size),vitemitrs(node.vitemitrs),InDisk(node.InDisk){}
    SizeNode& additem(const vector<Item>::iterator itemitr, const vector<Item> &items){
        size += itemitr->size;
        vitemitrs.push_back(itemitr);
        InDisk.set(itemitr-items.begin());
        return *this;
    }
    bool operator<(const SizeNode &comp)const{
        return size < comp.size;
    }
    bool operator>(const SizeNode &comp)const{
        return size > comp.size;
    }
};

class SNVec : public vector<SizeNode> {
public:
    void sort_push_back(const SizeNode &sznode){
        if(empty()){
            push_back(sznode);
            return;
        }
        resize(size()+1);
        reverse_iterator ritr = rbegin() + 1;
        while(ritr != rend() && sznode.size < ritr->size){
            *(ritr-1) = *ritr;
            ++ritr;
        }
        *(ritr-1) = sznode;
    }

    void calc(vector<Item> &items, const double maxsize){
        clear();
        push_back(SizeNode());
        int idx = 0;

        while(idx < int(size()) && operator[](idx).size < maxsize){
            int start = 0;
            for(vector<Item>::reverse_iterator ritr=items.rbegin();ritr!=items.rend();++ritr){
                if(operator[](idx).InDisk.test(items.rend()-ritr-1)){
                    start = items.rend() - ritr;
                    break;
                }
            }
            for(vector<Item>::iterator itemitr=items.begin()+start;itemitr!=items.end();++itemitr){
                if(operator[](idx).InDisk.test(itemitr-items.begin()))continue;
                double newsize = operator[](idx).size + itemitr->size;
                if(newsize > maxsize)continue;
                sort_push_back(SizeNode(operator[](idx)).additem(itemitr,items));
            }
            ++idx;
        }
    }
};

SNVec snvec;

struct Disks {
    vector<SNVec::iterator> vsnitrs;
    double sizesum;

    Disks():sizesum(0.0){}
    void clear(){
        vsnitrs.clear();
        sizesum = 0.0;
    }
    void adddisk(SNVec::iterator snvitr){
        vsnitrs.push_back(snvitr);
        sizesum += snvitr->size;
    }
    void deldisk(){
        sizesum -= (*vsnitrs.rbegin())->size;
        vsnitrs.pop_back();
    }
};

struct AnsVec : public vector<Disks> {
    void sort_push_back(const Disks &disk){
        if(empty()){
            push_back(disk);
            return;
        }
        resize(size()+1);
        vector<Disks>::reverse_iterator ritr=rbegin()+1;
        while(ritr != rend() && disk.sizesum > ritr->sizesum){
            *(ritr-1) = *ritr;
            ++ritr;
        }
        *(ritr-1) = disk;
    }
};

AnsVec vAnswers;

class DiskComb : public Disks {
public:
    bitset<MaxItem> InDisks;

    void clear(){
        Disks::clear();
        InDisks.reset();
    }
    void adddisk(SNVec::iterator snvitr){
        Disks::adddisk(snvitr);
        InDisks ^= snvitr->InDisk;
    }
    void deldisk(){
        InDisks ^= (*vsnitrs.rbegin())->InDisk;
        Disks::deldisk();
    }
    void adddiskitr(SNVec::iterator snvitr){
        Disks::vsnitrs.push_back(snvitr);
        InDisks ^= (*vsnitrs.rbegin())->InDisk;
    }
    void deldiskitr(){
        InDisks ^= (*vsnitrs.rbegin())->InDisk;
        Disks::vsnitrs.pop_back();
    }
    int DFSearch(double lowcut){
        if(InDisks == allitembits){
            vAnswers.sort_push_back(*this);
            if(int(vAnswers.size())>nAns){
                vAnswers.pop_back();
                return -1;
            }
            return 0;
        }

        bool last = true;
        SNVec::iterator itr;
        if(vsnitrs.empty())itr = snvec.end() - 1;
        else itr = *vsnitrs.rbegin() - 1;
        for(;itr->size>lowcut && itr->size>mostlowcut && itr!=snvec.begin();--itr){
            if((itr->InDisk & InDisks) != 0)continue;
            last = false;
            adddisk(itr);
            int rvalue = DFSearch(itr->size * fillrate);
            deldisk();
//            if(-1 == rvalue)return -1;
        }
        if(last){
            int rvalue;
            while(itr!=snvec.begin() && (itr->InDisk & InDisks)!=0)--itr;
            if(itr == snvec.begin())return 1;
            adddiskitr(itr);
            rvalue = DFSearch(DiskCapacity * 0.0001);
            deldiskitr();
//            if(-1 == rvalue)return -1;

            //for(;itr!=snvec.begin();--itr){
            //    if((itr->InDisk & InDisks) != 0)continue;
            //    adddiskitr(itr);
            //    DFSearch();
            //    deldiskitr();
            //    break;
            //}
        }
        return 0;
    }
};

int main(){
    ifstream fin("input.txt");
    fin>>DiskCapacity>>nAns;

    char ch;
    double size;
    string name;
    while(fin>>ch){
        if(ch==';'){
            while((ch=fin.get())!='\n');
            continue;
        }
        fin.seekg(-1,ios_base::cur);
        if(!(fin>>name))break;
        fin>>size;
        vItems.push_back(Item(name,size));
    }
    fin.close();
    for(int i=0;i<int(vItems.size());++i)allitembits.set(i);

    snvec.calc(vItems,DiskCapacity);
    DiskComb dc;
    dc.DFSearch(DiskCapacity * fillrate);

    system("pause");
    return 0;
}




//=============================================================

//  version 2, not as good as version 1
/*

#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<algorithm>
#include<functional>

//#define NDEBUG
#include<cassert>

using namespace std;

const int MaxItem = 128; // bitset<MaxItem> max num of items in one disk -> affects memory use
const int DiskCapacity = 5000; // relative space of one disk -> affects precision & memory
double realcapacity;

struct Item {
private:
    static double rate;
public:
    string name;
    int size;
    double realsize;
    Item():size(0),realsize(0.0){}
    Item(const string &Name, double RealSize):name(Name),realsize(RealSize){
        setsize();
    }

    static void setrate(double newrate){
        rate = newrate;
    }
    void setsize(){
        size = int(realsize * rate + 0.9);
    }
};

double Item::rate = 0.0;

vector<Item> vItems;

class DiskDPNode : public bitset<MaxItem> {
public:
    int used;

    DiskDPNode():used(0){}
};

class DiskUse {
public:
    vector<int> itemidxs;
    int used;

    DiskUse():used(0){}

    bool GT(const DiskUse *const comp)const{
        return (used > comp->used);
    }
    friend ostream& operator<<(ostream &, const DiskUse&);
};

class DiskState : public DiskUse {
public:
    vector<DiskDPNode> DP;

    //计算 DP 的函数，要包含计算 perfect point 的代码么？返回一个 vector 吧。
    vector<int> calcdp(){
        vector<int> vppts;
        DP.clear();
        DP.resize(DiskCapacity+1);

        DP[0].used = 0;
        for(int n=0;n<=DiskCapacity;++n){
            if(n>0 && 0 == DP[n].used)DP[n] = DP[n-1];
            else if(n == DP[n].used)
                vppts.push_back(n); //perfect point
            for(int idx=0;idx<int(itemidxs.size());++idx){
                if(DP[n].test(idx))continue;
                Item &it = vItems[itemidxs[idx]];
                int newsize = n + it.size;
                if(newsize > DiskCapacity)continue;
                int newused = DP[n].used + it.size;
                if(newused > DP[newsize].used){
                    DP[newsize] = DP[n];
                    DP[newsize].set(idx);
                    DP[newsize].used = newused;
                }
            }
        }
        return vppts;
    }

    //将此盘中 size 对应的 DP 中的物体移入 desdisk 盘中，修改两盘的 used，但不计算 DP
    void moveitems(DiskState &desdisk, int size){
//        assert( DP[size].used + desdisk.used <= DiskCapacity );

        int i=0,j=0;
        while(j<int(itemidxs.size())){
            if(DP[size].test(j)){
                desdisk.itemidxs.push_back(itemidxs[j++]);
            }
            else {
                itemidxs[i++]=itemidxs[j++];
            }
        }
        itemidxs.resize(i);

        used -= DP[size].used;
        desdisk.used += DP[size].used;
    }
};

DiskState extra;

struct PPt {
    DiskState *pdisk;
    int size;
    PPt(void):pdisk(NULL),size(-1){}
    PPt(DiskState *pDisk, int Size):pdisk(pDisk),size(Size){}

    bool IsDisk(const DiskState *const pDisk)const{
        return (pdisk == pDisk);
    }
};

class PPtArray : public vector<PPt> {
public:
    void DelDisk(const DiskState *const pdisk){
        erase(remove_if(begin(),end(),bind2nd(mem_fun_ref(&PPt::IsDisk),pdisk)),end());
    }
    void Insert(DiskState *pdisk, const vector<int> &vints){
        int count = size();
        resize(count+vints.size());
        for(vector<int>::const_iterator itr1=vints.begin();itr1!=vints.end();++itr1){
            PPtArray::iterator itr2 = begin() + count;
            while(itr2 > begin() && *itr1 < (itr2-1)->size){
                *itr2 = *(itr2-1);
                --itr2;
            }
            *itr2 = PPt(pdisk,*itr1);
            ++count;
        }
    }
};

class DiskArray : public vector<DiskState*> {
    PPtArray ppts;
public:
    DiskArray::iterator PdiskToItr(DiskState *pdisk){
        for(DiskArray::iterator itr=begin();itr!=end();++itr)if((*itr) == pdisk){
            return itr;
        }
        return end();
    }

    void sortdisk(DiskArray::iterator itr){
        DiskState *temp = *itr;
        while(itr>begin() && temp->used > (*(itr-1))->used){
            *itr = *(itr-1);
            --itr;
        }
        *itr = temp;
    }

    void adjustdisk(DiskState *pdisk){
    //DiskState* adjustitem(std::vector<Item>::iterator itemitr){
    //若塞不下则仍返回包含此 iItem 的临时 DiskState 指针。用完后须 delete
    //若塞下但挤出新物体，则返回包含新物体的 DiskState 指针。用完后须 delete
    //若装下则返回 NULL
        bool flag = true;
        int curuse, maxuse;
        PPtArray tmppt;
        //DiskState *tmpdisk = new DiskState;

        //tmpdisk->used = itemitr->size;
        //tmpdisk->itemidxs.push_back(itemitr-vItems.begin());
        tmppt.Insert(pdisk,pdisk->calcdp());

        while(flag /*&& !pdisk->itemidxs.empty()*//*){
            flag = false;
            maxuse = 0;
            PPtArray::iterator maxfrompptitr;
            PPtArray::iterator maxtopptitr;
            for(PPtArray::iterator frompptitr=tmppt.begin()+1;frompptitr!=tmppt.end();++frompptitr){
                for(PPtArray::iterator topptitr=ppts.begin();
                    topptitr!=ppts.end() && topptitr->size<frompptitr->size;++topptitr){

                        curuse = topptitr->pdisk->used - topptitr->size + frompptitr->size;
                        if(curuse <= DiskCapacity && curuse > maxuse){
                            flag = true;
                            maxuse = curuse;
                            maxfrompptitr = frompptitr;
                            maxtopptitr = topptitr;
                        }
                }
            }
            if(flag){
                //if(maxtopptitr->size == 0){
                //    DiskState *ptodisk = maxtopptitr->pdisk;
                //    //DiskState *pfromdisk = maxfrompptitr->pdisk;
                //    pdisk->moveitems(*ptodisk,maxfrompptitr->size);
                //    ppts.DelDisk(ptodisk);
                //    ppts.Insert(ptodisk,ptodisk->calcdp());
                //    //delete tmpdisk;
                //    return NULL;
                //}
                //else {
                    DiskState *ptodisk = maxtopptitr->pdisk;
                    pdisk->moveitems(*ptodisk,maxfrompptitr->size);
                    ptodisk->moveitems(*pdisk,maxtopptitr->size);
                    ppts.DelDisk(ptodisk);
                    ppts.Insert(ptodisk,ptodisk->calcdp());
                    tmppt.clear();
                    tmppt.Insert(pdisk,pdisk->calcdp());
                //}
            }
            //else {
            //    return pdisk;
            //}
        }
        //delete tmpdisk;
        //return pdisk;
    }

    //void adjustdisk(DiskState *pdesdisk){
    //    bool flag = true;
    //    int space = DiskCapacity - pdesdisk->used;
    //    int curuse, maxuse;
    //    DiskState *pmaxdisk = NULL;
    //    while(flag){
    //        flag = false;
    //        maxuse = 0;
    //        for(DiskArray::iterator itr=begin();itr!=end();++itr){
    //            int DPspace_use;
    //            if(pdesdisk == *itr)continue;
    //            DPspace_use = (*itr)->DP[space].used;
    //            if(DPspace_use == 0)continue;
    //            curuse = pdesdisk->used + DPspace_use;
    //            if(curuse > (*itr)->used && curuse > maxuse){
    //                flag = true;
    //                maxuse = curuse;
    //                pmaxdisk = *itr;
    //            }
    //        }
    //        if(flag)pmaxdisk->moveitems(*pdesdisk,space);
    //        ppts.DelDisk(pdesdisk);
    //        ppts.Insert(pdesdisk,pdesdisk->calcdp());
    //        if(flag){
    //            pdesdisk = pmaxdisk;
    //            space = DiskCapacity - pdesdisk->used;
    //        }
    //    }

    //    stable_sort(begin(),end(),mem_fun(&DiskState::GT));
    //}

    void addWholeDisk(DiskState &disk){
        while(disk.used >= DiskCapacity){
            push_back(new DiskState);
            disk.moveitems(*(*rbegin()),DiskCapacity);
            ppts.Insert(*rbegin(),(*rbegin())->calcdp());
            
            disk.calcdp();
        }
    }

    void enitem(std::vector<Item>::iterator itemitr){
        extra.itemidxs.push_back(itemitr-vItems.begin());
        extra.used += itemitr->size;
        adjustdisk(&extra);

        if(extra.used < DiskCapacity)return;
        //DiskState *remaindisk = adjustitem(itemitr);
        //if(NULL == remaindisk)return;

        //remaindisk->moveitems(extra, DiskCapacity - extra.used);
        //if(0 == remaindisk->used){
        //    delete remaindisk;
        //    return;
        //}

        //增加新盘:
        addWholeDisk(extra);
        //extra.itemidxs = remaindisk->itemidxs;
        //extra.used = remaindisk->used;
        //delete remaindisk;
    }

};

DiskArray disks;

class Answer : public vector<DiskUse> {
public:
    Answer(){
        resize(disks.size());
        Answer::iterator itr = begin();
        for(DiskArray::iterator itr2=disks.begin();itr2!=disks.end();++itr,++itr2){
            *itr = *(*itr2);
        }
    }
    friend ostream& operator<<(ostream&, const Answer &);
};

ostream& operator<<(ostream &os, const DiskUse &disk){
    double realuse = 0.0;
    for(vector<int>::const_iterator itr=disk.itemidxs.begin();itr!=disk.itemidxs.end();++itr){
        realuse += vItems[*itr].realsize;
    }
    os.setf(ios::fixed);
    os<<"free space:"<<setw(8)<<setprecision(2)<<realcapacity-realuse<<",";
    os.unsetf(ios::floatfield);
    os.precision(6);
    for(vector<int>::const_iterator itr=disk.itemidxs.begin();itr!=disk.itemidxs.end();++itr){
        os<<" "<<vItems[*itr].name<<'('<<vItems[*itr].realsize<<')';
    }
    return os;
}

ostream& operator<<(ostream &os, const Answer &ans){
    os<<"Disk used:"<<ans.size()<<'\t'<<"Disk Capacity:"<<realcapacity<<'\n';
    for(Answer::const_iterator itr=ans.begin();itr!=ans.end();++itr){
        os<<"\tDisk No."<<setw(2)<<itr-ans.begin()+1<<" : "<<*itr<<'\n';
    }
    return os;
}

int main(){
    int nAns;
    ifstream fin("input.txt");
    fin>>realcapacity>>nAns;
    Item::setrate(double(DiskCapacity)/realcapacity);

    char ch;
    double rsize;
    string name;
    while(fin>>ch){
        if(ch==';'){
            while((ch=fin.get())!='\n');
            continue;
        }
        fin.seekg(-1,ios_base::cur);
        if(!(fin>>name))break;
        fin>>rsize;
        vItems.push_back(Item(name,rsize));
    }
    fin.close();

    for(vector<Item>::iterator itr=vItems.begin();itr!=vItems.end();++itr)
        disks.enitem(itr);
    //disks.addDisk(extra);
    disks.push_back(new DiskState(extra));

    ofstream fout("output.txt");
    fout<<Answer();

    return 0;
}
*/

//==============================================================================
//==============================================================================
//  backup

/*
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<bitset>
#include<algorithm>
#include<functional>

//#define NDEBUG
#include<cassert>

using namespace std;

const int MaxItem = 128; // bitset<MaxItem> max num of items in one disk -> affects memory use
const int DiskCapacity = 5000; // relative space of one disk -> affects precision & memory
double realcapacity;

struct Item {
private:
    static double rate;
public:
    string name;
    int size;
    double realsize;
    Item():size(0),realsize(0.0){}
    Item(const string &Name, double RealSize):name(Name),realsize(RealSize){
        setsize();
    }

    static void setrate(double newrate){
        rate = newrate;
    }
    void setsize(){
        size = int(realsize * rate + 0.9);
    }
};

double Item::rate = 0.0;

vector<Item> vItems;

class DiskDPNode : public bitset<MaxItem> {
public:
    int used;

    DiskDPNode():used(0){}
};

class DiskUse {
public:
    vector<int> itemidxs;
    int used;

    bool GT(const DiskUse *const comp)const{
        return (used > comp->used);
    }
    friend ostream& operator<<(ostream &, const DiskUse&);
};

class DiskState : public DiskUse {
public:
    vector<DiskDPNode> DP;

    //计算 DP 的函数，要包含计算 perfect point 的代码么？返回一个 vector 吧。
    vector<int> calcdp(){
        vector<int> vppts;
        DP.clear();
        DP.resize(DiskCapacity+1);

        DP[0].used = 0;
        for(int n=0;n<=DiskCapacity;++n){
            if(n>0 && 0 == DP[n].used)DP[n] = DP[n-1];
            else if(n == DP[n].used)
                vppts.push_back(n); //perfect point
            for(int idx=0;idx<int(itemidxs.size());++idx){
                if(DP[n].test(idx))continue;
                Item &it = vItems[itemidxs[idx]];
                int newsize = n + it.size;
                if(newsize > DiskCapacity)continue;
                int newused = DP[n].used + it.size;
                if(newused > DP[newsize].used){
                    DP[newsize] = DP[n];
                    DP[newsize].set(idx);
                    DP[newsize].used = newused;
                }
            }
        }
        return vppts;
    }

    //将此盘中 size 对应的 DP 中的物体移入 desdisk 盘中，修改两盘的 used，但不计算 DP
    void moveitems(DiskState &desdisk, int size){
//        assert( DP[size].used + desdisk.used <= DiskCapacity );

        int i=0,j=0;
        while(j<int(itemidxs.size())){
            if(DP[size].test(j)){
                desdisk.itemidxs.push_back(itemidxs[j++]);
            }
            else {
                itemidxs[i++]=itemidxs[j++];
            }
        }
        itemidxs.resize(i);

        used -= DP[size].used;
        desdisk.used += DP[size].used;
    }
};

DiskState extra;

struct PPt {
    DiskState *pdisk;
    int size;
    PPt(void):pdisk(NULL),size(-1){}
    PPt(DiskState *pDisk, int Size):pdisk(pDisk),size(Size){}

    bool IsDisk(const DiskState *const pDisk)const{
        return (pdisk == pDisk);
    }
};

class PPtArray : public vector<PPt> {
public:
    void DelDisk(const DiskState *const pdisk){
        erase(remove_if(begin(),end(),bind2nd(mem_fun_ref(&PPt::IsDisk),pdisk)),end());
    }
    void Insert(DiskState *pdisk, const vector<int> &vints){
        int count = size();
        resize(count+vints.size());
        for(vector<int>::const_iterator itr1=vints.begin();itr1!=vints.end();++itr1){
            PPtArray::iterator itr2 = begin() + count;
            while(itr2 > begin() && *itr1 < (itr2-1)->size){
                *itr2 = *(itr2-1);
                --itr2;
            }
            *itr2 = PPt(pdisk,*itr1);
            ++count;
        }
    }
};

class DiskArray : public vector<DiskState*> {
    PPtArray ppts;
public:
    DiskArray::iterator PdiskToItr(DiskState *pdisk){
        for(DiskArray::iterator itr=begin();itr!=end();++itr)if((*itr) == pdisk){
            return itr;
        }
        return end();
    }

    void sortdisk(DiskArray::iterator itr){
        DiskState *temp = *itr;
        while(itr>begin() && temp->used > (*(itr-1))->used){
            *itr = *(itr-1);
            --itr;
        }
        *itr = temp;
    }

    DiskState* adjustitem(std::vector<Item>::iterator itemitr){
    //若塞不下则仍返回包含此 iItem 的临时 DiskState 指针。用完后须 delete
    //若塞下但挤出新物体，则返回包含新物体的 DiskState 指针。用完后须 delete
    //若装下则返回 NULL
        bool flag = true;
        int curuse, maxuse;
        PPtArray tmppt;
        DiskState *tmpdisk = new DiskState;

        tmpdisk->used = itemitr->size;
        tmpdisk->itemidxs.push_back(itemitr-vItems.begin());
        tmppt.Insert(tmpdisk,tmpdisk->calcdp());

        while(flag && !tmpdisk->itemidxs.empty()){
            flag = false;
            maxuse = 0;
            PPtArray::iterator maxfrompptitr;
            PPtArray::iterator maxtopptitr;
            for(PPtArray::iterator frompptitr=tmppt.begin()+1;frompptitr!=tmppt.end();++frompptitr){
                for(PPtArray::iterator topptitr=ppts.begin();
                    topptitr!=ppts.end() && topptitr->size<frompptitr->size;++topptitr){

                        curuse = topptitr->pdisk->used - topptitr->size + frompptitr->size;
                        if(curuse <= DiskCapacity && curuse > maxuse){
                            flag = true;
                            maxuse = curuse;
                            maxfrompptitr = frompptitr;
                            maxtopptitr = topptitr;
                        }
                }
            }
            if(flag){
                if(maxtopptitr->size == 0){
                    DiskState *ptodisk = maxtopptitr->pdisk;
                    DiskState *pfromdisk = maxfrompptitr->pdisk;
                    tmpdisk->moveitems(*ptodisk,maxfrompptitr->size);
                    ppts.DelDisk(ptodisk);
                    ppts.Insert(ptodisk,ptodisk->calcdp());
                    delete tmpdisk;
                    return NULL;
                }
                else {
                    tmpdisk->moveitems(*(maxtopptitr->pdisk),maxfrompptitr->size);
                    maxtopptitr->pdisk->moveitems(*(maxfrompptitr->pdisk),maxtopptitr->size);
                    DiskState *ptodisk = maxtopptitr->pdisk;
                    ppts.DelDisk(ptodisk);
                    ppts.Insert(ptodisk,ptodisk->calcdp());
                    tmppt.clear();
                    tmppt.Insert(tmpdisk,tmpdisk->calcdp());
                }
            }
            else {
                return tmpdisk;
            }
        }
        delete tmpdisk;
        return NULL;
    }

    void adjustdisk(DiskState *pdesdisk){
        bool flag = true;
        int space = DiskCapacity - pdesdisk->used;
        int curuse, maxuse;
        DiskState *pmaxdisk = NULL;
        while(flag){
            flag = false;
            maxuse = 0;
            for(DiskArray::iterator itr=begin();itr!=end();++itr){
                int DPspace_use;
                if(pdesdisk == *itr)continue;
                DPspace_use = (*itr)->DP[space].used;
                if(DPspace_use == 0)continue;
                curuse = pdesdisk->used + DPspace_use;
                if(curuse > (*itr)->used && curuse > maxuse){
                    flag = true;
                    maxuse = curuse;
                    pmaxdisk = *itr;
                }
            }
            if(flag)pmaxdisk->moveitems(*pdesdisk,space);
            ppts.DelDisk(pdesdisk);
            ppts.Insert(pdesdisk,pdesdisk->calcdp());
            if(flag){
                pdesdisk = pmaxdisk;
                space = DiskCapacity - pdesdisk->used;
            }
        }

        stable_sort(begin(),end(),mem_fun(&DiskState::GT));
    }

    void addDisk(const DiskState &disk){
        push_back(new DiskState(disk));
        adjustdisk(*rbegin());
    }

    void enitem(std::vector<Item>::iterator itemitr){
        DiskState *remaindisk = adjustitem(itemitr);
        if(NULL == remaindisk)return;

        remaindisk->moveitems(extra, DiskCapacity - extra.used);
        if(0 == remaindisk->used){
            delete remaindisk;
            return;
        }

        //增加新盘:
        addDisk(extra);
        extra.itemidxs = remaindisk->itemidxs;
        extra.used = remaindisk->used;
        delete remaindisk;
    }

};

DiskArray disks;

class Answer : public vector<DiskUse> {
public:
    Answer(){
        resize(disks.size());
        Answer::iterator itr = begin();
        for(DiskArray::iterator itr2=disks.begin();itr2!=disks.end();++itr,++itr2){
            *itr = *(*itr2);
        }
    }
    friend ostream& operator<<(ostream&, const Answer &);
};

//class AnsVec : public vector< Answer > {
//public:
//    void loganswer(){
//        push_back(Answer());
//    }
//    friend ostream& operator<<(ostream&, const AnsVec &);
//};

ostream& operator<<(ostream &os, const DiskUse &disk){
    double realuse = 0.0;
    for(vector<int>::const_iterator itr=disk.itemidxs.begin();itr!=disk.itemidxs.end();++itr){
        realuse += vItems[*itr].realsize;
    }
    os.setf(ios::fixed);
    os<<"free space:"<<setw(8)<<setprecision(2)<<realcapacity-realuse<<",";
    os.unsetf(ios::floatfield);
    os.precision(6);
    for(vector<int>::const_iterator itr=disk.itemidxs.begin();itr!=disk.itemidxs.end();++itr){
        os<<" "<<vItems[*itr].name<<'('<<vItems[*itr].realsize<<')';
    }
    return os;
}

ostream& operator<<(ostream &os, const Answer &ans){
    os<<"Disk used:"<<ans.size()<<'\t'<<"Disk Capacity:"<<realcapacity<<'\n';
    for(Answer::const_iterator itr=ans.begin();itr!=ans.end();++itr){
        os<<"\tDisk No."<<setw(2)<<itr-ans.begin()+1<<" : "<<*itr<<'\n';
    }
    return os;
}

//ostream& operator<<(ostream &os, const AnsVec &vans){
//    for(AnsVec::const_iterator itr=vans.begin();itr!=vans.end();++itr){
//        os<<*itr<<'\n';
//    }
//    return os;
//}

int main(){
    int nAns;
    ifstream fin("input.txt");
    fin>>realcapacity>>nAns;
    Item::setrate(double(DiskCapacity)/realcapacity);

    char ch;
    double rsize;
    string name;
    while(fin>>ch){
        if(ch==';'){
            while((ch=fin.get())!='\n');
            continue;
        }
        fin.seekg(-1,ios_base::cur);
        if(!(fin>>name))break;
        fin>>rsize;
        vItems.push_back(Item(name,rsize));
    }
    fin.close();

    for(vector<Item>::iterator itr=vItems.begin();itr!=vItems.end();++itr)
        disks.enitem(itr);
    disks.addDisk(extra);

    ofstream fout("output.txt");
    fout<<Answer();

    return 0;
}
*/