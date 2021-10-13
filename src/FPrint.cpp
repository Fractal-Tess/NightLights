#include <FPrint.hpp>

template <typename... Args>
void pprint(const Args &...a)
{
    using expander = int[];
    (void)expander{0, ((void)Serial.println(a), 0)...};
}

void print_uint32_t(uint32_t num)
{
    char rev[10];
    char *p = rev + 1;
    int i = 0;

    while (num > 0)
    {
        *p++ = (char)48 + (num % 10);
        num /= 10;
        i++;
    }

    p--;

    while (p > rev)
    {
        Serial.print(*p--);
    }
    Serial.println(i);
}