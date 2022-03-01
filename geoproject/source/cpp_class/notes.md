技术要点

1. 基于opencv，使用BFS获取连通的曲线

   算法输入：一张图片，要获取的连通曲线的一个点p

   算法输出：连通曲线的所有点的集合

   算法描述：

   1. 初始化队列que，把p加入que
   2. 初始化一个数组vect用来存储点集合
   3. while( que不为空 ):
   4. ​        初始化变量tmpp为que第一个元素，并且弹出这个元素
   5. ​        for tmpp周围八个像素点x:
   6. ​                 if x是一个黑色的可以被访问的点:
   7. ​                             把x加入que和vect数组
   8. 返回vect数组

   

2. 基于向量夹角和向量模长判断点在环内还是环外

   对于给定的点A

   ![a](D:\workplace\geoproject\pictureproject\data\UML\判断环内点.png)

   判断环内的方法
   $$
   |\cos \theta - 1|<0.0009    \\
   \lVert \alpha \rVert <\lVert \beta \rVert\\
   $$
   其中
   $$
   \cos \theta = \frac{(\alpha,\beta) }{\lVert \alpha \rVert \lVert \beta \rVert}
   $$
   
   
   
3. 利用DFS，访问最近的非本曲线的点，并标记曲线点深度数值

4. 使用策略模式编写代码，UML图如下


![a](D:\workplace\geoproject\pictureproject\data\UML\策略模式.png)



5. main文件夹的main.cpp可以计算每个点位每个地层的深度
