# SensorUtils

## Building

1. Install armadillo

**If you have conda:**

```bash
conda install armadillo
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
