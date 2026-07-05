#pragma once

#include <vector>
#include <deque>
#include <cstddef>


class PmergeMe
{
    public:
    struct Node
    {
        int value = 0;
        int prev = -1;
        int partner = -1;

        Node() = default;
        Node(int v, int pr, int pa);
        Node(const Node& other) = default;
        Node& operator=(const Node& other) = default;
        ~Node() = default;
    }; 
    private:

        PmergeMe() = default;
        PmergeMe(const PmergeMe& other) = default;
        PmergeMe& operator=(const PmergeMe& other) = default;
        ~PmergeMe() = default;
    
        static std::size_t getJacobsthalNumber(std::size_t idx);
        static inline std::vector<std::size_t> jacobsthal;
        static inline std::size_t count_cmp = 0;

        template <template <typename...> class Container>
        static Container<int> fordJohnson(Container<Node>& nodes, Container<int>& current);
        
        template <typename T, typename N>
        static void insertElem(T& where,
                        typename T::iterator startIt,
                        typename T::iterator endIt,
                        int elem,
                        N& nodes);
        
    public:
        template <typename Tnode, typename Tint>
        static Tint sort(const std::vector<int>& values);

        static std::size_t getCountComparing();

};

#include "PmergeMe.tpp"
