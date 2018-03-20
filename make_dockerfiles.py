#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}

# dependencies
versions['EMBREE_VERSION'] = '2.17.1'

# glotzer lab
versions['FRESNEL_VERSION'] = 'v0.5.0'
versions['FREUD_VERSION'] = 'v0.7.0'
versions['GSD_VERSION'] = 'v1.5.1'
versions['HOOMD_VERSION'] = 'v2.2.4'
versions['SIGNAC_VERSION'] = 'v0.9.2'
versions['SIGNAC_FLOW_VERSION'] = 'v0.5.6'


def write(fname, templates, **kwargs):
    with open(fname, 'w') as f:
        for template in templates:
            f.write(template.render(**kwargs));

env = jinja2.Environment(loader=jinja2.FileSystemLoader('template'))
base_template = env.get_template('base.jinja')
openmpi_template = env.get_template('openmpi.jinja')
software_template = env.get_template('software.jinja')

write('cuda8/Dockerfile', [base_template, software_template],
      FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
      ENABLE_MPI='off',
      CC='/usr/bin/gcc',
      CXX='/usr/bin/g++',
      **versions)

write('cuda8/openmpi3.0/Dockerfile', [base_template, openmpi_template, software_template],
      FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
      OPENMPI_VERSION='3.0.0',
      OSU_MICROBENCHMARK_VERSION='5.4.1',
      ENABLE_MPI='on',
      CC='/usr/bin/gcc',
      CXX='/usr/bin/g++',
      **versions)

write('olcf-titan/Dockerfile', [base_template, software_template],
      FROM='olcf/titan:ubuntu-16.04_2018-01-18',
      ENABLE_MPI='on',
      CC='/usr/bin/gcc-4.9',
      CXX='/usr/bin/g++-4.9',
      **versions)
