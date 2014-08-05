// C++11 Lambda 递归调用自己

#include <cstdio>
#include <cstdlib>
#include <functional>

int main()
{
    // 注意：参数引用方式必须是 &
    std::function<int(int)> sum = [&](const int x) -> int {
        if(x == 1) return 1;
        return sum(x - 1) + x;
    };
    // 不能使用 auto sum 来声明，因为后面函数体内要引用 sum 时无法推断出类型，
    // 必须用 std::function<> 显示声明类型。

    printf("%d\n", sum(10));
    system("pause");
}

