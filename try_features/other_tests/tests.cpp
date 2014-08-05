/*
本程序用来试验各种问题
每次新试验都将以前的代码注释掉
*/

//===========================================================================
//===========================================================================
// test template

//#include<algorithm>
//#include<iostream>
////using namespace std;
//
//template<typename T,typename Compare>
//inline T& min(T&a,T&b,Compare comp){
//    return comp(b,a)?b:a;
//}
//
//class X {
//public:
//    int i;
//    X(int ii=0):i(ii){}
//    void modify(){i++;}
//};
//
//bool comp(const X& a,const X& b){
//    return a.i<b.i;
//}
//
//int main(){
//    X a(1),b(2);
//    std::cout<<"before fun:"<<a.i<<' '<<b.i<<std::endl<<std::endl;
//    (min(a,b,comp)).modify();
//    std::cout<<"after fun:"<<a.i<<' '<<b.i<<std::endl;
//
//    system("pause");
//    return 0;
//}

//============================================================================
//============================================================================
// differences of size() max_size() capacity()

//#include<vector>
//#include<iostream>
//using namespace std;
//
//int main(){
//    int arr[]={3,5,33,59,89};
//    vector<int> a(arr,arr+sizeof(arr)/sizeof(arr[0]));
//    a.reserve(20);
//    a.push_back(36);
//    cout<<"empty:"<<a.empty()<<endl;
//    cout<<"size:"<<a.size()<<endl;
//    cout<<"max size:"<<a.max_size()<<endl;
//    cout<<"capacity:"<<a.capacity()<<endl;
//
//    system("pause");
//    return 0;
//}
//
//============================================================================
//============================================================================

//高效判断素数
//设查询的最大数为n，则内存使用为小于sqrt(n)的素数个数个整型变量
//试验中判断为素数的最大数是1000万亿量级，占内存17MB


//#include<vector>
//#include<iostream>
//#include<algorithm>
//#include<math.h>
//
////折半查找
//std::vector<unsigned __int64>::iterator find_bin(const std::vector<unsigned __int64>::iterator &beg,const std::vector<unsigned __int64>::iterator &end,const unsigned __int64 &key){
//    std::vector<unsigned __int64>::iterator low=beg;
//    std::vector<unsigned __int64>::iterator high=end;
//    std::vector<unsigned __int64>::iterator mid;
//    while(low<high){
//        mid=(high-low)/2+low;
//        if(key==(*mid)) return mid;
//        else if(key<(*mid)) high=mid;
//        else low=mid+1;
//    }
//    return end;
//}
//
//bool isPrime(const unsigned __int64 a){
//    static std::vector<unsigned __int64> prime(1,3);
//    if(a<2)return false;
//    if(a==2)return true;
//    if(a%2==0)return false;
//    if(a<=prime.back()){
//        if(find_bin(prime.begin(),prime.end(),a)!=prime.end())return true;//折半查找
//        return false;
//    }
//    const unsigned __int64
//        qa=static_cast<unsigned __int64>(sqrt(static_cast<long double>(a)));
//    for(unsigned __int64 num=prime.back()+2;qa>prime.back();num+=2){
//        if(isPrime(num))prime.push_back(num);
//    }
//    std::vector<unsigned __int64>::iterator pos=prime.begin();
//    for(;pos!=prime.end();++pos){
//        if((*pos)>qa)break;
//        if(a%(*pos)==0)break;
//    }
//    if(pos==prime.end())return true;
//    if((*pos)>qa)return true;
//    return false;
//}
//
////int main(){
////    unsigned __int64 n,total=0;
////    std::cin>>n;
////    for(unsigned __int64 i=n;i>1;--i){
////        if(isPrime(i))++total;
////    }
////    std::cout<<"There are "<<total<<" prime numbers less than "<<n<<std::endl;
////
////    system("pause");
////    return 0;
////}
//
//int main(){
//    unsigned __int64 n,i;
//    std::cin>>n;
//    while(n>0){
//        i=n+1;
//        for(;!isPrime(i);++i);
//        std::cout<<i<<" is the first prime number greater than "<<n<<'.'<<std::endl;
//        std::cin>>n;
//    }
//
//    system("pause");
//    return 0;
//}

//int main(){
//    __int64 maxnum=3;
//    __int64 multi=6;
//    while(isPrime(multi+1)){
//        maxnum+=2;
//        while(!isPrime(maxnum))maxnum+=2;
//        multi*=maxnum;
//    }
//    std::cout<<multi+1<<std::endl;
//
//    maxnum=3;
//    while((multi+1)%maxnum!=0){
//        maxnum+=2;
//        while(!isPrime(maxnum))maxnum+=2;
//    }
//    std::cout<<maxnum<<std::endl;
//
//    system("pause");
//    return 0;
//}

//=========================================================================
//=========================================================================

//#include<iostream>
//using namespace std;
//
///*       black '@'，white 'O' (uppercase letter o)     */
//
//int main(){
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + O + + + + +"<<endl;
//    cout<<"+ + + + + + @ + @ O + + + + +"<<endl;
//    cout<<"+ + + + + + O @ O + + + + + +"<<endl;
//    cout<<"+ + + + + + @ + O O + + + + +"<<endl;
//    cout<<"+ + + + + + @ + + @ + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//    cout<<"+ + + + + + + + + + + + + + +"<<endl;
//
//    system("pause");
//    return 0;
//}

//=======================================================================
//=======================================================================

//#include<iostream>
//#include<fstream>
//#include<vector>
//#include<ios>
//#include<iomanip>
//using namespace std;
//
//class rtot {
//    static vector<float> trstd;
//public:
//    static void init(){
//        ifstream TRSTD("TRSTD.txt");
//        float tmp;
//        while(TRSTD>>tmp)trstd.push_back(tmp);
//        trstd.push_back(252.925);
//        TRSTD.close();
//    }
//    float operator()(float r){
//        if(r<8.68)return 0.0;
//        if(r<=10.0){
//            int idx=((static_cast<int>(100.0*r)-870)/5);
//            return (r-(8.7+idx*0.05))/0.05*(trstd[idx+1]-trstd[idx])+trstd[idx];
//        }
//        if(r<=13.0){
//            int idx=((static_cast<int>(100.0*r)-1000)/10)+26;
//            return (r-(10.0+(idx-26)*0.10))/0.10*(trstd[idx+1]-trstd[idx])+trstd[idx];
//        }
//        if(r<=37.8){
//            int idx=((static_cast<int>(100.0*r)-1300)/20)+56;
//            return (r-(13.0+(idx-56)*0.20))/0.20*(trstd[idx+1]-trstd[idx])+trstd[idx];
//        }
//        if(r<=46.2){
//            int idx=((static_cast<int>(100.0*r)-3780)/40)+180;
//            return (r-(37.8+(idx-180)*0.40))/0.40*(trstd[idx+1]-trstd[idx])+trstd[idx];
//        }
//        return 0.0;
//    }
//};
//
//vector<float> rtot::trstd;
//
//int main(){
//    ifstream fin("R.txt");
//    ofstream fout("T-R.txt");
//    rtot::init();
//
//    float r;
//    fout<<setprecision(3);
//    fout.setf(ios::fixed);
//    while(fin>>r){
//        fout<<rtot(r)<<'\t'<<r<<endl;
//    }
//
//    return 0;
//}

//========================================================================
//========================================================================
//随机密码产生器

//#include<iostream>
//#include<vector>
//#include"random"
//#include<string>
//using namespace std;
//
//int main(){
//    char judge;
//    int length;
//    vector<char> alwords;
//    cout<<"allow letters?[y/n]:";
//    cin>>judge;
//    if(judge=='y'||judge=='Y'){
//        for(char ch='A';ch<='Z';++ch){
//            alwords.push_back(ch);
//        }
//        cout<<"capitals sensitive?[y/n]:";
//        cin>>judge;
//        if(judge=='y'||judge=='Y'){
//            for(char ch='a';ch<='z';++ch){
//                alwords.push_back(ch);
//            }
//        }
//    }
//    cout<<"allow numbers?[y/n]:";
//    cin>>judge;
//    if(judge=='y'||judge=='Y'){
//        for(char ch='0';ch<='9';++ch){
//            alwords.push_back(ch);
//        }
//    }
//    cout<<"allow symbols?[y/n]:";
//    cin>>judge;
//    if(judge=='y'||judge=='Y'){
//        cout<<"choose 'y' to use default symbols or 'n' to indicates special ones.[y/n]:";
//        cin>>judge;
//        if(judge=='y'||judge=='Y'){
//            for(char ch='!';ch<='/';++ch)alwords.push_back(ch);
//            for(char ch=':';ch<='@';++ch)alwords.push_back(ch);
//            for(char ch='[';ch<='`';++ch)alwords.push_back(ch);
//            for(char ch='{';ch<='~';++ch)alwords.push_back(ch);
//        }
//        else {
//            string symbol;
//            cout<<"input the special symbols:(no spaces devides)"<<endl;
//            cin>>symbol;
//            for(int i=0;i<symbol.length();++i)alwords.push_back(symbol[i]);
//        }
//    }
//    if(alwords.empty()){
//        cout<<"no available character..."<<endl;
//        system("pause");
//        return -1;
//    }
//    cout<<"input the length of the psword to build:";
//    cin>>length;
//    cout<<"input '0' to exit this program...\n\n"<<endl;
//    char ex;
//    cin.get(ex);
//
//    while(ex!='0'){
//        for(int i=0;i<length;++i){
//            int idx=static_cast<int>(random()*alwords.size());
//            cout<<alwords[idx];
//        }
//        cout<<endl;
//        cin.get(ex);
//    }
//
//    return 0;
//}

//=======================================================================
//=======================================================================
// iostream 的 iterator

//#define DEQUE

//#include<iostream>
//#include<algorithm>
//
//#ifdef DEQUE
//#include<deque>
//#else
//#include<vector>
//#endif
//
//using namespace std;
//
//int main(){
//
//#ifdef DEQUE
//    deque<int> abc;
//#else
//    vector<int> abc;
//#endif
//    for(int i=0;i<10;++i){
//        abc.push_back(i);
//    }
//
//#ifdef DEQUE
//    for(int i=0;i<5;++i){
//        abc.push_front(i);
//    }
//#endif
//    copy(abc.begin(),abc.end(),ostream_iterator<int>(cout," "));
//    cout<<endl;
//
//    abc.resize(abc.size()/2);
//    copy(abc.begin(),abc.end(),ostream_iterator<int>(cout," "));
//    cout<<endl;
//
//    system("pause");
//    return 0;
//}

//==============================================================================
//==============================================================================
/* no problem */

//#include<iostream>
//using namespace std;
//
//class A
//{
//private:
//	int num;
//public:
//	A(int n=0){num=n;}
//    friend bool operator==(A &a,A &b);
//}; 
//
//bool operator==(A &a,A &b)
//{
//	if(a.num==b.num)
//		return true;
//	else 
//		return false;
//}
//
//int main()
//{
//	A a1(10);
//	A b1(1)	;
//	if(a1==b1)
//		cout<<"a1==b1";
//	else 
//		cout<<"a1!=b1";
//
//    cin.get();
//	return 0;
//}

//===============================================================================
//===============================================================================
// 比较 C printf() 与 C++ cout 的效率么？

////#define ANSIC
//#ifdef ANSIC
//
//#include<stdio.h>
//void main(){
//    for(int i=0;i<30000;++i){
//        for(int j=0;j<300;++j)printf("%d ",j);
//        printf("\n");
//    }
//}
//
////-----------------------------------------------------------
//#else
//
//#include<iostream>
//using namespace std;
//int main(){
//    for(int i=0;i<30000;++i){
//        for(int j=0;j<300;++j)cout<<j<<' ';
//        cout<<'\n';
//    }
//    return 0;
//}
//
//#endif

//================================================================================
//================================================================================
// 字符串与各数字类型的转换

//#include<iostream>
//#include<sstream>
//using namespace std;
//
//int main(){
//    int a;
//    float b;
//    double c;
//    stringstream tempstream;
//    string instring;
//
//    cout<<"Input an int, a float and a double num:"<<endl;
//
//    getline(cin,instring,'\n');
//    tempstream<<instring;
//    tempstream>>a>>b>>c;
//
//    cout<<a<<' '<<b<<' '<<c<<endl;
//    system("pause");
//    return 0;
//}

//==================================================================================
//==================================================================================

//main(a){printf(a,34,a="main(a){printf(a,34,a=%c%s%c,34);}",34);getch();}   

//==================================================================================
//==================================================================================

//写一个组合类

//用法
//int main(){
//    combination com;
//    com.init(6,4);
//
//    while(com.next()){
//        for(int i=0;i<4;++i){
//            cout<<com[i]<<' ';
//        }
//        cout<<endl;
//    }
//    system("pause");
//    return 0;
//}

//输出
//0 1 2 3
//0 1 2 4
//0 1 2 5
//0 1 3 4
//0 1 3 5
//0 1 4 5
//0 2 3 4
//0 2 3 5
//0 2 4 5
//0 3 4 5
//1 2 3 4
//1 2 3 5
//1 2 4 5
//1 3 4 5
//2 3 4 5

//#include<vector>
//#include<iostream>
//using namespace std;
//
//class combination {
//    vector<size_t> vec;
//    int n;
//    int r;
//public:
//    bool init(int N, int r){
//        if(N<r || N<1 || r<1)return false;
//        combination::n=N;
//        combination::r=r;
//        vec.resize(r);
//        for(int i=0;i<r;++i)vec[i]=i;
//        vec[r-1]=r-2;
//        return true;
//    }
//    bool next(void){
//        if(vec.empty())return false;
//        int i=r-1;
//        while((int)vec[i]>=n-r+i){
//            --i;
//            if(i<0)return false;    //循环结束
//        }
//        size_t tmp=vec[i];
//        for(int idx=i;idx<r;++idx){
//            vec[idx]=++tmp;
//        }
//        return true;
//    }
//    size_t operator[](const int i)const{
//        return vec[i];
//    }
//};

//======================================================================================
//======================================================================================
//使用举例

//int main(){
//    int n=0;
//    arrange pailie(n);
//    while(pailie.next()){
//        for(int i=0;i<n;++i)cout<<pailie[i]<<' ';
//        cout<<endl;
//    }
//
//    cout<<"======================="<<endl;
//    n=2;
//    pailie.init(n);
//    while(pailie.next()){
//        for(int i=0;i<n;++i)cout<<pailie[i]<<' ';
//        cout<<endl;
//    }
//    cout<<"%%%%%%%%%%%%%%%%%%%%%%"<<endl;
//    cout<<"||||||||||||||||||||||"<<endl;
//    n=4;
//    pailie.init(n);
//    while(pailie.next()){
//        for(int i=0;i<n;++i)cout<<pailie[i]<<' ';
//        cout<<endl;
//    }
//
//    cout<<"======================="<<endl;    //可以连续使用
//    while(pailie.next()){
//        for(int i=0;i<n;++i)cout<<pailie[i]<<' ';
//        cout<<endl;
//    }
//    system("pause");
//    return 0;
//}

// 全排列类

//#ifndef _ARRANGE_
//#define _ARRANGE_
//#include<vector>
//
//class arrange{
//    std::vector<int> vec;
//    int n;
//    int m;
//    int im;
//    int idx;
//    int direct;
//    bool turn;
//public:
//    arrange(void){}
//    arrange(int N):n(N),m(1),im(-1),idx(N-1),direct(1),turn(true){
//        if(N<1)return;
//        switch(N){
//            default:
//                vec.reserve(N);
//                for(int i=0;i<N;++i)vec.push_back(i);
//                swap(vec[0],vec[1]);
//                for(int i=3;i<N;++i)m*=i;
//                break;
//            case 1:
//                im=0;
//                vec.push_back(0);
//                break;
//            case 2:
//                im=0;
//                vec.push_back(1);
//                vec.push_back(0);
//                break;
//        }
//    }
//    bool init(int N){
//        if(N<1)return false;
//        vec.clear();
//        switch(N){
//            default:
//                vec.reserve(N);
//                for(int i=0;i<N;++i)vec.push_back(i);
//                swap(vec[0],vec[1]);
//                n=N;m=1;im=-1;idx=N-1;direct=1;turn=true;
//                for(int i=3;i<N;++i)m*=i;
//                break;
//            case 1:
//                im=0;
//                vec.push_back(0);
//                break;
//            case 2:
//                im=0;
//                vec.push_back(1);
//                vec.push_back(0);
//                break;
//        }
//        return true;
//    }
//    int operator[](int i)const{
//        return vec[i];
//    }
//    bool next(){
//        if(n<1)return false;
//        switch(n){
//            default:
//                if( idx==n-1 && turn ){
//                    ++im;
//                    if(im >= m){
//                        im=-1;
//                        return false;
//                    }
//                    swap(vec[0],vec[1]);
//                    turn=false;
//                    direct=-direct;
//                    return true;
//                }
//                if( idx==0 && turn ){
//                    swap(vec[n-1],vec[n-2]);
//                    turn=false;
//                    direct=-direct;
//                    return true;
//                }
//                swap(vec[idx],vec[idx+direct]);
//                idx+=direct;
//                if(idx==n-1 || idx==0)turn=true;
//                break;
//            case 1:
//                if(1 == im){
//                    im=0;
//                    return false;
//                }
//                else ++im;
//                break;
//            case 2:
//                if(2 == im){
//                    im=0;
//                    return false;
//                }
//                else {
//                    ++im;
//                    swap(vec[0],vec[1]);
//                }
//                break;
//        }
//        return true;
//    }
//};
//
//#endif

//================================================================================
//================================================================================

//==============
//f0905.cpp
//对象成员的默认构造
//==============
//#include<iostream>
//#include<string>
//using namespace std;
//class studentID{
//	int value;
//public:
//	studentID(){
//	static int nextstudentid=0;
//	value=++nextstudentid;
//	cout<<"Assigning student id "<<value<<"\n";
//	}
//};
//class student{
//	string name;
//	studentID id;
//public:
//	student(string n="Noname"){
//		cout<<"Constructing student "+n+"\n";
//		name=n;
//	}
//};
//int main(){
//	student s("Randy");
//    system("pause");
//    return 0;
//}

//==================================================================================
//==================================================================================

//测试 limits

