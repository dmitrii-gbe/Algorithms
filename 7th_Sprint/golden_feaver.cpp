#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

struct Pile {
    Pile(int cost_, int mass_) : mass(mass_), cost(cost_) {}
    Pile() = default;
    size_t mass = 0;
    size_t cost = 0;
};

std::ostream& operator<<(std::ostream& out, const Pile& i) {
    out << i.mass << " " << i.cost << '\n';
    return out;
}

std::vector<Pile> GetPiles(size_t n) {
    std::vector<Pile> result(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> result[i].cost >> result[i].mass;
    }
    return result;
}

size_t GetMaxGain(std::vector<Pile>& piles, size_t max_mass) {
    std::sort(piles.begin(), piles.end(),
              [](const Pile& lhs, const Pile& rhs) { return lhs.cost > rhs.cost; });
    size_t result = 0;
    size_t current_mass = 0;
    size_t i = 0;
    while (current_mass < max_mass && i < piles.size()) {
        int mass_to_take = std::min(max_mass - current_mass, piles[i].mass);
        result += mass_to_take * piles[i].cost;
        ++i;
        current_mass += mass_to_take;
    }
    return result;
}

int main() {
    size_t max_mass = 0;
    std::cin >> max_mass;
    int piles_number = 0;
    std::cin >> piles_number;
    auto piles = GetPiles(piles_number);
    std::cout << GetMaxGain(piles, max_mass);
    return 0;
}
