#!/bin/python2
# What it's come to: we can't even write a wrapper script in bash

import subprocess
import os
import sys

if sys.argv[1] == '--test':
    # Exception handling baroquery because it's not possible to redirect to dev null in python
    # Why am I torturing myself with this joke language again?
    try:
        subprocess.check_output(['xset', '-q'], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as pythonSucks:
        exit(pythonSucks.returncode)
else:
    exit(subprocess.call(['notify-desktop']+sys.argv[1:]))
