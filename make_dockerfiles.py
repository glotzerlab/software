#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
shas = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '3.6.1'
shas['EMBREE_SHA'] = '76e9c619e11c2baace2935b14f1d6ee8ff085fd12c72b7d62d6fcb9a4ffaca3e'

versions['OSU_MICROBENCHMARK_VERSION'] ='5.4.1'
shas['OSU_MICROBENCHMARK_SHA'] ='e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c'

versions['MPI4PY_VERSION'] = '3.0.2'
versions['PYBIND11_VERSION'] = '2.3.0'
versions['QHULL_VERSION'] = '2019.1'
versions['UCX_VERSION'] = '1.6.0'
versions['PMIX_VERSION'] = '2.2.3'

# Summit-only dependencies
versions['TBB_VERSION'] = '2019_U8'
shas['TBB_SHA'] = '7b1fd8caea14be72ae4175896510bf99c809cd7031306a1917565e6de7382fba'

versions['SCIPY_VERSION'] = '1.3.1'
shas['SCIPY_SHA'] = '2643cfb46d97b7797d1dbdb6f3c23fe3402904e3c90e6facfe6a9b98d808c1b5'

# ubuntu 16 only dependencies
versions['CMAKE_VERSION'] = '3.15.3'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.10.1'
shas['FRESNEL_SHA'] = '2ba1f85f3599f349a7a20d5dcc19a84ea43bb8dd707cad22bbf9f4767ca4b955'

repo_version['freud']       = versions['FREUD_VERSION']       = 'v1.2.2'
shas['FREUD_SHA'] = '53e58f157be07e6fcf90431c19188874c5cba9ac48bffc19f631930d176b6c9d'

repo_version['garnett']     = versions['GARNETT_VERSION']     = 'v0.5.0'
shas['GARNETT_SHA'] = '9be24f8332757c00945849784316b06a2db58f06569a988bfb88c0af6455df1f'

repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.9.3'
shas['GSD_SHA'] = '89db85565b87d7a167ecf01881382ec4bc7280f07fe0295c2cf74af5db949231'

repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.7.0'
shas['HOOMD_SHA'] = 'f884583b4d16bc630e177aefc198fb8361e644f6cad1b0c0474e840f00a4e4e1'

repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v1.0.1'
shas['LIBGETAR_SHA'] = '0a438dc8336103158fc4dbb7ebcbc011279d7a8ae134824dda5946e6b9042039'

repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.5'
shas['PYTHIA_SHA'] = '5dfe1efeb7343fbfc7260dc6f05a8ee17908add288c67094d3740c7056627140'

repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v1.2.2'
shas['ROWAN_SHA'] = '88ed2c0003543d3154374f741a04fcb21cce32180e7b29152dc93c4c887e0c51'

repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.7.0'
shas['PLATO_SHA'] = '8268ab6982f9135d1f7788309804eb15a1e98ef1d2f6d959733a3e23a1595def'

repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v1.2.0'
shas['SIGNAC_SHA'] = '38591f2c0dcb77d28dfeb7906b2c25bfc3df39d67486ff819872ba69be4fa187'

repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.8.0'
shas['SIGNAC_FLOW_SHA'] = 'ae933964e2786f22963f70ff147a2cbd152e7e32c903ba550154b91db890451b'

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
          ubuntu_version=16,
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('docker/nompi/Dockerfile', [base_template, glotzerlab_software_template, finalize_template, test_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          ubuntu_version=16,
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('docker/flux/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.1-devel-ubuntu16.04',
          ubuntu_version=16,
          system='flux',
          OPENMPI_VERSION='3.0',
          OPENMPI_PATCHLEVEL='0',
          OPENMPI_SHA = 'f699bff21db0125d8cccfe79518b77641cd83628725a1e1ed3e45633496a82d7',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('docker/greatlakes/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          system='greatlakes',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='1',
          OPENMPI_SHA = 'cce7b6d20522849301727f81282201d609553103ac0b09162cf28d102efb9709',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=skylake-avx512 -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=25344 -mtune=skylake-avx512',
          **versions,
          **shas)

    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'
    write('docker/comet/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:9.2-devel-ubuntu16.04',
          ubuntu_version=16,
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
          ubuntu_version=16,
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
          ubuntu_version=16,
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
