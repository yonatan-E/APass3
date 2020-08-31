# Assignment 3 - cache manager
## Overview
In this project we wrote a program which supports different kinds of operations, and uses cache management to enable faster calculations based on calculations which have been previously made.

## About the Cache Manager
To achieve faster calculations based on calculations which have been previously made, we implemented a cache manager module that manages the calculations and saves the five most relevant results, so no uneccesary calculations are made.
The cache saves the files in a folder named *cache*. That folder contains files which holds the recent relevant results.
That folder also saves the file *info.txt*, which contains meta data about the files, and will hold it through the different runs of the program. The *info.txt* file contains the ID's of all of the files in the *cache* folder, and will hold information about the relevance of each file. The relevance of each file will be according to the LRU algorithm, which works actually like a priority queue:  
If a result is not exist on the cache, it will be inserted to the end of the queue, and if the result is already exist on the cache, its place will be changed to the end of the queue. If the queue is full (the cache is full), popping the result which is placed at the start of the queue.  
**About the way the result are saved in the cache**: Every operation has a *hashCode*, which is designed in a very specific way, according to the operation, and is calculated using the *crc32* algorithm.  
The cache saves an operation by a *hashCode* and a *result file*, in a way that the name of the result file is the hashCode of the operation, to make it more comfortable. When a new operation is added to the cache, we can easily check if the operation is already exist in the cache, by just calculating the *hashCode* of the new operation and compare it with all of the *hashCodes* in the cache. That thing allows us to get the result of an operation in O(1) time, if the operation is already exist in the cache.  
This hashing cache technique is very safe, because the chance that there will be two different operations with the same *hashCode* is almost zero, due of the specific way that the hash is designed and calculated in which promises us that collisions are almost not possible, and due to the fact that the number of possible *hashCodes* that can be created that way is **2^32**, while the maximun capacity of the cache is only **five**.

## About the Design
We designed the project using the **abstract factory** design pattern. The objects that are handeled are *Operations*, objects of a class implementing the 
*Operation* interface.

An *operation* is a command, for example ```ex3.out matrix multiply matrix1.txt matrix2.txt mult_result.txt```, written into an object. The object contains
the input/s, and the hash code of the input. in that way, we can compare between operations using the hash codes, and calculating the result only if neccesary.
The *OperationFactory* abstract factory is the base factory class, which is implemented by all of the operation classes implementing the 
*Operation* interface. Each of these classes has a ```CreateOperation``` method, which returns a new *operation* object of the class type.

The code designed this way makes the cache management in the main function simple and readble.
for each caculation command, a new suitable *operation* object is created, and can managed easily .
A list of hash codes, which is initialized at every run of the program with the *Info* file, 
is kept in the hash manager, and every new *operation*'s hash code is added to the list. 
This enables us to easy and simple *search* and *clear* methods on the cache manager.


