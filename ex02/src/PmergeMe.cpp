#include "PmergeMe.hpp"
#include <algorithm>
#include <vector>


// namespace {
    // void printValues(std::vector<int> v, std::string name) {
    //     int width = 4;
    //     std::cout << std::right; 

    //     std::cout << std::setw(7) << name << ":";
    //     std::cout << std::setw(width) << v[0];
    //     for (std::size_t i = 1; i < v.size(); ++i) {
    //         std::cout << std::setw(width) << v[i];
    //     }
    //     std::cout << std::endl;
    // }

// }

PmergeMe::Node::Node(int v, int pr, int pa) : value(v), prev(pr), partner(pa) {}

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

std::size_t PmergeMe::getCountComparing()
{
    return count_cmp;
}

void PmergeMe::insertElem(std::vector<int>& where,
    std::vector<int>::iterator startIt,
    std::vector<int>::iterator endIt,
    int elem,
    std::vector<Node>& nodes)
{
    auto it = std::lower_bound(startIt, endIt, elem,
        [&nodes](int a, int b) { ++count_cmp; return nodes[a].value < nodes[b].value; });
    where.insert(it, elem);
}

std::vector<int> PmergeMe::fordJohnson(std::vector<Node>& nodes,
        std::vector<int>& current)
{
    if (current.size() <= 1)
        return current;

    std::vector<int> level;
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
    
    std::vector<int> mainChain = fordJohnson(nodes, level);
    
    std::vector<int> inserts;
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

std::vector<int> PmergeMe::sort(std::vector<int> values)
{
    std::size_t size = values.size();
    std::vector<Node> nodes;
    nodes.reserve(2 * size);
    std::vector<int> current(size);

    for (size_t i = 0; i < values.size(); ++i)
    {
        Node node = {values[i], -1, -1};
        nodes.push_back(node);
        current[i] = i;
    }
        
    count_cmp = 0;
    std::vector<int> res = fordJohnson(nodes, current);
    
    for (int& elem: res)
        elem = values[elem];

    return res;
}
