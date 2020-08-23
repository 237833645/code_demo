modem自动编译脚本python

包状态
ubuntu
Python 2.7.3
sudo apt-get install python-pip
sudo pip install xlrd
xlrd==1.1.0

1. 创建excel表单，填入makefile名称及最终打包名称，多个makefile多行填写
2. python XX.py xx.xls
3. XX.py 内完成：
    1. 获取参数及判断
    2. 更改目录地址app调用system来编译APP，解压编译包到根目录下
    3. 通过绝对路径解析excel表里面的数据存与buffer，xlrd
    4. 更改目录地址：
        1. 编译modem，
            1. for循环
                1. 删除build等临时目录，
                2. 调用os.system()下发编译指令，
                3. 等待最后的结果判断是否继续还是fail 退出，
                4. 调用mtk的打包pl脚本打包
                5. 拷贝根目录APP包到temp包
                6. 完成后重新命名包文件（buffer取出）
    5. 程序退出


xx.py分层：
1. app编译
2. modem编译
3. 拷贝文件
4. 重命名
5. 系统调用
6. 解压
7. 读取excel
8. 编译结果统计


涉及python知识点：
1. python传参
2. 绝对路径，工作目录切换
3. 读写excel表
4. 系统指令调用及返回值判断
5. tar解压
6. 拷贝及删除文件
7. 重命名文件
8. for循环
9. 字符串合并，字符串数组
10. 打包依赖包  tar和excel
11. python版本依赖













