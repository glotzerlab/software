try:
    import hoomd
    dev = hoomd.device.CPU
    assert(dev.communicator.num_ranks == 2)

    if (dev.communicator.rank == 0):
        results = open('test-results-cpu.out', 'a')
        results.write('** Starting MPI CPU tests **\n')
        results.write('HOOMD version     : {}\n'.format(hoomd.__version__))
        results.write('** MPI CPU tests PASSED **\n')
except:
    with open('test-results-cpu.out', 'a') as results:
        results.write('** Starting MPI CPU tests **\n')
        results.write('** MPI CPU tests FAILED **\n')

    raise

