#!/usr/bin/env python
import re

a,b = [sorted(re.findall('\d+', raw_input())) for line in (1,2)]
print 'equal' if a == b else 'not equal'
