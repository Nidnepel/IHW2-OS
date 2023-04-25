# Отчет 
## Вариант 23
Лепендин Дмитрий Алексеевич, студент группы БПИ-218

### Условие задачи
```
Задача об инвентаризации по книгам. После нового года в
библиотеке университета обнаружилась пропажа каталога. После
поиска и наказания, виноватых ректор дал указание восстановить
каталог силами студентов. Фонд библиотека представляет собой
прямоугольное помещение, в котором находится M рядов по N шкафов по K книг в каждом шкафу. Требуется создать приложение, составляющее каталог. При решении задачи в качестве
отдельного процесса задается внесение в каталог записи об отдельной книге, которая сразу ставится на место в соответствии с выбранным методом упорядочения каталога. Примечание. Каталог —
это список книг, упорядоченный по их инвентарному номеру или
по алфавиту (на выбор разработчика). Каждая строка каталога содержит идентифицирующее значение (номер или название),
номер ряда, номер шкафа, номер книги в шкафу.
```

### Схема решаемой задачи
- В программе будут взаимодействовать два процесса. 
- Процесс-поставщик который генерирует идентифицирующие номера книг в рандомном порядке 
- И процесс-обработчик который принимает номера по одному и вычисляет место в каталоге
- Процесс-поставщик стартует первым и выделяет все ресурсы. Далее начинает передовать номера по одному
- Когда поставщик снимает блок семафора, сигнализируя обработчкику что появились данные тот блочит семафором процесс-поставщик
- И обрабатывает их, затем снимает блок и ждет новые данные.
- После завершения обработки или прерывания сигналом процесс обработчик завершается, а затем поставщик чистит все данные
- И тоже завершается.


### Запуск программы

Файлу catalog_filling.out на вход передается 3 аргумента: количество рядов, количество шкафов и количество книг в шкафу.

Пример запуска:

```bash
./catalog_filling.out 2 1 5
```

### Пример работы программы
```
/home/lependin/CLionProjects/IHW2_OS/cmake-build-debug/IHW2_OS 2 2 4
Book numbers: 5 13 4 14 9 16 12 3 15 8 7 2 1 10 11 6 
Producer give book: 5
Handler took book: 5
Handler set book in 1 row/ 2 bookshelf/ 1 place
Producer give book: 13
Handler took book: 13
Handler set book in 2 row/ 2 bookshelf/ 1 place
Producer give book: 4
Handler took book: 4
Handler set book in 1 row/ 1 bookshelf/ 4 place
Producer give book: 14
Handler took book: 14
Handler set book in 2 row/ 2 bookshelf/ 2 place
Producer give book: 9
Handler took book: 9
Handler set book in 2 row/ 1 bookshelf/ 1 place
Producer give book: 16
Handler took book: 16
Handler set book in 2 row/ 2 bookshelf/ 4 place
Producer give book: 12
Handler took book: 12
Handler set book in 2 row/ 1 bookshelf/ 4 place
Producer give book: 3
Handler took book: 3
Handler set book in 1 row/ 1 bookshelf/ 3 place
Producer give book: 15
Handler took book: 15
Handler set book in 2 row/ 2 bookshelf/ 3 place
Producer give book: 8
Handler took book: 8
Handler set book in 1 row/ 2 bookshelf/ 4 place
Producer give book: 7
Handler took book: 7
Handler set book in 1 row/ 2 bookshelf/ 3 place
Producer give book: 2
Handler took book: 2
Handler set book in 1 row/ 1 bookshelf/ 2 place
Producer give book: 1
Handler took book: 1
Handler set book in 1 row/ 1 bookshelf/ 1 place
Producer give book: 10
Handler took book: 10
Handler set book in 2 row/ 1 bookshelf/ 2 place
Producer give book: 11
Handler took book: 11
Handler set book in 2 row/ 1 bookshelf/ 3 place
Producer give book: 6
Handler took book: 6
Handler set book in 1 row/ 2 bookshelf/ 2 place
Handler finished
```

#### Task4

В коде на 4 используются именованные семафоры Posix.

#### Task5

В коде на 5 используются неименованные семафоры Posix.
