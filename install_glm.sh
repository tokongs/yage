#!/bin/sh
wget https://github.com/g-truc/glm/archive/0.9.9.2.tar.gz
tar -xzvf 0.9.9.2.tar.gz
cd glm-0.9.9.2
cmake -DGLM_TEST_ENABLE=OFF .
make && sudo make install