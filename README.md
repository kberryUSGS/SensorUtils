# SensorUtils
[![Build Status](https://travis-ci.org/USGS-Astrogeology/SensorUtils.svg?branch=master)](https://travis-ci.org/USGS-Astrogeology/SensorUtils)
[![Coverage Status](https://coveralls.io/repos/github/USGS-Astrogeology/SensorUtils/badge.svg?branch=master)](https://coveralls.io/github/USGS-Astrogeology/SensorUtils?branch=master)

## Building

1. Install armadillo

**If you have conda:**

```bash
conda install armadillo -c conda-forge
```
  > *Make sure your environment is activated if you have a dedicated conda environment.*

**Otherwise:**
```
wget https://sourceforge.net/projects/arma/files/armadillo-8.600.0.tar.xz && \
tar -xf armadillo-8.600.0.tar.xz && \
cd armadillo-8.600.0 && \
cmake -DDETECT_HDF5=false . -DCMAKE_INSTALL_PREFIX=/usr/local && \
sudo make install 
```

2. `mkdir build && cd build`
3. `cmake .. && cmake --build .`
4. `ctest`
