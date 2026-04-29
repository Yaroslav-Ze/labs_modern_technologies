# Лабораторная работа №6. Простые CI-CD пайплайны

## Цель работы

Познакомиться с простыми средствами автоматизации процесса задач
разработки в рамках работы с системой контроля версий.

## Этапы выполнения работы

### Базовые хуки в Git на стороне клиента

Git-хуки — скрипты, которые автоматически запускаются при наступлении определённых событий в жизненном цикле репозитория, таких как commit, push, merge, rebase и других операций. Такие действия разделяются на две группы: 
  - клиентские (хуки хранятся локально на компьютере разработчика и выполняются только для конкретного разработчика, то есть они невидимы для остальных); 
  - серверные (файл един для всех).

Все клиентские хуки хранятся по пути `.git/hooks/`. Список "сэмплов" (примеров) возможных хуков, название хука показывает, когда именно он запускается и к чему относится:
  - `applypatch-msg` — проверяет сообщение коммита при применении патча (`git am`)
  - `commit-msg` — проверяет текст сообщения коммита
  - `fsmonitor-watchman` — ускоряет отслеживание изменений файлов (интеграция с Watchman)
  - `post-update` — выполняется после обновления веток на сервере
  - `pre-applypatch` — выполняется перед применением патча
  - `pre-commit` — проверяет файлы перед созданием коммита
  - `pre-merge-commit` — выполняется перед созданием merge-коммита
  - `pre-push` — выполняется перед отправкой изменений (`git push`)
  - `pre-rebase` — выполняется перед `git rebase` (можно остановить)
  - `pre-receive` — выполняется на сервере до принятия `push` (можно отклонить)
  - `prepare-commit-msg` — изменяет сообщение коммита перед редактированием пользователем
  - `push-to-checkout` — управляет обновлением рабочей директории при `push`
  - `sendemail-validate` — проверяет email перед отправкой патчей (`git send-email`)
  - `update` — проверяет обновление каждой ветки при `push` на сервер
Среди них те, которые способны прервать действие:
  * `applypatch-msg` — может остановить применение патча
  * `pre-applypatch` — может остановить применение патча
  * `pre-commit` — может остановить создание коммита
  * `commit-msg` — может остановить коммит из-за плохого сообщения
  * `pre-merge-commit` — может остановить merge-коммит
  * `pre-rebase` — может остановить `rebase`
  * `pre-push` — может остановить `push`
  * `pre-receive` — может отклонить весь `push`
  * `update` — может отклонить обновление конкретной ветки

