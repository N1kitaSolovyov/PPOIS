#include "LongInt.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

LongInt::LongInt() {
    digits.push_back(0);      // Всегда начинаем с нуля
    isNegative = false;       // Ноль не бывает отрицательным
}

LongInt::LongInt(const string& str) {
    if (str.empty()) {
        digits.push_back(0);
        isNegative = false;
        return;
    }

    // Разбираемся со знаком - только минус в начале имеет значение
    size_t start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;  // Перескакиваем через знак минус
    }
    else {
        isNegative = false;
    }

    // Превращаем символы в цифры один за другим
    for (size_t i = start; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            digits.push_back(str[i] - '0');  // '5' -> 5, '9' -> 9 и т.д.
        }
        else {
            // Встретили не-цифру - создаем ноль и выходим
            digits.clear();
            digits.push_back(0);
            isNegative = false;
            return;
        }
    }

    // Убираем лидирующие нули типа "000123"
    removeLeadingZeros();

    // На случай, если после чистки у нас пусто - вернем ноль
    if (digits.empty()) {
        digits.push_back(0);
        isNegative = false;
    }
}

LongInt::LongInt(int num) {
    if (num == 0) {
        digits.push_back(0);
        isNegative = false;
        return;
    }

    // Запоминаем отрицательное ли число, потом работаем с модулем
    isNegative = (num < 0);
    if (isNegative) {
        num = -num;  // Делаем положительным для простоты
    }

    // Разбираем число на цифры - от младших к старшим
    digits = {};
    while (num > 0) {
        digits.insert(digits.begin(), num % 10);  // Вставляем в начало
        num /= 10;  // Отрезаем последнюю цифру
    }
}

// Просто копируем все что есть в другом числе
LongInt::LongInt(const LongInt& other)
    : digits(other.digits), isNegative(other.isNegative) {
}

// Превращаем внутреннее представление в красивую строку
string LongInt::toString() const {
    string result;

    // Минус нужен только для отрицательных ненулевых чисел
    if (isNegative && !isZero()) {
        result += '-';
    }

    // Каждую цифру превращаем обратно в символ
    for (int digit : digits) {
        result += ('0' + digit);
    }

    return result;
}

// Проверяем является ли число нулем (хранится как [0])
bool LongInt::isZero() const {
    return digits.size() == 1 && digits[0] == 0;
}

// Присваивание - копируем если это не тот же объект
LongInt& LongInt::operator=(const LongInt& other) {
    if (this != &other) {
        digits = other.digits;
        isNegative = other.isNegative;
    }
    return *this;
}