//#include<fstream>
//#include<iostream>
//#include<limits>
//#include<iomanip>
//#include<cmath>
//using namespace std;
//
//const double dbepsilon=100.0*numeric_limits<double>::epsilon();
//
//int main(){
//    ifstream fin("input.txt");
//    //double a=2.0/3.0;
//    //double b=20.0/3.0;
//    double a,b;
//
//    fin>>a>>b;
//    double c=asin(asin(asin(asin(asin(asin(sin(sin(sin(sin(sin(sin(a))))))))))));
//
//    cout<<"precision="<<numeric_limits<double>::digits10<<endl;
//    cout.precision(numeric_limits<double>::digits10+2);
//
//    cout<<fixed<<"e="<<numeric_limits<double>::epsilon()<<endl;
//    cout<<"a="<<a<<endl;
//    cout<<"c="<<c<<endl;
//    if( abs(c-a) < (dbepsilon) ){
//        cout<<"equal!"<<endl;
//    }
//    else {
//        cout<<"not equal!"<<endl;
//    }
//
//    system("pause");
//}

//===========================================================================
//===========================================================================
// algorithm std::rotate()

//#include<vector>
//#include<algorithm>
//#include<iterator>
//#include<iostream>
//using namespace std;
//
//int main(){
//    vector<int> vec;
//    for(int i=1;i<=10;++i)vec.push_back(i);
//    vector<int>::iterator iter;
//    rotate(vec.begin()+3,vec.begin()+4,vec.end());
//    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
//    cout<<endl;
//    system("pause");
//    return 0;
//}

//============================================================================
//============================================================================
// algorithm std::transform()
// toupper() tolower()

//#include<iostream>
//#include<algorithm>
//#include<iterator>
//using namespace std;
//
//int main(){
//    transform(istream_iterator<char>(cin),istream_iterator<char>(),ostream_iterator<char>(cout),toupper);
//    system("pause");
//    return 0;
//}

//=============================================================================
//=============================================================================
//作为基类的类一定要定义虚析构函数(否则delete时只能调用基类的析构函数)
//纯虚函数不代表不能出现函数体，只是说明这个类是一个抽象类，不能出现对象实体
//而作为基类的抽象类一定要定义纯虚析构函数的函数体，因为它会在派生类的对象删除时
//被链接调用。。。不定义的话必然出现link error

//#include<iostream>
//using namespace std;
//class base{
//public:
//    base(void){}
//    //~base();
//    virtual ~base()=0;
//};
//
//base::~base(){
//    cout<<"base delete..."<<endl;
//}
//
//class derived:public base{
//public:
//    ~derived(){
//        cout<<"derived delete..."<<endl;
//    }
//};
//
//int main(){
//    base *bp;
//    bp=new derived;
//    delete bp;
//
//    system("pause");
//}

//=================================================
//=================================================
// 多态、构造函数、析构函数、虚析构函数、静态成员变量

//#include <iostream> 
//using namespace std;
//class Value 
//{ 
//public: 
//    Value(int nVal){m_nVal = nVal;printf("Call Value::Value(int nValue)\n");} 
//    ~Value(){printf("Call Value::~Value()\n");system("pause");} 
//    Value& operator=(int nVal){m_nVal = nVal;printf("Call Value::operator=\n");return *this;} 
//    void Dump(){printf("Value::m_nVal=%d\n",m_nVal);} 
//protected: 
//    int m_nVal; 
//}; 
//
//class Base 
//{ 
//public: 
//    Base(){Init();} 
//    virtual ~Base(){Release();} 
//    virtual void Init(){printf("Call Base::Init()\n");} 
//    virtual void Release(){printf("Call Base::Release()\n");} 
//    virtual void Dump(){printf("Call Base::Dump()\n");} 
//}; 
//
//
//class Derive:public Base 
//{ 
//public: 
//    Derive(){printf("Call Derive::Derive()\n");} 
//    ~Derive(){printf("Call Derive::~Derive()\n");} 
//    virtual void Init(){m_Val=2;printf("Call Derive::Init()\n");} 
//    virtual void Release(){printf("Call Derive::Release()\n");} 
//    virtual void Dump(){m_Val.Dump();} 
//protected: 
//    static Value m_Val; 
//}; 
//
////Value Derive::m_Val=0; 
//
//void DestroyObj(Base* pOb) 
//{ 
//    pOb->Dump(); 
//    delete pOb; 
//} 
//
//int main() 
//{ 
//    Derive *pOb = new Derive; 
//    DestroyObj(pOb); 
//
//    return 0; 
//} 

//==============================================================
//==============================================================
// demostration of usage of zlib ...........

//#include<iostream>
//#include<string>
//#include<zlib.h>
//using namespace std;
//
//char source[] = "hello world!\n\
//    aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
//    aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
//    aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\
//    aaaaa bbbbb ccccc ddddd aaaaa bbbbb ccccc ddddd中文测试 中文测试\n";
//
//int main(){
//    unsigned long srcLeng = sizeof(source);
//    unsigned long desLeng = srcLeng * 1.5 + 15;
//    unsigned char *pBuffer = new unsigned char[desLeng];
//    compress(pBuffer, &desLeng, (Bytef*)source, srcLeng);
//    string str((char*)pBuffer, desLeng);
//    cout<<srcLeng<<' '<<desLeng<<endl;
//    cout<<source<<endl;
//    cout<<string((char*)pBuffer, desLeng)<<'\n'<<endl;
//    delete [] pBuffer;
//
//    desLeng = sizeof(source) + 10;
//    pBuffer = new unsigned char[desLeng];
//    uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());
//    cout<<string((char*)pBuffer, desLeng)<<endl;
//    system("pause");
//    return 0;
//}

//=================================================================
//=================================================================
// Is std::string has a reference-count

//#include<string>
//#include<ctime>
//#include<iostream>
//
//int main(){
//    std::string str1("uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());\
//        uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());");
//    std::string str2;
//    char cch1[] = "uncompress(pBuffer, &desLeng, (Bytef*)str.c_str(), str.length());";
//    char cch2[sizeof(cch1)];
//
//    std::cout<<"Begin copying cstrings..."<<std::endl;
//    clock_t start = clock();
//    for(int i=1; i<500000; ++i){
//        strcpy(cch2, cch1);cch2[0]++;
//        strcpy(cch1, cch2);cch1[1]--;
//    }
//    clock_t finish = clock();
//    std::cout<<"Copying cstrings finished."<<std::endl;
//    std::cout<<"cstring time:\t"<<finish - start<<'\n'<<std::endl;
//
//    std::cout<<"Begin copying cpp strings..."<<std::endl;
//    start = clock();
//    for(int i=1; i<500000; ++i){
//        str2.assign(str1);/*str2[0]++;*/
//        str2.assign(str2);/*str1[1]--;*/
//    }
//    finish = clock();
//    std::cout<<"Copying cpp strings finished."<<std::endl;
//    std::cout<<"Cpp string time:\t"<<finish - start<<'\n'<<std::endl;
//
//    system("pause");
//    return 0;
//}

// conclusion: not use a reference-count...
// in VC6.0 it used reference-count , but after VC7.1 this had been removed, for thread safe...

//=================================================================
//=================================================================
// 实验空串时 str.c_str() 返回 NULL 还是一个指向 '\0' 的指针
// 经验证空串时返回一个指向 '\0' 的指针。
// "" (空串常量) 返回的也是一个有效地址。

//#include<string>
//#include<iostream>
//using namespace std;
//
//int main(){
//    string str;
//    if(str.c_str() == NULL)
//        cout<<"str.c_str() == NULL"<<endl;
//    else
//        cout<<"str.c_str() != NULL"<<endl;
//
//    if(*str.c_str() == '\0')
//        cout<<"*str.c_str() == \'\\0\'"<<endl;
//    else
//        cout<<"*str.c_str() != \'\\0\'"<<endl;
//
//    if(0 == "")
//        cout<<"0 == \"\""<<endl;
//    else
//        cout<<"0 != \"\""<<endl;
//
//    system("pause");
//    return 0;
//}

//=================================================================
//=================================================================
// 写自己的 string 类，实现 引用计数与写时拷贝
// 学习关联类的功能结构设计。
// strcpy() 函数复制时连带最后的 null 一起复制。

//#include<cassert>
//#include<cstring>
////#include<cctype>
//#include<locale>
////#include<algorithm>
//
//class StringVal {
//    char * _buf;
//    size_t _len;
//    size_t _capacity;
//public:
//    typedef unsigned size_t;
//    StringVal(const char *p = 0){
//        if(p != 0) Init(p);
//        else Init("");
//    }
//    StringVal(const StringVal &str){
//        if(str.c_str() != 0) Init(str.c_str());
//        else Init("");
//    }
//    ~StringVal(){
//        delete [] _buf;
//    }
//    const char *c_str() const {return _buf;}        // the return value must be a valid address
//    StringVal& operator=(const char *p){
//        assert(_buf != 0);
//        size_t len;
//        if(p == 0){                                 // the string to copy is empty...
//            clear();
//        } else if(_capacity < (len = strlen(p))){   // the size of buf is not enough
//            delete [] _buf;
//            Init(p);
//        } else {                                    // size is enough
//            _len = len;
//            strcpy(_buf, p);
//        }
//        return *this;
//    }
//    StringVal& operator=(const StringVal &str){
//        assert(_buf != 0);
//        if(_capacity < str.len()){
//            delete [] _buf;
//            Init(str.c_str());
//        } else {
//            _len = str.len();
//            strcpy(_buf, str.c_str());
//        }
//        return *this;
//    }
//    size_t len(void) const {
//        return _len;
//    }
//    bool empty(void) const {
//        return _len == 0;
//    }
//    void clear(void){
//        assert(_buf != 0);
//        _len = 0;
//        _buf[0] = '\0';
//    }
//    void UpcaseAll(void){
//        assert(_buf != 0);
//        //std::transform(_buf, _buf+_len, _buf, toupper);
//        std::use_facet<std::ctype<char> >(std::locale("C")).toupper(_buf, _buf+_len);
//    }
//private:
//    void Init(const char *p){
//        assert(p != 0);
//        _len = strlen(p);
//        _buf = new char[_len + 1];
//        _capacity = _len;
//        strcpy(_buf, p);
//    }
//};
//
//#include<iostream>
//using namespace std;
//
//istringstream isstr;
//
//int main(){
//    StringVal str1("abc");
//    std::cout<<str1.c_str()<<' '<<str1.len()<<std::endl;
//    str1 = "defg";
//    std::cout<<str1.c_str()<<' '<<str1.len()<<std::endl;
//    str1.UpcaseAll();
//    std::cout<<str1.c_str()<<' '<<str1.len()<<std::endl;
//
//    system("pause");
//    return 0;
//}

//========================================================
//========================================================
// 实验 list::size() 和 list::splice() 的时间复杂度

//#include<iostream>
//#include<list>
//#include<ctime>
//using namespace std;
//
//int main(){
//    time_t start, finish;
//    int num = 0;
//    list<int> coll;
//
//    start = clock();
//    for(int i=0;i<10000;++i){
//        coll.push_back(i);
//        num += coll.size();
//    }
//    finish = clock();
//    cout<<finish - start<<"   num:"<<num<<endl;
//
//    coll.clear();
//    start = clock();
//    for(int i=0;i<10000;++i){
//        coll.push_back(i);
//    }
//    finish = clock();
//    cout<<finish - start<<endl;
//    system("pause");
//    return 0;
//}

//#include<iostream>
//#include<list>
//#include<ctime>
//using namespace std;
//
//int main(){
//    time_t start,finish;
//    list<int> col;
//    col.push_back(1);
//    col.push_back(10000);
//
//    list<int> col2;
//    start = clock();
//    for(int i=2;i<10000;++i)
//        col2.push_back(i);
//    finish = clock();
//    cout<<finish - start<<endl;
//
//    int num = 0;
//    start = clock();
//    for(int i=0;i<10000;++i){
//        col.splice(++col.begin(),col2,++col2.begin(),--col2.end());
//        num += *(++col.begin());
//        col2.splice(++col2.begin(),col,++col.begin(),--col.end());
//        num += *(++col2.begin());
//    }
//    finish = clock();
//    cout<<finish - start<<"   num:"<<num<<endl;
//    system("pause");
//    return 0;
//}

//==============================================================
//==============================================================
//#include<iostream>
//#include<limits>
//#include<vector>
//#include<algorithm>
//#include<iterator>
//#include<iomanip>
//using namespace std;
//
//int main(){
//    cout<<setw(25)<<"int digits:\t"<<setw(5)<<numeric_limits<int>::digits<<endl;
//    cout<<setw(25)<<"float digits:\t"<<setw(5)<<numeric_limits<float>::digits<<endl;
//    cout<<setw(25)<<"double digits:\t"<<setw(5)<<numeric_limits<double>::digits<<endl;
//    cout<<setw(25)<<"unsigned digits:\t"<<setw(5)<<numeric_limits<unsigned>::digits<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int digits10:\t"<<setw(5)<<numeric_limits<int>::digits10<<endl;
//    cout<<setw(25)<<"float digits10:\t"<<setw(5)<<numeric_limits<float>::digits10<<endl;
//    cout<<setw(25)<<"double digits10:\t"<<setw(5)<<numeric_limits<double>::digits10<<endl;
//    cout<<setw(25)<<"unsigned digits10:\t"<<setw(5)<<numeric_limits<unsigned>::digits10<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int radix:\t"<<setw(5)<<numeric_limits<int>::radix<<endl;
//    cout<<setw(25)<<"float radix:\t"<<setw(5)<<numeric_limits<float>::radix<<endl;
//    cout<<setw(25)<<"double radix:\t"<<setw(5)<<numeric_limits<double>::radix<<endl;
//    cout<<setw(25)<<"unsigned radix:\t"<<setw(5)<<numeric_limits<unsigned>::radix<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int min_exponent:\t"<<setw(5)<<numeric_limits<int>::min_exponent<<endl;
//    cout<<setw(25)<<"float min_exponent:\t"<<setw(5)<<numeric_limits<float>::min_exponent<<endl;
//    cout<<setw(25)<<"double min_exponent:\t"<<setw(5)<<numeric_limits<double>::min_exponent<<endl;
//    cout<<setw(25)<<"unsigned min_exponent:\t"<<setw(5)<<numeric_limits<unsigned>::min_exponent<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int min_exponent10:\t"<<setw(5)<<numeric_limits<int>::min_exponent10<<endl;
//    cout<<setw(25)<<"float min_exponent10:\t"<<setw(5)<<numeric_limits<float>::min_exponent10<<endl;
//    cout<<setw(25)<<"double min_exponent10:\t"<<setw(5)<<numeric_limits<double>::min_exponent10<<endl;
//    cout<<setw(25)<<"unsigned min_exponent10:\t"<<setw(5)<<numeric_limits<unsigned>::min_exponent10<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int epsilon():\t"<<setw(5)<<numeric_limits<int>::epsilon()<<endl;
//    cout<<setw(25)<<"float epsilon():\t"<<setw(5)<<numeric_limits<float>::epsilon()<<endl;
//    cout<<setw(25)<<"double epsilon():\t"<<setw(5)<<numeric_limits<double>::epsilon()<<endl;
//    cout<<setw(25)<<"unsigned epsilon():\t"<<setw(5)<<numeric_limits<unsigned>::epsilon()<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"float round_error():\t"<<setw(5)<<numeric_limits<float>::round_error()<<endl;
//    cout<<setw(25)<<"double round_error():\t"<<setw(5)<<numeric_limits<double>::round_error()<<endl;
//    cout<<endl;
//
//    cout<<((numeric_limits<int>::round_style == std::round_toward_zero)?"True":"False")<<endl;
//    cout<<endl;
//
//    cout<<setw(25)<<"int has_infinity:\t"<<setw(5)<<numeric_limits<int>::has_infinity<<endl;
//    cout<<setw(25)<<"int infinity():\t"<<setw(5)<<numeric_limits<int>::infinity()<<endl;
//    cout<<setw(25)<<"float has_infinity:\t"<<setw(5)<<numeric_limits<float>::has_infinity<<endl;
//    cout<<setw(25)<<"float infinity():\t"<<setw(5)<<numeric_limits<float>::infinity()<<endl;
//    cout<<setw(25)<<"double has_infinity:\t"<<setw(5)<<numeric_limits<double>::has_infinity<<endl;
//    cout<<setw(25)<<"double infinity():\t"<<setw(5)<<numeric_limits<double>::infinity()<<endl;
//    cout<<endl;
//
//    int init[] = {5,3,2,4,1,7,10};
//    vector<int> coll(init, init+sizeof(init)/sizeof(init[0]));
//    if(coll.size() > 1){
//        using namespace std::rel_ops;
//        sort(++coll.begin(), coll.end());
//    }
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//
//    system("pause");
//}

//=====================================================================
//////////////////////////////////////////////////////////////////////////
// VC 的 STL 对标准支持还是有问题，考虑所有平台和编译器都统一为 STLport

