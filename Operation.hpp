#include <string>

namespace operation {

    class Operation {

        // the path to the file in the cache
        std::string _cachePath;
        // the time and the date when the operation happened
        std::string _info;

        public:
            
            virtual void writeOperationToFile(const std::string& outputPath) = 0;

            virtual void deleteOperationFile() const final;

            virtual const std::string& getPath() const final; 
    };
}