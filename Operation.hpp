#include <string>

namespace operation {

    class Operation {

        // the path to the file in the cache
        std::string _cachePath;
        // the time and the date when the operation happened
        std::string _info;

        public:

            Operation(std::string info);
            
            virtual void writeOperationToOutputFile(const std::string& outputPath) const = 0;

            virtual void addOperationFileToCache() const = 0;

            virtual void deleteOperationFileFromCache() const final;

            virtual const std::string& getCachePath() const final; 
    };
}