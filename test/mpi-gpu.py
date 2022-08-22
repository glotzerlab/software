import sys
results = sys.stdout

try:
    import hoomd
    dev = hoomd.device.GPU()
    assert(dev.communicator.num_ranks == 2)

    if (dev.communicator.rank == 0):
        results.write('** Starting MPI GPU tests **\n')
        results.write('HOOMD version     : {}\n'.format(hoomd.version.version))
        results.write('** MPI GPU tests PASSED **\n')
except:
    results.write('** Starting MPI GPU tests **\n')
    results.write('** MPI GPU tests FAILED **\n')

    raise
