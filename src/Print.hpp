#pragma once

template <typename... Args>
void pprint(const Args &...a)
{
    using expander = int[];
    (void)expander{0, ((void)Serial.println(a), 0)...};
}
