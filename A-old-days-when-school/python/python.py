#!/usr/bin/env python

# _*_ coding: iso-8859-1 _*_

import os

FileName = os.environ.get('PYTHONSTARTUP')
if FileName and os.path.isfile(FileName):
	execfile(FileName)
