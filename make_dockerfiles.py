#!/usr/bin/env python

import jinja2
import yaml
import multiprocessing

# software versions
versions = {}

# load package versions
with open('packages.yml', 'r') as f:
    packages = yaml.safe_load(f)

for name, p in packages.items():
    versions[f'{name.upper()}_VERSION'] = p['version']

if __name__ == '__main__':

    def write(fname, templates, **kwargs):
        with open(fname, 'w') as f:
            for template in templates:
                f.write(template.render(**kwargs))

    env = jinja2.Environment(loader=jinja2.FileSystemLoader('template'))
    base_template = env.get_template('base.jinja')
    crusher_template = env.get_template('crusher.jinja')
    frontier_template = env.get_template('frontier.jinja')
    ib_mlx_template = env.get_template('ib-mlx.jinja')
    openmpi_template = env.get_template('openmpi.jinja')
    pmix_template = env.get_template('pmix.jinja')
    mvapich2_template = env.get_template('mvapich2.jinja')
    summit_template = env.get_template('summit.jinja')
    ucx_template = env.get_template('ucx.jinja')
    glotzerlab_software_template = env.get_template('glotzerlab-software.jinja')
    finalize_template = env.get_template('finalize.jinja')
    test_template = env.get_template('test.jinja')

    write('docker/nompi/Dockerfile', [base_template, glotzerlab_software_template, test_template, finalize_template],
          FROM='nvidia/cuda:11.1.1-devel-ubuntu20.04',
          ENABLE_MPI='off',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CUDA_VERSION='11.1',
          **versions)

    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'

    write('docker/greatlakes/Dockerfile', [base_template,
                                           ib_mlx_template,
                                           pmix_template,
                                           ucx_template,
                                           openmpi_template,
                                           glotzerlab_software_template,
                                           finalize_template],
          FROM='nvidia/cuda:11.6.2-devel-ubuntu20.04',
          system='greatlakes',
          CUDA_VERSION='11.6',
          OPENMPI_VERSION='4.1',
          OPENMPI_PATCHLEVEL='4',
          UCX_VERSION='1.12.0',
          PMIX_VERSION='4.1.2',
          ENABLE_MPI='on',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CFLAGS='-march=skylake-avx512 -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=25344 -mtune=skylake-avx512',
          **versions)

    write('docker/delta/Dockerfile', [base_template,
                                      ib_mlx_template,
                                      pmix_template,
                                      ucx_template,
                                      openmpi_template,
                                      glotzerlab_software_template,
                                      finalize_template],
          FROM='nvidia/cuda:11.6.2-devel-ubuntu20.04',
          system='delta',
          CUDA_VERSION='11.6',
          OPENMPI_VERSION='4.1',
          OPENMPI_PATCHLEVEL='2',
          UCX_VERSION='1.11.2',
          PMIX_VERSION='3.2.3',
          LIBFABRIC_VERSION='1.13.2',
          ENABLE_MPI='on',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CFLAGS='-march=znver2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mwbnoinvd -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver2',
          **versions)

    write('script/summit/install.sh', [summit_template, glotzerlab_software_template],
          ENABLE_MPI='on',
          MAKEJOBS=8,
          CFLAGS='-mcpu=power9 -mtune=power9',
          output='script',
          system='summit',
          ENABLE_TBB='off',
          **versions)

    write('script/crusher/install.sh', [crusher_template, glotzerlab_software_template],
          MAKEJOBS=32,
          CFLAGS='-march=native',
          output='script',
          system='crusher',
          ENABLE_MPI='on',
          ENABLE_TBB='off',
          ENABLE_LLVM='off',
          HOOMD_GPU_PLATFORM='HIP',
          **versions)

    write('script/frontier/install.sh', [frontier_template, glotzerlab_software_template],
          MAKEJOBS=32,
          CFLAGS='-march=native',
          output='script',
          system='frontier',
          ENABLE_MPI='on',
          ENABLE_TBB='off',
          ENABLE_LLVM='off',
          HOOMD_GPU_PLATFORM='HIP',
          **versions)

    write('docker/bridges2/Dockerfile', [base_template,
                                         ib_mlx_template,
                                         ucx_template,
                                         openmpi_template,
                                         glotzerlab_software_template,
                                         finalize_template],
          FROM='nvidia/cuda:11.1.1-devel-ubuntu20.04',
          system='bridges2',
          CUDA_VERSION='11.1',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='5',
          UCX_VERSION='1.9.0',
          ENABLE_MPI='on',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CFLAGS='-march=znver2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mwbnoinvd -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver2 -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection',
          **versions)

    write('docker/expanse/Dockerfile', [base_template,
                                        ib_mlx_template,
                                        pmix_template,
                                        ucx_template,
                                        openmpi_template,
                                        glotzerlab_software_template,
                                        finalize_template],
          FROM='nvidia/cuda:11.1.1-devel-ubuntu20.04',
          system='expanse',
          CUDA_VERSION='11.1',
          OPENMPI_VERSION='4.1',
          OPENMPI_PATCHLEVEL='1',
          PMIX_VERSION='4.1.2',
          UCX_VERSION='1.10.1',
          ENABLE_MPI='on',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CFLAGS='-march=znver2 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mwbnoinvd -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver2',
          **versions)

    write('docker/expanse-gpu/Dockerfile', [base_template,
                                            ib_mlx_template,
                                            ucx_template,
                                            openmpi_template,
                                            glotzerlab_software_template,
                                            finalize_template],
          FROM='nvidia/cuda:11.1.1-devel-ubuntu20.04',
          system='expanse-gpu',
          CUDA_VERSION='11.1',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='4',
          UCX_VERSION='1.8.0',
          ENABLE_MPI='on',
          MAKEJOBS=multiprocessing.cpu_count()+2,
          CFLAGS='-march=knl -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=28160 -mtune=generic',
          **versions)
