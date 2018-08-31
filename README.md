Simple Chinese Word Segmentation Python package
======================
SCWS:http://www.xunsearch.com/scws/<br />
修改自：https://github.com/assad2008/Python-scws

安装：
----
	1】自行编译
```Bash
gcc scws.c -shared -o scws.so -I/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/usr/local/scws/include/scws -fPIC -L/usr/local/scws/lib/ -L/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/lib/ -lscws -lpython3.6	
```
		
	我的是Mac安装了python2和python3,so 路径包含比较长。
	
	gcc scws.c -shared -o scws.so -Ipython的include路径（头文件路径）-Iscws头文件路径 -fPIC -Lscws lib路径（库文件路径）-Lpython库文件路径 -lscws库名称（一般就是scws）-lpython3.6pythonlib库名称

	2】make
	请自行修改Makefile文件内容

	生成的scws.so 文件拷贝到你python的sites-packages下，然后fenci.py可自行参考修改，放到哪里无所谓，能引入到你项目就OK

	
	###请自行修改scws.c中的Python头文件
	
直接setup安装：
----
	创建setup.py文件.
```Python
from distutils.core import setup,Extension
MOD = 'scws' #模块名
setup(name=MOD,ext_modules=[Extension(MOD,sources=['scws.c'])]) #源文件名
```
```Python
python3 setup.py build 
python3 setup.py install
```

注意：
----
	若import出现“ImportError: libscws.so.1: cannot open shared object file: No such file or directory”错误。
	请将libscws.so.1文件创建软连接到/lib64中应该就可以解决“ln -s /usr/local/scws/lib/libscws.so.1 /lib64/libscws.so.1”。如不行请自行ldd scws.so文件查看库文件地址，将其软连接过去即可
	
	请使用python3
	若python2请clone https://github.com/assad2008/Python-scws

