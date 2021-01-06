# -*- coding: utf-8 -*-
# @Author: TD21forever
# @Date:   2019-12-07 14:57:58
# @Last Modified by:   TD21forever
# @Last Modified time: 2019-12-07 15:00:35
import threading
def print_word(count):
	for i in range(count):
		print("It's counging ",i)
def main():
	t = threading.Thread(target=print_word,args=(10,))
	t.start()
	sum = 0
	for i in range(100):
		print("main print: ",i)

if __name__ == '__main__':
	main()
