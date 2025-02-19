### 一、模板类别

​	数据结构：最小割树。

### 二、模板功能

#### 1.最小割树

1. 数据类型

   模板参数 `typename _Tp` ，表示图中边权的类型。

   模板参数 `typename _Solver` ，表示最大流解法。

   构造参数 `uint32_t __vertexNum`​ ，表示图中的点数。

   构造参数 `uint32_t __edgeNum` ，表示图中预备要存的边数。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   本模板也可称之为 `Gusfield` 等价流树算法。用于查询无向图上任意两点之间的最小割。

   本模板类继承了 `FlowHelper` 类，而 `FlowHelper` 类继承了最大流的类。

   本模板支持自环和重边，支持不连通的图。

   **注意：**目前，本模板的最大流类，不支持预流推进法。

#### 2.加无向边

1. 数据类型

   输入参数 `uint32_t __a`​ ，表示无向边的一端的编号。

   输入参数 `uint32_t __b` ，表示无向边的另一端的编号。

   输入参数 `_Tp __cap` ，表示无向边的边容量。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   网络流的边往往是有向的，所以本方法实际插入了两条有向边。

#### 3.预备

1. 数据类型

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   本方法用于在加完所有边后，进行一些预处理。

#### 4.计算

1. 数据类型

   输入参数 `_Tp __infiniteCap` ，表示无穷大边权值。默认为 `_Tp` 类的最大值的一半。

2. 时间复杂度

   取决于使用的最大流类，如果使用 `Dinic` ，为 $O(n^3\cdot m)$ 。

3. 备注

   在调用本方法之前，请先预备或者按顺序预备。

   本方法通过分治法计算 `n-1` 对点之间的最大流（最小割），并将其连成树结构。

#### 5.查询两点间最小割

1. 数据类型

   输入参数 `uint32_t __a`​ ，表示一个结点的编号。

   输入参数 `uint32_t __b` ，表示另一个结点的编号。

   返回类型 `_Tp` ，表示两个结点间的最小割。

2. 时间复杂度

   $O(1)$ 。

3. 备注

   在调用本方法之前，请先调用计算方法。

### 三、模板示例

```c++
#include "GRAPH/GomoryHuTree.h"
#include "IO/FastIO.h"

int main() {
    //建图
    OY::GomoryHuTree<int, OY::Dinic> G(5, 5);
    //加五条边
    G.addEdge(0, 1, 200);
    G.addEdge(1, 2, 200);
    G.addEdge(3, 1, 300);
    G.addEdge(3, 2, 100);
    G.addEdge(0, 2, 100);
    //预备
    G.prepare();
    //计算
    G.calc();
    //查询
    cout << "mincut between 0 and 2 is: " << G.query(0, 2) << endl;
    cout << "mincut between 1 and 4 is: " << G.query(1, 4) << endl;
}
```

```
#输出如下
mincut between 0 and 2 is: 300
mincut between 1 and 4 is: 0

```

