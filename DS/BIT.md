### 一、模板类别

​	数据结构：树状数组

### 二、模板功能

#### 1.建立树状数组

1. 数据类型

   类型设定 `size_type = uint32_t` ，表示树状数组中下标编号的变量类型。

   模板参数 `typename Tp` ，表示元素类型。

   模板参数 `bool RangeUpdate`​ ，表示是否要支持区间修改。

   模板参数 `size_type MAX_NODE` ，表示最大结点数，默认为 `1<<22` 。

   构造参数 `size_type length` ，表示树状数组的覆盖范围为 `[0, length)`。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   树状数组处理的问题为单点增值修改，单点/区间和的查询。当 `RangeUpdate` 参数设置为 `true` 时，可以同时兼备区间增值修改的功能，但是时空效率都会下降。

   本树状数组模板与之前版本的重大区别为，不再支持乘法/除法或者其他类型的模板函数传递，转而要求树中元素类型支持加减法运算。如果确实有进行区间乘积维护的需求，使用者须自定义一个类作为元素类型。

   树状数组通过加和函数求解前缀和，再通过前缀和做差求解任意区间和。

   树状数组通过一些差分运算，实现了区间修改。

#### 2.建立树状数组

1. 数据类型

   构造参数 `Iterator __first` ，表示区间维护的区间头。

   构造参数 `Iterator __last` ，表示区间维护的区间尾。（开区间）

   其它同上。

2. 时间复杂度

   同上。

3. 备注

   同上。

   使用迭代器进行初始化，可以将区间初状态直接赋到树状数组里。

   本构造方法要求元素支持 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (减法)， `-` (负号)， `+=` 和 `*` 运算符。


#### 3.重置(resize)

1. 数据类型

   输入参数 `size_type length` ，表示树状数组要处理的区间大小。

2. 时间复杂度

   $O(n)$ 。

3. 备注

   调用本函数会将树状数组大小改变，并将之前的合并信息重置。

#### 4.重置(reset)

1. 数据类型

   输入参数 `Iterator first` ，表示区间维护的区间头。

   输入参数 `Iterator last` ，表示区间维护的区间尾。（开区间）

2. 时间复杂度

   同上。

3. 备注

   同上。

   使用迭代器进行重置，可以将区间初状态直接赋到树状数组里。

   本构造方法要求元素支持 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (减法)， `-` (负号)， `+=` 和 `*` 运算符。

#### 5.单点增值(add)

1. 数据类型

   输入参数 `size_type i​` ，表示单点增值的下标。

   输入参数 `const Tp &inc​` ，表示增量大小。

2. 时间复杂度

   $O(\log n)$ 。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

   本构造方法要求元素支持 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (负号)， `+=` 和 `*` 运算符。

#### 6.区间增值(add)

1. 数据类型

   输入参数 `size_type left` ，表示区间增值的开头下标。

   输入参数 `size_type right​` ，表示区间增值的结尾下标。(闭区间)

   输入参数 `const Tp &inc` ，表示增量大小。

2. 时间复杂度

   $O(\log n)$ 。

3. 备注

   本方法仅当 `RangeUpdate` 为 `true` 时合法。

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`，且 `left <= right + 1` ）

   本构造方法要求元素支持 `-` (负号)， `+=` 和 `*` 运算符。

#### 7.前缀和查询(presum)

1. 数据类型

   输入参数 `size_type i`，表示前缀和查询的结尾下标。(闭区间)

2. 时间复杂度

   $O(\log n)$ 。

3. 备注

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

   本构造方法要求元素支持 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (负号)， `+=` 和 `*` 运算符。

#### 8.单点查询(query)

1. 数据类型

   输入参数 `size_type i` ，表示单点查询的下标。

2. 时间复杂度

   $O(\log n)$ 。

3. 备注

   本方法只有在做差函数合理的时候有意义。

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`）

   本构造方法要求元素支持 `-=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `+=` 运算符。

#### 9.区间查询(query)

1. 数据类型

   输入参数 `size_type left​` ，表示区间查询的开头下标。

   输入参数 `size_type right​`，表示区间查询的结尾下标。(闭区间)

2. 时间复杂度

   $O(\log n)$ 。
   
3. 备注

   本方法只有在做差函数合理的时候有意义。

   本函数没有进行参数检查，所以请自己确保下标合法。（位于`[0，n)`，且 `left <= right + 1` ）

   本构造方法要求元素支持  `-` (减法) 和 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (减号)， `+=` 和 `*` 运算符。

#### 10.查询全部和(queryAll)

1. 数据类型

2. 时间复杂度

   $O(\log n)$ 。

#### 11.查询第 k 个元素(kth)

1. 数据类型

   输入参数 `Tp k​` ，表示要查询的元素从小到大的顺次。

2. 时间复杂度

   $O(\log n)$ 。

3. 备注

   仅当树状数组的元素类型 `Tp` 为数字，且每个位置的值均为非负时，本方法才有意义。

   也可以解释为，本方法在求可令 `presum(i) > k` 成立的最小的 `i` 。

   顺次 `k​` 表示第 `k + 1` 小，顺次 `0` 表示查询最小的元素。

   本函数没有进行参数检查，所以请自己确保 `k` 合法。（位于`[0，queryAll())`）

   本构造方法要求元素支持 `<=` 和 `+=` 运算符。当 `RangeUpdate` 为 `true` 时，要求元素支持 `-` (减号)， `<=` ， `+=` ， `+` 和 `*` 运算符。
   

### 三、模板示例

```c++
#include "DS/BIT.h"
#include "IO/FastIO.h"

