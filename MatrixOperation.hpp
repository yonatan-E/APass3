#pragma once

#include "Operation.hpp"
#include "Matrix.hpp"
#include <fstream>

namespace operation {

    class MatrixOperation : public Operation {
        
        // the left operand matrix
        matrix::Matrix _leftArg;
        // the right operand matrix
        matrix::Matrix _rightArg;
        // the output matrix
        matrix::Matrix _result;

        public:

            MatrixOperation(std::string info, const matrix::Matrix& leftArg, 
                const matrix::Matrix& rightArg, const matrix::Matrix& result);

            virtual void writeOperationToOutputFile(const std::string& outputPath) const override;

            virtual void addOperationFileToCache() const override;

        private:

            static void writeMatrixToOfStream(std::ofstream& stream, const matrix::Matrix& matrix);
    };
}