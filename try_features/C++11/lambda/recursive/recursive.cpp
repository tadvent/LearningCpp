// C++11 Lambda �ݹ�����Լ�

#include <cstdio>
#include <cstdlib>
#include <functional>

int main()
{
    // ע�⣺�������÷�ʽ������ &
    std::function<int(int)> sum = [&](const int x) -> int {
        if(x == 1) return 1;
        return sum(x - 1) + x;
    };
    // ����ʹ�� auto sum ����������Ϊ���溯������Ҫ���� sum ʱ�޷��ƶϳ����ͣ�
    // ������ std::function<> ��ʾ�������͡�

    printf("%d\n", sum(10));
    system("pause");
}