/*
 * 常规元素类型的单点修改树状数组
 */
void test1() {
    cout << "test of normal BIT(modify a single position):" << endl;
    // 当以长度进行构造的时候，树中元素均为默认初始值
    OY::BIT32<false> T(10);
    cout << T << endl;
    // 单点修改
    for (int i = 0; i < 10; i++) T.add(i, i * 100);
    cout << T << endl;
    // 输出前缀和
    cout << "presum(5) = " << T.presum(5) << endl;
    cout << "presum(3) = " << T.presum(3) << endl;
    // 输出单点值
    cout << "val(4) = " << T.query(4) << endl;
    cout << "val(5) = " << T.query(5) << endl;
    // 输出区间和
    cout << "sum(4 ~ 5) = " << T.query(4, 5) << endl;
    // 树中第 k 小元素查询
    cout << "kth(0) = " << T.kth(0) << endl;
    cout << "kth(99) = " << T.kth(99) << endl;
    cout << "kth(100) = " << T.kth(100) << endl;
    cout << "kth(299) = " << T.kth(299) << endl;
    cout << "kth(1499) = " << T.kth(1499) << endl;
    cout << "kth(1500) = " << T.kth(1500) << endl;
    cout << endl;
}

/*
 * 常规元素类型的区间增值修改树状数组
 */
void test2() {
    cout << "test of normal BIT(modify a range):" << endl;
    // 可以以区间来构造
    OY::BIT64 T;
    int64_t arr[7] = {4, 9, 2, 3, 5, 8, 7};
    T.reset(arr, arr + 7);
    cout << T << endl;

    // 如果 RangeUpdate 为 true ，则可以进行区间增值
    OY::BIT64<true> T2(arr, arr + 7);
    cout << T2 << endl;
    T2.add(1, 5, 1000);
    cout << T2 << endl;
    cout << endl;
}

struct elem {
    // 假设我们这里的元素的加法重载为成员 val 的乘法
    // 那么减法就是 val 的除法
    double val;
    // 默认元素的值必须为 1
    elem(double _val = 1) : val(_val) {}
    elem operator+(const elem &rhs) const { return elem(val * rhs.val); }
    elem operator-(const elem &rhs) const { return elem(val / rhs.val); }
    elem &operator+=(const elem &rhs) {
        val *= rhs.val;
        return *this;
    }
    elem &operator-=(const elem &rhs) {
        val /= rhs.val;
        return *this;
    }
    bool operator<=(const elem &rhs) const { return val <= rhs.val; }
    elem operator-() const { return elem(1 / val); }
    elem operator*(uint32_t x) const {
        elem res;
        while (x--) res += *this;
        return res;
    }
    template <typename Ostream>
    friend Ostream &operator<<(Ostream &out, const elem &x) {
        if (x.val < 1)
            return out << "1/" << int64_t(std::round(1 / x.val));
        else
            return out << int64_t(std::round(x.val));
    }
};
/*
 * 自定义类型的单点修改树状数组
 */
