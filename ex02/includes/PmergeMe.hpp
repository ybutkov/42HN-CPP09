#pragma once

#include <vector>


class PmergeMe
{
    private:

        PmergeMe() = default;
        PmergeMe(const PmergeMe& other) = default;
        PmergeMe& operator=(const PmergeMe& other) = default;
        ~PmergeMe() = default;
    
        struct Node
        {
            int value;
            int prev;
            int partner;

            Node(int v, int pr, int pa);
        };

        static inline std::vector<std::size_t> jacobsthal;
        static inline std::size_t count_cmp = 0;
        
        static std::vector<int> fordJohnson(std::vector<Node>& nodes,
                            std::vector<int>& current);
        static void insertElem(std::vector<int>& where,
                            std::vector<int>::iterator startIt,
                           std::vector<int>::iterator endIt,
                           int elem,
                           std::vector<Node>& nodes);
        
    public:

        static std::size_t getJacobsthalNumber(std::size_t idx);
        static std::size_t getPrevJacobsthalNumber(std::size_t value);
        static std::vector<int> sort(std::vector<int>);
        static std::size_t getCountComparing();

};
