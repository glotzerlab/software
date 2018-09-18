try:
    import hoomd
    hoomd.context.initialize('--mode=cpu')
    assert(hoomd.comm.get_num_ranks() == 2)

    if (hoomd.comm.get_rank() == 0):
        results = open('test-results-cpu.out', 'a')
        results.write('** Starting MPI CPU tests **\n')
        results.write('HOOMD version     : {}\n'.format(hoomd.__version__))
        results.write('** MPI CPU tests PASSED **\n')
except:
    with open('test-results-cpu.out', 'a') as results:
        results.write('** Starting MPI CPU tests **\n')
        results.write('** MPI CPU tests FAILED **\n')

    raise