void custom_test1() {
    cout << "test of custom BIT(modify a single position):" << endl;
    elem arr[] = {1, 2, 1, 2, 1};
    // 从区间构造时，必须支持 += 运算符
    OY::BinaryIndexedTree::BIT<elem, false> T(arr, arr + 5);
    // 要想支持打印，必须支持 -= 运算符和流式输出
    cout << T << endl;
    // 要想支持单点修改，必须支持 += 运算符
    for (int i = 0; i < 5; i++) T.add(i, elem((i + 2) * 10));
    cout << T << endl;
    // 要想支持“前缀和”查询，必须支持 += 运算符
    cout << "presum(0, 4) = " << T.presum(4) << endl;
    // 要想支持单点查询，必须支持 -= 运算符
    cout << "val(3) = " << T.query(3) << endl;
    cout << "val(4) = " << T.query(4) << endl;
    // 要想支持区间查询，必须支持 += 和 -(减法) 运算符
    cout << "sum(3 ~ 4) = " << T.query(3, 4) << endl;
    // 对于本元素，kth 没有实际意义。硬要说的话，算是一个二分，即“至少到哪儿，才可以让前缀和超过一定的程度”
    // 要想支持 kth，必须支持 <= 和 += 运算符
    cout << "kth(599) = " << T.kth(599) << endl;
    cout << "kth(600) = " << T.kth(600) << endl;
    cout << "kth(23999) = " << T.kth(23999) << endl;
    cout << "kth(24000) = " << T.kth(24000) << endl;
    cout << endl;
}

/*
 * 自定义类型的区间增值修改树状数组
 */
void custom_test2() {
    cout << "test of custom BIT(modify a range):" << endl;
    elem arr2[] = {4, 9, 2, 3, 5, 7, 8};
    // 从区间构造，必须支持 -(减法)， -(负号)，+= 和 * 运算符
    OY::BinaryIndexedTree::BIT<elem, true> T(arr2, arr2 + 7);
    // 要想支持打印，必须支持 += 运算符和流式输出
    cout << T << endl;
    // 要想支持单点修改，必须支持 -(负号)，+= 和 * 运算符
    for (int i = 0; i < 5; i++) T.add(i, 10);
    cout << T << endl;
    // 要想支持区间修改，必须支持 -(负号)，+= 和 * 运算符
    T.add(5, 7, elem(10));
    cout << T << endl;
    // 要想支持“前缀和”查询，必须支持 -(负号)，+= 和 * 运算符
    cout << "presum(6) = " << T.presum(6) << endl;
    cout << "presum(4) = " << T.presum(4) << endl;
    // 要想支持单点查询，必须支持 += 运算符
    cout << "val(5) = " << T.query(5) << endl;
    cout << "val(6) = " << T.query(6) << endl;
    // 要想支持区间查询，必须支持 -(减号)，+= 和 * 运算符
    cout << "sum(5 ~ 6) = " << T.query(5, 6) << endl;
    // 对于本元素，kth 没有实际意义。硬要说的话，算是一个二分，即“至少到哪儿，才可以让前缀和超过一定的程度”
    // 要想支持 kth，必须支持 <= ， + ， -(减号)，+= 和 * 运算符
    cout << "kth(3599) = " << T.kth(3599) << endl;
    cout << "kth(3600) = " << T.kth(3600) << endl;
    cout << "kth(71999) = " << T.kth(71999) << endl;
    cout << "kth(72000) = " << T.kth(72000) << endl;
    cout << endl;
}

int main() {
    test1();
    test2();
    custom_test1();
    custom_test2();
}
```

```
#输出如下
test of normal BIT(modify a single position):
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
[0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 0, 0, 0, 0, 0, 0]
presum(5) = 1500
presum(3) = 600
val(4) = 400
val(5) = 500
sum(4 ~ 5) = 900
kth(0) = 1
kth(99) = 1
kth(100) = 2
kth(299) = 2
kth(1499) = 5
kth(1500) = 6

test of normal BIT(modify a range):
[4, 9, 2, 3, 5, 8, 7, 0]
[4, 9, 2, 3, 5, 8, 7, 0]
[4, 1009, 1002, 1003, 1005, 1008, 7, 0]

test of custom BIT(modify a single position):
[1, 2, 1, 2, 1, 1, 1, 1]
[20, 60, 40, 100, 60, 1, 1, 1]
presum(0, 4) = 288000000
val(3) = 100
val(4) = 60
sum(3 ~ 4) = 6000
kth(599) = 1
kth(600) = 1
kth(23999) = 2
kth(24000) = 2

test of custom BIT(modify a range):
[4, 9, 2, 3, 5, 7, 8, 1]
[40, 90, 20, 30, 50, 7, 8, 1]
[40, 90, 20, 30, 50, 70, 80, 10]
presum(6) = 604800000000
presum(4) = 108000000
val(5) = 70
val(6) = 80
sum(5 ~ 6) = 5600
kth(3599) = 1
kth(3600) = 2
kth(71999) = 2
kth(72000) = 3

```

