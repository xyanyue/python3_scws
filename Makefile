all:
	gcc scws.c -shared -o scws.so -I/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/usr/local/scws/include/scws -fPIC -L/usr/local/scws/lib/ -L/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/lib/ -lscws -lpython3.6
clean:
	rm scws.so
