#pragma once

template <class T>
void heapsort_desc(T* begin, T* end)
{
    // creating heap
    size_t k = 1;
    size_t kp = size_t((k-1)/2);
    while(begin+k != end)
    {
        size_t kt = k;
        while(k > kp && *(begin+kt) > *(begin+kp))
        {
            T temp = *(begin+kt);
            *(begin+kt) = *(begin+kp);
            *(begin+kp) = temp;
            kt = kp;
            kp = size_t((kt-1)/2);
        }
        ++k;
        kp = size_t((k-1)/2);
    }

    //
    --k;
    while(k > 0)
    {
        T temp = *(begin+k);
        *(begin+k) = *begin;
        *begin = temp;

        size_t n = k;
        size_t l = 0;
        size_t m = 1;

        while(m < n)
        {
            if(m+1 < n && *(begin+m+1) > *(begin+m))
                m += 1;
            if(*(begin+m) > *(begin+l))
            {
                T temp = *(begin+m);
                *(begin+m) = *(begin+l);
                *(begin+l) = temp;
            }

            l = m;
            m = 2*l + 1;
        }
        --k;
    }
}

template <class T>
void heapsort_asc(T* begin, T* end)
{
    // creating heap
    size_t k = 1;
    size_t kp = size_t((k-1)/2);
    while(begin+k != end)
    {
        size_t kt = k;
        while(k > kp && *(begin+kt) < *(begin+kp))
        {
            T temp = *(begin+kt);
            *(begin+kt) = *(begin+kp);
            *(begin+kp) = temp;
            kt = kp;
            kp = size_t((kt-1)/2);
        }
        ++k;
        kp = size_t((k-1)/2);
    }

    //
    --k;
    while(k > 0)
    {
        T temp = *(begin+k);
        *(begin+k) = *begin;
        *begin = temp;

        size_t n = k;
        size_t l = 0;
        size_t m = 1;

        while(m < n)
        {
            if(m+1 < n && *(begin+m+1) < *(begin+m))
                m += 1;
            if(*(begin+m) < *(begin+l))
            {
                T temp = *(begin+m);
                *(begin+m) = *(begin+l);
                *(begin+l) = temp;
            }

            l = m;
            m = 2*l + 1;
        }
        --k;
    }
}
