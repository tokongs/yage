#!/bin/sh
wget https://github.com/gabime/spdlog/archive/v1.1.0.tar.gz
tar -xzvf v1.1.0.tar.gz
cd spdlog-1.1.0
cmake -DSPDLOG_BUILD_EXAMPLES=OFF -DSPDLOG_BUILD_BENCH=OFF -DSPDLOG_BUILD_TESTING=OFF .
make && sudo make install