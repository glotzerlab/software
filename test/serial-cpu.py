results = open('test-results-cpu.out', 'a')
results.write('** Starting serial CPU tests **\n')

try:
    # Fresnel
    import fresnel
    results.write('Fresnel version   : {}\n'.format(fresnel.__version__))
    dev = fresnel.Device(mode='cpu')
    results.write('Fresnel device    : {}\n'.format(dev))

    # Freud
    import freud
    results.write('Freud version     : {}\n'.format(freud.__version__))

    # garnett
    # import garnett
    # results.write('garnett version       : {}\n'.format(garnett.__version__))

    # GSD
    import gsd
    results.write('GSD version       : {}\n'.format(gsd.__version__))

    # HOOMD
    import hoomd
    device = hoomd.device.CPU()
    results.write('HOOMD version     : {}\n'.format(hoomd.version.version))
    results.write('HOOMD flags       : {}\n'.format(hoomd.version.compile_flags))

    # libgetar
    import gtar
    results.write('libgetar version  : {}\n'.format(gtar.__version__))

    # pythia
    import pythia
    results.write('pythia version    : {}\n'.format(pythia.__version__))

    # libgetar
    import plato
    results.write('plato version     : {}\n'.format(plato.__version__))

    # rowan
    import rowan
    results.write('rowan version     : {}\n'.format(rowan.__version__))

    # signac
    import signac
    results.write('signac version    : {}\n'.format(signac.__version__))

    # signac-flow
    import flow
    results.write('flow version      : {}\n'.format(flow.__version__))

    results.write('\n')

    # h5py
    import h5py
    results.write('h5py version      : {}\n'.format(h5py.__version__))

    # matplotlib
    import matplotlib
    results.write('matplotlib version: {}\n'.format(matplotlib.__version__))

    # numpy
    import numpy
    results.write('numpy version     : {}\n'.format(matplotlib.__version__))

    # pandas
    import pandas
    results.write('pandas version    : {}\n'.format(matplotlib.__version__))

    # pillow
    import PIL
    results.write('pillow version    : {}\n'.format(PIL.__version__))

    # scipy
    import scipy
    results.write('scipy version     : {}\n'.format(scipy.__version__))

    # sklearn
    import sklearn
    results.write('sklearn version   : {}\n'.format(sklearn.__version__))

    # pyyaml
    import yaml
    results.write('pyyaml version    : {}\n'.format(yaml.__version__))

    results.write('** Serial CPU tests PASSED **\n\n')
except:
    results.write('** Serial CPU tests FAILED **\n\n')
    raise

