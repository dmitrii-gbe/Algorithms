#include <cstddef>
#include <iostream>
#include <vector>

struct Item {
    Item(int mass_, int cost_) : mass(mass_), cost(cost_) {}
    Item() = default;
    int mass = 0;
    int cost = 0;
    Item operator+(const Item& other) { return Item{mass + other.mass, cost + other.cost}; }
    bool operator==(const Item& other) const { return mass == other.mass && cost == other.cost; }
};

std::ostream& operator<<(std::ostream& out, const Item& i) {
    out << "[ " << i.mass << " " << i.cost << " ]";
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> v) {
    bool is_first = true;
    for (auto& item : v) {
        if (is_first) {
            std::cout << item;
            is_first = false;
        } else {
            std::cout << " " << item;
        }
    }

    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v) {
    bool is_first = true;
    for (auto& item : v) {
        if (is_first) {
            std::cout << item;
            is_first = false;
        } else {
            std::cout << '\n' << item;
        }
    }

    return out;
}

std::vector<Item> GetItems(size_t n) {
    std::vector<Item> result(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> result[i].mass >> result[i].cost;
    }
    return result;
}

Item Max(const Item& lhs, const Item& rhs) {
    if (lhs.cost > rhs.cost) {
        return lhs;
    } else {
        return rhs;
    }
}

std::vector<int> GetItemSet(const std::vector<Item> items, int max_mass) {
    std::vector<std::vector<Item>> matrix(items.size() + 1, std::vector<Item>(max_mass + 1, {0, 0}));

    for (size_t item = 1; item < matrix.size(); ++item) {
        for (size_t mass = 1; mass < matrix[0].size(); ++mass) {
            size_t index = ((mass < (size_t)items[item - 1].mass) ? 0 : mass - items[item - 1].mass);
            Item sum = matrix[item - 1][index] + items[item - 1];
            Item value = Max(matrix[item - 1][mass], sum);

            if ((size_t)value.mass <= mass) {
                matrix[item][mass] = value;
            } else {
                matrix[item][mass] = matrix[item - 1][mass];
            }
        }
    }

    std::vector<int> path;
    for (int i = matrix.size() - 1, j = matrix[0].size() - 1; i > 0 && j > 0;) {
        if (matrix[i][j] == matrix[i - 1][j]) {
            --i;
        } else {
            j = j - items[i - 1].mass;
            path.push_back(i);
            --i;
        }
    }
    return path;
}

int main() {
    int count = 0;
    int max_mass = 0;
    std::cin >> count >> max_mass;

    auto items = GetItems(count);
    auto result = GetItemSet(items, max_mass);
    std::cout << result.size() << '\n' << result;

    return 0;
}
