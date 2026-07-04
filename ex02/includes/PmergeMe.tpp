#include "PmergeMe.hpp"
#include <algorithm>
#include <vector>
#include <deque>


template <typename T, typename N>
void PmergeMe::insertElem(T& where,
    typename T::iterator startIt,
    typename T::iterator endIt,
    int elem,
    N& nodes)
{
    auto it = std::lower_bound(startIt, endIt, elem,
        [&nodes](int a, int b) { ++count_cmp; return nodes[a].value < nodes[b].value; });
    where.insert(it, elem);
}

template <typename Tnode, typename Tint>
Tint PmergeMe::sort(const std::vector<int>& values)
{
    Tnode nodes;
    Tint current;

    for (size_t i = 0; i < values.size(); ++i)
    {
        nodes.push_back({values[i], -1, -1});
        current.push_back(i);
    }
        
    count_cmp = 0;
    Tint res = fordJohnson(nodes, current);

    for (int& elem: res)
        elem = values[elem];

    return res;
}

template <template <typename...> class Container>
Container<int> PmergeMe::fordJohnson(Container<Node>& nodes,
        Container<int>& current)
{
    if (current.size() <= 1)
        return current;

    Container<int> level;
    int lonely = -1;

    for (size_t i = 0; i + 1 < current.size(); i += 2) {
        int idx1 = current[i];
        int idx2 = current[i+1];
        level.push_back(nodes.size());

        ++count_cmp;
        if (nodes[idx1].value < nodes[idx2].value)
            nodes.push_back(Node(nodes[idx2].value, current[i+1], idx1));
        else 
            nodes.push_back(Node(nodes[idx1].value, current[i], idx2));
    }
    if (current.size() % 2 == 1)
        lonely = current.back();
    
    Container<int> mainChain = fordJohnson(nodes, level);
    
    Container<int> inserts;
    for (std::size_t i = 0; i < mainChain.size(); ++i)
    {
        int partnerIdx = nodes[mainChain[i]].partner;
        inserts.push_back(partnerIdx);
        int idx = mainChain[i];
        mainChain[i] = nodes[idx].prev;
    }
    if (lonely != -1)
        inserts.push_back(lonely);
    mainChain.insert(mainChain.begin(), inserts[0]);

    std::size_t jacobsthalNumberIdx = 2;
    std::size_t prevJacob = getJacobsthalNumber(jacobsthalNumberIdx);
    std::size_t inserted = 1;
    while (true)
    {
        if (prevJacob > inserts.size())
            break;
        std::size_t currJacob = getJacobsthalNumber(++jacobsthalNumberIdx);
        std::size_t upper = currJacob > inserts.size() ? inserts.size() : currJacob;
        for(std::size_t i = upper; i > prevJacob; --i)
        {
            insertElem(mainChain, 
                mainChain.begin(), mainChain.begin() + (i + inserted - 1),
                inserts[i - 1], nodes);
            inserted++;
        }
        prevJacob = currJacob;
    }

    return mainChain;
}
