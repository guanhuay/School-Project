//
//  Exception.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-02
//  From Goodrich et al., 2d Ed., Sections 2.4.3 and 9.1.2
//

#ifndef Binary_Search_Trees_Exception_h
#define Binary_Search_Trees_Exception_h

#include <string>

namespace Exceptions {
    
    using std::string;

    class RuntimeException {
    private:
        string errorMsg;
    public:
        RuntimeException(const string& err) { errorMsg = err; }
        string getMessage() const { return errorMsg; }
    };
    
    class NonexistentElement : RuntimeException {
    public:
        NonexistentElement(const string& err) : RuntimeException(err) {}
    };

}

using Exceptions::RuntimeException;
using Exceptions::NonexistentElement;
#endif
