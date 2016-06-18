#/usr/bin/env python

"this is a module"

import sys
import os

debug = True

class FooClass(object):
	"Foo Class"
	pass

def test():
	"test fuction"
	foo = FooClass()

	if debug:
		print "ran test()'


if __name__ == '__main__':
	test()
