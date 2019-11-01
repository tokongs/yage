#include "Reference.h"

namespace yage{
    Reference::Reference() {
        mRefCount = 0;
    }

    void Reference::addRef() {
        mRefCount++;
    }

    void Reference::release(){
        mRefCount--;
    }

    int Reference::getRefCount() {
        return mRefCount;
    }
}