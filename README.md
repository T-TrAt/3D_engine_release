# 3D_engine_release

操作方法：
两种控制模式：**移动相机**和**移动物体**，按“1”键切换

**移动相机模式：**操作方法跟minecraft类似，懂得都懂。

**移动物体模式：**按“2”键切换选择的物体，选中的物体会被用白框围住。wasd控制移动，↑↓←→控制方向。

---

**资源文件**里面的txt文件是各种模型的顶点数据（相当于obj文件后缀名改为了txt）。
使用方法示例：

```c++
// 创建一个Object(Mesh对象, 缩放倍数), Mesh(文件路径,正面顶点是否为顺时针排列,读取形式)
// 读取形式：如果索引部分包含贴图和发现索引（形如a/b/c）那么就添0
// 如果索引不包含贴图和法线索引（形如a//）那么就添1
Object power_chair(Mesh("power_chair.txt", "clockwise", 0), 10);
power_chair.setPosition(Vector(0.0, 0.0, 5.0));	// 设置位置
power_chair.rotateTo(0.0, 180.0, 0.0);			// 设置旋转方向
power_chair.setColor(BGR(0xdddddd));			// 设置颜色（模型是纯色）
power_chair.setName(L"抛瓦！！！");				// 设置名称
Shader::objects.push_back(&power_chair);		// 将模型填入着色器（不填入就不渲染）
```

