### 编译
```shell
g++ -std=c++17 -o trpool trpool.cpp -pthread
```
注：需要g++6.x以上，g++5.x不支持shared_mutex。

### 运行结果
```
./trpool
id : 2
id : 4
id : 10
id : 6
id : 12
id : 8
id : 14
id : 1
id : 16
id : 5
id : 18
id : 3
id : 20
id : 7
id : 9
id : 11
id : 13
id : 15
id : 17
id : 19
```
