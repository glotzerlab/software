if [[ $1 == "gpu" ]]; then
    ENABLE_GPU="on"
fi

cmake -B build \
      ${CMAKE_ARGS} \
      -DENABLE_MPI=on \
      -DENABLE_GPU=${ENABLE_GPU:-off} \
      -DBUILD_TESTING=off \
      -DENABLE_TBB=off \
      -DENABLE_LLVM=off \
      -DPLUGINS="" \
      -GNinja

ninja -C build
ninja -C build install
