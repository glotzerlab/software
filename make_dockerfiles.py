#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
shas = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '3.12.0'
versions['OSU_MICROBENCHMARK_VERSION'] ='5.4.1'
versions['PYBIND11_VERSION'] = '2.6.2'
versions['QHULL_VERSION'] = '2020.2'
versions['MPI4PY_VERSION'] = '3.0.3'

# Summit-only dependencies
versions['TBB_VERSION'] = '2020.2'
versions['SCIPY_VERSION'] = '1.5.2'

# glotzer lab
repo_version['freud']       = versions['FREUD_VERSION']       = 'v2.5.0'
repo_version['fsph']        = versions['FSPH_VERSION']        = 'v0.2.0'
repo_version['garnett']     = versions['GARNETT_VERSION']     = 'v0.7.1'
repo_version['gsd']         = versions['GSD_VERSION']         = 'v2.4.1'
repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v1.1.0'
repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.5'
repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v1.3.0.post1'
repo_version['coxeter']     = versions['COXETER_VERSION']     = 'v0.4.0'
repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.7.0'
repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v1.6.0'
repo_version['signac-flow'] = versions['SIGNAC_FLOW_VERSION'] = 'v0.13.0'

repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.13.1'
repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.9.6'

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

    write('docker/nompi/Dockerfile', [base_template, glotzerlab_software_template, finalize_template, test_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          ENABLE_MPI='off',
          MAKEJOBS=4,
          **versions,
          **shas)

    write('docker/greatlakes/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          system='greatlakes',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='2',
          UCX_VERSION='1.6.0',
          PMIX_VERSION='2.2.3',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=sandybridge -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -maes -mpclmul -mpopcnt -mavx -msse4.2 -msse4.1 -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=20480 -mtune=sandybridge',
          **versions,
          **shas)

          ## great lakes compile flags once lighthouse is running avx512 chips
          # CFLAGS='-march=skylake-avx512 -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=25344 -mtune=skylake-avx512',


    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'
    write('docker/comet/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          system='comet',
          OPENMPI_VERSION='3.1',
          OPENMPI_PATCHLEVEL='4',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=30720 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security',
          **versions,
          **shas)

    write('docker/stampede2/Dockerfile', [base_template, ib_hfi1_stampede2_template, mvapich2_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          system='stampede2',
          MVAPICH_VERSION='2.3',
          MVAPICH_PATCHLEVEL='',
          MVAPICH_SHA='01d5fb592454ddd9ecc17e91c8983b6aea0e7559aa38f410b111c8ef385b50dd',
          MVAPICH_EXTRA_OPTS='--with-device=ch3:psm --with-ch3-rank-bits=32 --enable-cxx --enable-romio --enable-fast=O3 --enable-g=dbg',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=skylake-avx512 -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=25344 -mtune=skylake-avx512',
          **versions,
          **shas)

    write('script/summit/install.sh', [summit_template, glotzerlab_software_template],
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-mcpu=power9 -mtune=power9',
          output='script',
          system='summit',
          ENABLE_TBB='off',
          BUILD_JIT='off',
          ENABLE_MPI_CUDA='on',
          **versions,
          **shas)

    write('docker/bridges2/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:10.1-devel-ubuntu18.04',
          ubuntu_version=18,
          system='bridges2',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='5',
          UCX_VERSION='1.9.0',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=znver1 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver1',
          **versions,
          **shas)