// Проверка равенства - сначала по знаку, потом по цифрам
bool LongInt::operator==(const LongInt& other) const {
    // Числа с разными знаками равны только если оба нули
    if (isNegative != other.isNegative) {
        return isZero() && other.isZero();
    }

    // Разное количество цифр - точно разные числа
    if (digits.size() != other.digits.size()) {
        return false;
    }

    // Сравниваем каждую цифру
    for (size_t i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

// Неравенство - просто обратное равенству
bool LongInt::operator!=(const LongInt& other) const {
    return !(*this == other);
}

// Сравнение "меньше" - самая хитрая операция
bool LongInt::operator<(const LongInt& other) const {
    // Отрицательное всегда меньше положительного
    if (isNegative != other.isNegative) {
        return isNegative;  // Если мы отрицательные - мы меньше
    }

    // Для одинаковых знаков сравниваем по модулю
    if (!isNegative) {
        // Оба положительные: меньше то, у которого меньше модуль
        return compareAbsolute(other) < 0;
    }
    else {
        // Оба отрицательные: меньше то, у которого БОЛЬШЕ модуль (-5 < -3)
        return compareAbsolute(other) > 0;
    }
}

// Остальные сравнения выражаем через уже написанные
bool LongInt::operator>(const LongInt& other) const {
    return other < *this;  // A > B значит B < A
}

bool LongInt::operator<=(const LongInt& other) const {
    return !(other < *this);  // A <= B значит не (B < A)
}

bool LongInt::operator>=(const LongInt& other) const {
    return !(*this < other);  // A >= B значит не (A < B)
}

// Версии для int - превращаем int в LongInt и используем готовые операторы
bool LongInt::operator==(int other) const {
    return *this == LongInt(other);
}

bool LongInt::operator!=(int other) const {
    return *this != LongInt(other);
}

bool LongInt::operator<(int other) const {
    return *this < LongInt(other);
}

bool LongInt::operator>(int other) const {
    return *this > LongInt(other);
}

bool LongInt::operator<=(int other) const {
    return *this <= LongInt(other);
}

bool LongInt::operator>=(int other) const {
    return *this >= LongInt(other);
}

// СЛОЖЕНИЕ - самая интересная арифметическая операция
LongInt LongInt::operator+(const LongInt& other) const {
    // Если знаки разные, превращаем сложение в вычитание
    if (isNegative != other.isNegative) {
        if (isNegative) {
            // (-5) + 3 = 3 - 5
            return other - this->absoluteValue();
        }
        else {
            // 5 + (-3) = 5 - 3
            return *this - other.absoluteValue();
        }
    }

    // Оба числа с одинаковыми знаками - складываем как обычно
    LongInt result;
    result.digits.clear();
    result.isNegative = isNegative;  // Сохраняем знак

    // Переворачиваем цифры чтобы младшие разряды были в начале
    // Так проще делать переносы
    vector<int> a_rev = digits;
    vector<int> b_rev = other.digits;
    reverse(a_rev.begin(), a_rev.end());
    reverse(b_rev.begin(), b_rev.end());

    int carry = 0;  // То, что "переносим" в следующий разряд
    size_t max_len = max(a_rev.size(), b_rev.size());

    // Складываем столбиком как в школе
    for (size_t i = 0; i < max_len; i++) {
        int digit_a = (i < a_rev.size()) ? a_rev[i] : 0;
        int digit_b = (i < b_rev.size()) ? b_rev[i] : 0;

        int sum = digit_a + digit_b + carry;
        carry = sum / 10;  // Что понесем дальше (0 или 1)
        result.digits.push_back(sum % 10);  // Что останется в этом разряде
    }

    // Если после всех разрядов остался перенос - добавляем новую цифру
    if (carry > 0) {
        result.digits.push_back(carry);
    }

    // Возвращаем цифры в нормальный порядок
    reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();

    return result;
}

// ВЫЧИТАНИЕ - тоже интересная логика
LongInt LongInt::operator-(const LongInt& other) const {
    // Если знаки разные, превращаем вычитание в сложение
    if (isNegative != other.isNegative) {
        if (isNegative) {
            // (-5) - 3 = -(5 + 3) = -8
            LongInt result = this->absoluteValue() + other;
            result.isNegative = true;
            return result;
        }
        else {
            // 5 - (-3) = 5 + 3 = 8
            return *this + other.absoluteValue();
        }
    }

    // Оба числа с одинаковыми знаками
    if (!isNegative) {
        // Оба положительные: смотрим какое число больше
        if (*this >= other) {
            // 5 - 3 = 2 (просто вычитаем)
            return subtractAbsolute(other);
        }
        else {
            // 3 - 5 = -2 (вычитаем наоборот и ставим минус)
            LongInt result = other.subtractAbsolute(*this);
            result.isNegative = true;
            return result;
        }
    }
    else {
        // Оба отрицательные: (-5) - (-3) = -5 + 3 = 3 - 5 = -2
        return other.absoluteValue() - this->absoluteValue();
    }
}

// УМНОЖЕНИЕ - используем школьный метод "в столбик"
LongInt LongInt::operator*(const LongInt& other) const {
    // Умножение на ноль дает ноль
    if (isZero() || other.isZero()) {
        return LongInt("0");
    }

    LongInt result;
    result.digits.clear();

    // Определяем знак: минус на минус дает плюс, плюс на минус дает минус
    result.isNegative = (isNegative != other.isNegative);

    // Переворачиваем цифры для удобства вычислений
    vector<int> a_rev = digits;
    vector<int> b_rev = other.digits;
    reverse(a_rev.begin(), a_rev.end());
    reverse(b_rev.begin(), b_rev.end());

    // Временный массив для промежуточных результатов
    vector<int> temp(a_rev.size() + b_rev.size(), 0);

    // Умножаем каждую цифру на каждую
    for (size_t i = 0; i < a_rev.size(); i++) {
        int carry = 0;  // Перенос для текущей строки умножения

        for (size_t j = 0; j < b_rev.size(); j++) {
            // Умножаем цифры и добавляем перенос и то что уже было
            int product = a_rev[i] * b_rev[j] + temp[i + j] + carry;
            carry = product / 10;  // Что переносим дальше
            temp[i + j] = product % 10;  // Что оставляем
        }

        // Если остался перенос после умножения на все цифры - записываем его
        if (carry > 0) {
            temp[i + b_rev.size()] += carry;
        }
    }

    result.digits = temp;
    // Возвращаем цифры в нормальный порядок
    reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();

    return result;
}

// ДЕЛЕНИЕ - самый сложный алгоритм (деление в столбик)
LongInt LongInt::operator/(const LongInt& other) const {
    if (other.isZero()) {
        throw invalid_argument("Division by zero");  // На ноль делить нельзя!
    }

    if (isZero()) {
        return LongInt("0");  // Ноль деленный на что угодно = ноль
    }

    // Определяем знак результата по правилу знаков
    bool resultIsNegative = (isNegative != other.isNegative);

    // Работаем с модулями чисел
    LongInt dividend = this->absoluteValue();
    LongInt divisor = other.absoluteValue();

    // Если делимое меньше делителя - результат 0
    if (dividend < divisor) {
        return LongInt("0");
    }

    // Деление на 1 - просто возвращаем число с нужным знаком
    if (divisor == LongInt("1")) {
        LongInt result = dividend;
        result.isNegative = resultIsNegative;
        return result;
    }

    // Будем строить результат по одной цифре
    LongInt result;
    result.digits.clear();
    result.isNegative = resultIsNegative;

    // Текущее частичное делимое (то, что мы сейчас делим)
    LongInt current;
    current.digits.clear();
    current.isNegative = false;

    // Проходим по каждой цифре делимого (как при делении в столбик)
    for (size_t i = 0; i < dividend.digits.size(); i++) {
        // Берем следующую цифру из делимого
        current.digits.push_back(dividend.digits[i]);
        current.removeLeadingZeros();  // Убираем возможные нули

        // Подбираем цифру частного: сколько раз делитель помещается в текущее число
        int quotientDigit = 0;
        while (current >= divisor) {
            current = current - divisor;  // Вычитаем пока можем
            quotientDigit++;  // Считаем сколько раз вычли
        }

        // Записываем найденную цифру в результат
        result.digits.push_back(quotientDigit);
    }

    // Убираем возможные нули в начале результата
    result.removeLeadingZeros();

    return result;
}

// Составные операторы - просто делаем операцию и присваиваем результат
LongInt& LongInt::operator+=(const LongInt& other) {
    *this = *this + other;
    return *this;
}

LongInt& LongInt::operator-=(const LongInt& other) {
    *this = *this - other;
    return *this;
}

LongInt& LongInt::operator*=(const LongInt& other) {
    *this = *this * other;
    return *this;
}

LongInt& LongInt::operator/=(const LongInt& other) {
    *this = *this / other;
    return *this;
}

// Версии для int - превращаем int в LongInt и используем готовые операторы
LongInt LongInt::operator+(int other) const {
    return *this + LongInt(other);
}

LongInt LongInt::operator-(int other) const {
    return *this - LongInt(other);
}

LongInt LongInt::operator*(int other) const {
    return *this * LongInt(other);
}

LongInt LongInt::operator/(int other) const {
    return *this / LongInt(other);
}

LongInt& LongInt::operator+=(int other) {
    *this = *this + other;
    return *this;
}

LongInt& LongInt::operator-=(int other) {
    *this = *this - other;
    return *this;
}

LongInt& LongInt::operator*=(int other) {
    *this = *this * other;
    return *this;
}

LongInt& LongInt::operator/=(int other) {
    *this = *this / other;
    return *this;
}

// ПРЕФИКСНЫЙ инкремент (++x) - увеличиваем и возвращаем новое значение
LongInt& LongInt::operator++() {
    *this = *this + LongInt("1");
    return *this;
}

// ПОСТФИКСНЫЙ инкремент (x++) - возвращаем старое значение, потом увеличиваем
LongInt LongInt::operator++(int) {
    LongInt old = *this;  // Запоминаем текущее значение
    *this = *this + LongInt("1");  // Увеличиваем
    return old;  // Возвращаем старое значение
}

// ПРЕФИКСНЫЙ декремент (--x)
LongInt& LongInt::operator--() {
    *this = *this - LongInt("1");
    return *this;
}

// ПОСТФИКСНЫЙ декремент (x--)
LongInt LongInt::operator--(int) {
    LongInt old = *this;
    *this = *this - LongInt("1");
    return old;
}

// Вывод в поток - просто выводим строковое представление
ostream& operator<<(ostream& os, const LongInt& num) {
    os << num.toString();
    return os;
}

// Ввод из потока - читаем строку и создаем из нее LongInt
istream& operator>>(istream& is, LongInt& num) {
    string str;
    is >> str;
    num = LongInt(str);  // Используем конструктор из строки
    return is;
}

// Преобразование в int (может потерять точность для больших чисел!)
LongInt::operator int() const {
    int result = 0;
    // Собираем число из цифр: каждая цифра добавляется к результату
    for (int digit : digits) {
        result = result * 10 + digit;
    }
    // Возвращаем с учетом знака
    return isNegative ? -result : result;
}

// Убираем нули в начале числа (но оставляем хотя бы одну цифру)
void LongInt::removeLeadingZeros() {
    size_t i = 0;
    // Пропускаем все нули, но оставляем последнюю цифру (даже если это 0)
    while (i < digits.size() - 1 && digits[i] == 0) {
        i++;
    }
    // Отрезаем все что до первого ненулевого элемента
    digits = vector<int>(digits.begin() + i, digits.end());
}

// Сравнение чисел по модулю (без учета знака)
int LongInt::compareAbsolute(const LongInt& other) const {
    // Сначала сравниваем по длине (больше цифр = больше число)
    if (digits.size() < other.digits.size()) {
        return -1;  // Мы меньше
    }
    if (digits.size() > other.digits.size()) {
        return 1;   // Мы больше
    }

    // При одинаковой длине сравниваем цифры слева направо
    for (size_t i = 0; i < digits.size(); i++) {
        if (digits[i] > other.digits[i]) {
            return 1;   // Мы больше
        }
        if (digits[i] < other.digits[i]) {
            return -1;  // Мы меньше
        }
    }

    return 0;  // Числа равны по модулю
}

// Возвращает число без знака (всегда положительное)
LongInt LongInt::absoluteValue() const {
    LongInt result = *this;
    result.isNegative = false;  // Просто убираем знак
    return result;
}

// Вычитание модулей (предполагается что this >= other)
LongInt LongInt::subtractAbsolute(const LongInt& other) const {
    LongInt result;
    result.digits.clear();
    result.isNegative = false;

    // Переворачиваем цифры для удобства вычитания
    vector<int> a_rev = digits;
    vector<int> b_rev = other.digits;
    reverse(a_rev.begin(), a_rev.end());
    reverse(b_rev.begin(), b_rev.end());

    int borrow = 0;  // "Заем" из старшего разряда

    // Вычитаем столбиком как в школе
    for (size_t i = 0; i < a_rev.size(); i++) {
        int digit_a = a_rev[i];
        int digit_b = (i < b_rev.size()) ? b_rev[i] : 0;

        // Вычитаем с учетом заема
        int diff = digit_a - digit_b - borrow;

        if (diff < 0) {
            diff += 10;  // Занимаем из старшего разряда
            borrow = 1;  // Запомнили что заняли
        }
        else {
            borrow = 0;  // Заем не нужен
        }

        result.digits.push_back(diff);
    }

    // Возвращаем цифры в нормальный порядок
    reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();

    return result;
}