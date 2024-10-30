# install geos
https://libgeos.org/usage/download/
```
tar xvf geos-3.10.6.tar.bz2
cd geos-3.10.6
./configure
make 
sudo make install 
```
# install proj
## 1
https://download.osgeo.org/proj/ 
```
tar xvf proj-9.5.0.tar.gz
cd proj-9.5.0/
sudo apt-get install sqlite3 libsqlite3-dev libtiff-dev libcurl4-openssl-dev
mkdir build && cd build
make
sudo make install
```
## 2
sudo apt-get install sqlite3 libsqlite3-dev libtiff-dev libcurl4-openssl-dev
sudo apt install libproj-dev proj-bin proj-data
# Question
## 1

# query utm zone
https://blog.csdn.net/d7986/article/details/127600579
http://www.jaworski.ca/utmzones.htm#utm%20zones

# reference
https://bbs.huaweicloud.com/blogs/207010
https://blog.csdn.net/qq_41204464/article/details/104543636


- UTM to WGS84 online
https://www.engineeringtoolbox.com/utm-latitude-longitude-d_1370.html
- WGS84 to UTM online
https://www.lddgo.net/coordinate/projection
- query latitude-longitude
https://tool.lu/coordinate/


源代码中添加以下行，以定义这个宏:(确保这段代码在包含 proj_api.h 之前)
#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H

