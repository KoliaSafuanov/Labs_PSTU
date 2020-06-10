#ifndef GRAPH_T
#define GRAPH_T
#include "glfunc.h"
#include <vector>
#include <iomanip>
#include <iostream>

extern bool* Mouse_Vert;
int COL, KommiRez = -1;
std::string  p;
class Graph; //прототип класса 
void drawVertex(int n, Graph& graph); //прототип функции drawVertex
int Circle_Check(int x, int y, Graph& graph); //прототип функции Circle_Check
void mouseMove(int x, int y); //прототип функции mouseMove

struct Edge{
  int from;
  int dest;
};

class Graph
{
private:
  std::vector<Edge> rez; //Вектор пути
  int **adjMatrix;//Матрица смежности
public:
  std::vector<std::string> vertList; //Вектор вершин
  Graph() {this->InsertMatrix();}
  int GetAmountVerts() { return vertList.size(); }
  void InsertMatrix()//Ввод матрицы с клавиатуры
  {
    setlocale(LC_ALL, "ru");
    std::cout << "Введите количество вершин: ";std::cin >> COL;
    adjMatrix = new int* [COL];//Матрица смежности
    for (int i = 0; i < COL; i++) { adjMatrix[i] = new int[COL]; }
    std::cout << "Введите " << COL << " вершин: ";
    for (int i = 0; i < COL; i++)
    {
      std::string temp;
      std::cin >> temp;
      vertList.push_back(temp);
    }

    for (int i = 0; i < COL; i++)
    {
      for (int j = i; j < COL; j++)
      {
        if (i == j) adjMatrix[i][j] = -1;
        else
        {
          std::cout << "Введите вес ребра " << vertList[i] << " -> " << vertList[j] << ": ";
          std::cin >> adjMatrix[i][j];
          adjMatrix[j][i] = adjMatrix[i][j];
        }
      }
    }
    return;
  };

