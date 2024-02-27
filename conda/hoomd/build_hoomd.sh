if [[ $1 == "gpu" ]]; then
    ENABLE_GPU="on"
fi

cmake -B build \
      ${CMAKE_ARGS} \
      -DENABLE_MPI=on \
      -DENABLE_GPU=${ENABLE_GPU:-off} \
      -DHOOMD_GPU_PLATFORM=$2 \
      -DBUILD_TESTING=off \
      -DENABLE_TBB=off \
      -DENABLE_LLVM=off \
      -DPLUGINS="" \
      -DCMAKE_CXX_FLAGS=-march=native -DCMAKE_C_FLAGS=-march=native \
      -GNinja

ninja -C build -j $SLURM_CPUS_PER_TASK
ninja -C build install -j $SLURM_CPUS_PER_TASK
