# Assignment 3 - cache manager
## Overview
In this project we wrote a program which solves different types of problems, and uses chach management to enable faster 
calculations based on calculations which have been previously made.

## The Cache Manager
to achieve faster calculations based on calculations which have been previously made, we implemented a cache manager structure which manages calculation files
and makes sure no uneccesary calculations are made. First of all, a "cache" folder is created. That folder includes 2 types of files; The *Info* file, and the result 
files. The *info* file, contains a list of the names of the hash result files, each name representing the hash of the input files of the calculation, In a specific order. Once a new calculation is made, the input hash is calculated and a search on the *Info* file is initiated. if we found a file with the same hash - that means we found the file in the cache and we return the content of the file, so no caculation is needed. If we do not find a matching file in the cache, then we have to perform a calculation, and then add the new file to the cache. 

The cache *Info* file contains a list of cache files in an order according to the LRU cache algorithm; when a new file is added it is added to the top and the last file is removed from the cache, and if we perform a calculation and it exists in the cache then the cache file is moved to the top.

## The Structure
We designed the project using the **abstract factory** design pattern. The objects that are handeled are *Operations*, objects of a class implementing the 
*Operation* interface.

An operation is a command, for example ```ex3.out matrix multiply matrix1.txt matrix2.txt mult_result.txt```
