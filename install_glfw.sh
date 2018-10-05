#!/bin/sh
wget https://github.com/glfw/glfw/archive/3.2.1.tar.gz
sudo apt-get install xorg-dev -y
tar -xzvf 3.2.1.tar.gz
cd glfw-3.2.1
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_VULKAN_STATIC=OFF .
make && sudo make install