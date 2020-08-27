#include "HashOperationFactory.hpp"
#include "OperationExceptions.hpp"
#include "Operation.hpp"
#include "HashOperation.hpp"
#include "CrcHash.hpp"
#include <fstream>

namespace operation{

     const Operation& HashOperationFactory::createOperation(const std::string command[]) const{

         if(!isValidCommand(command)){
             throw exceptions::OperationUnvalidException();
         }

         std::string info = "";
         for(uint32_t i = 0 ; i < command->size() ; i++){
             info += command[i];
         }

        HashOperation hash(info, readHashFromFile(command[2]));

        return static_cast<Operation>(hash);

     }

     bool HashOperationFactory::isValidCommand(const std::string command[]) const{

         if(command->size() != 4){
             return false;
         }

         if(command[0].compare("hash") != 0 ){
             return false;
         }

         if(command[1].compare("crc32") != 0 ){
             return false;
         }

        return true;
     }

     const hash::CrcHash HashOperationFactory::readHashFromFile(const std::string& pathToFile){

         std::ifstream hashFile(pathToFile);

         // checking if an error has occured while opening the file
         if (!hashFile.is_open()) {
            throw exceptions::FileOpenException();
        }

        std::string line;
        std::string content = "";
        while (!hashFile.eof()){
            std::getline(hashFile, line);
            content += line;
            content += "\n";
        }

        hash::CrcHash hash(content);

        return hash;   
     }

}