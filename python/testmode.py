
import foo

fooInstance = foo.Foo('xyz')
fooInstance.show_name()

print(globals())
print(locals())


def local_func():
    num = 1
    print(locals())

local_func()

import sys

print(sys.path)
print(sys.modules)
