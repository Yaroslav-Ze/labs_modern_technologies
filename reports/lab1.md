# Лабораторная работа №1. Базовая работа с git.

## Цель работы

Познакомиться с базовыми операциями при работе с git, изучить необходимые
инструменты для работы в рамках курса.

## Этапы выполнения работы

### Установка и настройка

Программа `git` была скачана с официального сайта [git-scm.com](git-scm.com) и установлена с настройками по умолчанию. 
После команды `git --version` на консоль вывелось: `git version 2.53.0.windows.1`. 
Далее были введены команды `git config --global user.name "Yaroslav Zelepukhin"` и `git config --global user.email "yarzeltan@gmail.com"`, где флаг `--global` определяет, что настройки будут использованы для всех проектов на компьютере. 
С помощью `git --help` на консоль выводится список основных команд, разбитый на группы. Далее приведен список наиболее часто используемых команд и их значения, источник - Фишерман Леонид Владленович "Git. Практическое руководство. Управление и контроль версий в разработке программного обеспечения".

`add` Добавляет содержимое файла в индекс

`bisect` Выполняет бинарный поиск ошибки по истории фиксаций

`branch` Выводит, создает или удаляет ветки

`checkout` Проверяет и переключает на ветку

`clone` Клонирует репозиторий в новый каталог

`commit` Записывает изменения в каталог (фиксация)

`diff` Показывает изменения между фиксациями, рабочими деревьями и т.д.

`fetch` Загружает объекты и ссылки из другого репозитария

`grep` Выводит строки, соответствующие шаблону

`init` Создает пустой репозиторий git или переинициализирует существующий

`log` Показывает журналы фиксации

`merge` Объединяет две или больше истории разработки

`mv` Перемещает или переименовывает файл, каталог или символическую ссылку

`pull` Получает изменения из удаленного репозитария и объединяет их с локальным репозитарием или локальной веткой

`push` Загружает изменения из вашего локального репозитория в удаленный

`rebase` Строит ровную линию фиксаций

`reset` Сбрасывает текущий HEAD в указанное состояние

`rm` Удаляет файлы из рабочего дерева и из индекса

`show` Показывает различные типы объектов

`status` Показывает состояние рабочего дерева

`tag` Создает, выводит, удаляет или проверяет тег объекта, подписанного с GPG  

### Начало работы с новым проектом

