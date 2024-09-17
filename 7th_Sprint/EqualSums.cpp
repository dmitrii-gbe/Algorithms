// https://contest.yandex.ru/contest/25597/run-report/117915313/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью функции GetNumbers и хранит их в виде массива. Ответ вычисляется в
функции IfPossibleToSplit. Сначала проверяется что массив содержит более одного элемента и что их общая сумма
кратна 2. Затем, если массив удовлетворяет этим условиям, функция пытается набрать из массива элементы таким
образом, чтобы получить наибольшую сумму, непревышающую половину от общей. Механизм подсчета аналогичен
реализации задачи о рюкзаке. В случае, если эта величина окажется равной половине общей сумма, функция
возвращает true, в противном случае - false.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Очевидно, что чтобы разделить массив чисел на две части с равными суммами, в массиве должно быть больше одного
элемента, а их сумма должна быть кратна 2. Проверка того, можно ли набрать из массива числа с определенной
суммой базируется на решении задачи о рюкзаке. Рассмотрим набор элементов (чисел) от 0 до i-го и сумму S.
Нужно выбрать такой набор чисел, чтобы получить сумму непревышающую и максимально близкую к S. Каждое число
может входить в искомую сумму и не входить в нее. Тогда максимальное значение будет максимумом от двух
величин, соответствующих первой и второй ситуации. Первая величина - максимальая сумма чисел для верхней
границы суммы, меньшей на значение элемента, решение о добавлении которого принимается в текущий момент, плюс
значение этого элемента. Вторая величина - максимальная сумма для того же верхнего ограничения на сумму и
набора элементов, несодержащего текущего. Таким образом, решение можно представить как последовательное (слева
направо и сверху вниз) вычисление значений матрицы, где столбцы соответствуют верхнему ограничению на
максимальную сумму элементов, а строки набору элементов от нуля до i.


-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временая сложность алгоритма составляет O(MN), где M - половина общей суммы элементов, а N - общее число
элементов в массиве.


-- Пространственная сложность --
Пространственная сложность алгоритма составляет O(M), где M - где M - половина суммы элементов в массиве.
Поскольку восстановление ответа не требуется вместо полной матрицы хранятся только две строки, необходимые для
вычисления в текущий момент.
*/

#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> GetNumbers(int number) {
    std::vector<int> numbers(number, 0);
    for (int i = 0; i != number; ++i) {
        std::cin >> numbers[i];
    }
    return numbers;
}

bool IfPossibleToSplit(const std::vector<int>& numbers) {
    int max_sum = std::reduce(numbers.begin(), numbers.end(), 0, std::plus{});
    if (numbers.size() < 2 || max_sum % 2 != 0) {
        return false;
    }

    int half_sum = max_sum / 2;
    std::vector<int> active(half_sum + 1, 0);
    std::vector<int> buffer = active;

    for (int i = 1; i < (int)numbers.size() + 1; ++i) {
        for (int j = 1; j < (int)active.size(); ++j) {
            int top_left = (numbers[i - 1] > j ? buffer[j] - numbers[i - 1] : buffer[j - numbers[i - 1]]);
            int value = std::max(buffer[j], top_left + numbers[i - 1]);
            active[j] = value;
        }

        if (active.back() == half_sum) {
            return true;
        }

        std::swap(active, buffer);
    }

    return false;
}

int main() {
    int numbers_count = 0;

    std::cin >> numbers_count;

    auto numbers = GetNumbers(numbers_count);

    std::cout << (IfPossibleToSplit(numbers) ? "True" : "False");

    return 0;
}
