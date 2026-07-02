#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cctype>


namespace {
    void printValues(std::vector<int> v) {
        int width = 4;
        std::cout << std::right; 

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


}

void insertElem(std::vector<int>& where, std::vector<int>::iterator endIt, int elem)
{
    // where.insert(where.begin(), endIt, elem);
    auto it = std::lower_bound(where.begin(), endIt, elem);
    where.insert(it, elem);
}

std::vector<int> fordJohnson(
    std::vector<int>& value,
     std::vector<int>& partner,
     std::vector<int> current)
{
    if (current.size() <= 1)
        return current;

    printValues(value);
    printValues(partner);
    printValues(current);
    std::cout << std::endl;

    std::vector<int> tail;     // если нечётное число элементов

    std::vector<int> level0;
    int lonely = -1;

    for (size_t i = 0; i + 1 < current.size(); i += 2) {
        int a = current[i], b = current[i+1];
        if (value[a] < value[b]) std::swap(a, b);

        int new_id = value.size();
        value.push_back(value[a]);
        partner.push_back(b);
        level0.push_back(new_id);
    }
    if (current.size() % 2 == 1)
        lonely = current.back();
    //     level0.push_back(current.back());
    // std::cout << lonely << std::endl;
    
    printValues(value);
    printValues(partner);
    printValues(current);
    printValues(level0);
    for (int idx: level0)
        std::cout << value[idx] << " ";
    if (lonely != -1)
        std::cout << "lonely=" << value[lonely];
    std::cout << "\n-----------------------------------------------" <<std::endl;

    std::vector<int> mainChain = fordJohnson(value, partner, level0);

    std::cout << "mainChain raw:";
    printValues(mainChain);

    std::vector<int> inserts;
    for (std::size_t i = 0; i < mainChain.size(); ++i)
    {
        int partnerIdx = partner[mainChain[i]];
        // int v = partner[partnerIdx];
        inserts.push_back(partnerIdx);
        // std::cout << mainChain[i] << " " <<  value[mainChain[i]] << " " << partnerIdx << " " << v << ", ";
        std::cout << mainChain[i]<< "->" << partnerIdx << ", ";
    }
    std::cout << std::endl;
    // std::cout << "lonely=" << lonely << "\n";
    std::cout << "inserts:";
    printValues(inserts);
    mainChain.insert(mainChain.begin(), inserts[0]);

    for (std::size_t i = 1; i < inserts.size(); ++i)
    {
        std::cout << i << " " << inserts[i] << " ";
        // insertElem(mainChain, mainChain.end(), inserts[i]);
         int loserId = inserts[i];
        // ищем позицию через std::lower_bound по value[mainChain[i]] < value[loserId]
        auto it = std::lower_bound(mainChain.begin(), mainChain.end(), loserId,
            [&value](int a, int b) { return value[a] < value[b]; });
        mainChain.insert(it, loserId);
    }
    if (lonely != -1)
        insertElem(mainChain, mainChain.end(), lonely);

    std::cout << "mainChain raw:";
    printValues(mainChain);
    std::cout << "mainChain org:";
    printChain(value, mainChain);

    std::cout << "===========================================" <<std::endl;
    return mainChain;
}

void fordJohnsonSort(std::vector<int>& input) {
    std::vector<int> value = input;      // value[0..n-1] = исходные значения
    std::vector<int> partner(input.size(), -1);
    
    std::vector<int> current(input.size());
    for (size_t i = 0; i < input.size(); ++i)
        current[i] = i;                   // изначально ID = индекс в исходном массиве
    
    fordJohnson(value, partner, current); // первый вызов — без ручного разбиения на пары
}


// "17 3 22 8 14 25 1 19 6 11 23 9 16 4 20 12 7 24 2 15 10 21 5 18 13"
std::vector<int> PmergeMe::sort(std::vector<int> values)
{
    std::size_t n = 42;

    std::vector<int> table;
    for (std::size_t i = 0; i < n; i++) {
        table.push_back(i);
    }
    printValues(table);
    std::cout << std::endl;

    fordJohnsonSort(values);
    // std::vector<int> partner(n, -1);
    // std::vector<int> level;

    // for (std::size_t i = 0; i+1 < n; i += 2) {
    //    int a = i, b = i+1;
    //     if (values[a] < values[b]) std::swap(a, b); // a = max, b = min
    //     partner[a] = b;
    //     level.push_back(a);
    // }

    // std::vector<int> table;
    // for (std::size_t i = 0; i < n; i++) {
    //     table.push_back(i);
    // }

    // printValues(table);
    // std::cout << std::endl;
    // printValues(partner);
    // printValues(level);

    std::vector<int> res;
    return res;
}
