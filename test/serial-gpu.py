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
    context = hoomd.context.initialize('--mode=gpu')
    assert(context.on_gpu())
    results.write('HOOMD version     : {}\n'.format(hoomd.__version__))
    results.write('HOOMD flags       : {}\n'.format(hoomd._hoomd.hoomd_compile_flags()))

    results.write('** Serial GPU tests PASSED **\n\n')
except:
    results.write('** Serial GPU tests FAILED **\n\n')
    raise

