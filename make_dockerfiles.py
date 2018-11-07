#!/usr/bin/env python

import jinja2

# repository name (change this if you want to modify and rebuild these in your own repository)
base_repository = 'glotzerlab/base'

# software versions
versions = {}
shas = {}
repo_version = {}

# dependencies
versions['EMBREE_VERSION'] = '3.2.1'
shas['EMBREE_SHA'] = '4bc1801d7a358dfd71e1fb6d46c9401397923980c11e7801f26d5b3f1aed4506'

versions['OSU_MICROBENCHMARK_VERSION'] ='5.4.1'
shas['OSU_MICROBENCHMARK_SHA'] ='e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c'

versions['MPI4PY_VERSION'] = '3.0.0'
shas['MPI4PY_SHA'] = 'b457b02d85bdd9a4775a097fac5234a20397b43e073f14d9e29b6cd78c68efd7'

# glotzer lab
repo_version['fresnel']     = versions['FRESNEL_VERSION']     = 'v0.6.0'
shas['FRESNEL_SHA'] = 'de1b18f87b5bcdd96844c143d6a9cf560df873a9f1f7eae8d6ff2eac5a1d2467'

repo_version['freud']       = versions['FREUD_VERSION']       = 'v0.11.3'
shas['FREUD_SHA'] = 'fc803bd20a43b998cc660011ac408c51750427bebe5e26131aef9f9446fe53ec'

repo_version['gsd']         = versions['GSD_VERSION']         = 'v1.5.4'
shas['GSD_SHA'] = '09b09f1316c809dae96b1a02972673ef928eb549fcc1cae484265590a5b4acff'

repo_version['hoomd-blue']  = versions['HOOMD_VERSION']       = 'v2.4.0'
shas['HOOMD_SHA'] = '052fffd0ebcc43a86fa530ff54054ae183dcd5c404957e41f7d83f633e39569a'

repo_version['libgetar']    = versions['LIBGETAR_VERSION']    = 'v0.7.0'
shas['LIBGETAR_SHA'] = '2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7'

repo_version['pythia']      = versions['PYTHIA_VERSION']      = 'v0.2.3'
shas['PYTHIA_SHA'] = '6fa74e608024d8126657d788016ec3a4112a7c17b8deda86e51a2905c47f5ed5'

repo_version['rowan']       = versions['ROWAN_VERSION']       = 'v1.1.6'
shas['ROWAN_SHA'] = '14627245b95b88e3d4358e6d9df0501eec1bcb892c71ba5829904d4728ecb9f8'

repo_version['plato']       = versions['PLATO_VERSION']       = 'v1.2.0'
shas['PLATO_SHA'] = 'fdd574a5ed6956bb68430de13991938d4765697736c857822c8c1addf5edd07d'

repo_version['signac']      = versions['SIGNAC_VERSION']      = 'v0.9.4'
shas['SIGNAC_SHA'] = '8a3c5b46d079decb9fa2d5d85628c2bd31057a44e945beba930d3b624dcb8437'

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
    glotzerlab_software_template = env.get_template('glotzerlab-software.jinja')
    glotzerlab_software_mpi_template = env.get_template('glotzerlab-software-mpi.jinja')
    finalize_template = env.get_template('finalize.jinja')

    write('cuda8/Dockerfile', [base_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('cuda8/nompi/Dockerfile', [base_template, glotzerlab_software_template, glotzerlab_software_mpi_template, finalize_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          ENABLE_MPI='off',
          MAKEJOBS=10,
          **versions,
          **shas)

    write('cuda8/flux/Dockerfile', [base_template, glotzerlab_software_template, ib_mlx_template, openmpi_template, glotzerlab_software_mpi_template, finalize_template],
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
    # gcc -'###' -E - -march=native 2>&1 | sed -r '/cc1/!d;s/(")|(^.* - )|( -mno-[^\ ]+)//g'
    write('cuda8/comet/Dockerfile', [base_template, glotzerlab_software_template, ib_mlx_template, openmpi_template, glotzerlab_software_mpi_template, finalize_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='1.8',
          OPENMPI_PATCHLEVEL='4',
          OPENMPI_SHA='23158d916e92c80e2924016b746a93913ba7fae9fff51bf68d5c2a0ae39a2f8a',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=30720 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security',
          **versions,
          **shas)

    write('cuda8/bridges/Dockerfile', [base_template, glotzerlab_software_template, ib_hfi1_template, openmpi_template, glotzerlab_software_mpi_template, finalize_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          OPENMPI_VERSION='2.1',
          OPENMPI_PATCHLEVEL='2',
          OPENMPI_SHA='3cc5804984c5329bdf88effc44f2971ed244a29b256e0011b8deda02178dd635',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security',
          **versions,
          **shas)

    # TODO: update cflags after switching to newer compiler
    write('cuda8/stampede2/Dockerfile', [base_template, glotzerlab_software_template, ib_hfi1_template, mvapich2_template, glotzerlab_software_mpi_template, finalize_template],
          FROM='nvidia/cuda:8.0-devel-ubuntu16.04',
          MVAPICH_VERSION='2.3',
          MVAPICH_PATCHLEVEL='',
          MVAPICH_SHA='01d5fb592454ddd9ecc17e91c8983b6aea0e7559aa38f410b111c8ef385b50dd',
          ENABLE_MPI='on',
          MAKEJOBS=10,
          CFLAGS='-march=knl -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrtm -mhle -mrdrnd -mf16c -mfsgsbase -mrdseed -mprfchw -madx -mfxsr -mxsave -mxsaveopt -mavx512f -mavx512cd -mclflushopt -mxsavec -mxsaves -mavx512dq -mavx512bw -mclwb --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=33792 -mtune=generic',
          **versions,
          **shas)

    write('olcf-titan/Dockerfile', [base_template, titan_template, glotzerlab_software_template, glotzerlab_software_mpi_template, finalize_template],
          FROM='olcf/titan:ubuntu-16.04_2018-01-18',
          ENABLE_MPI='on',
          MAKEJOBS=2,
          CFLAGS='-D_FORCE_INLINES',
          **versions,
          **shas)
