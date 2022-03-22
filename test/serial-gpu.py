results = open('test-results-gpu.out', 'a')
results.write('** Starting serial GPU tests **\n')

try:
    # Fresnel
    #import fresnel
    #results.write('Fresnel version   : {}\n'.format(fresnel.__version__))
    #dev = fresnel.Device(mode='gpu', n=1)
    #results.write('Fresnel device    : {}\n'.format(dev))

    # HOOMD
    import hoomd
    device = hoomd.device.GPU()
    results.write('HOOMD version     : {}\n'.format(hoomd.version.version))
    results.write('HOOMD flags       : {}\n'.format(hoomd.version.compile_flags))

    results.write('** Serial GPU tests PASSED **\n\n')
except:
    results.write('** Serial GPU tests FAILED **\n\n')
    raise

