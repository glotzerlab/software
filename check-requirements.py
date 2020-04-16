#!/usr/bin/env python3

import pkg_resources
import sys

requirements = pkg_resources.parse_requirements(open(sys.argv[1]))
for requirement in requirements:
    requirement = str(requirement)
    pkg_resources.require(requirement)
