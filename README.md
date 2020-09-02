# Assignment 3 - Cache Manager
## Overview
In this project we wrote a program which supports different kinds of operations, and uses cache management to enable faster calculations based on calculations which have been previously made.

About the Design
--------------------------------------------------------------------------------------------------------------------------
The project is designed according to the **Abstract Factory** design pattern. The objects that are created by the factories are *operation* objects, which are objects from classes that inherit from the abstract class **Operation**, like *MatrixOperation*, *BitmapOperation*, and more. All of the *operation* objects holds at least their *hashCode* and the result of the specific *operation*. The use of the *hashCode* is explained at the part of the *Cache Manager*.  
The abstract class **OperationFactory** is a base class for all of the *operation factory* classes, like *MatrixOperationFactory*, *BitmapOperationFactory*, and more.   
The *operation factory* classes are in charge of creating *operation* objects from a given command, using the createOperation() method. Those classes create *operation* objects without revealing the implementation and the structure of the specific *operation* class. The purpose of the *operation factory* classes is to optimize the complex initialize of the *operation* objects.    
*Operation* objects are created using commands, like the command ```ex3.out matrix multiply matrix1.txt matrix2.txt mult_result.txt```, which gets the result of the multiplication of the given matrices, and writes it into a *MatrixOperation* object, using a *MatrixOperationFactory* object.  

Maintaining the SOLID principals:
------------------------------------------------------------------------------------------------------------------------- 
***Single responsibility principle:*** All of the *operation* classes have a responsibility just on their own, and they are not depending on other classes like the *operation factory* classes or the *Cache Manager* class, because those classes are not in the responsibility of the *operation* classes.  
All of the *operation factory* classes do just what in their responsibility, according to the design pattern **Abstract Factory**, which is performing creation of the specific *operation* objects, and more actions which are related to that. 
The *Cache Manager* class does just what in its responsibility, which is managing the cache, and not doing things like create *operation* objects or another things which are outside of the classes respobsibility.  

***Open/Close principle***: On the one hand, the system is very flexible and open for extensions, because adding a new *operation* class is very easy - just force the new *operation* class to inherit from the abstract class *Operation* and implement its behavior, and also, if needed, create a *operation factory* class that will create objects of the new *operation* class, and force it to inherit from the abstract class **OperationFactory** and implement its behavior.   
On the other hand, the system is very tough and close for changes because the *CacheManager* class uses and based on the structure and the behavior of the *operation* and the *operation factory* classes, so if the structure or the behavior of those classes will be changed, there is a big chance that the *CacheManager* will not work correctly. 

***Liskov substitution principle:*** In the project, every class that have subclasses is an abstract class, so its obvious that this principle exists here.  

***Interface segregation principle:*** All of the classes in the project have interfaces which are adjusted to the needs of the client. For example, the interface of the 
**Operation** abstract class includes methods like *writeOperationToFile()*, which are necessary for the clients which use the *operation* classes objects, like *CacheManager* which saves *operations* by writing them into files, using this method. Another example is that the interface of the **OperationFactory** abstract class includes methods which are really relevant for the clients which use the *operation factory* class objects, like the *createOperation()* method which is used by the clients to create *operation* class objects.  

***Dependency Inversion principle:*** The *CacheManager* class manages objects of *operation* classes and saves them, but never uses a specific *operation* like *MatrixOperation* or *BitmapOperation*, but uses the **Operation** base class and relies on its interface.    

About the Cache Manager
--------------------------------------------------------------------------------------------------------------------------
To achieve faster calculations based on calculations which have been previously made, we implemented a cache manager module that manages the calculations and saves the five most relevant results, so no uneccesary calculations are made.
The cache saves the result files in a folder named *cache*. That folder contains files which holds the recent relevant results.
That folder also saves the file *info.txt*, which contains meta data about the result files, and will hold it through the different runs of the program. The *info.txt* file contains the *hashCodes* of all of the results in the *cache* folder, and holds information about the relevance of each result. The relevance of each result will be according to the LRU algorithm, which works actually like a priority queue:  
When loading a new result into the cache, if the result is not exist on the cache, it will be inserted to the end of the queue, and if the result is already exist on the cache, its place will be changed to the end of the queue. If the queue is already full (the cache is full), popping the result which is placed at the start of the queue, which is the most unrelevant result.  
The meta data that the *info.txt* file saves is about the current order of the results in the priority queue, according to the LRU algorithm.      
**The way the results are saved in the cache:**  
Every operation has a *hashCode*, which is designed in a very specific way, according to the specific *operation*, and is calculated using the *crc32* algorithm.  
The cache saves an *operation* object by a *hashCode* and a *result file*, in a way that the name of the result file is the *hashCode* of the specific *operation*, to make it more comfortable. When a new *operation* is added to the cache, we can easily check if the *operation* is already exist in the cache, by just calculating the *hashCode* of the new *operation* and compare it with all of the *hashCodes* in the cache. That thing allows us to get the result of a specific *operation* in O(1) time, if the specific *operation* is already exist in the cache.  
This hashing cache technique is very safe, because the chance that there will be two different *operations* with the same *hashCode* is almost zero, due of the specific way that the hash is designed and calculated in which promises us that collisions are almost not possible, and due to the fact that the number of possible *hashCodes* that can be created that way is **2^32**, while the maximun capacity of the cache is only **five**.

