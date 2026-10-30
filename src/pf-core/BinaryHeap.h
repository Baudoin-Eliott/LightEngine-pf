#pragma once
#include <functional>
#include <vector>
#include <cassert>
#include <utility>

template<typename T, typename Compare = std::less<T>>
class BinaryHeap {
public:


    explicit BinaryHeap(Compare _comp = Compare()) : m_compare(_comp) {}


    void push(const T& _val) {
        m_data.push_back(_val);
        siftUp(size() - 1);

    }
    void push(T&& _val) { // permet d'appeller la fonction avec des rvalue
        m_data.push_back(std::move(_val));
        siftUp(size() - 1);
    }

    const T& top() const {
        assert(empty() == false && "Top() was use on an empty BinaryHeap");
        return m_data[0];
    }

    void pop() {
        assert(empty() == false && "Pop() was use on an empty BinaryHeap");

        if (size() > 1) m_data[0] = std::move(m_data[size()-1]);
        m_data.pop_back();
        siftDown(0);

    }
    
    size_t size() const { return m_data.size(); }

    bool empty() const { return size() == 0; }

    
private:

    void swap(size_t _i, size_t _j) {
        std::swap(m_data[_i], m_data[_j]);
    }


    void siftUp(size_t _i) {
        //on remonte on verifiant le parent

        while (_i > 0) {
            size_t parent = (_i - 1) / 2;

            if (m_compare(m_data[parent], m_data[_i]) == false) break;
            
            swap(parent, _i);
            _i = parent;
            
        }
    }

    void siftDown(size_t _i) {
        //on descend en choppant les enfants

        //gauche + 1 c'est droit;
        while (2 * _i + 1 < size()) {
            size_t gauche = 2 * _i + 1;
            size_t best = gauche;

            if (gauche + 1 < size() && m_compare(m_data[gauche], m_data[gauche + 1])) best = gauche + 1;

            if (m_compare(m_data[_i], m_data[best]) == false) break;
            swap(_i, best);
            _i = best;
        }
    }


    Compare m_compare;
    std::vector<T> m_data;
};
