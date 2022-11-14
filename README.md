# stdexec-example

Examples of using the stdexec library for parallel computation

## Build

Use the standard CPU scheduler
```
cmake . -B build -DCMAKE_CXX_COMPILER=clang++
cmake --build build
```

Use the CUDA GPU scheduler
```
cmake . -B build -DCMAKE_CXX_COMPILER=clang++ -DCUDA_HOST_COMPILER=clang++ -DCMAKE_CUDA_COMPILER=clang++ -DSTDEXEC_EXAMPLE_USE_CUDA=ON
cmake --build build
```