  void PrintMatrix(int** matrix) //Печать матрицы
  {
    for (int i = 0; i < COL; i++)
    {
      std::cout << std::setw(2) << vertList[i] << ' ';
      for (int j = 0; j < COL; j++)
      {
        if (matrix[i][j] == -1) std::cout << "[] ";
        else std::cout << std::setw(2) << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }
  };

  void RedRows(int** matrix) //Редукция строк
  {
    for (int i = 0; i < COL; i++) //Проход по столбцам
    {
      std::cout << std::setw(2) << vertList[i] << ' ';
      for (int j = 0; j < COL; j++)
      {
        if (matrix[i][j] == -1) std::cout << "[] ";
        else std::cout << std::setw(2) << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }
  };

  void RedCols(int** map) //Редукция столбцов
  {
    for (int j = 0; j < COL; j++) //Проход по столбцам
    {
      int min = INT32_MAX; //Минимум для каждого столбца вычисляется заново

      for (int i = 0; i < COL; i++) //Проход по ячейкам столбца
      {
        if ((map[i][j] < min) && (map[i][j] >= 0)) //Если ячейка меньше минимума и не является путём в тот же город
          min = map[i][j]; //обновляем минимум
      }

      for (int i = 0; i < COL; i++) //Редукция столбца
        if (map[i][j] != -1) //Если не путь в тот же город
          map[i][j] -= min; //вычитаем минимум
    }
  };

  int ZeroRows(int** map, int row, int nCheck) //Оценка нулей в строках
  {
    int min = INT32_MAX; // Создаем переменную минимального элемента
    for (int j = 0; j < COL; j++) // Проходим каждый столбец в заданной строке
      if (j != nCheck) // Координаты столбца не совпали с заданными
        if ((min > map[row][j]) && (map[row][j] >= 0)) // Ищем минимум
          min = map[row][j]; // Обновляем значение переменной

    return min; // Возвращаем минимальное значение
  };

  int ZeroCols(int** map, int nCheck, int col) //Оценка нулей в столбцах
  {
    int min = INT32_MAX; //Минимум

    for (int i = 0; i < col; i++) //Проходим все строки в столбце
      if (i != nCheck) //строка не совпала с заданной
        if ((map[i][col] < min) && (map[i][col] >= 0)) //Поиск минимума
          min = map[i][col];

    return min;
  };

  Edge ClearMap(int** map) //Удаление строки и столбца с наибольшим нулём
  {
    Edge temp;

    int max = -1, k, l; //Максимальный оцененный ноль, координаты его строки и столбца

    for (int i = 0; i < COL; i++)
    {
      for (int j = 0; j < COL; j++)
      {
        if (map[i][j] == 0)
        {
          int tSum = this->ZeroRows(map, i, j) + this->ZeroCols(map, j, i);
          if (tSum >= max)
          {
            max = tSum;
            k = i;
            l = j;
          }
        }
      }
    }

    for (int i = 0; i < COL; i++)
      for (int j = 0; j < COL; j++)
      {
        if (i == k) map[i][j] = -1;
        if (j == l) map[i][j] = -1;
      }

    temp.from = k;
    temp.dest = l;

    return temp;
  };

  void Kommi() //Алгоритм решения задачи коммивояжёра
  {
    int col = COL;
    int** map = new int* [col];
    for (int i = 0; i < col; i++) map[i] = new int[col];

    for (int i = 0; i < col; i++)
      for (int j = 0; j < col; j++)
        map[i][j] = adjMatrix[i][j];

    int i = 0;
    while (i != col - 2) //Основной цикл
    {
      RedRows(map);
      std::cout << i + 1 << ". Редукция строк\n";
      PrintMatrix(map);

      RedCols(map);
      std::cout << i + 1 << ". Редукция столбцов\n";
      PrintMatrix(map);

      rez.push_back(ClearMap(map));

      std::cout << i + 1 << ". Новая матрица\n";
      PrintMatrix(map);

      i++;
    }

  for (int i = 1; i < rez.size(); i++)
    {
      for (int j = i; j < rez.size(); j++)
        if (rez[i].from == rez[j].dest) std::swap(rez[i], rez[j]);
    }//Создание пути
    p += "Way: "+ vertList[rez[0].from] + " -> " + vertList[rez[0].dest] + " -> ";
    for (int i = 1; i < rez.size(); i++)
    {
      if (rez[i - 1].dest != rez[i].from) p += vertList[rez[i].from] + " -> " + vertList[rez[i].dest] + " -> ";
      else p += vertList[rez[i].dest] + " -> ";
    }
   
    {
      p += vertList[rez[0].from];
      std::string* s = new std::string;
      for (int i = 0; i < p.size(); i++)
      {
        *s += p[i];
      }
      p = *s;
      delete s;
    }
    std::cout << std::endl << p;

    int a = adjMatrix[rez[i - 1].dest][rez[0].from]; // Расстояние от последней вершины до первой
    a += adjMatrix[rez[0].from][rez[0].dest]; // Расстояние первого ребра

    for (int i = 1; i < rez.size(); i++) // Проходим по массиву структур
      a += adjMatrix[rez[i].from][rez[i].dest]; // Прибавим расстояние i-того ребра 

    for (int i = 0; i < rez.size() - 1; i++) // Проходим по массиву структур
      if (rez[i].dest != rez[i + 1].from) // Если поля равны, то расстояние от вершины А до А считаем равным 0
        a += adjMatrix[rez[i].dest][rez[i + 1].from]; // Считаем расстояние между ребрами 

    std::cout << "\nРасстояние: " << a << '\n';
    KommiRez = a;

    for (int i = 0; i < col; i++) delete[] map[i];
    delete[] map;
  }

  void DrawGraph()//Отрисовка графа
  {

    int n = vertList.size();
    for (int i = 0; i < n; i++)
    {
      setCoord(i, n);//Устанавливаются координаты
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0 /*i + 1*/; j < n; j++)
      {
        int a = adjMatrix[i][j]; //a -- int, потому что это вес ребра
        if (a > 0) //не рисуем ребро из А в А (оно равно -1)
        {
          drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
        }
      }
    }
    drawVertex(n, *this);
    if (KommiRez == -1) Kommi();
    drawRez(KommiRez, p);
  }
};

int Circle_Check(int x, int y, Graph& graph)//Проверка наличия курсора в круге - вершине графа
{
  for (int i = 0; i < graph.GetAmountVerts(); i++)
    if (pow(x - vertC[i].x, 2) + pow(y - vertC[i].y, 2) <= pow(R, 2))
      return i;
  return -1;
}
bool* Mouse_Vert = new bool[COL] ;

void drawVertex(int n, Graph& graph)//Отрисовка вершин графа
{
  for (int i = 0; i < n; i++)
  {
    if (Mouse_Vert[i])//Если курсор наведён, то жёлтым цветом
      drawBorderedCircle(vertC[i].x, vertC[i].y, R);
    else
      drawCircle(vertC[i].x, vertC[i].y, R);//Иначе - красным
    drawText(graph.vertList[i], vertC[i].x, vertC[i].y);
  }
}

#endif