Была создана новая директория по адресу `C:\Users\Тот Самый\Documents\Политех 2025-2029\2 семестр\Современные тех раз ПО\lab_1`. С помощью команды `git init` был создан пустой репозиторий git, командная строка вывела: `Initialized empty Git repository in C:/Users/Тот Самый/Documents/Политех 2025-2029/2 семестр/Современные тех раз ПО/lab_1/.git/`. 
В папке создалась скрытая подпапка `.git`. В репозитории был создан файл `README.md`, директория `reports` и файл `reports/lab1.md`. 
Основные синтаксические элементы языка Markdown:
1. **Жирный текст**:  `**Жирный текст**`
2. *Курсив*: `*Курсив*`
3. > Цитата: 
`> Цитата`
4. Заголовки: `#Заголовки \n ##Заголовки \n ###Заголовки`
5. Список: `1. первый \n 2. второе`
6. `Код`: ``` `Код` ```
7. [Ссылки](https://www.markdownguide.org/cheat-sheet/): `[Ссылки](https://www.markdownguide.org/cheat-sheet/)`

Был сделан первый коммит. С помощью команды `git status` в командной строке отобразилось:

```
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md
        reports/

nothing added to commit but untracked files present (use "git add" to track)
```

Далее с помощью команды `git add .` подготовили к коммиту все файлы в папке, с помощью команды `git status` в командной строке отобразилось:

```
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   README.md
        new file:   reports/lab1.md
```

Сделан первый коммит с помощью команды `git commit -m "Первый коммит, readme.md и пустой lab1.md"`. Флаг `-m` позволяет написать сообщение прямо в команде. В командной строке отобразилось:

```
[main (root-commit) 99bcd4f] Первый коммит, readme.md и пустой lab1.md
 2 files changed, 4 insertions(+)
 create mode 100644 README.md
 create mode 100644 reports/lab1.md
```

### Отслеживание состояния кода

Выполнена команда `git status`, она отображает состояние директории, есть ли незакоммиченные файлы/папки. Ее вывод:

```
On branch main
nothing to commit, working tree clean
```

Выполнена команда `git diff`. Командная строка ничего не вывела. Эта команда отображает различия между файлами, какие произошли изменения.
Заметки по предыдущим этапам были перенесены в `lab1.md`, после чего была выполнена команда `git status`, ее вывод показал, что в файле `lab1.md` произошли изменения и файл не готов к коммиту (красный):

```
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   reports/lab1.md

no changes added to commit (use "git add" and/or "git commit -a")
```

После была выполнена команда `git diff`, она вывела на консоль текст заметок перенесенных в файл `lab1.md`, то есть отобразила сами изменения. Ее вывод:

```
diff --git a/reports/lab1.md b/reports/lab1.md
index e69de29..6267525 100644
--- a/reports/lab1.md
+++ b/reports/lab1.md
@@ -0,0 +1,110 @@
+# Лабораторная работа №1. Базовая работа с git.
+
+## Цель работы
.....
```

Изменения в файле были добавлены в индекс с помощью команды `git add reports\lab1.md`. В свою очередь, `git status` вывела, файл `lab1.md` зеленый, то есть готов и войдет в следующий коммит:

```
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   reports/lab1.md
```

Были внесены изменения в файл `README.md`. С помощью команды `git diff -- README.md` отследили изменения в файле, где `--` означает, что необходимо отобразить изменения только для этого файла. Вывод команды:

```
diff --git a/README.md b/README.md
index 4d8d4de..9308a92 100644
--- a/README.md
+++ b/README.md
@@ -1,4 +1,6 @@
 ## Лабораторные работы по дисциплине *"Современные технологии разработки программного обеспечения"*

 **Студент:** Зелепухин Ярослав Олегович
-**Группа:** 5130201/50302
\ No newline at end of file
+**Группа:** 5130201/50302
+
+### Новая глава
\ No newline at end of file
```

Был сделан второй коммит, в него вошли только изменения в файле `lab1.md`, с помощью комманды `git commit -m "Второй коммит, добавлены измения ТОЛЬКО в lab1.md"`. При этом команда `git status` все еще отображала красным файл `README.md`, так как он не был подготовлен к коммиту. Вывод команды:

```
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

Была использована команда `git restore README.md`, после нее соответствующий файл откатился до последнего коммита, из него изчезла добавленная ранее строка.  
Был удален файл `lab1.md`. После этого была использована команда  `git status`, вывод которой указал, что файл `lab1.md` был удален. Git зафиксировал отсутствие файла, который раньше был под версионным контролем.

```
On branch main
Changes not staged for commit:
  (use "git add/rm <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        deleted:    reports/lab1.md
```

Далее с помощью команды `git restore reports\lab1.md` файл был восстановлен до последнего коммита. То есть, эта команда позволяет не только восстанавливать изменения, но и восстанавливать удаленные файлы из последнего коммита.

### Ветвление версий

После команды `git branch` на консоли вывелось: `* main`. Была создана новая ветка с помощью команды `git branch lab1-1`. Далее после команды `git checkout lab1-1` на консоли отобразилось:

```
M       reports/lab1.md
Switched to branch 'lab1-1'
```

После очередной команды `git branch` было выведено следующее:

```
* lab1-1
  main
```

Далее в настоящий протокол были внесены дополнения по предыдущим шагам, после чего он был закоммичен. При переключении на ветку `main` все эти изменения пропали из файла,  так как в этой ветке не было этих изменений. Далее были внесены изменения в файл `README.md`, но не закоммичены. Однако попытка переключиться на ветку `lab1-1` прошла испешно, командная строка вывела лишь: 

```
M       README.md
Switched to branch 'lab1-1'
```

Не получив ожидаемой ошибки, были проделаны следующие шаги. Был изменен файл `README.md` в ветке `main`, после - закоммичен. Далее, после переключения на ветку `lab1-1`, был изменен файл `README.md` в этой ветке, изменения были закоммичены. Далее после команды `git checkout main` были внесены изменения в файл `README.md`, но не закоммичены. После попытки `git checkout lab1-1` на консоль вывелось:

```
error: Your local changes to the following files would be overwritten by checkout:
        README.md
Please commit your changes or stash them before you switch branches.
Aborting
```

Git защитил от попытки переключения ветки без коммита, потому что в ином случае незакоммиченные изменения стерлись бы. Поэтому git просит закоммитить перед перключением веток файл `README.md`. После всех этих процедур версии были откатаны в прошлые, одинаковые состояния.

### Слияние веток, конфликты

Была выполнена команда `git merge lab1-1`, ее вывод:

```
Already up to date.
```

Далее в ветке `main` были сделаны изменения в файле `README.md` и закоммичены. После ветка была переключена на `lab1-1`, внесены изменения, которые вы читаете сейчас, в файл `reports\lab1.md`, изменен заголовок в `README.md` и добавлена строка, закоммичено всё. Снова было переключение веток. После переключения обратно на ветку `main` команда `git merge lab1-1` привела к конфликту, так как одни и те же строки были изменены в двух ветках и гит не знает какую из них выбрать за правильную. На консоли отобразилось:

```
Auto-merging README.md
CONFLICT (content): Merge conflict in README.md
Automatic merge failed; fix conflicts and then commit the result.
```

В самом файле `README.md` было следующее содержимое:

```
<<<<<<< HEAD
## ЛАбы по смрпо

**Студент:** Зелепухин Ярослав Олегович
**Группа:** 5130201/50302
=======
## Заголовок в ветке lab1-1

**Студент:** Зелепухин Ярослав Олегович
**Группа:** 5130201/50302

строка из ветки лаб1
>>>>>>> lab1-1
```

Вручную содержимое файла было восстановлено к исходному варианту и сделан его коммит. Конфликт был разрешен. Ветка `lab1-1` была удалена с помощью команды `git branch -d lab1-1`, где флаг `-d` отвечает за безопасное удаление ветки, это возможно, когда ветка полностью слита в текущую ветку. На консоли напечаталось: 

```
Deleted branch lab1-1 (was e723e1f).
```

### Работа с удаленным репозиторием

Был создан аккаунт на GitHub. Был сгенерирован ssh-ключ с помощью команды `ssh-keygen -t ed25519 -C "yarzeltan@gmail.com"` и вставлен на github. Был создан пустой репозиторий на github. Репозиторий был указан в качестве удаленного для локального с помощью `git remote add origin git@github.com:Yaroslav-Ze/labs_modern_technologies.git`. Данные были отправлены на удаленный репозиторий с помощью команды `git push -u origin main`. Вывод консоли:

```
The authenticity of host 'github.com (140.82.121.4)' can't be established.
ED25519 key fingerprint is: SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added 'github.com' (ED25519) to the list of known hosts.
Enumerating objects: 33, done.
Counting objects: 100% (33/33), done.
Delta compression using up to 12 threads
Compressing objects: 100% (28/28), done.
Writing objects: 100% (33/33), 7.90 KiB | 1.97 MiB/s, done.
Total 33 (delta 5), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (5/5), done.
To github.com:Yaroslav-Ze/labs_modern_technologies.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

После этого все данные появились на github.

### Синхронизация с удаленным репозиторием

Был создан клон репозитория с github с помощью команды `git clone https://github.com/Yaroslav-Ze/labs_modern_technologies`. На консоль вывелось:

```
Cloning into 'labs_modern_technologies'...
info: please complete authentication in your browser...
remote: Enumerating objects: 33, done.
remote: Counting objects: 100% (33/33), done.
remote: Compressing objects: 100% (23/23), done.
remote: Total 33 (delta 5), reused 33 (delta 5), pack-reused 0 (from 0)
Receiving objects: 100% (33/33), 7.90 KiB | 1.97 MiB/s, done.
Resolving deltas: 100% (5/5), done.
```

Последние протоколы были добавлены уже в отчет-клон и закоммичены. Измененные данные были отправлены на удаленный репозиторий с помощью команды  `git push`, на консоль вывелось:

```
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (4/4), 2.27 KiB | 1.14 MiB/s, done.
Total 4 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/Yaroslav-Ze/labs_modern_technologies
   5ebb9f6..eac8591  main -> main
```

Была запрошена информация об изменениях и скачаны данные с удаленного репозитория с помощью команды `git fetch`, локальные данные не менялись, на консоль вывелось:

```
remote: Enumerating objects: 13, done.
remote: Counting objects: 100% (13/13), done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 9 (delta 3), reused 9 (delta 3), pack-reused 0 (from 0)
Unpacking objects: 100% (9/9), 2.86 KiB | 101.00 KiB/s, done.
From github.com:Yaroslav-Ze/labs_modern_technologies
   5ebb9f6..f884f1e  main       -> origin/main
```

Далее была использована команда `git pull`, которая произвела слияние скачанных данных с текущей веткой, таким образом синхронизировав содержимое репозитория. 

### История изменений

Получена сводка последних изменений с помощью `git log`. На консоль вывелось:

```
commit 21a585edaf6d6f0223f1037303ca6017fce5cc4c (HEAD -> main)
commit 21a585edaf6d6f0223f1037303ca6017fce5cc4c (HEAD -> main)
Merge: 2129ad6 f884f1e
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:45:53 2026 +0300

    Коммит скачанного с удаленного репозитория

commit 2129ad6644c7c21cc61b8031a5d31f8260d188dc
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:43:59 2026 +0300

    Коммит не клона

commit f884f1e3510d536ac38c87d0e391cf0a35c60921 (origin/main, origin/HEAD)
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:38:20 2026 +0300

    Косметические изменения отчета

commit eac8591b1bb7f11690aa6a78152284e312a4a948
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:33:23 2026 +0300

    Добавлены изменения по поводу клонирования в отчет-клон

commit 5ebb9f60a58da3fff77f12046fbc07e9e90b6edd
Merge: b5c2617 e723e1f
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 15:28:18 2026 +0300

    слияние веток и разрешения конфликта в README

commit e723e1fab61b6b81e61c986fdd45c922464b3e71
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 15:16:25 2026 +0300

    Правки в отчете и README.md для создания конфликта в ветке lab1-1

commit b5c2617d2a422ff3d8bf84b61c11b458a96f46d9
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 14:43:09 2026 +0300

    изменил заголовок в main для создания конфликта

commit 33d14df0a705e4875ca3aa633805ee53137ca341
Merge: 1463410 08cf181
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 14:10:17 2026 +0300

    Вернул все как было в README.md

commit 21a585edaf6d6f0223f1037303ca6017fce5cc4c (HEAD -> main)
Merge: 2129ad6 f884f1e
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:45:53 2026 +0300

    Коммит скачанного с удаленного репозитория

commit 2129ad6644c7c21cc61b8031a5d31f8260d188dc
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:43:59 2026 +0300

    Коммит не клона

commit f884f1e3510d536ac38c87d0e391cf0a35c60921 (origin/main, origin/HEAD)
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:38:20 2026 +0300

    Косметические изменения отчета

commit eac8591b1bb7f11690aa6a78152284e312a4a948
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 17:33:23 2026 +0300

    Добавлены изменения по поводу клонирования в отчет-клон

commit 5ebb9f60a58da3fff77f12046fbc07e9e90b6edd
Merge: b5c2617 e723e1f
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 15:28:18 2026 +0300

    слияние веток и разрешения конфликта в README

commit e723e1fab61b6b81e61c986fdd45c922464b3e71
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 15:16:25 2026 +0300

    Правки в отчете и README.md для создания конфликта в ветке lab1-1

commit b5c2617d2a422ff3d8bf84b61c11b458a96f46d9
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 14:43:09 2026 +0300

    изменил заголовок в main для создания конфликта

commit 33d14df0a705e4875ca3aa633805ee53137ca341
Merge: 1463410 08cf181
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 14:10:17 2026 +0300

    Вернул все как было в README.md

commit 08cf181776aa74a11e85312e4ea4b78df5965606
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 14:01:04 2026 +0300

    изменил README в lab1-1

commit 1463410dd9143d7c24321e072a8953a3d944dc33
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Sat Mar 14 13:59:00 2026 +0300

    изменил начало README в main

commit 96259e551ee701ec43fa351885068cc0f0abc530
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Fri Mar 13 23:36:14 2026 +0300

    Третий коммит: коммит в ветке lab1-1

commit ec670582f0002d795ee315c7e8331e063b213f5e
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Fri Mar 13 21:03:55 2026 +0300

    Второй коммит, добавлены измения ТОЛЬКО в lab1.md

commit 99bcd4f334ac9eb2833caa518a3aedf1bfb3e0c0
Author: Yaroslav Zelepukhin <yarzeltan@gmail.com>
Date:   Fri Mar 13 20:17:15 2026 +0300

    Первый коммит, readme.md и пустой lab1.md
```

На этом всё.

