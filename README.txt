Name: Weiyu Zhu
UT EID: wz4245

To build, use the following commands:

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8

excutable file will be "build/bin/menger"

The saved file "geometry.obj" should be saved in the folder where the executable file is executed, e.g. "bin".

The light is a little brighter than the reference solution. We can see some lines from the cubes now.