//#include<algorithm>
//#include<vector>
//#include<iostream>
//#include<iterator>
//using namespace std;
//
//class IntSeq{
//    int value;
//public:
//    IntSeq(int InitVal):value(InitVal){}
//    int operator()(){
//        return value++;
//    }
//};
//
//int main(){
//    vector<int> coll;
//    IntSeq seq(1);
//
//    generate_n<back_insert_iterator<vector<int> >,
//        vector<int>::difference_type, IntSeq&>  // IntSeq& reference has no effect in VC, but it works in g++
//        (back_inserter(coll), 4, seq);
//    generate_n(back_inserter(coll), 4, IntSeq(42));
//    generate_n(back_inserter(coll), 4, seq);
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//    system("pause");
//}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//#include<iostream>
//#include<list>
//#include<algorithm>
//#include<iterator>
//using namespace std;
//
//class Nth{
//    int nth;
//    int count;
//public:
//    Nth(int n):nth(n), count(0){}
//    bool operator()(int){
//        return ++count == nth;
//    }
//};
//
//int main(){
//    list<int> coll;
//    for(int i=1; i<=9; ++i)
//        coll.push_back(i);
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//
//    list<int>::iterator pos;
//    pos = remove_if(coll.begin(), coll.end(), Nth(3));
//    coll.erase(pos, coll.end());
//
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//#include<iostream>
//#include<algorithm>
//#include<functional>
//#include<vector>
//#include<iterator>
//using namespace std;
//
//int main(){
//    vector<int> coll;
//    coll.insert(coll.end(), 4, 0);
//    coll.insert(coll.end(), 3, 1);
//
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
///*
//    std::prev_permutation(coll.begin(), coll.end());
//    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//*/
//    while(next_permutation(coll.begin(), coll.end())){
//        copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
//        cout<<endl;
//    }
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <functional>
//using namespace std;
///*
//typedef (const string&) constStringRef;
//typedef (const string )  constString;
////typedef      string&       StringRef;
//*/
/////------------------------------------------------
//class Test
//{
//public:
//    Test(int a, const string& b)
//        :_a(a), _b(b){    }
//    ~Test()    {}
//    bool compareByInt( const int a){
//        return a == _a;
//    }
//    bool compareByString(const string b){
//        return b == _b;
//    }
//    bool compareByStringRef(const string& b){  //<-------- const string& b
//        return b == _b;
//    }
//    int _a;
//    string _b;
//    void print(){
//        cout << "<" << _a << "," << _b << ">,  " ;
//    }
//};
//void print();
/////------------------------------------------------
//vector < Test > vt;
/////------------------------------------------------
//int main()
//{
//    vt.push_back(Test(1, "A"));
//    vt.push_back(Test(2, "B"));
//    vt.push_back(Test(3, "C"));
//    vt.push_back(Test(4, "D"));
//    print();
//    
//    //--运行OK------------------------------------
//    vt.erase( remove_if(vt.begin(), vt.end(),
//        bind2nd( mem_fun_ref<bool,Test, const  int>(&Test::compareByInt)
//            , 2 )
//            ),
//        vt.end());
//    print();
//
//
//    //--运行OK------------------------------------
//    vt.erase( remove_if(vt.begin(), vt.end(),
//        bind2nd( mem_fun_ref<bool,Test, const string>(&Test::compareByString)
//        , "D" )
//        ),
//        vt.end());
//    print();
//
//    /*---编译错误-----------------------------------
//    1>...\....\functional(312) : error C2529: '_Right' : reference to reference is illegal
//        我想使用compareByStringRef(const string& b),因为这比compareByString(const string b)效率高,
//    可是无法编译,怎么办? 难道是应该用mem_funX_XXX系列中的其他几个?
//    */
//    vt.erase( remove_if(vt.begin(), vt.end(),
//        bind2nd( mem_fun_ref/*<bool,Test,const string& >*/(&Test::compareByStringRef)
//        , "A" )
//        ),
//        vt.end());
//    print();
//
//    return 1;
//}
/////------------------------------------------------
//void print()
//{
//    vector < Test > ::iterator i = vt.begin();
//    vector < Test > ::iterator e = vt.end();
//    for(; i!=e; ++i){
//        i->print();
//    }
//    cout << endl;
//}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 实验 random_shuffle() 是否需要 rand() 函数。
// 结论是需要。因此调用 random_shuffle() 函数前须先设定 srand(unsigned(time(NULL)));

//#include<iostream>
//#include<iterator>
//#include<vector>
//#include<algorithm>
//#include<cstdlib>
//#include<ctime>
//using namespace std;
//
//int main(){
//    vector<int> vec;
//    for(int i=0; i<10; ++i)vec.push_back(i);
//    //srand((size_t)time(NULL));
//    random_shuffle(vec.begin(), vec.end());
//    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout," "));
//    cout<<RAND_MAX<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 对 1 2 7 8 插入 5 ，看 lower_bound() 和 upper_bound() 的返回位置

//#include<algorithm>
//#include<iostream>
//#include<deque>
//#include<iterator>
//using namespace std;
//
//int main(){
//    deque<int> deq;
//    deq.push_back(1);
//    deq.push_back(2);
//    deq.push_back(5);
//    deq.push_back(7);
//    deq.push_back(8);
//    cout<<"deque: ";
//    copy(deq.begin(), deq.end(), ostream_iterator<int>(cout, " "));
//    cout<<"\n";
//
//    cout<<"lower_bound: "<<*lower_bound(deq.begin(), deq.end(), 5)<<"\n";
//    cout<<"upper_bound: "<<*upper_bound(deq.begin(), deq.end(), 5)<<"\n";
//    system("pause");
//}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// test of vector<bool>
//#include<vector>
//#include<algorithm>
//#include<functional>
//#include<iterator>
//#include<iostream>
//using namespace std;
//int main(){
//    vector<bool> bvec(10);
//    for_each(bvec.begin(), bvec.end(), mem_fun_ref(&vector<bool>::reference::flip));
//    copy(bvec.begin(), bvec.end(), ostream_iterator<bool>(cout,""));
//    cout<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// use of bitset
//#include<bitset>
//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<iterator>
//using namespace std;
//int main(){
//    enum Color {
//        red, yellow, green, blue, white, black, pink, numColors
//    };
//
//    bitset<numColors> usedColors;
//
//    usedColors.set(red);
//    usedColors.set(blue);
//
//    cout<<"bitfield of used colors: "<<usedColors<<endl;
//    cout<<"number of used colors: "<<usedColors.count()<<endl;
//    cout<<"bitfield of unused colors: "<<~usedColors<<'\n'<<endl;
//
//    if(usedColors.any()){
//        for(int c=0; c<numColors; ++c){
//            if(usedColors[(Color)c]){cout<<c<<" ";}
//        }
//    }
//
//    string str;
//    str = usedColors.to_string();
//    cout<<str<<endl;
//    bitset<10> b10(string("1101"));
//    cout<<b10<<" "<<b10.to_ulong()<<endl;
//    if(b10.any()){
//        for(int c=0; c<10; ++c){
//            if(b10[(size_t)c]){cout<<c<<" ";}
//        }
//    }
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 外企笔试题

// 1.
//typedef struct bitstruct{
//    int b1:5;
//    int :2;
//    int b2:2;
//}bitstruct;
//
//void main(){
//    bitstruct b;
//    memcpy(&b,"EMC EXAMINATION",sizeof(b));
//    printf("%d,%d\n", b.b1, b.b2);
//    /* 在Linux上测试得到 5 -2，不明白的是b.b1和b.b2代表的是什么？ */
//}

// 2.
//#define MAX 255
//int main(){
//    unsigned char A[MAX+1],i;
//    for(i=0;i <=MAX;i++)
//        A[i]=i;
//    printf("%d\n",A[0]);
//    return 0;
//}
// i is unsigned char (0~255), so when i = 255, i++, then i become 0 again.
// 死循环

// 3.
//#include<iostream>
//using namespace std;
//void main(){
//    float a = 1.0f;
//    cout <<"&a :\t\t"<< &a << endl;
//    cout <<"(int)&a :\t"<< (int)&a << endl;
//    cout <<"(int&)a :\t"<< (int&)a << endl;
//    cout << boolalpha << ( (int)a == (int&)a ) << endl; // 输出什么？
//    float b = 0.0f;
//    cout <<"(int)b :\t"<< (int)b << endl;
//    cout <<"(int&)b :\t"<< (int&)b << endl;
//    cout << boolalpha << ( (int)b == (int&)b ) << endl; // 输出什么？
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// bitset 's count method

//#include<iostream>
//#include<bitset>
//#include<string>
//using namespace std;
//
//int main(){
//    //bitset<7> b(string("1101"));
//    bitset<3> b(unsigned(900));
//    cout<<b.count()<<endl;
//    cout<<b<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Does partial_sort_copy modifies the first range?
//#include<iostream>
//#include<iterator>
//#include<algorithm>
//#include<vector>
//#include<ctime>
//using namespace std;
//
//int main(){
//    vector<int> vec;
//    for(int i=1; i<11; ++i)vec.push_back(i);
//    srand((unsigned)time(NULL));
//    random_shuffle(vec.begin(), vec.end());
//
//    cout<<"vec before partial_sort_copy:\n";
//    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//    vector<int> destvec(4);
//    partial_sort_copy(vec.begin(), vec.end(), destvec.begin(), destvec.end());
//
//    cout<<"destvec: ";
//    copy(destvec.begin(), destvec.end(), ostream_iterator<int>(cout, " "));
//    cout<<"\nvec after partial_sort_copy:\n";
//    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
//    cout<<endl;
//    system("pause");
//}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// performance of valarray vs. vector

