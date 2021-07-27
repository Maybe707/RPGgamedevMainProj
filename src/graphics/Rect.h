#ifndef RPG_RECT_H
#define RPG_RECT_H

template <typename T>
class Rect {
private:
    T m_left;
    T m_bottom;
    T m_width;
    T m_height;
public:
    Rect(T left, T bottom, T width, T height);

    inline T getLeft() const {
        return m_left;
    }

    inline T getBottom() const {
        return m_bottom;
    }

    inline T getWidth() const {
        return m_width;
    }

    inline T getHeight() const {
        return m_height;
    }
};

template<typename T>
Rect<T>::Rect(T left, T bottom, T width, T height)
        : m_left(left), m_bottom(bottom), m_width(width), m_height(height) {

}

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

#endif //RPG_RECT_H
