[TOC]



#### 数据定义语句

+ create table 创建基本表

  ```sql
  create table xxx
  (
      eno char(4) not null unique,
      sex char(2) not null default('male'),
      age int
  )
  ```

+ alert table 增加、修改或删除其中一列，但是不支持修改列名

  + add 增加一个新的列
  + drop column 删除一个原有的列
  + alert column 修改列的数据类型

+ drop table 删除基本表

+ **create index 创建索引**

  >1. 数据库中的索引类似于一本书的目录，在一本书中通过目录可以快速找到你想要的信息，而不需要读完全书。
  >2. 索引建少了，用 WHERE 子句找数据效率低，不利于查找数据。索引建多了，不利于新增、修改和删除等操作
  >
  >3. 适合建立索引的情况：
  >   1. 经常被查询的属性
  >   2. 在order by中使用的属性
  >   3. 频繁出现在连接条件中的属性（主码、外部码）
  >   4. 该列的值唯一的属性

  + 聚集索引（CLUSTERED）**一个表只能有一个**

  >聚集索引就相当于使用字典的拼音查找，因为聚集索引存储记录是物理上连续存在的，即拼音 a 过了后面肯定是 b 一样

  ```sql
  create clustered index xxx on xxx()
  ```

  + 非聚集索引（NONCLUSTERED）**一个表可以存在多个,默认**

  > 非聚集索引就相当于使用字典的部首查找，非聚集索引是逻辑上的连续，物理存储并不连续。

+ drop index 删除索引

  ``` 
  drop index 表.索引
  ```

#### 基本的数据操作

+ insert

  ```sql
  insert into Employee(...)
  values(...)
  ```

+ update 修改表中已有记录的数据

  ```sql
  update xxx
  set xxx=""
  
  update xxx
  set xxx=xxx+12
  ```

+ delete 删除一些元组

  ```sql
  delete from xxx
  where xxx=xxx
  ```

#### 数据查询

+ select 返回指定列的信息

  ```sql
  select (distinct) name,sex,title from xxx
  ```

+ 特殊运算符号

  + IN,NOT IN
  + BETWEEN AND, NOT BETWEEN AND
  + IS NULL, IS NOT NULL
  + LIKE, NOT LIKE
    + `-` 表示任意单个字符串
    + `%` 表示任意长度字符串

+ 分组查询

  ```sql
  select name,AVG(age) as average_age 
  from xxx
  group by num  
  having avg(age)<50 //分组后的数据进行筛选
  
  ----|-----
  num |average_age
  01  |36
  ----|----
  02  |33
  ----|-----
  03  |43
  ```

  **where和having的区别**：

  1. where作用于基本表或者视图，having作用于分组后的组
  2. 分组之前先去掉不满足where条件的行
  3. having后可以用聚合函数（avg、count..），where后面不可以

+ 排序查询

  ```sql
  select* from xxx
  where xxx=xxx
  order by xxx DESC,xxx
  ```

  **DESC**降序，**ASC**升序，默认升序

