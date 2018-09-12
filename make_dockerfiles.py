#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
shas = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '3.2.0'
shas['EMBREE_SHA'] = '7671cc37c4dc4e3da00b2b299b906b35816f058efea92701e7b89574b15e652d'

versions['OSU_MICROBENCHMARK_VERSION'] ='5.4.1'
shas['OSU_MICROBENCHMARK_SHA'] ='e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c'

versions['MPI4PY_VERSION'] = '3.0.0'
shas['MPI4PY_SHA'] = 'b457b02d85bdd9a4775a097fac5234a20397b43e073f14d9e29b6cd78c68efd7'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.6.0'
shas['FRESNEL_SHA'] = 'de1b18f87b5bcdd96844c143d6a9cf560df873a9f1f7eae8d6ff2eac5a1d2467'

repo_version['freud']       = versions['FREUD_VERSION']       = 'v0.10.0'
shas['FREUD_SHA'] = 'f0d00cf5d958b0e3b819ab09ba0433f2fb29b0cdac30879222d49cad7e460e1f'

repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.5.3'
shas['GSD_SHA'] = '10b6d37b2dadb9dc3543f4975e3722da3f3fd790df44e887b2a0306c045cf76d'

repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.3.4'
shas['HOOMD_SHA'] = '72bea429483528d38e8c8da77cc4b0fa6df6dcfd8846bbe9d7975a007c749525'

repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v0.6.1'
shas['LIBGETAR_SHA'] = '3e7e0124ba6b7c831e789e13d75313a4700fbea9b0d04ebd5c1afc87b732aa24'

repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.2'
shas['PYTHIA_SHA'] = '38992fd2f10368681b3151b2cba999e9fa413f811882d0900c3e0ee5cb25e400'

repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v1.1.0'
shas['ROWAN_SHA'] = '43a7a29a95409acb458184647081c0e6e178943018db58f993e771b9d48602c7'

repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.1.0'
shas['PLATO_SHA'] = 'ad1b213f28990e34677bcd6449f17852420a0c6ed8b807ec842b6a0b0433a8ad'

repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v0.9.3'
shas['SIGNAC_SHA'] = 'b54f977d347180d6f7a737d84a63bcc1140d7e6f4fe681f8b8315db6fe32d7ab'

repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.6.3'
shas['SIGNAC_FLOW_SHA'] = '0a1ff4d052ea1e02079b60c0a5710df28e3fa8286649ccc030d032ec99901dba'


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
          **versions,
          **shas)

    write('cuda8/flux/Dockerfile', [base_template, ib_mlx_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='3.0',
          OPENMPI_PATCHLEVEL='0',
          OPENMPI_SHA = 'f699bff21db0125d8cccfe79518b77641cd83628725a1e1ed3e45633496a82d7',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          **versions,
          **shas)

    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    write('cuda8/comet/Dockerfile', [base_template, ib_mlx_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='1.8',
          OPENMPI_PATCHLEVEL='4',
          OPENMPI_SHA='23158d916e92c80e2924016b746a93913ba7fae9fff51bf68d5c2a0ae39a2f8a',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell',
          **versions,
          **shas)

    write('cuda8/bridges/Dockerfile', [base_template, ib_hfi1_template, openmpi_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='1.10',
          OPENMPI_PATCHLEVEL='4',
          OPENMPI_SHA='fb3c0c4c77896185013b6091b306d29ba592eb40d8395533da5c8bc300d922db',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell',
          **versions,
          **shas)

    write('cuda8/stampede2/Dockerfile', [base_template, ib_hfi1_template, mvapich2_template, software_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          MVAPICH_VERSION='2.3',
          MVAPICH_PATCHLEVEL='rc1',
          MVAPICH_SHA='607d309c864a6d57f5fa78fe6dd02368919736b8be0f4ddb938aba303ef9c45c',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=knl -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mno-avx512er -mavx512cd -mno-avx512pf -mno-prefetchwt1 -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mclwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=33792 -mtune=generic',
          **versions,
          **shas)

    write('olcf-titan/Dockerfile', [base_template, titan_template, software_template],
          FROM='olcf/titan:ubuntu-16.04_2018-01-18',
          ENABLE_MPI='on',
          MAKEJOBS=2,
          CFLAGS='-D_FORCE_INLINES',
          **versions,
          **shas)
