UpdatePlan
==========

在开发驼峰验算程序时，AutoCAD格式的平面图中参数输入到验算程序时数据量大，而且复杂容易出错。李昕旭发现AutoCAD有一个“数据提取”工具，可以将图形参数导出到Excel中。

此程序就是根据CAD数据提取工具提取的Excel数据，整理出道岔、曲线，以及他们之间的连接关系。

#流程

删除不必要的图形，并将车场后半部也一同删除，然后使用数据提取工具，将图形导出到一个EXCEL文件中；

通过TMainForm::Import(void)函数，将AutoCAD的曲线和线段分别导入到TLines和TArcs数组中。

判断线段交叉，并将这些交叉保存到一个TCrosses类中。

删除一些明显不是道岔的线段交叉。

更新这些交叉中的线段的角度。

删除一些角度不符合道岔数据的交叉。



#AutoCAD平面图的要求

使用AutoCAD“数据提取”工具提取数据前应删除不必要的图形，只保留压钩坡至股道内的直线部分，尾部图形应删除。格式要求：

- 线路水平
- 股道在右，驼峰平台在左。
- 一个驼峰平台（压钩坡）

*注意：AutoCAD中常有隐藏图层，这些图层中的图像能够通过“数据提取”工具导出到EXCEL文件中，这些图层中的图形如果没必要导出，应删掉。*

#绘图

绘图部分是将TPlan绘制在TImage上。在TPlan中定义OriginX和OriginY两个定位参数，这两个参数标示TImage的左下角在TPlan中的坐标。

#识别道岔

道岔暂时只考虑两种：单开道岔和对称道岔。其他道岔可暂时手工添加。

对称道岔的特点为：有三个直线组成，三个线段的一个端点相交于一点。

根据不同绘图风格，单开道岔有各开向分别绘制；也有将直股按照一条直线绘制，侧向与直股相交的。各开向单独绘制的与对称道岔相似。

## 识别道岔位置

遍历所有线段的两个端点，判断这个端点是否与其他线段的端点重合，计数重合端点数量（三个为单开或对称道岔、四个为三开对称道岔），标记重合端点，计入重合点（即道岔）；

判断线段端点是否与其他线段重合，标记重合端点，计入重合点（即道岔）。

##识别道岔类型

**开向识别**：判断重合点个线段的角度关系：

- 三开道岔中有相同角度的为直向，其他为侧向；
- 双开道岔中相同角度的为直向，其他为侧向。
- 一个线段的端点在另一个线段上为单开道岔，线段为直向；

**角度**：通过直向与侧向角度可判定道岔转辙角，逆向或顺向。在开向识别的基础上通过线段之间的夹角判断道岔转辄号，并过滤掉一些非道岔线段连接。