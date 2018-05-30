#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '2.17.1'
versions['MPI4PY_VERSION'] = '3.0.0'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.5.0'
repo_version['freud']       = versions['FREUD_VERSION']       = 'v0.8.1'
repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.5.3'
repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.3.1'
repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v0.5.4'
repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.2'
repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v0.6.1'
repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.0.0'
repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v0.9.2'
repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.6.0'

if __name__ == '__main__':

    def write(fname, templates, **kwargs):
        with open(fname, 'w') as f:
            for template in templates:
                f.write(template.render(**kwargs));

    env = jinja2.Environment(loader=jinja2.FileSystemLoader('template'))
    base_template = env.get_template('base.jinja')
    ib_mlx_template = env.get_template('ib-mlx.jinja')
    ib_hfi1_template = env.get_template('ib-hfi1.jinja')
    openmpi_template = env.get_template('openmpi.jinja')
    mvapich2_template = env.get_template('mvapich2.jinja')
    titan_template = env.get_template('titan.jinja')
    software_template = env.get_template('software.jinja')

    write('cuda8/Dockerfile', [base_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions)

    write('cuda8/flux/Dockerfile', [base_template, ib_mlx_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='3.0',
          OPENMPI_PATCHLEVEL='0',
          OSU_MICROBENCHMARK_VERSION='5.4.1',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          **versions)

    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    write('cuda8/comet/Dockerfile', [base_template, ib_mlx_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='1.8',
          OPENMPI_PATCHLEVEL='4',
          OSU_MICROBENCHMARK_VERSION='5.4.1',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell',
          **versions)

    write('cuda8/bridges/Dockerfile', [base_template, ib_hfi1_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='1.10',
          OPENMPI_PATCHLEVEL='4',
          OSU_MICROBENCHMARK_VERSION='5.4.1',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell',
          **versions)

    write('cuda8/stampede2/Dockerfile', [base_template, ib_hfi1_template, mvapich2_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          MVAPICH_VERSION='2.3',
          MVAPICH_PATCHLEVEL='rc1',
          OSU_MICROBENCHMARK_VERSION='5.4.1',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=knl -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mno-avx512er -mavx512cd -mno-avx512pf -mno-prefetchwt1 -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mclwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=33792 -mtune=generic',
          **versions)

    write('olcf-titan/Dockerfile', [base_template, titan_template, software_template],
          FROM='olcf/titan:ubuntu-16.04_2018-01-18',
          ENABLE_MPI='on',
          MAKEJOBS=2,
          CFLAGS='-D_FORCE_INLINES',
          **versions)
