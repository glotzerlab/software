if [[ $1 == "gpu" ]]; then
    ENABLE_GPU="on"
fi

# Use CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE to keep absolute links to mpi and other modules
cmake -B build \
      ${CMAKE_ARGS} \
      -DBUILD_MPCD=on \
      -DENABLE_MPI=on \
      -DENABLE_GPU=${ENABLE_GPU:-off} \
      -DHOOMD_GPU_PLATFORM=$2 \
      -DBUILD_TESTING=off \
      -DENABLE_TBB=off \
      -DENABLE_LLVM=off \
      -DPLUGINS="" \
      -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE \
      -DCMAKE_CXX_FLAGS=-march=native -DCMAKE_C_FLAGS=-march=native \
      -GNinja

ninja -C build -j $SLURM_CPUS_PER_TASK
ninja -C build install -j $SLURM_CPUS_PER_TASK
