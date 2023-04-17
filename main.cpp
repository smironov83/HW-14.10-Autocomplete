//�������� ���� ���������
#include <conio.h>
#include "autocomplete_dictionary.h"
#include <iostream>

//������� �� ����� ������� �������������� ����� �� ��������, ������� 
//������������ ����� �������������� ������ ����. ��������� ������� 
//�������������� ��������� � ���������� ����, ���������� ������� �������.
//������� ��������� �������������� �������� ���������� "<-", 
//����������� - "->'.
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
//���������, � ������� ����� ���������� ���� ����� �� ������ �����.
std::string stream;

//������� ����� � ������������� ��� ��������� ���������� �� stream.
void ScreenUpdate(void)
{
  system("cls");
  std::cout << stream;
}

//���� MAIN.
auto main() -> int
{
  //������������� ��������� 1251. ������� ����������.
  system("chcp 1251");
  system("cls");

  std::cout << "������������!\n\n� ������ ��������� ���������� ����� � �������"
    "��������� �������������� �� ���������� ��������.\n��������� �������� ����"
    "�� � ��������� ��������� ������ ��������.\n������� ������� ���������. ���"
    " ��������� ����� �� ��������� ����������� � �������.\n������������ ����� "
    "���������� ���������� �������������� �� �������� �������������� ���������"
    " ����� � ������.\n������� ����� ����������� �������������� <- � ->, �����"
    "���������.\n��� ������ �������� �������� �������������� ������� ������� �"
    "����.\n��� ������ �� ��������� ������� Escape.\n\nP.S.�� ������������� ��"
    "��������� ��������� � ������� ������ ������ �� �������� ���������.\n�����"
    "���, Backspace. �������� ������������� ��������� ���������.\n�� ��� �� ��"
    "���!\n\n";
  system("pause");
  system("cls");

  //�������������� ������� �������.
  std::string const words[] =
  {
    {"�����������"},
    {"������"},
    {"����"},
    {"�����"},
    {"�����"},
    {"����"},
    {"����"},
    {"���"},
    {"������"},
    {"�����"}
  };

  //�������������� ���������� ������ ������� ��������.
  AutocompleteDictionary* root = new AutocompleteDictionary;
  for (auto& word : words)
    root->Insert(root, word);

  //�������������� ��������������� ����������.
  char wordConstructor[100] = {};
  char symbol = {};
  size_t position = 0;
  std::string prefix;

  do
  {
    //��������� ��� ������� �������.
    symbol = _getch();
    //��������� �� ������� ������������ ���� ������� �������, � ����� true - 
    //��������� ��������.
    if (_kbhit())
      symbol = _getch();
    //Switch �� ���� ������� �������.
    switch (symbol)
    {
      //������. ��������� ����� �� ������� � ������. ������� ������� �������.
      //��������� ������ � stream. ��������� �����.
    case 32:
      root->Insert(root, prefix);
      prefix = {};
      stream.push_back(' ');
      ScreenUpdate();
      break;
      //Enter. ��������� ������� �� ��������� ������. ��������� ����� �� Enter
      //� ������. ������� ������� �������. ��������� ������� �� ��������� 
      //������ � stream. ��������� �����.
    case 13:
      std::cout << std::endl;
      root->Insert(root, prefix);
      prefix = {};
      stream.push_back('\n');
      ScreenUpdate();
      break;
      //������� �����. ��������� ������� �� ���������� �����, ���� ������� �� 
      //������. ���������� � stream. ������� ������� �������. ��������� �����.
    case 72:
      if (prefix != "")
        stream += root->prefixes_[position] + " ";
      prefix = {};
      ScreenUpdate();
      break;
      //������� �����. ���� ���� ���������� ������� ���������� �������� - 
      //������� ���.
    case 75:
      if (position > 0 && root->prefCount != 0)
      {
        ScreenUpdate();
        --position;
        PrintAutocomplete(root, position);
      }
      break;
      //������� ������. ���� ���� ����������� ������� ���������� �������� - 
      //������� ���.
    case 77:
      if (position + 1 < root->prefCount)
      {
        ScreenUpdate();
        ++position;
        PrintAutocomplete(root, position);
      }
      break;
      //��� ��������� �������� ���� ������� �������. ��������� � stream.
      //���� ������ �� ��������� - ��������� � �������� ��������.
      //����� - ��������� ������� ������� � ������ � ������� ������� �������.
      //���� ������� ������� �� ������ � ���������� � ������ - ��������� �����
      //���� ���� ��� �������� � ������. �� ��������� ������� ������ �� 
      //��������� � �������� �������/���������� ����������� ���������.
    default:
      stream.push_back(symbol);
      position = 0;
      ScreenUpdate();
      if (symbol - '�' >= -32 && symbol - '�' <= 31)
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
    //Esc. ������� �� ������������ �����.
  } while (symbol != 27);
  //������� ���������� ������.
  delete root;
  return 0;
}