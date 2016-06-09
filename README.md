# GREMLINS
GREMLINS - GeREnciador de Memória com LIsta eNcadeada Simples (Memory Manager with Simple Linked List)

## Author
The project where developed by:

 Johnnylee Bryan Marques da Rocha - [GitHub](https://github.com/kfjohnny2)
 
 Pedro Arthur Medeiros Fernandes - [GitHub](https://github.com/pedroarthur-mf).

## About
Is a memory requirement system that will take reserved block of memory and do some manipulations. Small blocks can be created by client to allocate inside the bigger block.

## Functionality
There is a class called "SLPool" for the implementation of the methods from the abstract class "StoragePool".

### These methods are:

```cpp
void *Allocate ( std::size_t ) // Used to insert some bytes of memory inside the bigger block;

void Free( void * ) // Used to liberate required bytes of memory from the bigger block;
```


## How to Compile
There a two types of test, the timing test. The first: will use the method StoragePoolTest, that test the alocation of memory using the StoragePool and calculating the time of the Event
- For this test type the following command on terminal inside de "GREMLINS" folder:
```shell
g++ -Wall -std=c++11 -I include/ src/drive_gremlins.cpp -o bin/gremlins

./bin/gremlins
```

The second: Will make a series of manipulations using normal Allocate, Best-Fit Allocate and Free
- Following the same instruction above, type:
```shell
g++ -Wall -std=c++11 -I include/ src/drive_gremlins2.cpp -o bin/gremlins

./bin/gremlins
```
