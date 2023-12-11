#pragma once
#include "BaseVariant.h"

namespace ImpReflect
{
    /// <summary>
    /// new�� ������ ��ü�� ������ �ִ� Ŭ����
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
