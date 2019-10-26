#pragma once
namespace yage{
class RefCounted {

public:

    Ref()
    void addRef();
    void Release();

private:
    int mRefCount = 0;
};
}