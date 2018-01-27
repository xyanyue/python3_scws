#coding:utf8
import sys
from fenci import fenci

fc = fenci()
fc.init_fenci()
ret = fc.get_text_fc('中华人民共和国万岁！')
for i in ret:
	print(i[0])
	print('-----')
