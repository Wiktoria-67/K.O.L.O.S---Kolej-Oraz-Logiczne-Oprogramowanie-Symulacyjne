#pragma once
#include <stdexcept>

namespace Industry {

    class EmptyStorageException : public std::logic_error {
    public:
        EmptyStorageException(); 
    };

}