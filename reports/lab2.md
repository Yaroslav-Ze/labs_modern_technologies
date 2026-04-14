# Лабораторная работа №2. Git Flow, Code Review

## Цель работы

Познакомиться с (распространенным) вариантом организации совместной
работы над новой функциональностью и проведения инспекции кода.

## Этапы выполнения работы

### Подготовка репозитория

Была создана папка `labs`, в нее перемещена лабораторная работа 1 по Структурам данных. 

Git классифицирует файлы на три группы: отслеживаемые, игнорируемые и неотслеживаемые. Изначально нет никаких отслеживаемых или игнорируемых файлов, поэтому набор неотслеживаемых файлов пуст.  Временные файлы обычно не должны отслеживаться, как файлы исходного кода. Чтобы Git игнорировал файлы в каталоге, нужно просто добавить имя этого файла в специальный файл `.gitignore`. Чтобы проигнорировать любой файл, просто нужно добавить его имя в файл `.gitignore`, который находится в этом же каталоге. Также можно игнорировать файлы где угодно, добавив его в файл `.gitignore`, который находится в корневом каталоге репозитария. Кроме того, Git позволяет создавать файл `.gitignore` в любом каталоге вашего репозитария. Каждый такой файл влияет на свой каталог и все подкаталоги. Правила `.gitignore` каскадные: вы можете переопределить правила в каталоге более высокого уровня, включив инвертированный шаблон (с использованием ! в начале правила) в одном из подкаталогов. Источник: Фишерман Леонид Владленович "Git. Практическое руководство. Управление и контроль версий в разработке программного обеспечения".

Был создан файл `.gitignore` со следующим содержимым:

```
out/

*.o
*.out
*.obj
```

Из папки `labs` были добавлены в индекс все файлы с помощью команды `git add .`, благодаря файлу `.gitignore` в индекс не вошли все временные файлы. Однако в командной строке вывелось предупреждение о том, что все переходы на новую строку в стиле Linux будут изменены на переходы в стиле Windows:

```
warning: in the working copy of 'labs/lab1/Makefile', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/input.txt', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/barrel.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/barrel.hpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/lab1.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/matrix.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/matrix.hpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/rect.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/rect.hpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/string.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/string.hpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/wrap.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/src/wrap.hpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/tests/test_bounding_rect.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/tests/test_rect_basic_methods.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/tests/test_rect_operations.cpp', LF will be replaced by CRLF the next time Git touches it
warning: in the working copy of 'labs/lab1/tests/test_rect_properties.cpp', LF will be replaced by CRLF the next time Git touches it
```

Команда `git status` отобразила следующее:

```
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   labs/.gitignore
        new file:   labs/lab1/0
        new file:   labs/lab1/Makefile
        new file:   labs/lab1/input.txt
        new file:   labs/lab1/src/barrel.cpp
        new file:   labs/lab1/src/barrel.hpp
        new file:   labs/lab1/src/lab1.cpp
        new file:   "labs/lab1/src/lab1.cpp\357\200\272Zone.Identifier"
        new file:   labs/lab1/src/matrix.cpp
        new file:   labs/lab1/src/matrix.hpp
        new file:   labs/lab1/src/rect.cpp
        new file:   labs/lab1/src/rect.hpp
        new file:   labs/lab1/src/string.cpp
        new file:   labs/lab1/src/string.hpp
        new file:   labs/lab1/src/wrap.cpp
        new file:   labs/lab1/src/wrap.hpp
        new file:   labs/lab1/tests/test_bounding_rect.cpp
        new file:   labs/lab1/tests/test_rect_basic_methods.cpp
        new file:   labs/lab1/tests/test_rect_operations.cpp
        new file:   labs/lab1/tests/test_rect_properties.cpp
```

Был сделан коммит, а потом перенос в удаленный репозиторий с помощью команды `git push origin main`. 

### Защита веток

Правила защиты ветвей — это функция систем контроля версий, таких как GitHub. Они позволяют администраторам репозитория устанавливать определенные условия, которые должны быть выполнены до слияния изменений в конкретные ветви. Эти правила защищают ветви, в частности, основную `main` ветвь, от непроверенных изменений и гарантируют соблюдение определенных рабочих процессов, таких как проверка кода и проверка статуса.

Вот некоторые распространенные настройки:

