#!/usr/bin/env python

import jinja2
import yaml

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
    ib_mlx_template = env.get_template('ib-mlx.jinja')
    ib_hfi1_template = env.get_template('ib-hfi1.jinja')
    openmpi_template = env.get_template('openmpi.jinja')
    mvapich2_template = env.get_template('mvapich2.jinja')
    summit_template = env.get_template('summit.jinja')
    glotzerlab_software_template = env.get_template('glotzerlab-software.jinja')
    finalize_template = env.get_template('finalize.jinja')
    test_template = env.get_template('test.jinja')

    write('docker/nompi/Dockerfile', [base_template, glotzerlab_software_template, finalize_template, test_template],
          FROM='nvidia/cuda:11.0.3-devel-ubuntu20.04',
          ENABLE_MPI='off',
          MAKEJOBS=4,
          **versions)

    write('docker/greatlakes/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:11.4.2-devel-ubuntu20.04',
          system='greatlakes',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='2',
          UCX_VERSION='1.6.0',
          PMIX_VERSION='2.2.3',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=sandybridge -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -maes -mpclmul -mpopcnt -mavx -msse4.2 -msse4.1 -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=20480 -mtune=sandybridge',
          **versions)

          ## great lakes compile flags once lighthouse is running avx512 chips
          # CFLAGS='-march=skylake-avx512 -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mavx512vl -mclwb -mpku --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=25344 -mtune=skylake-avx512',


    # see https://stackoverflow.com/questions/5470257/how-to-see-which-flags-march-native-will-activate
    # for information on obtaining CFLAGS settings for specific machines
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'
    write('script/summit/install.sh', [summit_template, glotzerlab_software_template],
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-mcpu=power9 -mtune=power9',
          output='script',
          system='summit',
          ENABLE_TBB='off',
          **versions)

    write('docker/bridges2/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:11.0.3-devel-ubuntu20.04',
          system='bridges2',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='5',
          UCX_VERSION='1.9.0',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=znver1 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver1',
          **versions)

    write('docker/expanse/Dockerfile', [base_template, ib_mlx_template, openmpi_template, glotzerlab_software_template, finalize_template],
          FROM='nvidia/cuda:11.1.1-devel-ubuntu20.04',
          system='expanse',
          OPENMPI_VERSION='4.0',
          OPENMPI_PATCHLEVEL='4',
          UCX_VERSION='1.8.1',
          ENABLE_MPI='on',
          MAKEJOBS=4,
          CFLAGS='-march=znver1 -mmmx -msse -msse2 -msse3 -mssse3 -msse4a -mcx16 -msahf -mmovbe -maes -msha -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mclflushopt -mxsavec -mxsaves -mclwb -mmwaitx -mclzero -mrdpid --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=512 -mtune=znver1',
          **versions)
