import sys
results = sys.stdout

try:
    import hoomd
    dev = hoomd.device.CPU()
    assert(dev.communicator.num_ranks == 2)

    if (dev.communicator.rank == 0):
        results.write('** Starting MPI CPU tests **\n')
        results.write('HOOMD version     : {}\n'.format(hoomd.version.version))
        results.write('** MPI CPU tests PASSED **\n')
except:
    results.write('** Starting MPI CPU tests **\n')
    results.write('** MPI CPU tests FAILED **\n')

    raise