1. Требовать запроса на слияние перед объединением : Включение этой настройки гарантирует, что все изменения должны проходить через запрос на слияние, что упрощает соблюдение рабочих процессов проверки кода.
2. Требование одобрения : Вы можете установить требование, согласно которому запросы на слияние (pull requests) должны быть одобрены определенным количеством рецензентов (например, как минимум одним или двумя). Это особенно важно для обеспечения качества кода и обмена знаниями.
3. Требовать прохождения проверок статуса перед слиянием : Эта опция гарантирует, что определенные автоматизированные проверки, такие как тесты непрерывной интеграции (CI) или линтеры, должны пройти перед слиянием запроса на слияние. Вы можете выбрать, какие проверки следует применять.
4. Требовать подписанных коммитов : Если безопасность вызывает опасения, требование подписанных коммитов гарантирует, что каждый коммит будет проверен с помощью ключа GPG участника.
5. Требовать линейную историю : Включение этой опции предотвращает слияние коммитов, обеспечивая более чистую историю коммитов, где каждое изменение воспроизводится последовательно в ветке.
6. Не разрешайте принудительную отправку изменений : это предотвратит принудительную отправку изменений в защищенную ветку со стороны участников проекта, что может привести к перезаписи истории коммитов и потенциальной потере важных данных.
7. Не разрешать удаление : Эта опция гарантирует, что ветка не может быть случайно удалена. Она особенно полезна для защиты веток main или release.
8. Требование завершения обсуждения перед слиянием : GitHub позволяет обеспечить, чтобы все комментарии и запрошенные изменения в запросе на слияние были учтены до его слияния.

(Источник)[https://graphite.com/guides/how-to-set-up-branch-protection-rules-github]

Был открыт мой репозиторий на GitHub. В разделе `Branches` раздела `Settings` была выбрана кнопка `Add classic branch protection rule`. В поле `Branch name pattern` было введено `main`. Была поставлена галочка у поля `Require a pull request before merging`, далее кнопка с сохранением. Однако на GitHub было написано следующее: `Your rules won't be enforced on this private repository until you move to a GitHub Team or Enterprise organization account.`, оказалось, что такие методы защиты ветки доступны бесплатно только для публичных репозиториев. В "опасной зоне" репозиторий был изменен с приватного на публичный. Защита веток стала доступна. 

Был создан файл `test.txt` в папке с лабораторными по структурам. Первые два коммита, вопреки ожиданиям, увенчались успехом, на командной строке вывелось:

```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 500 bytes | 500.00 KiB/s, done.
Total 4 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote: Bypassed rule violations for refs/heads/main:
remote:
remote: - Changes must be made through a pull request.
remote:
To github.com:Yaroslav-Ze/labs_modern_technologies.git
   2aa8b7e..480d077  main -> main
```

Оказалось, что была забыта галочка около поля, запрещающего администратору пушить в защищенную ветку. Таким образом, git лишь сообщал о нарушении правил, но оставлял их безнаказанными. После была поставлена необходимая галочка в поле `Do not allow bypassing the above settings`. После очередного коммита и попытки пуша вывелось следующее, пуш был запрещен:

```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 526 bytes | 526.00 KiB/s, done.
Total 4 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote: error: GH006: Protected branch update failed for refs/heads/main.
remote:
remote: - Changes must be made through a pull request.
To github.com:Yaroslav-Ze/labs_modern_technologies.git
 ! [remote rejected] main -> main (protected branch hook declined)
error: failed to push some refs to 'github.com:Yaroslav-Ze/labs_modern_technologies.git'
```

Были сделаны откаты коммитов, а файл `test.txt` удален. Далее была создана новая ветка при помощи `git checkout -b test` и сразу запушена на github с помощью `git push origin test`, никаких преград не возникло. 

### Запросы на слияние

Были внесены изменения в lab1.cpp, закоммичены и запушены. На GitHub в разделе Pull requests была нажата кнопка `Compare & pull request`, написан заголовок и нажата кнопка `Create pull request`. 

Далее были последовательно нажаты кнопки `Merge pull request`, `Confirm merge`, `Delete branch`, для слияния и удаления уже ненужной ветки. 

В командной строке ветка была переключена на `main`, с помощью команды `git pull origin main` были скачаны последние изменения с GitHub, а потом удалена ветка `test` с помощью `git branch -d test`, после пулла на командной строке вывелось:

```
remote: Enumerating objects: 7, done.
remote: Counting objects: 100% (7/7), done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 1.09 KiB | 93.00 KiB/s, done.
From github.com:Yaroslav-Ze/labs_modern_technologies
 * branch            main       -> FETCH_HEAD
   480d077..64322ec  main       -> origin/main
Updating bada4d0..64322ec
Fast-forward
 labs/lab1/src/lab1.cpp | 2 ++
 labs/test.txt          | 3 +++
 2 files changed, 5 insertions(+)
 create mode 100644 labs/test.txt
```

### Code Review

Была создана отдельная ветка для лабораторной номер 1 по структурам данных. Внесены некоторые изменения, закоммичены и запушены на github. Был создан новый Pull Request. Преподаватель был отмечен как Reviewer. Работа с замечаниями......

В ходе работы над первой лабораторной работой по "Современным технологиям разработки ПО" был также создан PR, преподаватель был отмечен как Reviewer. Через некоторое количество времени было получено письмо на указанную почту от GitHub, PR был одобрен ревьюером, поставлена метка `Approve`. Аналогично с предыдущим этапом  `"Запросы на слияние"`, ветка была смёрджена в основную и впоследствии удалена.