### 一、模板类别

​	数据结构：无向图的欧拉回路。

### 二、模板功能

#### 1.构造图

1. 数据类型

   构造参数 `uint32_t __vertexNum`​ ，表示图中的点数。

   构造参数 `uint32_t __edgeNum` ，表示图中预备要存的边数。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   本算法处理的问题为无向图的欧拉回路和欧拉通路问题。

   本数据结构可以接受重边和自环。
   
   **注意：**

   本数据结构一开始指定的 `__vertexNum` 参数必须是确切值。
   
   一开始指定的 `__edgeNum` 参数可以是模糊值，是用来为加边预留空间的，即使一开始没有留够空间，也可以自动扩容。如果边数不确定，可以预估一个上限填进去。

#### 2.加边

1. 数据类型

   输入参数 `uint32_t __a`​ ，表示无向边的起点编号。

   输入参数 `uint32_t __b` ，表示无向边的终点编号。

2. 时间复杂度

   $O(1)$ 。


#### 3.预备

1. 数据类型

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   本方法用于在加完所有边后，进行一些预处理。

#### 4.判断是否是欧拉图

1. 数据类型

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   在调用本方法前，请先预备。

   欧拉图要求可以一笔画走完全图，且起点和终点相同。

#### 5.获取半欧拉图的起点

1. 数据类型

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   在调用本方法前，请先预备。

   半欧拉图要求可以一笔画走完全图，但不要求起点和终点相同。

   如果该图为欧拉图，任何点都可以作为起点，返回 `0` 。

   如果该图不为欧拉图但为半欧拉图，有且只有一个点可以作为起点，返回之。

   如果该图不为半欧拉图，返回 `-1` 。

#### 6.获取欧拉通路

1. 数据类型

   模板参数 `bool _EdgePath` ，表示最后的通路是否以边的编号形式返回。

   输入参数 `uint32_t __source` ，表示指定的起点。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   在调用本方法前，请先预备。

   如果该图为欧拉图，任何点都可以作为起点，且最后一定会得到一个环路。

   如果该图不为欧拉图但为半欧拉图，有且只有一个点可以作为起点，请先使用“获取半欧拉图的起点”方法来获取起点。

#### 7.获取欧拉通路（边形式）

1. 数据类型

   输入参数 `uint32_t __source` ，表示指定的起点。

   返回类型 `std::vector<uint32_t>` ，表示欧拉通路上每条边的编号。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   在调用本方法前，请先预备。

   如果该图为欧拉图，任何点都可以作为起点，且最后一定会得到一个环路。

   如果该图不为欧拉图但为半欧拉图，有且只有一个点可以作为起点，请先使用“获取半欧拉图的起点”方法来获取起点。

#### 8.获取欧拉通路（点形式）

1. 数据类型

   输入参数 `uint32_t __source` ，表示指定的起点。

   返回类型 `std::vector<uint32_t>` ，表示欧拉通路上每个点的编号。

2. 时间复杂度

   $O(n+m)$ 。

3. 备注

   在调用本方法前，请先预备。

   如果该图为欧拉图，任何点都可以作为起点，且最后一定会得到一个环路。

   如果该图不为欧拉图但为半欧拉图，有且只有一个点可以作为起点，请先使用“获取半欧拉图的起点”方法来获取起点。

### 三、模板示例

```c++
#include "GRAPH/EulerPath_udg.h"
#include "IO/FastIO.h"

int main() {
    OY::EulerPath_udg G(5, 5);
    //加五条边
    G.addEdge(0, 1);
    G.addEdge(2, 1);
    G.addEdge(2, 4);
    G.addEdge(4, 1);
    G.addEdge(3, 1);
    G.prepare();
    //判断是否是欧拉图
    if (G.isEulerGraph()) {
        cout << "Graph is EulerGraph\n";
    } else {
        cout << "Graph isn't EulerGraph\n";
    }
    //由于它不是欧拉图，只好退而求其次求半欧拉图的起点
    uint32_t source = G.getHalfEulerSource();
    if (source == -1) {
        cout << "Graph isn't half EulerGraph\n";
    } else {
        auto path = G.getPath_vertex(source);
        cout << "path:\n";
        for (auto a : path) cout << a << ' ';
    }
}
```

```
#输出如下
Graph isn't EulerGraph
path:
0 1 2 4 1 3 
```

