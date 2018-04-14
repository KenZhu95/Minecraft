Name: Weiyu Zhu
UT EID: wz4245

To build, use the following commands:

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make minecraft

excutable file will be "build/bin/minecraft"

Something might be not so correct:
The cylinder will not intersect or fall through into any cube, but sometimes it might be unavailable to walk while it seems should have more space. Mouse control might not follow Minecraft. Jump will make the virtual character to jump as high as 2, suppose 1*1*1 cubic units, and then fall.

Texture of each cube is very similar, with minor difference which can be detected if watching carefully.

For extra credits:

1. On the mountain top, several blocks(small walls) are there, with brown color. And at the bottom of the scene, there is water there. So totally five types of cubes.

2. Pick and place cubes. Toggle "P" for placing and "Y" for picking up cubes. Toggle keyboard keys 1,2,3,4,5 will switch the type of cube to place. Default type is dirt. Can only pick up or place cubes at the close front of eye. Some errors: these placed or picked cubes are not considered for character cylinder intersection detection. 

Two late days used.