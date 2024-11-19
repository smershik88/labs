#!/bin/bash

if [ -z "$1" ]
  then
    echo $'Ошибка, не указано имя исходного файла!\nУкажите имя исходного файла как параметр (без .cpp)...'
    exit 1
fi

echo $'Компиляция '$1'.cpp в '$1'...'
g++ -std=c++20 -Wall -Wextra -Wpedantic -pedantic $1.cpp -o$1