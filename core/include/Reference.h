#pragma once
#include "Logger.h"
namespace yage {
    class Reference {

    public:

        Reference();

        void addRef();

        void release();

        int getRefCount();

    private:
        int mRefCount = 0;
    };

    template<typename T>
    class Ref {
    public:
        Ref() {
            mReference = nullptr;
        }

        Ref(T *reference){
            if(mReference == reference) return;
            if(mReference){
                mReference->release();
                if (mReference->getRefCount() <= 0) {
                    delete mReference;
                    mReference = nullptr;
                }
            }
            mReference = reference;
            if (mReference)
                mReference->addRef();
        };

        template<typename U>
        Ref(Ref<U> &other) {
            if(mReference){
                mReference->release();
                if (mReference->getRefCount() <= 0) {
                    delete mReference;
                    mReference = nullptr;
                }
            }
            mReference = (T *) other.get();
            if (mReference)
                mReference->addRef();
        }

        Ref(const Ref& other){
            if(this == &other) return;
            if(mReference){
                mReference->release();
                if (mReference->getRefCount() <= 0) {
                    delete mReference;
                    mReference = nullptr;
                }
            }
            mReference = other.get();
            if (mReference)
                mReference->addRef();
        }


        ~Ref() {
            if (!mReference) {
                return;
            }
            mReference->release();
            if (mReference->getRefCount() <= 0) {
                delete mReference;
                mReference = nullptr;
            }
        };

        T *get() const {
            return mReference;
        }

        T *operator->() const {
            return mReference;
        }

        Ref &operator=(const Ref &other) {

            if(this == &other) return *this;
            if(mReference){
                mReference->release();
                if (mReference->getRefCount() <= 0) {
                    delete mReference;
                    mReference = nullptr;
                }
            }
            mReference = other.get();

            if (mReference)
                mReference->addRef();
            return *this;
        }

        bool operator! (){
            return mReference == nullptr;
        }

    private:
        T *mReference = nullptr;
    };
}