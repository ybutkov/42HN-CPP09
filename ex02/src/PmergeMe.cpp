#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cctype>


namespace {
    void printValues(std::vector<int> v, std::string name) {
        int width = 4;
        std::cout << std::right; 

        std::cout << std::setw(7) << name << ":";
        std::cout << std::setw(width) << v[0];
        for (std::size_t i = 1; i < v.size(); ++i) {
            std::cout << std::setw(width) << v[i];
        }
        std::cout << std::endl;
    }

    void printChain(std::vector<int> v, std::vector<int> ch) {
        int width = 4;
        std::cout << std::right; 

        std::cout << std::setw(width) << v[ch[0]];
        for (std::size_t i = 1; i < ch.size(); ++i) {
            std::cout << std::setw(width) << v[ch[i]];
        }
        std::cout << std::endl;
    }

    bool checkSorting(std::vector<int>& arr, std::size_t size)
    {
        for (std::size_t i = 1; i < size; ++i)
            if (arr[i]<arr[i-1]) return false;
        return true;
    }
}

// iterator ??
std::size_t PmergeMe::getJacobsthalNumber(std::size_t idx)
{
    for(std::size_t i = jacobsthal.size(); i <= idx; ++i)
    {
        if (i < 2)
            jacobsthal.push_back(static_cast<int>(i));
        else
            jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
    }
    return jacobsthal[idx];
}

std::size_t PmergeMe::getPrevJacobsthalNumber(std::size_t value)
{
    if (value == 0)
        return getJacobsthalNumber(0);    
    std::size_t idx = 1;
    while (value >= getJacobsthalNumber(idx))
        idx++;
    return getJacobsthalNumber(idx - 1);
}

void PmergeMe::insertElem(std::vector<int>& where,
    std::vector<int>::iterator endIt,
    int elem,
    std::vector<int>& value)
{
    auto it = std::lower_bound(where.begin(), endIt, elem,
        [&value](int a, int b) { ++count_cmp; return value[a] < value[b]; });
        // [&value](int a, int b) { return value[a] < value[b]; });
    where.insert(it, elem);
}

std::vector<int> PmergeMe::fordJohnson(
    std::vector<int>& value,
    std::vector<int>& prev,
    std::vector<int>& partner,
    std::vector<int> current)
{
    if (current.size() <= 1)
        return current;

    // printValues(value, "value");
    // printValues(prev, "prev");
    // printValues(partner, "partner");
    // printValues(current, "curr");
    // std::cout << std::endl;

    std::vector<int> level0;
    int lonely = -1;

    for (size_t i = 0; i + 1 < current.size(); i += 2) {
        int a = current[i];
        int b = current[i+1];
        int new_id = value.size();
        level0.push_back(new_id);
        ++count_cmp;
        if (value[a] < value[b])
        {
            value.push_back(value[b]);
            prev.push_back(current[i+1]);
            partner.push_back(a);
        }
        else 
        {
            value.push_back(value[a]);
            prev.push_back(current[i]);
            partner.push_back(b);
        }
    }
    if (current.size() % 2 == 1)
        lonely = current.back();
    
    // printValues(value, "value");
    // printValues(prev, "prev");
    // printValues(partner, "partner");
    // printValues(current, "curr");
    // printValues(level0, "level0");
    // for (int idx: level0)
    //     std::cout << "l_v=" << value[idx] << " ";
    // if (lonely != -1)
    //     std::cout << "lonely=" << value[lonely];
    // std::cout << "\n------------ recursion into -------------------------" <<std::endl;

    std::vector<int> mainChain = fordJohnson(value, prev, partner, level0);
    
    // std::cout << "\n------------ recursion out -------------------------" <<std::endl;
    // printValues(mainChain, "mainChain raw");

    std::vector<int> inserts;
    for (std::size_t i = 0; i < mainChain.size(); ++i)
    {
        int partnerIdx = partner[mainChain[i]];
        inserts.push_back(partnerIdx);
        int idx = mainChain[i];
        mainChain[i] = prev[idx];
    }
    // std::cout << std::endl;
    // printValues(mainChain, "mainChain raw");
    // std::cout << "mainChain org:";     printChain(value, mainChain);
    // // std::cout << "lonely=" << lonely << "\n";
    // printValues(inserts, "inserts      ");
    // std::cout << "inserts   org:";
    // printChain(value, inserts);

    // if (lonely != -1)
    //     insertElem(mainChain, mainChain.end(), lonely, value);
    if (lonely != -1)
        inserts.push_back(lonely);
    mainChain.insert(mainChain.begin(), inserts[0]);

    // for (std::size_t idx = 1; idx < inserts.size(); ++idx)
    // {
    //     insertElem(mainChain, mainChain.begin() + 2 * idx, inserts[idx], value);
    // }
    
    // int n = PmergeMe::getPrevJacobsthalNumber(inserts.size());
    std::size_t jacobsthalNumberIdx = 2;
    std::size_t prevJacob = PmergeMe::getJacobsthalNumber(jacobsthalNumberIdx);
    // std::cout << "JacobsthalNumber=" << prevJacob << "\n";
    std::size_t inserted = 1;
    while (true)
    {
        if (prevJacob > inserts.size())
            break;
        std::size_t currJacob = PmergeMe::getJacobsthalNumber(++jacobsthalNumberIdx);
        std::size_t upper = currJacob > inserts.size() ? inserts.size() : currJacob;
        for(std::size_t i = upper; i > prevJacob; --i)
        {
            insertElem(mainChain, mainChain.begin() + (i + inserted - 1), inserts[i - 1], value);
            inserted++;
        }
        prevJacob = currJacob;
    }
    // std::cout << "\n";

    // for (std::size_t idx = 1; idx < inserts.size(); ++idx)
    // {
    //     insertElem(mainChain, mainChain.begin() + 2 * idx, inserts[idx], value);
    // }


    // if (lonely != -1)
    //     insertElem(mainChain, mainChain.end(), lonely, value);

    (void)printChain;
    (void)printValues;
    // printValues(mainChain, "mainChain raw");
    // std::cout << "mainChain org:";     printChain(value, mainChain);
    // std::cout << "+++++++++++++" <<std::endl;
    // printValues(mainChain, "mainChain raw");
    // std::cout << "mainChain org:";
    // printChain(value, mainChain);
    // std::cout << "===========================================" <<std::endl;
    return mainChain;
}

std::vector<int> PmergeMe::sort(std::vector<int> values)
{
    std::size_t size = values.size();
    std::vector<int> partner(values.size(), -1);
    std::vector<int> prev(values.size(), -1);
    
    std::vector<int> current(values.size());
    for (size_t i = 0; i < values.size(); ++i)
        current[i] = i;
    
    count_cmp = 0;
    std::vector<int> res = fordJohnson(values, prev, partner, current);
    std::cout << "CMP count=" << count_cmp << std::endl;
    // printValues(res, "res raw");
    
    for (int& elem: res)
        elem = values[elem];

    // printValues(res, "res aft");
    std::cout << "Result arr is " << (checkSorting(res, size) ? " sorted" : " not sorted") << std::endl;
    
    return res;
}
