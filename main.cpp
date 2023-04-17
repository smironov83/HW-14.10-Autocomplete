//Основной блок программы
#include <conio.h>
#include "autocomplete_dictionary.h"
#include <iostream>

//Выводит на экран вариант автодополнения слова по префиксу, выделяя 
//предлагаемую часть альтернативным цветом фона. Проверяет наличие 
//альтернативных вариантов в контейнере слов, содержащих текущий префикс.
//Наличие вариантов предшествующих текущему отмечается "<-", 
//последующих - "->'.
void PrintAutocomplete(AutocompleteDictionary* root, size_t position)
{
  printf_s("\033[46m");
  std::cout << root->prefixes_[position];
  printf_s("\033[0m");
  if (position > 0)
    std::cout << "<-";
  if (root->prefCount > position + 1)
    std::cout << "->";
}
//Контейнер, в которую будет складывать весь поток из строки ввода.
std::string stream;

//Очищает экран и актуализирует всю введенную информацию из stream.
void ScreenUpdate(void)
{
  system("cls");
  std::cout << stream;
}

//Блок MAIN.
auto main() -> int
{
  //Устанавливает кодировку 1251. Выводит инструкцию.
  system("chcp 1251");
  system("cls");

  std::cout << "Здравствуйте!\n\nВ данной программе реализован поиск в словаре"
    "вариантов автодополнения по введенному префиксу.\nПрограмма работает толь"
    "ко с символами кириллицы любого регистра.\nБазовый словарь ограничен. Все"
    " введенные слова на кириллице добавляются в словарь.\nПереключение между "
    "доступными вариантами автодополнения по префиксу осуществляется стрелками"
    " влево и вправо.\nНаличие такой возможности подсвечивается <- и ->, соотв"
    "етственно.\nДля выбора текущего варианта автодополнения нажмите стрелку в"
    "верх.\nДля выхода из программы нажмите Escape.\n\nP.S.Не рекомендуется пе"
    "ремещение указателя в сторону начала строки от текущего положения.\nНапри"
    "мер, Backspace. Возможно неопредленное поведение программы.\nНо это не то"
    "чно!\n\n";
  system("pause");
  system("cls");

  //Инициализирует базовый словарь.
  std::string const words[] =
  {
    {"палеонтолог"},
    {"привет"},
    {"пока"},
    {"пошли"},
    {"банан"},
    {"бука"},
    {"бяка"},
    {"бор"},
    {"бамбук"},
    {"поток"}
  };

  //Инициализирует префиксное дерево базовым словарем.
  AutocompleteDictionary* root = new AutocompleteDictionary;
  for (auto& word : words)
    root->Insert(root, word);

  //Инициализирует вспомогательные переменные.
  char wordConstructor[100] = {};
  char symbol = {};
  size_t position = 0;
  std::string prefix;

  do
  {
    //Считывает код нажатой клавиши.
    symbol = _getch();
    //Проверяет на наличие расширенного кода нажатой клавиши, в случе true - 
    //считывает повторно.
    if (_kbhit())
      symbol = _getch();
    //Switch по коду нажатой клавиши.
    switch (symbol)
    {
      //Пробел. Сохраняет слово до пробела в дерево. Очищает текущий префикс.
      //Добавляет пробел в stream. Обновляет экран.
    case 32:
      root->Insert(root, prefix);
      prefix = {};
      stream.push_back(' ');
      ScreenUpdate();
      break;
      //Enter. Переводит каретку на следующую строку. Сохраняет слово до Enter
      //в дерево. Очищает текущий префикс. Добавляет переход на следующую 
      //строку в stream. Обновляет экран.
    case 13:
      std::cout << std::endl;
      root->Insert(root, prefix);
      prefix = {};
      stream.push_back('\n');
      ScreenUpdate();
      break;
      //Стрелка вверх. Дополняет префикс до выбранного слова, если префикс не 
      //пустой. Дописывает в stream. Очищает текущий префикс. Обновляет экран.
    case 72:
      if (prefix != "")
        stream += root->prefixes_[position] + " ";
      prefix = {};
      ScreenUpdate();
      break;
      //Стрелка влево. Если есть предыдущий вариант дополнения префикса - 
      //выводит его.
    case 75:
      if (position > 0 && root->prefCount != 0)
      {
        ScreenUpdate();
        --position;
        PrintAutocomplete(root, position);
      }
      break;
      //Стрелка вправо. Если есть последующий вариант дополнения префикса - 
      //выводит его.
    case 77:
      if (position + 1 < root->prefCount)
      {
        ScreenUpdate();
        ++position;
        PrintAutocomplete(root, position);
      }
      break;
      //Все остальные варианты кода нажатой клавиши. Добавляет в stream.
      //Если символ на кириллице - добавляет к текущему префиксу.
      //Иначе - сохраняет текущий префикс в дереве и очищает текущий префикс.
      //Если текущий префикс не пустой и содержится в дереве - запускает поиск
      //всех слов про префиксу в дереве. По умолчанию выводит первый из 
      //найденных и помечает наличие/отстуствие последующих вариантов.
    default:
      stream.push_back(symbol);
      position = 0;
      ScreenUpdate();
      if (symbol - 'а' >= -32 && symbol - 'а' <= 31)
        prefix.push_back(symbol);
      else
      {
        root->Insert(root, prefix);
        prefix = "";
      }
      if (root->Search(root, prefix) && prefix != "")
      {
        root->FindAllPrefixes(root, wordConstructor, 0, prefix);
        PrintAutocomplete(root, position);
      }
      break;
    }
    //Esc. Выходит из циклического ввода.
  } while (symbol != 27);
  //Удаляет префиксное дерево.
  delete root;
  return 0;
}