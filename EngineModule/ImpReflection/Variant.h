#pragma once
#include "BaseVariant.h"

namespace ImpReflect
{
    /// <summary>
    /// new로 생성한 객체를 가지고 있는 클래스
    /// </summary>
    template <typename T>
    class Variant : public BaseVariant
    {
    public:
        Variant(T* object);

        void* Get()const override { return _object; }

        bool IsVaild()const override { return _object != nullptr; }

    private:
        T* _object;
    };

	template <typename T>
	ImpReflect::Variant<T>::Variant(T* object)
        :_object(object)
	{}

}