//#include <algorithm>
//#include <iostream>
//#include <valarray>
//#include <vector>
//#include <ctime>
//#include <iomanip>
//using namespace std;
//
//void rndm(float& a);
//void zerocheck(float& a);
//double duration(vector<clock_t>::iterator start, vector<clock_t>::iterator stop);
//
//int main()
//{
//  int i(0);
//  int p(0);
//  float k(5.3235),l(9.212);
//  int size(4000000);
//
//  vector<clock_t> vstart;
//  vector<clock_t> vstop;
//  vector<clock_t>::iterator istartclock;
//  vector<clock_t>::iterator istopclock;
//  vector<float> vfloat(size);
//  vector<float>::iterator ifloat;
//  valarray<float> valfloat(size);
//
//  cout << "Filling float array with " << size << " random elements" << endl;
//  cout << "(each element needs " << sizeof(float) << " bytes of memory, so " \
//       << "we need to make use of " << size*sizeof(float)/1000000<< "MBytes.)"<< endl;
//
//  // ======================= ORDINARY OPERATIONS =======================
//  // fill array
//
//  vstart.push_back(clock());
//  //  vfloat.resize(size);
//  ifloat=vfloat.begin();
//  for_each(vfloat.begin(),vfloat.end(),rndm);
//  vstop.push_back(clock());
//
//  cout << "****** Phase 1: Math. operations on ordinary array" << endl;  
//
//  // Add k to each element
//  cout << "*** Adding " << k << " to each element " ;
//  cout << "(10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)+=k; }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")" << endl;
//
//
//  // Multiply each element with k
//  cout << "*** Multiplying each element with " << k ;
//  cout << " (10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)*=k; }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")"<< endl;
//
//  // Divide each element by k
//  cout << "*** Dividing each element by " << l ;
//  cout << " (10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)/=l; }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")" << endl;
//
//  // Cos of each
//  cout << "*** Calculate cos for each element "  ;
//  cout << " (10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)= cosf(*(ifloat+i)); }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")" << endl;
//
//  for_each(vfloat.begin(),vfloat.end(),zerocheck);
//
//  // Expand each element by itself
//  cout << "*** Calculate element ^ element "  ;
//  cout << " (10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)= pow(*(ifloat+i),*(ifloat+i)); }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")" << endl;
//
//  // log
//  cout << "*** Calculate log of each element "  ;
//  cout << " (10th element was: " << *(ifloat+10) ;
//  vstart.push_back(clock());
//  for (i=0; i<vfloat.size(); i++) { *(ifloat+i)= log(*(ifloat+i)); }
//  vstop.push_back(clock());
//  cout << " now is: " << *(ifloat+10) << ")" << endl;
//
//
//  // Summary
//  istartclock=vstart.begin(); istopclock=vstop.begin();
//  cout << "****** Clock ticks for operations: " << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (random fill)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (add.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (mult.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (div.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (cos)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++) << " (pow)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock,istopclock) << " (log)" << endl;
//  cout << right << fixed << setw(13) << *(vstop.rbegin())-*(vstart.begin()) << " (total) " << endl;
//
//
//  p=vstart.size();
//  // ======================= VALARRAY OPERATIONS =======================
//  // fill valarray
//
//  cout << "****** Phase 2: Math. operations on valarray" << endl;  
//  vstart.push_back(clock());
//  for (i=0;i<size;i++)
//    {
//      rndm(valfloat[i]);
//    }
//  vstop.push_back(clock());
//
//
//  // Add k to each element
//  cout << "*** Adding " << k << " to each element " ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat+=k;
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//  // Multiply
//  cout << "*** Multiplying each element with " << k ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat*=k;
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//  // Divide
//  cout << "*** Dividing each element by " << l ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat/=l;
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//  // Cosinus
//  cout << "*** Calculate cos for each element "  ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat=cos(valfloat);
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//
//  for (i=0;i<size;i++)
//    {
//      zerocheck(valfloat[i]);
//    }
//
//  // Expand each element by itself
//  cout << "*** Calculate element ^ element "  ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat=pow(valfloat,valfloat);
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//  // log
//  cout << "*** Calculate log of each element "  ;
//  cout << "(10th element was: " << valfloat[10] ;
//  vstart.push_back(clock());
//  valfloat=log(valfloat);
//  vstop.push_back(clock());
//  cout << " now is: " << valfloat[10] << ")" << endl;
//
//  // Summary
//
//  cout << "****** Clock ticks for operations: " << endl;
//  istartclock=vstart.begin(); istopclock=vstop.begin();
//  
//  istartclock+=p; istopclock+=p;
//  
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (random fill)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (add.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (mult.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (div.)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (cos)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock++,istopclock++)  << " (pow)" << endl;
//  cout << right << fixed << setw(13) << duration(istartclock,istopclock)      << " (log)" << endl;
//  cout << right << fixed << setw(13) << *(vstop.rbegin())-*(vstart.begin()+p) << " (total) " << endl;
//
//
//  system("pause");
//
//}
//
//void rndm(float& a)
//{
//  a=rand()%1000000;
//  a/=(1000);
//}
//
//void zerocheck(float& a)
//{
//  if (a<0) { a*=-1; } 
//}
//
//double duration(
//	      vector<clock_t>::iterator start, 
//	      vector<clock_t>::iterator stop
//	      )
//{
//  return difftime(*stop,*start) ;
//}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// compare the subscript operator's performance of vector and deque
//#include<iostream>
//#include<iomanip>
//#include<deque>
//#include<vector>
//#include<algorithm>
//#include<ctime>
//#include<cstdlib>
//using namespace std;
//
//const int containersize = 100000;
//const int looptimes = 10000000;
//int init[containersize];
//
//struct randgen{
//    randgen(){srand((unsigned)time(NULL));}
//    int operator()(){
//        return (int)(double(rand())/RAND_MAX * (containersize - 1));
//    }
//};
//
//int main(){
//    vector<int> v;
//    deque<int> d;
//    randgen r;
//    generate(init, init + sizeof(init)/sizeof(init[0]), r);
//    v.assign(init, init + sizeof(init)/sizeof(init[0]));
//    d.assign(init, init + sizeof(init)/sizeof(init[0]));
//
//    clock_t start, finish;
//    volatile
//    int tmpval = 0;
//
//    cout<<left<<setw(18)<<"loop for vector:";
//    start = clock();
//    for(int i=0; i<looptimes; ++i)
//        tmpval = v[tmpval];
//    finish = clock();
//    cout<<setw(8)<< finish - start <<" clocks\n";
//
//    tmpval = 0;
//    cout<<left<<setw(18)<<"loop for deque:";
//    start = clock();
//    for(int i=0; i<looptimes; ++i)
//        tmpval = d[tmpval];
//    finish = clock();
//    cout<<setw(8)<< finish - start <<" clocks\n";
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<string>
//using namespace std;
//
//int main(){
//    string s("abcde");
//    cout<< (s < "123") <<endl;
//    cout<< ("www" > s) <<endl;
//    s.insert(0, 3, 'a');
//    cout<<s<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<string>
//using namespace std;
//
//int main(){
//    string ostr("Hello Everyone");
//    string::size_type idx1, idx2;
//    idx1 = ostr.rfind('e', 8);
//    cout<<idx1<<endl;
//
//    idx2 = ostr.rfind("Eve of Christmas", 6, 3);
//    cout<<idx2<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//using namespace std;
//int main(){
//    unsigned a = 20;
//    int b = -130;
//    cout<< (a<b)<<endl;
//    cout<< (b>a)<<endl;
//    cout<< (a+b)<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<string>
//using namespace std;
//int main(){
//    char buf[100] = {0};
//    string str("abcde");
//    cout<<str.copy(buf, 100, 3)<<"chars copied\n";
//    cout<<"buf: "<<buf<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<complex>
//using namespace std;
//int main(){
//    complex<double> z(1.234, 0);
//    cout<<z<<endl;
//    cout<<pow(complex<double>(-1), 0.33333333333)<<endl;
//    cout<<(cin.operator void *())<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// gcount of wchar_ts

//#include<iostream>
//#include<fstream>
//#include<locale>
//using namespace std;
//int main(){
//    wifstream wfin("input.txt");
//    wfin.imbue(locale(""));
//    wcout.imbue(locale(""));
//
//    wchar_t buf[10];
//    wfin.getline(buf, 10);
//    wcout<<buf<<L'\n'<<wfin.gcount()<<endl;
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// wistringstream can convert char stream to wchar_ts ?
// 无法用 char* 构造 wistringstream。猜测 stringstream 处于 codecvt_facet 转换之后的位置，无法调用下层编码转换函数。
// 但为何还可以设定 imbue() ，设完有何用处，还有待研究。

//#include<iostream>
//#include<sstream>
//#include<locale>
//#include<iomanip>
//using namespace std;
//int main(){
//    wchar_t buf[10];
//    wistringstream wis("123汉字456\n", ios::in);
//    wis.imbue(locale(""));
//
//    wis.getline(buf, 10);
//    wcout.imbue(locale(""));
//    wcout<<buf<<endl;
//    cout<<setw(5)<<"123"<<endl;
//    ios_base::fmtflags flags;
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// 试验 width() 对 istream 的作用

//#include<iostream>
//#include<iomanip>
//using namespace std;
//const int bufsize = 5;
//
//int main(){
//    char buffer[bufsize];
//    cin.width(bufsize);
//    while(cin>>buffer){
//        cout<<buffer<<endl;
//        cout<<left<<"123"<<endl;
//        cout<<setiosflags(ios_base::showpos);
//        cin.width(bufsize);
//    }
//    //system("pause");
//}


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
// test the format of float numbers
//#include<iostream>
//#include<iomanip>
//using namespace std;
//
//void printd(double num, int prcsn){
//    cout<<endl;
//    cout.precision(prcsn);
//    cout.unsetf(ios::floatfield);
//    cout<<setw(30)<<"normal with noshowpoint:"<<noshowpoint<<setw(40)<<num<<'\n';
//    cout<<setw(30)<<"normal with showpoint:"<<showpoint<<setw(40)<<num<<'\n';
//
//    cout.setf(ios::fixed, ios::floatfield);
//    cout<<setw(30)<<"fixed with noshowpoint:"<<noshowpoint<<setw(40)<<num<<'\n';
//    cout<<setw(30)<<"fixed with showpoint:"<<showpoint<<setw(40)<<num<<'\n';
//    
//    cout.setf(ios::scientific, ios::floatfield);
//    cout<<setw(30)<<"scientific with noshowpoint:"<<noshowpoint<<setw(40)<<num<<'\n';
//    cout<<setw(30)<<"scientific with showpoint:"<<showpoint<<setw(40)<<num<<'\n';
//}
//
//int main(){
//    printd(4210.0, 2);
//    printd(4210.0, 9);
//    printd(0.00123456789, 3);
//    printd(0.00123456789, 12);
//    printd(5432e-20, 3);
//    printd(5e-20,3);
//
//    system("pause");
//}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// test seekg and seekp of fstream
// 看来 seekg 是按字节来算位置的，与 locale 无关。
// read 读取 1 字符后，位置变了 2 。
//#include<iostream>
//#include<fstream>
//#include<locale>
//#include<cstdlib>
//using namespace std;
//int main(){
//    wifstream wif("input.txt");
//    wchar_t wch;
//    if(!wif)return EXIT_FAILURE;
//    wif.imbue(locale(""));
//    wif.seekg(1, ios::beg);
//    wif.read(&wch, 1);
//    if(wif.fail())
//        cout<<"fail"<<endl;
//    cout<<wif.tellg()<<endl;
//    wcout.imbue(locale(""));
//    wcout<<wch<<endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
// c and c++ file io performance comparision
//#include<ctime>
//#include<cstdio>
//#include<iostream>
//#include<fstream>
//using namespace std;
//int main( int argc, const char* argv[] ){
//    ios::sync_with_stdio(false);
//    const int max = 1000000;
//    const char* teststr = "example";
//
//    clock_t start = clock();
//    FILE* file = fopen( "example1", "w" );
//    for( int i = 0; i < max; i++ ){
//        fprintf( file, "%s:%d\n", teststr, i );
//    }
//    fclose( file );
//    clock_t end = clock();
//    printf( "C FILE: %d clocks\n", end-start );
//
//    start = clock();
//    ofstream outdata;
//    outdata.open("example2.dat");
//    for( int i = 0; i < max; i++ ){
//        outdata << teststr << ":" << i << '\n';
//    }
//    outdata.close();
//    end = clock();
//    printf( "C++ Streams: %d clocks\n", end-start );
//    system("pause");
//    return 0;
//}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// use of rdbuf()
//#include<iostream>
//using namespace std;
//int main(){
//    ostream hexout(cout.rdbuf());
//    hexout.setf(ios::hex, ios::basefield);
//    hexout.setf(ios::showbase);
//
//    hexout<<"hexout: "<<177<<"\n";
//    cout  <<"cout  : "<<177<<"\n";
//    hexout<<"hexout: "<<-49<<"\n";
//    cout  <<"cout  : "<<-49<<"\n";
//    hexout<<endl;
//
//    system("pause");
//}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// get whole file in a string ?
//#include<fstream>
//#include<iostream>
//#include<string>
//#include<sstream>
//#include<iterator>
//#include<vector>
//using namespace std;
//
//int main(){
//    ifstream fin("input.txt");
//
//    //string str;
//    //getline(fin, str, (int)EOF);  // EOF can't stop the getline function...it's not a valid char
//    //str.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());  // !!
//    //cout<<str;
//
//    stringstream ss;
//    //ss.rdbuf(fin.rdbuf());  // can't convert a filebuf to a stringbuf
//
//    //fin.seekg(0, ios::end);
//    //streampos size = fin.tellg();
//    //fin.seekg(0, ios::beg);
//    //vector<char> buffer(size);
//    //fin.read(&buffer[0], size);
//
//    //vector<char> buffer((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
//
//    ss<<fin.rdbuf();
//    //ss.rdbuf()->pubsetbuf(&buffer[0], buffer.size());  // no use
//    // in VC2008, pubsetbuf() is a non-op function.
//    cout<<ss.rdbuf();
//
//    system("pause");
//}

///////////////////////////////////////////////////////////////
// for each .................
//#include<stdio.h>
//#include<stdlib.h>
//int main(){
//    int a[10];
//    for(int i=0; i<10; ++i)
//        a[i] = i;
//
//    for each(int c in a){    // ...................
//        printf("%d ", c);
//    }
//    system("pause");
//}

//////////////////////////////////////////////////////////////////
//#include<iostream>
//using namespace std;
//union {
//    int x;
//    struct {
//        char c1, c2;
//    }b;
//}a;
//int main(){
//    a.x = 0x1234;
//    cout.setf(ios::hex, ios::basefield);
//    cout<<(int)a.b.c1<<endl;
//    //cout<<a.b.c1<<endl;
//    cout<<(int)a.b.c2<<endl;
//    system("pause");
//}

/////////////////////////////////////////////////////////////////
// no use ...
//#include<iostream>
//#include<algorithm>
//#include<iterator>
//#include<string>
//int main(){
//    using namespace std;
//    string buffer;
//    getline(cin, buffer);
//    reverse_copy(buffer.begin(), buffer.end(),
//        ostreambuf_iterator<char>(cout));
//    cout<<endl;
//    system("pause");
//}

//#include<iostream>
//#include<iomanip>
//using namespace std;
//
//void printTriangle(ostream &os, const char ch, int n){
//    os<<setw(n)<<ch<<'\n';
//    int line = n;
//    while(--line > 1)
//        os<<setw(line)<<ch<<setw(2*(n-line))<<ch<<'\n';
//    char oldch = os.fill(ch);
//    os<<setw(2*n-1)<<ch<<'\n';
//    os.fill(oldch);
//}
//
//int main(){
//    char ch;
//    int n;
//    while((cin>>ch) && ch != '@'){
//        cin>>n;
//        printTriangle(cout, ch, n);
//    }
//    system("pause");
//}

////////////////////////////////////////////////////////////////
// test link to msvcrt.lib with some stl components
// result: can't use iostream & vector ...
// but can use operator new and algorithms
// all C functions are available
// next try static link to STLport with dynamic link to msvcrt.lib ... (how?)
// or try to write some my own STL components...
// when static link, VC STL exesize is smaller than STLport exesize

// temp conclusion:
// do not use STL containers ...
// dynamic link to msvcrt6.lib (disable c++ exceptions and buffer security check)
//     do not use operator new[] or delete[]
//     use malloc() and free() instead
// OR
//     override operator new[] and operator delete[]
//     use heap APIs in override functions: HeapAlloc HeapFree
// can use auto_ptr in <memory>
// this makes smaller exe size

// in stlport/stl/config/host.h:
// define _STLP_USE_ALLOC and rebuild stlport lib
// then use std containers may not involve stlport.dll

//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<cstdlib>
//#include<memory>
//using namespace std;
//
//struct genet{
//    int num;
//    genet(int n):num(n){}
//    int operator()(){
//        return num++;
//    }
//};
//int main(){
//    //int* pi = new int(5);
//    auto_ptr<int> pi(new int(5));
//
//    vector<int> vi(10);
//    //vi.reserve(10);
//    //generate_n(back_inserter(vi), 10, genet(100));
//    //rotate(vi.begin(), vi.begin()+3, vi.end());
//    //printf("test %d!\n", vi[*pi]);
//    //for(int i=0; i<(int)vi.size(); ++i)
//    //    printf("%d ", vi[i]);
//
//    //int *vi = new int[10];
//    generate_n(vi.begin(), 10, genet(200));
//    rotate(vi.begin(), vi.begin()+3, vi.end());
//    printf("test %d!\n", vi[*pi]);
//    for(int i=0; i<10; ++i)
//        printf("%d ", vi[i]);
//
//    printf("\n");
//    //std::cout<<"another test!\n";
//
//    //delete []vi;
//    //delete pi;
//
//    system("pause");
//}


//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// test the performance of C I/O & C++ streams & C++ codecvt facet
//#include<cstdio>
//#include<iostream>
//#include<fstream>
//#include<vector>
//#include<locale>
//#include<cstdlib>
//#include<ctime>
//#include<windows.h>
//#include<boost/filesystem/fstream.hpp>
//using namespace std;
//namespace fs = boost::filesystem;
//
//const int testsize = 50000;
//
//int main(){
//    char cstr[] = "这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串";
//    wchar_t wstr[] = L"这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串这是实验字符串";
//    char buffer[200];
//    int cstrlen = strlen(cstr);
//    locale defloc("");
//
//    clock_t start;
//    FILE *cfile;
//    ofstream fout;
//    wofstream wfout;
//    fs::wofstream bwfout;
//
//    // pure text ...........................
//    start = clock();
//    cfile = fopen("text_out_C_fwrite.txt", "w");
//    for(int i = 0; i < testsize; ++i){
//        fwrite(cstr, sizeof(char), cstrlen, cfile);
//        fputc('\n', cfile);
//    }
//    fclose(cfile);
//    printf("Text out C fwrite: %d\n", clock()-start);
//
//    //start = clock();
//    //cfile = fopen("text_out_C_fputs.txt", "w");
//    //for(int i = 0; i < testsize; ++i){
//    //    fputs(cstr, cfile);
//    //    fputc('\n', cfile);
//    //}
//    //fclose(cfile);
//    //printf("Text out C fputs: %d\n", clock()-start);
//
//    //start = clock();
//    //cfile = fopen("test_out_C_fprintf.txt", "w");
//    //for(int i = 0; i < testsize; ++i){
//    //    fprintf(cfile, "%s\n", cstr);
//    //}
//    //fclose(cfile);
//    //printf("Text out C fprintf: %d\n", clock()-start);
//
//    fout.clear();
//    start = clock();
//    fout.open("text_out_Cpp_ofstream.txt");
//    for(int i = 0; i < testsize; ++i){
//        fout << cstr << '\n';
//    }
//    fout.close();
//    printf("Text out Cpp ofstream: %d\n", clock()-start);
//
//    fout.clear();
//    start = clock();
//    vector<char> vbuffer((cstrlen+1)*testsize);
//    char* pb = &vbuffer[0];
//    for(int i = 0; i < testsize; ++i){
//        memcpy(pb, cstr, cstrlen);
//        pb += cstrlen;
//        *pb++ = '\n';
//    }
//    fout.open("text_out_Cpp_buf_ofstream.txt");
//    fout.write(&vbuffer[0], vbuffer.size());
//    vbuffer.clear();
//    fout.close();
//    printf("Text out Cpp buf ofstream: %d\n", clock()-start);
//
//    fout.clear();
//    start = clock();
//    fout.open("text_out_Cpp_rdbuf.txt");
//    for(int i = 0; i < testsize; ++i){
//        fout.rdbuf()->sputn(cstr, cstrlen);
//        fout.rdbuf()->sputc('\n');
//    }
//    fout.close();
//    printf("Text out Cpp rdbuf: %d\n", clock()-start);
//
//    // wchar_t text ...............................
//    //wfout.clear();
//    //start = clock();
//    //wfout.open("wtext_out_Cpp_wofs_defloc.txt");
//    //wfout.imbue(defloc);
//    //for(int i = 0; i < testsize; ++i){
//    //    wfout << wstr << L'\n';
//    //}
//    //wfout.close();
//    //printf("wText out Cpp wofs with default locale: %d\n", clock()-start);
//
//    //// the performance of fs::fstream is identical to std fstreams.
//    ////bwfout.clear();
//    ////start = clock();
//    ////bwfout.open("wtext_out_CPP_boost_wofs_defloc.txt");
//    ////bwfout.imbue(defloc);
//    ////for(int i = 0; i < testsize; ++i){
//    ////    bwfout << wstr << L'\n';
//    ////}
//    ////bwfout.close();
//    ////printf("wText out Cpp boost wofs with default locale: %d\n", clock()-start);
//
//    //fout.clear();
//    //start = clock();
//    //char *next;
//    //const wchar_t *wnext;
//    //mbstate_t st;
//    //fout.open("wtext_out_Cpp_codecvt_facet.txt");
//    //for(int i = 0; i < testsize; ++i){
//    //    use_facet<codecvt<wchar_t, char, mbstate_t> >(defloc).out(
//    //        st, wstr, wstr+sizeof(wstr)/2-1, wnext, buffer, buffer+sizeof(buffer)-1, next);
//    //    fout.rdbuf()->sputn(buffer, next-buffer);
//    //    fout.rdbuf()->sputc('\n');
//    //}
//    //fout.close();
//    //printf("wText out Cpp ofs with codecvt facet: %d\n", clock()-start);
//
//    //fout.clear();
//    //start = clock();
//    //fout.open("wtext_out_Cpp_ofs_WinAPI.txt");
//    //for(int i = 0; i < testsize; ++i){
//    //    WideCharToMultiByte(CP_ACP, 0, wstr, -1, buffer, 200, NULL, NULL);
//    //    fout << buffer << '\n';
//    //}
//    //fout.close();
//    //printf("wText out Cpp ofs with WideCharToMultiByte API: %d\n", clock()-start);
//
//    // Format out ...........................................
//    //srand((unsigned)time(NULL));
//
//    //char datastr[] = "TestDataString实验格式化字符串";
//    //start = clock();
//    //cfile = fopen("format_data_out_C_fprintf.txt", "w");
//    //for(int i = 0; i < testsize; ++i){
//    //    fprintf(cfile, "%d %lf %s\n", rand(), double(rand())/RAND_MAX, datastr);
//    //}
//    //fclose(cfile);
//    //printf("Format data out C fprintf: %d\n", clock()-start);
//
//    //fout.clear();
//    //start = clock();
//    //fout.open("format_data_out_Cpp_ofstream.txt");
//    //for(int i = 0; i < testsize; ++i){
//    //    fout << rand() << ' ' << double(rand())/RAND_MAX << ' '
//    //        << datastr << '\n';
//    //}
//    //fout.close();
//    //printf("Format data out Cpp ofstream: %d\n", clock()-start);
//
//    //fout.clear();
//    //start = clock();
//    //fout.open("format_data_out_Cpp_ofs_facet.txt");
//    //for(int i = 0; i < testsize; ++i){
//    //    use_facet<num_put<char> >(locale::classic()).put(
//    //        ostreambuf_iterator<char>(fout), fout, ' ', (long)rand());
//    //    fout.rdbuf()->sputc(' ');
//    //    use_facet<num_put<char> >(locale::classic()).put(
//    //        ostreambuf_iterator<char>(fout), fout, ' ', double(rand())/RAND_MAX);
//    //    fout.rdbuf()->sputc(' ');
//    //    fout.rdbuf()->sputn(datastr, sizeof(datastr) - 1);
//    //    fout.rdbuf()->sputc('\n');
//    //}
//    //fout.close();
//    //printf("Format data out Cpp ofs with facet: %d\n", clock()-start);
//
//    system("pause");
//}

////////////////////////////////////////////////////////////
// boost header test
//#include<boost/lambda/lambda.hpp>
//#include<iostream>
//#include<iterator>
//#include<algorithm>
//int main(){
//    using namespace boost::lambda;
//    typedef std::istream_iterator<int> in;
//    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
//}

// boost lib test
//#include<boost/filesystem.hpp>
//#include<iostream>
//#include<locale>
//namespace bf = boost::filesystem;
//int main(){
//    bf::wpath p(L"E:/Temp/试验.txt");
//    std::wcout.imbue(std::locale(std::locale::classic(), "", std::locale::ctype));
//    if(bf::exists(p))
//        std::wcout << p.filename() << std::endl;
//    else 
//        std::wcout << p.file_string() << L"do not exist..." << std::endl;
//    system("pause");
//    return 0;
//}

///////////////////////////////////////////////////////
//#include<iostream>
//#include<sstream>
//#include<fstream>
//#include<iterator>
//#include<functional>
//#include<algorithm>
//using namespace std;
//class divider{
//    ostreambuf_iterator<char> osb;
//    bool lastws;
//public:
//    divider(ostream &os):osb(ostreambuf_iterator<char>(os)), lastws(false){}
//    void operator()(char ch){
//        if(ch < '0' || ch > '9'){
//            if(!lastws){
//                *osb++ = ' ';
//                lastws = true;
//            }
//        } else {
//            *osb++ = ch;
//            lastws = false;
//        }
//    }
//};
//int main(){
//    ifstream fin("i.txt");
//    stringstream ss;
//    for_each(istreambuf_iterator<char>(fin), istreambuf_iterator<char>(), divider(ss));
//    transform(istream_iterator<int>(ss), istream_iterator<int>(),
//        ostream_iterator<int>(cout, " "), bind2nd(multiplies<int>(), 3));
//    cout << endl;
//    system("pause");
//}

/////////////////////////////////////////////////////////
// file copy performance
// it seems that fout << fin.rdbuf(); is not that efficient
// when manually allocate a larger buffer, the speed can be much faster...

//#include<fstream>
//int main(){
//    char data[] = "Test Data Text...Test Data Text...Test Data Text...";
//    std::ofstream fout("Data.txt");
//    for(int i=0; i<200000; ++i){
//        fout.rdbuf()->sputn(data, sizeof(data) - 1);
//        fout.rdbuf()->sputc('\n');
//    }
//    fout.close();
//}
// -----------------------------------------------
//#include <fstream> 
//#include <vector>
//#include <iostream> 
//#include <ctime>
//
//int main(int argc, char* argv[]) 
//{
//    std::ofstream ofile; 
//    std::ifstream ifile; 
//    const int BuSize=1024*1024*2; 
//    std::clock_t t1 = 0, t2 = 0; 
//    t1 = ::clock();
//
//    std::vector<char> Buffer(BuSize);
//    ifile.open("Data.txt", std::ios::binary); 
//    ofile.open("Data2.txt", std::ios::binary); 
//
//    while(!ifile.eof()) 
//    {
//        ifile.read(&Buffer[0],BuSize); 
//        ofile.write(&Buffer[0],ifile.gcount()); 
//    } 
//    ifile.close(); 
//    ofile.close(); 
//    t2 = ::clock();
//    std::cout << t2-t1 << std::endl; 
//    system("pause");
//    return 0; 
//} 
// ----------------------------------------------------
//#include <fstream> 
//#include <ctime>
//#include <vector>
//#include <iostream> 
//
//int main(int argc, char* argv[]) 
//{
//    std::ofstream ofile; 
//    std::ifstream ifile; 
//    clock_t t1, t2; 
//    const int bsize = 1024*1024*2;
//    t1 = clock();
//
//    ifile.open("Data.txt",std::ios::binary); 
//    ofile.open("Data2.txt",std::ios::binary); 
//
//    ofile << ifile.rdbuf();
//    ifile.close(); 
//    ofile.close(); 
//    t2 = clock();
//    std::cout << t2-t1 << std::endl; 
//    system("pause");
//    return 0; 
//} 
// ----------------------------------------
//#include <stdio.h> 
//#include <time.h>
//#include <stdlib.h>
//
//int main(int argc, char* argv[]) 
//{ 
//    FILE *fhr=NULL,*fhw=NULL; 
//    int BuSize=1024*1024*2,DataSize=0; 
//    clock_t t1, t2;
//    t1 = clock();

//    char* Buffer=new char[BuSize]; 
//
//    fhr=fopen("Data.txt","rb"); 
//    fhw=fopen("Data1.txt","wb"); 
//
//    while(!feof(fhr)) 
//    { 
//        DataSize=fread(Buffer,sizeof(char),BuSize,fhr); 
//        fwrite(Buffer,sizeof(char),DataSize,fhw); 
//    } 
//    fclose(fhr); 
//    fclose(fhw); 
//    t2 = clock();
//    printf("%d\n", t2-t1);
//    system("pause");
//    return 0; 
//} 

//////////////////////////////////////////////////////////////
// rand3() make rand5()
//#include<iostream>
//#include<map>
//#include<functional>
//#include<iomanip>
//#include<algorithm>
//using namespace std;
//int init[3] = {1, 2, 3};
//int a[3][3];
//int main(){
//    int m1, m2, m3;
//    map<int, int> count;
//
//    while(cin >> m1 >> m2 >> m3){
//        transform(init, init+3, a[0], bind2nd(multiplies<int>(), m1));
//        transform(init, init+3, a[1], bind2nd(multiplies<int>(), m2));
//        transform(init, init+3, a[2], bind2nd(multiplies<int>(), m3));
//        count.clear();
//
//        for(int i=0; i<3; ++i)
//            for(int j=0; j<3; ++j)
//                for(int k=0; k<3; ++k)
//                    ++count[a[0][i]+a[1][j]+a[2][k]];
//
//        for(map<int,int>::iterator it=count.begin(); it!=count.end(); ++it)
//            cout<<setw(3)<<it->first;
//        cout<<'\n';
//        for(map<int,int>::iterator it=count.begin(); it!=count.end(); ++it)
//            cout<<setw(3)<<it->second;
//        cout<<endl;
//    }
//
//    system("pause");
//}

//#include<iostream>
//#include<ctime>
//#include<cstdlib>
//using namespace std;
//inline int rand3(){
//    int r;
//    while((r=rand()) >= 32766);
//    return r%3 + 1;
//
//    //return rand()%3+1;
//}
//#define MY
//#ifdef MY
//int rand5(){
//    int r;
//    while((r=2*rand3() - 2*rand3() + rand3()) >= 6);
//    switch(r){
//        case -3:
//        case -2:
//        case -1: return 1; break;
//        case  1: return 2; break;
//        case  3: return 3; break;
//        case  0:
//        case  2: return 4; break;
//        case  4:
//        case  5: return 5; break;
//    }
//    return 0; // cannot get here...
//}
//#else
//int rand5_count[5] = {0};
//int rand5(){
//    for(;;){
//        int rnd = rand3() + rand3() - 2;
//        rand5_count[rnd] += (rnd - 4) * rnd + 6;
//        if(rand5_count[rnd] > 5){
//            rand5_count[rnd] -= 6;
//            return rnd+1;
//        }
//    }
//}
//#endif
//const int testcnt = 1000000;
//int main(){
//    int a[6] = {0};
//    srand((unsigned)time(NULL));
//    for(int i=0; i<testcnt; ++i)
//        ++a[rand3()];
//    for(int i=1; i<4; ++i)
//        cout << a[i] << ' ';
//    cout << endl;
//    a[1]=a[2]=a[3]=0;
//
//    clock_t t1 = clock();
//    for(int i=0; i<testcnt; ++i)
//        ++a[rand5()];
//    for(int i=1; i<6; ++i)
//        cout << a[i] << ' ';
//    cout << '\n' << clock()-t1 << endl;
//    system("pause");
//}

//////////////////////////////////////////////////////////////////
// test for argument
// 引号中的参数会自动识别并去掉引号传进来，这样可以使用有空格的参数。
//#include<iostream>
//#include<locale>
//#include<boost/filesystem.hpp>
//int wmain(int argc, wchar_t* argv[]){
//    using namespace std;
//    wcout.imbue(locale(""));
//    if(argc != 2){
//        wcout << L"Usage: " << argv[0] << L" path" << endl;
//        return 0;
//    }
//    namespace fs = boost::filesystem;
//    fs::wpath path(argv[1]);
//    if(!fs::exists(path)){
//        wcout << path.file_string() << L" not exist ..." << endl;
//    } else if(fs::is_directory(path)){
//        fs::wdirectory_iterator enditr;
//        for(fs::wdirectory_iterator it(path); it!=enditr; ++it){
//            wcout << it->path().file_string() << endl;
//        }
//    } else {
//        if(fs::is_symlink(path))
//            wcout << L"Symlink:\n";
//        wcout << L"File size: " << fs::file_size(path) << endl;
//    }
//    //system("pause");
//}

////////////////////////////////////////////////////////////////
// boost wchar_t path and boost fstream
//#include<iostream>
//#include<fstream>
//#include<string>
//#include<locale>
////#include<boost/filesystem.hpp>
//#include<boost/filesystem/fstream.hpp>
//int main(){
//    using namespace std;
//    locale loc(locale::classic(), "", locale::ctype);
//    //wifstream ifile(boost::filesystem::wpath(L"中文.txt"));
//    boost::filesystem::wifstream ifile(L"中文.txt");
//    ifile.imbue(loc);
//    wcout.imbue(loc);
//    wcin.imbue(loc);
//    if(ifile.fail()){
//        wcout << L"Can't open file " << L"中文.txt" << endl;
//        return 0;
//    }
//    wstring line;
//    while(getline(ifile, line)){
//        wcout << line << '\n';
//    }
//    wcout << endl;
//
//    system("pause");
//}

///////////////////////////////////////////////////////////////////
// 最大公共子串算法 动态规划
//#include<cstdio>
//#include<iostream>
//#include<vector>
//#include<string>
//using namespace std;
//
//vector<char> str1, str2;
//vector<vector<int> > lenmatrix;
//
//int maxstr(char* str1, int len1, char* str2, int len2, char* &combeg1, char* &combeg2){
//    int maxlen = 0, i, j;
//    if(len1 == 0 || len2 == 0)return 0;
//    // init lenmatrix
//    lenmatrix.resize(len1+1);
//    lenmatrix[0].assign(len2+1, 0);
//    for(i = 1; i <= len1; ++i){
//        lenmatrix[i].resize(len2+1);
//        lenmatrix[i][0] = 0;
//    }
//    // dp
//    for(i = 1; i <= len1; ++i)
//        for(j = 1; j <= len2; ++j){
//            if(str1[i-1] == str2[j-1]){
//                if((lenmatrix[i][j] = lenmatrix[i-1][j-1] + 1) > maxlen){
//                    maxlen = lenmatrix[i][j];
//                    combeg1 = str1 + i - maxlen;
//                    combeg2 = str2 + j - maxlen;
//                }
//            } else
//                lenmatrix[i][j] = 0;
//        }
//    return maxlen;
//}
//
//void diffout(char* str1, int len1, char* str2, int len2){
//    char *beg1, *beg2;
//    int maxlen = maxstr(str1, len1, str2, len2, beg1, beg2);
//    if(maxlen == 0){
//        if(len1 <= 1)
//            cout << str1 - &::str1[0] + 1 << ":\t";
//        else
//            cout << str1 - &::str1[0] + 1 << "-"
//                << str1 - &::str1[0] + len1 << ":\t";
//        cout.write(str1, len1);
//        cout << ", ";
//        cout.write(str2, len2);
//        cout.put('\n');
//    } else {
//        int newlen1 = beg1 - str1, newlen2 = beg2 - str2;
//        if(newlen1 > 0 || newlen2 > 0)
//            diffout(str1, newlen1, str2, newlen2);
//        beg1 += maxlen;
//        beg2 += maxlen;
//        newlen1 = len1 - (beg1 - str1);
//        newlen2 = len2 - (beg2 - str2);
//        if(newlen1 > 0 || newlen2 > 0)
//            diffout(beg1, newlen1, beg2, newlen2);
//    }
//}
//
//int main(){
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//    string tempstr;
//    getline(cin, tempstr);
//    str1.assign(tempstr.begin(), tempstr.end());
//    getline(cin, tempstr);
//    str2.assign(tempstr.begin(), tempstr.end());
//
//    diffout(&str1[0], str1.size(), &str2[0], str2.size());
//    return 0;
//}

// 别人写的程序。效率更高
//#include <iostream>
//#include <cstdio>
//using namespace std;
//
//const int MAXN = 10000; //字符串最大长度
//char a[MAXN], b[MAXN], c[MAXN];
//int dp[MAXN][MAXN], lena, lenb, lenc;
//
//int main()
//{
//    scanf("%s%s", a, b);
//    lena = strlen(a), lenb = strlen(b);
//    for (int i=lena-1; i>=0; i--)
//        for (int j=lenb-1; j>=0; j--)
//            if (a[i] != b[j]) dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
//            else dp[i][j] = dp[i+1][j+1]+1;
//    printf("最大公共子串长度：%d\n匹配串：", dp[0][0]);
//    int i=0, j=0, k, x, t1, t2, t3;
//    while (i<lena && j<lenb)
//    {
//        if (a[i] == b[j]) c[lenc++] = a[i], i++, j++;
//        else if (dp[i][j] == dp[i+1][j]) i++;
//        else j++;
//    }
//    c[lenc++] = 0;
//    printf("%s\n\n对齐之后的字符串:\n", c);
//    for (i=j=k=x=0; k<lenc; i++,j++,k++,x++)
//    {
//        if (a[i]==c[k] && b[j]==c[k]) { putchar(a[i]); continue; }
//        t1 = t2 = 0;
//        while (a[i] != c[k]) i++, t1++;
//        while (b[j] != c[k]) j++, t2++;
//        t3 = max(t1, t2);
//        for (t2=i-t1; t2<i; t2++) putchar(a[t2]);
//        for (t2=i; t2<i-t1+t3; t2++) putchar(' ');
//        x += t3;
//        putchar(a[i]);
//    }
//    putchar('\n');
//    for (i=j=k=x=0; k<lenc; i++,j++,k++,x++)
//    {
//        if (a[i]==c[k] && b[j]==c[k]) { putchar(b[j]); continue; }
//        t1 = t2 = 0;
//        while (a[i] != c[k]) i++, t1++;
//        while (b[j] != c[k]) j++, t2++;
//        t3 = max(t1, t2);
//        for (t1=j-t2; t1<j; t1++) putchar(b[t1]);
//        for (t1=j; t1<j-t2+t3; t1++) putchar(' ');
//        x += t3;
//        putchar(b[j]);
//    }
//    putchar('\n');putchar('\n');
//    for (i=j=k=x=0; k<lenc; i++,j++,k++,x++)
//    {
//        if (a[i]==c[k] && b[j]==c[k]) continue;
//        t1 = t2 = 0;
//        while (a[i] != c[k]) i++, t1++;
//        while (b[j] != c[k]) j++, t2++;
//        t3 = max(t1, t2);
//        if (t3 == 1) printf("%d\t'", x+1);
//        else printf("%d-%d\t'", x+1, x+1+t3);
//        for (t3=i-t1; t3<i; t3++) putchar(a[t3]);
//        printf("'   '");
//        for (t3=j-t2; t3<j; t3++) putchar(b[t3]);
//        printf("'\n");
//        x += max(t1, t2);
//    }
//
//    system("pause");
//} 

/////////////////////////////////////////////////////////////
// test for fstream state after each operation
//#include<iostream>
//#include<fstream>
//#include<cstdlib>
//using namespace std;
//
//inline void stateout(const ios &os, char* text = NULL){
//    ios::fmtflags old = cout.setf(ios::boolalpha | ios::hex | ios::showbase);
//    if(text)
//        cout << text << ":" ;
//    cout << ' ' << (void*)os.rdbuf() << '\n';
//    cout << " good? " << os.good() << " fail? " << os.fail()
//        << " eof? " << os.eof() << " bad? " << os.bad() << '\n';
//    cout.flags(old);
//}
//
//int main(){
//    ifstream ifs;
//    ofstream ofs;
//    fstream fs;
//    stateout(ifs, "ifs default constructor");
//    stateout(ofs, "ofs default constructor");
//    stateout(fs, "fs default constructor");
//    cout << '\n';
//
//    ifs.open("ifs.txt");
//    ofs.open("ofs.txt");
//    fs.open("fs.txt");
//    stateout(ifs, "ifs after open empty file");
//    stateout(ofs, "ofs after open empty file");
//    stateout(fs, "fs after open empty file");
//    cout << '\n';
//
//    ifs.close();
//    ofs.close();
//    fs.close();
//    stateout(ifs, "ifs after close");
//    stateout(ofs, "ofs after close");
//    stateout(fs, "fs after close");
//    cout << '\n';
//
//    ifs.clear();
//    ofs.clear();
//    fs.clear();
//    stateout(ifs, "ifs after clear");
//    stateout(ofs, "ofs after clear");
//    stateout(fs, "fs after clear");
//    cout << '\n' << '\n' ;
//
//    //istream mis;
//    //ostream mos;
//    //iostream mios;
//    //stateout(mis, "istream default constructor");
//    //stateout(mos, "ostream default constructor");
//    //stateout(mios, "iostream default constructor");
//    cout << '\n';
//
//    system("pause");
//}

///////////////////////////////////////////////////////////
// snprintf or _snprintf ? test STLP
//#include<stdio.h>
//#include<stdlib.h>
//int main(){
//    int m=5, n=10;
//    float a=1.5, b=-2e9, c=5.34e-5;
//    char buffer[200];
//    printf("%d\n",
//        _snprintf(buffer, 200, "m = %d, n = %d, a = %f, b = %g, c = %g\n", m, n, a, b, c));
//    printf("%s", buffer);
//    system("pause");
//}

/////////////////////////////////////////////////////////////
//#include<cstdio>
//#include<iostream>
//#include<string>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//class Acc {
//    vector<int> total;
//    vector<int> idxs;
//    struct idxcmp{
//        const vector<int> &vt;
//        idxcmp(const vector<int> &cmpvt):vt(cmpvt){}
//        bool operator()(int idx1, int idx2) const {
//            return vt[idx1] > vt[idx2];
//        }
//    };
//    void sort(){
//        ::stable_sort(idxs.begin(), idxs.end(), idxcmp(total));
//    }
//public:
//    Acc():total(26, 0), idxs(26){
//        for(int i = 0; i < 26; ++i)idxs[i] = i;
//    }
//    void operator()(char ch){
//        if(ch < 'a' || ch > 'z')return;
//        ++total[ch - 'a'];
//    }
//    void output(ostream &os){
//        sort();
//        os << "Max:\n" << char(idxs.front() + 'a') << ' ' << total[idxs.front()] << '\n';
//        os << "Sort:\n";
//        for(vector<int>::iterator it = idxs.begin(); it != idxs.end(); ++it){
//            if(total[*it] > 0)
//                os << char(*it + 'a') << ' ' << total[*it] << '\n';
//        }
//    }
//};
//
//int main(){
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//    Acc accumulator;
//    string line;
//    while(getline(cin, line) && line != "###")
//        for_each<string::const_iterator, Acc&>(line.begin(), line.end(), accumulator);
//    accumulator.output(cout);
//}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// P(n, r)
//#include<iostream>
//#include<ctime>
//using namespace std;
//
//int digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
//int n = sizeof(digits)/sizeof(digits[0]);
//int m = 11;
//// 从 n 个中取 m 个排列。当前例子 n = 9, m = 4
//
//int arr[3024];
//int idx = 0;
//
//int makenum(){
//    int num = digits[0];
//    for(int i = 1; i < m; ++i){
//        num *= 10;
//        num += digits[i];
//    }
//    return num;
//}
//
//void arrange(int writepos = 0){
//    if(writepos == m){  // 得到一个排列，输出
//        //arr[idx++] = makenum();
//        ++idx;
//        return;
//    }
//    for(int readpos = writepos; readpos < n; ++readpos){
//        swap(digits[writepos], digits[readpos]);
//        arrange(writepos + 1);
//        swap(digits[writepos], digits[readpos]);
//    }
//}
//
//int main(){
//    clock_t start = clock();
//    int times = 1;
//    while(times--){
//        idx = 0;
//        arrange();
//    }
//    cout << "CPU Clocks: " << clock()-start << '\n';
//    cout << "Total arranges: " << idx << endl;
//    system("pause");
//}
//-----------------------------------------------
//#include<stdio.h>
//#include<time.h>
//#include<stdlib.h>
//void MakeNums(int index,int limit,int pick[],int *nums,int *Index_arr,int *arr,int times);
//int NotContains(int *nums,int n,int index);
//int MakeNum(int nums[],int limit);
//int main()
//{
//    int i;
//    int Index_arr = 0,arr[3024],nums[11];
//    int pick[]={1,2,4,5,6,7,8,9,10,11,'\0'};
//    clock_t start = clock();
//    MakeNums(0,11,pick,nums,&Index_arr,arr,3024);
//    printf("%d\n", clock()-start);
//    //for(i = 0;i<Index_arr;i++)
//    // printf("%d\n",arr[i]);
//    system("pause");
//    return 0;
//}
//
////index：位数下标，用于标识现在循环到了某次整数的第几位
////limit：标志是几位数
////pick：筛选序列，pick以'\0'结尾
////nums：存放整数的每一位的数组
////Index_arr:作为最终存放所有符合条件的生成数的数组的下标
////arr：存放所有的数
////times：生成多少个数，没有本参数程序正常运行，但是某种情况下会降低性能
//
//void MakeNums(int index,int limit,int pick[],int *nums,int *Index_arr,int *arr,int times)
//{
//    int i;
//    if(index < limit)
//    {
//        for(i = 0;pick[i]!='\0';i++)
//            if(NotContains(nums,pick[i],index) == 1)
//            {
//                *(nums+index) = pick[i];
//                MakeNums(index+1,limit,pick,nums,Index_arr,arr,times);   
//            }
//    }
//    else if(index == limit) 
//    {
//        //*(arr+*Index_arr) = MakeNum(nums,limit);
//        //(*Index_arr)++;
//        //if(*Index_arr == times)
//        //{
//        // return;
//        //}
//    }
//
//}
//
////判断某个数是否在数组中
////nums：数组
////n：某个数
////index：需要判断到数组的第几个元素
//
//int NotContains(int *nums,int n,int index)
//{
//    int i;
//    for(i = 0;i<index;i++)
//    {
//        if(*(nums+i) == n)
//            return 0;
//    }
//    return 1;
//}
//
////利用数组累加生成整数
////nums:数组
////limit:生成几位数
//
//int MakeNum(int nums[],int limit)
//{
//    int i,sum = 0;
//    for(i = 0;i<limit;i++)
//        sum = sum*10+nums[i];
//    return sum;
//} 

//#include<stdio.h>
//#include<stdlib.h>
//int main(){
//    char ch;
//    printf("%d\n", scanf("%*[^\n]"));
//    fflush(stdout);
//    system("pause");
//}

////////////////////////////////////////////////////////////////
// vector vs deque ...
// VC STL is rubbish
//#include<iostream>
//#include<vector>
//#include<deque>
//#include<ctime>
//using namespace std;
//const int testsize = 1000000;
//int main(){
//    vector<int> vec;
//    deque<int> deq;
//    clock_t s;
//
//    s = clock();
//    for(int i=0; i<testsize; ++i)
//        vec.push_back(i);
//    cout << "vector initial: " << clock() - s << '\t';
//    vec.clear();
//    s = clock();
//    for(int i=0; i<testsize; ++i)
//        vec.push_back(i);
//    cout << clock() - s << '\n';
//
//    s = clock();
//    for(int i=0; i<testsize; ++i)
//        deq.push_back(i);
//    cout << "deque initial: " << clock() - s << '\n';
//
//    cout << endl;
//
//    s = clock();
//    srand((unsigned)time(NULL));
//    for(int i=0; i<testsize; ++i){
//        vec[i] = deq[i] = rand()%testsize;
//    }
//    cout << "randomize time: " << clock() - s << '\n';
//
//    s = clock();
//    int idx = 0;
//    for(int i=0; i<testsize; ++i)
//        idx = vec[idx];
//    cout << "last idx: " << idx << "\tvector time: " << clock() - s << '\n';
//
//    s = clock();
//    idx = 0;
//    for(int i=0; i<testsize; ++i)
//        idx = deq[idx];
//    cout << "last idx: " << idx << "\tdeque time:  " << clock() - s << endl;
//    system("pause");
//}

//#include<iostream>
//#include<vector>
//using namespace std;
//int main(){
//    vector<int> vec;
//    int cap = 0;
//
//    for(int i=0; i<1000000; ++i){
//        vec.push_back(i);
//        if(vec.capacity() != cap){
//            cap = vec.capacity();
//            cout << cap << '\n';
//        }
//    }
//    cout.flush();
//    system("pause");
//}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// dynamic 2-dimention array with pointer
// learn the typedef of pointers

//#include<stdlib.h>
//#include<stdio.h>
//int main(){
//    int m = 5, n = 6;
//    //int **p = new int*[m];
//    //for(int i=0; i<m; ++i){
//    //    p[i] = new int[n];
//    //}
//    //int i;
//    //int **p = (int**)malloc(m*sizeof(int*));
//    //for(i=0; i<m; ++i)
//    //    p[i]=(int*)malloc(n*sizeof(int));
//    int (*p)[2] = (int(*)[2])malloc(m*sizeof(int[2]));
//    p[1][1] = 3;
//    p[2][0] = 5;
//    for(int i=0; i<m; ++i)
//        printf("%d %d\n", p[i][0], p[i][1]);
//    free(p);
//    system("pause");
//}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// test of virtual function table
//#include<iostream>
//#include<cstdlib>
//using std::cout;
//using std::endl;
//
//class Base {
//public:
//    virtual void f() 
//    {
//        cout<<"Base b:"<<(void*)this << endl;
//    }
//};
//
//void main(void)
//{
//    typedef void(*Fun)(void);
//
//    Base b;
//    Fun pFun = NULL;
//
//    cout << "对象b虚函数表地址：" << (&b) << endl;
//    cout << "对象b虚函数表 第一个函数f()的地址：" << (int*)*(int*)(&b) << endl;
//
//    pFun = (Fun)*((int*)*(int*)(&b));
//    pFun();
//
//    b.f();
//
//    Base* pNull = &b;
//    pNull->f();
//
//    system("pause");
//}

//#include <iostream>
//#include<cstdlib>
//using namespace std;
//class A
//{
//public:
//     A(int x){cout<<"构造函数执行中...\n",i=x;}
//     A(A&a){cout<<"复制构造函数执行中...\n";i=a.i;}
//     ~A(){cout<<"析构函数执行中...\n";}
//     int get(){return i;}
//     void set(int x){i=x;}
//private:
//     int i;
//};
//A func();
//int cal(int a, int b){
//    return b==0?a:(a+cal(a-1, b-1));
//}
//int main()
//{
//     A &r=func();
//     //func();
//     //cout<<cal(5,20)<<endl;
//     cout<<"主函数中,a对象副本的地址:"<<&r<<endl;
//     cout<<r.get()<<endl;
//     system("pause");
//     return 0;
//}
//A func()
//{
//     cout<<"跳转到func函数"<<endl;
//     A a(8888);
//     cout<<"func函数中,对象a的地址:"<<&a<<endl;
//     return a;
//}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// move file pointer to last position and write there
// this can make a definite size of file
//#include<cstdio>
//#include<cstdlib>
//const int filesize = 1 * 1024;
//int main(){
//    FILE *fp = fopen("ofile.bnr", "wb");
//    fseek(fp, filesize - 1, SEEK_SET);
//    fputc(0, fp);
//    fclose(fp);
//}

////////////////////////////////////////////////
// complicated pointer
//typedef int (*intfun)();
//void *abc(){return 0;}
//int main(){
//    int a;
//    int (*(*ptr(void *(), int *))[])();
//    intfun (*pfunarray)[];
//    pfunarray = ptr(abc, &a);
//}

///////////////////////////////////
// random points in a triangle
//#include<iostream>
//#include<fstream>
//#include<cmath>
//#include<ctime>
//#include<cstdlib>
//using namespace std;
//class random3{
//    double a,b;
//public:
//    double k1, k2, k3;
//    random3(){srand((unsigned)time(NULL));}
//    void next(){
//        a = (double)rand()/RAND_MAX;
//        b = (double)rand()/RAND_MAX;  // 0 <= a,b <= 1
//        if(a>b)swap(a,b);
//        k1 = a;
//        k2 = b - a;
//        k3 = 1 - b;
//    }
//};
//int main(){
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//    random3 r;
//    double x[3], y[3], z[3];
//    for(int i=0; i<3; ++i)cin>>x[i]>>y[i]>>z[i];
//    for(int i=0; i<10000; ++i){
//        r.next();
//        cout << r.k1 * x[0] + r.k2 * x[1] + r.k3 * x[2] << ' '
//            << r.k1 * y[0] + r.k2 * y[1] + r.k3 * y[2] << ' '
//            << r.k1 * z[0] + r.k2 * z[1] + r.k3 * z[2] << '\n';
//    }
//}

////////////////////////////////////////////////
////////////////////////////////////////////////
// combination : next_permutation() vs dfs
// dfs is about 4.5 times faster than next_permutation()
//#include<iostream>
//#include<algorithm>
//#include<ctime>
//using namespace std;
//const int MAX_N = 30;
//const int n = 25;
//const int m = 10;
//int a[MAX_N];
//int b[m];
//
//void combine(int a[], int n, int m,  int b[], const int M ){
//    int i,j;
//    for(i=n; i>=m; i--)   // 注意这里的循环范围
//    {
//        b[m-1] = i - 1;
//        if (m > 1)
//            combine(a,i-1,m-1,b,M);
//        else {                   // m == 1, 输出一个组合
//            int idx = 0;
//            for(j=M-1; j>=0; j--)
//                ::b[idx++] = a[b[j]];
//                //printf("%d  ", a[b[j]]); 
//        }
//    }
//}
//
//int main(){
//    clock_t start;
//    for(int i=0; i<MAX_N; ++i)a[i] = i+1;
//
//    int comb[n];
//    start = clock();
//    fill_n(comb, n-m, 0);
//    fill_n(comb+n-m, m, 1);
//    do{
//        int idx = 0;
//        for(int i=0; i<n; ++i)if(comb[i])
//            b[idx++] = a[i];
//    }while(next_permutation(comb, comb+n));
//    cout << "next_permutation(): " << clock() - start << endl;
//
//    start = clock();
//    combine(a, n, m, comb, m);
//    cout << "dfs combine(): " << clock() - start << endl;
//    system("pause");
//}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// BKDRHash is better than DJBHash
// seed = 131, 1313   slightly slow , less collision
// seed = 31          fast but more collision (like DJBHash)
//#include<cstdio>
//#include<cstring>
//#include<cstdlib>
//#include<ctime>
//const char cstr[] = "abcdefghijklmnopqrstuvwxyz0123456789 ";
//const int testtime = 10;
//const int bufsize = 10000000;
//char buffer[bufsize];
//const int maxstrsize = bufsize / sizeof(cstr) * 1.1;
//char *str[maxstrsize];
//const int hashsize = maxstrsize * 10;
//char hash[hashsize];
//int strsize;
//
//void initstr(){
//    buffer[bufsize-1] = 0;
//    int bufidx = 0, stridx = 0;
//    while(bufidx < bufsize - 1 && stridx < maxstrsize){
//        str[stridx++] = buffer + bufidx;
//        while((buffer[bufidx++] = cstr[rand()%sizeof(cstr)]) != 0){
//            if(bufidx == bufsize-1)break;
//        }
//    }
//    strsize = stridx;
//}
//
//unsigned int BKDRHash(char *str)
//{
//	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
//	unsigned int hash = 0;
// 
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
// 
//	return (hash & 0x7FFFFFFF);
//}
//unsigned int BKDRHash1(char *str)
//{
//	unsigned int seed = 31; // 31 131 1313 13131 131313 etc..
//	unsigned int hash = 0;
// 
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
// 
//	return (hash & 0x7FFFFFFF);
//}
//unsigned int BKDRHash2(char *str)
//{
//	unsigned int seed = 1313; // 31 131 1313 13131 131313 etc..
//	unsigned int hash = 0;
// 
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
// 
//	return (hash & 0x7FFFFFFF);
//}
//unsigned int BKDRHash3(char *str)
//{
//	unsigned int seed = 13131; // 31 131 1313 13131 131313 etc..
//	unsigned int hash = 0;
// 
//	while (*str)
//	{
//		hash = hash * seed + (*str++);
//	}
// 
//	return (hash & 0x7FFFFFFF);
//}
//unsigned int DJBHash(char *str)
//{
//	unsigned int hash = 5381;
// 
//	while (*str)
//	{
//		hash += (hash << 5) + (*str++);
//	}
// 
//	return (hash & 0x7FFFFFFF);
//}
//
//int main(){
//    srand((unsigned)time(NULL));
//    initstr();
//    unsigned h, collision;
//    clock_t st;
//
//    printf("Total strings: %d\n", strsize);
//
//    collision = 0;
//    memset(hash, 0, sizeof(hash));
//    st = clock();
//    for(int i = 0; i < strsize; ++i){
//        for(int j=0; j<testtime; ++j)
//            h = BKDRHash(str[i])%hashsize;
//        if(hash[h])++collision;
//        else hash[h] = 1;
//    }
//    printf("BKDRHash: %u\tCollision: %u\n", clock() - st, collision);
//
//    collision = 0;
//    memset(hash, 0, sizeof(hash));
//    st = clock();
//    for(int i = 0; i < strsize; ++i){
//        for(int j=0; j<testtime; ++j)
//            h = BKDRHash1(str[i])%hashsize;
//        if(hash[h])++collision;
//        else hash[h] = 1;
//    }
//    printf("BKDRHash1: %u\tCollision: %u\n", clock() - st, collision);
//
//    collision = 0;
//    memset(hash, 0, sizeof(hash));
//    st = clock();
//    for(int i = 0; i < strsize; ++i){
//        for(int j=0; j<testtime; ++j)
//            h = BKDRHash2(str[i])%hashsize;
//        if(hash[h])++collision;
//        else hash[h] = 1;
//    }
//    printf("BKDRHash2: %u\tCollision: %u\n", clock() - st, collision);
//
//    collision = 0;
//    memset(hash, 0, sizeof(hash));
//    st = clock();
//    for(int i = 0; i < strsize; ++i){
//        for(int j=0; j<testtime; ++j)
//            h = BKDRHash3(str[i])%hashsize;
//        if(hash[h])++collision;
//        else hash[h] = 1;
//    }
//    printf("BKDRHash3: %u\tCollision: %u\n", clock() - st, collision);
//
//    collision = 0;
//    memset(hash, 0, sizeof(hash));
//    st = clock();
//    for(int i = 0; i < strsize; ++i){
//        for(int j=0; j<testtime; ++j)
//            h = DJBHash(str[i])%hashsize;
//        if(hash[h])++collision;
//        else hash[h] = 1;
//    }
//    printf("DJBHash:  %u\tCollision: %u\n", clock() - st, collision);
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////
// ATL 3.0 Windowing programming
//#include <atlbase.h>
//CComModule _Module;
//
//int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd )
//{
//    _Module.Init( NULL, hInstance );
//    _Module.m_hInstResource = LoadLibrary( _T("shell32.dll") );
//
//    MSGBOXPARAMS mbp;
//    ZeroMemory( &mbp, sizeof( mbp ) );
//    mbp.cbSize       = sizeof( mbp );
//    mbp.dwLanguageId = GetSystemDefaultLangID();
//    mbp.dwStyle      = MB_USERICON;
//    mbp.hInstance    = _Module.GetResourceInstance();
//    mbp.lpszCaption  = _T("Hello");
//    mbp.lpszIcon     = MAKEINTRESOURCE( 44 );
//    mbp.lpszText     = _T("Hello, World!");
//    MessageBoxIndirect( &mbp );
//
//    FreeLibrary( _Module.m_hInstResource );
//    _Module.m_hInstResource = NULL;
//    _Module.Term();
//    return 0;
//}

////////////////////////////////////////////////////////////
// Baidu zhidao problem.
//#include<iostream>
//#include<algorithm>
//#include<vector>
//using namespace std;
//
//class queue{
//    struct node{
//        char val;
//        node *next;
//        node(char Val = 0):val(Val), next(NULL){}
//    };
//    node hnode;
//    node *head, *tail;
//public:
//    queue(){
//        head = tail = &hnode;
//    }
//    void push(char val){
//        tail->next = new node(val);
//        tail = tail->next;
//    }
//    char pop(){
//        if(head->next != NULL){
//            node *tmp = head->next;
//            if(tmp == tail)tail = head;
//            char val = tmp->val;
//            head->next = tmp->next;
//            delete tmp;
//            return val;
//        } else {
//            cout << "Error! Cannot pop from an EMPTY queue !" << endl;
//            return 0;
//        }
//    }
//    bool empty() const {
//        return head->next == NULL;
//    }
//};
//
//class heap{
//    struct node{
//        char ch;
//        int key;
//        node(char Ch, int Key):ch(Ch), key(Key){}
//        bool operator<(const node &r)const{
//            return key > r.key;
//        }
//    };
//    vector<node> vec;
//public:
//    void push(char ch, int key){
//        vec.push_back(node(ch, key));
//        push_heap(vec.begin(), vec.end());
//    }
//    char pop(){
//        if(!vec.empty()){
//            pop_heap(vec.begin(), vec.end());
//            char ch = vec.back().ch;
//            vec.pop_back();
//            return ch;
//        } else {
//            cout << "Error! Cannot pop from an EMPTY heap !" << endl;
//            return 0;
//        }
//    }
//    bool empty() const {
//        return vec.empty();
//    }
//};
//
//int main(){
//    char ch;
//    int key, count;
//    queue highqueue, lowqueue;
//    heap hp;
//    while(cin>>ch && ch != '='){
//        if(ch == '*'){
//            cin>>count;
//            while(!hp.empty())
//                lowqueue.push(hp.pop());
//            cout<<"service: ";
//            while(count--){
//                if(!highqueue.empty())
//                    cout<<highqueue.pop()<<' ';
//                else
//                    cout<<lowqueue.pop()<<' ';
//            }
//            cout<<'\n';
//        } else {
//            cin>>key;
//            if(key == 1){
//                highqueue.push(ch);
//            } else {
//                hp.push(ch, key);
//            }
//        }
//    }
//    system("pause");
//}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// 1000,000 内的亲和数
//#include<cstdio>
//#include<vector>
//#include<cmath>
//using namespace std;
//
//const int maxnum = 6000000;
//vector<int> primes;
//void init(){
//    static int inits[] = {2,3,5,7,11,13,17,19,23,29,31};
//    primes.reserve(370);
//    primes.assign(inits, inits+sizeof(inits)/sizeof(inits[0]));
//    for(int num = primes.back() + 2; num <= (int)ceil(sqrt(double(maxnum))); num += 2){
//        int root = int(ceil(sqrt((double)num))), i;
//        for(i = 1; primes[i] <= root; ++i)
//            if(num % primes[i] == 0)break;
//        if(primes[i] > root)primes.push_back(num);
//    }
//}
//void factor(int num, vector<pair<int,int> > &facs){
//    int idx = 0;
//    facs.clear();
//    while(num > 1){
//        int root = int(ceil(sqrt((double)num)));
//        while(primes[idx] <= root && num%primes[idx]) ++idx;
//        if(primes[idx] > root){
//            if(!facs.empty() && num == facs.back().first)
//                ++facs.back().second;
//            else facs.push_back(make_pair(num, 1));
//            break;
//        } else {
//            if(!facs.empty() && primes[idx] == facs.back().first)
//                ++facs.back().second;
//            else facs.push_back(make_pair(primes[idx], 1));
//            num /= primes[idx];
//        }
//    }
//}
//int facsum(int num){
//    static vector< pair<int, int> > factors;
//    factor(num, factors);
//    int product = 1, sum, val, times;
//    for(vector<pair<int,int> >::iterator it=factors.begin();
//        it != factors.end(); ++it){
//            sum = 1; val = it->first; times = it->second;
//            while(times--){
//                sum += val;
//                val *= it->first;
//            }
//            product *= sum;
//    }
//    return product - num;
//}
//
//int main(){
//    freopen("o.txt", "w", stdout);
//    init();
//    for(int a = 1; a <= 1000000; ++a){
//        int b = facsum(a);
//        if(b < a)continue;
//        if(facsum(b) == a){
//            printf("%d %d\n", a, b);
//        }
//    }
//    //system("pause");
//}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// n 选 r 组合
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<conio.h>
//using namespace std;
//
//class combination{
//    vector<int> seq;
//public:
//    combination(int n, int r):seq(n, 0){
//        if(r > n)return;
//        fill_n(seq.begin(), r, 1);
//    }
//    bool next(){
//        return prev_permutation(seq.begin(), seq.end());
//    }
//    ostream& output(ostream &os) const {
//        for(int i = 0; i < (int)seq.size(); ++i)
//            if(seq[i])os<< i+1 << ' ';
//        os.put('\n');
//        return os;
//    }
//};
//
//int main(){
//    int n = 0;
//    combination comb(11, 3);
//    do{
//        comb.output(cout);
//        ++n;
//        _getch();
//    }while(comb.next());
//    cout<< "\nTotal: " << n << " combinations." << endl;
//    system("pause");
//}

//---------------------------------------
//#include<cstdio>
//#include<vector>
//#include<conio.h>
//using namespace std;
//
//void combination(int seq[], int n, int r){
//    static vector<int> comb;
//    if(n == r || r == 0){
//        for(int i=0; i<r; ++i)
//            comb.push_back(seq[i]);
//        for(int i=0; i<(int)comb.size(); ++i)
//            printf("%d ", comb[i]);
//        putchar('\n');
//        for(int i=0; i<r; ++i)
//            comb.pop_back();
//        _getch();
//        return;
//    }
//    comb.push_back(seq[0]);
//    combination(seq+1, n-1, r-1);
//    comb.pop_back();
//    combination(seq+1, n-1, r);
//}
//
//int main(){
//    vector<int> seq;
//    for(int i=1; i<=11; ++i)
//        seq.push_back(i);
//
//    combination(&seq[0], 11, 3);
//    system("pause");
//
//    combination(&seq[0], 7, 4);
//    system("pause");
//}


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
// 构造函数 顺序
//#include<iostream>
//using namespace std;
//
//class A
//{
//public:
//	A(int j) : age(j),num(age + 1)
//	{
//		cout << "age:" << age << ",num:" << num <<endl;
//	}
////protected:
//	int num;
//	int age;
//};
//void main()
//{
//	A sa(15);
//    cout<< "num: " << sa.num << "\nage: " << sa.age << endl;
//    system("pause");
//}; 

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// string::find vs std::search
// string::find is a little better !

// in STL they are not KMP search algorithm...
//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<ctime>
//using namespace std;
//const int test_sz = 1000000;
//
//int main(){
//    string text1 = "234567890234567234567890234567234567890234567234567890234567234567890234567";
//    string searchText1 = "123456789012345";
//    string text2 = "111111111111112111111111111112111111111111112111111111111112111111111111112";
//    string searchText2 = "111111111111111";
//
//    int sum;
//    clock_t start;
//
//    cout<<"string::find :\t";
//    start = clock();
//    sum = 0;
//    for(int i=0; i<test_sz; ++i){
//        sum += text1.find(searchText1);
//    }
//    cout<<clock() - start<<'\t';
//    start = clock();
//    sum = 0;
//    for(int i=0; i<test_sz; ++i){
//        sum += text2.find(searchText2);
//    }
//    cout<<clock() - start<<'\n';
//
//    cout<<"std::search :\t";
//    start = clock();
//    sum = 0;
//    for(int i=0; i<test_sz; ++i){
//        //sum += text1.find(searchText1);
//        sum += search(text1.begin(), text1.end(), searchText1.begin(), searchText1.end())
//            - text1.begin();
//    }
//    cout<<clock() - start<<'\t';
//    start = clock();
//    sum = 0;
//    for(int i=0; i<test_sz; ++i){
//        //sum += text2.find(searchText2);
//        sum += search(text2.begin(), text2.end(), searchText2.begin(), searchText2.end())
//            - text2.begin();
//    }
//    cout<<clock() - start<<'\n';
//
//    system("pause");
//}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//char *keys[] = {
//    "int", "float", "double", "void", "char", "unsigned", "short", "long"
//};
//
//int main(){
//    freopen("i.txt", "r", stdin);
//    freopen("o.txt", "w", stdout);
//    int first = 1;
//    char str[200] = {0};
//    for(;;){
//        if(scanf("%[a-zA-Z_]", str) == 1){
//            for(int i=0; i<sizeof(keys)/sizeof(keys[0]); ++i)
//                if(strcmp(str, keys[i]) == 0){
//                    if(first)first = 0;
//                    else putchar(' ');
//                    printf("%s", str);
//                }
//        }
//        int ch = getchar();
//        if(ch == '\n'){
//            putchar('\n');
//            first = 1;
//        }
//        else if(ch == EOF)break;
//    }
//
//    return 0;
//}

///////////////////////////////////////////////////
// test system structure's influence on performance ...
//#include<cstdio>
//#include<ctime>
//#include<cstdlib>
//
//const int maxn = 2048;
//
//int matrix[maxn][maxn];
//
//int main(){
//    int sum1, sum2;
//    clock_t st;
//    srand((unsigned)time(NULL));
//
//    for(int i=0; i<maxn; ++i)
//        for(int j=0; j<maxn; ++j)
//            matrix[i][j] = rand()%1024;
//
//    sum1 = 0;
//    st = clock();
//    for(int i=0; i<maxn; ++i)
//        for(int j=0; j<maxn; ++j)
//            sum1 += matrix[i][j];
//    printf("sum1 = %d\t%d\n", sum1, clock()-st);
//
//    sum2 = 0;
//    st = clock();
//    for(int i=0; i<maxn; ++i)
//        for(int j=0; j<maxn; ++j)
//            sum2 += matrix[j][i];
//    printf("sum2 = %d\t%d\n", sum2, clock()-st);
//
//    system("pause");
//}

//////////////////////////////////////////////////////////////////
// zhuangbility
//#include<cstdlib>
//int *bigger(){
//    return 0;
//}
//int main(){
//    int *(*(*p)[10])();
//    p = (int*(*(*)[10])())malloc(10 * sizeof(int*(*)()));
//    (*p)[0] = bigger;
//}

//////////////////////////////////////////////////////////////////
// 俄罗斯方块
//#include <windows.h>
//#include <iostream>
//#include <stdio.h>
//#include <conio.h>
//#include <time.h>
//using namespace std ;
//#define set_color(c) SetConsoleTextAttribute(hOut,c)
//
//enum {H=23, W=14, nBlock=7};
//HANDLE hIn, hOut;
//bool   bExit = false;
//int    level=0, score=0;
//int    ox=4, oy=1;
//int    B, N;
//int    X, Y, dir=0;
//int    delay_time = 20;
//int    flexible_time = 20;
//char   room[W][H];
//int    block[nBlock][4] =
//       {{0x6220,0x1700,0x2230,0x0740},      // L
//        {0x6440,0x0e20,0x44c0,0x8e00},      // _|
//        {0x04e0,0x0464,0x00e4,0x04c4},      // T
//        {0x4620,0x6c00,0x4620,0x6c00},      // z
//        {0x2640,0xc600,0x2640,0xc600},      // 反z
//        {0x0f00,0x4444,0x0f00,0x4444},      // |
//        {0x0660,0x0660,0x0660,0x0660}};     // 田
//
//void gotoxy (int x, int y)
//{
//    static COORD c; c.X = x; c.Y = y;
//    SetConsoleCursorPosition (hOut, c);
//}
//void draw (int x, int y, char* s) {gotoxy (x*2,y); cout<<s;}
//void over (int x, int y, char* s) {draw(x,y,s);getch();exit(1);}
//
//bool bMove_block (int bx, int by, int d)
//{
//    for (int p = 0x8000, x, y=0; y<4; y++)
//        for (x=0; x<4; x++, p>>=1)
//            if ((block[B][d]&p) && room[bx+x-ox][by+y-oy])
//                return false;
//    return true;
//}
//
//void show_next_block (char* s)
//{
//    set_color (N+7);
//    int x, y, p = 0x8000;
//    for (y=0; y<4; y++)
//        for (x=0; x<4; x++, p>>=1)
//            if (block[N][0] & p) draw (ox+W+2+x, 2+y, s);
//}
//void show_block (char* s)
//{
//    set_color (B+7);
//    int x, y, p = 0x8000;
//    for (y=0; y<4; y++)
//        for (x=0; x<4; x++, p>>=1)
//            if (block[B][dir] & p) draw (x+X, y+Y, s);
//}
//void show_room()
//{
//    for (int x,y=0; y<H; y++)
//        for (x=0; x<W; x++)
//            if (room[x][y]) {
//                set_color (room[x][y]);
//                draw (ox+x, oy+y, "█");
//            }else draw (ox+x, oy+y, "  ");
//}
//
//void try_move_block (int x, int y, int d)
//{
//    if (!bMove_block (x,y,d)) return;
//    show_block ("  "); X = x; Y = y; dir = d;
//    show_block ("█");
//}
//
//int remove_lines()
//{
//    int x, y, i,j, line=0;
//    for (y=1; y<H-1; y++) {
//        for (x=1; x<W-1; x++)
//            if (!room[x][y]) break;
//        if (x==W-1) {
//            line++;
//            for (i=1; i<W-1; i++) room[i][0] = 0;
//            for (i=y; i>1; i--)
//                for (j=1; j<W-1; j++)
//                    room[j][i] = room[j][i-1];
//            show_room ();
//        }
//    }return line;
//}
//
//void move_block()
//{
//    if (bMove_block (X,Y+1,dir)) {try_move_block (X,Y+1,dir); return;}
//    if (Y==0) over (ox+2, H/2, "G a m e    O v e r");
//
//    for (int p = 0x8000, x, y=0; y<4; y++)
//        for (x=0; x<4; x++, p>>=1)
//            if (block[B][dir] & p)
//                room[X+x-ox][Y+y-oy] = B+7;
//
//    int n = remove_lines();
//    level = (score+=(1+n*n)*4)/200;
//    delay_time = 10-level;
//    if (level > 10) over (ox+4, H/2, "Y o u    W i n");
//
//    show_next_block ("  ");
//    B = N; X = ox+W/2-1; Y = 0;
//    N = rand() % nBlock;
//    show_next_block ("█");
//}
//
//void init()
//{
//    srand (time(0));
//    hOut = GetStdHandle (STD_OUTPUT_HANDLE);
//    hIn  = GetStdHandle (STD_INPUT_HANDLE);
//    HANDLE err = INVALID_HANDLE_VALUE;
//    if (hIn == err || hOut == err) {
//        puts ("handle failed"); getch (); exit (1);
//    }
//    for (int x=0; x<W; x++) room[x][H-1] = 4;
//    for (int y=0; y<H; y++) room[0][y] = room[W-1][y] = 4;
//
//    B = rand() % nBlock;
//    N = rand() % nBlock;
//    X = ox+W/2-1;
//    Y = 0;
//    show_room();
//    show_next_block ("█");
//}
//
//void key_control()
//{
//    static DWORD count;
//    static INPUT_RECORD ir;
//    ReadConsoleInput (hIn, &ir, 1, &count);
//    if (!ir.Event.KeyEvent.bKeyDown) return;
//
//    switch (ir.Event.KeyEvent.wVirtualKeyCode) {
//        case VK_ESCAPE: bExit = true; break;
//        case VK_DOWN : try_move_block (X,Y+1,dir); break;
//        case VK_LEFT : try_move_block (X-1,Y,dir); break;
//        case VK_RIGHT: try_move_block (X+1,Y,dir); break;
//        case VK_UP   : try_move_block (X,Y,(dir+1)&3); break;
//    }
//}
//
//int main ()
//{
//    int i; init();
//    while (!bExit)
//    {
//        for (i=0; i<flexible_time; i++)
//        {
//            if (kbhit()) key_control();
//            Sleep (delay_time);
//        }
//        move_block ();
//        set_color (14);
//        gotoxy (ox+W*2+8, 10); cout<< "Level: "<<level+1;
//        gotoxy (ox+W*2+8, 12); cout<< "Score: "<<score;
//    }
//}

//////////////////////////////////////////////////////////////
// 三根火柴组成三角形 概率
//#include<cstdlib>
//#include<cstdio>
//#include<ctime>
//const int testcase = 10;
//const int testnum = 100000;
//
//inline bool valid(double x, double y){
//    if(x < y){
//        return x < 0.5 && y > 0.5 && y-x < 0.5;
//    } else {
//        return y < 0.5 && x > 0.5 && x-y < 0.5;
//    }
//}
//
//int main(){
//    srand((unsigned)time(NULL));
//    for(int i=0; i<testcase; ++i){
//        int cnt = 0;
//        for(int j=0; j<testnum; ++j){
//            if(valid((double)rand()/RAND_MAX, (double)rand()/RAND_MAX))
//                ++cnt;
//        }
//        printf("%.2f%%\n", (double)cnt/testnum*100);
//    }
//    system("pause");
//}

//////////////////////////////////////////////////
// 动态二维数组
//#include<cstdio>
//#include<cstdlib>
//
//int main(){
//    int m, n, num, i, j;
//    int *buf, **a;
//    scanf("%d%d", &m, &n);
//    buf = (int*)malloc(m*n*sizeof(int));
//    a = (int**)malloc(m*sizeof(int*));
//    for(i=0; i<m; ++i)
//        a[i] = buf+i*n;
//    for(num=1, i=0; i<m; ++i)for(j=0; j<n; ++j){
//        a[i][j] = num++;
//    }
//    num = m * n;
//    for(i=0; i<num; ++i)
//        printf("%d\n", buf[i]);
//    for(i=0; i<m; ++i){
//        for(j=0; j<n; ++j)printf("%d ", a[i][j]);
//        putchar('\n');
//    }
//    free(a);
//    free(buf);
//    system("pause");
//}

////////////////////////////////////////////
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef unsigned char *byte_pointer;
//
//void show_bytes(byte_pointer start, int len){
//    int i;
//    for(i=0; i<len; ++i)
//        printf("%02X ", start[i]);
//    printf("\n");
//}
//
//void show_int(int x){
//    show_bytes((byte_pointer) &x, sizeof(x));
//}
//
//void show_float(float x){
//    show_bytes((byte_pointer) &x, sizeof(x));
//}
//
//void show_pointer(void *x){
//    show_bytes((byte_pointer) &x, sizeof(x));
//}
//
//void test_show_bytes(int val){
//    printf("%d:\n", val);
//    int ival = val;
//    float fval = (float) ival;
//    int *pval = &ival;
//    show_int(ival);
//    show_float(fval);
//    show_pointer(pval);
//    printf("\n");
//}
//
//int main(){
//    test_show_bytes(0);
//    test_show_bytes(1);
//    test_show_bytes(2);
//    test_show_bytes(3);
//
//    //int val = 0x12345678;
//    //byte_pointer pval = (byte_pointer) &val;
//    //show_bytes(pval, 1);
//    //show_bytes(pval, 2);
//    //show_bytes(pval, 3);
//
//    system("pause");
//}

/////////////////////////////////////////////////////
//// VC STL incompatible: increment to end iterator should be legal
//#include<cstdio>
//#include<iostream>
//#include<iterator>
//#include<string>
//using namespace std;
//
//int main(){
//    //freopen("i.txt", "r", stdin);
//    //freopen("o.txt", "w", stdout);
//
//    //istream_iterator<string> cinStr(cin);
//    //istream_iterator<string> cinEnd;
//    //ostream_iterator<string> coutStr(cout, "\n");
//    //while(cinStr != cinEnd){
//    //    *coutStr = *cinStr;
//    //    advance(cinStr, 2);
//    //}
//    ++istream_iterator<int>();
//    ++istream_iterator<int>();
//    ++istream_iterator<int>();
//    ++istream_iterator<int>();
//    ++istream_iterator<int>();
//}

////////////////////////////////////////////////////////////////////////
// setjmp() longjmp()
//#include<cstdio>
//#include<cstdlib>
//#include<csetjmp>
//
//int main(){
//    jmp_buf env;
//    int a = 1;
//    volatile int b = 2;
//    int c = setjmp(env);
//    if(!c){
//        printf("First here...:\na = %d\tb = %d\n", a, b);
//        a = 11;
//        b = 12;
//        longjmp(env, 1);
//    } else {
//        printf("\na = %d\tb = %d\n", a, b);
//    }
//    system("pause");
//}

////////////////////////////////////////////////////////
// A? B: C 算符，当 A true 时仅 B 会运算，C 部分不会执行；反之亦然
//#include<iostream>
//#include<cstdlib>
//using namespace std;
//
//int main(){
//    int a(3), b(4), c;
//    c = a>b? ++a: ++b;
//    cout << a << ' ' << b << ' ' << c << endl;
//    c = a-b? a+b: a-3? b: a;
//    cout << a << ' ' << b << ' ' << c << endl;
//    system("pause");
//}

///////////////////////////////////////////////////////
// return value of sprintf() function
// conclusion: not count the ending '\0'

//#include<cstdio>
//#include<cstdlib>
//
//int main(){
//    char buf[20];
//    printf("Return value: %d\nString: %s\n", sprintf(buf, "%d %s", 1, "321"), buf);
//    system("pause");
//}

///////////////////////////////////////////////////////
// int *a[10];
// int (*a)[10];

//#include<cstdio>
//#include<cstdlib>
//
//int main(){
//    int *a[10];
//    int (*b)[10];
//    printf("sizeof(int *[10]):\t%d\n", sizeof(a));
//    printf("sizeof(int (*)[10]:\t%d\n", sizeof(b));
//    system("pause");
//}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int adjcent_matrix[50][50] = {0};
//int shortest_path[50][50] = {0};
//int cost_matrix[50][50] = {0};
//
//void Floyd();
//// Floyd: compute  shortest path
//void Floyd()
//{
//	FILE * file = 0;
//	int i , j , k;
//
//	fopen_s(&file , "m1.txt" , "r");
//	if(!file)
//		exit(0);
//
//	for(i=0 ; i<50 ; i++)
//		for(j=0 ; j<50 ; j++)
//			fscanf(file , "%d" , &adjcent_matrix[i][j]);
//
//	for(i=0 ; i<50 ; i++)
//		for(j=0 ; j<50 ; j++)
//			shortest_path[i][j] = adjcent_matrix[i][j];
//
//	for(k=0 ; k<50 ; k++)
//		for(i=0 ; i<50 ; i++)
//			for(j=0 ; j<50 ; j++)
//				shortest_path[i][j] = ( shortest_path[i][j] < shortest_path[i][k] + shortest_path[k][j] ) ? shortest_path[i][j] : shortest_path[i][k] + shortest_path[k][j];
//}
//
//typedef struct {
//	int cur_city;
//	int visited[50];
//	int cost;
//	int length;
//	int min_length;
//
//	int cur_city_num;
//	int seq[50];
//} Spot;
//Spot * Queue[10000000];
//int head=0 , tail=0;
//
//void enQueue(Spot * s)
//{
//	Queue[head] = s;
//	head = head+1;
//}
//
//Spot * deQueue()
//{
//	int pos;
//	if(head == tail)
//		return 0;
//	head = head-1;
//	//pos = head;
//	//head = head-1;
//	return Queue[head];
//}
//
//void BranchAndBound()
//{
//	int cur_city = 0;
//	int bestc = 9999;
//	int i;
//	Spot * cur_spot = 0;
//	Spot * p = 0;
//	Spot * cur_best_spot = 0;
//
//	Spot * city_0 = (Spot *) malloc( sizeof(Spot) );
//	city_0->cost = 0;
//	city_0->cur_city = 0;
//	city_0->length = 0;
//	city_0->min_length = shortest_path[0][49];
//	memset(city_0->visited , 0 , 50*sizeof(int));
//	city_0->visited[0] = 1;
//
//	//store path
//	city_0->cur_city_num = 1;
//	city_0->seq[city_0->cur_city_num-1] = 0;
//
//	enQueue(city_0);
//
//	while( (cur_spot=deQueue()) != 0)
//	{
//		cur_city = cur_spot->cur_city;
//		for(i=1 ; i<50 ; i++)
//		{
//			if(!cur_spot->visited[i])
//			{
//				if(adjcent_matrix[cur_city][i] != 9999)
//				{
//					if(cur_spot->cost + cost_matrix[cur_city][i] <= 1500)
//					{
//						p = (Spot *) malloc( sizeof(Spot) );
//						*p = *cur_spot;
//						p->cur_city = i;
//						p->cost = cur_spot->cost + cost_matrix[cur_city][i];
//						p->length = cur_spot->length + adjcent_matrix[cur_city][i];
//						p->min_length = p->length + shortest_path[i][49];
//						p->visited[i] = 1;
//
//						//update path
//						p->seq[p->cur_city_num++] = i;
//						if(i==49)
//						{
//							if(p->length < bestc)
//							{
//								bestc = p->length;
//								cur_best_spot = p;
//							}
//						}
//
//						else if(p->min_length < bestc)
//						{
//							enQueue(p);
//						}
//						else
//							free(p);
//					}
//				}
//			}
//		}
//
//	}
//	printf("shortest path length: %d\n" , bestc);
//	printf("shortest path: 0");
//	for(i=1 ; i<cur_best_spot->cur_city_num ; i++)
//		printf(" -> %d" , cur_best_spot->seq[i]);
//	printf("\n");
//}
//
//
//
//int main()
//{
//	FILE * file = 0;
//	int i , j;
//
//	fopen_s(&file , "m2.txt" , "r");
//	if(!file)
//		exit(0);
//
//	for(i=0 ; i<50 ; i++)
//		for(j=0 ; j<50 ; j++)
//			fscanf(file , "%d" , &cost_matrix[i][j]);
//
//	Floyd();
//	BranchAndBound();
//	return 0;
//}
//


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// explicit keyword:
// class constructor. operator= initialization

//#include<iostream>
//using namespace std;
//
//class X{
//    int i;
//public:
//    explicit X(int ii): i(ii){}
//    explicit X(const X &r): i(r.i){}
//    void output()const{
//        cout << "i: " << i << endl;
//    }
//};
//
//int main(){
//    X x = X(5);
//    x.output();
//    system("pause");
//}

//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 去掉多余 \n
//#include<iostream>
//#include<fstream>
//using namespace std;
//
//int main(int argc, char *argv[]){
//    if(argc != 3){
//        cout << "Usage: "<< argv[0] << " InFile OutFile\n";
//        exit(1);
//    }
//    ifstream fin(argv[1]);
//    if(!fin){
//        cout << "Cann't open file " << argv[1] << "...\n";
//        exit(1);
//    }
//    ofstream fout(argv[2]);
//
//    char ch;
//    int state = 0;
//    while(fin.get(ch)){
//        switch(state){
//        case 0:
//            fout.put(ch);
//            if(ch == '\n') state = 1;
//            break;
//        case 1:
//            if(ch != '\n'){
//                fout.put(ch);
//            }
//            state = 0;
//        }
//    }
//
//    return 0;
//}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//#include<stdio.h>
//
//void r(){
//    int c = getchar();
//    if(c != '\n') r();
//    putchar(c);
//}
//int main(){
//    r();
//}

/////////////////////////////////////////////////////////////////////////////////////////////////
//#include<iostream>
//using namespace std;
//class xxx{
//    xxx(){cout<<"ctor"<<endl;}
//    xxx(const xxx &x){cout<<"cp ctor"<<endl;}
//    xxx& operator=(const xxx &x){cout<<"assign op"<<endl;return *this;}
//    ~xxx(){cout<<"dtor"<<endl;}
//};
//int main(){
//    xxx x(xxx());   // declaration, not variable definition
//    system("pause");
//}

////////////////////////////////////////////////////////////////////////////////////////////////
//#include <Windows.h>
//#include <tchar.h>
//#include <stdio.h>
//
//LRESULT CALLBACK Wndproc(HWND,UINT ,WPARAM, LPARAM );
//
//int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPTSTR lpCmdLine, int nCmdShow )
//
//{
//	HWND          hwnd;
//	MSG           msg;
//	WNDCLASS      wndclass;
//	TCHAR          lpszClassName[]    = _T("窗口");//窗口类名
//	TCHAR          lpszTitle[]   = _T("my ,windows");//窗口标题
//	wndclass.style              =0;//窗口类型
//	wndclass.lpfnWndProc        =Wndproc;//窗口处理函数
//	wndclass.cbClsExtra         =0;
//	wndclass.cbWndExtra         =0;
//	wndclass.hInstance          =hInstance;//当前实例句柄
//	wndclass.hIcon              =LoadIcon(NULL,IDI_APPLICATION);//窗口最小化图标
//	wndclass.hCursor            =LoadCursor(NULL,IDC_ARROW);//窗口箭头光标
//	wndclass.hbrBackground      =(HBRUSH)GetStockObject(WHITE_BRUSH);//窗口背景颜色
//	wndclass.lpszMenuName       =NULL;//窗口菜单
//	wndclass.lpszClassName       =lpszClassName;//窗口类名
//
////窗口类的注册
//	if(!RegisterClass(&wndclass))
//	{
//		MessageBeep(0);
//		return FALSE;
//	}
//
////创建窗口
//
//	hwnd=CreateWindow
//		(
//		lpszClassName,//窗口类名
//		lpszTitle,//窗口标题名
//		WS_OVERLAPPEDWINDOW,//窗口风格
//		CW_USEDEFAULT,//X坐标
//		CW_USEDEFAULT,//Y坐标
//		CW_USEDEFAULT,//宽度
//		CW_USEDEFAULT,//高度
//		NULL,//父窗口
//		NULL,//主菜单
//		hInstance,//当前实例句柄
//		NULL
//		);
//
//	//显示窗口
//
//	ShowWindow(hwnd,nCmdShow);
//
//	//绘制用户区，或者刷新用户区
//
//	UpdateWindow(hwnd);
//
//	//消息循环
//
//	while(GetMessage(&msg,NULL,0,0))
//	
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//
//	}
//	return msg.wParam;//程序终止时将信息返回系统
//
//}
//
////窗口处理
//
//LRESULT CALLBACK Wndproc(HWND  hwnd,UINT  message,WPARAM   wparam, LPARAM   lparam )
//
//{
//	switch(message)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);//发出WM_Quit
//
//	default:
//		return DefWindowProc (hwnd,message,wparam,lparam);
//	}
//	return 0;
//
//}
/************************************************************/
/*
#include <iostream>
using std::ostream;
class Complex {
public:
	int re;
	int im;
	Complex(int a,int b):re(a),im(b) {}
	Complex operator+(Complex& a) {
		return Complex(re+a.re,im+a.im);
	}
};
ostream& operator<<(ostream& output,Complex& a) {
    a.re += 5;
    a.im += 5;
	output<<a.re;
	if (a.im>0) { output<<"+"; }
	if (a.im==0) { return output; }
	output<<a.im<<"i";
	return output;
}
int main() {
	using std::cout;
	using std::endl;
	Complex a(5,3);
	Complex b(10,4);
	cout<<a+b<<endl;
	cout<<(a+b)<<endl;
    system("pause");
	return 0;
}
/************************************************************/
/* 测试大内存占用与小内存占用多次访问之间的速度差异（L1 L2 Cache 未命中时的影响）
// 小于 200K 的 10 个质数 [204679, 204707, 204719, 204733, 204749, 204751, 204781, 204791, 204793]
#include<cstdlib>
#include<cstdio>
#include<ctime>

int main(){
    const int LARGESIZE = 177147;
    const int SMALLSIZE = 59049;
    int *largebuf, *smallbuf;
    largebuf = (int*)malloc(LARGESIZE * sizeof(int));
    smallbuf = (int*)malloc(SMALLSIZE * sizeof(int));

    clock_t start, end;
    start = clock();
    for(int n=0; n<7000; ++n){
        for(int i=0; i<LARGESIZE; i+=1) largebuf[i] += 2;
    }
    end = clock();
    printf("large buffer: %ld\n", end - start);

    start = clock();
    for(int n=0; n<13000; ++n){
        for(int i=0; i<SMALLSIZE; i+=1) smallbuf[i] *= 23;
    }
    end = clock();
    printf("small buffer: %ld\n", end - start);
    system("pause");
}

/**/

/************************************************************/
/* 测试数组是否调用 object 的默认构造函数
// 结论是会调用
#include <cstdio>
#include <cstdlib>
class A{
public:
    A(){
        printf("A::A() called...\n");
    }
};
int main(){
    A a[3];
    system("pause");
}
/************************************************************/
//* 测试 vec.push_back(vec.back()) 是否有问题
// 貌似可以用

//#include <iostream>
//#include <vector>
//#include <string>
//using namespace std;
//
//int main(){
//    vector<string> vec;
//    vec.push_back("string1");
//    vec.push_back("abc");
//
//    vec.push_back(vec.back());
//    for(auto i = vec.begin(); i != vec.end(); ++i){
//        cout << *i << endl;
//    }
//    system("pause");
//}


/************************************************************/
//* Boost 1.54.0 TEST

//#include <boost/lambda/lambda.hpp>
//#include <iostream>
//#include <iterator>
//#include <algorithm>
//
//int main()
//{
//    using namespace boost::lambda;
//    typedef std::istream_iterator<int> in;
//
//    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
//
//    system("pause");
//}

/************************************************************/
//* Boost random class

//#include <boost/random.hpp>
//#include <iostream>
//
//int main()
//{
//    boost::random::mt19937 gen;
//    boost::random::uniform_int_distribution<unsigned long long> ran;
//
//    for(int i=0; i<10; ++i)
//    {
//        std::cout << ran(gen) << '\n';
//    }
//    system("pause");
//}



/***************************************************************/
//* constructor
/* VS2010 中 vector::emplace_back 仅是个占位函数，效果与 push_back 等价

#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

class A{
public:
    A(){
        cout << "Normal Constructor" << endl;
    }
    A(const A &r){
        cout << "Copy Constructor" << endl;
    }
    A(A &&r){
        cout << "Move Constructor" << endl;
    }

    A& operator=(const A &r){
        cout << "Normal operator=" << endl;
        return *this;
    }
    A& operator=(A &&r){
        cout << "Move operator=" << endl;
        return *this;
    }
};


int main(){
    vector<A> va;
    va.reserve(20);
    cout << "va.emplace_back(move(A())):" << endl;
    va.emplace_back(move(A()));
    cout << "va constructed." << endl;

    cout << "\nva.push_back(A()):" << endl;
    va.push_back(A());
    cout << "va.push_back(va.back()):" << endl;
    va.push_back(va.back());

    cout << "\nva.emplace_back():" << endl;
    va.emplace_back(va.back());

    

    cout << endl;
    system("pause");
}

/**/
/******************************************************************/
/* C++11 test

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

template <typename C>
class less_by_idx{
    const C &con;
public:
    less_by_idx(const C &c): con(c) {}
    bool operator()(int idx1, int idx2) const {
        return con[idx1] < con[idx2];
    }
};

int main(){
    ::srand((unsigned)::time(nullptr));
    vector<int> vec;
    vec.resize(10);
    for_each(vec.begin(), vec.end(), [](int &x){
        x = rand();
    });

    cout << "vec:\n";
    for(auto i = vec.begin(); i != vec.end(); ++i){
        cout << (*i) << ' ';
    }
    cout << endl;

    vector<int> idx;
    idx.resize(vec.size());
    for(int i = 0; i < idx.size(); ++i){
        idx[i] = i;
    }

    sort(idx.begin(), idx.end(), less_by_idx<vector<int>>(vec));

    //sort(idx.begin(), idx.end(), [&](int i, int j) -> bool{
    //    return vec[i] < vec[j];
    //});

    cout << "sorted:\n";
    for(auto i = idx.begin(); i != idx.end(); ++i){
        cout << vec[*i] << ' ';
    }
    cout << endl;

    system("pause");
}

/**/

/************************************************************************/
/* test if std::copy optimized for POD type

#include <algorithm>
#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

class My_POD{
    int a, b;
    char str[4];
};

class Not_POD{
    vector<int> *pv;
public:
    Not_POD():pv(nullptr){}
    Not_POD(const Not_POD &r): pv(r.pv){pv->push_back(5);}
    Not_POD& operator=(const Not_POD &r){
        pv = r.pv;
        pv->push_back(3);
        return *this;
    }
    virtual void output(){cout << pv << endl;}
    virtual ~Not_POD(){}
};

int main(){
    My_POD pod[10] = {};
    My_POD des[20];
    Not_POD npod[10] = {};
    Not_POD ndes[20];

    // 貌似没有针对 POD 类型进行优化，还是手动 memcpy 靠谱。。
    copy(pod, pod + sizeof(pod)/sizeof(pod[0]), des);
    copy(npod, npod + sizeof(npod)/sizeof(npod[0]), ndes);

}

enum MyColor : char {Green, Black, MyYellow};

/**/


/************************************************************************/
/* lambda 内的 static 变量就相当于一个普通函数内的 static 变量
//* 对于同一语句中的临时 lambda，（如 test 函数中，for_each 里的那个），反复调用
//* 此函数时仅产生一个 static 变量，也只初始化一次。相当于整个 lambda 都变成函数内
//* 的 static lambda 变量了。
//* 目前的理解是，同一段代码就产生一个 lambda，反复调用也仅是调用此 lambda。不是同
//* 一段的代码产生不同的 lambda，哪怕 lambda 完全一致，也是不同的 lambda 对象。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class A{
public:
    A(){
        cout << "A ctor." << endl;
    }
    ~A(){
        cout << "A dtor." << endl;
        system("pause");
    }
};

void test(vector<int> &v){
    cout << "In test():" << endl;
    for_each(v.begin(), v.end(), [](int &x){
        static int a = 1;
        static A aa;
        x = a++;
        cout << "a address: " << &a << endl;
    });
}

int main(){
    cout << "In main():" << endl;
    vector<int> v(3);
    test(v);
    test(v);

    class B{};
    B b;

    //auto op = [](int &x){
    //    static int a = 1;
    //    x = a++;
    //    cout << "a address: " << &a << endl;
    //};
    //for_each(v.begin(), v.end(), op);
    //for_each(v.begin(), v.end(), op);

    //for_each(v.begin(), v.end(), [](int &x){
    //    static int a = 1;
    //    x = a++;
    //    cout << "a address: " << &a << endl;
    //});
    //for_each(v.begin(), v.end(), [](int &x){
    //    static int a = 1;
    //    x = a++;
    //    cout << "a address: " << &a << endl;
    //});

    for_each(v.begin(), v.end(), [](int x){
        cout << x << ' ';
    });

    system("pause");
}


/************************************************************************/
/* lambda 访问类成员变量是 by value 还是 by reference ?

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class A{
    int a;
    vector<int> v;
public:
    A():v(2){}
    void test(){
        cout << "test for int a:" << endl;
        cout << "the address of class int a: " << &a << endl;
        cout << "the address of lambda int a: ";
        for_each(v.begin(), v.end(), [this](int){
            cout << &a << ' ';
        });
        cout << endl;
    }
};

int main(){
    A t;
    t.test();

    system("pause");
}

/************************************************************************/
/* change the variable captured by value in a lambda

#include<iostream>
#include<vector>
using namespace std;

mysum(int x, int y) -> int {
    return x + y;
}

int main(){
    int n = 0;
    auto op = [=]()mutable{cout << n++ << endl;};
    for(int i=0; i<3; ++i){
        op();
    }

    system("pause");
}

/************************************************************************/
/*

#include <iostream>
using namespace std;

class A{
public:
    A(){
        cout << "A ctor." << endl;
    }
    ~A(){
        cout << "In A dtor:" << endl;
        system("pause");
        cout << "A dtor finisned." << endl;
    }
};

void test(){
    static A a;
    cout << "In test(), address of a: " << &a << endl;
}

int main(){
    cout << "In main(), test() begin:" << endl;
    test();
    cout << "In main(), test() finished." << endl;

    system("pause");

    return 0;
}


/************************************************************************/
/* unique_ptr to array

#include<memory>
#include <iostream>
using namespace std;

class A{
public:
    A(){ cout << "A ctor." << endl; }
    ~A(){ cout << "A dtor." << endl; }
};

int main(){
    {unique_ptr<A[]> a(new A[3]);}
    system("pause");
}

/************************************************************************/
