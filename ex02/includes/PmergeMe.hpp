#pragma once

#include <string>
#include <vector>


class PmergeMe
{
    private:
        static inline std::vector<std::size_t> jacobsthal;
        static inline std::size_t count_cmp = 0;
        
        static inline void insertElem(std::vector<int>& where,
            std::vector<int>::iterator endIt,
            int elem,
            std::vector<int>& value);
        static inline std::vector<int> fordJohnson(
            std::vector<int>& value,
            std::vector<int>& prev,
            std::vector<int>& partner,
            std::vector<int> current);
        
    public:
        PmergeMe() = default;
        PmergeMe(const PmergeMe& other) = default;
        PmergeMe& operator=(const PmergeMe& other) = default;
        ~PmergeMe() = default;

        static std::size_t getJacobsthalNumber(std::size_t idx);
        static std::size_t getPrevJacobsthalNumber(std::size_t value);
        static std::vector<int> sort(std::vector<int>);
        

};
