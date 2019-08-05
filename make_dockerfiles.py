#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
shas = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '3.5.2'
shas['EMBREE_SHA'] = 'a2f2adf05db1ee3fb9f3116d041b36c8d272a3d3f5156ba0e042146d641db750'

versions['OSU_MICROBENCHMARK_VERSION'] ='5.4.1'
shas['OSU_MICROBENCHMARK_SHA'] ='e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c'

versions['MPI4PY_VERSION'] = '3.0.0'
shas['MPI4PY_SHA'] = 'b457b02d85bdd9a4775a097fac5234a20397b43e073f14d9e29b6cd78c68efd7'

versions['TBB_VERSION'] = '2019_U3'
shas['TBB_SHA'] = 'b2244147bc8159cdd8f06a38afeb42f3237d3fc822555499d7ccfbd4b86f8ece'

versions['SCIPY_VERSION'] = '1.2.0'
shas['SCIPY_SHA'] = '51a2424c8ed80e60bdb9a896806e7adaf24a58253b326fbad10f80a6d06f2214'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.9.0'
shas['FRESNEL_SHA'] = '8f3d49bbb0c8410772f9d5a997b77b9546d512b8fba01ce5604dbf2b1499dd4e'

repo_version['freud']       = versions['FREUD_VERSION']       = 'v1.2.1'
shas['FREUD_SHA'] = '4234ba0304742a8a2dd70df0663c23485c9cdd415789d34a434a76c116212d2e'

repo_version['garnett']     = versions['GARNETT_VERSION']     = 'v0.4.1'
shas['GARNETT_SHA'] = '8e4860f676f92bc252d8ebc915c0ba6aeb35156f0105a685aebeb19ae54955b4'

repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.8.0'
shas['GSD_SHA'] = 'f6a99e86198a2f01e9a33b6d5eafed5ed82fa7084e1661316ac06a660e2f809d'

repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.6.0'
shas['HOOMD_SHA'] = 'f926b2d39cf58916794edbf4c619d0542a9b1e66b6c6a1b6a01b70f5617ec728'

repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v1.0.1'
shas['LIBGETAR_SHA'] = '0a438dc8336103158fc4dbb7ebcbc011279d7a8ae134824dda5946e6b9042039'

repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.5'
shas['PYTHIA_SHA'] = '5dfe1efeb7343fbfc7260dc6f05a8ee17908add288c67094d3740c7056627140'

repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v1.2.1'
shas['ROWAN_SHA'] = 'c59ad2dded288e5626db19869ed2915852734520347f7e0afd9dd08171d4541b'

repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.6.0'
shas['PLATO_SHA'] = 'd7282e2b7a8cd641e41a845f1a7075031b821440ab1ea9ad11a0dc991b86f91d'

repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v1.2.0'
shas['SIGNAC_SHA'] = '38591f2c0dcb77d28dfeb7906b2c25bfc3df39d67486ff819872ba69be4fa187'

repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.7.1'
shas['SIGNAC_FLOW_SHA'] = '970ea990d8c86143161670e7c260a66357323a55ee8a5b8d8d30fe00386a929c'

if __name__ == '__main__':

    def write(fname, templates, **kwargs):
        with open(fname, 'w') as f:
            for template in templates:
                f.write(template.render(**kwargs));

    env = jinja2.Environment(loader=jinja2.FileSystemLoader('template'))
    base_template = env.get_template('base.jinja')
    ib_mlx_template = env.get_template('ib-mlx.jinja')
    ib_hfi1_template = env.get_template('ib-hfi1.jinja')
    ib_hfi1_stampede2_template = env.get_template('ib-hfi1-stampede2.jinja')
    openmpi_template = env.get_template('openmpi.jinja')
    mvapich2_template = env.get_template('mvapich2.jinja')
    summit_template = env.get_template('summit.jinja')
    glotzerlab_software_template = env.get_template('glotzerlab-software.jinja')
    finalize_template = env.get_template('finalize.jinja')
    test_template = env.get_template('test.jinja')

    write('docker/Dockerfile', [base_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('docker/nompi/Dockerfile', [base_template, glotzerlab_software_template, finalize_template, test_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('docker/flux/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.1-devel-ubuntu16.04',
          system='flux',
          OPENMPI_VERSION='3.0',
          OPENMPI_PATCHLEVEL='0',
          OPENMPI_SHA = 'f699bff21db0125d8cccfe79518b77641cd83628725a1e1ed3e45633496a82d7',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          **versions,
          **shas)

    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'
    write('docker/comet/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          system='comet',
          OPENMPI_VERSION='1.8',
          OPENMPI_PATCHLEVEL='4',
          OPENMPI_SHA='23158d916e92c80e2924016b746a93913ba7fae9fff51bf68d5c2a0ae39a2f8a',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=30720 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security',
          **versions,
          **shas)

    write('docker/bridges/Dockerfile', [base_template, ib_hfi1_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          system='bridges',
          OPENMPI_VERSION='2.1',
          OPENMPI_PATCHLEVEL='2',
          OPENMPI_SHA='3cc5804984c5329bdf88effc44f2971ed244a29b256e0011b8deda02178dd635',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security',
          **versions,
          **shas)

    # TODO: update cflags after switching to newer compiler
    write('docker/stampede2/Dockerfile', [base_template, ib_hfi1_stampede2_template, mvapich2_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          system='stampede2',
          MVAPICH_VERSION='2.3',
          MVAPICH_PATCHLEVEL='',
          MVAPICH_SHA='01d5fb592454ddd9ecc17e91c8983b6aea0e7559aa38f410b111c8ef385b50dd',
          MVAPICH_EXTRA_OPTS='--with-device=ch3:psm --with-ch3-rank-bits=32 --enable-cxx --enable-romio --enable-fast=O3 --enable-g=dbg',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=knl -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mclwb --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=33792 -mtune=generic',
          **versions,
          **shas)

    write('script/summit/install.sh', [summit_template, glotzerlab_software_template],
          ENABLE_MPI='on',
          MAKEJOBS=20,
          CFLAGS='-mcpu=power9 -mtune=power9',
          output='script',
          system='summit',
          ENABLE_TBB='off',
          BUILD_JIT='off',
          ENABLE_MPI_CUDA='on',
          **versions,
          **shas)