Пока в папке с хуками какой-либо хук имеет `.sample` в конце, он исполняться не будет. Информация черпалась [отсюда](https://git-scm.com/book/ru/v2/%D0%9D%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-Git-%D0%A5%D1%83%D0%BA%D0%B8-%D0%B2-Git) и [отсюда](https://habr.com/ru/companies/2gis/articles/838966/).

В ходе лабораторной работы, был добавлен хук, который проверяет код, добавляемый в коммит, на предмет наличия запрещенных слов или паттернов. Основы синтаксиса bash были подчерпнуты [здесь](https://skillbox.ru/media/code/kak-polzovatsya-bash-ekspressrukovodstvo-dlya-nachinayushchikh/), а также [здесь](https://gitverse.ru/blog/articles/development/117-osnovy-bash-v-linux-kak-napisat-svoj-pervyj-skript-na-bash). 

Чтобы создать файл хука, необходимо создать файл, имя которого будет соответствовать одному из выше приведенных сэмплов, для первого хука -- `pre-commit`, так как перед созданием коммита будет проверяться содержимое файла. С помощью команды `cd .git/hooks`, а также `touch pre-commit` был создан нужный файл будущего хука. Далее -- `code pre-commit`, чтобы редактировать в VS Code. Код хука, где `-q` - ничего не выводит на консоль, `--cached` -- изменения идущие в коммит, `grep` -- поиск текста в файле:
```
#!/bin/sh
# специальная инструкция в начале текстового файла, которая сообщает операционной системе, 
# какую программу нужно использовать для выполнения команд в этом файле.

echo "Хук для проверки на наличие запрещенки в коммите"

if git diff --cached | grep -q "например-пароль"; then
  echo "Найден пароль"
  exit 1
fi

if git diff --cached | grep -q "токен-например"; then
  echo "Найден токен-например"
  exit 1
fi

echo "Запрещенки нет!"
exit 0
```

Уточнение: при первой (мало обдуманной) попытке привести листинг кода хука, и дальнейшего коммита - ничего не вышло, ибо в тексте отчета были найдены запрещенные слова. Вывод консоли:
```
$ git commit -m "Коммит первого хука"
Хук для проверки на наличие запрещенки в коммите
Найден пароль
```
Успешная попытка:
```
$ git commit -m "Коммит первого хука"
Хук для проверки на наличие запрещенки в коммите
Запрещенки нет!
[modern-tec-6 74ac1bd] Коммит первого хука
 1 file changed, 58 insertions(+)
```

Был добавлен второй хук, проверяющий длину сообщения коммита, где `cat "$1"` - прочитать файл с сообщением, `${#msg}` - длина строки сообщения, `-lt` - меньше чем:
```
#!/bin/sh

msg=$(cat "$1")

echo "Проверка сообщения коммита"

if [ ${#msg} -lt 5 ]; then
  echo "Сообщение слишком короткое"
  exit 1
fi

echo "Сообщение одобрено"
exit 0
```
Вывод консоли в неудачном случае:
```
$ git commit -m "Норм"
Хук для проверки на наличие запрещенки в коммите
Запрещенки нет!
Проверка сообщения коммита
Сообщение слишком короткое
```
В удачном:
```
$ git commit -m "Добавлен второй хук"
Хук для проверки на наличие запрещенки в коммите
Запрещенки нет!
Проверка сообщения коммита
Сообщение одобрено
[modern-tec-6 3c6c3d7] Добавлен второй хук
 1 file changed, 29 insertions(+)

```

### Хуки Git на стороне сервера

С помощью команды ` git clone --bare lab_1 server` был создан клон репозитория, клон является "голым" репозиторием:

> Bare repository (голый репозиторий) в Git — это репозиторий, у которого нет рабочей директории (working directory), что делает его идеальным для хранения версий проекта на сервере и взаимодействия между разработчиками.
>
> Голое (bare) хранилище называются так потому, что у него нет рабочего каталога. Оно содержит только файлы, которые обычно скрыты в подкаталоге .git. Другими словами, голое хранилище содержит историю изменений, но не содержит снимка какой-либо определенной версии.
>
> Голое хранилище играет роль, похожую на роль основного сервера в централизованной системе управления версиями: это дом вашего проекта. Разработчики клонируют из него проект и закачивают в него свежие официальные изменения. Как правило, оно располагается на сервере, который не делает почти ничего кроме раздачи данных. Разработка идет в клонах, поэтому домашнее хранилище может обойтись и без рабочего каталога. [Источник](http://www-cs-students.stanford.edu/~blynn/gitmagic/intl/ru/ch04.html).

Был добавлен этот репозиторий в качестве удаленного с помощью команды `git remote add server ../server`. Сделан коммит, ветка запушена в удаленный репозиторий-сервер с помощью команды `git push server modern-tec-6`. Пуш удался. 

Конвертация из `.md` в `.html` возможна с помощью pandoc. Pandoc — это универсальный инструмент командной строки для конвертации текстовых документов из одного формата в другой. Скачать его можно [отсюда](https://pandoc.org/installing.html). 

Был создан хук `post-receive` в голом репозитории. 
```
#!/bin/sh
echo ""
echo "post-receive запущен"

while read oldrev newrev ref
# пока Git передаёт строки об обновлениях, читать их и обрабатывать
do
  git show "$newrev:reports/lab6.md" | pandoc -o lab6.html

  echo "Создан html"
  echo ""
done
```
Был сделан коммит, запушен на "сервер". Html успешно был создан. Последние действия были повторены еще раз, при перезагрузки html файла изменения отобразились. 

### Сборка с помощью CMake

Из терминала wsl был установлен cmake с помощью команды `sudo apt install cmake`. Cmake доступен. 

> CMake — кроcсплатформенная утилита для автоматической сборки программы из исходного кода. 
> 
> Для того что бы собрать проект средствами CMake, необходимо в корне дерева исходников разместить файл CMakeLists.txt, хранящий правила и цели сборки. 
>
> Файл CMakeLists.txt служит скриптом (рецептом, сценарием) сборки проекта. Обычно один такой файл собирает все исходники в своём каталоге и в подкаталогах, при этом подкаталоги могут содержать, а могут не содержать дочерние файлы CMakeLists.txt. С точки зрения IDE, таких как CLion или Visual Studio, файл CMakeLists.txt также служит проектом, с которым работает программист внутри IDE.
>
> В cmake есть *цель* (target) - компонент, который следует собрать. Компонент может быть исполняемым файлом, так и статической либо динамической библиотекой.
>
> В cmake есть *проект* (project) - это набор компонентов, по смыслу похожий на Solution в Visual Studio.
>
> В cmake есть *флаги* (flags) - это аргументы командной строки для компилятора, компоновщика и других утилит, вызываемых при сборке.
>
> В cmake есть переменные, и в процессе интерпретации файла CMakeLists.txt система сборки cmake вычисляет ряд встроенных переменных для каждой цели, тем самым получая флаги. Затем cmake создаёт вторичный скрипт сборки, который будет напрямую вызывать компилятор, компоновщик и другие утилиты с вычисленными флагами. 
>
> [Источник](https://ps-group.github.io/cxx/cmake_cheatsheet#wow0).

* `cmake_minimum_required` — задаёт минимальную версию CMake
```
cmake_minimum_required(VERSION 3.10)
```

* `project` — объявляет проект
```
project(MyProject)
```

* `add_executable` — создаёт исполняемый файл
```
add_executable(app main.cpp)
```

* `add_library` — создаёт библиотеку
```
add_library(lib file.cpp)
```

* `target_link_libraries` — связывает цель с библиотеками
```
target_link_libraries(app lib)
```

* `target_include_directories` — добавляет путь к заголовочным файлам
```
target_include_directories(lib PUBLIC include)
```

* `add_subdirectory` — подключает подпроект (другую папку с CMakeLists.txt)
```
add_subdirectory(tests)
```

* `set` — создаёт переменную
```
set(SOURCES main.cpp file.cpp)
```

* `message` — выводит сообщение при конфигурации
```
message("Configuring project")
```

* `include_directories` — добавляет include-пути
```
include_directories(include)
```

* `link_directories` — добавляет путь к библиотекам
```
link_directories(lib)
```

* `add_definitions` — добавляет макросы компиляции
```
add_definitions(-DDEBUG)
```

* `target_compile_definitions` — добавляет макросы для конкретной цели
```
target_compile_definitions(app PRIVATE DEBUG)
```

* `target_compile_options` — задаёт флаги компилятора
```
target_compile_options(app PRIVATE -Wall)
```

* `file` — работает с файлами (поиск, копирование и др.)
```
file(GLOB SRC "*.cpp")
```

* `enable_testing` — включает поддержку тестов
```
enable_testing()
```

* `add_test` — добавляет тест
```
add_test(NAME test1 COMMAND test_app)
```

* `find_package` — ищет внешние библиотеки
```
find_package(Threads REQUIRED)
```

* `if` — условие
```
if(WIN32)
  message("Windows")
endif()
```

* `foreach` — цикл
```
foreach(file ${SOURCES})
  message(${file})
endforeach()
```

Make-файл лабораторной 2 по сд был переписан на Cmake.

<details>
<summary>Исходник:</summary>

```
obj = out/string.o out/base.o

out/debug.out: $(obj) src/lab2.cpp
	g++ -g -o out/debug.out src/lab2.cpp $(obj)

out/leaks.out: $(obj) src/lab2.cpp
	g++ -g -o out/leaks.out src/lab2.cpp $(obj) -fsanitize=address

out/%.o: src/%.cpp src/%.hpp
	g++ -g -c -o $@ $<

debug: out/debug.out
	gdb out/debug.out

leaks: out/leaks.out
	./out/leaks.out

out/test_%.out: tests/test_%.cpp $(obj)
	g++ -g -o $@ $< $(obj) -fsanitize=address

test_%: out/test_%.out
	./$<

tests: \
	test_BF \
	test_B32 \
	test_RLE \
	test_B32_2 \
	test_RLE_2 \
	test_COMP1 \
	test_COMP2

.PHONY: clean

clean:
	-rm -f out/*.o out/debug.out out/leaks.out out/test_*.out *.bin
```
</details>

<details>
<summary>Получившийся корневой CMakeLists.txt</summary>

```
cmake_minimum_required(VERSION 3.10)

project(lab2)

add_library(lib src/string.cpp src/base.cpp)

target_include_directories(lib PUBLIC src)
# где искать заголовочные файлы

add_executable(debug_out src/lab2.cpp)

target_link_libraries(debug_out lib)

target_compile_options(debug_out PRIVATE -g)

add_executable(leaks_out src/lab2.cpp)

target_link_libraries(leaks_out lib)

target_compile_options(leaks_out PRIVATE -g -fsanitize=address)
target_link_options(leaks_out PRIVATE -fsanitize=address)

enable_testing()
add_subdirectory(tests)
```
</details>

<details>
<summary>Получившийся для тестов CMakeLists.txt</summary>

```
set(TESTS BF B32 RLE B32_2 RLE_2 COMP1 COMP2)

foreach(TEST_NAME ${TESTS})
    add_executable(test_${TEST_NAME} test_${TEST_NAME}.cpp)

    target_link_libraries(test_${TEST_NAME} lab2_lib)

    add_test(NAME test_${TEST_NAME} COMMAND test_${TEST_NAME})
endforeach()
```
</details>

Команда `cmake ..` выполнила конфигурацию проекта, прочитав файл CMakeLists.txt из родительской директории и сгенерировав файлы сборки (например, Makefile) в текущей папке. Далее, команда `cmake --build .` выполнила сборку проекта на основе ранее сгенерированных файлов сборки. 

<details>
<summary>Вывод консоли:</summary>

```
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/yawr/Projects/lab2/lab2/out
[ 14%] Built target lib
[ 23%] Built target debug_out
[ 33%] Built target leaks_out
[ 38%] Building CXX object tests/CMakeFiles/test_BF.dir/test_BF.cpp.o
[ 42%] Linking CXX executable test_BF
[ 42%] Built target test_BF
[ 47%] Building CXX object tests/CMakeFiles/test_B32.dir/test_B32.cpp.o
[ 52%] Linking CXX executable test_B32
[ 52%] Built target test_B32
[ 57%] Building CXX object tests/CMakeFiles/test_RLE.dir/test_RLE.cpp.o
[ 61%] Linking CXX executable test_RLE
[ 61%] Built target test_RLE
[ 66%] Building CXX object tests/CMakeFiles/test_B32_2.dir/test_B32_2.cpp.o
[ 71%] Linking CXX executable test_B32_2
[ 71%] Built target test_B32_2
[ 76%] Building CXX object tests/CMakeFiles/test_RLE_2.dir/test_RLE_2.cpp.o
[ 80%] Linking CXX executable test_RLE_2
[ 80%] Built target test_RLE_2
[ 85%] Building CXX object tests/CMakeFiles/test_COMP1.dir/test_COMP1.cpp.o
[ 90%] Linking CXX executable test_COMP1
[ 90%] Built target test_COMP1
[ 95%] Building CXX object tests/CMakeFiles/test_COMP2.dir/test_COMP2.cpp.o
[100%] Linking CXX executable test_COMP2
[100%] Built target test_COMP2
```
</details>

Теперь, в собранном проекте, можно, например, запустить тесты с помощью `ctest`

<details>
<summary>Вывод консоли после тестов:</summary>

```
Test project /home/yawr/Projects/lab2/lab2/out
    Start 1: test_BF
1/7 Test #1: test_BF ..........................   Passed    0.00 sec
    Start 2: test_B32
2/7 Test #2: test_B32 .........................   Passed    0.01 sec
    Start 3: test_RLE
3/7 Test #3: test_RLE .........................   Passed    0.01 sec
    Start 4: test_B32_2
4/7 Test #4: test_B32_2 .......................   Passed    0.01 sec
    Start 5: test_RLE_2
5/7 Test #5: test_RLE_2 .......................   Passed    0.01 sec
    Start 6: test_COMP1
6/7 Test #6: test_COMP1 .......................   Passed    0.02 sec
    Start 7: test_COMP2
7/7 Test #7: test_COMP2 .......................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.08 sec
```
</details>

### Автоматизация задач CMake в git

Была создана ветка `dev`. В хук `pre-commit` было добавлено:
```
if [ "$branch" != "dev" ]; then
  exit 0
fi

mkdir -p build
cd build || exit 1

cmake .. || {
  echo "Ошибка конфигурации CMake"
  exit 1
}

cmake --build . || {
  echo "Ошибка сборки"
  exit 1
}

ctest || {
  echo "Тесты не удались коммит отменён"
  exit 1
}

echo "Сборка и тесты прошли успешно"
```

Хук был проверен при выполнении коммита в ветке dev, а также merge. В обоих случаях автоматически выполнялась сборка проекта и запуск тестов, при ошибках процесс прерывался. 

Хук был дополнен фрагментом о проверке сборке библиотеки.
```
cmake --build . --target lib || {
  echo "Библиотека не собирается"
  exit 1
}
# собрать не полностью, но только библиотеку
```

### Автоматизация с помощью Github Actions
