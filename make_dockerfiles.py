#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '2.17.1'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.5.0'
repo_version['freud']       = versions['FREUD_VERSION']       = 'v0.7.0'
repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.5.2'
repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.2.4'
repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v0.9.2'
repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.5.6'

if __name__ == '__main__':

    def write(fname, templates, **kwargs):
        with open(fname, 'w') as f:
            for template in templates:
                f.write(template.render(**kwargs));

    env = jinja2.Environment(loader=jinja2.FileSystemLoader('template'))
    base_template = env.get_template('base.jinja')
    openmpi_template = env.get_template('openmpi.jinja')
    titan_template = env.get_template('titan.jinja')
    software_template = env.get_template('software.jinja')

    write('cuda8/Dockerfile', [base_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions)

    write('cuda8/openmpi3.0/Dockerfile', [base_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='3.0.0',
          OSU_MICROBENCHMARK_VERSION='5.4.1',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          **versions)

    write('olcf-titan/Dockerfile', [base_template, titan_template, software_template],
          FROM='olcf/titan:ubuntu-16.04_2018-01-18',
          ENABLE_MPI='on',
          MAKEJOBS=2,
          **versions)