+ **多关系连接查询**

  **student表**

  | ID   | Name |
  | ---- | ---- |
  | 1    | 张三 |
  | 2    | 李四 |
  | 3    | 王二 |

  **course**

  | ID   | Cname |
  | ---- | ----- |
  | 1    | 足球  |
  | 2    | 音乐  |
  | 4    | 美术  |

  1. 交叉连接(Cross Join)

     ```sql
     select * from student cross join course
     ```

     **笛卡尔积**，第一个表的行数乘以第二个表的行数等于笛卡尔积结果集的大小。(不常用)

     可以加入where条件，从笛卡尔积以后的集合中选择需要的元组

     ![1555826190250](C:\Users\TD21forever\AppData\Roaming\Typora\typora-user-images\1555826190250.png)

  2. 内部连接(Inner Join 或 join)

     ```sql
     select * from student inner join course on student.ID=course.ID
     <==>等价于
     select * from student,course where student.ID=course.ID
     ```

     inner join 是比较运算符，仅仅返回**符合条件的行**。

     ![1555825976962](C:\Users\TD21forever\AppData\Roaming\Typora\typora-user-images\1555825976962.png)

  3. 外部连接(Outer Join)

     + 左外连接(left join 或left outer join)

       ```sql
       select * from student left join course on student.ID = course.ID
       ```

       左外连接**包括left join左表所有行**。假设**左表中某行在右表没有匹配**。则结果中相应行**右表的部分所有为空(NULL)**

       ![1555825273799](C:\Users\TD21forever\AppData\Roaming\Typora\typora-user-images\1555825273799.png)

     + 右外连接

       ```sql
       select * from student right join course on student.ID=course.ID
       ```

       右外连接**包括right join右表所有行**，假设**左表中某行在右表没有匹配**，则结果中相应**左表的部分所有为空(NULL)**。

       ![1555825587994](C:\Users\TD21forever\AppData\Roaming\Typora\typora-user-images\1555825587994.png)

     + 全外连接

       ```sql
       select * from student full join course on student.ID=course.ID
       ```

       全然外连接包括full join左右两表中所有的行，假设右表中某行在左表中没有匹配，则结果中相应行右表的部分所有为空(NULL)，假设左表中某行在右表中没有匹配，则结果中相应行左表的部分所有为空(NULL)。

       ![1555825632988](C:\Users\TD21forever\AppData\Roaming\Typora\typora-user-images\1555825632988.png)

  4. 自身连接(Self Join)

     ```sql
     select emp1.name,emp2.manager from Employee emp1,Employee emp2 
     where emp1.manager = emp2.name
     ```

     如上代码，找到各个员工的老板。`emp1` 和 `emp2` 表的两个别名

+ 嵌套查询

  子查询都在父查询处理前求解，不依赖于父查询的任何条件

  ```sql
  select * from xxx where x in (select xxx from xxx ...)
  ```

+ **相关子查询**

  + Q1：输出每个年龄高于该部门平均年龄的职工姓名

    + 该职工所在部门的平均年龄（父查询）

    + 主查询职工所在的部门（子查询）

      ```sql
      select name
      from Employee emp1
      where age>    --该职工所在部门的平均年龄
      (
          select avg(age)
          from Employee emp2
          where emp2.Dno=emp1.Dno   --主查询职工所在的部门
      )
      ```

  + EXISTS

    + 测试子查询是否存在返回值

    ```sql
    --选择 参加了项目的职工
    select *
    Employee e
    where EXISTS --只要参加过一个项目就满足条件了
    (
    	select * --一般用*号处理
        from Item_Emp
        where Eno = e.Eno -- 在项目表里有这个员工的记录
    )
    ```

  + NOT EXITS

    ```sql
    --选择 一个项目都没有参加的职工
    select *
    Employee e
    where NOT EXISTS --只要参加过一个项目就满足条件了
    (
    	select * --一般用*号处理
        from Item_Emp
        where Eno = e.Eno -- 在项目表里有这个员工的记录
    )
    --要扫描到表底，证明item表中确实没这个人
    ```

  + 综合

    ```sql
    -- 找到 选修了所有课程的学生
    
--只要这门课在grade中被人选了 就返回
    select * from Course where exists
    (select * from Grade where Cno = Course.Cno)
    --如果这门课在grade中死活没有被人选
    select * from Course where not exists
    (select * from Grade where Cno = Course.Cno)
    
    --如果这门课被人选了而且选的人是2000101
    --简言之 这门课被2000101选了
    select * from Course where exists
    (select * from Grade where Cno = Course.Cno and Sno='2000101')
    
    --这门课没有被2000101选
    select * from Course where not exists
    (select * from Grade where Cno = Course.Cno and Sno='2000101')
    
    select * from Student where not exists
    --不存在这种情况
    (
    --这门课没有被某某某选
    select * from Course where not exists
    (select * from Grade where Cno = Course.Cno and Sno=Student.Sno)
    )
    ```
    
    
