#!/usr/bin/python

import fib
import __builtin__

fib.fib(1000)

print fib.__name__

print dir(fib)

print dir(__builtin__)
